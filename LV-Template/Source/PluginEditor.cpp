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
    uiConstructor();
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
    
    uiResized(width, height);
}
