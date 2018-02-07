/**********************************************************************************
 *  Digital Button class
 *  Header file.
 *  Franck Touanen - Dec 2017.
 **********************************************************************************
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#pragma once

#include "HiObjects_Namespace.h"

#ifndef HIPushButton_h
#define HIPushButton_h

#if ARDUINO
#include <Arduino.h>
#else
#include <inttypes.h>
typedef uint8_t byte;
#endif

class HIPushButton {
 public:
   // Enumeration of Button state
   enum btnState {
    btnStateUnknow      = 255,
    btnStateReleased     = 0,
    btnStatePushed       = 1,
    btnStatePressed      = 2,
    btnStateHolded       = 4
   };

 private:
       
 protected:  
  uint8_t             _pin              = 0;               // Arduino pin assigned
  uint8_t             _pinLevelPush     = LOW;             // Logic when button pressed
  boolean             _enablePullups    = true;            // True if internal pullups must be set. Specific to digital button.
  uint8_t             _value            = 255;             // Button value.
  unsigned long       _debounceMillis   = 50;              // Delay to debounce when button pushed
  unsigned long       _holdTimeMillis   = 950;             // Delay of holding (from button on)

  btnState            _state            = btnStateUnknow;  // Current button state
  btnState            _previousState    = btnStateUnknow;  // Previous button state
  uint8_t             _previousPinState = 0 ;              // Previous pin state
  unsigned int        _holdedCount      = 0;               // Count number of holded events
  unsigned int        _pressedCount     = 0;               // Count number of pressed events

  public:
  // Constructor
  HIPushButton (uint8_t pin, uint8_t pinLevelPush = LOW , bool enablePullups = true, uint8_t value = 255, unsigned long debounceMillis = 50 , unsigned long holdTimeMillis = 950 );
 
  protected:
    virtual bool         debounce(bool reset=false, unsigned long debounceMillis=0 );
    virtual btnState     stateMachine(); 
    virtual uint8_t      logicRead();
    
  public:
    virtual void         begin();
    uint8_t              getValue();
    virtual void         setValue(uint8_t value);
    
    virtual btnState     read();
    virtual bool         pressed() ;
    virtual bool         holded() ;
    virtual void         resetStateCounters() ;
    virtual btnState     getState();
    virtual btnState     getPreviousState();
    virtual unsigned int getHoldedCount();
    virtual unsigned int getPressedCount();
    virtual void         setDebounceTime(unsigned long debounceMillis);
    virtual void         setHoldTime(unsigned long holdTimeMillis);
};
#endif
