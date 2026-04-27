#pragma once

#include <JuceHeader.h>

class EllipseComponent : public juce::Component
{
public:
    EllipseComponent();
    ~EllipseComponent();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void mouseDown(const juce::MouseEvent& e) override;
    void mouseDrag(const juce::MouseEvent& e) override;
    void mouseUp(const juce::MouseEvent& e) override;

private:
    static constexpr float ELLIPSE_SIZE = 40.0f;
    static constexpr float PADDING = 4.0f;
    
    bool isDragging = false;

    juce::Rectangle<float> getEllipseBounds() const;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EllipseComponent)
};
