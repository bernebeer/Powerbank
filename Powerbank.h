/* My comments */
#ifndef powerbank
#define powerbank

#if (ARDUINO >=100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define BQ25895_ADDRESS 0x6a
#define MAX17043_ADDRESS 0x36

#define BQ25895_REG_INP_LIM 0x00
#define BQ25895_REG_ADC_DATALINE_CONFIG 0x02
#define BQ25895_REG_WD_CE_SYSVOLT_CONFIG 0x03
#define BQ25895_REG_CHRG_CURRENT_CONFIG 0x04
#define BQ25895_REG_BATFET_CONFIG 0x09
#define BQ25895_REG_ADC_CHRG_CURRENT 0x12
#define BQ25895_REG_RESET 0x14

class Powerbank  {
  
  public:
    // Constructor
    Powerbank();
    // Methods
    void begin();
    void keepAlive();
    int chargeCurrent();

  private:    
    byte readReg8(int deviceAddress, int regAddress);
    void writeReg8(int deviceAddress, int regAddress, byte data);
    
};

#endif
