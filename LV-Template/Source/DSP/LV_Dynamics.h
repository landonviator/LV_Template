/*
  ==============================================================================

    LV_Clipper.h
    Created: 12 Jan 2022 3:55:22pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once
#ifndef LV_Dynamics_h
#define LV_Dynamics_h

#include <JuceHeader.h>

class LV_Dynamics
{
public:
    
    void prepare(juce::dsp::ProcessSpec& spec);
        
    void processBlock(juce::dsp::AudioBlock<float>& block);
        
    enum class ParameterId
    {
        kThresh,
        kRatio,
        kAttack,
        kRelease,
        kTrim,
        kBypass
    };
    
    void setParameter(ParameterId parameter, float parameterValue);
    
private:
    
    float logScale(float value, float scalar = 0.05f) const;
    
    juce::SmoothedValue<float> thresh {0.0f};
    juce::SmoothedValue<float> ratio {2.0f};
    float attack {50.0f};
    float release {500.0f};
    juce::SmoothedValue<float> trim {0.0f};
    
    float alphaAttack;
    float alphaRelease;
    
    float gainSC = 0.0;
    float gainChangeDB = 0.0;
    float gainSmoothPrev = 0.0;
    float gainSmooth;
    
    float sampleRate {44100.0f};
    float clippedSignal {0.0f};
    float blendSignal {0.0f};
    float drySignal {0.0f};
    
    bool bypassModule {false};
    
    const float piDivisor = 2.0f / juce::MathConstants<float>::pi;
};

#endif /* LV_Dynamics_h */

