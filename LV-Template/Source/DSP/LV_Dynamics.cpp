/*
  ==============================================================================

    LV_Dynamics.cpp
    Created: 26 Jan 2022 6:34:20pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "LV_Dynamics.h"

void LV_Dynamics::prepare(juce::dsp::ProcessSpec &spec)
{
    thresh.reset(spec.sampleRate, 0.02);
    ratio.reset(spec.sampleRate, 0.02);
    attack.reset(spec.sampleRate, 0.02);
    release.reset(spec.sampleRate, 0.02);
    trim.reset(spec.sampleRate, 0.02);
}

void LV_Dynamics::processBlock(juce::dsp::AudioBlock<float> &block)
{
    for (int sample = 0; sample < block.getNumSamples(); ++sample)
    {
        for (int ch = 0; ch < block.getNumChannels(); ++ch)
        {
            float* data = block.getChannelPointer(ch);
        }
    }
}

void LV_Dynamics::setParameter(ParameterId parameter, float parameterValue)
{
    switch (parameter)
    {
        case LV_Dynamics::ParameterId::kThresh:
        {
            thresh.setTargetValue(parameterValue);
            break;
        }
            
        case LV_Dynamics::ParameterId::kRatio:
        {
            ratio.setTargetValue(parameterValue);
            break;
        }
            
        case LV_Dynamics::ParameterId::kAttack:
        {
            attack.setTargetValue(parameterValue);
            break;
        }
            
        case LV_Dynamics::ParameterId::kRelease:
        {
            release.setTargetValue(parameterValue);
            break;
        }
            
        case LV_Dynamics::ParameterId::kTrim:
        {
            trim.setTargetValue(parameterValue);
            break;
        }
            
        case LV_Dynamics::ParameterId::kBypass:
        {
            bypassModule = parameterValue;
            break;
        }
    }
}
