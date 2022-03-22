
/*!
 *@file setConfig.ino
 *@brief How to configure parameters of the config register
 *@copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 *@license     The MIT license (MIT)
 *@author [fengli](li.feng@dfrobot.com)
 *@version  V1.0
 *@date  2022-3-1
 *@url https://github.com/DFRobot/DFRobot_INA219
*/
#include <Wire.h>
#include "DFRobot_INA219.h"

/**
 * @fn DFRobot_INA219_IIC
 * @brief pWire I2C controller pointer
 * @param i2caddr  I2C address
 * @n INA219_I2C_ADDRESS1  0x40   A0 = 0  A1 = 0
 * @n INA219_I2C_ADDRESS2  0x41   A0 = 1  A1 = 0
 * @n INA219_I2C_ADDRESS3  0x44   A0 = 0  A1 = 1
 * @n INA219_I2C_ADDRESS4  0x45   A0 = 1  A1 = 1	 
  */
DFRobot_INA219_IIC     ina219(&Wire, INA219_I2C_ADDRESS4);

void setup(void) 
{
    Serial.begin(115200);
    while(!Serial);
    
    Serial.println();
    while(ina219.begin() != true) {
        Serial.println("INA219 begin faild");
        delay(2000);
    }
	//Set BRNG (Bus Voltage Range)
    ina219.setBRNG(ina219.eIna219BusVolRange_32V);
	//Set PGA parameter(Shunt Voltage Only)
    ina219.setPGA(ina219.eIna219PGABits_1);
    //Set BADC parameter (Bus ADC Resolution/Averaging)
	ina219.setBADC(ina219.eIna219AdcBits_12, ina219.eIna219AdcSample_8);
    //Set SADC parameter (Shunt ADC Resolution/Averaging)
	ina219.setSADC(ina219.eIna219AdcBits_12, ina219.eIna219AdcSample_8);
	//Set operation Mode(Bus Voltage Range)
    ina219.setMode(ina219.eIna219SAndBVolCon);
    Serial.println("");
    //ina219.reset();
}

void loop(void) 
{

}
