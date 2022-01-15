/*
  ==============================================================================

    LV_PostToneComponent.cpp
    Created: 14 Jan 2022 7:11:27pm
    Author:  Landon Viator

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LV_PostToneComponent.h"

//==============================================================================
LV_PostToneComponent::LV_PostToneComponent(juce::AudioProcessorValueTreeState& tree)
{
    // Post stuff
    addAndMakeVisible(postGroup);
    postGroup.setText("Post Tone");
}

LV_PostToneComponent::~LV_PostToneComponent()
{
}

void LV_PostToneComponent::paint (juce::Graphics& g)
{
    
}

void LV_PostToneComponent::resized()
{
    auto leftMargin = getWidth() * 0.05;
    auto topMargin = getWidth() * 0.1;
    auto dialSize = width * 0.1;
    auto spaceBetween = 1.15;
    auto dialSpaceBetween = 1.1;
    
    // Pre stuff
    postGroup.setBounds(0, 0, getWidth(), getHeight());

}

void LV_PostToneComponent::setWidthAndHeight(float w, float h)
{
    width = w;
    height = h;
}
