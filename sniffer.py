import threading
import queue
import time
import csv
from scapy.all import sniff, wrpcap
from pythonosc import dispatcher, osc_server
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from collections import deque

class osc_data:
    def __init__(self, addr, args):
        self.addr = addr
        self.ax = args[0]
        self.ay = args[1]
        self.az = args[2]
        self.ex = args[3]
        self.ey = args[4]
        self.ez = args[5]
        self.gx = args[6]
        self.gy = args[7]
        self.gz = args[8]
        self.mx = args[9]
        self.my = args[10]
        self.mz = args[11]
        self.qw = args[12]
        self.qx = args[13]
        self.qy = args[14]
        self.qz = args[15]
        # args[16] aka datagram17 is undocumented
        self.battery = args[17]
        self.sys_status = args[18]
        self.gyro_status = args[19]
        self.accl_status = args[20]
        self.mag_status = args[21]
        self.seconds = args[22]
        self.seqnum = args[23]


def quat_to_euler_degrees(qw, qx, qy, qz):
    """
    Convert quaternion (qw, qx, qy, qz) to Euler angles (roll, pitch, yaw) in degrees.
    Uses the convention: roll around X, pitch around Y, yaw around Z (Tait-Bryan ZYX).
    """
    # Normalize quaternion to avoid errors
    import math
    norm = math.sqrt(qw*qw + qx*qx + qy*qy + qz*qz)
    if norm == 0:
        return 0.0, 0.0, 0.0
    qw /= norm
    qx /= norm
    qy /= norm
    qz /= norm

    # roll (x-axis rotation)
    sinr_cosp = 2 * (qw * qx + qy * qz)
    cosr_cosp = 1 - 2 * (qx * qx + qy * qy)
    roll = math.atan2(sinr_cosp, cosr_cosp)

    # pitch (y-axis rotation)
    sinp = 2 * (qw * qy - qz * qx)
    if abs(sinp) >= 1:
        pitch = math.copysign(math.pi / 2, sinp)  # use 90 degrees if out of range
    else:
        pitch = math.asin(sinp)

    # yaw (z-axis rotation)
    siny_cosp = 2 * (qw * qz + qx * qy)
    cosy_cosp = 1 - 2 * (qy * qy + qz * qz)
    yaw = math.atan2(siny_cosp, cosy_cosp)

    # convert to degrees
    return (math.degrees(roll), math.degrees(pitch), math.degrees(yaw))


IP = "0.0.0.0"
UDP_PORT = 4000
# CHANGE THESE NOT TO OVERWRITE
CAPTURE_FILE = "osc_capture3.pcap"
CSV_FILE = "osc_capture3.csv"
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
        d = osc_data(address, args)
        data_queue.put(d)
        # LOG TO CSV HERE FOR SOME REASON
        log_csv(d)

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
            # writer.writerow(["acclx", "accly", "acclz"])
            writer.writerow([CSV_FILE])

def log_csv(data):
    with csv_lock:
        with open(CSV_FILE, "a", newline="") as f:
            writer = csv.writer(f)
            row = list(data.__dict__.values()) #convert to list
            writer.writerow(row)

