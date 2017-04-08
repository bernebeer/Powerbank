#include "Powerbank.h"
#include <Wire.h>

#define MAX_FASTCHARGE_CURRENT  2000
#define MAX_INPUT_CURRENT       3000

// Instantiate Powerbank object, name it anything, in this case 'mypb'
Powerbank mypb;

unsigned long previousMillis = 0;

void setup() {
  
  Serial.begin(115200);
  mypb.init(MAX_FASTCHARGE_CURRENT, MAX_INPUT_CURRENT);

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
    Serial.print("Vbus input type: \t");
    Serial.print( mypb.vbusInputType() );
    Serial.println("\t 0 = No input, 2 = USB CDP (1.5A), 3 = USB DCP (3.25A), 4 = Adj. Hi-V. DCP (1.5A), 5 = Unk. Adap., 6 = Non Std. Adap.");
    
    Serial.print("Vbus voltage: \t\t");
    Serial.print( mypb.getVbusVoltage() );
    Serial.println("mV");
    
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
    
    Serial.print("System voltage: \t");
    Serial.print( mypb.getSysVoltage() );
    Serial.println("mV");
    
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
    mypb.sleepBtnWake();    
  }
  
}

