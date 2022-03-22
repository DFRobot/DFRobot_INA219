# DFRobot_INA219
- [中文版](./README_CN.md)

INA219 is a Gravity I2C digital power meter<br>
INA219 can measure the current, voltage and power of various electronic modules within 26V 8A with an accuracy higher than 0.2%.<br>
INA219 can be used for power measurement of solar system, battery coulomb meter or electronic module.<br>

![产品效果图片](../../resources/images/SEN0291.jpg)

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

This Sensor should work with INA219 on RaspberryPi.<br>
Run the program:
```
$> python DFRobot_INA219_test.py

```

## Methods

```Python

  def begin(self):
    '''!
      @fn begin
      @brief Initialize I2C bus and configure INA219 config register before reading data
      @return True (succeeded)/False (failed)
    '''
  
  def linear_cal(self, ina219_reading_mA, ext_meter_reading_mA):
      '''!
        @fn linear_cal
        @brief Linear calibration
        @param ina219_reading_mA    The current measured by INA219 (before calibration)
        @param ext_meter_reading_mA  Actual measured current
      '''
  
  def reset(self):
      '''!
        @fn reset
        @brief Reset config register
      '''

  def get_bus_voltage_V(self):
      '''!
        @fn get_bus_voltage_V
        @brief  get the BusVoltage （Voltage of IN- to GND)
        @return Voltage unit:V
      '''

  def get_shunt_voltage_mV(self):
      '''
        @fn get_shunt_voltage_mV
        @brief  get the ShuntVoltage （Voltage of the sampling resistor, IN+ to NI-)
        @return Voltage unit:mV
      '''

  def get_current_mA(self):
      '''
        @fn get_current_mA
        @brief get the Current(Current flows across IN+ and IN-.
        @n If the current flows from IN+ to IN-, the reading is positive. 
        @n If the current flows from IN- to IN+, the reading is negative)
        @return Current unit:mA
      '''

  def get_power_mW(self):
     '''
       @fn get_power_mW
       @brief  get the ShuntVoltage （Voltage of the sampling resistor, IN+ to NI-)
       @return Voltage unit:mV
     '''

  def set_bus_RNG(self, value):
      '''
        @fn set_bus_RNG
        @brief  Set BRNG (Bus Voltage Range)
        @param value     bus_vol_range_16V < 16V >
        @n               bus_vol_range_32V < 32V >
      '''

  def set_PGA(self, bits):
      '''
        @fn set_PGA
        @brief  Set PGA parameter (Shunt Voltage Only)
        @param bits          PGA_bits_1 <GAIN:1,Range ±40 mV>
        @n                   PGA_bits_2 <GAIN:/2,Range ±80 mV>
        @n                   PGA_bits_4 <GAIN:/4,Range ±160 mV> 
        @n                   PGA_bits_8 <GAIN:/8,Range ±320 mV> 
      '''

  def set_bus_ADC(self, bits, sample):
      '''!
        @fn set_bus_ADC
        @brief  Set BADC parameter (Bus ADC Resolution/Averaging)
        @param bits           Resolution
        @n                    adc_bits_9,
        @n                    adc_bits_10,
        @n                    adc_bits_11,
        @n                    adc_bits_12
        @param sample         Sample size
        @n                    adc_sample_1,
        @n                    adc_sample_2,
        @n                    adc_sample_4,
        @n                    adc_sample_8,
        @n                    adc_sample_16,
        @n                    adc_sample_32,
        @n                    adc_sample_64,
        @n                    adc_sample_128
      '''

  def set_shunt_ADC(self, bits, sample):
      '''!
        @fn set_shunt_ADC
        @brief  Set SADC parameter (Shunt ADC Resolution/Averaging)
        @param bits           Resolution
        @n                    adc_bits_9,
        @n                    adc_bits_10,
        @n                    adc_bits_11,
        @n                    adc_bits_12
        @param sample         Sample size
        @n                    adc_sample_1,
        @n                    adc_sample_2,
        @n                    adc_sample_4,
        @n                    adc_sample_8,
        @n                    adc_sample_16,
        @n                    adc_sample_32,
        @n                    adc_sample_64,
        @n                    adc_sample_128
      '''

  def set_mode(self, mode):
      '''
        @fn set_mode
        @brief  Set operation Mode
        @param mode  
        @n                power_down,   <Power-down> 
        @n                shunt_vol_trig,    <Shunt voltage, triggered> 
        @n                bus_vol_trig,    <Bus voltage, triggered>  
        @n                shunt_and_bus_vol_trig,<Shunt and bus, triggered>  
        @n                adc_off,      <ADC off (disabled)> 
        @n                shunt_vol_con,     <Shunt voltage, continuous>  
        @n                bus_vol_con,     <Bus voltage, continuous>  
        @n                shunt_and_bus_vol_con   <Shunt and bus, continuous> 
      '''

```


## Compatibility

| MCU         | Work Well | Work Wrong | Untested | Remarks |
| ------------ | :--: | :----: | :----: | :--: |
| RaspberryPi2 |      |        |   √    |      |
| RaspberryPi3 |      |        |   √    |      |
| RaspberryPi4 |  √   |        |        |      |

* Python Version

| Python  | Work Well | Work Wrong | Untested | Remarks |
| ------- | :--: | :----: | :----: | ---- |
| Python2 |  √   |        |        |      |
| Python3 |  √   |        |        |      |
## History

- 2022/3/1 - Version 1.0.0 released.

## Credits

Written by fengli(li.feng@dfrobot.com), 2022.3.1 (Welcome to our [website](https://www.dfrobot.com/))
