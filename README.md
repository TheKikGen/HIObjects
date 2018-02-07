# HIObjects
Arduino classes to use easily Human interface objects like buttons, keypad,...

The classes embedd all the logic to debounce, press and hold buttons or keypads.

## Examples :

* Create 2 "digital" buttons on pins 2 & 3 :

```c++
HIPushButton myButton(2),myButton(3);
```

* Create a an LCDkeypad, returning analog values on pin 0 (like the DFRobot one) :

```c++
HILCDKeypad myKeypad(0);
```

* Reading myButton state :

```c++
r = myButton.read();
```

* Reading keypad value after a button holded :

```c++
if ( myKeypad.holded() ) v = myKeypad.getValue();
```

* Waiting for a button pressed :

```c++
while ( !myButton.pressed() ) ;
```

* Full example sketch :

```c++

#include "HIObjects.h"
HIPushButton myButton(2);

void setup() {
  // put your setup code here, to run once:

Serial.begin(115200);
lcd.begin(16, 2); 
myButton.begin() ;
}

void loop() {

  int r = myButton.read();

  switch (r) {

  case HIPushButton::btnStateReleased:
      Serial.println("Released   ");
      break;
  case HIPushButton::btnStatePushed:  
      Serial.println("Pushed     ");
      break;
  case HIPushButton::btnStatePressed: 
     Serial.print("Pressed     ");
     Serial.println(myButton.getValue()); 
     delay(1000)
     break;
  case HIPushButton::btnStateHolded:  
     Serial.print("Holded     ");
     Serial.println(myButton.getValue()); 
     delay(1000);
     break;
  }

}

```

## TODO :
* Create a factory to create and manage instance (eg : create a "panel" object with 10 buttons
* Add HIPotentiometer, HiRotaryEncoder....
