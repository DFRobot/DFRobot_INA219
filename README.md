# INA219

INA219 is a Gravity I2C digital power meter<br>
INA219 can measure current, voltage and power of various electronic modules within 26V 8A with an accuracy higher than 0.2%.<br>
INA219 can be used for power measurement of solar system, battery coulomb counter or electronic module.<br>

## DFRobot_INA219 Library for Arduino
---------------------------------------------------------
Provide an Arduino library for the INA219 modules.

## Table of Contents

* [Summary](#summary)
* [Feature](#feature)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [Credits](#credits)
<snippet>
<content>

## Summary
The voltage, current, power and voltage at both ends of the sampling resistance of INA219 can be read through I2C.
These data are printed out through the serial port.

## Feature
1. Low standby current
2. Serial input via I2C-bus
3. Configurable sample rate
4. I2C address can be modified by revising the macro definition
5. Maximum measurement range up to 26V 8A

## Installation

Download the library ZIP file and unzip it to the Arduino folder of the library.<br>

## Methods

```C++

#include "DFRobot_INA219.h"

/*!
 * @brief Set IIC address by setting the hardware
 *
 * @param IIC Address setting
 *      addr = INA219_I2C_ADDRESS1  0x40
 *             INA219_I2C_ADDRESS2  0x41
 *             INA219_I2C_ADDRESS3  0x44
 *             INA219_I2C_ADDRESS4  0x45
 */
DFRobot_INA219_IIC(TwoWire *pWire, uint8_t i2cAddr);

/* 
 * @brief ina219 begin
 *
 * @return begin return true if succeed, otherwise return false
 */
bool begin();

/*
 * @brief calibrate the current
 *
 * @param ina219Reading_A can not be zero
 */
void linearCalibrate(float ina219Reading_mA, float extMeterReading_mA);

/* 
 * @brief ina219 reset
 */
void reset();

/*
 * @brief  Get the shunt voltage in volts
 *
 * @return The bus voltage converted into volts
 */
float getBusVoltage_V();

/*
 * @brief  Get the shunt voltage in mV
 *
 * @return The shunt voltage converted into millivolts
 */
float getShuntVoltage_mV();

/*
 * @brief  Get the current value in mA, taking into account the
 *         config settings and current LSB
 *
 * @return The current reading convereted to milliamps
 */
float getCurrent_mA();

/*
 * @brief  Get the power value in mW, taking into account the
 *         config settings and power LSB
 *
 * @return Power reading converted to milliwatts
 */
float getPower_mW();

/*
 * @brief Bus voltage range setting
 *
 * @param typedef enum {eIna219BusVolRange_16V,
 *                      eIna219BusVolRange_32V
 *                      } eIna219BusVolRange_t;
 */
void setBRNG(eIna219BusVolRange_t value);

/*
 * @brief PGA gain and range setting
 *
 * @param typedef enum {eIna219PGABits_1,
 *                      eIna219PGABits_2,
 *                      eIna219PGABits_4,
 *                      eIna219PGABits_8
 *                      } eIna219PGABits_t;
 */
void setPGA(eIna219PGABits_t bits);

/*
 * @brief Bus ADC resolution setting
 *
 * @param typedef enum {eIna219AdcBits_9, 
 *                      eIna219AdcBits_10,
 *                      eIna219AdcBits_11,
 *                      eIna219AdcBits_12
 *                      } eIna219AdcBits_t;
 *
 * @param typedef enum {eIna219AdcSample_1,
 *                      eIna219AdcSample_2,
 *                      eIna219AdcSample_4,
 *                      eIna219AdcSample_8,
 *                      eIna219AdcSample_16,
 *                      eIna219AdcSample_32,
 *                      eIna219AdcSample_64,
 *                      eIna219AdcSample_128
 *                      } eIna219AdcSample_t;
 *
 * if eIna219AdcSample_t >= 1, eIna219AdcBits_t must be "eIna219AdcBits_12"
 */
void setBADC(eIna219AdcBits_t bits, eIna219AdcSample_t sample);
void setSADC(eIna219AdcBits_t bits, eIna219AdcSample_t sample);

/*
 * @brief Operating mode setting
 *
 * @param typedef enum{eIna219PowerDown,
 *                     eIna219SVolTrig,
 *                     eIna219BVolTrig,
 *                     eIna219SAndBVolTrig,
 *                     eIna219AdcOff,
 *                     eIna219SVolCon,
 *                     eIna219BVolCon,
 *                     eIna219SAndBVolCon
 *                     } eInaMode;
 */
void setMode(eInaMode mode);

```



## Compatibility

MCU                | Work Well | Work Wrong | Untested  | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino uno |       √      |             |            | 
RaspberryPi |       √      |             |            | 


## Credits

·author [luoyufeng yufeng.luo@dfrobot.com]
