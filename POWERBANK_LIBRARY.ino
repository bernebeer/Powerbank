#include "Powerbank.h"
#include <Wire.h>

Powerbank mypb;

unsigned long previousMillis = 0;

void setup() {
  
  Serial.begin(9600);
  mypb.begin();
  
}

void loop() {

  // Check powerbank 
  unsigned long currentMillis = millis();
  if ( currentMillis - previousMillis >= 1000 ) {

    mypb.resetWatchdog();

    Serial.print("Charge current: \t");
    Serial.print( mypb.chargeCurrent() );
    Serial.println("mA");
    Serial.print("Battery level: \t\t");
    Serial.print( mypb.batteryLevel() );
    Serial.println("%");
    Serial.print("Battery voltage: \t");
    Serial.print( mypb.batteryVoltage() );
    Serial.println("mV");
    Serial.print("Output current: \t");
    Serial.print( mypb.outputCurrent(), 0 );
    Serial.println("mA");
    Serial.print("Charging: \t\t");
    if ( mypb.isCharging() == true ) {
      Serial.println("Yes");
    }
    else {
      Serial.println("No");
    }
    
    Serial.println();
    previousMillis = currentMillis;
    
  } 

}
