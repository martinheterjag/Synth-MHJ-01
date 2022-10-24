/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

constexpr int WIDTH = 1000;
constexpr int HEIGHT = 400;

//==============================================================================
Mhj01AudioProcessorEditor::Mhj01AudioProcessorEditor (Mhj01AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (WIDTH, HEIGHT);
}

Mhj01AudioProcessorEditor::~Mhj01AudioProcessorEditor()
{
}

//==============================================================================
void Mhj01AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (40.0f);
    g.drawFittedText ("MHJ-01", getLocalBounds(), juce::Justification::centred, 1);
}

void Mhj01AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
