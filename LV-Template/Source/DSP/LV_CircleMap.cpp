/*
  ==============================================================================

    LV_LogisticMap.cpp
    Created: 4 Nov 2021 2:56:30pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "LV_CircleMap.h"

void LV_CircleMap::prepare(juce::dsp::ProcessSpec spec)
{
    sampleRate = spec.sampleRate;
}

void LV_CircleMap::processBlock(juce::dsp::AudioBlock<float> block)
{
    // Disable circuit
    if (bypassModule) return;
    
    // Process circuit
    for (int sample = 0; sample < block.getNumSamples(); ++sample)
    {
        for (int ch = 0; ch < block.getNumChannels(); ++ch)
        {
            float* data = block.getChannelPointer(ch);
            
            const auto input = data[sample];
            
            // Circle map
            currentOutput = input + (drive / twoPi) * std::sin(twoPi * input);
            
            // Compensate
            currentOutput *= std::powf(10.0, -drive * 0.15);
            
            // Blend
            currentOutput = input * (1.0 - mix) + (currentOutput * mix);
            
            // Set as output
            data[sample] = currentOutput;
        }
    }
}

void LV_CircleMap::setParameter(ParameterId parameter, float parameterValue)
{
    switch (parameter)
    {
        case LV_CircleMap::ParameterId::kDrive:
        {
            assertRange(parameterValue, 0.0f, 5.0f);
            drive = parameterValue;
            break;
        }
            
        case LV_CircleMap::ParameterId::kMix:
        {
            assertRange(parameterValue, 0.0f, 100.0f);
            mix = juce::jmap(parameterValue, 0.0f, 100.0f, 0.0f, 1.0f);
            break;
        }
            
        case LV_CircleMap::ParameterId::kBypass:
        {
            assertBool(parameterValue);
            bypassModule = parameterValue;
            break;
        }
    }
}

void LV_CircleMap::assertRange(float sourceValue, float min, float max)
{
    if (sourceValue < min || sourceValue > max) jassertfalse;
}

void LV_CircleMap::assertBool(float sourceValue)
{
    if (sourceValue != 0.0f || sourceValue != 1.0f) jassertfalse;
}
