/*
  ==============================================================================

    LV_Toggle.h
    Created: 21 Aug 2021 2:06:36am
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "StyleSheet.h"

namespace juce
{

    class LV_PhaseToggle : public ToggleButton
    {
        
    public:
    
        LV_PhaseToggle()
        {
            setClickingTogglesState(true);
            setColour(juce::ToggleButton::tickDisabledColourId, juce::Colours::dimgrey);
            setColour(juce::ToggleButton::tickColourId, juce::Colours::springgreen);
            setLookAndFeel(&customToggle);
        }
        
        ~LV_PhaseToggle() override
        {
            setLookAndFeel(nullptr);
        }
        
        private:
        
        LV_CustomToggleLAF customToggle;
    };
}
