/*!
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
  btnStateUnknwow = 255,
  btnStateReleased     = 0, 
  btnStatePushed       = 1,
  btnStatePressed      = 2, 
  btnStateHolded       = 4
 };

 
 static int _instanceRegisterIndex;
 static HIPushButton* _instanceRegister[];
  
  int     _thisInstanceRegisterIndex = 0;
  uint8_t _state  ;                               // Current button state
  uint8_t _previousState ;                        // Previous button state

  uint8_t             _pin;                       // Arduino pin assigned 
  uint8_t             _previousPinState ;         // Previous pin state  
  uint8_t             _pinLevelPush   =  LOW;     // Logic when button pressed
  boolean             _enablePullups  =  true;    // True if internal pullups must be set
 
  unsigned long       _debounceMillis =  50;     // Delay to debounce when button pushed
  unsigned long       _holdTimeMillis =  950;    // Delay of holding (from button on)
  unsigned int        _holdedCount    =  0;
  unsigned int        _pressedCount   =  0;





// Constructor
HIPushButton::HIPushButton (uint8_t pin) ;
void HIPushButton::begin();
uint8_t HIPushButton::read();
uint8_t HIPushButton::pressed() ;
void HIPushButton::resetStateCounters() ;
unsigned int HIPushButton::getHoldedCount();
unsigned int HIPushButton::getPressedCount();
void setDebounceTime(unsigned long debounceMillis);
void setHoldTime(unsigned long holdTimeMillis);

bool HIPushButton::debounce(bool reset=false, unsigned long debounceMillis=0 );
uint8_t HIPushButton::stateMachine();
};
