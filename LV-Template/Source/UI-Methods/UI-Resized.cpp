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
    
    // Pre stuff
    preGroup.setBounds(leftMargin, topMargin, width * 0.24f, height * 0.88f);
    
    // Clip stuff
    clipGroup.setBounds(preGroup.getX() + preGroup.getWidth() + leftMargin, topMargin, width * 0.48f, height * 0.88f);
    
    driveFader.setBounds(clipGroup.getX() * 1.1, clipGroup.getY() * 2, dialSize, clipGroup.getHeight() * 0.55);
    
    ceilingDial.setBounds(driveFader.getX(), driveFader.getY() + driveFader.getHeight() * spaceBetween, dialSize, dialSize);
    mixDial.setBounds(ceilingDial.getX() + ceilingDial.getWidth() * dialSpaceBetween, ceilingDial.getY(), dialSize, dialSize);
    trimDial.setBounds(mixDial.getX() + mixDial.getWidth() * dialSpaceBetween, mixDial.getY(), dialSize, dialSize);
    hpfDial.setBounds(trimDial.getX() + trimDial.getWidth() * dialSpaceBetween, trimDial.getY(), dialSize, dialSize);
    
    // Post stuff
    postGroup.setBounds(clipGroup.getX() + clipGroup.getWidth() + leftMargin, topMargin, width * 0.24f, height * 0.88f);
    
    
    
    // Save plugin size in the tree
    saveWindowSize();
}
