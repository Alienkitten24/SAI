import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# SETTINGS
FILE_PATH = "Test3_Johan/sensor_data_1775148037_Test3_distortion"

# LOAD DATA
df = pd.read_csv(FILE_PATH)
time = df["time"]

# PREPROCESS MIC → dB
mic_rms = df["mic_rms"].values
mic_rms = np.maximum(mic_rms, 1e-12)  # avoid log(0)
mic_db = 20 * np.log10(mic_rms)

# Optional normalization (nice plotting)
mic_db = mic_db - np.max(mic_db)

roll = df['ex'].values
pitch = df['ey'].values
yaw = df['ez'].values

def minmax(x):
    return (x - np.min(x)) / (np.max(x) - np.min(x) + 1e-12)

roll = minmax(roll)
pitch = minmax(pitch)
yaw= minmax(yaw)

# CREATE SUBPLOTS
fig, axs = plt.subplots(3, 1, figsize=(10, 8), sharex=True)

axs[0].plot(time,roll, label="roll")
axs[0].plot(time,pitch, label="pitch")
axs[0].plot(time, yaw, label="yaw")
axs[0].set_title("Normalized Euler Angles (degrees)")
axs[0].set_ylabel("Normalized")
axs[0].legend()
axs[0].grid()

axs[1].plot(time, mic_db, label="mic (dB)")
axs[1].set_title("Microphone Level (dB)")
axs[1].set_ylabel("dB")
axs[1].legend()
axs[1].grid()

axs[2].plot(time, df["proximity"], label="proximity")
axs[2].set_title("Proximity")
axs[2].set_ylabel("Value")
axs[2].set_xlabel("Time")
axs[2].legend()
axs[2].grid()

# FINAL TOUCHES
plt.tight_layout()
# title = input("title:")
# plt.savefig(f"appendixPlots/{title}.png")
plt.show()