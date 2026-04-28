import time
import asyncio
from devices import vcnl, bno, mic
import struct
# Bluetooth libs:
import bluetooth
import aioble


""" Main Data Structure """
class SensorData:
    def __init__(self):
        self.proximity = None
        self.accel = [None, None, None]
        self.gyro = [None, None, None]
        self.euler = [None, None, None]
        self.mic_rms = None

data = SensorData()
start_time = time.time()

# Create sensor instances
vcnl_sensor = vcnl()
bno_sensor = bno()
mic_sensor = mic()

""" Worker loops to populate data points """
async def vcnl_loop():
    while True:
        data.proximity = vcnl_sensor.proximity
        await asyncio.sleep(0.01)

async def bno_loop():
    while True:
        data.accel = bno_sensor.acceleration
        data.gyro = bno_sensor.gyro 
        data.euler = bno_sensor.euler

        await asyncio.sleep(0.01)

async def mic_loop():
    while True:
        data.mic_rms = mic_sensor.rms
        
        await asyncio.sleep(0.01)


""" Byte Encoding for ble transmission """
def encode_sensors():
    # byte format -- little endian 
    # time,  prox,   accel xyz, gyro xyz, euler xyz, mic_rms
    # float, uint16, 3 floats,  3 floats, 3 floats,  float   
    fmt = "<fH3f3f3ff"
    
    # Handle None values with defaults
    current_time = time.time() - start_time
    proximity = data.proximity if data.proximity is not None else 0
    accel = data.accel if all(x is not None for x in data.accel) else [0.0, 0.0, 0.0]
    gyro = data.gyro if all(x is not None for x in data.gyro) else [0.0, 0.0, 0.0]
    euler = data.euler if all(x is not None for x in data.euler) else [0.0, 0.0, 0.0]
    mic_rms = data.mic_rms if data.mic_rms is not None else 0.0
    
    byte_data = struct.pack(
        fmt,
        current_time,
        proximity,
        *accel,
        *gyro,
        *euler,
        mic_rms,
    )

    print(byte_data.hex())
    print(f'{proximity}, {accel}, {gyro}, {euler}, {mic_rms}') 

    return byte_data 

""" Create BLE service """
SERVICE_UUID = bluetooth.UUID('12341000-1234-1234-1234-123456789abc')
READ_UUID = bluetooth.UUID('12345678-1234-1234-1234-123456789ab1')
NOTIFY_UUID = bluetooth.UUID('12345678-1234-1234-1234-123456789ab2')
ADV_INTERVAL_US = 250_000 # How frequently to send advertising beacons

service = aioble.Service(SERVICE_UUID)
# sensor_read  -- read characteristic
sensor_read = aioble.Characteristic(service, READ_UUID, read=True)
aioble.register_services(service)

async def peripheral_task():
    while True:
        async with await aioble.advertise(
            ADV_INTERVAL_US,
            name='Audimo', 
            services=[SERVICE_UUID],
        ) as connection:
            # Start sensor data collection only after connection established
            t1 = asyncio.create_task(vcnl_sensor.read_vcnl())
            t2 = asyncio.create_task(bno_sensor.read_bno())
            t3 = asyncio.create_task(vcnl_loop())
            t4 = asyncio.create_task(bno_loop())
            t5 = asyncio.create_task(mic_sensor.read_mic())
            t6 = asyncio.create_task(mic_loop())
            
            # Continuously update the characteristic while connected
            try:
                while True:
                    sensor_read.write(encode_sensors())
                    await asyncio.sleep(0.05)  # Update every 50ms
            except:
                pass
            finally:
                # Cancel sensor tasks when connection is lost
                t1.cancel()
                t2.cancel()
                t3.cancel()
                t4.cancel()
                t5.cancel()
                t6.cancel()
            
            await connection.disconnected(timeout_ms=None)

""" Start BLE server and data collection """
async def start_server():
    # Only run the advertising/connection task
    await peripheral_task()

