#include "PluginEditor.h"

#include <juce_audio_processors/juce_audio_processors.h>
#include <optional>
#include "PluginProcessor.h"
#include "juce_core/juce_core.h"
#include "juce_graphics/juce_graphics.h"
#include "juce_gui_extra/juce_gui_extra.h"

//==============================================================================
MyAudioProcessorEditor::MyAudioProcessorEditor(MyAudioProcessor &p)
        : AudioProcessorEditor(&p), processorRef(p),
          modelOrderRelay{
                  webView, "modelOrder"
          },
          modelOrderSliderAttachment{
                  *processorRef.treeState.getParameter("modelOrder"), modelOrderRelay, nullptr
          },
          webView{juce::WebBrowserComponent::Options{}
                          .withBackend(juce::WebBrowserComponent::Options::Backend::webview2)
                          .withWinWebView2Options(juce::WebBrowserComponent::Options::WinWebView2{}
                                                          .withBackgroundColour(juce::Colours::white)
                                                          .withUserDataFolder(juce::File::getSpecialLocation(juce::File::SpecialLocationType::tempDirectory)))
                          .withNativeIntegrationEnabled()
                          .withResourceProvider([](const auto &url) { return getResource(url); })
                          .withOptionsFrom(modelOrderRelay)
          } {
    juce::ignoreUnused(processorRef);

    addAndMakeVisible(webView);

    webView.goToURL("https://juce.com/");

    setResizable(true, true);
    setSize(500, 500);
}

MyAudioProcessorEditor::~MyAudioProcessorEditor() { }

//==============================================================================

auto MyAudioProcessorEditor::getResource(const juce::String& url) -> std::optional<Resource> {
    return std::nullopt;
}

void MyAudioProcessorEditor::resized() {
    webView.setBounds(getLocalBounds());
}
