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
    
    oversamplingMenu.setBounds(500, 6, width * 0.16, width * 0.04);
    
    // Pre Tone
    preToneComponent.setWidthAndHeight(width, height);
    preToneComponent.setBounds(leftMargin, topMargin, width * 0.24f, height * 0.88f);
    
    // Clip stuff
    clipperComponent.setWidthAndHeight(width, height);
    clipperComponent.setBounds(preToneComponent.getX() + preToneComponent.getWidth() + leftMargin, topMargin, width * 0.48f, height * 0.88f);
    
    // Post stuff
//    postGroup.setBounds(clipGroup.getX() + clipGroup.getWidth() + leftMargin, topMargin, width * 0.24f, height * 0.88f);
    
    
    
    // Save plugin size in the tree
    saveWindowSize();
}
