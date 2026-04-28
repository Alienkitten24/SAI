import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from scipy.signal import find_peaks

from dtw_funcs import *

import os
from datetime import datetime

'''Utilizes functions from dtw_funcs and the CSV files saved from client file. Input data
and template files into the filename and template_filenamed'''

# LOAD DATA
filename = "Gesture Template Sets 1/data1_1776187415"
template_filename = "Gesture Template Sets 1/template1_1776187408"

# USER INPUT
plot_input = input("Show plots? [y/n]: ").lower()
plots = True if plot_input == "y" else False

save_input = input("Save plots? [y/n]: ").lower()
plot_save = True if save_input == "y" else False


# Create timestamped output folder
timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
file_save = os.path.join("DTWSearch_out", timestamp)
os.makedirs(file_save, exist_ok=True)

df = pd.read_csv(filename)
template_df = pd.read_csv(template_filename)

time = df["time"].values
template_time = template_df["time"].values

features = ["ax","ay","az","gx","gy","gz","ex","ey","ez","proximity","mic_rms"]

X = df[features].values
template_X = template_df[features].values


# NORMALIZE
X, scaler = normalize_signal(X)
template_X = scaler.transform(template_X)


# TEMPLATE PLOT
if plots:
    plt.figure()
    plt.plot(template_time, template_X[:, 8], label="yaw")
    plt.plot(template_time, template_X[:, 2], label="az")
    plt.title("Template Signal")
    plt.legend()
    plt.grid()


# DTW SEARCH
scales = np.linspace(0.1, 0.5, 5)

distances, indices, time_centers = compute_dtw_distances(
    time, X, template_X, scales, plots=plots
)


# SMOOTH + PEAK DETECTION
smoothed = smooth_data(distances, plots=plots)

peaks, _ = find_peaks(
    -smoothed,
    distance=50,
    prominence=1
)

if plots:
    plt.figure()
    plt.plot(time_centers, smoothed, label="Smoothed")
    plt.scatter(time_centers[peaks], smoothed[peaks], color="red", label="Matches")
    plt.title("Detected Peaks")
    plt.legend()
    plt.grid()

# RANGES
detected_ranges = get_detected_ranges(peaks, indices, time)

if plots:
    plt.figure()
    for i in range(X.shape[1]):
        plt.plot(time, X[:, i])
    for (start, end) in detected_ranges:
        plt.axvspan(start, end, alpha=0.2)
    plt.title("Unmerged Detection Windows")
    plt.grid()

# MERGE
merged = merge_ranges(detected_ranges, plots=plots)

print("\nDetected gesture time periods:")
for m in merged:
    print(m)

# FINAL PLOT
if plots:
    plt.figure(figsize=(12,6))
    plt.plot(time, X[:, 0], label="ax")
    plt.plot(time, X[:, 2], label="az")
    plt.plot(time, X[:, 8], label="yaw")

    for i, (start, end) in enumerate(merged):
        plt.axvspan(start, end, alpha=0.3,
                    label="Detected Gesture" if i == 0 else "")

    plt.title("Final Gesture Detection")
    plt.legend()
    plt.grid()
    plt.show()