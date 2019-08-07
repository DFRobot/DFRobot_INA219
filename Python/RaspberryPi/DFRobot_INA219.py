import smbus
import time

class INA219:

    _INA219_READ                              = (0x01)

    INA219_I2C_ADDRESS1                      = (0x40)
    INA219_I2C_ADDRESS2                      = (0x41)
    INA219_I2C_ADDRESS3                      = (0x44)
    INA219_I2C_ADDRESS4                      = (0x45)

    INA219_CONFIG_RESET                      = (0x8000)
    _INA219_REG_CONFIG                       = (0x00)

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
        self.i2c_addr = addr

    def begin(self):
        if not self.scan():
            return False
        else:
            self.cal_value = 4096
            self.set_bus_RNG(self.bus_vol_range_32V)
            self.set_PGA(self.PGA_bits_8)
            self.set_bus_ADC(self.adc_bits_12, self.adc_sample_8)
            self.set_shunt_ADC(self.adc_bits_12, self.adc_sample_8)
            self.set_mode(self.shunt_and_bus_vol_con)
            return True

    def linear_cal(self, ina219_reading_mA, ext_meter_reading_mA):
        ina219_reading_mA = float(ina219_reading_mA)
        ext_meter_reading_mA = float(ext_meter_reading_mA)
        self.cal_value = int((ext_meter_reading_mA / ina219_reading_mA) * self.cal_value) & 0xFFFE
        self._write_register(self._INA219_REG_CALIBRATION, self.cal_value)

    def reset(self):
        self._write_register(self._INA219_REG_CONFIG, self._INA219_CONFIG_RESET)

    def _write_register(self, register, value):
        self.i2cbus.write_i2c_block_data(self.i2c_addr, register, [value >> 8, value & 0xff])

    def _read_register(self, register):
        return self.i2cbus.read_i2c_block_data(self.i2c_addr, register) 

    def get_bus_voltage_V(self):
        return float(self.read_ina_reg(self._INA219_REG_BUSVOLTAGE) >> 1) * 0.001

    def get_shunt_voltage_mV(self):
        return float(self.read_ina_reg(self._INA219_REG_SHUNTVOLTAGE))

    def get_current_mA(self):
        return float(self.read_ina_reg(self._INA219_REG_CURRENT))

    def get_power_mW(self):
        return float(self.read_ina_reg(self._INA219_REG_POWER)) * 20

    def set_bus_RNG(self, value):
        conf = 0
        conf = self.read_ina_reg(self._INA219_REG_CONFIG)
        conf &= ~(0x01 << 13)
        conf |= value << 13
        self._write_register(self._INA219_REG_CONFIG, conf)

    def set_PGA(self, bits):
        conf = 0
        conf = self.read_ina_reg(self._INA219_REG_CONFIG)
        conf &= ~(0x03 << 11)
        conf |= bits << 11
        self._write_register(self._INA219_REG_CONFIG, conf)
    
    def set_bus_ADC(self, bits, sample):
        conf = 0
        value = 0
        if(bits < self.adc_bits_12 and sample > adc_sample_1):
            return
        if(bits < self.adc_bits_12):
            value = bits
        else:
            value = 0x80 | sample
        conf = self.read_ina_reg(self._INA219_REG_CONFIG)
        conf &= ~(0x0f << 7)
        conf |= value << 7
        self._write_register(self._INA219_REG_CONFIG, conf)
    
    def set_shunt_ADC(self, bits, sample):
        conf = 0
        value = 0
        if(bits < self.adc_bits_12 and sample > adc_sample_1):
            return
        if(bits < self.adc_bits_12):
            value = bits
        else:
            value = 0x80 | sample
        conf = self.read_ina_reg(self._INA219_REG_CONFIG)
        conf &= ~(0x0f << 3)
        conf |= value << 3
        self._write_register(self._INA219_REG_CONFIG, conf)
    
    def set_mode(self, mode):
        conf = 0
        conf = self.read_ina_reg(self._INA219_REG_CONFIG)
        conf &= ~0x07
        conf |= mode
        self._write_register(self._INA219_REG_CONFIG, conf)

    def read_ina_reg(self, reg):
        buf = []
        buf = self._read_register(reg)
        if (buf[0] & 0x80):
            return - 0x10000 + ((buf[0] << 8) | (buf[1]))
        else:
            return (buf[0] << 8) | (buf[1])

    def scan(self):
        try:
            self.i2cbus.read_byte(self.i2c_addr)
            return True
        except:
            print("I2C init fail")
            return False



