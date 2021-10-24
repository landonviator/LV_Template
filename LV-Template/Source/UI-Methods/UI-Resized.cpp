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
    
    // Position demo fader
    demoFader.setBounds(128, 128, 128, 256);
    
    // Position demo dial
    demoDial.setBounds(demoFader.getX() + demoFader.getWidth(), demoFader.getY(), 128, 128);
    
    // Position demo border
    demoTitleBorder.setBounds(128, 100, demoFader.getWidth(), demoFader.getHeight() + 28);
    
    // Position demo menu
    demoMenu.setBounds(demoDial.getX() + demoDial.getWidth(), demoDial.getY(), demoDial.getWidth(), demoMenu.getWidth() / 2.5);
    
    // Save plugin size in the tree
    saveWindowSize();
}
