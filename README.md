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
2. [SimpleBLE](https://github.com/simpleble/simpleble): Used for bluetooth communication


## Building 

### Requirements

* **C++ Standard:** 20
* **CMake Version:** 3.15 or higher

### Building Example

Note: make sure to set your JUCE path in CMakeLists.txt

Example building on Windows 11:

```bash
cmake -B Builds
cmake --build Builds --config Release
```

This will build the standalone executable to ".\Builds\Audimo_artefacts\Release\Standalone\Audimo.exe" and the vst3 file to ".\Builds\Audimo_artefacts\Release\VST3\Audimo.vst3\Contents\x86_64-win\Audimo.vst3"

## Credits

Jennifer Tsai: Chief Hardware Engineer

Felix Iov: Chief Software Engineer

Dr. Ben Whiting & Dr. Ran Yang: Advisorary Roles