import smbus
import time

class INA219:

    _INA219_READ                              = (0x01)

    INA219_I2C_ADDRESS1                      = (0x40)
    INA219_I2C_ADDRESS2                      = (0x41)
    INA219_I2C_ADDRESS3                      = (0x44)
    INA219_I2C_ADDRESS4                      = (0x45)

    INA219_CONFIG_RESET                      = (0x8000)

    bus_vol_range_16V                    = 0
    bus_vol_range_32V                    = 1

    PGA_bits_1                                = 0
    PGA_bits_2                                = 1
    PGA_bits_4                                = 2
    PGA_bits_8                                = 3
    
    adc_bits_9                             = 0
    adc_bits_10                            = 1
    adc_bits_11                            = 2
    adc_bits_12                            = 3
    
    adc_sample_1                             = 0
    adc_sample_2                             = 1
    adc_sample_4                             = 2
    adc_sample_8                             = 3
    adc_sample_16                            = 4
    adc_sample_32                            = 5
    adc_sample_64                            = 6
    adc_sample_128                           = 7
    
    power_down                               = 0
    shunt_vol_trig                           = 1
    bus_vol_trig                             = 2
    shunt_and_bus_vol_trig                   = 3
    adc_off                                  = 4
    shunt_vol_con                            = 5
    bus_vol_con                              = 6
    shunt_and_bus_vol_con                    = 7

    _INA219_REG_SHUNTVOLTAGE                       = (0x01)

    _INA219_REG_BUSVOLTAGE                         = (0x02)

    _INA219_REG_POWER                              = (0x03)

    _INA219_REG_CURRENT                            = (0x04)

    _INA219_REG_CALIBRATION                        = (0x05)


    def __init__(self, bus, addr):
        self.i2cbus=smbus.SMBus(bus)
        self.i2cAddr = addr

    def begin(self):
        if not self.scan():
            return False
            self.setBRNG(self.bus_vol_range_32V)
            self.setPGA(self.PGA_bits_8)
            self.setBADC(self.adc_bits_12, self.adc_sample_8)
            self.setSADC(self.adc_bits_12, self.adc_sample_8)
            self.setMode(self.shunt_and_bus_vol_con)
        else:
            return True

    def linearCal(self, ina219Reading_mA, extMeterReading_mA):
        calValue = 4096
        ina219Reading_mA = float(ina219Reading_mA)
        extMeterReading_mA = float(extMeterReading_mA)
        calValue = int((extMeterReading_mA / ina219Reading_mA) * calValue) & 0xFFFE
        self._writeRegister(self._INA219_REG_CALIBRATION, calValue)

    def reset(self):
        self._writeRegister(self._INA219_REG_CONFIG, self._INA219_CONFIG_RESET)

    def _writeRegister(self, register, value):
        self.i2cbus.write_i2c_block_data(self.i2cAddr, register, [value >> 8, value & 0xff])

    def _readRegister(self, register):
        return self.i2cbus.read_i2c_block_data(self.i2cAddr, register) 

    def getBusVoltage_V(self):
        return float(self.readInaReg(self._INA219_REG_BUSVOLTAGE) >> 1) * 0.001

    def getShuntVoltage_mV(self):
        return float(self.readInaReg(self._INA219_REG_SHUNTVOLTAGE))

    def getCurrent_mA(self):
        return float(self.readInaReg(self._INA219_REG_CURRENT))

    def getPower_mW(self):
        return float(self.readInaReg(self._INA219_REG_POWER)) * 20

    def setBRNG(self, value):
        conf = 0
        conf = self.readInaReg(self._INA219_REG_CONFIG)
        conf &= ~(0x01 << 13)
        conf |= value << 13
        self._writeRegister(self._INA219_REG_CONFIG, conf)

    def setPGA(self, bits):
        conf = 0
        conf = self.readInaReg(self._INA219_REG_CONFIG)
        conf &= ~(0x03 << 11)
        conf |= bits << 11
        self._writeRegister(self._INA219_REG_CONFIG, conf)
    
    def setBADC(self, bits, sample):
        conf = 0
        value = 0
        if(bits < adc_bits_12 and sample > adc_sample_1):
            return
        if(bits < adc_bits_12):
            value = bits
        else:
            value = 0x80 | sample
        conf = self.readInaReg(self._INA219_REG_CONFIG)
        conf &= ~(0x0f << 7)
        conf |= value << 7
        self._writeRegister(self._INA219_REG_CONFIG, conf)
    
    def setSADC(self, bits, sample):
        conf = 0
        value = 0
        if(bits < adc_bits_12 and sample > adc_sample_1):
            return
        if(bits < adc_bits_12):
            value = bits
        else:
            value = 0x80 | sample
        conf = self.readInaReg(self._INA219_REG_CONFIG)
        conf &= ~(0x0f << 3)
        conf |= value << 3
        self._writeRegister(self._INA219_REG_CONFIG, conf)
    
    def setMode(self, mode):
        conf = 0
        conf = self.readInaReg(self._INA219_REG_CONFIG)
        conf &= ~0x07
        conf |= mode
        self._writeRegister(self._INA219_REG_CONFIG, conf)

    def readInaReg(self, reg):
        buf = []
        buf = self._readRegister(reg)
        if (buf[0] & 0x80):
            return - 0x10000 + ((buf[0] << 8) | (buf[1]))
        else:
            return (buf[0] << 8) | (buf[1])

    def scan(self):
        try:
            self.i2cbus.read_byte(self.i2cAddr)
            return True
        except:
            print("I2C init fail")
            return False



