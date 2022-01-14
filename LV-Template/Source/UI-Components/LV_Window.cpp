/*
  ==============================================================================

    LV_Window.cpp
    Created: 23 Oct 2021 12:53:38am
    Author:  Landon Viator

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LV_Window.h"

//==============================================================================
LV_Window::LV_Window()
{
}

LV_Window::~LV_Window()
{
}

void LV_Window::paint (juce::Graphics& g)
{
    // Paint UI components
    paintBackground(g);
    paintLogoAndLink(g);
    paintText(g);
}

void LV_Window::resized()
{
}

void LV_Window::paintBackground(juce::Graphics &g)
{
    //Image layer from Illustrator
    //pluginBackground = juce::ImageCache::getFromMemory(BinaryData::testTexture_png, BinaryData::testTexture_pngSize);
    
    // Draw and position the image
    //g.drawImageWithin(pluginBackground, 0, 0, width, height, juce::RectanglePlacement::stretchToFit);
    g.fillAll (juce::Colour::fromFloatRGBA(0.1f, 0.12f, 0.16f, 1.0));
        
    juce::Rectangle<int> background = getBounds();
    g.setGradientFill(juce::ColourGradient::vertical(juce::Colour::fromFloatRGBA(0.18f, 0.20f, 0.24f, 1.0), height * .25, juce::Colour::fromFloatRGBA(0.12f, 0.14f, 0.18f, 1.0), height * .99));
    g.fillRect(background);
    
    // Header rectangle
    juce::Rectangle<float> header;
    header.setBounds(0, 0, width, height * 0.08f);
    g.setColour(juce::Colours::black.brighter(0.1).withAlpha(0.85f));
    g.fillRect(header);
}

void LV_Window::paintLogoAndLink(juce::Graphics &g)
{
    // Logo layer
    footerLogo = juce::ImageCache::getFromMemory(BinaryData::landon5504_png, BinaryData::landon5504_pngSize);
    
    // Draw and position the image
    g.drawImageWithin(footerLogo, width * 0.025, height * 0.01, width * 0.125, height * 0.065, juce::RectanglePlacement::centred);
    
    // Patreon link
    mWebLink.setURL(mWebUrl);
    addAndMakeVisible(mWebLink);
    mWebLink.setBounds(width * 0.38, height * 0.9, width * 0.25, height * 0.1);
    
}

void LV_Window::paintText(juce::Graphics &g)
{
    // Plugin text
//    g.setColour (juce::Colours::whitesmoke.withAlpha(0.125f));
//    g.setFont(juce::Font ("Helvetica", width * 0.02, juce::Font::FontStyleFlags::plain));
//    g.drawFittedText ("Plugin v1.0.0", width * 0.45, height * 0.02, width, height, juce::Justification::topLeft, 1);
}

void LV_Window::setWidthAndHeight(float w, float h)
{
    width = w;
    height = h;
}
