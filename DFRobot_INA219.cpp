/*!
 * @file DFRobot_INA219.cpp
 * @brief Define the infrastructure of the DFRobot_INA219 class
 * @details The library is used to drive INA219 chip, which can detect the voltage, current and power of various electronic devices.
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @License     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2022-03-1
 * @url https://github.com/DFRobot/DFRobot_INA219
 */


#include <Arduino.h>
#include <Wire.h>
#include <DFRobot_INA219.h>

bool DFRobot_INA219::begin()
{
    lastOperateStatus = eIna219_InitError;
    Wire.begin();
    if (scan() == true)
    {
        setBRNG(eIna219BusVolRange_32V);
        setPGA(eIna219PGABits_8);
        setBADC(eIna219AdcBits_12, eIna219AdcSample_8);
        setSADC(eIna219AdcBits_12, eIna219AdcSample_8);
        setMode(eIna219SAndBVolCon);
        calValue = 4096;
        writeInaReg(INA219_REG_CALIBRATION, calValue);
        lastOperateStatus = eIna219_ok;
        return true;
    }
    else{
        return false;
    }
}


void DFRobot_INA219::linearCalibrate(float ina219Reading_mA, float extMeterReading_mA)
{
    calValue = (uint16_t)((extMeterReading_mA / ina219Reading_mA) * calValue) & 0xFFFE;
    writeInaReg(INA219_REG_CALIBRATION, calValue);
}

float DFRobot_INA219::getBusVoltage_V()
{
    return (float) (readInaReg(INA219_REG_BUSVOLTAGE) >> 1) * 0.001;
}

float DFRobot_INA219::getShuntVoltage_mV()
{
    return (float) readInaReg(INA219_REG_SHUNTVOLTAGE) * 0.01;
}

float DFRobot_INA219::getCurrent_mA()
{
    return (float) readInaReg(INA219_REG_CURRENT);
}

float DFRobot_INA219::getPower_mW()
{
    return (float) readInaReg(INA219_REG_POWER) * 20;
}
/*Sets Bus Voltage Range(default value is 32V)*/
void DFRobot_INA219::setBRNG(eIna219BusVolRange_t value)/**/
{
    int16_t    conf;
    conf = readInaReg(INA219_REG_CONFIG);
    conf &= ~((uint16_t) 1 << 13);
    conf |= (uint16_t) value << 13;
    writeInaReg(INA219_REG_CONFIG, conf);
}
/*Sets PGA gain and range(default value is 320mV)*/
void DFRobot_INA219::setPGA(eIna219PGABits_t bits)//Sets PGA gain and range(default value is 320mV)
{
    int16_t    conf;
    conf = readInaReg(INA219_REG_CONFIG);
    conf &= ~((uint16_t) 0x03 << 11);
    conf |= (uint16_t) bits << 11;
    writeInaReg(INA219_REG_CONFIG, conf);
}
/*
 *These bits adjust the Bus ADC resolution (9-, 10-, 11-, or 12-bit) 
 *or set the number of samples used when averaging results for the Bus Voltage Register
 */
void DFRobot_INA219::setBADC(eIna219AdcBits_t bits, eIna219AdcSample_t sample)
{
    int16_t    conf;
    int16_t    value = 0;
    if(bits < eIna219AdcBits_12 && sample > eIna219AdcSample_1)
       return;
    if(bits < eIna219AdcBits_12)
        value = bits;
    else
        value = 0x08 | sample;
    conf = readInaReg(INA219_REG_CONFIG);
    conf &= ~((uint16_t) 0x0f << 7);
    conf |= (uint16_t) value << 7;
    writeInaReg(INA219_REG_CONFIG, conf);
}
/*
 *These bits adjust the Shunt ADC resolution (9-, 10-, 11-, or 12-bit) 
 *or set the number of samples used when averaging results for the Shunt Voltage Register
 */
void DFRobot_INA219::setSADC(eIna219AdcBits_t bits, eIna219AdcSample_t sample)
{
    int16_t    conf;
    int16_t    value = 0;
    if(bits < eIna219AdcBits_12 && sample > eIna219AdcSample_1)
       return;
    if(bits < eIna219AdcBits_12)
        value = bits;
    else
        value = 0x08 | sample;
    conf = readInaReg(INA219_REG_CONFIG);
    conf &= ~((uint16_t) 0x0f << 3);
    conf |= (uint16_t) value << 3;
    writeInaReg(INA219_REG_CONFIG, conf);
}
/*Selects continuous, triggered, or power-down mode of operation*/
void DFRobot_INA219::setMode(eInaMode_t mode)
{
    int16_t    conf;
    conf = readInaReg(INA219_REG_CONFIG);
    conf &= ~((uint16_t) 0x07);
    conf |= (uint16_t) mode;
    writeInaReg(INA219_REG_CONFIG, conf);
}

void DFRobot_INA219::reset()
{
    writeInaReg(INA219_REG_CONFIG, INA219_CONFIG_RESET);
}

void DFRobot_INA219_IIC::writeReg(uint8_t reg, uint8_t *pBuf, uint16_t len)
{
    lastOperateStatus = eIna219_WriteRegError;
    _pWire->begin();
    _pWire->beginTransmission(_addr);
    _pWire->write(reg);
    for(uint16_t i = 0; i < len; i ++)
        _pWire->write(pBuf[i]);
    _pWire->endTransmission();
    lastOperateStatus = eIna219_ok;
}

void DFRobot_INA219_IIC::readReg(uint8_t reg, uint8_t *pBuf, uint16_t len)
{
    lastOperateStatus = eIna219_ReadRegError;
    _pWire->begin();
    _pWire->beginTransmission(_addr);
    _pWire->write(reg);
    if(_pWire->endTransmission() != 0)
        return;
    _pWire->requestFrom(_addr, (uint8_t) len);
    for(uint16_t i = 0; i < len; i ++) {
        pBuf[i] = _pWire->read();
    }
    _pWire->endTransmission();
    lastOperateStatus = eIna219_ok;
}

int16_t DFRobot_INA219::readInaReg(uint8_t reg)
{
    uint8_t buf[2] = {0};
    
    readReg(reg, buf, sizeof(buf));
    return (buf[0] << 8) | buf[1];
}

void DFRobot_INA219::writeInaReg(uint8_t reg, uint16_t value)
{
    uint8_t buffer[2] = {(value >> 8), value & 0xff};
    writeReg(reg, buffer, 2);
}

bool DFRobot_INA219_IIC::scan()
{
    _pWire->beginTransmission(_addr);
    if (_pWire->endTransmission() == 0){
        return true;
    }
    return false;
}
