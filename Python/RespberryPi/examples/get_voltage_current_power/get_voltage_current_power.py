# -*- coding: utf-8 -*-

'''!
  @file getVoltageCurrentPower.py
  @brief Get the current, voltage, and power of electronic devices.
  @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license     The MIT license (MIT)
  @author [fengli](li.feng@dfrobot.com)
  @version  V1.0
  @date  2022-3-1
  @url https://github.com/DFRobot/DFRobot_INA219
'''
import sys
import time
sys.path.append("../..")
from DFRobot_INA219 import INA219

ina219_reading_mA = 1000
ext_meter_reading_mA = 1000

ina = INA219(1, INA219.INA219_I2C_ADDRESS4)                                #Change I2C address by dialing DIP switch

#begin return True if succeed, otherwise return False
while not ina.begin():
    time.sleep(2)
'''
Revise the following two paramters according to actual reading of the INA219 and the multimeter
for linearly calibration
'''

ina.linear_cal(ina219_reading_mA, ext_meter_reading_mA)


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
