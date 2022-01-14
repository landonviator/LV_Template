/*
  ==============================================================================

    OversamplingMenu.cpp
    Created: 11 Jan 2022 5:41:21pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "../PluginEditor.h"

void LVTemplateAudioProcessorEditor::initOversamplingMenu()
{
    using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;
    oversamplingMenuAttach = std::make_unique<ComboBoxAttachment>(audioProcessor.treeState, qualityID, oversamplingMenu);
    oversamplingMenu.setTextWhenNothingSelected("Quality");
    oversamplingMenu.addItem("Normal Quality", 1);
    oversamplingMenu.addItem("High Quality", 2);
    addAndMakeVisible(oversamplingMenu);
}
