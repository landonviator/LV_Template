/*
  ==============================================================================

    LV_ClipperComponent.cpp
    Created: 14 Jan 2022 5:33:49pm
    Author:  Landon Viator

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LV_ClipperComponent.h"

//==============================================================================
LV_ClipperComponent::LV_ClipperComponent(juce::AudioProcessorValueTreeState& tree)
{
    // Drive
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    addAndMakeVisible(moduleBypass);
    moduleBypass.setToggleStyle(juce::LV_Toggle::ToggleStyle::kPower);
    
    driveFaderAttach = std::make_unique<SliderAttachment>(tree, driveID, driveFader);
    addAndMakeVisible(driveFader);
    
    addAndMakeVisible(driveFaderLabel);
    driveFaderLabel.attachToComponent(&driveFader, false);
    driveFaderLabel.setText("Drive", juce::dontSendNotification);
    
    addAndMakeVisible(clipGroup);
    clipGroup.setText("Clipper");
    
    // Ceiling Dial
    addAndMakeVisible(ceilingDial);
    addAndMakeVisible(ceilingDialLabel);
    ceilingDialLabel.attachToComponent(&ceilingDial, false);
    ceilingDialLabel.setText("Ceiling", juce::dontSendNotification);
    
    // Mix Dial
    addAndMakeVisible(mixDial);
    addAndMakeVisible(mixDialLabel);
    mixDialLabel.attachToComponent(&mixDial, false);
    mixDialLabel.setText("Mix", juce::dontSendNotification);
    
    // Trim Dial
    addAndMakeVisible(trimDial);
    addAndMakeVisible(trimDialLabel);
    trimDialLabel.attachToComponent(&trimDial, false);
    trimDialLabel.setText("Trim", juce::dontSendNotification);
    
    // High Pass Filter Dial
    addAndMakeVisible(hpfDial);
    addAndMakeVisible(hpfDialLabel);
    hpfDialLabel.attachToComponent(&hpfDial, false);
    hpfDialLabel.setText("HPF", juce::dontSendNotification);
}

LV_ClipperComponent::~LV_ClipperComponent()
{
}

void LV_ClipperComponent::paint (juce::Graphics& g)
{
}

void LV_ClipperComponent::resized()
{
    auto leftMargin = getWidth() * 0.05;
    auto topMargin = getWidth() * 0.1;
    auto dialSize = width * 0.1;
    auto spaceBetween = 1.15;
    auto dialSpaceBetween = 1.1;
    
    // Clip stuff
    clipGroup.setBounds(0, 0, getWidth(), getHeight());
    moduleBypass.setBounds(clipGroup.getX() + leftMargin / 3, clipGroup.getY() + topMargin / 3, 48, 48);
    driveFader.setBounds(clipGroup.getX() + leftMargin, clipGroup.getY() + topMargin * 2.0, dialSize, clipGroup.getHeight() * 0.45);
    ceilingDial.setBounds(driveFader.getX(), driveFader.getY() + driveFader.getHeight() * spaceBetween, dialSize, dialSize);
    mixDial.setBounds(ceilingDial.getX() + ceilingDial.getWidth() * dialSpaceBetween, ceilingDial.getY(), dialSize, dialSize);
    trimDial.setBounds(mixDial.getX() + mixDial.getWidth() * dialSpaceBetween, mixDial.getY(), dialSize, dialSize);
    hpfDial.setBounds(trimDial.getX() + trimDial.getWidth() * dialSpaceBetween, trimDial.getY(), dialSize, dialSize);
}

void LV_ClipperComponent::setWidthAndHeight(float w, float h)
{
    width = w;
    height = h;
}
