/*!
 *
 *
 */

#ifndef ADAFRUIT_SGP30_H
#define ADAFRUIT_SGP30_H

#include "Arduino.h"
#include <Wire.h>

#define SGP30_DEFAULT_ADDR 0x58     // the i2c address

// commands and constants
#define SGP30_FEATURESET       0x0020  ///< The required set for this library
#define SGP30_CRC8_POLYNOMIAL  0x31    ///< Seed for SGP30's CRC polynomial
#define SGP30_CRC8_INIT        0xFF    ///< Init value for CRC
#define SGP30_WORD_LEN         2       ///< 2 bytes per word

/**************************************************************************/
/*!  Class that stores state and functions for interacting with SGP30 Gas Sensor */
/**************************************************************************/
class Adafruit_SGP30 {
	public:
		Adafruit_SGP30();
		boolean begin(uint8_t i2caddr = SGP30_DEFAULT_ADDR);
		boolean IAQinit(void);
		boolean IAQmeasure(void);

		uint16_t TVOC; //The last measurement of the IAQ-calculated Total Volatile Organic Compounds in ppb. This value is set when you call {@link IAQmeasure()}
		uint16_t eCO2; // The last measurement of the IAQ-calculated equivalent CO2 in ppm. This value is set when you call {@link IAQmeasure()}		
		uint16_t serialnumber[3]; 		// The 48-bit serial number, this value is set when you call {@link begin()}

		
		boolean getIAQBaseline(uint16_t *eco2_base, uint16_t *tvoc_base);
		boolean setIAQBaseline(uint16_t eco2_base, uint16_t tvoc_base);
		boolean setHumidity(uint32_t absolute_humidity);
		
	private:
		uint8_t _i2caddr;
				boolean readWordFromCommand(uint8_t command[], uint8_t commandLength, uint16_t delay, uint16_t *readdata = NULL, uint8_t readlen = 0);
		uint8_t crc8(const uint8_t *data, int len);
};
#endif






