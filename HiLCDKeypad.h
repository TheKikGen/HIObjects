/**********************************************************************************
 *  LCD keypad class
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

#ifndef HILCDKeypad_h
#define HILCDKeypad_h

#if ARDUINO
#include <Arduino.h>
#else
#include <inttypes.h>
typedef uint8_t byte;
#endif

#ifndef HIPushButton_h
#include "HIPushButton.h"
#endif

class HILCDKeypad: public HIPushButton   {
  public:
   // Enumeration of Button name
   enum btnValue {
    btnNone              = 0,
    btnRight             = 1,
    btnUp                = 2,
    btnDown              = 3,
    btnLeft              = 4,
    btnSelect            = 5
   };
 private: 
  btnValue           _value          =  btnNone;      // Button value.
  btnValue           _previousValue  =  btnNone;      // Previous value.
 public:
  // Constructor
   HILCDKeypad (uint8_t pin, unsigned long debounceMillis = 50 , unsigned long holdTimeMillis = 950 );


 virtual void      begin();
  btnValue          getValue();
 
 private:
  btnValue          lcdKeypadReadPinValue();
  // Digital "Logic" is simulated here
  virtual uint8_t   logicRead() ;
  // Mask public setValue and getValue as keypad is multivalued in an enum type
  using HIPushButton::getValue;
  using HIPushButton::setValue;
};

#endif
