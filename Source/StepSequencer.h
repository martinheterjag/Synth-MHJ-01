/*
  ==============================================================================

    StepSequencer.h
    Created: 4 Mar 2023 2:12:44pm
    Author:  Martin

  ==============================================================================
*/

#include <array>

#pragma once

const unsigned int SEQUENCER_MAX_STEPS = 5;

class StepSequencer
{
public:
    enum class Trigger
    {
        LFO1 = 0,
        KEY_PRESS
    };
    explicit StepSequencer (std::array<double, 5> init_values);
    void trigger (bool forward = true);
    double getActiveStepValue();
    unsigned int getActiveStep();
    void updateValues (std::array<double, SEQUENCER_MAX_STEPS> new_values);

private:
    unsigned int active_step_ { 0 };
    std::array<double, SEQUENCER_MAX_STEPS> values_;
};
