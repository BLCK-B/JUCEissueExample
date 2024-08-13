#pragma once
#include "PluginProcessor.h"
//==============================================================================
class MyAudioProcessorEditor final : public juce::AudioProcessorEditor
{
public:
    explicit MyAudioProcessorEditor (MyAudioProcessor&);
    ~MyAudioProcessorEditor() override;

    //==============================================================================
    void resized() override;
private:
    using Resource = juce::WebBrowserComponent::Resource;
    static std::optional<Resource> getResource(const juce::String& url) ;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MyAudioProcessor& processorRef;

    juce::WebSliderRelay modelOrderRelay;
    juce::WebSliderParameterAttachment modelOrderSliderAttachment;

    juce::WebBrowserComponent webView;

    const juce::ParameterID modelOrder{"modelOrder", 1};


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyAudioProcessorEditor)
};
