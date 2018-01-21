#include <LiquidCrystal.h>

// Set pins used by the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

#include "HIObjects.h"

//HIPushButton myButton(2);
HILCDKeypad myButton(0);

void setup() {
  // put your setup code here, to run once:

Serial.begin(115200);
 // Start LCD library
lcd.begin(16, 2);
myButton.begin() ;


}

void loop() {

int r = myButton.read();


lcd.setCursor(0,0);lcd.print("Press ");lcd.print(myButton.getPressedCount());lcd.print(" Hold ");lcd.print(myButton.getHoldedCount());
switch (r) {

case HIPushButton::btnStateReleased:
    lcd.setCursor(0,1);lcd.print("Released   ");
    break;
case HIPushButton::btnStatePushed:  
    lcd.setCursor(0,1);lcd.print("Pushed     ");
    break;
case HIPushButton::btnStatePressed: 
   lcd.setCursor(0,1);lcd.print("Pressed     ");
   Serial.println(myButton.getValue()); 
   break;

case HIPushButton::btnStateHolded:  
    lcd.setCursor(0,1);lcd.print("Holded     ");
    delay(1000);
    lcd.setCursor(0,1);lcd.print("Waiting press..."); 
    while ( !myButton.pressed() ) ;
    lcd.setCursor(0,1);lcd.print("Value = ");lcd.print(myButton.getValue());lcd.print("     ");
    delay(2000);
    lcd.setCursor(0,1);lcd.print("Hold again...   "); 
    while ( !myButton.holded() ) ;
    lcd.setCursor(0,1);lcd.print("Value = ");lcd.print(myButton.getValue());lcd.print("     ");
    delay(2000);    
    break;
}






}
