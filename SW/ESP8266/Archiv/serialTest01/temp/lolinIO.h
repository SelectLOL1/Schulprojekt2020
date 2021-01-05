/**
 ******************************************************************************
 * \file                        io.h
 *
 * \brief                       Definitions of the IOs for use as GPIOs
 *
 * - <b>Project:</b>            SensorProject
 * - <b>Copyright:</b>          Chris Linvers & Michael Andres
 *
 * - <b>IDE:</b>                Arduino 1.8.7
 * - <b>Controller:</b>         LoLin NodeMcu V3
 *
 * \par<b>Detailed Description:</b>
 * Input / Output definitions
 ******************************************************************************
 */
#ifndef IO_H
#define IO_H

/******************************************************************************
 ** Constants, Makros and type definitions                                   **
 ******************************************************************************/
#define   VERSION 001
                        #define   LEDPIN = 13; // GPIO13

                        #define   TASTER    10
                        #define   LED1 5
                        #define   LED2 6
                        #define   LED3 7
                        #define   LED4 8
                        #define   LED5 9
                        #define   FBLASER  2
                        #define   DISPMON  1
                        #define   VIDEOP   0 

                        // Sensor 1
                        #define READ       3
                        #define SHUTTER    2
                        #define DATA_RDY  11
                        #define CLR_PIX   12



#endif // IO_H
