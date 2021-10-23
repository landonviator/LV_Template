/*
  ==============================================================================

    LV_FaderComponent.cpp
    Created: 23 Oct 2021 2:38:27am
    Author:  Landon Viator

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LV_FaderComponent.h"

//==============================================================================
LV_FaderComponent::LV_FaderComponent(juce::String suffix, double rangeStart, double rangeEnd, double intervalValue, double returnValue)
{
    init_shadows();
    slider.setRange(rangeStart, rangeEnd, intervalValue);
    slider.setDoubleClickReturnValue(true, returnValue);
    slider.setTextValueSuffix(suffix);
    slider.setLookAndFeel(&customFader);
    slider.setComponentEffect(&sliderShadow);
    addAndMakeVisible(slider);
}

LV_FaderComponent::~LV_FaderComponent()
{
    slider.setLookAndFeel(nullptr);
}

void LV_FaderComponent::paint (juce::Graphics& g)
{

}

void LV_FaderComponent::resized()
{
    slider.setBounds(getLocalBounds());
}

void LV_FaderComponent::setColour(int colourID, juce::Colour newColour)
{
    slider.setColour(colourID, newColour);
}

void LV_FaderComponent::init_shadows()
{
    sliderShadowProperties.radius = 8;
    sliderShadowProperties.offset = juce::Point<int> (0, 0);
    sliderShadowProperties.colour = juce::Colours::black.withAlpha(1.0f);
    sliderShadow.setShadowProperties (sliderShadowProperties);
}
