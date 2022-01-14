/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LVTemplateAudioProcessorEditor::LVTemplateAudioProcessorEditor (LVTemplateAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
driveFader (" dB", 0.0, 24.0, 0.01, 0.0),
ceilingDial (" dB", -60.0, 0.0, 0.1, 0.0),
mixDial (" dB", 0.0, 100.0, 1.0, 100.0),
trimDial (" dB", -96.0, 24.0, 0.1, 0.0),
hpfDial (" dB", 20.0, 250.0, 1.0, 20.0)
{
    uiConstructor();
}

LVTemplateAudioProcessorEditor::~LVTemplateAudioProcessorEditor()
{
    
}

//==============================================================================
void LVTemplateAudioProcessorEditor::paint (juce::Graphics& g)
{
    uiPaint(g);
    
}

void LVTemplateAudioProcessorEditor::resized()
{
    // Helpful vars
    auto width = getWidth();
    auto height = getHeight();
    
    uiResized(width, height);
}
