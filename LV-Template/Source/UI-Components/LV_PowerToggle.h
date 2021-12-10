/*
  ==============================================================================

    LV_PowerToggle.h
    Created: 24 Oct 2021 7:39:06pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Widgets/StyleSheet.h"

//==============================================================================
/*
*/
namespace juce {
class LV_PowerToggle  : public ToggleButton
{
public:
    LV_PowerToggle();
    ~LV_PowerToggle() override;

    void paint (Graphics&) override;
    void resized() override;
    void setColour(int colourID, Colour newColour);

private:
    
    ToggleButton powerToggle;
    LV_CustomToggleLAF customPowerToggle;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LV_PowerToggle)
};
}
