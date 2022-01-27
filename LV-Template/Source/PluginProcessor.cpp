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
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), false)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), false)
                     #endif
                       ),
treeState (*this, nullptr, "PARAMETER", createParameterLayout()),
oversamplingModule(2, 3, juce::dsp::Oversampling<float>::FilterType::filterHalfBandPolyphaseIIR)
#endif
{
    scopeModule.setBufferSize(256);
    scopeModule.setSamplesPerBlock(256);
    scopeModule.setRepaintRate(32);
    
    treeState.addParameterListener (qualityID, this);
}

LVTemplateAudioProcessor::~LVTemplateAudioProcessor()
{
    treeState.removeParameterListener (qualityID, this);
}

juce::AudioProcessorValueTreeState::ParameterLayout LVTemplateAudioProcessor::createParameterLayout()
{
  std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;

  juce::StringArray qualities = {"Normal", "8X OS"};
  juce::StringArray types = {"Compressor", "Expander"};
  juce::StringArray presets = {"Streamer", "Radio", "Voice Over"};
    
  // Make sure to update the number of reservations after adding params
  auto pQuality = std::make_unique<juce::AudioParameterChoice>(qualityID, qualityName, qualities, 0);
  auto pType = std::make_unique<juce::AudioParameterChoice>("type", "Type", types, 0);
  auto pPreset = std::make_unique<juce::AudioParameterChoice>("preset", "Preset", presets, 0);
  auto pThresh = std::make_unique<juce::AudioParameterFloat>("thresh", "Thresh", -60.0, 0.0, 0.0);
  auto pRatio = std::make_unique<juce::AudioParameterFloat>("ratio", "Ratio", 2.0, 20.0, 2.0);
  auto pAttack = std::make_unique<juce::AudioParameterFloat>("attack", "Attack", 1.0, 100.0, 50.0);
  auto pRelease = std::make_unique<juce::AudioParameterFloat>("release", "Release", 1.0, 1000.0, 500.0);
    
  params.push_back(std::move(pQuality));
  params.push_back(std::move(pType));
  params.push_back(std::move(pPreset));
  params.push_back(std::move(pThresh));
  params.push_back(std::move(pRatio));
  params.push_back(std::move(pAttack));
  params.push_back(std::move(pRelease));

  return { params.begin(), params.end() };
}

void LVTemplateAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue)
{
    /** Oversampling */
    if (parameterID == qualityID)
    {
        if (newValue - 1 == 0)
        {
            oversamplingState = false;
            overSampleRate = getSampleRate();
        }
        
        else
        {
            oversamplingState = true;
            overSampleRate = getSampleRate() * oversamplingModule.getOversamplingFactor();
        }
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
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = getTotalNumOutputChannels();
    
    oversamplingState = *treeState.getRawParameterValue(qualityID) - 1;

    if (oversamplingState)
    {
        overSampleRate = spec.sampleRate * oversamplingModule.getOversamplingFactor();
    }

    else
    {
        overSampleRate = spec.sampleRate;
    }

    projectSampleRate = sampleRate;
    
    oversamplingModule.reset();
    oversamplingModule.initProcessing(samplesPerBlock);
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

    juce::dsp::AudioBlock<float> audioBlock {buffer};
    juce::dsp::AudioBlock<float> upSampledBlock;
    
    if (oversamplingState)
    {
        upSampledBlock = oversamplingModule.processSamplesUp(audioBlock);
        oversamplingModule.processSamplesDown(audioBlock);
    }

    else
    {
    }
}

//==============================================================================
bool LVTemplateAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* LVTemplateAudioProcessor::createEditor()
{
//    return new LVTemplateAudioProcessorEditor (*this);
    return new juce::GenericAudioProcessorEditor (*this);
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
        
        // Window Size
        windowWidth = variableTree.getProperty("width");
        windowHeight = variableTree.getProperty("height");
        
        oversamplingState = *treeState.getRawParameterValue(qualityID) - 1;
    }
    
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new LVTemplateAudioProcessor();
}
