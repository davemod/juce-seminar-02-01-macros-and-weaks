#include "MainComponent.h"
#include "SelfDestructingObject.h"

//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible (checkButton);
    addAndMakeVisible (crashButton);
    addAndMakeVisible (deleteButton);

    setSize (400, 400);
    
    /* lets create an example object and assume that its lifetime
     * is managed somewhere else in our application and we have no
     * control over it when is deleted. We'll simulate this with a object
     * that deletes itself after a random time (within up to 3 second,
     * you'll see a print).
     */
    
    auto obj = new SelfDestructingObject ();
    obj->setName ("Self Destructing Object");
    


    //The crash button tries to access the object by checking a normal pointer passed
    crashButton.onClick = [obj](){
        if (obj)
            DBG ("Name: " << obj->getName ());
        else
            DBG ("Object has been deleted");
    };
    
    // the checkButton uses a weak reference for this.
    checkButton.onClick = [weak = WeakReference<SelfDestructingObject> (obj)] (){
        if (weak)
            DBG ("Name: " << weak->getName ());
        else
            DBG ("Object has been deleted");
    };
}

MainComponent::~MainComponent()
{
    
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    auto bounds = getLocalBounds ();
    auto b = Rectangle<int> { 100, 25 };
    checkButton.setBounds (bounds.removeFromLeft (bounds.getWidth () / 2).withSizeKeepingCentre(b.getWidth (), b.getHeight ()));
    crashButton.setBounds (bounds.withSizeKeepingCentre(b.getWidth(), b.getHeight ()));
}
