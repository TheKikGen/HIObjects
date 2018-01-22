# HIObjects
Arduino classes to use easily Human interface objects like buttons, keypad,...

The classes embedd all the logic to debounce, press and hold buttons or keypads.

## Examples :


Create 2 "digital" buttons opn pins 2 & 3 :

HIPushButton myButton(2),myButton(3);

Create a an LCDkeypad, returning analog values on pin 0 :

HILCDKeypad myKeypad(0);

Reading myButton state :
r = myButton.read();

Reading keypad value after a button holded :
if ( myKeypad.holded() ) v = myKeypad.getValue();

Waiting for a button pressed :

while ( !myButton.pressed() ) ;

