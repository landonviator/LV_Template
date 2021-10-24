/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LVTemplateAudioProcessorEditor::LVTemplateAudioProcessorEditor (LVTemplateAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    initWindow();
    addAndMakeVisible(windowComponent);
    
    addAndMakeVisible(demoTitleBorder);
    
    demoFader.setColour(juce::Slider::thumbColourId, juce::Colours::rebeccapurple);
    demoFader.enableShadow(true);
    addAndMakeVisible(demoFader);
    
    demoDial.setColour(juce::Slider::thumbColourId, juce::Colours::rebeccapurple);
    demoDial.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::rebeccapurple);
    demoDial.enableShadow(true);
    addAndMakeVisible(demoDial);
    
}

LVTemplateAudioProcessorEditor::~LVTemplateAudioProcessorEditor()
{
    
}

//==============================================================================
void LVTemplateAudioProcessorEditor::paint (juce::Graphics& g)
{
}

void LVTemplateAudioProcessorEditor::resized()
{
    // Helpful vars
    auto width = getWidth();
    auto height = getHeight();
    
    // Plugin background UI
    windowComponent.setWidthAndHeight(width, height);
    windowComponent.setBounds(getLocalBounds());
    
    // Position demo fader
    demoFader.setBounds(128, 128, 128, 256);
    
    // Position demo dial
    demoDial.setBounds(demoFader.getX() + demoFader.getWidth(), demoFader.getY(), 128, 128);
    
    // Position demo border
    demoTitleBorder.setBounds(128, 100, demoFader.getWidth(), demoFader.getHeight() + 28);
    
    // Save plugin size in the tree
    saveWindowSize();
}

void LVTemplateAudioProcessorEditor::initWindow()
{
    // Grab the window instance and create a rectangle
    juce::Rectangle<int> r = juce::Desktop::getInstance().getDisplays().getPrimaryDisplay()->userArea;
    
    // Using the width is more useful than the height, because we know the height will always be < than width
    int x = r.getWidth();
    
    // Plugin window will always initialize to half the screen width by half of that for a rectangle
    auto width = x / 2.0;
    auto height = width / 2.0;
    
    //Making the window resizable by aspect ratio and setting size
    AudioProcessorEditor::setResizable(true, true);
    AudioProcessorEditor::setResizeLimits(width * 0.75, height * 0.75, width * 1.25, height * 1.25);
    AudioProcessorEditor::getConstrainer()->setFixedAspectRatio(2.0);
    
    if (audioProcessor.windowWidth != 0.0)
    {
        setSize(audioProcessor.windowWidth, audioProcessor.windowHeight);
    }
        
    else
    {
        setSize (width, height);
    }
    
    constructorFinished = true;
}

void LVTemplateAudioProcessorEditor::saveWindowSize()
{
    // Save plugin size in value tree
    audioProcessor.variableTree.setProperty("width", getWidth(), nullptr);
    audioProcessor.variableTree.setProperty("height", getHeight(), nullptr);
    
    // Don't know why I needed to do this
    if (constructorFinished)
    {
        audioProcessor.windowWidth = getWidth();
        audioProcessor.windowHeight = getHeight();
    }
}
