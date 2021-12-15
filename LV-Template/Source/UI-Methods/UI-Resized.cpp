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
    
    toggle2.setBounds(50, 50, 48, 48);
    
    demoFader.setBounds(200, 200, 300, 300);
    demoDial.setBounds(500, 200, 128, 128);
    
    // Save plugin size in the tree
    saveWindowSize();
}
