import csv
import matplotlib.pyplot as plt
from collections import defaultdict
from math import degrees, atan2, asin, copysign, sqrt
import numpy as np

CSV_FILE = "osc_capture1.csv"

def quat_to_euler_degrees(qw, qx, qy, qz):
    """Convert quaternion to Euler angles (roll, pitch, yaw) in degrees."""
    norm = sqrt(qw*qw + qx*qx + qy*qy + qz*qz)
    if norm == 0:
        return 0.0, 0.0, 0.0
    qw /= norm
    qx /= norm
    qy /= norm
    qz /= norm

    sinr_cosp = 2 * (qw * qx + qy * qz)
    cosr_cosp = 1 - 2 * (qx * qx + qy * qy)
    roll = atan2(sinr_cosp, cosr_cosp)

    sinp = 2 * (qw * qy - qz * qx)
    pitch = copysign(np.pi / 2, sinp) if abs(sinp) >= 1 else asin(sinp)

    siny_cosp = 2 * (qw * qz + qx * qy)
    cosy_cosp = 1 - 2 * (qy * qy + qz * qz)
    yaw = atan2(siny_cosp, cosy_cosp)

    return degrees(roll), degrees(pitch), degrees(yaw)

def read_csv(file_path):
    data = defaultdict(list)
    with open(file_path, newline="") as f:
        reader = csv.reader(f)
        next(reader, None)  # skip header if any
        for row in reader:
            # skip rows that are just the file name line
            if len(row) < 24 or not row[0].startswith("/"):
                continue
            try:
                # Map each field
                (
                    addr, ax, ay, az, ex, ey, ez,
                    gx, gy, gz, mx, my, mz,
                    qw, qx, qy, qz,
                    battery, sys_status, gyro_status,
                    accl_status, mag_status, seconds, seqnum
                ) = row
                # Convert to float where needed
                data["time"].append(float(seconds))
                data["ax"].append(float(ax))
                data["ay"].append(float(ay))
                data["az"].append(float(az))
                data["gx"].append(float(gx))
                data["gy"].append(float(gy))
                data["gz"].append(float(gz))
                data["mx"].append(float(mx))
                data["my"].append(float(my))
                data["mz"].append(float(mz))
                roll, pitch, yaw = quat_to_euler_degrees(float(qw), float(qx), float(qy), float(qz))
                data["roll"].append(roll)
                data["pitch"].append(pitch)
                data["yaw"].append(yaw)
            except ValueError:
                continue
    return data

def plot_data(data):
    plt.style.use("dark_background")
    fig, axes = plt.subplots(4, 1, sharex=True, figsize=(10, 10))

    t = np.array(data["time"]) - min(data["time"])  # start at 0

    # Plot acceleration
    axes[0].plot(t, data["ax"], 'r', label="Ax")
    axes[0].plot(t, data["ay"], 'g', label="Ay")
    axes[0].plot(t, data["az"], 'b', label="Az")
    axes[0].set_ylabel("Accel (m/s²)")
    axes[0].legend()
    axes[0].grid(alpha=0.3)

    # Plot gyro
    axes[1].plot(t, data["gx"], 'r', label="Gx")
    axes[1].plot(t, data["gy"], 'g', label="Gy")
    axes[1].plot(t, data["gz"], 'b', label="Gz")
    axes[1].set_ylabel("Gyro (°/s)")
    axes[1].legend()
    axes[1].grid(alpha=0.3)

    # Plot magnetometer
    axes[2].plot(t, data["mx"], 'r', label="Mx")
    axes[2].plot(t, data["my"], 'g', label="My")
    axes[2].plot(t, data["mz"], 'b', label="Mz")
    axes[2].set_ylabel("Mag (µT)")
    axes[2].legend()
    axes[2].grid(alpha=0.3)

    # Plot Euler angles
    axes[3].plot(t, data["roll"], 'r', label="Roll")
    axes[3].plot(t, data["pitch"], 'g', label="Pitch")
    axes[3].plot(t, data["yaw"], 'b', label="Yaw")
    axes[3].set_xlabel("Time (s)")
    axes[3].set_ylabel("Rotation (°)")
    axes[3].legend()
    axes[3].grid(alpha=0.3)

    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    data = read_csv(CSV_FILE)
    if not data["time"]:
        print("No valid data found in CSV.")
    else:
        plot_data(data)
