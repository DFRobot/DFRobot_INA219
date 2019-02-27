# -*- coding: utf-8 -*-

'''
file getVoltageCurrentPower.py
SEN0291 Wattmeter Sensor
This sensor can detect Voltage ,Current,and Power
This demo is used to change configuration mode
The module has four I2C, these addresses are:

_I2C_ADDRESS 1  0x40   A0 = 0  A1 = 0
_I2C_ADDRESS 2  0x41   A0 = 1  A1 = 0
_I2C_ADDRESS 3  0x44   A0 = 0  A1 = 1
_I2C_ADDRESS 4  0x45   A0 = 1  A1 = 1

Copyright    [DFRobot](http://www.dfrobot.com), 2018
Copyright    GNU Lesser General Public License
version  V1.0
date  2018-12-11
'''

import time
import sys
sys.path.append('../')
from DFRobot_INA219 import INA219

ina219Reading_mA = 1000
extMeterReading_mA = 1000

ina = INA219(1, _INA219_I2C_ADDRESS4)                                #Change I2C address by dialing DIP switch

#begin return True if succeed, otherwise return False
while not ina.begin():
    time.sleep(2)
'''
Revise the following two paramters according to actula reading of the INA219 and the multimeter
for linearly calibration
'''


ina.setBRNG(Ina219BusVolRange_32V)
ina.setPGA(Ina219PGA_8)
ina.setBADC(Ina219Badc_9)
ina.setSADC(Ina219Sadc_32)
ina.setMode(eIna219SAndBVolCon)

#ina.reset()                                     #Resets all registers to default values

def main():
    while True:
        time.sleep(1)
        print ("Shunt Voltage : %.2f mV" % ina.getShuntVoltage_mV())
        print ("Bus Voltage   : %.3f V" % ina.getBusVoltage_V())
        print ("Current       : %.f mA" % ina.getCurrent_mA())
        print ("Power         : %.f mW" % ina.getPower_mW())
        print (" ")

if __name__ == "__main__":
    main()
