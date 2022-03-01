# DFRobot_INA219
- [English Version](./README.md)

  Gravity: I2C数字功率计是一款可测量26V 8A以内各类电子模块、用电设备的电压、电流和功率，最大相对误差不超过±0.2%的高分辨、高精度、大量程测量模块（使用前需进行一次简单的手动校准）。可用于太阳能系统、电池库仑计、电机、主控板或电子模块的功耗测量、电池续航评估与实时电源参数在线监控。

![产品效果图片](./resources/images/SEN0291.jpg)


## 产品链接（https://www.dfrobot.com.cn/goods-1890.html）

    SEN0291：Gravity: I2C数字功率计
   
## 目录

  * [概述](#概述)
  * [库安装](#库安装)
  * [方法](#方法)
  * [兼容性](#兼容性)
  * [历史](#历史)
  * [创作者](#创作者)

## 概述
通过I2C读取INA219取样电阻两端的电压、电流、功率和电压。
这些数据通过串口输出。
## 库安装
要使用此库，请先下载库文件，并将其粘贴到\Arduino\libraries目录中
，然后打开示例文件夹并在该文件夹中运行demo。

## 方法

```C++

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
    void linearCalibrate(float ina219Reading_mA, float extMeterReading_mA),
 
    /**
     * @fn reset
     * @brief 复位配置寄存器
     */
    void reset();

    /**
     * @fn getBusVoltage_V
     * @brief  获取 IN-相对GND电压
     * @return 电压 单位:V
     */
    float getBusVoltage_V();

    /**
     * @fn getShuntVoltage_mV
     * @brief  获取IN+相对IN-的两端电压
     * @return 电压 单位:mV
     */
    float getShuntVoltage_mV();
    
    /**
     * @fn getCurrent_mA
     * @brief 获取流经IN+和IN-的电流
     * @n 若电流从IN+流向IN-，电流值为正. 
     * @n 若为电流从IN-流向IN+，电流值为负
     * @return 电流 单位:mA
     */
    float getCurrent_mA();
    
    /**
     * @fn getPower_mW
     * @brief 获取功率
     * @details 直接从模块读取到的功率分辨率为20mW（硬件方式），若使用语句“Power = 
     * @n  BusVoltage*Current;”得到功率，其分辨率可提高至4mW（软件方式）。
     * @return 功率 unit：mW
     */
    float getPower_mW();

    /**
     * @fn setBRNG
     * @brief  设置 BRNG参数
     * @param value     eIna219BusVolRange_16V < 16V >
     * @n               eIna219BusVolRange_32V < 32V >
     */
    void  setBRNG(eIna219BusVolRange_t value);
 
    /**
     * @fn setPGA
     * @brief  设置 PGA参数
     * @param bits          eIna219PGABits_1 <增益:1,量程 ±40 mV>
     * @n                   eIna219PGABits_2 <增益:/2,量程 ±80 mV>
     * @n                   eIna219PGABits_4 <增益:/4,量程 ±160 mV> 
     * @n                   eIna219PGABits_8 <增益:/8,量程 ±320 mV> 
     */
    void  setPGA(eIna219PGABits_t bits);
 
    /**
     * @fn setBADC
     * @brief  设置 BADC参数
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
     * @brief  设置SADC参数
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
     * @brief  设置读取模式
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

```

## 兼容性
MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino Uno        |      √       |              |             | 
Raspberry Pi      |      √       |              |             | 

## 历史

- 2022/3/1 - Version 1.0.0 released.

## 创作者

Written by fengli(li.feng@dfrobot.com), 2022.3.1 (Welcome to our [website](https://www.dfrobot.com/))





