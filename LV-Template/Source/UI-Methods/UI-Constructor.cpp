/*
  ==============================================================================

    UI-Constructor.cpp
    Created: 24 Oct 2021 1:40:44am
    Author:  Landon Viator

  ==============================================================================
*/

#include "../PluginEditor.h"

void LVTemplateAudioProcessorEditor::uiConstructor()
{
    addAndMakeVisible(windowComponent);
    
    // Window
    initWindow();
    
    addAndMakeVisible(toggle2);
    toggle2.setToggleStyle(juce::LV_Toggle::ToggleStyle::kPower);
    
    addAndMakeVisible(demoFader);
    
    demoDial.setDialStyle(juce::LV_Dial::DialStyle::kHardDial);
    addAndMakeVisible(demoDial);
}
