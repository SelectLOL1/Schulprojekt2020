/**
 ******************************************************************************
 * \file                        mqtt.h
 *
 * \brief                       Definitions of the mqtt
 *
 * - <b>Project:</b>            SensorProject
 * - <b>Copyright:</b>          Chris Linvers & Michael Andres
 *
 * - <b>IDE:</b>                Arduino 1.8.7
 * - <b>Controller:</b>         LoLin NodeMcu V3
 *
 * \par<b>Detailed Description:</b>
 * receive data from the Sensors
 ******************************************************************************
 */
#ifndef MQTT_H
#define MQTT_H
#include "serialTest01.h" //main.h
#include "uMQTTBroker.h"


/******************************************************************************
 ** Constants, Makros and type definitions                                   **
 ******************************************************************************/

/*
 * Custom broker class with overwritten callback functions
 */
class myMQTTBroker: public uMQTTBroker {
public:
    virtual bool onConnect(IPAddress addr, uint16_t client_count) {
      Serial.println(addr.toString()+" connected");
      return true;
    }
    
    virtual bool onAuth(String username, String password) {
      Serial.println("New MQTT Connection: Username/Password: "+username+"/"+password);
      return true;
    }
    
    virtual void onData(String topic, const char *data, uint32_t length) {
      char data_str[length+1];
      os_memcpy(data_str, data, length);
      data_str[length] = '\0';
      
      Serial.println("received topic '"+topic+"' with data '"+(String)data_str+"'");
    }
};

/******************************************************************************
 ** Variables                                                                **
 ******************************************************************************/


/******************************************************************************
 ** Functions                                                                **
 ******************************************************************************/
extern void mqttInit(void);
extern int mqttPublishTest(int value);

#endif // MQTT_H
