/* My comments */

#ifndef powerbank

#define powerbank

#if (ARDUINO >=100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define CCPIN                             A0
#define BTNPIN                            3

#define BQ25895_ADDRESS                   0x6a
#define MAX17043_ADDRESS                  0x36

#define BQ25895_REG_INP_LIM               0x00
#define BQ25895_REG_ADC_DATALINE_CONFIG   0x02
#define BQ25895_REG_WD_CE_SYSVOLT_CONFIG  0x03
#define BQ25895_REG_CHRG_CURRENT_CONFIG   0x04
#define BQ25895_REG_BATFET_CONFIG         0x09
#define BQ25895_REG_ADC_CHRG_CURRENT      0x12
#define BQ25895_REG_RESET                 0x14
#define BQ25895_REG_VBUS_CHRG_STAT        0x0b

#define MAX17043_REG_VCELL                0x02
#define MAX17043_REG_SOC                  0x04

class Powerbank  {
  
  public:
    // Constructor
    Powerbank();
    // Methods
    void begin();
    void resetWatchdog();
    int getChargeCurrent();
    int getBatteryLevel();
    float getOutputCurrent();
    unsigned long getBatteryVoltage();
    boolean isCharging();
    void sleepPower();
    void sleepMicro();
    boolean btnPressed();

  private:
    byte readReg8(int deviceAddress, int regAddress);
    void writeReg8(int deviceAddress, int regAddress, byte data);
    
}; // End class constructor in semi-colon...

#endif
