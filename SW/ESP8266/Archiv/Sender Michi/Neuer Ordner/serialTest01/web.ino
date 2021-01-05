
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include "web.h"
#include "wifi.h"
#include "index.h"
#include "serialTest01.h" //main.h
#include "lolinIO.h"

ESP8266WebServer server(80); //Server on port 80


/**
 ******************************************************************************
 * \brief   Handle client requests
 *
 * \param   -
 * \return  -
 */
void webHandle(void) {
  server.handleClient();          //Handle client requests
}


/**
 ******************************************************************************
 * \brief   This routine is executed when you open its IP in browser
 *
 * \param   -
 * \return  -
 */
static void handleRoot(void) {
  String s = MAIN_page;             //Read HTML contents  -->index.h
  server.send(200, "text/html", s); //Send web page
}


/**
 ******************************************************************************
 * \brief   connect to the server
 *
 * \param   -
 * \return  -
 */
static void handleSensors(void) {
  
  float humidity, temperature;  

  digitalWrite(LED_OB,HIGH); //set LED_OB ON on data request ajax

  // get Sensor values
  humidity = 5;      // getSensorValue(HUMIDITY)
  temperature = 10;  // getSensorValue(TEMP)
  int a = analogRead(A0);
  
  String data = "{\"ADC\":\""+String(a)+"\", \"Temperature\":\""+ String(temperature) +"\", \"Humidity\":\""+ String(humidity) +"\"}";
  server.send(200, "text/plane", data); //Send values JSON to client ajax request

  Serial.print("\t Spannung A0: ");
  Serial.print(a, 2);
  Serial.print("Luftfeuchtigkeit: ");
  Serial.print(humidity, 1);
  Serial.print("\t Temperatur: ");
  Serial.println(temperature, 1);
  
  digitalWrite(LED_OB,LOW); //LED_OB OFF
}



/**
 ******************************************************************************
 * \brief   setup WiFi connection and server
 *
 * \param   -
 * \return  -
 */
void webInit(void){
  server.on("/", handleRoot);      //Which routine to handle at root location. This is display page
  server.on("/LoliReadSensorsFunc", handleSensors); //This page is called by java Script AJAX
  server.begin();                  //Start server
  Serial.println("HTTP server started");
}
 

/**
 ******************************************************************************
 * \brief   print WiFi status to the console
 *
 * \param   -
 * \return  -
 */
void webStatus(void){
  Serial.println("webStatus not available");
}












 
