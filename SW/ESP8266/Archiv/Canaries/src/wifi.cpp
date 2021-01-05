#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "wifi.h"
#include "main.h" //main.h




// LOGIN
//const char* ssid = WLAN_NAME;
//const char* password = WLAN_PWD;


/**
 ******************************************************************************
 * \brief   connect to the server
 *
 * \param   -
 * \return  -
 */
static void connectWiFiClient(void){
    Serial.print("connect WiFi Client...");


    IPAddress staticIP(192, 168,  137, boardid); //ESP static ip
    IPAddress gateway( 192, 168,  137,   1);     //IP Address of your WiFi Router (Gateway)
    IPAddress subnet(  255, 255,  255,   0);       //Subnet mask


    WiFi.hostname(BOARDNAME);                    // DHCP Hostname (useful for finding device for static lease)
    //WiFi.config(staticIP, gateway, subnet, gateway);
    WiFi.config(staticIP, subnet, gateway);      //server.config(staticIP, subnet, gateway, dns);
    WiFi.mode(WIFI_STA);
    WiFi.begin(WLAN_NAME, WLAN_PWD);                  //Connect to your WiFi router

    Serial.println("");
    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    //If connection successful show IP address in serial monitor
    Serial.print("Connected to ");
    Serial.println(WLAN_NAME);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());  //IP address assigned to your ESP
}

/**
 ******************************************************************************
 * \brief   print WiFi status to the console
 *
 * \param   -
 * \return  -
 */
static void connectWiFiAP(void)
{
  WiFi.mode(WIFI_AP);
  WiFi.softAP(WLAN_NAME, WLAN_PWD);
  Serial.println("AP started");
  Serial.println("IP address: " + WiFi.softAPIP().toString());
}



/**
 ******************************************************************************
 * \brief   print WiFi status to the console
 *
 * \param   -
 * \return  -
 */
void wifiInit(void){

    Serial.setDebugOutput(MODE);  //Enable for debug use
    connectWiFiClient();
    //connectWiFiAP();
}


/**
 ******************************************************************************
 * \brief   print WiFi status to the console
 *
 * \param   -
 * \return  -
 */
void wifiStatus(void){
  WiFi.printDiag(Serial);
}
