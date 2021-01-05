/*!
 *
 *
 */

#ifndef ADAFRUIT_SHT31_H
#define ADAFRUIT_SHT31_H

#include "Arduino.h"
#include "Wire.h"

#define SHT31_DEFAULT_ADDR         0x44	//i2c Address

#define SHT31_FETCH_DATA           0xE000
#define SHT31_PER_MEAS_ART         0x2B32

#define SHT31_BREAK                0x3093
#define SHT31_SW_RESET             0x30A2
#define SHT31_HEATER_ENABLE        0x306D
#define SHT31_HEATER_DISABLE       0x3066

#define SHT31_READ_STATUS          0xF32D
#define SHT31_CLEAR_STATUS         0x3041

#define SHT31_MEAS_HIGHREP_STRETCH 0x2C06
#define SHT31_MEAS_MEDREP_STRETCH  0x2C0D
#define SHT31_MEAS_LOWREP_STRETCH  0x2C10
#define SHT31_MEAS_HIGHREP         0x2400
#define SHT31_MEAS_MEDREP          0x240B
#define SHT31_MEAS_LOWREP          0x2416


/**
 * Driver for the Adafruit SHT31-D Temperature and Humidity breakout board.
 */
class Adafruit_SHT31 {
    public:
        Adafruit_SHT31();

        boolean begin(uint8_t i2caddr = SHT31_DEFAULT_ADDR);
        float readTemperature(void);
        float readHumidity(void);
        uint16_t readStatus(void);
        void reset(void);
        void heater(boolean on);
        uint8_t crc8(const uint8_t *data, int len);

    private:
        uint8_t _i2caddr;
        float humidity;
        float temp;
        boolean  readTempHum(void);
        void     writeCommand(uint16_t cmd);
        boolean  readData(void);
};

#endif
