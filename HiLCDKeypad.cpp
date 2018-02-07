/**********************************************************************************
 *  LCD Keypad class
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

#include "HILCDKeypad.h"

// ----------------------------------------------------------
// Constructor
// ----------------------------------------------------------
// Only member variable initialization here. Arduino best practice
HILCDKeypad::HILCDKeypad (uint8_t pin, unsigned long debounceMillis, unsigned long holdTimeMillis) :  HIPushButton(pin,LOW,true,btnNone,debounceMillis, holdTimeMillis) {

}

// ----------------------------------------------------------
// Begin.  Must be called from setup()
// ----------------------------------------------------------
void HILCDKeypad::begin() {
      // Set pin to input.
       pinMode(_pin, INPUT);
}

// ----------------------------------------------------------
// GETTERS
// ----------------------------------------------------------
HILCDKeypad::btnValue HILCDKeypad::getValue() { 
  // Pressed state is sent when button is released (btnNone), so we have to take care
  // Force the last "true" value red 
  if (_state == btnStatePressed ) return _previousValue ;
  return _value; 
}

// ----------------------------------------------------------
// LCD Keypad reliable value reading
// ----------------------------------------------------------
// As many keypad shields use a resistor network on analog pin n,
// unreliable results are seen when pressing buttons.
// This method acts as a filter and returns value after 6 consistents reads or unknow after n try
HILCDKeypad::btnValue HILCDKeypad::lcdKeypadReadPinValue() {
    int adcKeyPressed ;
    uint8_t i=0;

    if ( (adcKeyPressed = analogRead(_pin))  > 1000) return btnNone;
    while ( (adcKeyPressed = analogRead(_pin)) - analogRead(_pin)  + analogRead(_pin) - analogRead(_pin) + analogRead(_pin) - analogRead(_pin) ) {
      if ( i++ > 20 ) return btnNone;
    }
    if (adcKeyPressed < 120)  return btnRight;    // 0
    if (adcKeyPressed < 250)  return btnUp;       // 130
    if (adcKeyPressed < 450)  return btnDown;     // 305
    if (adcKeyPressed < 650)  return btnLeft;     // 478
    if (adcKeyPressed < 850)  return btnSelect;   // 720
    return btnNone; // when all others fail...
}

// ----------------------------------------------------------
// LogicRead. Simulate a digital logic
// ----------------------------------------------------------
// So, we can rely on the state machine of the ancestor
uint8_t HILCDKeypad::logicRead() { 
  // Read the value of the Keypad
  // If button valued, set the value and pseudo logic level for the machine state ancestor
  // Pressed state is sent when button is released (btnNone), so we have to take care

  if (_value != btnNone) _previousValue = _value;
  _value = lcdKeypadReadPinValue();

  return ( _value  != btnNone ? _pinLevelPush : !_pinLevelPush ) ;
}




