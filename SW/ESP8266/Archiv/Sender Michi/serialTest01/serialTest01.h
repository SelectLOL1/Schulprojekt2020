/**
 ******************************************************************************
 * \file                        serialTest01.h
 *
 * \brief                       userdetails 
 *
 * - <b>Project:</b>            SensorProject
 * - <b>Copyright:</b>          Chris Linvers & Michael Andres
 *
 * - <b>IDE:</b>                Arduino 1.8.7
 * - <b>Controller:</b>         LoLin NodeMcu V3
 *
 * \par<b>Detailed Description:</b>
 * userspecific definitions like ssid and password
 ******************************************************************************
 */

#ifndef SERIALTEST01_H
#define SERIALTEST01_H

/******************************************************************************
 ** Constants, Makros and type definitions                                   **
 ******************************************************************************/
      #define DEBUG       1              // prints additional information
      #define RELEASE     0              // normal and simple mode
      #define BAUDRATE    115200         //serial Baudrate
      
      #define VERSION     "001"
      #define DESCRIPTION "This is a Test SW"
      #define MODE        RELEASE       // use RELEASE for normal use

      #define BOARDNR     1
      #define IPOFFSET    90
      #define USER        "Chef_vom_Dienst"
      #define WLAN_NAME   "Test"
      #define WLAN_PWD    "12345679"

/******************************************************************************
 ** Variables                                                                **
 ******************************************************************************/
      //Static IP address configuration
      const unsigned char boardid = IPOFFSET + BOARDNR;      // OFFSET + Board number 
      const char* deviceName = "SensorDevice" + BOARDNR;
      IPAddress staticIP(192, 168,   4, boardid); //ESP static ip
      IPAddress gateway( 192, 168,   4,   1);     //IP Address of your WiFi Router (Gateway)
      IPAddress subnet(  255, 255, 255,   0);     //Subnet mask
      //IPAddress dns(8, 8, 8, 8);               //DNS Michi??????
      
#endif // SERIALTEST01_H
