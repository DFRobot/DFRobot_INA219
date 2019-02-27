# INA219

INA219 is a Gravity I2C digital power meter<br>
INA219 can measure the current, voltage and power of various electronic modules within 26V 8A with an accuracy higher than 0.2%.<br>
INA219 can be used for power measurement of solar system, battery coulomb meter or electronic module.<br>

## DFRobot_INA219 Library for RaspberryPi
---------------------------------------------------------
Provide a Raspberry Pi library for the INA219 modules.

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

This Sensor should work with INA219 on RaspberryPi.<br>
Run the program:
```
$> python DFRobot_INA219_test.py

```

## Methods

```Python

'''
@brief Init The INA219

@param bus      I2C bus
       address  INA219_I2C_ADDRESS1
                INA219_I2C_ADDRESS2
                INA219_I2C_ADDRESS3
                INA219_I2C_ADDRESS4
'''
DFRobot_INA219(bus, addr)

'''
@brief Init The INA219

@return True If succeed
        False If failed
'''
def begin(self)

'''
@brief calibrate the current

@param ina219_reading_A can not be zero
'''
def linear_cal(self, ina219_reading_A, extMeter_reading_A)
'''
@brief ina219 reset

@param rst    1
'''
def reset(self)

'''
@brief  Get the shunt voltage in volts

@return The bus voltage converted into volts
'''
def get_bus_voltage_V(self)

''' 
@brief  Get the shunt voltage in mV

@return The shunt voltage converted into millivolts
'''
def get_shunt_voltage_mV(self)

'''
 @brief  Get the current value in mA, taking into account the
         config settings and current LSB

 @return Current reading convereted into milliamps
'''
def get_current_mA(self)

'''
 @brief  Get the power value in mW, taking into account the
         config settings and power LSB

 @return Power reading converted into milliwatts
'''
def get_power_mW(self)

'''
@brief Bus voltage range setting

@param value : bus_vol_range_16V
               bus_vol_range_32V
'''
def set_bus_RNG(self, value)

'''
@brief PGA gain and range setting

@param bits : PGA_bits_1
              PGA_bits_2
              PGA_bits_4
              PGA_bits_8
'''
def set_PGA(self, bits)

'''
@brief Bus and shunt ADC resolution setting

@param bits: adc_bits_9 
             adc_bits_10
             adc_bits_11
             adc_bits_12
       
@param sample: adc_sample_1
               adc_sample_2
               adc_sample_4
               adc_sample_8
               adc_sample_16
               adc_sample_32
               adc_sample_64
               adc_sample_128
'''
def set_bus_ADC(self, bits, sample)
def set_shunt_ADC(self, bits, sample)

'''
@brief Operating mode setting

@param mode : power_down
              shunt_vol_trig
              bus_vol_trig
              shunt_and_bus_vol_trig
              adc_off
              shunt_vol_con
              bus_vol_con
              shunt_and_bus_vol_con
'''
def set_shunt_ADC(self, mode)

```


## Credits

·author [luoyufeng yufeng.luo@dfrobot.com]
