# DFRobot_INA219
- [中文版](./README_CN.md)

INA219 is a Gravity I2C digital power meter<br>
INA219 can measure current, voltage and power of various electronic modules within 26V 8A with an accuracy higher than 0.2%.<br>
INA219 can be used for power measurement of solar system, battery coulomb counter or electronic module.<br>

![产品效果图片](./resources/images/SEN0291.jpg)

## Product Link（https://www.dfrobot.com/product-1827.html）

    SEN0291：I2C Digital Wattmeter
	
## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [Credits](#credits)


## Summary
The voltage, current, power and voltage at both ends of the sampling resistance of INA219 can be read through I2C.
These data are printed out through the serial port.


## Installation

To use this library, please download the library file first, and paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.<br>

## Methods

```C++

    /**
     * @fn begin
     * @brief Initialize I2C bus and configure INA219 config register before reading data
     * @return true (succeeded)/false (failed)
     */
    bool begin();

    /**
     * @fn linearCalibrate
     * @brief Linear calibration
     * @param ina219Reading_mA    The current measured by INA219 (before calibration)
     * @param extMeterReading_mA  Actual measured current
     */
    void linearCalibrate(float ina219Reading_mA, float extMeterReading_mA),
 
    /**
     * @fn reset
     * @brief Reset config register
     */
    void reset();

    /**
     * @fn getBusVoltage_V
     * @brief  get the BusVoltage （Voltage of IN- to GND)
     * @return Voltage unit:V
     */
    float getBusVoltage_V();

    /**
     * @fn getShuntVoltage_mV
     * @brief  get the ShuntVoltage （Voltage of the sampling resistor, IN+ to NI-)
     * @return Voltage unit:mV
     */
    float getShuntVoltage_mV();
    
    /**
     * @fn getCurrent_mA
     * @brief get the Current(Current flows across IN+ and IN-.
     * @n If the current flows from IN+ to IN-, the reading is positive. 
     * @n If the current flows from IN- to IN+, the reading is negative)
     * @return Current unit:mA
     */
    float getCurrent_mA();
    
    /**
     * @fn getPower_mW
     * @brief Get power
     * @details the power resolution read directly from the module is 20mW 
     * @n (hardware mode). If the power is obtained by using the statement 
     * @n "Power = BusVoltage*Current;", the resolution can be increased to 4mW 
     * @n (software mode).
     * @return power unit：mW
     */
    float getPower_mW();

    /**
     * @fn setBRNG
     * @brief  Set BRNG (Bus Voltage Range)
     * @param value     eIna219BusVolRange_16V < 16V >
     * @n               eIna219BusVolRange_32V < 32V >
     */
    void  setBRNG(eIna219BusVolRange_t value);
 
    /**
     * @fn setPGA
     * @brief  Set PGA parameter (Shunt Voltage Only)
     * @param bits          eIna219PGABits_1 <GAIN:1,Range ±40 mV>
     * @n                   eIna219PGABits_2 <GAIN:/2,Range ±80 mV>
     * @n                   eIna219PGABits_4 <GAIN:/4,Range ±160 mV> 
     * @n                   eIna219PGABits_8 <GAIN:/8,Range ±320 mV> 
     */
    void  setPGA(eIna219PGABits_t bits);
 
    /**
     * @fn setBADC
     * @brief  Set BADC parameter (Bus ADC Resolution/Averaging)
     * @param bits           Resolution
     * @n                    eIna219AdcBits_9,
     * @n                    eIna219AdcBits_10,
     * @n                    eIna219AdcBits_11,
     * @n                    eIna219AdcBits_12
     * @param sample         Sample size
     * @n                    eIna219AdcSample_1,
     * @n                    eIna219AdcSample_2,
     * @n                    eIna219AdcSample_4,
     * @n                    eIna219AdcSample_8,
     * @n                    eIna219AdcSample_16,
     * @n                    eIna219AdcSample_32,
     * @n                    eIna219AdcSample_64,
     * @n                    eIna219AdcSample_128
     */
    void  setBADC(eIna219AdcBits_t bits, eIna219AdcSample_t sample);

    /**
     * @fn setSADC
     * @brief  Set SADC parameter (Shunt ADC Resolution/Averaging)
     * @param bits           Resolution
     * @n                    eIna219AdcBits_9,
     * @n                    eIna219AdcBits_10,
     * @n                    eIna219AdcBits_11,
     * @n                    eIna219AdcBits_12
     * @param sample         Sample size
     * @n                    eIna219AdcSample_1,
     * @n                    eIna219AdcSample_2,
     * @n                    eIna219AdcSample_4,
     * @n                    eIna219AdcSample_8,
     * @n                    eIna219AdcSample_16,
     * @n                    eIna219AdcSample_32,
     * @n                    eIna219AdcSample_64,
     * @n                    eIna219AdcSample_128
     */
    void  setSADC(eIna219AdcBits_t bits, eIna219AdcSample_t sample);

    /**
     * @fn setMode
     * @brief  Set operation Mode
     * @param mode  
     * @n                eIna219PowerDown,   <Power-down> 
     * @n                eIna219SVolTrig,    <Shunt voltage, triggered> 
     * @n                eIna219BVolTrig,    <Bus voltage, triggered>  
     * @n                eIna219SAndBVolTrig,<Shunt and bus, triggered>  
     * @n                eIna219AdcOff,      <ADC off (disabled)> 
     * @n                eIna219SVolCon,     <Shunt voltage, continuous>  
     * @n                eIna219BVolCon,     <Bus voltage, continuous>  
     * @n                eIna219SAndBVolCon  <Shunt and bus, continuous> 
     */
    void  setMode(eInaMode_t mode);

```



## Compatibility

MCU                | Work Well | Work Wrong | Untested  | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino uno |       √      |             |            | 
RaspberryPi |       √      |             |            | 


## History

- 2022/3/1 - Version 1.0.0 released.

## Credits

Written by fengli(li.feng@dfrobot.com), 2022.3.1 (Welcome to our [website](https://www.dfrobot.com/))
