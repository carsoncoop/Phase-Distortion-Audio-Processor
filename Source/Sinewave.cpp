
#include "Sinewave.h"

void Sinewave::prepare(const double sampleRate, const int numChannels) {
    currentSampleRate = static_cast<float>(sampleRate);
    phases.resize(numChannels, 0.0f);
    smoothedFreq.reset(sampleRate, 0.03f);
    smoothedFreq.setCurrentAndTargetValue(getFreq());
}

void Sinewave::process (juce::AudioBuffer<float>& buffer) {

    if (phases.size() != buffer.getNumChannels()) {
        return; // will prevent processing
    }

    for (int channel = 0; channel < buffer.getNumChannels(); ++channel) {   //loops for each channel (left & right)
        auto* output = buffer.getWritePointer(channel); //will become sine-wave output

        for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {   //fills up buffer with samples
            const float frequency = smoothedFreq.getNextValue();
            const float phaseInc = (juce::MathConstants<float>::twoPi * frequency) / currentSampleRate;
            auto& phase = phases[static_cast<size_t>(channel)];

            output[sample] = amplitude * std::sinf(phase); //sinewave equation
            phase += phaseInc;

            if (phase >= juce::MathConstants<float>::twoPi) {
                phase -= juce::MathConstants<float>::twoPi;
            }

        }
    }

}