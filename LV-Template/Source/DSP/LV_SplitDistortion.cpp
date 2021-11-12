/*
  ==============================================================================

    LV_SplitDistortion.cpp
    Created: 7 Nov 2021 3:30:43pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "LV_SplitDistortion.h"

void LV_SplitDistortion::prepare(juce::dsp::ProcessSpec spec)
{
    sampleRate = spec.sampleRate;
    
    prepareTopBandFilter(spec);
}

void LV_SplitDistortion::processBlock(juce::dsp::AudioBlock<float>& block)
{
    // Disable circuit
    if (bypassModule) return;
    
    // Process circuit
    for (auto sample {0}; sample < block.getNumSamples(); sample++)
    {
        
        for (auto ch {0}; ch < block.getNumChannels(); ch++)
        {
            float* data = block.getChannelPointer(ch);
            
            const auto input = data[sample];
            
            currentOutput = input * juce::Decibels::decibelsToGain(18.0f);
            
            filteredOutput = topBandFilter.processSample(currentOutput, ch);
            
            auto softClip = std::atanf(filteredOutput * logScale(drive));
            
            currentOutput = softClip * juce::Decibels::decibelsToGain(-18.0f) * logScale(drive, 0.0025f);
            
            currentOutput *= 0.25f * wet;
            
            data[sample] = (currentOutput + input) * logScale(trim);
        }
    }
}

void LV_SplitDistortion::setParameter(ParameterId parameter, float parameterValue)
{
    switch (parameter)
    {
        case LV_SplitDistortion::ParameterId::kDrive:
        {
            assertRange(parameterValue, 0.0f, 12.0f);
            drive = parameterValue * 4.0f;
            break;
        }
            
        case LV_SplitDistortion::ParameterId::kWet:
        {
            assertRange(parameterValue, 0.0f, 100.0f);
            wet = juce::jmap(parameterValue, 0.0f, 100.0f, 0.0f, 1.0f);
            break;
        }
            
        case LV_SplitDistortion::ParameterId::kTrim:
        {
            assertRange(parameterValue, -96.0, 24.0f);
            trim = parameterValue;
            break;
        }
            
        case LV_SplitDistortion::ParameterId::kCutoff:
        {
            assertRange(parameterValue, 20.0f, 20000.0f);
            cutoff = parameterValue - 1.0;
            topBandFilter.setParameter(LV_SVFilter::ParameterId::kCutoff, cutoff);
            break;
        }
            
        case LV_SplitDistortion::ParameterId::kBypass:
        {
            assertBool(parameterValue);
            bypassModule = parameterValue;
            break;
        }
    }
}

void LV_SplitDistortion::assertRange(float sourceValue, float min, float max)
{
    if (sourceValue < min || sourceValue > max) jassertfalse;
}

void LV_SplitDistortion::assertBool(float sourceValue)
{
    // If you hit this assert, you didn't
    // pass a bool to this parameter call!
    if (sourceValue != 0.0f || sourceValue != 1.0f) jassertfalse;
}

float LV_SplitDistortion::logScale(float value, float scalar)
{
    return std::powf(10.0f, value * scalar);
}

void LV_SplitDistortion::prepareTopBandFilter(juce::dsp::ProcessSpec spec)
{
    topBandFilter.prepare(spec);
    topBandFilter.setParameter(LV_SVFilter::ParameterId::kType, LV_SVFilter::FilterType::kHighPass);
    topBandFilter.setParameter(LV_SVFilter::ParameterId::kCutoff, cutoff);
}
