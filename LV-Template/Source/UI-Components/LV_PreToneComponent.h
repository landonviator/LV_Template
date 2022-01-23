/*
  ==============================================================================

    LV_PreToneComponent.h
    Created: 14 Jan 2022 7:01:32pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Widgets/WidgetIncludes.h"
#include "../Parameters/ParamDefs.h"

//==============================================================================
/*
*/
class LV_PreToneComponent  : public juce::Component
{
public:
    LV_PreToneComponent(juce::AudioProcessorValueTreeState& tree);
    ~LV_PreToneComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void setWidthAndHeight(float w, float h);

private:
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    
    juce::LV_Toggle moduleBypass;
    juce::LV_GroupComponent preGroup;
    
    juce::LV_Dial freqDial {" dB", 250.0, 2500.0, 1.0, 1000.0};
    juce::LV_Dial gainDial {" dB", -12.0, 12.0, 0.1, 0.0};
    juce::LV_Dial qDial {" dB", 0.01, 0.99, 0.1, 0.3};
    
    juce::LV_Label freqDialLabel;
    juce::LV_Label gainDialLabel;
    juce::LV_Label qDialLabel;
    
    /** Vars ==================================================================*/
    float width {0.0f};
    float height {0.0f};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LV_PreToneComponent)
};
