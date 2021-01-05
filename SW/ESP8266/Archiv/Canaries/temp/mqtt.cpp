#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include "main.h" //main.h
#include "uMQTTBroker.h"
#include "mqtt.h"


myMQTTBroker myBroker;


/**
 ******************************************************************************
 * \brief   initialise the MQTT
 *
 * \param   -
 * \return  -
 */
void mqttInit(void){

  // Start the broker
  Serial.println("Starting MQTT broker");
  myBroker.init();

/*
 * Subscribe to anything
 */
  myBroker.subscribe("#");
}




int mqttPublishTest(int value){
  myBroker.publish("broker/counter", (String)value++);
  return value;
}
