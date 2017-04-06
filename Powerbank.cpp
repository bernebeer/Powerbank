/* My comments */

#include "Powerbank.h"
#include <Wire.h>

// Powerbank object
Powerbank::Powerbank() {

}

void Powerbank::init(unsigned int fast_chrg_current, unsigned int input_current) {
  Wire.begin();
  // Set ADC refrence to Internal
  analogReference(INTERNAL);
  // Reset registers
  writeReg8(BQ25895_ADDRESS, BQ25895_REG_RESET, B10111001);
  // Init ADC, force D+ D- detection
  writeReg8(BQ25895_ADDRESS, BQ25895_REG_ADC_DATALINE_CONFIG, B11111101);
  // Set minimum system voltage to 3.7v  
  writeReg8(BQ25895_ADDRESS, BQ25895_REG_WD_CE_SYSVOLT_CONFIG, B01111110);
  // Disable enter ship mode delay
  writeReg8(BQ25895_ADDRESS, BQ25895_REG_BATFET_CONFIG, B01000000);
  // Set fast charge current limit
  byte data = 0;
  if( fast_chrg_current < 5000 ) {
    data = fast_chrg_current / 64;
  }
  else {
    data = 1000 / 64;
  }
  writeReg8(BQ25895_ADDRESS, BQ25895_REG_CHRG_CURRENT_CONFIG, data);
  // Set input current limit
  data = B00111111 & ((input_current / 50) - 100);
  writeReg8(BQ25895_ADDRESS, BQ25895_REG_INP_LIM, data);
}

void Powerbank::resetWatchdog() {
  writeReg8(BQ25895_ADDRESS, BQ25895_REG_WD_CE_SYSVOLT_CONFIG, B01111110);
}

int Powerbank::getChargeCurrent() {
  byte data = readReg8(BQ25895_ADDRESS, BQ25895_REG_ADC_CHRG_CURRENT);
  return (data * 50);
}

int Powerbank::getBatteryLevel() {
  byte data = readReg8(MAX17043_ADDRESS, MAX17043_REG_SOC);
  return data;
}

unsigned int Powerbank::getSysVoltage() {
  byte data = readReg8(BQ25895_ADDRESS, BQ25895_REG_ADC_SYS_VOLT);
  unsigned int sysVoltage = ((data * 20) + 2304);
  return sysVoltage;
}

unsigned int Powerbank::getVbusVoltage() {
  byte data = readReg8(BQ25895_ADDRESS, BQ25895_REG_ADC_VBUS_VOLT);
  unsigned int vbusVoltage = ( data & B01111111 ) * 100 + 2600;
  if ( (data & B10000000) >> 7 ) {
    return vbusVoltage;
  }
  else {
    return 0;
  }
}

unsigned long Powerbank::getBatteryVoltage() {
  byte dataMSB = readReg8(MAX17043_ADDRESS, MAX17043_REG_VCELL);
  byte dataLSB = readReg8(MAX17043_ADDRESS, MAX17043_REG_VCELL + 1 );
  unsigned long data = word( dataMSB, dataLSB );
  data = ( data >> 4 ) * 125 / 100;
  return data;
}

float Powerbank::getOutputCurrent() {
  float data = ( 1100.0 / 1024.0 * analogRead(CCPIN) ) / 33000.0 * 100000.0;
  return data;
}

boolean Powerbank::isCharging() {
  byte data = readReg8(BQ25895_ADDRESS, BQ25895_REG_VBUS_CHRG_STAT);
  boolean charging;
  if ( ( (data & B11100000) >> 5 ) > 0 ) {
    charging = true;
  }
  else {
    charging = false;
  }
  return charging;  
}

void Powerbank::batfetDisable() {
  writeReg8(BQ25895_ADDRESS, BQ25895_REG_BATFET_CONFIG, B01100000);  
}

boolean Powerbank::isBatfetDisabled() {
  byte data = readReg8(BQ25895_ADDRESS, BQ25895_REG_BATFET_CONFIG);
  if ( (data & B00100000) >> 5 ) {
    return true;
  }
  else {
    return false;
  }
}

void Powerbank::batfetEnable() {
  writeReg8(BQ25895_ADDRESS, BQ25895_REG_BATFET_CONFIG, B01000000);
}

boolean Powerbank::btnPressed() {
  boolean data;
  if ( digitalRead(BTNPIN) == LOW ) {
    data = true;
  }
  else {
    data = false;
  }
  return data;
}

byte Powerbank::vbusInputType() {
  byte data = readReg8(BQ25895_ADDRESS, BQ25895_REG_VBUS_CHRG_STAT);
  data = (data & B11100000) >> 5;
  return data;
}

void Powerbank::restartFuelGauge() {
  writeReg16(MAX17043_ADDRESS, MAX17043_REG_MODE, 0x4000);
}

byte Powerbank::readReg8(int deviceAddress, int regAddress) {
  byte data = 0;
  Wire.beginTransmission(deviceAddress);
  Wire.write(regAddress);
  Wire.endTransmission();
  Wire.requestFrom(deviceAddress, 1);
  data = Wire.read();
  return(data);
}

void Powerbank::writeReg8(int deviceAddress, int regAddress, byte data) {
  Wire.beginTransmission(deviceAddress);
  Wire.write(regAddress);
  Wire.write(data);
  Wire.endTransmission();
}

void Powerbank::writeReg16(int deviceAddress, int regAddress, word data) {
  Wire.beginTransmission(deviceAddress);
  Wire.write(regAddress);
  Wire.write(highByte(data));
  Wire.write(lowByte(data));
  Wire.endTransmission();
}



