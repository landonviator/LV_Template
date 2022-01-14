/*
  ==============================================================================

    LV_Clipper.h
    Created: 12 Jan 2022 3:55:22pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once
#ifndef LV_Clipper_h
#define LV_Clipper_h

#include <JuceHeader.h>

class LV_Clipper
{
public:
    
void prepare(juce::dsp::ProcessSpec& spec);
    
    
void processBlock(juce::dsp::AudioBlock<float>& block);
    
    float returnSoftClip(const float input);
    
    float returnHardClip(const float input);
    
    enum class ParameterId
    {
        kPreamp,
        kDrive,
        kWet,
        kTrim,
        kBypass
    };
    
    enum class ClipperTypeId
    {
      kSoftClipper,
        kHardClipper
    };

    void setParameter(ParameterId parameter, float parameterValue);
    
    void setClipperType(ClipperTypeId clipperType);
    
private:
    
    float logScale(float value, float scalar = 0.05f) const;
    
    juce::SmoothedValue<float> drive;
    
    float wet {0.0f};
    float trim {0.0f};
    float sampleRate {44100.0f};
    float clippedSignal {0.0f};
    float ceiling {0.0f};
    
    float constA {1.5};
    float constB {-0.5};
    
    bool bypassModule {false};
    
    const float piDivisor = 2.0f / juce::MathConstants<float>::pi;
    
    ClipperTypeId clipperType = ClipperTypeId::kSoftClipper;
};

#endif /* LV_Clipper_h */
