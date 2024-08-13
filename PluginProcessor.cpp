#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MyAudioProcessor::MyAudioProcessor() :
    AudioProcessor (BusesProperties()
        .withInput("Input",  juce::AudioChannelSet::stereo(), true)
        .withInput("Sidechain",  juce::AudioChannelSet::stereo(), true)
        .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
    ),
    treeState{*this, nullptr, "PARAMETERS", createParameterLayout()},
    modelOrder{treeState.getRawParameterValue("modelOrder")}
{ }

MyAudioProcessor::~MyAudioProcessor() { }

juce::AudioProcessorValueTreeState::ParameterLayout MyAudioProcessor::createParameterLayout() {
    using namespace juce;
    AudioProcessorValueTreeState::ParameterLayout layout;

    layout.add(std::make_unique<AudioParameterFloat>("modelOrder", "modelOrder",
           NormalisableRange<float>(0.f, 50.f, 1.f, 1.f), 50.f));

    return layout;
}

//==============================================================================
const juce::String MyAudioProcessor::getName() const {
    return JucePlugin_Name;
}

bool MyAudioProcessor::acceptsMidi() const {
    return false;
}

bool MyAudioProcessor::producesMidi() const {
    return false;
}

bool MyAudioProcessor::isMidiEffect() const {
    return false;
}

double MyAudioProcessor::getTailLengthSeconds() const {
    return 0.0;
}

int MyAudioProcessor::getNumPrograms() {
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs, so this should be at least 1, even if you're not really implementing programs.
}

int MyAudioProcessor::getCurrentProgram() {
    return 0;
}

void MyAudioProcessor::setCurrentProgram (int index) {
    juce::ignoreUnused (index);
}

const juce::String MyAudioProcessor::getProgramName (int index) {
    juce::ignoreUnused (index);
    return {};
}

void MyAudioProcessor::changeProgramName (int index, const juce::String& newName) {
    juce::ignoreUnused (index, newName);
}

void MyAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock) {
}

void MyAudioProcessor::releaseResources() {
}

bool MyAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const {
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;

    return true;
}

void MyAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) {
    juce::ignoreUnused(midiMessages);

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());
}

//==============================================================================
bool MyAudioProcessor::hasEditor() const {
    return true; // false if you choose to not supply an editor
}

juce::AudioProcessorEditor* MyAudioProcessor::createEditor() {
    return new MyAudioProcessorEditor (*this);
}

//==============================================================================
// storing parameters in memory block
// destination data from DAW
void MyAudioProcessor::getStateInformation (juce::MemoryBlock& destData) {
    juce::ignoreUnused (destData);
    juce::MemoryOutputStream stream(destData, false);
}
//when plugin is opened - restore saved parameters
void MyAudioProcessor::setStateInformation (const void* data, int sizeInBytes) {
    juce::ignoreUnused (data, sizeInBytes);
    juce::ValueTree tree = juce::ValueTree::readFromData(data, size_t(sizeInBytes));
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
    return new MyAudioProcessor();
}
