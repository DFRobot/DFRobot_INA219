
/*!
   file getVoltageCurrentPower.ino
   SEN0291 Gravity: I2C Digital Wattmeter
   The module is connected in series between the power supply and the load to read the voltage, current and power
   The module has four I2C, these addresses are:
   INA219_I2C_ADDRESS1  0x40   A0 = 0  A1 = 0
   INA219_I2C_ADDRESS2  0x41   A0 = 1  A1 = 0
   INA219_I2C_ADDRESS3  0x44   A0 = 0  A1 = 1
   INA219_I2C_ADDRESS4  0x45   A0 = 1  A1 = 1
  
   Copyright    [DFRobot](http://www.dfrobot.com), 2018
   Copyright    GNU Lesser General Public License
   version  V0.1
   date  2018-12-13
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
    
    
}

void loop(void) 
{

}
