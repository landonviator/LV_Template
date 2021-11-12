/*
  ==============================================================================

    DemoSliderBank.h
    Created: 29 Oct 2021 12:00:03am
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "UI-Components/LV_FaderComponent.h"
#include "UI-Components/LV_DialComponent.h"
#include "./Parameters/ParamDefs.h"

//==============================================================================
/*
*/
class DemoSliderBank  : public juce::Component
{
public:
    DemoSliderBank(juce::AudioProcessorValueTreeState& tree);
    ~DemoSliderBank() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void setBoundsConstraints(float boundsWidth, float boundsHeight);
    

private:
    
    /** Sliders =====================================================*/
    LV_FaderComponent slider1;
    LV_FaderComponent slider3;
    LV_DialComponent slider2;
    
    float width;
    float height;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DemoSliderBank)
};
