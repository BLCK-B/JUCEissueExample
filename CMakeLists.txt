cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 20)

#set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_BUILD_TYPE "RelWithDebInfo")

project(AUDIO_PLUGIN_EXAMPLE VERSION 0.0.1)

# need to set JUCE and nuget.exe paths

add_subdirectory("C:/JUCE" JUCE)

set(NUGET_EXE "C:/.../nuget.exe")
if(MSVC)
    find_program(NUGET_EXE NAMES nuget)
    if(NOT NUGET_EXE)
        message(FATAL_ERROR "Install NUGET.EXE and run CMake again.")
    endif()
    execute_process(COMMAND ${NUGET_EXE} install "Microsoft.Web.WebView2" -OutputDirectory ${CMAKE_BINARY_DIR}/packages)
    set(WebView2_DIR ${CMAKE_BINARY_DIR}/packages/Microsoft.Web.WebView2)
    set(JUCE_WEBVIEW2_PACKAGE_LOCATION "${CMAKE_BINARY_DIR}/packages")
endif()

juce_add_plugin(AudioPluginExample
        # VERSION ...                               # Set this if the plugin version is different to the project version
        # ICON_BIG ...                              # ICON_* arguments specify a path to an image file to use as an icon for the Standalone
        # ICON_SMALL ...
        # COMPANY_NAME ...                          # Specify the name of the plugin's author
        IS_SYNTH FALSE                       # Is this a synth or an effect?
        # NEEDS_MIDI_INPUT TRUE/FALSE               # Does the plugin need midi input?
        # NEEDS_MIDI_OUTPUT TRUE/FALSE              # Does the plugin need midi output?
        # IS_MIDI_EFFECT TRUE/FALSE                 # Is this plugin a MIDI effect?
        # EDITOR_WANTS_KEYBOARD_FOCUS TRUE/FALSE    # Does the editor need keyboard focus?
        COPY_PLUGIN_AFTER_BUILD TRUE/FALSE          # Should the plugin be installed to a default location after building?
        PLUGIN_MANUFACTURER_CODE Juce               # A four-character manufacturer id with at least one upper-case character
        PLUGIN_CODE Dem0                            # A unique four-character plugin id with exactly one upper-case character
                                                    # GarageBand 10.3 requires the first letter to be upper-case, and the remaining letters to be lower-case
        FORMATS AU VST3 Standalone                  # The formats to build. Other valid formats are: AAX Unity VST AU AUv3
        PRODUCT_NAME "learningPugin"                # The name of the final executable, which can differ from the target name
        NEEDS_WEBVIEW2 TRUE
)


target_sources(AudioPluginExample
        PRIVATE
        PluginEditor.cpp
        PluginProcessor.cpp)


target_compile_definitions(AudioPluginExample
        PUBLIC
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=1  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_plugin` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_plugin` call
        JUCE_VST3_CAN_REPLACE_VST2=0
        JUCE_USE_WIN_WEBVIEW2_WITH_STATIC_LINKING=1
)

target_link_libraries(AudioPluginExample
        PRIVATE
        juce::juce_audio_utils
        juce::juce_dsp
        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)