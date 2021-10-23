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
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

LV_Window::~LV_Window()
{
}

void LV_Window::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("LV_Window", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void LV_Window::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
