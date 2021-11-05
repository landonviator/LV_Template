/*
  ==============================================================================

    LV_LogisticMap.h
    Created: 4 Nov 2021 2:56:30pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once

#ifndef LV_LV_CircleMap_h
#define LV_LV_CircleMap_h

#include <JuceHeader.h>

class LV_CircleMap
{
public:
    
    void prepare(juce::dsp::ProcessSpec spec);
    
    void processBlock(juce::dsp::AudioBlock<float> block);
    
    enum class ParameterId
    {
        kDrive,
        kMix,
        kBypass
    };

    void setParameter(ParameterId parameter, float parameterValue);
    
private:
    
    void assertRange(float sourceValue, float min, float max);
    void assertBool(float sourceValue);
    
    float drive {0.0};
    float sampleRate {44100.0};
    float currentOutput;
    float mix {1.0};
    float twoPi = juce::MathConstants<float>::twoPi;
    
    bool bypassModule;
};

#endif /* LV_CircleMap_h */
