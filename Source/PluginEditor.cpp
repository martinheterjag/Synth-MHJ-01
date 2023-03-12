/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginEditor.h"
#include "PluginProcessor.h"
#include "gui/ModWheelComponent.h"
#include "gui/OscComponent.h"

constexpr int WIDTH = 1000;
constexpr int HEIGHT = 495;

//==============================================================================
Mhj01AudioProcessorEditor::Mhj01AudioProcessorEditor (Mhj01AudioProcessor& p)
    : AudioProcessorEditor (&p),
      audioProcessor (p),
      osc1_ ("Osc 1", p.apvts, ParamIdPrefix::OSC_1),
      osc2_ ("Osc 2", p.apvts, ParamIdPrefix::OSC_2),
      noise_ ("Noise", p.apvts),
      filter_ ("Filter", p.apvts),
      env1_ ("Env 1", p.apvts, ParamIdPrefix::ENV_1),
      env2_ ("Env 2", p.apvts, ParamIdPrefix::ENV_2),
      lfo1_ ("LFO 1", p.apvts, ParamIdPrefix::LFO_1),
      lfo2_ ("LFO 2", p.apvts, ParamIdPrefix::LFO_2),
      seq_ ("Sequencer", p.apvts),
      volume_knob_ ("Volume", SliderComponent::Style::KNOB),
      modwheel_controls_ (p.apvts),
      aftertouch_controls_ (p.apvts)
{
    addAndMakeVisible (osc1_);
    addAndMakeVisible (osc2_);
    addAndMakeVisible (noise_);
    addAndMakeVisible (filter_);
    addAndMakeVisible (env1_);
    addAndMakeVisible (env2_);
    addAndMakeVisible (lfo1_);
    addAndMakeVisible (lfo2_);
    addAndMakeVisible (seq_);
    volume_knob_.attatchToParameter (p.apvts, "VCA_GAIN");
    addAndMakeVisible (volume_knob_);
    addAndMakeVisible (modwheel_controls_);
    addAndMakeVisible (aftertouch_controls_);

    setSize (WIDTH, HEIGHT);
    startTimer (10);
}

Mhj01AudioProcessorEditor::~Mhj01AudioProcessorEditor() {}

void Mhj01AudioProcessorEditor::timerCallback() { repaint(); }

//==============================================================================
void Mhj01AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (40.0f);
    g.drawFittedText ("MHJ-01", getLocalBounds(), juce::Justification::bottomRight, 1);
    seq_.setActiveStep (audioProcessor.getSequencerActiveStep());
}

void Mhj01AudioProcessorEditor::resized()
{
    osc1_.setBounds (0, 0, 390, 130);
    osc2_.setBounds (0, 130, 390, 130);
    noise_.setBounds (390, 130, 75, 130);
    filter_.setBounds (465, 130, 220, 130);
    env1_.setBounds (390, 0, 220, 130);
    env2_.setBounds (610, 0, 220, 130);
    lfo1_.setBounds (0, 260, 200, 130);
    lfo2_.setBounds (200, 260, 200, 130);
    seq_.setBounds (400, 260, 255, 130);
    volume_knob_.setBounds (15, 390, 60, 95);
    modwheel_controls_.setBounds (75, 390, 105, 95);
    aftertouch_controls_.setBounds (200, 390, 105, 95);
}
