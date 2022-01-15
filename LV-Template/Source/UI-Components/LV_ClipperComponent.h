/*
  ==============================================================================

    LV_ClipperComponent.h
    Created: 14 Jan 2022 5:33:49pm
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
class LV_ClipperComponent  : public juce::Component
{
public:
    LV_ClipperComponent(juce::AudioProcessorValueTreeState& tree);
    ~LV_ClipperComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void setWidthAndHeight(float w, float h);

private:
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    juce::LV_Fader driveFader {" dB", 0.0, 24.0, 0.01, 0.0};
    juce::LV_Label driveFaderLabel;
    std::unique_ptr<SliderAttachment> driveFaderAttach;
    
    juce::LV_Dial ceilingDial {" dB", -60.0, 0.0, 0.1, 0.0};
    juce::LV_Dial mixDial {" dB", 0.0, 100.0, 1.0, 100.0};
    juce::LV_Dial trimDial {" dB", -96.0, 24.0, 0.1, 0.0};
    juce::LV_Dial hpfDial {" dB", 20.0, 250.0, 1.0, 20.0};
    
    juce::LV_Label ceilingDialLabel;
    juce::LV_Label mixDialLabel;
    juce::LV_Label trimDialLabel;
    juce::LV_Label hpfDialLabel;
    
    juce::LV_GroupComponent clipGroup;
    
    /** Vars ==================================================================*/
    float width {0.0f};
    float height {0.0f};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LV_ClipperComponent)
};
