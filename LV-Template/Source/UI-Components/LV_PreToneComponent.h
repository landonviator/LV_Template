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
    
    juce::LV_GroupComponent preGroup;
    
    /** Vars ==================================================================*/
    float width {0.0f};
    float height {0.0f};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LV_PreToneComponent)
};
