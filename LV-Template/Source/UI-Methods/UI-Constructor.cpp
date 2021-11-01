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
    addAndMakeVisible(sliders);
    
    // Window
    initWindow();
    
}
