#include "EllipseComponent.h"
#include "ParameterLinkerComponent.h"

EllipseComponent::EllipseComponent()
{
    setSize(ELLIPSE_SIZE, ELLIPSE_SIZE);
}

EllipseComponent::~EllipseComponent()
{
}

juce::Rectangle<float> EllipseComponent::getEllipseBounds() const
{
    auto bounds = getLocalBounds().toFloat();
    const float ellipseWidth = ELLIPSE_SIZE - 2 * PADDING;
    
    float ellipseX = (bounds.getWidth() - ellipseWidth) / 2.0f;
    float ellipseY = PADDING;
    
    return juce::Rectangle<float>(ellipseX, ellipseY, ellipseWidth, ellipseWidth);
}

void EllipseComponent::paint(juce::Graphics& g)
{
    auto ellipseBounds = getEllipseBounds();

    // Background circle
    g.setColour(isDragging ? juce::Colours::deepskyblue : juce::Colours::cornflowerblue);
    g.fillEllipse(ellipseBounds);
}

void EllipseComponent::resized()
{
}

void EllipseComponent::mouseDown(const juce::MouseEvent& e)
{
    isDragging = false;
}

void EllipseComponent::mouseDrag(const juce::MouseEvent& e)
{
    // Check if we are already in a drag session to avoid multiple starts
    if (juce::DragAndDropContainer::findParentDragContainerFor(this)->isDragAndDropActive())
        return;

    // Only trigger after a small threshold to avoid "accidental" drags on clicks
    if (e.getDistanceFromDragStart() > 5) 
    {
        if (auto* container = juce::DragAndDropContainer::findParentDragContainerFor(this)) 
        {
            isDragging = true;
            container->startDragging("ParameterLink", this);
            repaint(); 
        }
    }
}

void EllipseComponent::mouseUp(const juce::MouseEvent& e)
{
    isDragging = false;
    repaint();
}
