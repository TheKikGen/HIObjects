#include "HIObjects.h"

//HIPushButton myButton(2);
HILCDKeypad myButton(0);

void setup() {
  // put your setup code here, to run once:


    myButton.begin() ;
    
    Serial.begin(115200);
    Serial.println("HIObjects demo");
    
}

void loop() {

    switch (myButton.read()) {
    
    case HIPushButton::btnStateUnknow:
        Serial.println("Unknow     \r");
        break;

    case HIPushButton::btnStateReleased:
        Serial.println("Released   \r");
        break;
    case HIPushButton::btnStatePushed:  
        Serial.println("Pushed     \r");
        break;
    case HIPushButton::btnStatePressed: 
       Serial.print("Pressed. Value = ");
       Serial.println(myButton.getValue()); 
       Serial.print("Press count ");
       Serial.println(myButton.getPressedCount());
       delay(1000);
       break;
    case HIPushButton::btnStateHolded:  
        Serial.print("Holded. value = ");
        Serial.println(myButton.getValue()); 
        Serial.print(" Hold cound ");
        Serial.println(myButton.getHoldedCount());
        delay(1000);
        break;
    }
}
