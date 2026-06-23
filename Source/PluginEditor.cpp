#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p), freqSliderAttachment(processorRef.getState(), "freqHz", frequencySlider),
    playButtonAttachment(processorRef.getState(), "play", playButton)
{
    juce::ignoreUnused (processorRef);

    playButton.setButtonText("Playing");
    playButton.setToggleState(true, juce::NotificationType::dontSendNotification);
    playButton.setClickingTogglesState(true);
    playButton.onClick = [this]() {
        const bool isPlaying = playButton.getToggleState();
        if (isPlaying) {
            playButton.setButtonText("Playing");
        }
        else {
            playButton.setButtonText("Bypassed");
        }
    };
    addAndMakeVisible(playButton);

    addAndMakeVisible(firstObj);

    frequencyLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(frequencyLabel);

    frequencySlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    frequencySlider.setNumDecimalPlacesToDisplay(2);
    frequencySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 50);
    addAndMakeVisible(frequencySlider);//makes freq slider a child component of the editor

    setSize (400, 300);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void AudioPluginAudioProcessorEditor::resized()
{
    playButton.setBounds(getWidth() / 2 - 50, getHeight() - 50, 100, 50);
    frequencySlider.setBounds(getWidth() / 2 - 100, getHeight() / 2 - 100, 200, 200);
    frequencyLabel.setBounds(getWidth() / 2 - 100, getHeight() / 2 - 125, 200, 200);
    firstObj.setBounds(50, 0, 300, 20);
}

