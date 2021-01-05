#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <Ticker.h>
#include "ports.h"
#include "lolinIO.h"           // General GPIO defines
#include "sensors.h"       #include "wifi.h"
#include "web.h"          // controls the communication over the web
#include "mqtt.h"
#include "serialTest01.h" //main.h

     
  
float humidity, temperature, TVOC, eCO2;  
Ticker SecTicker;
Ticker TenSecTicker;


void everyTenSeconds(void){        // interrupt service routine 
  temperature = shtTemperature();  // getSensorValue(TEMP)
  humidity = shtHumidity();        // getSensorValue(HUMIDITY)
  // set the absolute humidity to enable the humditiy compensation for the air quality signals

}


void everyOneSecond(void){        // interrupt service routine 
  sgpData(temperature,humidity);
}


void setup() {
      delay(100);
      noInterrupts();           // disable all interrupts
      Serial.begin(BAUDRATE);      // open the serial port:    
      Serial.print("\n \t \t Version:");
      Serial.println(VERSION);
      Serial.println(DESCRIPTION);
      Serial.println(USER);
      Serial.println("");
      interrupts();             // enable all interrupts 

      portsInit();                // initialize HW GPIO-Ports
      Wire.begin(4,0);
      //sensor1Init(); 
      shtInit();
      delay(500); 
      sgpInit();
      wifiInit();
      mqttInit();
      webInit();
      delay(100);
      SecTicker.attach(1, everyOneSecond);
      TenSecTicker.attach(10, everyTenSeconds);
}



void loop() {
    bool SWRESET = 3;
    char state = 2;       //start without deepsleep
    for(;;){
        state = 1;
        while(state  != 0){
          //state = userrequestHandle(state);

          /*
          if (state == 1){
              Serial.println("normaly i should sleep but i am awake so i wait (20s)");
              char sleeptime = 20;
              for(int i = 0; i < sleeptime; i++){
                delay(1000);
              }
              //ESP.deepSleep(20e6); // 20e6 is 20 microseconds     //not working as expected.. It's sleeping!
          }*/
          //mqttPublishTest(state);
          webHandle();    // handle a client request
        }
    }
}
