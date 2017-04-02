#include "Powerbank.h"
#include <Wire.h>

Powerbank::Powerbank() {
  // Anything you need when instantiating your object goes here
}

void Powerbank::begin() {
  Wire.begin();
  // Reset registers
  writeReg8(BQ25895_ADDRESS, BQ25895_REG_RESET, B10111001);
  // Init ADC, force D+ D- detection
  writeReg8(BQ25895_ADDRESS, BQ25895_REG_ADC_DATALINE_CONFIG, B11111101);
  // Set minimum system voltage to 3.7v  
  writeReg8(BQ25895_ADDRESS, BQ25895_REG_WD_CE_SYSVOLT_CONFIG, B01111110);
  // Disable enter ship mode delay
  writeReg8(BQ25895_ADDRESS, BQ25895_REG_BATFET_CONFIG, B01001000);
  // Set fast charge current limit
  writeReg8(BQ25895, 0x04, B00100010);
}

int Powerbank::chargeCurrent() {
  byte data = readReg8(BQ25895_ADDRESS, BQ25895_REG_ADC_CHRG_CURRENT);
  return (data * 50);
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



