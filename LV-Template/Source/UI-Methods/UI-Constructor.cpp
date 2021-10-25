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
    initWindow();
    addAndMakeVisible(windowComponent);
    
    addAndMakeVisible(demoTitleBorder);
    
    demoFader.setColour(juce::Slider::thumbColourId, juce::Colours::rebeccapurple);
    demoFader.enableShadow(true);
    addAndMakeVisible(demoFader);
    
    demoDial.setColour(juce::Slider::thumbColourId, juce::Colours::rebeccapurple);
    demoDial.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::rebeccapurple);
    demoDial.enableShadow(true);
    addAndMakeVisible(demoDial);
    
    demoMenu.addItem("comp", 1);
    addAndMakeVisible(demoMenu);
    
    addAndMakeVisible(demoPowerToggle);
    demoPowerToggle.setColour(juce::ToggleButton::tickColourId, juce::Colours::blue);
}
