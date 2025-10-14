cmake_minimum_required(VERSION 3.15)
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
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
    Source/PluginEditor.cpp
    Source/PluginEditor.h)

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
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)
