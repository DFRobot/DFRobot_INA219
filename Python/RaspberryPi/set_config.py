# -*- coding: utf-8 -*-

'''
file set_config.py
SEN0291 Wattmeter Sensor
This sensor can detect Voltage ,Current,and Power
This demo is used to change configuration mode
The module has four I2C, these addresses are:

ADDRESS 1  0x40   A0 = 0  A1 = 0
ADDRESS 2  0x41   A0 = 1  A1 = 0
ADDRESS 3  0x44   A0 = 0  A1 = 1
ADDRESS 4  0x45   A0 = 1  A1 = 1

set_bus_RNG
value                = bus_vol_range_16V
                       bus_vol_range_32V
                       
set_PGA
bits                 = PGA_bits_1
                       PGA_bits_2
                       PGA_bits_4
                       PGA_bits_8
                       
set_bus_ADC
set_shunt_ADC
bits                 = adc_bits_9
                       adc_bits_10
                       adc_bits_11
                       adc_bits_12
                       
sample               = adc_sample_1
                       adc_sample_2
                       adc_sample_4
                       adc_sample_8
                       adc_sample_16
                       adc_sample_32
                       adc_sample_64
                       adc_sample_128
set_mode
mode                 = power_dow
                       shunt_vol_trig
                       bus_vol_trig
                       shunt_and_bus_vol_trig
                       adc_off
                       shunt_vol_con 
                       bus_vol_con
                       shunt_and_bus_vol_con
                       
Copyright    [DFRobot](http://www.dfrobot.com), 2016
Copyright    GNU Lesser General Public License
version  V1.0
date  2019-2-27
'''

import time
from DFRobot_INA219 import INA219

ina219_reading_mA = 1000
ext_meter_reading_mA = 1000

ina = INA219(1, INA219.INA219_I2C_ADDRESS4)                                #Change I2C address by dialing DIP switch

#begin return True if succeed, otherwise return False
while not ina.begin():
    time.sleep(2)
'''
Revise the following two paramters according to actula reading of the INA219 and the multimeter
for linearly calibration
'''


ina.set_bus_RNG(ina.bus_vol_range_32V)
ina.set_PGA(ina.PGA_bits_8)
ina.set_bus_ADC(ina.adc_bits_12, ina.adc_sample_8)
ina.set_shunt_ADC(ina.adc_bits_12, ina.adc_sample_8)
ina.set_mode(ina.shunt_and_bus_vol_con)

#ina.reset()                                     #Resets all registers to default values

def main():
    while True:
        time.sleep(1)
        print ("Shunt Voltage : %.2f mV" % ina.get_shunt_voltage_mV())
        print ("Bus Voltage   : %.3f V" % ina.get_bus_voltage_V())
        print ("Current       : %.f mA" % ina.get_current_mA())
        print ("Power         : %.f mW" % ina.get_power_mW())
        print (" ")

if __name__ == "__main__":
    main()
