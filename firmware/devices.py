"""Central sensor and device initialization module."""
import machine
import time
import struct
import asyncio

""" Initialize I2C bus (once) """
i2c = machine.I2C(0, scl=machine.Pin(1), sda=machine.Pin(0))
print(i2c.scan())
time.sleep(1)


class vcnl():
    VCNL_ADDR = 0x13

    PROX_RATE_ADDR = 0x82 
    PROX_RATE = 0x07 # 250 measurements/second

    LED_CURRENT_ADDR = 0x83
    LED_CURRENT = 0x14 # 200 mA

    COMMAND_REGISTER = 0x80   
    PROX_ON_DEMAND = 0x08

    PROX_REGISTER = 0x87  

    proximity = None

    def __init__(self):
        i2c.writeto_mem(self.VCNL_ADDR, self.PROX_RATE_ADDR, bytes([self.PROX_RATE]))
        i2c.writeto_mem(self.VCNL_ADDR, self.LED_CURRENT_ADDR, bytes([self.LED_CURRENT]))

    async def read_vcnl(self):
        while True:
            # signal we want to read prox
            i2c.writeto_mem(self.VCNL_ADDR, self.COMMAND_REGISTER, bytes([self.PROX_ON_DEMAND]))

            # wait for sensor to produce value (alternatively, use prox_data_rdy register)
            time.sleep(0.01)

            # read 2 bytes -- upper bits are first so fmt big endian
            data = i2c.readfrom_mem(self.VCNL_ADDR, self.PROX_REGISTER, 2)
            self.proximity = struct.unpack('>H', data)[0]

            await asyncio.sleep(0.01)


class bno():
    BNO_ADDR = 0x28

    MODE_REGISTER = 0x3D 
    CONFIG_MODE = 0x00
    NDOF_MODE = 0x0C

    ACCEL_REGISTER = 0x08
    GYRO_REGISTER = 0x14
    EULER_REGISTER = 0x1A

    acceleration = () # meter/second^2
    gyro = () # degrees/second
    euler = () # degrees

    def __init__(self):
        i2c.writeto_mem(self.BNO_ADDR, self.MODE_REGISTER, bytes([self.CONFIG_MODE]))
        time.sleep(0.1)
        i2c.writeto_mem(self.BNO_ADDR, self.MODE_REGISTER, bytes([self.NDOF_MODE])) # NDOF = 9 degrees of freedom 'fusion'
        time.sleep(0.1)

    def read_vector(self, register, scale):
        # read 6 bytes 
        data = i2c.readfrom_mem(self.BNO_ADDR, register, 6)
        x, y, z = struct.unpack('<hhh', data)
        return (x/scale, y/scale, z/scale)

    async def read_bno(self):
        while True:
            try:
                # Values have a scale factor of x LSB (Least Significant Bit) per y
                self.acceleration = self.read_vector(self.ACCEL_REGISTER, 100.0)
                self.gyro = self.read_vector(self.GYRO_REGISTER, 16.0)
                self.euler = self.read_vector(self.EULER_REGISTER, 16.0)
            except Exception as e:
                print(e) 

            await asyncio.sleep(0.01)
            
"""" Initializing INMP microphone """
from machine import I2S, Pin
import array 

class mic():
    def __init__(self):
        self.audio = None
        self.buf = bytearray(1024)
        self.rms = 0.0

    def init_i2s(self):
        if self.audio is None:
            try:
                self.audio = I2S(
                    0,
                    sck=Pin(10),
                    ws=Pin(11),
                    sd=Pin(9),
                    mode=I2S.RX,
                    bits=32,
                    format=I2S.MONO,
                    rate=8000,
                    ibuf=1024
                )
                print("I2S initialized")
            except Exception as e:
                print("I2S INIT FAILED:", e)

    async def read_mic(self):
        self.init_i2s()

        while True:
            try:
                if self.audio is None:
                    await asyncio.sleep(0.1)
                    continue

                self.audio.readinto(self.buf)
                samples = array.array("i", self.buf)

                total = 0
                for s in samples:
                    total += s * s

                self.rms = (total / len(samples)) ** 0.5

            except Exception as e:
                print("MIC ERROR:", e)

            await asyncio.sleep(0.01) 


