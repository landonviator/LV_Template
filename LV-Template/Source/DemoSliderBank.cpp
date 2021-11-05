/*
  ==============================================================================

    DemoSliderBank.cpp
    Created: 29 Oct 2021 12:00:03am
    Author:  Landon Viator

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DemoSliderBank.h"
#include "PluginProcessor.h"

//==============================================================================
DemoSliderBank::DemoSliderBank(juce::AudioProcessorValueTreeState& tree) :
slider1(" dB", 0.0, 5.0, 0.1, 0.0, tree, inputID),
slider2(" dB", 0.0, 100.0, 1.0, 0.0, tree, outputID)
{
    addAndMakeVisible(slider1);
    
    addAndMakeVisible(slider2);
    slider2.setDialStyle(LV_DialComponent::DialStyle::kHardDial);
    slider2.enableShadow(true);
}

DemoSliderBank::~DemoSliderBank()
{
}

void DemoSliderBank::paint (juce::Graphics& g)
{

}

void DemoSliderBank::resized()
{
    auto leftMargin = width * 0.1;
    auto topMargin = height * 0.2;
    auto sliderHeight = height * 0.5;
    auto sliderWidth = width * 0.08;
    
    slider1.setBounds(leftMargin, topMargin, sliderWidth, sliderHeight);
        
    slider2.setBounds(slider1.getX() + slider1.getWidth(), topMargin, sliderWidth, sliderHeight);
}

void DemoSliderBank::setBoundsConstraints(float boundsWidth, float boundsHeight)
{
    width = boundsWidth;
    height = boundsHeight;
}
