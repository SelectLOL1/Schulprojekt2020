
#include "wifi.h"
#include "serialTest01.h" //main.h




/**
 ******************************************************************************
 * \brief   connect to the server
 *
 * \param   -
 * \return  -
 */
static void connectWiFiClient(void){ 
    Serial.print("connect WiFi Client...");
    WiFi.hostname(deviceName);                   // DHCP Hostname (useful for finding device for static lease)
    WiFi.config(staticIP, subnet, gateway);      //server.config(staticIP, subnet, gateway, dns);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);                  //Connect to your WiFi router
    
    Serial.println(""); 
    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    //If connection successful show IP address in serial monitor
    Serial.print("Connected to ");
    Serial.println(ssid);
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
  WiFi.softAP(ssid, password);
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