# --- Live plotting ---
def live_plot():
    plt.style.use("dark_background")

    # Four stacked subplots: Accel, Gyro, Mag, Orientation
    fig, axes = plt.subplots(4, 1, sharex=True, figsize=(10, 10))
    ax_accel, ax_gyro, ax_mag, ax_orient = axes

    history = 300  # number of samples to keep
    colors = ["r", "g", "b"]

    # Deques for time and each axis for each sensor
    times = deque(maxlen=history)

    aX = deque(maxlen=history)
    aY = deque(maxlen=history)
    aZ = deque(maxlen=history)

    gX = deque(maxlen=history)
    gY = deque(maxlen=history)
    gZ = deque(maxlen=history)

    mX = deque(maxlen=history)
    mY = deque(maxlen=history)
    mZ = deque(maxlen=history)

    # Orientation deques (roll, pitch, yaw in degrees)
    r = deque(maxlen=history)
    p = deque(maxlen=history)
    y = deque(maxlen=history)

    # Create line objects
    a_lines = [ax_accel.plot([], [], color=colors[i], label=f"A{axis}")[0] for i, axis in enumerate(["X", "Y", "Z"])]
    g_lines = [ax_gyro.plot([], [], color=colors[i], label=f"G{axis}")[0] for i, axis in enumerate(["X", "Y", "Z"])]
    m_lines = [ax_mag.plot([], [], color=colors[i], label=f"M{axis}")[0] for i, axis in enumerate(["X", "Y", "Z"])]
    o_lines = [ax_orient.plot([], [], color=colors[i], label=l)[0] for i, l in enumerate(["Roll", "Pitch", "Yaw"])]

    # Configure axes
    ax_accel.set_title("Acceleration")
    ax_gyro.set_title("Gyroscope")
    ax_mag.set_title("Magnetometer")
    ax_orient.set_title("Rotation")

    for ax in (ax_accel, ax_gyro, ax_mag, ax_orient):
        ax.grid(True, alpha=0.3)
        ax.legend(loc="upper right")

    ax_accel.set_ylabel("m/s^2 or raw")
    ax_gyro.set_ylabel("deg/s or raw")
    ax_mag.set_ylabel("uT or raw")
    ax_mag.set_xlabel("time (s)")
    ax_orient.set_xlabel("time (s)")

    def update(frame):
        updated = False
        # drain queue
        while not data_queue.empty():
            d = data_queue.get()
            t = time.time() - start_time
            times.append(t)

            aX.append(d.ax)
            aY.append(d.ay)
            aZ.append(d.az)

            gX.append(d.gx)
            gY.append(d.gy)
            gZ.append(d.gz)

            mX.append(d.mx)
            mY.append(d.my)
            mZ.append(d.mz)

            # compute roll/pitch/yaw from quaternion fields
            roll, pitch, yawv = quat_to_euler_degrees(d.qw, d.qx, d.qy, d.qz)
            r.append(roll)
            p.append(pitch)
            y.append(yawv)

            updated = True

        if not times:
            return a_lines + g_lines + m_lines

        # update line data
        for line, seq in zip(a_lines, (aX, aY, aZ)):
            line.set_data(times, seq)
        for line, seq in zip(g_lines, (gX, gY, gZ)):
            line.set_data(times, seq)
        for line, seq in zip(m_lines, (mX, mY, mZ)):
            line.set_data(times, seq)
        for line, seq in zip(o_lines, (r, p, y)):
            line.set_data(times, seq)

        # Adjust x-limits
        xmin, xmax = times[0], times[-1]
        for ax in (ax_accel, ax_gyro, ax_mag):
            ax.set_xlim(xmin, xmax + 0.001)

        # Optional: autoscale y per subplot with some padding
        def autoscale(ax, sequences, pad=0.1):
            all_vals = []
            for s in sequences:
                if s:
                    all_vals.extend(s)
            if not all_vals:
                return
            mn, mx = min(all_vals), max(all_vals)
            if mn == mx:
                mn -= 0.5
                mx += 0.5
            rng = mx - mn
            ax.set_ylim(mn - rng * pad, mx + rng * pad)

        autoscale(ax_accel, (aX, aY, aZ))
        autoscale(ax_gyro, (gX, gY, gZ))
        autoscale(ax_mag, (mX, mY, mZ))
        autoscale(ax_orient, (r, p, y))

        return a_lines + g_lines + m_lines

    ani = animation.FuncAnimation(fig, update, interval=100, blit=False)
    plt.tight_layout()
    plt.show()

# --- Run all ---
if __name__ == "__main__":
    start_time = time.time()
    init_csv()
    threading.Thread(target=capture_packets, daemon=True).start()
    threading.Thread(target=flush_packets, daemon=True).start()
    threading.Thread(target=start_osc_server, daemon=True).start()
    live_plot()
