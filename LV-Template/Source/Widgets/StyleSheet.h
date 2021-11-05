/*
  ==============================================================================

    StyleSheet.h
    Created: 20 Jul 2021 6:38:58pm
    Author:  landon viator

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace juce
{

class LV_CustomAbleDialLAF : public LookAndFeel_V4
{
    
public:
    
    LV_CustomAbleDialLAF(bool isStereoDial)
    {
        setDialIsStereoDial(isStereoDial);
    }
    
    void drawRotarySlider (Graphics &,
                           int x, int y,
                           int width, int height,
                           float sliderPosProportional,
                           float rotaryStartAngle,
                           float rotaryEndAngle, Slider &) override;
    
    void setDialIsStereoDial(bool isStereoDial);
    
private:
    
    float stereoDialScalar = 1.0;
};

class LV_AlphaDialLAF : public juce::LookAndFeel_V4{
public:
    void drawRotarySlider(Graphics &g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, Slider &slider) override{
        
        float diameter = fmin(width, height) * .7;
        float radius = diameter * 0.5;
        float centerX = x + width * 0.5;
        float centerY = y + height * 0.5;
        float rx = centerX - radius;
        float ry = centerY - radius;
        float angle = rotaryStartAngle + (sliderPos * (rotaryEndAngle - rotaryStartAngle));
                        
        Rectangle<float> dialArea (rx, ry, diameter, diameter);
        g.setColour(slider.findColour(Slider::thumbColourId)); //center
        g.fillEllipse(dialArea);
                        
        g.setColour(Colours::black.withAlpha(0.15f)); //outline
        g.drawEllipse(rx, ry, diameter, diameter, 10.0f);
        Path dialTick;
        g.setColour(Colours::whitesmoke.darker(0.5)); //tick color
        dialTick.addRectangle(0, -radius + 6, 3.0f, radius * 0.6);
        g.fillPath(dialTick, AffineTransform::rotation(angle).translated(centerX, centerY));
    }
};

class LV_HardDialLAF : public juce::LookAndFeel_V4{
public:
    void drawRotarySlider(Graphics &g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, Slider &slider) override{
        
        float diameter = fmin(width, height) * .9;
                float radius = diameter * 0.5;
                float centerX = x + width * 0.5;
                float centerY = y + height * 0.5;
                float rx = centerX - radius;
                float ry = centerY - radius;
                float angle = rotaryStartAngle + (sliderPos * (rotaryEndAngle - rotaryStartAngle));
                
        juce::Rectangle<float> dialArea (rx, ry, diameter, diameter);
        g.setColour(slider.findColour(Slider::thumbColourId)); //center
        g.fillEllipse(dialArea);
        
        g.setColour(juce::Colours::black.brighter(0.5f).withAlpha(1.0f)); //outline
        g.drawEllipse(rx, ry, diameter, diameter, 3.0f);
        juce::Path dialTick;
        g.setColour(juce::Colours::black.brighter(1.0f).withAlpha(0.75f)); //tick color
        dialTick.addRectangle(0, -radius + 2, 3.0f, radius * 0.6);
        g.fillPath(dialTick, juce::AffineTransform::rotation(angle).translated(centerX, centerY));
    }
    
    void drawLabel (Graphics& g, Label& label) override
    {
        g.fillAll (label.findColour (Label::backgroundColourId));

        if (! label.isBeingEdited())
        {
            auto alpha = label.isEnabled() ? 1.0f : 0.5f;
            const Font font (juce::Font ("Helvetica", 12.0f, juce::Font::FontStyleFlags::plain));

            g.setColour (label.findColour (Label::textColourId).withMultipliedAlpha (alpha));
            g.setFont (font);

            auto textArea = getLabelBorderSize (label).subtractedFrom (label.getLocalBounds());

            g.drawFittedText (label.getText(), textArea, label.getJustificationType(),
                              jmax (1, (int) ((float) textArea.getHeight() / font.getHeight())),
                              label.getMinimumHorizontalScale());

            g.setColour (label.findColour (Label::outlineColourId).withMultipliedAlpha (alpha));
        }
        else if (label.isEnabled())
        {
            g.setColour (label.findColour (Label::outlineColourId));
        }

        g.drawRect (label.getLocalBounds());
    }
};


class LV_FaderLAF : public LookAndFeel_V4
{
public:
    
    void drawLinearSlider (Graphics& g, int x, int y, int width, int height,
                                           float sliderPos,
                                           float minSliderPos,
                                           float maxSliderPos,
                                                     const Slider::SliderStyle style, Slider& slider) override;
    
    void drawLabel(Graphics &g, Label &label) override;
    
};

class LV_CustomPowerToggleLAF : public LookAndFeel_V4
{
    
public:

    
    void drawToggleButton(juce::Graphics &g,
                                       juce::ToggleButton &toggleButton,
                                       bool shouldDrawButtonAsHighlighted,
                          bool shouldDrawButtonAsDown) override;
    
    
private:
    
};


}
