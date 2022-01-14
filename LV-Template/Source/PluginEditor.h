/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI-Components/LV_Window.h"
#include "Widgets/WidgetIncludes.h"

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
    
    /** UI Methods ================================================================*/
    void uiConstructor();
    void uiPaint(juce::Graphics& g);
    void uiResized(float width, float height);
    
    /** Window ====================================================================*/
    LV_Window windowComponent;
    
    void initWindow();
    void saveWindowSize();
    bool constructorFinished {false};
    
    juce::LV_Toggle toggle2 {};
    
    juce::LV_Fader driveFader;
    juce::LV_Label driveFaderLabel;
    
    juce::LV_Dial ceilingDial;
    juce::LV_Dial mixDial;
    juce::LV_Dial trimDial;
    juce::LV_Dial hpfDial;
    
    juce::LV_Label ceilingDialLabel;
    juce::LV_Label mixDialLabel;
    juce::LV_Label trimDialLabel;
    juce::LV_Label hpfDialLabel;
    
    juce::LV_GroupComponent preGroup;
    juce::LV_GroupComponent clipGroup;
    juce::LV_GroupComponent postGroup;
    
    juce::LV_Menu oversamplingMenu;
    void initOversamplingMenu();
    
    using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;
    std::unique_ptr<ComboBoxAttachment> oversamplingMenuAttach;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LVTemplateAudioProcessorEditor)
};
