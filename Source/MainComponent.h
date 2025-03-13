#pragma once

#include <JuceHeader.h>

/** 
 * MACROS
 * 
 * In C++, macros are a feature of the preprocessor that allows you to define 
 * code that can be reused throughout your program. They are defined using the 
 * #define directive and can be used to create constants, functions, or even 
 * conditional compilation. Macros are replaced by their definitions before 
 * the actual compilation process begins.
 */

// Define a constant macro
#define MAX(a, b) ((a) > (b) ? (a) : (b))  // Define a function-like macro

// Define a conditional compilation macro
#define EXTENDED_FEATURE_SET 1  

// define different macros depending on the value of EXTENDED_FEATURE_SET
#if EXTENDED_FEATURE_SET
#define IF_EXTENDED(extendedValue, normalValue) extendedValue
#else
#define IF_EXTENDED(extendedValue, normalValue) normalValue
#endif

// Define a macro that expands to the name of the plugin
const static inline String PluginName{ IF_EXTENDED ("Extended Plugin", "Normal Plugin") };





 /*
 * #if, #elif, #else, #endif
 * 
 * The `#if` and `#endif` directives are used for conditional compilation. 
 * They allow you to include or exclude parts of the code based on certain conditions.
 * This is particularly useful for writing platform-specific code.
 * 
 * Example:
 * 
 * #if JUCE_MAC
 *     // Code specific to macOS
 * #elif JUCE_WINDOWS
 *     // Code specific to Windows
 * #elif JUCE_LINUX
 *     // Code specific to Linux
 * #elif JUCE_IOS
 *     // Code specific to iOS
 * #elif JUCE_ANDROID
 *     // Code specific to Android
 * #else
 *     // Code for unsupported platforms
 * #endif
 * 
 * This ensures that the correct code is compiled for the target platform. 
 * 
 * JUCE provides also some useful macros to check the build configuration:
 * 
 * JUCE_DEBUG - Defined when the project is built in debug mode.
 * JUCE_RELEASE - Defined when the project is built in release mode.
 */






 /** ProjectInfo excursus - not a macro but also useful
  * 
  * The ProjectInfo class provides information about the project, such as the
  * project name, company name, and version string. This information is defined
  * in the Projucer and can be accessed in your code using the ProjectInfo class.
  */

  static inline void printProjectInfo ()
  {
      DBG ("projectName " << ProjectInfo::projectName);
      DBG ("companyName " << ProjectInfo::companyName);
      DBG ("versionString " << ProjectInfo::versionString);
  }





/**
 * Memory Leaks
 * 
 * Memory leaks are a common problem in C++ programs. They occur when memory
 * is allocated but not deallocated, leading to a loss of memory that can
 * accumulate over time and cause the program to run out of memory. 
 * 
 * Example:
 * 
 * void memoryLeakExample () { new LeakingObject (); }
 * 
 * In this example, a new LeakingObject is created but never deleted, causing
 * a memory leak. To avoid memory leaks, always make sure to use smart pointers
 * like std::unique_ptr, std::shared_ptr, juce::OwnedArray or 
 * juce::ReferenceCountedObject.
 * 
 * To detect memory leaks, JUCE provides a leak detector that can be enabled by
 * using the JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR macro in your class as
 * shown in the example below.
 */

class LeakingObject
{
public:
    LeakingObject () = default;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LeakingObject)
};






/**
 * Bad Access, Null Pointer and Weak References
 * 
 * Bad access and null pointer errors are also common problems in C++ programs that
 * can lead to crashes. A bad access error occurs when a program tries to access
 * memory that it does not have permission to access, while a null pointer error
 * occurs when a program tries to access memory through a null pointer.
 * 
 * WeakReferenceableObject* obj = nullptr;
 * obj->printSomething ("Hello"); // obviously null pointer error
 * 
 * To avoid these errors, always make sure to check for null pointers before
 * dereferencing them. JUCE provides a WeakReference class that can be used to
 * safely reference objects without keeping them alive. This can help prevent
 * null pointer errors.
 * 
 * Here is an example of how to use WeakReference in JUCE. Also you'll find an 
 * example in MainComponent.h and MainComponent.cpp.
 */

class WeakReferenceableObject
{
public:

    void printSomething (juce::String dbg) { DBG (dbg); }
    
private:
    JUCE_DECLARE_WEAK_REFERENCEABLE (WeakReferenceableObject)
};
    

static inline void WeakReferenceExample ()
{
    WeakReference<WeakReferenceableObject> weak;

    {
        // creating a new object
        std::unique_ptr<WeakReferenceableObject> obj = std::make_unique<WeakReferenceableObject> ();
        
        // set the weak reference to the object
        weak = obj.get();

        if (weak)
            weak->printSomething ("Hello");

        // obj is deleted here and weak reference is automatically set to nullptr
    }

    if (weak)
        weak->printSomething ("This will not be printed"); // no crash
}






/**
 * MainComponent gives another example on how to use WeakReference in JUCE.
 * 
 * See MainComponent.cpp for details and start the application
 * 
 */
class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    TextButton checkButton{ "check" };
    TextButton crashButton{ "crash" };
    TextButton deleteButton{ "delete object" };

    // JUCE_HEAVYWEIGHT_LEAK_DETECTOR (classname)
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
