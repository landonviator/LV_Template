/*
  ==============================================================================

    LV_PostToneComponent.h
    Created: 14 Jan 2022 7:11:27pm
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
class LV_PostToneComponent  : public juce::Component
{
public:
    LV_PostToneComponent(juce::AudioProcessorValueTreeState& tree);
    ~LV_PostToneComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void setWidthAndHeight(float w, float h);

private:
    
    juce::LV_GroupComponent postGroup;
    
    /** Vars ==================================================================*/
    float width {0.0f};
    float height {0.0f};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LV_PostToneComponent)
};
