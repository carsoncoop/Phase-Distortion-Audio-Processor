#pragma once

#include <juce_audio_basics/juce_audio_basics.h>
//Notes
//Sample rate: how many samples are played per second
//Buffer size: how many samplesa are processed at once

class Sinewave {
    float amplitude = 0.1f;
    float currentSampleRate = 0.0f;
    std::vector<float> phases;
public:
    void prepare (double sampleRate, int numChannels);
    void process (juce::AudioBuffer<float>& buffer);
    [[nodiscard]] float getAmp() const { return amplitude; }
    [[nodiscard]] float getFreq() { return smoothedFreq.getNextValue(); }
    void setAmp(const float newAmp) { amplitude = newAmp; }
    void setFreq(const float newFreq) { smoothedFreq.setTargetValue(newFreq); }
    juce::SmoothedValue<float, juce::ValueSmoothingTypes::Multiplicative> smoothedFreq;

};
