/*!
 * @file DFRobot_INA219.h
 * @brief Define the infrastructure of the DFRobot_INA219 class
 * @details 该库用来驱动INA219芯片,可用来检测用电设备的电压、电流和功率
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @License     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2022-03-1
 * @url https://github.com/DFRobot/DFRobot_INA219
 */
 
#ifndef _DFROBOT_INA219_H
#define _DFROBOT_INA219_H
#include <Wire.h>

#define INA219_I2C_ADDRESS1                      (0x40)///< I2C ADDRESS 1
#define INA219_I2C_ADDRESS2                      (0x41)///< I2C ADDRESS 2
#define INA219_I2C_ADDRESS3                      (0x44)///< I2C ADDRESS 3
#define INA219_I2C_ADDRESS4                      (0x45)///< I2C ADDRESS 4

#define DFROBOT_INA219_READ                      (0x01)///<Register Configuration

#define INA219_REG_CONFIG                        (0x00) ///<配置寄存器
#define INA219_CONFIG_RESET                      (0x8000) ///<配置复位寄存器
#define INA219_CONFIG_BUSVOLTAGERANGE_MASK       (0x2000) ///<配置总线电压范围
#define INA219_REG_SHUNTVOLTAGE                  (0x01)///<Shunt Voltage Register
#define INA219_REG_BUSVOLTAGE                    (0x02)///<Bus Voltage Register
#define INA219_REG_POWER                         (0x03)///<Power Register
#define INA219_REG_CURRENT                       (0x04)///<Current Register
#define INA219_REG_CALIBRATION                   (0x05)///<Register Calibration


class DFRobot_INA219
{
public:
/**
 * @enum eIna219Status_t
 * @brief 错误码
 * @details 对程序运行上出现的错误进行说明
 */
typedef enum {
    eIna219_ok,/**<无错误 */
    eIna219_InitError,/**<初始化错误 */
    eIna219_WriteRegError,/**<写寄存器错误 */
    eIna219_ReadRegError,/**<读寄存器错误 */
}eIna219Status_t;

/**
 * @enum eIna219BusVolRange_t
 * @brief Bus Voltage Range
 */
typedef enum {
    eIna219BusVolRange_16V,/**< ±16V*/ 
    eIna219BusVolRange_32V/**< ±32V*/
} eIna219BusVolRange_t;

/**
 * @enum eIna219PGABits_t
 * @brief  GAIN and range for PGA(Shunt Voltage Only)
 */
typedef enum {
    eIna219PGABits_1,/**<GAIN:1,Range ±40 mV*/ 
    eIna219PGABits_2,/**<GAIN:/2,Range ±80 mV*/ 
    eIna219PGABits_4,/**<GAIN:/4,Range ±160 mV*/ 
    eIna219PGABits_8/**<GAIN:/8,Range ±320 mV*/ 
} eIna219PGABits_t;

/**
 * @enum eIna219AdcBits_t
 * @brief  These bits adjust the Shunt ADC resolution (9-, 10-, 11-, or 12-bit) or set the number of samples used when
averaging results for the Shunt Voltage Register (01h).

 */
typedef enum {
    eIna219AdcBits_9,
    eIna219AdcBits_10,
    eIna219AdcBits_11,
    eIna219AdcBits_12
} eIna219AdcBits_t;

/**
 * @enum eIna219AdcSample_t
 * @brief 每次adc采集的样本数
 */
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

/**
 * @enum eInaMode_t
 * @brief Operating Mode
 */
typedef enum{
    eIna219PowerDown,   /**<Power-down*/ 
    eIna219SVolTrig,    /**<Shunt voltage, triggered*/ 
    eIna219BVolTrig,    /**<Bus voltage, triggered*/ 
    eIna219SAndBVolTrig,/**<Shunt and bus, triggered*/ 
    eIna219AdcOff,      /**<ADC off (disabled)*/ 
    eIna219SVolCon,     /**<Shunt voltage, continuous*/ 
    eIna219BVolCon,     /**<Bus voltage, continuous*/ 
    eIna219SAndBVolCon  /**<Shunt and bus, continuous*/ 
} eInaMode_t;
public:
    /**
     * @fn DFRobot_INA219
     * @brief 构造函数
     * @return None
     */
    DFRobot_INA219(){};

    /**
     * @fn begin
     * @brief 在读取数据之前,初始化I2C总线,配置INA219的配置寄存器
     * @return true(成功)/false(失败)
     */
    bool begin();

    /**
     * @fn linearCalibrate
     * @brief 线性校准
     * @param ina219Reading_mA    通过INA219测量得到的电流(未校准前)
     * @param extMeterReading_mA  实际测量的电流
     */
    void linearCalibrate(float ina219Reading_mA, float extMeterReading_mA);
	
    /**
     * @fn reset
     * @brief 复位配置寄存器
     */
    void reset();

    /**
     * @fn getBusVoltage_V
     * @brief  get the BusVoltage （Voltage of IN- to GND)
     * @return Voltage unit:V
     */
    float getBusVoltage_V();

