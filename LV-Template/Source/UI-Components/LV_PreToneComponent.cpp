/*
  ==============================================================================

    LV_PreToneComponent.cpp
    Created: 14 Jan 2022 7:01:32pm
    Author:  Landon Viator

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LV_PreToneComponent.h"

//==============================================================================
LV_PreToneComponent::LV_PreToneComponent(juce::AudioProcessorValueTreeState& tree)
{
    // Pre stuff
    addAndMakeVisible(preGroup);
    preGroup.setText("Pre Tone");
}

LV_PreToneComponent::~LV_PreToneComponent()
{
}

void LV_PreToneComponent::paint (juce::Graphics& g)
{
}

void LV_PreToneComponent::resized()
{
    auto leftMargin = getWidth() * 0.05;
    auto topMargin = getWidth() * 0.1;
    auto dialSize = width * 0.1;
    auto spaceBetween = 1.15;
    auto dialSpaceBetween = 1.1;
    
    // Pre stuff
    preGroup.setBounds(0, 0, getWidth(), getHeight());

}

void LV_PreToneComponent::setWidthAndHeight(float w, float h)
{
    width = w;
    height = h;
}
