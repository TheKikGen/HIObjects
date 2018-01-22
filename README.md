# HIObjects
Arduino classes to use easily Human interface objects like buttons, keypad,...

The classes embedd all the logic to debounce, press and hold buttons or keypads.

## Examples :

* Create 2 "digital" buttons opn pins 2 & 3 :

```c++
HIPushButton myButton(2),myButton(3);
```

* Create a an LCDkeypad, returning analog values on pin 0 :

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

