/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI-Components/LV_Window.h"
#include "UI-Components/LV_FaderComponent.h"
#include "UI-Components/LV_DialComponent.h"
#include "UI-Components/LV_GroupComponent.h"
#include "UI-Components/LV_LabelComponent.h"
#include "UI-Components/LV_MenuComponent.h"

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
    void uiPaint();
    void uiResized(float width, float height);
    
    /** Window ====================================================================*/
    LV_Window windowComponent;
    
    void initWindow();
    void saveWindowSize();
    bool constructorFinished {false};
    
    /** Fader =====================================================================*/
    LV_FaderComponent demoFader {" dB", -24.0, 24.0, 0.25, 0.0};
    
    /** Dial ======================================================================*/
    LV_DialComponent demoDial {" dB", -24.0, 24.0, 0.25, 0.0, 1};
    
    /** Title Border ==============================================================*/
    LV_GroupComponent demoTitleBorder {"Demo Title"};
    
    /** Label =====================================================================*/
    LV_LabelComponent demoLabel {"Input", demoDial};
    
    /** Menu ======================================================================*/
    LV_MenuComponent demoMenu {"Default Item"};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LVTemplateAudioProcessorEditor)
};
