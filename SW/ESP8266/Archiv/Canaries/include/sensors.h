/**
 ******************************************************************************
 * \file                        sensors.h
 *
 * \brief                       Communication with the Sensors
 *
 * - <b>Project:</b>            SensorProject
 * - <b>Copyright:</b>          Chris Linvers & Michael Andres
 *
 * - <b>IDE:</b>                Arduino 1.8.7
 * - <b>Controller:</b>         LoLin NodeMcu V3
 *
 * \par<b>Detailed Description:</b>
 * How to initialize the sensors and get data
 ******************************************************************************
 */
#ifndef SENSOR_H
#define SENSOR_H
#include "main.h" //main.h

/******************************************************************************
 ** Constants, Makros and type definitions                                   **
 ******************************************************************************/

/******************************************************************************
 ** Variables                                                                **
 ******************************************************************************/


/******************************************************************************
 ** Functions                                                                **
 ******************************************************************************/

extern void shtInit(void);
extern float shtTemperature(void);
extern float shtHumidity(void);
extern uint32_t getAbsoluteHumidity(float temperature, float humidity);

extern void sgpInit(void);
extern void sgpData(float temperature, float humidity);
extern void sgpBaseline(void);


#endif // SENSOR_H
