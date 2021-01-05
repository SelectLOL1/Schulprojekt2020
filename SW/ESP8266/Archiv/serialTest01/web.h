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
#include "serialTest01.h" //main.h

/******************************************************************************
 ** Constants, Makros and type definitions                                   **
 ******************************************************************************/

/******************************************************************************
 ** Variables                                                                **
 ******************************************************************************/


/******************************************************************************
 ** Functions                                                                **
 ******************************************************************************/
extern void webInit(void);
extern void webHandle(void);
extern void webStatus(void);
#endif // WEB_H
