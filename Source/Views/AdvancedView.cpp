#include "AdvancedView.h"

#include <thread>

AdvancedView::AdvancedView (AudimoAudioProcessor& p)
    : audioProcessor (p)
{   
    // allows bleSettingsComponent to listen to blemanager errors
    audioProcessor.getBLEManager().addChangeListener(this);

    for (auto& label : rawDataLabels) {
      addAndMakeVisible(label);
    }
 
    addAndMakeVisible(bleSettingsComponent);
    bleSettingsComponent.setVisible(false);

    addAndMakeVisible(bleButton);
    bleButton.setButtonText("Bluetooth");
    bleButton.onClick = [this] {
        bleSettingsComponent.setVisible(!bleSettingsComponent.isVisible());
        if (bleSettingsComponent.isVisible()) {
            bleSettingsComponent.toFront(true);
            std::thread([this] { audioProcessor.getBLEManager().start(); }).detach();
        }
    };
   
    // Start timer to update label
    startTimerHz(30); 
}

AdvancedView::~AdvancedView()
{
    audioProcessor.getBLEManager().removeAllChangeListeners();
    // stopTimer
}

void AdvancedView::paint(juce::Graphics& g)
{
    g.setColour (juce::Colours::white);
    g.setFont (juce::Font (15.0f));
}

void AdvancedView::resized()
{
    // Layout labels in two columns
    const int totalLabels = (int)rawDataLabels.size();
    const int cols = 2;
    const int rows = (totalLabels + cols - 1) / cols;

    auto area = getLocalBounds().reduced (8);
    int labelH = area.getHeight() / rows;
    int colW = area.getWidth() / cols;

    for (int i = 0; i < totalLabels; ++i)
    {
        int r = i % rows;
        int c = i / rows;
        rawDataLabels[i].setBounds (area.getX() + c * colW, area.getY() + r * labelH, colW - 6, labelH - 4);
    }

    int buttonRow = (totalLabels) % rows; 
    int buttonCol = (totalLabels) / rows; 

    bleButton.setBounds (area.getX() + buttonCol * colW, 
                         area.getY() + buttonRow * labelH, 
                         colW - 6, 
                         labelH - 4);

    // The subwindow should be sized independently of the grid. 
    // Here, we center it and give it a fixed size (e.g., 300x200 pixels).
    const int subW = 300;
    const int subH = 200;

    bleSettingsComponent.setBounds (getWidth()/2 - subW/2, getHeight()/2 - subH/2, subW, subH);
}

void AdvancedView::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    juce::String msg = audioProcessor.getBLEManager().getLastErrorMessage();
    bleSettingsComponent.setErrorMessage(msg);
}

// Timer callback to update the label
void AdvancedView::timerCallback() 
{
  // Copy data under lock then update labels on GUI thread
  SensorDataSnapshot copy = audioProcessor.getSensorDataCopy();

  // Update label texts (match order in sensorData)
  if (rawDataLabels.size() == 13) {
    rawDataLabels[0].setText ("time: " + juce::String (copy.time, 3), juce::dontSendNotification);
    rawDataLabels[1].setText ("proximity: " + juce::String (copy.proximity), juce::dontSendNotification);
    rawDataLabels[2].setText ("gesture: " + juce::String (copy.gesture), juce::dontSendNotification);
    rawDataLabels[3].setText ("ax: " + juce::String (copy.ax, 3), juce::dontSendNotification);
    rawDataLabels[4].setText ("ay: " + juce::String (copy.ay, 3), juce::dontSendNotification);
    rawDataLabels[5].setText ("az: " + juce::String (copy.az, 3), juce::dontSendNotification);
    rawDataLabels[6].setText ("gx: " + juce::String (copy.gx, 3), juce::dontSendNotification);
    rawDataLabels[7].setText ("gy: " + juce::String (copy.gy, 3), juce::dontSendNotification);
    rawDataLabels[8].setText ("gz: " + juce::String (copy.gz, 3), juce::dontSendNotification);
    rawDataLabels[9].setText ("ex: " + juce::String (copy.ex, 3), juce::dontSendNotification);
    rawDataLabels[10].setText ("ey: " + juce::String (copy.ey, 3), juce::dontSendNotification);
    rawDataLabels[11].setText ("ez: " + juce::String (copy.ez, 3), juce::dontSendNotification);
    rawDataLabels[12].setText ("mic_rms: " + juce::String (copy.mic_rms, 3), juce::dontSendNotification);
  }

  repaint();
}