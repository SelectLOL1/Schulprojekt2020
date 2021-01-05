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

//####################### DO NOT EDIT! ################################ BEGIN
//okey
//                         ___________________________
//              TOUT ADC0 | A0                     D0 | GPIO16 USER WAKE
//                        | G                      D1 | GPIO5  
//                        | VU                     D2 | GPIO4  
//            SDD3 GPIO10 | S3                     D3 | GPIO0  FLASH
//             SDD2 GPIO9 | S2                     D4 | GPIO2  TXD1 ~PWM
//              SDD1 MOSI | S1                     3V | 3.3V   
//               SDCMD CS | SC                     G  | GND    
//              SDD0 MISO | S0                     D5 | GPIO14       HSCLK
//             SDCLK SCLK | SK                     D6 | GPIO12       HMISO
//                    GND | G                      D7 | GPIO13 RXD2  HMOSI
//                   3.3V | 3V                     D8 | GPIO15 TXD2  HCS
//                     EN | EN                     RX | GPIO3  RXD0
//                    RST | RST                    TX | GPIO1  TXD0
//                    GND | G                      G  | GND
//                    VIN | VIN                    3V | 3.3V
//                        |           // USB          |
//                        |___________________________|

                        // TX | GPIO1  TXD0
                        #define GPIO1 1
                        // D4 | GPIO2  TXD1 ~PWM
                        #define GPIO2 2
                        // RX | GPIO3  RXD0
                        #define GPIO3 3
                        // D2 | GPIO4  
                        #define GPIO4 4
                        // D1 | GPIO5
                        #define GPIO5 5
                        // SDD2 GPIO9 | S2
                        #define GPIO9 9
                        // SDD3 GPIO10 | S3
                        #define GPIO10 10
                        // D6 | GPIO12       HMISO
                        #define GPIO12 12
                        // D7 | GPIO13 RXD2  HMOSI
                        #define GPIO13 13
                        // D5 | GPIO14       HSCLK
                        #define GPIO14 14
                        // D8 | GPIO15 TXD2  HCS
                        #define GPIO15 15
                        //D0 | GPIO16 USER WAKE
                        #define GPIO16 16
                        
//####################### DO NOT EDIT! ################################ END

                      #define LED_OB 2

        //SENSOR 1----------------------------------------------------- BEGIN
                    #define WHATEVER1 GPIO1
                    #define WHATEVER2 GPIO4 
        //SENSOR 1----------------------------------------------------- END


#endif // IO_H
