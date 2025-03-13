#pragma once

#include <JuceHeader.h>

class SelfDestructingObject : public Component
{
public:
    SelfDestructingObject ()
    {
        Timer::callAfterDelay (Random::getSystemRandom ().nextInt (3000), [weak = WeakReference (this)](){
            if (weak)
                delete weak.get ();
            
            DBG ("Deleted object");
        });
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SelfDestructingObject)
    JUCE_DECLARE_WEAK_REFERENCEABLE (SelfDestructingObject)
};
