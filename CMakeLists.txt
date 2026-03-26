cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(test VERSION 0.0.1)


set(JUCE_PATH "C:/JUCE")  # your JUCE path
add_subdirectory(${JUCE_PATH} JUCE)

juce_add_plugin(test
    COMPANY_NAME "MyCompany"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    COPY_PLUGIN_AFTER_BUILD FALSE # set true to write to commonfiles/vst3
    PLUGIN_MANUFACTURER_CODE Juce
    PLUGIN_CODE MyPl
    FORMATS VST3 Standalone
    PRODUCT_NAME "test")

juce_generate_juce_header(test)

target_sources(test PRIVATE
    # --- BASE ---------------------------------------
    Source/PluginProcessor.h
    Source/PluginProcessor.cpp
    Source/PluginEditor.h
    Source/PluginEditor.cpp
    
    # --- MODEL --------------------------------------
    Source/Model/SensorData.h
    Source/Model/EffectsTreeState.h
    Source/Model/EffectsTreeState.cpp
    Source/Model/GainParams.h
    Source/Model/DistortionParams.h
    Source/Model/DelayParams.h
    Source/Model/FilterParams.h
    
    # --- DSP ----------------------------------------
    Source/Dsp/GainDsp.h
    Source/Dsp/GainDsp.cpp
    Source/Dsp/DistortionDsp.h
    Source/Dsp/DistortionDsp.cpp
    Source/Dsp/DelayDsp.h
    Source/Dsp/DelayDsp.cpp
    Source/Dsp/FilterDsp.h
    Source/Dsp/FilterDsp.cpp

    # --- COMMUNICATION ------------------------------
    Source/Communication/BLEClient.h
    Source/Communication/BLEClient.cpp
    Source/Communication/OSCBridge.h
    Source/Communication/OSCBridge.cpp
    Source/Communication/BLEOSCReceiver.h
    Source/Communication/BLEOSCReceiver.cpp
    Source/Communication/BLEManager.h
    Source/Communication/BLEManager.cpp

    # --- VIEWS --------------------------------------
    Source/Views/EffectsView.h
    Source/Views/EffectsView.cpp
    Source/Views/MatrixView.h
    Source/Views/MatrixView.cpp
    Source/Views/AdvancedView.h
    Source/Views/AdvancedView.cpp
    
    # --- COMPONENTS ---------------------------------
    # --- EFFECTS ---
    Source/Components/Effects/EffectComponent.h
    Source/Components/Effects/EffectComponent.cpp
    Source/Components/Effects/GainComponent.h
    Source/Components/Effects/GainComponent.cpp
    Source/Components/Effects/DistortionComponent.h
    Source/Components/Effects/DistortionComponent.cpp
    Source/Components/Effects/DelayComponent.h
    Source/Components/Effects/DelayComponent.cpp
    Source/Components/Effects/FilterComponent.h
    Source/Components/Effects/FilterComponent.cpp

    # --- CORE --- 
    Source/Components/Core/TitleBarComponent.h
    Source/Components/Core/TitleBarComponent.cpp
    Source/Components/Core/KnobComponent.h
    Source/Components/Core/KnobComponent.cpp
    Source/Components/Core/ComboBoxComponent.h
    Source/Components/Core/ComboBoxComponent.cpp
    
    # --- NAVIGATION ---
    Source/Components/Navigation/NavBar.h
    Source/Components/Navigation/NavBar.cpp

    # --- DIALOG ---
    Source/Components/Dialog/BLESettingsComponent.h
    Source/Components/Dialog/BLESettingsComponent.cpp
)

# Ensure VST2 is OFF
target_compile_definitions(test 
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0)

target_link_libraries(test
    PRIVATE
        juce::juce_audio_utils
        juce::juce_audio_devices
        juce::juce_osc
        juce::juce_dsp
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)
        

find_package(simpleble REQUIRED CONFIG)
target_link_libraries(test PRIVATE simpleble::simpleble)
