/*
  ==============================================================================

    UI-Resized.cpp
    Created: 24 Oct 2021 1:41:10am
    Author:  Landon Viator

  ==============================================================================
*/

#include "../PluginEditor.h"

void LVTemplateAudioProcessorEditor::uiResized(float width, float height)
{
    // Plugin background UI
    windowComponent.setWidthAndHeight(width, height);
    windowComponent.setBounds(getLocalBounds());
    
    sliders.setBoundsConstraints(width, height);
    sliders.setBounds(getLocalBounds());
    
    // Save plugin size in the tree
    saveWindowSize();
}
