# from scapy.all import * 
    
# def handle_packet(pkt):
#     print(pkt.summary())
#     if pkt.haslayer("UDP"):
#         # print(f"{pkt[IP].src}:{pkt[UDP].sport} -> {pkt[IP].dst}:{pkt[UDP].dport}")
#         # print("Payload:", bytes(pkt[UDP].payload))
#         payload = bytes(pkt[UDP].payload)
#         hex_spaced = " ".join(f"{b:02x}" for b in payload)
#         # print(f"{pkt[IP].src}:{pkt[UDP].sport} -> {pkt[IP].dst}:{pkt[UDP].dport}")

#         print(hex_spaced)

# print("starting")
# sniff(filter="udp port 4000", prn=handle_packet)

# from pythonosc import dispatcher, osc_server

# def handler(address, *args):
#     print(f"Received OSC: {address} {args}")

# # Map OSC address patterns to handler functions
# disp = dispatcher.Dispatcher()
# disp.map("/*", handler)  # catch all messages

# ip = "0.0.0.0"   # listen on all interfaces
# port = 4000      # the UDP port your device sends OSC to

# server = osc_server.BlockingOSCUDPServer((ip, port), disp)
# print(f"Listening for OSC on {ip}:{port}...")
# server.serve_forever()

import threading
import queue
import time
import csv
from scapy.all import sniff, wrpcap
from pythonosc import dispatcher, osc_server
import matplotlib.pyplot as plt
import matplotlib.animation as animation

IP = "0.0.0.0"
UDP_PORT = 4000
CAPTURE_FILE = "osc_capture.pcap"
CSV_FILE = "osc_capture.csv"
packet_buffer = []
capture_lock = threading.Lock()
csv_lock = threading.Lock()

# Shared queue for data between OSC thread and plot thread
data_queue = queue.Queue()

# --- OSC handling ---
def osc_handler(address, *args):
    # print(f"OSC: {address} {args}")
    # push data for plotting
    if args and isinstance(args[0], (int, float)):
        data_queue.put((address, args[0], args[1], args[2]))
        # LOG TO CSV HERE FOR SOME REASON
        log_csv(args[0], args[1], args[2])

def start_osc_server():
    disp = dispatcher.Dispatcher()
    disp.map("/*", osc_handler)
    server = osc_server.BlockingOSCUDPServer((IP, UDP_PORT), disp)
    print(f"[OSC] Listening on {IP}:{UDP_PORT}...")
    server.serve_forever()

# --- Packet capture ---
def capture_packets():
    print(f"[CAPTURE] Writing packets to {CAPTURE_FILE}...")

    def pkt_handler(pkt): 
        with capture_lock:
            packet_buffer.append(pkt)

    sniff(filter=f"udp port {UDP_PORT}", prn=pkt_handler, store=False)

def flush_packets():
    while True:
        time.sleep(3)
        with capture_lock:
            if packet_buffer:
                wrpcap(CAPTURE_FILE, packet_buffer, append=True)
                packet_buffer.clear()
                print("flush to disk")

# --- CSV logging --- 
def init_csv():
    with csv_lock:
        with open(CSV_FILE, "w", newline="") as f:
            writer = csv.writer(f)
            writer.writerow(["acclx", "accly", "acclz"])

def log_csv(acclx, accly, acclz):
    with csv_lock:
        with open(CSV_FILE, "a", newline="") as f:
            writer = csv.writer(f)
            row = [acclx, accly, acclz]
            writer.writerow(row)

# --- Live plotting ---
def live_plot():
    plt.style.use("dark_background")
    fig, ax = plt.subplots()
    ax.set_title("Live OSC Data")
    ax.set_xlabel("Time (s)")
    ax.set_ylabel("Value")

    # Fixed Y-axis range (adjust as needed)
    ax.set_ylim(-5, 5)

    lines = []
    xdata = []
    yseries = []
    colors = ["r", "g", "b"]

    # Store time series per OSC address
    data_dict = {}  # {address: (xdata, ydata, line)}

    def update(frame):
        current_time = time.time() - start_time
        # Process all new data in the queue
        while not data_queue.empty():
            address, acclx, accly, acclz = data_queue.get()
            if not lines:
                for i in range(3):
                    (line,) = ax.plot([],[],colors[i%3],label=f"val[{i}]")
                    lines.append(line)
                    yseries.append([])
                ax.legend(loc="upper right")
            xdata.append(current_time)
            yseries[0].append(acclx)
            yseries[1].append(accly)
            yseries[2].append(acclz)
            if len(xdata) > 300:
                xdata.pop(0)
                yseries[0].pop(0)
                yseries[1].pop(0)
                yseries[2].pop(0)

        for i, line in enumerate(lines):    
            line.set_data(xdata, yseries[i])

        # Rescale x-axis only
        if xdata:
            ax.set_xlim(xdata[0], xdata[-1]+1)

        return lines

    ani = animation.FuncAnimation(fig, update, interval=100)
    plt.show()

# --- Run all ---
if __name__ == "__main__":
    start_time = time.time()
    init_csv()
    threading.Thread(target=capture_packets, daemon=True).start()
    threading.Thread(target=flush_packets, daemon=True).start()
    threading.Thread(target=start_osc_server, daemon=True).start()
    live_plot()
