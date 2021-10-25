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
    // Window
    initWindow();
    addAndMakeVisible(windowComponent);
    
    // Title border
    addAndMakeVisible(demoTitleBorder);
    
    // Fader
    demoFader.setColour(juce::Slider::thumbColourId, juce::Colours::rebeccapurple);
    demoFader.enableShadow(true);
    addAndMakeVisible(demoFader);
    
    // Dial
    demoDial.setColour(juce::Slider::thumbColourId, juce::Colours::rebeccapurple);
    demoDial.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::rebeccapurple);
    demoDial.enableShadow(true);
    addAndMakeVisible(demoDial);
    
    // Menu
    demoMenu.addItem("comp", 1);
    addAndMakeVisible(demoMenu);
    
    // Power toggle
    demoPowerToggle.setColour(juce::ToggleButton::tickColourId, juce::Colours::seagreen);
    addAndMakeVisible(demoPowerToggle);
    
    // Power button
    addAndMakeVisible(demoPushButton);
}
