#include <LiquidCrystal.h>
#include "HiPushButton.h"

// Set pins used by the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

HIPushButton myButton(2);

void setup() {
  // put your setup code here, to run once:

Serial.begin(115200);
 // Start LCD library
lcd.begin(16, 2);
myButton.begin() ;

}

void loop() {
  // put your main code here, to run repeatedly:

/*
unsigned long t1,t2,t3;

t1=millis(); 
myButton.debounce(true,1000);
while (!myButton.debounce());
t1 = millis() - t1;
Serial.println(t1);

t1=millis(); 
!myButton.debounce(true,2000);
while (!myButton.debounce());
t1 = millis() - t1;
Serial.println(t1);
*/

 











int r = myButton.read();

lcd.setCursor(0,0);lcd.print("Press ");lcd.print(myButton.getPressedCount());lcd.print(" Hold ");lcd.print(myButton.getHoldedCount());
switch (r) {

case HIPushButton::btnStateReleased:
    lcd.setCursor(0,1);lcd.print("Released");
    break;
case HIPushButton::btnStatePushed:  
    lcd.setCursor(0,1);lcd.print("Pushed  ");
    break;
case HIPushButton::btnStatePressed: 
   lcd.setCursor(0,1);lcd.print("Pressed "); 
   break;

case HIPushButton::btnStateHolded:  
    lcd.setCursor(0,1);lcd.print("Holded  ");
    delay(1000);
    break;


}






}
