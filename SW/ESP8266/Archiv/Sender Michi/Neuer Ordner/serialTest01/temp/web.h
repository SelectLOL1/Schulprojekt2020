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
#ifndef WEB_H
#define WEB_H


/******************************************************************************
 ** Constants, Makros and type definitions                                   **
 ******************************************************************************/
// LOGIN 
const char* ssid = "Chris";
const char* password = "Chris12345678";
/******************************************************************************
 ** Variables                                                                **
 ******************************************************************************/


/******************************************************************************
 ** Functions                                                                **
 ******************************************************************************/
extern void webInit(void);
#endif // WEB_H
