import numpy as np
from dtw import dtw
from sklearn.preprocessing import StandardScaler
import matplotlib.pyplot as plt
from scipy.signal import savgol_filter

# NORMALIZATION
def normalize_signal(X):
    scaler = StandardScaler()
    return scaler.fit_transform(X), scaler

# TEMPLATE EXTRACTION
def extract_template(time, X, start_time, end_time):
    mask = (time >= start_time) & (time <= end_time)
    return X[mask]

# DTW DISTANCE SEARCH
def compute_dtw_distances(time, X, template, scales, step_fraction=8, plots=False):
    window_size = len(template)
    step_size = int(window_size / step_fraction)

    distances = []
    indices = []
    time_centers = []

    template_norm = (template - np.mean(template)) / (np.std(template) + 1e-6)

    for i in range(0, len(X) - window_size, step_size):
        for s in scales:
            w_size = int(window_size * s)
            if i + w_size >= len(X):
                continue

            window = X[i:i + w_size]
            window_norm = (window - np.mean(window)) / (np.std(window) + 1e-6)

            dist = dtw(template_norm, window_norm).distance / (
                len(template_norm) + len(window_norm)
            )

            distances.append(float(dist))
            indices.append((i, w_size))
            time_centers.append(time[i + w_size // 2])

    distances = np.array(distances)
    time_centers = np.array(time_centers)

    if plots:
        plt.figure()
        plt.plot(time_centers, distances)
        plt.title("DTW Distance Over Time")
        plt.xlabel("Time")
        plt.ylabel("Distance")
        plt.grid()

    return distances, indices, time_centers

# SMOOTH DATA
'''Window length and polyorder need tuning/optimization based on each trial'''

def smooth_data(distances, plots=False):
    window_length = 13
    polyorder = 3
    smooth_distances = savgol_filter(distances, window_length, polyorder)

    if plots:
        plt.figure()
        plt.plot(distances, label="Raw")
        plt.plot(smooth_distances, label="Smoothed", linewidth=2)
        plt.title("Smoothed DTW Distance")
        plt.legend()
        plt.grid()

    return smooth_distances

# DETECTED TIME RANGES
def get_detected_ranges(matches, indices, time):
    detected_ranges = []
    for m in matches:
        start_i, w_size = indices[m]
        end_i = start_i + w_size
        detected_ranges.append((float(time[start_i]), float(time[end_i])))
    return detected_ranges

# MERGE OVERLAPPING WINDOWS
def merge_ranges(detected_ranges, merge_gap=0.3, plots=False):
    merged = []

    for start, end in sorted(detected_ranges):
        if not merged:
            merged.append([start, end])
        else:
            prev = merged[-1]
            if start <= prev[1] + merge_gap:
                prev[1] = max(prev[1], end)
            else:
                merged.append([start, end])

    if plots:
        print("Merged ranges:", merged)

    return merged