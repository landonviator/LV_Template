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
    auto leftMargin = height * 0.02;
    auto topMargin = height * 0.1;
    auto dialSize = width * 0.1;
    auto spaceBetween = 1.15;
    auto dialSpaceBetween = 1.1;
    
    // Plugin background UI
    windowComponent.setWidthAndHeight(width, height);
    windowComponent.setBounds(getLocalBounds());
    
    headerComponent.setWidthAndHeight(width, height);
    headerComponent.setBounds(0, 0, width, height * 0.08f);
    
    // Save plugin size in the tree
    saveWindowSize();
}
