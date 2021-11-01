/*
  ==============================================================================

    LV_DialComponent.cpp
    Created: 24 Oct 2021 12:17:36am
    Author:  Landon Viator

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LV_DialComponent.h"

//==============================================================================
LV_DialComponent::LV_DialComponent(juce::String suffix,
                                   double rangeStart,
                                   double rangeEnd,
                                   double intervalValue,
                                   double returnValue,
                                   int dialStyle,
                                   juce::AudioProcessorValueTreeState& tree,
                                   juce::String parameter)
{
    initShadows();
    initAttach(tree, parameter);
    initProps(suffix, rangeStart, rangeEnd, intervalValue, returnValue, dialStyle);

}

LV_DialComponent::~LV_DialComponent()
{
    dial.setLookAndFeel(nullptr);
}

void LV_DialComponent::paint (juce::Graphics& g)
{
}

void LV_DialComponent::resized()
{
    dial.setBounds(getLocalBounds());
}

void LV_DialComponent::initShadows()
{
    shadowProperties.radius = 24;
    shadowProperties.offset = juce::Point<int> (-1, 4);
    shadowProperties.colour = juce::Colours::black.withAlpha(0.5f);
    dialShadow.setShadowProperties (shadowProperties);
}

void LV_DialComponent::setDialStyle(int dialStyle)
{
    jassert(dialStyle < 4 && dialStyle > 0);
    
    switch (dialStyle)
    {
        case 1:
            dial.setLookAndFeel(&hardDial);
            break;
            
        case 2:
            dial.setLookAndFeel(&alphaDial);
            break;
            
        case 3:
            dial.setLookAndFeel(&ableDial);
            break;
    }
}

void LV_DialComponent::initProps(juce::String suffix, double rangeStart, double rangeEnd, double intervalValue, double returnValue, int dialStyle)
{
    dial.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    dial.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 96, 32);
    dial.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, findColour(Slider::ColourIds::thumbColourId));
    dial.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colour::fromRGB(35, 35, 35));
    dial.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::black.withAlpha(0.0f));
    dial.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::whitesmoke.withAlpha(0.25f));
    dial.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colour::fromFloatRGBA(0.392f, 0.584f, 0.929f, 1.0f).darker(1.0));
    dial.setRange(rangeStart, rangeEnd, intervalValue);
    dial.setDoubleClickReturnValue(true, returnValue);
    dial.setTextValueSuffix(suffix);
    setDialStyle(dialStyle);
    dial.setComponentEffect(&dialShadow);
    addAndMakeVisible(dial);
}

void LV_DialComponent::initAttach(juce::AudioProcessorValueTreeState& tree, juce::String parameter)
{
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    dialAttach = std::make_unique<SliderAttachment>(tree, parameter, dial);
}
