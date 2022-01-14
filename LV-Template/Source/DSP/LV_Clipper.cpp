/*
  ==============================================================================

    LV_Clipper.cpp
    Created: 12 Jan 2022 3:55:22pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "LV_Clipper.h"

void LV_Clipper::prepare(juce::dsp::ProcessSpec& spec)
{
    sampleRate = spec.sampleRate;
    
    drive.reset(sampleRate, 0.02);
}

void LV_Clipper::processBlock(juce::dsp::AudioBlock<float>& block)
{
    for (auto sample {0}; sample < block.getNumSamples(); sample++)
    {
        for (auto ch {0}; ch < block.getNumChannels(); ch++)
        {
            float* data = block.getChannelPointer(ch);
            
            // Raw input
            const auto input = data[sample];
            
            switch (clipperType)
            {
                case ClipperTypeId::kSoftClipper:
                {
                    clippedSignal = returnSoftClip(input * logScale(juce::jmap(drive.getNextValue(), 0.0f, 24.0f, 0.0f, 6.0f)));
                    data[sample] = clippedSignal;
                    break;
                }
                    
                case ClipperTypeId::kHardClipper:
                {
                    clippedSignal = returnHardClip(input * logScale(drive.getNextValue()));
                    data[sample] = clippedSignal;
                    break;
                }
            }
        }
    }
}

float LV_Clipper::returnSoftClip(const float input)
{
    return constA * input + constB * std::pow(input, 3);
}

float LV_Clipper::returnHardClip(const float input)
{
    auto newInput = piDivisor * std::atan(input) * juce::Decibels::decibelsToGain(6.0);
    
    if (std::abs(newInput) > 1)
    {
        newInput *= 1 / std::abs(newInput);
    }
    
    return newInput;
}

void LV_Clipper::setClipperType(ClipperTypeId clipperType)
{
    switch (clipperType)
    {
        case LV_Clipper::ClipperTypeId::kSoftClipper:
        {
            clipperType = ClipperTypeId::kSoftClipper;
            break;
        }
            
        case LV_Clipper::ClipperTypeId::kHardClipper:
        {
            clipperType = ClipperTypeId::kHardClipper;
            break;
        }
    }
}

void LV_Clipper::setParameter(ParameterId parameter, float parameterValue)
{
    switch (parameter)
    {
        case LV_Clipper::ParameterId::kPreamp:
        {
//            preamp = parameterValue;
            break;
        }
            
        case LV_Clipper::ParameterId::kDrive:
        {
            drive.setTargetValue(parameterValue);
            break;
        }
            
        case LV_Clipper::ParameterId::kWet:
        {
            wet = juce::jmap(parameterValue, 0.0f, 100.0f, 0.0f, 1.0f);
            break;
        }
            
        case LV_Clipper::ParameterId::kTrim:
        {
            trim = parameterValue;
            break;
        }
            
        case LV_Clipper::ParameterId::kBypass:
        {
            bypassModule = parameterValue;
            break;
        }
    }
}

float LV_Clipper::logScale(float value, float scalar) const
{
    return std::pow(10.0f, value * scalar);
}
