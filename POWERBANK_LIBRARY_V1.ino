#include "Powerbank.h"
#include <Wire.h>

Powerbank pb;

unsigned long previousMillis = 0;

void setup() {
  
  Serial.begin(9600);
  pb.begin();
  
}

void loop() {

  unsigned long currentMillis = millis();
  if ( currentMillis - previousMillis >= 1000 ) {
    
    Serial.println( pb.chargeCurrent() );
    previousMillis = currentMillis;
    
  } 

}
