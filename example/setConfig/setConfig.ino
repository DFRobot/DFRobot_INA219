
/*!
   file getVoltageCurrentPower.ino
   SEN0291 Gravity: I2C Digital Wattmeter
   The module is connected in series between the power supply and the load to read the voltage, current and power
   The module has four I2C, these addresses are:
   INA219_I2C_ADDRESS1  0x40   A0 = 0  A1 = 0
   INA219_I2C_ADDRESS2  0x41   A0 = 1  A1 = 0
   INA219_I2C_ADDRESS3  0x44   A0 = 0  A1 = 1
   INA219_I2C_ADDRESS4  0x45   A0 = 1  A1 = 1
   
   eIna219BusVolRange_t         = eIna219BusVolRange_16V
                                  eIna219BusVolRange_32V
   
   eIna219BusVolRange_t         = eIna219PGABits_1
                                  eIna219PGABits_2
                                  eIna219PGABits_4
                                  eIna219PGABits_8

   eIna219BusVolRange_t         = eIna219AdcBits_9
                                  eIna219AdcBits_10
                                  eIna219AdcBits_11
                                  eIna219AdcBits_12
   
   eIna219BusVolRange_t         = eIna219AdcSample_1
                                  eIna219AdcSample_2
                                  eIna219AdcSample_4
                                  eIna219AdcSample_8
                                  eIna219AdcSample_16
                                  eIna219AdcSample_32
                                  eIna219AdcSample_64
                                  eIna219AdcSample_128
   
   eIna219BusVolRange_t         = eIna219PowerDown
                                  eIna219SVolTrig
                                  eIna219BVolTrig
                                  eIna219SAndBVolTrig
                                  eIna219AdcOff
                                  eIna219SVolCon
                                  eIna219BVolCon
                                  eIna219SAndBVolCon

   Copyright    [DFRobot](http://www.dfrobot.com), 2016
   Copyright    GNU Lesser General Public License
   version  V0.1
   date  2019-2-27
*/

#include <Wire.h>
#include "DFRobot_INA219.h"

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
    ina219.setBRNG(eIna219BusVolRange_32V);
    ina219.setPGA(eIna219PGABits_1);
    ina219.setBADC(eIna219AdcBits_12, eIna219AdcSample_8);
    ina219.setSADC(eIna219AdcBits_12, eIna219AdcSample_8);
    ina219.setMode(eIna219SAndBVolCon);
    Serial.println("");
    //ina219.reset();
    
    
}

void loop(void) 
{

}
