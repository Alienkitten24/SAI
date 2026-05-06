# Audimo

The Audimo is a compact, wireless system for real-time sound augmentation of acoustic instruments using gesture-based sensor interaction.  

## Key Features

* Custom hardware build with Raspberry Pi Pico W and custom PCB
* Equipped with a 9 axis motion sensor, proximity sensor, and microphone
* Bluetooth Low Energy (BLE) transmission of sensor data 
* Custom software plugin with multiple effects and controller types
* Easily modulate effect parameters based on sensor values 

## Dependencies 

This project manages its main dependencies via CMake. Ensure these are correctly installed:

1. [JUCE](https://github.com/juce-framework/JUCE): Used for the plugin framework

Download and install JUCE [here](https://juce.com/download), or build with CMake by following the instructions on the JUCE repo. Note: make sure to set your JUCE path in CMakeLists.txt.

2. [SimpleBLE](https://github.com/simpleble/simpleble): Used for bluetooth communication

Clone the SimpleBLE. Install using CMake. 

```bash
cmake -S [path-to-simpleble] -B [path-to-build]
cmake --build [path-to-build]
cmake --install [path-to-build]
```


## Building 

### Requirements

* **C++ Standard:** 20
* **CMake Version:** 3.15 or higher

### Building Example

To build the plugin:

```bash
cmake -S [path-to-audimo] -B [path-to-build]
cmake --build [path-to-build] --config Release
```

Example building on Windows 11:

```bash
cmake -B Builds -G "Visual Studio 18"
cmake --build Builds --config Release
```

-S can be omitted if building from the source directory. -G is included to specify which generator to use. This will build the standalone executable to ".\Builds\Audimo_artefacts\Release\Standalone\Audimo.exe" and the vst3 file to ".\Builds\Audimo_artefacts\Release\VST3\Audimo.vst3\Contents\x86_64-win\Audimo.vst3"

## Firmware

The Audimo device (Raspberry Pi Pico W) uses [MicroPython](https://micropython.org) for its code. 

To flash MicroPython onto the device, hold the BOOTSEL button while the Pi is connected to a computer via USB. The Pi should appear as a drive. Copy the [UF2 Bootloader](https://micropython.org/download/RPI_PICO_W/) files and the Audimo Python files onto the Pi. 

## Credits

Jennifer Tsai: Chief Hardware Engineer

Felix Iov: Chief Software Engineer

Dr. Ben Whiting & Dr. Ran Yang: Advisorary Roles