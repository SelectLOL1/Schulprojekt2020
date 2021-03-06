/**
 ******************************************************************************
 * \file                        web.h
 *
 * \brief                       Definitions of the webinterface
 *
 * - <b>Project:</b>            SensorProject
 * - <b>Copyright:</b>          Chris Linvers & Michael Andres
 *
 * - <b>IDE:</b>                Arduino 1.8.7
 * - <b>Controller:</b>         LoLin NodeMcu V3
 *
 * \par<b>Detailed Description:</b>
 * How to connect to the Router and send the data to the server
 ******************************************************************************
 */
#ifndef WIFI_H
#define WIFI_H
#include <ESP8266WiFi.h>
#include "main.h"

/******************************************************************************
 ** Constants, Makros and type definitions                                   **
 ******************************************************************************/

/******************************************************************************
 ** Variables                                                                **
 ******************************************************************************/


/******************************************************************************
 ** Functions                                                                **
 ******************************************************************************/
extern void wifiInit(void);
extern void wifiStatus(void);
#endif // WIFI_H
