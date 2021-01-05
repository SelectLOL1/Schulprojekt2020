#include <Wire.h>
#include <stdint.h>
#include "sensors.h"
#include "main.h"
#include "Adafruit_SGP30.h"
#include "Adafruit_SHT31.h"


Adafruit_SGP30 sgp;
Adafruit_SHT31 sht31 = Adafruit_SHT31();


/**
 ******************************************************************************
 * \brief   Initialise SHT
 *
 * \param   -
 * \return  -
 */
void shtInit(void) {
  if (! sht31.begin(0x44)){
    //while(1);
  }
  if(MODE == DEBUG){
    Serial.print("Found SHT31");
  }
}



/**
 ******************************************************************************
 * \brief   get humidity
 *
 * \param   -
 * \return  Humidity not absolute
 */
float shtHumidity(void){
  float h = sht31.readHumidity();
  if (isnan(h)) {
    Serial.println("Failed to read humidity");
  }
  return h;
}


/**
 ******************************************************************************
 * \brief   get temperature
 *
 * \param   -
 * \return  temperature
 */
float shtTemperature(void){
  float t = 0;
  t = sht31.readTemperature();
  if ( isnan(t)){
    Serial.println("Failed to read temperature");
  }
  return t;
}


/**
 ******************************************************************************
 * \brief   return absolute humidity [mg/m^3] with approximation formula
 *
 * \param   temperature [°C]
 * \param   humidity [%RH]
 * \return  temperature
 */
uint32_t getAbsoluteHumidity(float temperature, float humidity) {
    // approximation formula from Sensirion SGP30 Driver Integration chapter 3.15
    const float absoluteHumidity = 216.7f * ((humidity / 100.0f) * 6.112f * exp((17.62f * temperature) / (243.12f + temperature)) / (273.15f + temperature)); // [g/m^3]
    const uint32_t absoluteHumidityScaled = static_cast<uint32_t>(1000.0f * absoluteHumidity); // [mg/m^3]
    return absoluteHumidityScaled;
}




/**
 ******************************************************************************
 * \brief   Initialise SGP
 *
 * \param   -
 * \return  -
 */
void sgpInit() {
  if (! sgp.begin(0x58)){
    //while(1);
  }
  //if(MODE == 1){
  //  Serial.print("Found SGP30 serial #");
  //  Serial.print(sgp.serialnumber[0], HEX);
  //  Serial.print(sgp.serialnumber[1], HEX);
  //  Serial.println(sgp.serialnumber[2], HEX);
  //}
  // If you have a baseline measurement from before you can assign it to start, to 'self-calibrate'

  float temperature = shtTemperature();
  float humidity = shtHumidity();
  //sgp.setIAQBaseline(0x8E68, 0x8F41);  // Will vary for each sensor!
  sgp.setHumidity(getAbsoluteHumidity(temperature, humidity));
}



/**
 ******************************************************************************
 * \brief
 *
 * \param   -
 * \return  -
 */
void sgpData(float temperature, float humidity){
  if (! sgp.IAQmeasure()) {
    Serial.println("Airmeassurement failed");
    return;
  }
  Serial.print("TVOC "); Serial.print(sgp.TVOC); Serial.print(" ppb\t");
  Serial.print("eCO2 "); Serial.print(sgp.eCO2); Serial.println(" ppm");
}


/**
 ******************************************************************************
 * \brief
 *
 * \param   -
 * \return  -
 */
void sgpBaseline(void){
  uint16_t TVOC_base, eCO2_base;
  if (! sgp.getIAQBaseline(&eCO2_base, &TVOC_base)) {
    Serial.println("Failed to get baseline readings");
    return;
  }
  Serial.print("****Baseline values: eCO2: 0x");
  Serial.print(eCO2_base, HEX);
  Serial.print(" & TVOC: 0x");
  Serial.println(TVOC_base, HEX);
}