    /**
     * @fn getShuntVoltage_mV
     * @brief  get the ShuntVoltage （Voltage of the sampling resistor, IN+ to NI-)
     * @return Voltage unit:mV
     */
    float getShuntVoltage_mV();
    
	/**
     * @fn getCurrent_mA
     * @brief get the Current(Current flows across IN+ and IN-.
	 * @n If the current flows from IN+ to IN-, the reading is positive. 
	 * @n If the current flows from IN- to IN+, the reading is negative)
     * @return Current unit:mA
     */
    float getCurrent_mA();
    
    /**
     * @fn getPower_mW
     * @brief 获取功率
	 * @details the power resolution read directly from the module is 20mW 
	 * @n (hardware mode). If the power is obtained by using the statement 
	 * @n "Power = BusVoltage*Current;", the resolution can be increased to 4mW 
	 * @n (software mode).
     * @return power unit：mW
     */
	float getPower_mW();

    /**
     * @fn setBRNG
     * @brief  设置 BRNG参数(Bus Voltage Range)
     * @param value     eIna219BusVolRange_16V < 16V >
     * @n               eIna219BusVolRange_32V < 32V >
     */
    void  setBRNG(eIna219BusVolRange_t value);
	
    /**
     * @fn setPGA
     * @brief  设置 PGA参数(Shunt Voltage Only)
     * @param bits          eIna219PGABits_1 <GAIN:1,Range ±40 mV>
     * @n                   eIna219PGABits_2 <GAIN:/2,Range ±80 mV>
     * @n                   eIna219PGABits_4 <GAIN:/4,Range ±160 mV> 
     * @n                   eIna219PGABits_8 <GAIN:/8,Range ±320 mV> 
     */
    void  setPGA(eIna219PGABits_t bits);
	
    /**
     * @fn setBADC
     * @brief  设置 BADC参数(Bus ADC Resolution/Averaging)
     * @param bits           Resolution
     * @n                    eIna219AdcBits_9,
     * @n                    eIna219AdcBits_10,
     * @n                    eIna219AdcBits_11,
     * @n                    eIna219AdcBits_12
     * @param sample         样本数
     * @n                    eIna219AdcSample_1,
     * @n                    eIna219AdcSample_2,
     * @n                    eIna219AdcSample_4,
     * @n                    eIna219AdcSample_8,
     * @n                    eIna219AdcSample_16,
     * @n                    eIna219AdcSample_32,
     * @n                    eIna219AdcSample_64,
     * @n                    eIna219AdcSample_128
	 */
    void  setBADC(eIna219AdcBits_t bits, eIna219AdcSample_t sample);

    /**
     * @fn setSADC
     * @brief  设置SADC参数(Shunt ADC Resolution/Averaging)
     * @param bits           Resolution
     * @n                    eIna219AdcBits_9,
     * @n                    eIna219AdcBits_10,
     * @n                    eIna219AdcBits_11,
     * @n                    eIna219AdcBits_12
     * @param sample         样本数
     * @n                    eIna219AdcSample_1,
     * @n                    eIna219AdcSample_2,
     * @n                    eIna219AdcSample_4,
     * @n                    eIna219AdcSample_8,
     * @n                    eIna219AdcSample_16,
     * @n                    eIna219AdcSample_32,
     * @n                    eIna219AdcSample_64,
     * @n                    eIna219AdcSample_128
     */
    void  setSADC(eIna219AdcBits_t bits, eIna219AdcSample_t sample);

    /**
     * @fn setMode
     * @brief  Set operation Mode
     * @param mode  
     * @n                eIna219PowerDown,   <Power-down> 
     * @n                eIna219SVolTrig,    <Shunt voltage, triggered> 
     * @n                eIna219BVolTrig,    <Bus voltage, triggered>  
     * @n                eIna219SAndBVolTrig,<Shunt and bus, triggered>  
     * @n                eIna219AdcOff,      <ADC off (disabled)> 
     * @n                eIna219SVolCon,     <Shunt voltage, continuous>  
     * @n                eIna219BVolCon,     <Bus voltage, continuous>  
     * @n                eIna219SAndBVolCon  <Shunt and bus, continuous> 
     */
	void  setMode(eInaMode_t mode);
    
    eIna219Status_t lastOperateStatus;
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
    /**
     * @fn DFRobot_INA219_IIC
     * @brief 构造函数
     * @param pWire I2C控制器指针
     * @param i2caddr  I2C 地址
     * @n INA219_I2C_ADDRESS1  0x40   A0 = 0  A1 = 0
     * @n INA219_I2C_ADDRESS2  0x41   A0 = 1  A1 = 0
     * @n INA219_I2C_ADDRESS3  0x44   A0 = 0  A1 = 1
     * @n INA219_I2C_ADDRESS4  0x45   A0 = 1  A1 = 1
     */
    DFRobot_INA219_IIC(TwoWire *pWire, uint8_t i2caddr) : DFRobot_INA219() { _pWire = pWire; _addr = i2caddr; }

protected:
    void    writeReg(uint8_t reg, uint8_t *pBuf, uint16_t len);
    void    readReg(uint8_t reg, uint8_t *pBuf, uint16_t len);
    bool scan();
    uint8_t   _addr;
    TwoWire   *_pWire;
};

#endif
