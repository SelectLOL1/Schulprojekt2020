/*!
 *
 *
 */

#include "Adafruit_SGP30.h"


Adafruit_SGP30::Adafruit_SGP30() {
	  _i2caddr = NULL;
	  
}

/**************************************************************************/
/*! 
    @brief  Setups the hardware and detects a valid SGP30. Initializes I2C
    then reads the serialnumber and checks that we are talking to an SGP30
    @returns True if SGP30 found on I2C, False if something went wrong!
*/
/**************************************************************************/
boolean Adafruit_SGP30::begin(uint8_t i2caddr) {
  _i2caddr = i2caddr;
  
  uint8_t command[2];
  command[0] = 0x36;
  command[1] = 0x82;
  if (! readWordFromCommand(command, 2, 10, serialnumber, 3)) 
    return false;

  uint16_t featureset;
  command[0] = 0x20;
  command[1] = 0x2F;
  if (! readWordFromCommand(command, 2, 10, &featureset, 1)) 
    return false;
  //Serial.print("Featureset 0x"); Serial.println(featureset, HEX);
  if (featureset != SGP30_FEATURESET) 
    return false;
  if (! IAQinit()) 
    return false;

  return true;
}

/**************************************************************************/
/*! 
    @brief  Commands the sensor to begin the IAQ algorithm. Must be called after startup.
    @returns True if command completed successfully, false if something went wrong!
*/
/**************************************************************************/
boolean Adafruit_SGP30::IAQinit(void) {
  uint8_t command[2];
  command[0] = 0x20;
  command[1] = 0x03;
  return readWordFromCommand(command, 2, 10);
}
	

/**************************************************************************/
/*! 
    @brief  Commands the sensor to take a single eCO2/VOC measurement. Places results in TVOC and eCO2}
    @returns True if command completed successfully, false if something went wrong!
*/
/**************************************************************************/
boolean Adafruit_SGP30::IAQmeasure(void) {
  uint8_t command[2];
  command[0] = 0x20;
  command[1] = 0x08;
  uint16_t reply[2];
  if (! readWordFromCommand(command, 2, 12, reply, 2))
    return false;
  TVOC = reply[1];
  eCO2 = reply[0];
  return true;
}
 
/**************************************************************************/
/*! 
    @brief Request baseline calibration values for both CO2 and TVOC IAQ calculations. Places results in parameter memory locaitons.
    @param eco2_base A pointer to a uint16_t which we will save the calibration value to
    @param tvoc_base A pointer to a uint16_t which we will save the calibration value to
    @returns True if command completed successfully, false if something went wrong!
*/
/**************************************************************************/
boolean Adafruit_SGP30::getIAQBaseline(uint16_t *eco2_base, uint16_t *tvoc_base) {
  uint8_t command[2];
  command[0] = 0x20;
  command[1] = 0x15;
  uint16_t reply[2];
  if (! readWordFromCommand(command, 2, 10, reply, 2))
    return false;
  *eco2_base = reply[0];
  *tvoc_base = reply[1];
  return true;
}

/**************************************************************************/
/*! 
    @brief Assign baseline calibration values for both CO2 and TVOC IAQ calculations.
    @param eco2_base A uint16_t which we will save the calibration value from
    @param tvoc_base A uint16_t which we will save the calibration value from
    @returns True if command completed successfully, false if something went wrong!
*/
/**************************************************************************/
boolean Adafruit_SGP30::setIAQBaseline(uint16_t eco2_base, uint16_t tvoc_base) {
  uint8_t command[8];
  command[0] = 0x20;
  command[1] = 0x1e;
  command[2] = tvoc_base >> 8;
  command[3] = tvoc_base & 0xFF;
  command[4] = crc8(command+2, 2);
  command[5] = eco2_base >> 8;
  command[6] = eco2_base & 0xFF;
  command[7] = crc8(command+5, 2);

  return readWordFromCommand(command, 8, 10);
}

/**************************************************************************/
/*!
    @brief Set the absolute humidity value [mg/m^3] for compensation to increase precision of TVOC and eCO2.
    @param absolute_humidity A uint32_t [mg/m^3] which we will be used for compensation. If the absolute humidity is set to zero, humidity compensation will be disabled.
    @returns True if command completed successfully, false if something went wrong!
*/
/**************************************************************************/
boolean Adafruit_SGP30::setHumidity(uint32_t absolute_humidity) {
  if (absolute_humidity > 256000) {
    return false;
  }

  uint16_t ah_scaled = (uint16_t)(((uint64_t)absolute_humidity * 256 * 16777) >> 24);
  uint8_t command[5];
  command[0] = 0x20;
  command[1] = 0x61;
  command[2] = ah_scaled >> 8;
  command[3] = ah_scaled & 0xFF;
  command[4] = crc8(command+2, 2);

  return readWordFromCommand(command, 5, 10);
}

/**************************************************************************/
/*! 
    @brief  I2C low level interfacing
*/
/**************************************************************************/


boolean Adafruit_SGP30::readWordFromCommand(uint8_t command[], uint8_t commandLength, uint16_t delayms, uint16_t *readdata, uint8_t readlen)
{
  uint8_t data;
  Wire.beginTransmission(_i2caddr);

  for (uint8_t i=0; i<commandLength; i++) {
    Wire.write(command[i]);
  }
  Wire.endTransmission();
  delay(delayms);
  if (readlen == 0) 
    return true;

  uint8_t replylen = readlen * (SGP30_WORD_LEN +1);
  if (Wire.requestFrom(_i2caddr, replylen) != replylen) 
    return false;
  uint8_t replybuffer[replylen];
  
  for (uint8_t i=0; i<replylen; i++) {
    replybuffer[i] = Wire.read();
  }

  for (uint8_t i=0; i<readlen; i++) {
    uint8_t crc = crc8(replybuffer+i*3, 2);
    if (crc != replybuffer[i * 3 + 2])
      return false;
    // success! store it
    readdata[i] = replybuffer[i*3];
    readdata[i] <<= 8;
    readdata[i] |= replybuffer[i*3 + 1];
  }
  return true;
}


/*
*
* CRC-8 formula from page 14 of SHT spec pdf
*
* Test data 0xBE, 0xEF should yield 0x92
*
* Initialization data 0xFF
* Polynomial 0x31 (x8 + x5 +x4 +1)
* Final XOR 0x00
*/
uint8_t Adafruit_SGP30::crc8(const uint8_t *data, int len) {
  const uint8_t POLYNOMIAL(0x31);
  uint8_t crc(0xFF);

  for (int j = len; j; --j) {
    crc ^= *data++;
    for (int i = 8; i; --i) {
      crc = (crc & 0x80) ? (crc << 1) ^ POLYNOMIAL : (crc << 1);
    }
  }
  return crc;
}
