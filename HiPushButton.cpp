/**********************************************************************************
 *  Digital Button class
 *  Class file
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

#include "HIPushButton.h"

// ----------------------------------------------------------
// Constructor
// ----------------------------------------------------------
// Only member variable initialization here. Arduino best practice

HIPushButton::HIPushButton (uint8_t pin, uint8_t pinLevelPush, bool enablePullups , uint8_t value, unsigned long debounceMillis, unsigned long holdTimeMillis)
      : _pin(pin), _pinLevelPush(pinLevelPush), _enablePullups(enablePullups), _value(value), _debounceMillis(debounceMillis), _holdTimeMillis(holdTimeMillis) {

      // By default button value is set to pin
      if (value == 255 ) _value = _pin ;  else _value = value;

      // Initial state machine state = released
      _previousPinState       = ! _pinLevelPush ; // Released
      _state = _previousState = btnStateReleased;

}

// ----------------------------------------------------------
// Begin.  Must be called from setup()
// ----------------------------------------------------------
void HIPushButton::begin() {
      // Set pin to input.
       pinMode(_pin, INPUT);

      // Enable pullups internal resitors if asked
      if (_enablePullups) digitalWrite(_pin, HIGH);
}

// ----------------------------------------------------------
// Debounce. Used when a button is pushed or holded
// ----------------------------------------------------------
// Passing true will start deboucing.

bool HIPushButton::debounce(bool reset, unsigned long debounceMillis ){
    static bool debounced = false;
    static unsigned long dMillis;
    static unsigned long pMillis;

    if (reset ) {
      debounced = false;
      dMillis = debounceMillis;
      pMillis = millis();
    } else if ( !debounced && (millis() - pMillis) > dMillis ) debounced = true;

    return debounced;
}
// ----------------------------------------------------------
// resetStateCounters : Reset press/hold counters
// ----------------------------------------------------------
void HIPushButton::resetStateCounters() {
    _holdedCount = _pressedCount = 0;
}

// ----------------------------------------------------------
// GETTERS
// ----------------------------------------------------------
HIPushButton::btnState HIPushButton::getState() { return _state ; };
HIPushButton::btnState HIPushButton::getPreviousState(){ return _previousState ; };
unsigned int           HIPushButton::getHoldedCount() { return _holdedCount;}
unsigned int           HIPushButton::getPressedCount() { return _pressedCount; }
uint8_t                HIPushButton::getValue() { return _value; }

// ----------------------------------------------------------
// SETTERS
// ----------------------------------------------------------
void HIPushButton::setValue(uint8_t value) { _value = value ;}
void HIPushButton::setDebounceTime(unsigned long debounceMillis) { _debounceMillis = debounceMillis;}
void HIPushButton::setHoldTime(unsigned long holdTimeMillis) { _holdTimeMillis = holdTimeMillis; }

// ----------------------------------------------------------
// pressed. Evaluate if a button was pressed.
// ----------------------------------------------------------
// Use this instead of read to filter only "pressed" state

bool HIPushButton::pressed() {
    if ( stateMachine() == btnStatePressed ) return true;
    return false;
}

// ----------------------------------------------------------
// holded. Evaluate if a button was holded.
// ----------------------------------------------------------
// Use this instead of read to filter only "holded" state

bool HIPushButton::holded() {
    if ( stateMachine() == btnStateHolded ) return true;
    return false;
}
// ----------------------------------------------------------
// read. Read button state
// ----------------------------------------------------------

HIPushButton::btnState HIPushButton::read() { return stateMachine(); }


// ----------------------------------------------------------
// logicRead. internal
// ----------------------------------------------------------
// Method that read the logic level
uint8_t HIPushButton::logicRead() {
  return digitalRead(_pin) ;
}

// ----------------------------------------------------------
// stateMachine. internal
// ----------------------------------------------------------
// Evaluate button state. Return all buttons state.
HIPushButton::btnState HIPushButton::stateMachine() {
     uint8_t      p;                   // pin value
     btnState     nextState;           // next state
     bool         buttonOn;            // True is button pushed
     bool         pinStateChanged;     // True is pin state changed
     static bool  holded = false;      // True if button holded more than debounce+holded time
     static bool  debounced = false;   // True is button debounced

     nextState = btnStateUnknow;

     // State transition :
     //  btnStateReleased => btnStatePushed => btnStateHolded => btnStatePushed (=> btnStateReleased)

     p = logicRead() ;
     buttonOn = ( p == _pinLevelPush  );
     pinStateChanged =  ( p != _previousPinState );

     if (buttonOn) {
         if(pinStateChanged) {
          debounce(true,_debounceMillis);
          debounced = false;
          holded = false;
          nextState = btnStatePushed;
        }
        else {
          if ( _state == btnStateHolded) nextState = btnStatePushed;
          else if (_state == btnStatePushed ){
              if ( !debounced ) {
                 if ( debounce() ) {
                    debounce(true,_holdTimeMillis);
                    debounced = true;
                 }
                 nextState = btnStatePushed;
              }
              else if ( ! holded ) {
                 if ( debounce() ) {
                    holded = true;
                    _holdedCount++;
                    nextState = btnStateHolded;
                 } else nextState = btnStatePushed;
              }
          }
        }
     }
     else {
        if (pinStateChanged) {
          if (debounced && !holded ) {
            _pressedCount++;
            nextState = btnStatePressed;
          } else nextState = btnStateReleased;
        } else nextState = btnStateReleased;
     }
     _previousPinState = p;
     _previousState = _state;
     _state = nextState;
     return _state;
}
