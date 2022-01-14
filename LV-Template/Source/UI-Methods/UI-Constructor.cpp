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
    
    initOversamplingMenu();
    
    // Pre stuff
    addAndMakeVisible(preGroup);
    preGroup.setText("Pre Tone");
    
    // Clip stuff
    
    // Drive
    addAndMakeVisible(driveFader);
    driveFader.onValueChange = [this]()
    {
        audioProcessor.drive = driveFader.getValue();
    };
    
    addAndMakeVisible(driveFaderLabel);
    driveFaderLabel.attachToComponent(&driveFader, false);
    driveFaderLabel.setText("Drive", juce::dontSendNotification);
    
    addAndMakeVisible(clipGroup);
    clipGroup.setText("Clipper");
    
    // Ceiling Dial
    addAndMakeVisible(ceilingDial);
    addAndMakeVisible(ceilingDialLabel);
    ceilingDialLabel.attachToComponent(&ceilingDial, false);
    ceilingDialLabel.setText("Ceiling", juce::dontSendNotification);
    
    // Mix Dial
    addAndMakeVisible(mixDial);
    addAndMakeVisible(mixDialLabel);
    mixDialLabel.attachToComponent(&mixDial, false);
    mixDialLabel.setText("Mix", juce::dontSendNotification);
    
    // Trim Dial
    addAndMakeVisible(trimDial);
    addAndMakeVisible(trimDialLabel);
    trimDialLabel.attachToComponent(&trimDial, false);
    trimDialLabel.setText("Trim", juce::dontSendNotification);
    
    // High Pass Filter Dial
    addAndMakeVisible(hpfDial);
    addAndMakeVisible(hpfDialLabel);
    hpfDialLabel.attachToComponent(&hpfDial, false);
    hpfDialLabel.setText("HPF", juce::dontSendNotification);
    
    // Post stuff
    addAndMakeVisible(postGroup);
    postGroup.setText("Post Tone");
    
}
