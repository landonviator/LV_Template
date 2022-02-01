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
//    attack.reset(spec.sampleRate, 0.02);
//    release.reset(spec.sampleRate, 0.02);
    trim.reset(spec.sampleRate, 0.02);
    
    sampleRate = spec.sampleRate;
    
//    alphaAttack.reset(spec.sampleRate, 0.02);
//    alphaRelease.reset(spec.sampleRate, 0.02);
//    alphaAttack.setTargetValue(std::exp(-std::log(9.0) / (sampleRate * attack.getNextValue())));
//    alphaRelease.setTargetValue(std::exp(-std::log(9.0) / (sampleRate * release.getNextValue())));
}

void LV_Dynamics::processBlock(juce::dsp::AudioBlock<float> &block)
{
    
    for (int sample = 0; sample < block.getNumSamples(); ++sample)
    {
        for (int ch = 0; ch < block.getNumChannels(); ++ch)
        {
            float* data = block.getChannelPointer(ch);
            
            auto x_unipolar = std::abs(data[sample]);
            auto x_decibels = 20.0 * std::log10(x_unipolar);
            
            if (x_decibels < -96.0)
            {
                x_decibels = -96.0;
            }
            
            if (x_decibels > thresh.getNextValue())
            {
                gainSC = thresh.getNextValue() + (x_decibels - thresh.getNextValue()) / ratio.getNextValue();
            }
            
            else
            {
                gainSC = x_decibels;
            }
            
            gainChangeDB = gainSC - x_decibels;
            
            //smooth gain over time
            if (gainChangeDB < gainSmoothPrev)
            {
                gainSmooth = ((1.0 - alphaAttack) * gainChangeDB) + (alphaAttack * gainSmoothPrev);
            }
            
            else
            {
                gainSmooth = ((1.0 - alphaRelease) * gainChangeDB) + (alphaRelease * gainSmoothPrev);
            }
            
            gainSmoothPrev = gainSmooth;
            
            // Final Output
            data[sample] = data[sample] * std::pow(10.0, gainSmooth * 0.05) * std::pow(10.0, trim.getNextValue() * 0.05);
            
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
            attack = parameterValue;
            alphaAttack = std::exp(-std::log(9.0) / (sampleRate * attack));
            break;
        }
            
        case LV_Dynamics::ParameterId::kRelease:
        {
            release = parameterValue;
            alphaRelease = std::exp(-std::log(9.0) / (sampleRate * release));
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
