/*
  ==============================================================================

    LV_SplitDistortion.h
    Created: 7 Nov 2021 3:30:43pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once
#ifndef LV_SplitDistortion_h
#define LV_SplitDistortion_h

#include <JuceHeader.h>
#include "LV_SVFilter.h"

class LV_SplitDistortion
{
public:
    
    void prepare(juce::dsp::ProcessSpec spec);
    
    void processBlock(juce::dsp::AudioBlock<float>& block);
    
    enum class ParameterId
    {
        kDrive,
        kWet,
        kTrim,
        kCutoff,
        kBypass
    };

    void setParameter(ParameterId parameter, float parameterValue);
    
private:
    
    void assertRange(float sourceValue, float min, float max);
    void assertBool(float sourceValue);
    float logScale(float value, float scalar = 0.05f);
    
    float drive {0.0};
    float sampleRate {44100.0};
    float wet {1.0};
    float currentOutput;
    float filteredOutput;
    float trim {0.0f};
    float cutoff {2500.0};
    
    bool bypassModule;
    
    LV_SVFilter topBandFilter;
    void prepareTopBandFilter(juce::dsp::ProcessSpec spec);
    
};

#endif /* LV_SplitDistortion_h */
