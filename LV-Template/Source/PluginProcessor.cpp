/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LVTemplateAudioProcessor::LVTemplateAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
treeState (*this, nullptr, "PARAMETER", createParameterLayout())
#endif
{
    treeState.addParameterListener (inputID, this);
    treeState.addParameterListener (outputID, this);
}

LVTemplateAudioProcessor::~LVTemplateAudioProcessor()
{
    treeState.removeParameterListener (inputID, this);
    treeState.removeParameterListener (outputID, this);
}

juce::AudioProcessorValueTreeState::ParameterLayout LVTemplateAudioProcessor::createParameterLayout()
{
  std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;

  // Make sure to update the number of reservations after adding params
  params.reserve(2);

  auto pInput = std::make_unique<juce::AudioParameterFloat>(inputID, inputName, -24.0, 24.0, 0.0);
  auto pOutput = std::make_unique<juce::AudioParameterFloat>(outputID, outputName, -24.0, 24.0, 0.0);
  
  params.push_back(std::move(pInput));
  params.push_back(std::move(pOutput));

  return { params.begin(), params.end() };
}

void LVTemplateAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue)
{
    if (parameterID == inputID)
    {
        DBG("Input: " << newValue);
    }
    
    else
    {
        DBG("Output: " << newValue);
    }
}

//==============================================================================
const juce::String LVTemplateAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool LVTemplateAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool LVTemplateAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool LVTemplateAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double LVTemplateAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int LVTemplateAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int LVTemplateAudioProcessor::getCurrentProgram()
{
    return 0;
}

void LVTemplateAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String LVTemplateAudioProcessor::getProgramName (int index)
{
    return {};
}

void LVTemplateAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void LVTemplateAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
}

void LVTemplateAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool LVTemplateAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void LVTemplateAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
    }
}

//==============================================================================
bool LVTemplateAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* LVTemplateAudioProcessor::createEditor()
{
    return new LVTemplateAudioProcessorEditor (*this);
}

//==============================================================================
void LVTemplateAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // Save params
    treeState.state.appendChild(variableTree, nullptr);
    juce::MemoryOutputStream stream(destData, false);
    treeState.state.writeToStream (stream);
}

void LVTemplateAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // Recall params
    auto tree = juce::ValueTree::readFromData (data, size_t(sizeInBytes));
    variableTree = tree.getChildWithName("Variables");
    
    if (tree.isValid())
    {
        treeState.state = tree;
    }
    
    windowWidth = variableTree.getProperty("width");
    windowHeight = variableTree.getProperty("height");
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new LVTemplateAudioProcessor();
}
