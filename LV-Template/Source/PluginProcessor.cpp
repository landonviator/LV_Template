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
    
    treeState.addParameterListener (inputID, this);
    treeState.addParameterListener (driveID, this);
    treeState.addParameterListener (outputID, this);
    treeState.addParameterListener (qualityID, this);
    treeState.addParameterListener (clipTypeID, this);
    treeState.addParameterListener (clipColorID, this);
    treeState.addParameterListener (ceilingID, this);
    treeState.addParameterListener (trimID, this);
    treeState.addParameterListener (mixID, this);
    treeState.addParameterListener (clipperPowerID, this);
    treeState.addParameterListener (preFreqID, this);
    treeState.addParameterListener (preGainID, this);
    treeState.addParameterListener (preQID, this);
    treeState.addParameterListener (prePowerID, this);
    treeState.addParameterListener (postFreqID, this);
    treeState.addParameterListener (postGainID, this);
    treeState.addParameterListener (postQID, this);
    treeState.addParameterListener (postPowerID, this);
}

LVTemplateAudioProcessor::~LVTemplateAudioProcessor()
{
    treeState.removeParameterListener (inputID, this);
    treeState.removeParameterListener (driveID, this);
    treeState.removeParameterListener (outputID, this);
    treeState.removeParameterListener (qualityID, this);
    treeState.removeParameterListener (clipTypeID, this);
    treeState.removeParameterListener (clipColorID, this);
    treeState.removeParameterListener (ceilingID, this);
    treeState.removeParameterListener (trimID, this);
    treeState.removeParameterListener (mixID, this);
    treeState.removeParameterListener (clipperPowerID, this);
    treeState.removeParameterListener (preFreqID, this);
    treeState.removeParameterListener (preGainID, this);
    treeState.removeParameterListener (preQID, this);
    treeState.removeParameterListener (prePowerID, this);
    treeState.removeParameterListener (postFreqID, this);
    treeState.removeParameterListener (postGainID, this);
    treeState.removeParameterListener (postQID, this);
    treeState.removeParameterListener (postPowerID, this);
}

juce::AudioProcessorValueTreeState::ParameterLayout LVTemplateAudioProcessor::createParameterLayout()
{
  std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;

  // Make sure to update the number of reservations after adding params
  params.reserve(19);

  auto pInput = std::make_unique<juce::AudioParameterFloat>(inputID, inputName, 0.0, 12.0, 0.0);
  auto pDrive = std::make_unique<juce::AudioParameterFloat>(driveID, driveName, 0.0, 24.0, 0.0);
  auto pOutput = std::make_unique<juce::AudioParameterFloat>(outputID, outputName, 0.0, 100.0, 100.0);
  auto pQuality = std::make_unique<juce::AudioParameterInt>(qualityID, qualityName, 1, 2, 1);
  auto pClipType = std::make_unique<juce::AudioParameterInt>(clipTypeID, clipTypeName, 1, 3, 1);
  auto pClipColor = std::make_unique<juce::AudioParameterInt>(clipColorID, clipColorName, 1, 3, 3);
  auto pCeiling = std::make_unique<juce::AudioParameterFloat>(ceilingID, ceilingName, -60.0, 0.0, 0.0);
  auto pTrim = std::make_unique<juce::AudioParameterFloat>(trimID, trimName, -96.0, 24.0, 0.0);
  auto pMix = std::make_unique<juce::AudioParameterFloat>(mixID, mixName, 0.0, 100.0, 100.0);
  auto pClipperPower = std::make_unique<juce::AudioParameterBool> (clipperPowerID, clipperPowerName, false);
  auto pPreFreq = std::make_unique<juce::AudioParameterInt>(preFreqID, preFreqName, 250.0, 2500.0, 1000.0);
  auto pPreGain = std::make_unique<juce::AudioParameterFloat>(preGainID, preGainName, -12.0, 12.0, 0.0);
  auto pPreQ = std::make_unique<juce::AudioParameterInt>(preQID, preQName, 0.0, 100.0, 50.0);
  auto pPrePower = std::make_unique<juce::AudioParameterBool> (prePowerID, prePowerName, false);
  auto pPostFreq = std::make_unique<juce::AudioParameterInt>(postFreqID, postFreqName, 250.0, 2500.0, 1000.0);
  auto pPostGain = std::make_unique<juce::AudioParameterFloat>(postGainID, postGainName, -12.0, 12.0, 0.0);
  auto pPostQ = std::make_unique<juce::AudioParameterInt>(postQID, postQName, 0.0, 100.0, 50.0);
  auto pPostPower = std::make_unique<juce::AudioParameterBool> (postPowerID, postPowerName, false);
    
  params.push_back(std::move(pInput));
  params.push_back(std::move(pDrive));
  params.push_back(std::move(pOutput));
  params.push_back(std::move(pQuality));
  params.push_back(std::move(pClipType));
  params.push_back(std::move(pClipColor));
  params.push_back(std::move(pCeiling));
  params.push_back(std::move(pTrim));
  params.push_back(std::move(pMix));
  params.push_back(std::move(pClipperPower));
  params.push_back(std::move(pPreFreq));
  params.push_back(std::move(pPreGain));
  params.push_back(std::move(pPreQ));
  params.push_back(std::move(pPrePower));
  params.push_back(std::move(pPostFreq));
  params.push_back(std::move(pPostGain));
  params.push_back(std::move(pPostQ));
  params.push_back(std::move(pPostPower));

  return { params.begin(), params.end() };
}

void LVTemplateAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue)
{
    /** Clipper */
    if (parameterID == driveID)
    {
        clipperModule.setParameter(LV_Clipper::ParameterId::kDrive, newValue);
    }
    
    if (parameterID == ceilingID)
    {
        clipperModule.setParameter(LV_Clipper::ParameterId::kCeiling, newValue);
    }
    
    if (parameterID == trimID)
    {
        clipperModule.setParameter(LV_Clipper::ParameterId::kTrim, newValue);
    }
    
    if (parameterID == mixID)
    {
        clipperModule.setParameter(LV_Clipper::ParameterId::kMix, newValue);
    }
    
    if (parameterID == clipperPowerID)
    {
        clipperModule.setParameter(LV_Clipper::ParameterId::kBypass, newValue);
    }
    
    if (parameterID == clipTypeID)
    {
        clipTypeChoice = newValue;
        
        switch (static_cast<int>(clipTypeChoice))
        {
            case 1: clipperModule.setClipperType(LV_Clipper::ClipperTypeId::kHardClipper); break;
            case 2: clipperModule.setClipperType(LV_Clipper::ClipperTypeId::kSoftClipper); break;
            case 3: clipperModule.setClipperType(LV_Clipper::ClipperTypeId::kAnalogClipper); break;
        }
    }
    
    /** Pre */
    if (parameterID == preFreqID)
    {
        preToneModule.setParameter(LV_SVFilter::ParameterId::kCutoff, newValue);
    }
    
    if (parameterID == preGainID)
    {
        preToneModule.setParameter(LV_SVFilter::ParameterId::kGain, newValue);
    }
    
    if (parameterID == preQID)
    {
        auto newQ = juce::jmap(newValue, 0.0f, 100.0f, 0.01f, 0.95f);
        preToneModule.setParameter(LV_SVFilter::ParameterId::kQ, newQ);
    }
    
    if (parameterID == prePowerID)
    {
        preToneModule.setParameter(LV_SVFilter::ParameterId::kBypass, newValue);
    }
    
    /** Post */
    if (parameterID == postFreqID)
    {
        postToneModule.setParameter(LV_SVFilter::ParameterId::kCutoff, newValue);
    }
    
    if (parameterID == postGainID)
    {
        postToneModule.setParameter(LV_SVFilter::ParameterId::kGain, newValue);
    }
    
    if (parameterID == postQID)
    {
        auto newQ = juce::jmap(newValue, 0.0f, 100.0f, 0.01f, 0.95f);
        postToneModule.setParameter(LV_SVFilter::ParameterId::kQ, newQ);
    }
    
    if (parameterID == postPowerID)
    {
        postToneModule.setParameter(LV_SVFilter::ParameterId::kBypass, newValue);
    }
    
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
    
//    oversamplingState = *treeState.getRawParameterValue(qualityID) - 1;
//
//    if (oversamplingState)
//    {
//        overSampleRate = spec.sampleRate * oversamplingModule.getOversamplingFactor();
//    }
//
//    else
//    {
//        overSampleRate = spec.sampleRate;
//    }
//
//    projectSampleRate = sampleRate;
    
//    oversamplingModule.reset();
//    oversamplingModule.initProcessing(samplesPerBlock);
    
    preToneModule.prepare(spec);
    initPreTone();
    
    clipperModule.prepare(spec);
    initClipper();
    
    postToneModule.prepare(spec);
    initPostTone();
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
    
    preToneModule.processBlock(audioBlock);
    clipperModule.processBlock(audioBlock);
    postToneModule.processBlock(audioBlock);
    scopeModule.pushBuffer(buffer);
    
//    if (oversamplingState)
//    {
//        upSampledBlock = oversamplingModule.processSamplesUp(audioBlock);
//
//        for (int sample = 0; sample < upSampledBlock.getNumSamples(); ++sample)
//        {
//            for (int ch = 0; ch < upSampledBlock.getNumChannels(); ++ch)
//            {
//                float* data = upSampledBlock.getChannelPointer(ch);
//                midToneFilter.setParameter(LV_SVFilter::ParameterId::kSampleRate, overSampleRate);
//                data[sample] = midToneFilter.processSample(data[sample], ch);
//            }
//        }
//
//        oversamplingModule.processSamplesDown(audioBlock);
//    }
//
//    else
//    {
//        for (int sample = 0; sample < audioBlock.getNumSamples(); ++sample)
//        {
//            for (int ch = 0; ch < audioBlock.getNumChannels(); ++ch)
//            {
//                float* data = audioBlock.getChannelPointer(ch);
//                midToneFilter.setParameter(LV_SVFilter::ParameterId::kSampleRate, overSampleRate);
//                data[sample] = midToneFilter.processSample(data[sample], ch);
//            }
//        }
//    }
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
        
        // Window Size
        windowWidth = variableTree.getProperty("width");
        windowHeight = variableTree.getProperty("height");
        
        // Pre Tone
        initPreTone();
        
        // Clipper
        initClipper();
        
        // Post Tone
        initPostTone();
    }
    
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new LVTemplateAudioProcessor();
}
