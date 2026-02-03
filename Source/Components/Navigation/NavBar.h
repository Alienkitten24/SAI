#pragma once

#include <JuceHeader.h>
#include <functional>

class NavBar : public juce::Component
{
public:
    NavBar();
    ~NavBar();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void initButton(juce::TextButton& btn, const juce::String name, int screen_id);

    std::function<void(int)> changeScreenFn;
private:
    juce::TextButton effectsViewButton;
    juce::TextButton matrixViewButton;
    juce::TextButton advancedViewButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NavBar)
};