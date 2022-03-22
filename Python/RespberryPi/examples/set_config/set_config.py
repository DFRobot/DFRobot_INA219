# -*- coding: utf-8 -*-

'''
 *@file setConfig.py
 *@brief How to configure parameters of the config register
 *@copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 *@license     The MIT license (MIT)
 *@author [fengli](li.feng@dfrobot.com)
 *@version  V1.0
 *@date  2022-3-1
 *@url https://github.com/DFRobot/DFRobot_INA219
'''
import sys
import time
sys.path.append("../..")
from DFRobot_INA219 import INA219

ina219_reading_mA = 1000
ext_meter_reading_mA = 1000

'''
  @param i2caddr  I2C address
  @n INA219_I2C_ADDRESS1  0x40   A0 = 0  A1 = 0
  @n INA219_I2C_ADDRESS2  0x41   A0 = 1  A1 = 0
  @n INA219_I2C_ADDRESS3  0x44   A0 = 0  A1 = 1
  @n INA219_I2C_ADDRESS4  0x45   A0 = 1  A1 = 1	 
'''
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
