/*
  ==============================================================================

    StepSequencer.cpp
    Created: 4 Mar 2023 2:12:44pm
    Author:  Martin

  ==============================================================================
*/

#include "StepSequencer.h"

StepSequencer::StepSequencer (std::array<double, 5> init_values)
    : values_(init_values)
{
}

void StepSequencer::trigger (bool forward)
{
    if (forward)
    { 
        ++active_step_;
    }
    else
    {
        --active_step_;
    }
    active_step_ %= SEQUENCER_MAX_STEPS;
}

double StepSequencer::getActiveStepValue ()
{
    return values_[active_step_];
}

unsigned int StepSequencer::getActiveStep()
{
    return active_step_;
}

void StepSequencer::updateValues (std::array<double, SEQUENCER_MAX_STEPS> new_values)
{
    values_ = new_values;
}
