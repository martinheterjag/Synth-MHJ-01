/*
  ==============================================================================

    Lfo.h
    Created: 10 Nov 2022 10:10:26pm
    Author:  Martin

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
class Lfo : public juce::dsp::Oscillator<double> {
public:
    enum class Waveform {
        SINE = 0,
        SAW,
        SQUARE,
        TRIANGLE
    };
    void resetLfo();
    void setWaveform(Waveform waveform);
    double getOutput();
    void update(juce::dsp::ProcessContextReplacing<float>& context);

private:
    Waveform waveform_{ Waveform::SINE };
    double output_;
};