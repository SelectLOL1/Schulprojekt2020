#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "ports.h"
#include "lolinIO.h"           // General GPIO defines
//#include "sensor.h"       // Template for a Sensor
#include "wifi.h"
#include "web.h"          // controls the communication over the web
#include "mqtt.h"
#include "serialTest01.h" //main.h
#define CLIENT_ID "client2"
#define TOPIC "/client2/value"
#include <MQTT.h>

              MQTT myMqtt(CLIENT_ID, "192.168.4.1", 1883);

void setup() {
      delay(10);
      Serial.begin(BAUDRATE);      // open the serial port:    
      Serial.print("\t \t Version:");
      Serial.println(VERSION);
      Serial.println(DESCRIPTION);
      Serial.println(USER);
      Serial.println("");
        wifiInit();
              portsInit(); 
        myMqtt.connect();
}

void loop() {
    bool SWRESET = 3;
    char state = 2;       //start without deepsleep

                     // initialize HW GPIO-Ports
        //sensor1Init();
        //sensor2Init();
        //sensor3Init();

        //mqttInit();
        //webInit();     


  digitalWrite(LED_OB,HIGH);
String value = "222°";
      myMqtt.publish("/client1/Temp", value);
       delay(100);
value = "7.25 g/m3";
myMqtt.publish("/client1/Feuchte",value);
 delay(100);

value = "14279 ppm";
     myMqtt.publish("/client1/C02",value );
 delay(100);

value = "20038 ppb";
     myMqtt.publish("/client1/VOC",value );
 delay(100);
value = "3.24V";
      myMqtt.publish("/client1/AD0",value );

      delay(10000);
        digitalWrite(LED_OB,LOW);
          /*
          if (state == 1){
              Serial.println("normaly i should sleep but i am awake so i wait (20s)");
              char sleeptime = 20;
              for(int i = 0; i < sleeptime; i++){
                delay(1000);
              }
              //ESP.deepSleep(20e6); // 20e6 is 20 microseconds     //not working as expected.. It's sleeping!
          }*/
        }
