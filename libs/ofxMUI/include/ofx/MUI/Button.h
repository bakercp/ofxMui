// =============================================================================
//
// Copyright (c) 2009-2016 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#pragma once
	

#include "ofx/DOM/Events.h"
#include "ofx/MUI/Widget.h"


namespace ofx {
namespace MUI {


class Button;


class ButtonEventArgs: public DOM::EventArgs
{
public:
    using DOM::EventArgs::EventArgs;

    virtual ~ButtonEventArgs();

    static const std::string BUTTON_DOWN;
    static const std::string BUTTON_UP;
    static const std::string BUTTON_PRESSED;

};



/// \brief A simple one state push button.
///
/// In addition to the standard Pointer events, the following button events are
/// triggered when a button is pressed:
///
///     onButtonDown // When the button is pressed.
///     onButtonUp // When the button is released.
///
///     onButtonPressed // If the button is pressed and released according to
///         the `PointerOverOnRelease` policy.
///
///     onButtonStateChanged // Called
///     if
//    ofEvent<void> onButtonPressed;
//
//    /// \brief Event called when the button switches state.
//    ///
//    /// The event data represents the current state of the button.
//    ofEvent<const int> onButtonStateChanged;
//
//    /// \brief The event called when the button goes from an up to down state.
//    ofEvent<void> onButtonDown;
//
//    /// \brief The event called when the button goes from down to up state.
//    ofEvent<void> onButtonUp;
///
class Button: public Widget
{
public:
    /// \brief Create a Button with the given parameters.
    /// \param id The Widget's id string.
    /// \param x x-position in parent coordinates.
    /// \param y y-position in parent coordinates.
    /// \param width The width (x-dimension) of Widget.
    /// \param height The height (y-dimension) of Widget.
    /// \param autoExclusive If true, behaves like an exclusive radio button.
    /// \param triggersOnRelease If true, the button is toggled only on release.
    /// \param requirePointerOverOnRelease Require a pointer to be over the
    ///        button to trigger to change states.
    /// \param stateCount The number of values for multi-state buttons.
    Button(const std::string& id = "",
           float x = 0,
           float y = 0,
           float width = DEFAULT_WIDTH,
           float height = DEFAULT_HEIGHT,
           bool autoExclusive = false,
           bool triggersOnRelease = false,
           bool requirePointerOverOnRelease = true,
           std::size_t stateCount = 1);

    /// \brief Destroy the Button.
    virtual ~Button();

    /// \returns true iff the value should be changed on Button release.
    bool triggersOnRelease() const;

    bool requirePointerOverOnRelease() const;

    bool autoExclusive() const;

    /// \brief Return the number of Button states.
    std::size_t stateCount() const;

    virtual void onDraw() const override;

    /// \brief Default callback for built-in events, including dragging.
    /// \param e The event data.
    void onPointerEvent(DOM::PointerUIEventArgs& e);

    /// \brief Default callback for built-in events, including dragging.
    /// \param e The event data.
    void onPointerCaptureEvent(DOM::PointerCaptureUIEventArgs& e);

    /// \brief Add listeners to this onValueChanged event.
    /// \tparam ListenerClass The class type of the listener.
    /// \tparam ListenerMethod The name of the listener method.
    /// \param listener A pointer to the listener instance.
    /// \param method A pointer to the listener method.
    /// \param prioirty The order priority of this listener.
    template <class ListenerClass, typename ListenerMethod>
    void addListener(ListenerClass* listener, ListenerMethod method, int priority = OF_EVENT_ORDER_AFTER_APP)
    {
        ofAddListener(onValueChanged, listener, method, priority);
    }

    /// \brief Remove listeners to this onValueChanged event.
    /// \tparam ListenerClass The class type of the listener.
    /// \tparam ListenerMethod The name of the listener method.
    /// \param listener A pointer to the listener instance.
    /// \param method A pointer to the listener method.
    /// \param prioirty The order priority of this listener.
    template <class ListenerClass, typename ListenerMethod>
    void removeListener(ListenerClass* listener, ListenerMethod method, int priority = OF_EVENT_ORDER_AFTER_APP)
    {
        ofRemoveListener(onValueChanged, listener, method, priority);
    }

    /// \brief Event called when button is pressed and released.
    ///
    /// This event follows the require release over policy.
    DOM::DOMEvent<ButtonEventArgs> onButtonPressed;

    /// \brief The event called when the button goes from an up to down state.
    DOM::DOMEvent<ButtonEventArgs> onButtonDown;

    /// \brief The event called when the button goes from down to up state.
    DOM::DOMEvent<ButtonEventArgs> onButtonUp;

    /// \brief The event that is set when the value of a button changes.
    ofEvent<int> onValueChanged;

    /// \brief The assignment operator.
    /// \param v Value to assign.
    /// \returns the assigned value.
    int operator = (int v);

    /// \brief Dereference operator.
    operator const int& ();

    enum
    {
        DEFAULT_WIDTH = 40,
        DEFAULT_HEIGHT = 40,
    };

protected:
    /// \brief A callback for the ParameterWidget's value.
    /// \param value The the updated value.
    void _onValueChanged(const void* sender, int& value);

    /// \brief Increment the current button state.
    void _incrementState();

    /// \brief If true, will act as a radio button.
    ///
    /// It will disable all sibling autoExlusive buttons on press.
    bool _autoExclusive = true;

    /// \brief Update the value immediately on press.
    bool _triggersOnRelease = false;

    /// \brief Require that release is over the button.
    bool _requirePointerOverOnRelease = true;

    /// \brief How many states can this button represent?
    std::size_t _stateCount = 1;

    /// \brief The "primary" pointer id.
    ///
    /// This is the first pointer that was captured when dragging.
    std::size_t _primaryPointerId = 0;

    /// \brief The parameter to watch.
    ofParameter<int> _value;

    friend class ButtonGroup;

};


/// \brief A two state button.
class ToggleButton: public Button
{
public:
    /// \brief Create a ToggleButton with the given parameters.
    /// \param id The Widget's id string.
    /// \param x x-position in parent coordinates.
    /// \param y y-position in parent coordinates.
    /// \param width The width (x-dimension) of Widget.
    /// \param height The height (y-dimension) of Widget.
    /// \param autoExclusive If true, behaves like an exclusive radio button.
    /// \param triggersOnRelease If true, the button is toggled only on release.
    /// \param requirePointerOverOnRelease Require a pointer to be over the
    ///        button to trigger to change states.
    ToggleButton(const std::string& id = "",
                 float x = 0,
                 float y = 0,
                 float width = DEFAULT_WIDTH,
                 float height = DEFAULT_HEIGHT,
                 bool autoExclusive = false,
                 bool triggersOnRelease = false,
                 bool requirePointerOverOnRelease = true);

    /// \brief Destroy the ToggleButton
    virtual ~ToggleButton();

    virtual void onDraw() const override;

};


/// \brief A two state Radio style button.
class RadioButton: public Button
{
public:
    /// \brief Create a RadioButton with the given parameters.
    /// \param id The Widget's id string.
    /// \param x x-position in parent coordinates.
    /// \param y y-position in parent coordinates.
    /// \param width The width (x-dimension) of Widget.
    /// \param height The height (y-dimension) of Widget.
    RadioButton(const std::string& id = "",
                float x = 0,
                float y = 0,
                float width = DEFAULT_WIDTH,
                float height = DEFAULT_HEIGHT);

    /// \brief Destroy the ToggleButton
    virtual ~RadioButton();
    
    virtual void onDraw() const override;

    virtual bool hitTest(const DOM::Position& parentPosition) const override;

};

} } // ofx::MUI