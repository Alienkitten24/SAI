"""
saves CSVs, live plt plotting, sends UDP to plugdata
"""

import asyncio
from bleak import BleakScanner, BleakClient
import struct
import csv
import time
import socket 
import os
import datetime 

# Your specific UUIDs
TARGET_SERVICE_UUID = "12341000-1234-1234-1234-123456789abc"
CHARACTERISTIC_UUID = "12345678-1234-1234-1234-123456789ab1"

timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
file_save = os.path.join("_out", timestamp)
os.makedirs(file_save, exist_ok=True)

async def record_loop(client, writer, file, label, duration=None):
    print(f"\nRecording {label}...\n")

    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    pd_address = ("127.0.0.1", 9002)

    start_time = time.time()

    try:
        while True:
            current_time = time.time() - start_time

            # ⬇️ ADD THIS CHECK
            if duration is not None and current_time >= duration:
                print(f"\nFinished recording {label} ({duration} seconds).\n")
                break

            raw = await client.read_gatt_char(CHARACTERISTIC_UUID)
            fmt = "<fH3f3f3ff"
            
            values = struct.unpack(fmt, raw)
            values = (current_time,) + values[1:]

            ax, ay, az = values[2], values[3], values[4]
            gx, gy, gz = values[5], values[6], values[7]
            roll, pitch, yaw = values[8], values[9], values[10]
            
            proximity = values[1]
            mic_rms = values[11]

            msg = f"{ax} {ay} {az} {gx} {gy} {gz} {roll} {pitch} {yaw} {proximity} {mic_rms}; \n"
            sock.sendto(msg.encode(), pd_address)

            print(values)

            writer.writerow(values)
            file.flush()

    except KeyboardInterrupt:
        print(f"\nStopped recording {label}.\n")

async def main():
    device = None
    
    print(f"Searching for device with service: {TARGET_SERVICE_UUID}...")
    
    while device is None:
        device = await BleakScanner.find_device_by_filter(
            lambda d, ad: TARGET_SERVICE_UUID.lower() in ad.service_uuids
        )
        
        if device is None:
            print("Device not found yet. Retrying in 2 seconds...")
            await asyncio.sleep(2)

    print(f"Found target device! Address: {device.address}")

    print("Connecting...")
    async with BleakClient(device) as client:
        if client.is_connected:
            print("Successfully connected.")

            # =========================
            # TEMPLATE RECORDING
            # =========================
            input("\nPress ENTER to record TEMPLATE gesture")

            template_file_save = f"{file_save}/template_{round(time.time())}"
            template_file = open(template_file_save, "w", newline="")
            template_writer = csv.writer(template_file)

            template_writer.writerow([
                "time",
                "proximity",
                "ax", "ay", "az",
                "gx", "gy", "gz",
                "ex", "ey", "ez",
                "mic_rms"
            ])

            await record_loop(client, template_writer, template_file, "TEMPLATE", duration=2)

            template_file.close()

            # =========================
            # DATA RECORDING
            # =========================
            input("\nPress ENTER to record DATA")

            data_file_save = f"{file_save}/data_{round(time.time())}"
            data_file = open(data_file_save, "w", newline="")
            data_writer = csv.writer(data_file)

            data_writer.writerow([
                "time",
                "proximity",
                "ax", "ay", "az",
                "gx", "gy", "gz",
                "ex", "ey", "ez",
                "mic_rms"
            ])

            await record_loop(client, data_writer, data_file, "DATA")

            data_file.close()

        else:
            print("Connection failed.")


if __name__ == "__main__":
    try:
        asyncio.run(main())

    except KeyboardInterrupt:
        print("\nProgram stopped by user.")