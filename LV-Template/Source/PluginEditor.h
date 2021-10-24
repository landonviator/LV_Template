/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/LV_Window.h"
#include "UI/LV_FaderComponent.h"
#include "UI/LV_DialComponent.h"

//==============================================================================
/**
*/
class LVTemplateAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    LVTemplateAudioProcessorEditor (LVTemplateAudioProcessor&);
    ~LVTemplateAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    LVTemplateAudioProcessor& audioProcessor;
    
    /** Window ====================================================================*/
    LV_Window windowComponent;
    void initWindow();
    void saveWindowSize();
    bool constructorFinished {false};
    
    /** Fader =====================================================================*/
    LV_FaderComponent demoFader {" dB", -24.0, 24.0, 0.25, 0.0};
    
    /** Dial =====================================================================*/
    LV_DialComponent demoDial {" dB", -24.0, 24.0, 0.25, 0.0, 1};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LVTemplateAudioProcessorEditor)
};
