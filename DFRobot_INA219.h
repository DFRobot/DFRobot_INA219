#ifndef _DFROBOT_INA219_H
#define _DFROBOT_INA219_H
#include <Wire.h>


/*I2C ADDRESS*/
#define INA219_I2C_ADDRESS1                      (0x40)
#define INA219_I2C_ADDRESS2                      (0x41)
#define INA219_I2C_ADDRESS3                      (0x44)
#define INA219_I2C_ADDRESS4                      (0x45)

#define DFROBOT_INA219_READ                              (0x01)
/*Register Configuration*/
#define INA219_REG_CONFIG                        (0x00)
#define INA219_CONFIG_RESET                      (0x8000)
#define INA219_CONFIG_BUSVOLTAGERANGE_MASK       (0x2000)

/*Shunt Voltage Register*/
#define INA219_REG_SHUNTVOLTAGE                  (0x01)
/*Bus Voltage Register*/
#define INA219_REG_BUSVOLTAGE                    (0x02)
/*Power Register*/
#define INA219_REG_POWER                         (0x03)
/*Current Register*/
#define INA219_REG_CURRENT                       (0x04)
/*Register Calibration*/
#define INA219_REG_CALIBRATION                   (0x05)

enum eIna219_Status{
    eIna219_ok,
    eIna219_InitError,
    eIna219_WriteRegError,
    eIna219_ReadRegError,
};

typedef enum {
    eIna219BusVolRange_16V,
    eIna219BusVolRange_32V
} eIna219BusVolRange_t;

typedef enum {
    eIna219PGABits_1,
    eIna219PGABits_2,
    eIna219PGABits_4,
    eIna219PGABits_8
} eIna219PGABits_t;

typedef enum {
    eIna219AdcBits_9,
    eIna219AdcBits_10,
    eIna219AdcBits_11,
    eIna219AdcBits_12
} eIna219AdcBits_t;

typedef enum {
    eIna219AdcSample_1,
    eIna219AdcSample_2,
    eIna219AdcSample_4,
    eIna219AdcSample_8,
    eIna219AdcSample_16,
    eIna219AdcSample_32,
    eIna219AdcSample_64,
    eIna219AdcSample_128
} eIna219AdcSample_t;

typedef enum{
    eIna219PowerDown,
    eIna219SVolTrig,
    eIna219BVolTrig,
    eIna219SAndBVolTrig,
    eIna219AdcOff,
    eIna219SVolCon,
    eIna219BVolCon,
    eIna219SAndBVolCon
} eInaMode;

class DFRobot_INA219
{
public:

    DFRobot_INA219(){};
    bool begin();
    void linearCalibrate(float ina219Reading_mA, float extMeterReading_mA),
         reset();
    
    eIna219_Status lastOperateStatus;
    

    float getBusVoltage_V(),
          getShuntVoltage_mV(),
          getCurrent_mA(),
          getPower_mW();
    
    void  setBRNG(eIna219BusVolRange_t value),
          setPGA(eIna219PGABits_t bits),
          setBADC(eIna219AdcBits_t bits, eIna219AdcSample_t sample),
          setSADC(eIna219AdcBits_t bits, eIna219AdcSample_t sample),
          setMode(eInaMode mode);
    
    
protected:

    uint16_t calValue;
    void writeConfig();
    virtual bool scan();
    virtual void writeReg(uint8_t reg, uint8_t *pBuf, uint16_t len);
    virtual void readReg(uint8_t reg, uint8_t *pBuf, uint16_t len);
    uint8_t BusRange, Pga, Badc, Sadc, Mode;
    int16_t readInaReg(uint8_t reg);
    void writeInaReg(uint8_t reg, uint16_t value);
    
};

class DFRobot_INA219_IIC : public DFRobot_INA219
{
public:
    DFRobot_INA219_IIC(TwoWire *pWire, uint8_t i2caddr) : DFRobot_INA219() { _pWire = pWire; _addr = i2caddr; }

protected:
    void    writeReg(uint8_t reg, uint8_t *pBuf, uint16_t len);
    void    readReg(uint8_t reg, uint8_t *pBuf, uint16_t len);

    
    bool scan();
    uint8_t   _addr;
    TwoWire   *_pWire;
};

#endif
