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
slider1(" dB", 0.0, 12.0, 0.1, 0.0, tree, inputID),
slider3(" Hz", 20.0, 20000.0, 1.0, 1000.0, tree, drive2ID),
slider2(" dB", 0.0, 100.0, 1.0, 0.0, tree, outputID)
{
    //addAndMakeVisible(slider1);
    
    //addAndMakeVisible(slider3);
    slider3.setRange(20.0, 20000.0, 1.0);
    slider3.setSkewFactorFromMidPoint(1000.0);
    
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
    auto topMargin = height * 0.05;
    auto sliderHeight = height * 0.5;
    auto sliderWidth = width * 0.08;
    auto dialSize = width * 0.13;
    
    slider1.setBounds(leftMargin, topMargin, sliderWidth, sliderHeight);
    slider3.setBounds(slider1.getX() + slider1.getWidth(), topMargin, sliderWidth, sliderHeight);
    slider2.setBounds(slider3.getX() + slider3.getWidth(), topMargin, dialSize, dialSize);
}

void DemoSliderBank::setBoundsConstraints(float boundsWidth, float boundsHeight)
{
    width = boundsWidth;
    height = boundsHeight;
}
