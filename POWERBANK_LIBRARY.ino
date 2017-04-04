#include "Powerbank.h"
#include <Wire.h>
#include <FastLED.h>

#define MAX_CHARGE_CURRENT 300

// Instantiate Powerbank object, name it anything, in this case 'mypb'
Powerbank mypb;

unsigned long previousMillis = 0;

void setup() {
  
  Serial.begin(9600);
  mypb.begin(MAX_CHARGE_CURRENT);

  pinMode(LEDFETPIN, OUTPUT);
  
}

void loop() {

  digitalWrite(LEDFETPIN, HIGH);

  // Check powerbank every second
  unsigned long currentMillis = millis();
  if ( currentMillis - previousMillis >= 1000 ) {

    // Reset BQ25895 watchdog timer, prevents BQ25895 register reset to default, needed every 100 seconds if BQ25895 did not receive an I2c write
    mypb.resetWatchdog();

    // Serial print data
    Serial.print("Charge current: \t");
    Serial.print( mypb.getChargeCurrent() );
    Serial.println("mA");
    Serial.print("Battery level: \t\t");
    Serial.print( mypb.getBatteryLevel() );
    Serial.println("%");
    Serial.print("Battery voltage: \t");
    Serial.print( mypb.getBatteryVoltage() );
    Serial.println("mV");
    Serial.print("Output current: \t");
    Serial.print( mypb.getOutputCurrent(), 0 );
    Serial.println("mA");
    Serial.print("Batfet disabled: \t");
    if ( mypb.isBatfetDisabled() ) {
      Serial.println("Yes");
    }
    else {
      Serial.println("No");
    }
    Serial.print("Charging: \t\t");
    if ( mypb.isCharging() ) {
      Serial.println("Yes");
    }
    else {
      Serial.println("No");
    }
    
    // Print empty line for readability
    Serial.println();
    previousMillis = currentMillis;
    
  }

  if ( mypb.btnPressed() ) {   
    Serial.println("Button was pressed");
    mypb.restartFuelGauge();
    delay(250);
  }
  
}


