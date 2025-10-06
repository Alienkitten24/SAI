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

from pythonosc import dispatcher, osc_server

def handler(address, *args):
    print(f"Received OSC: {address} {args}")

# Map OSC address patterns to handler functions
disp = dispatcher.Dispatcher()
disp.map("/*", handler)  # catch all messages

ip = "0.0.0.0"   # listen on all interfaces
port = 4000      # the UDP port your device sends OSC to

server = osc_server.BlockingOSCUDPServer((ip, port), disp)
print(f"Listening for OSC on {ip}:{port}...")
server.serve_forever()
