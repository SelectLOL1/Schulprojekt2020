#include <Arduino.h>
#include "userrequest.h"
#include "wifi.h"
#include "lolinIO.h"           // General GPIO defines
#include "web.h"          // controls the communication over the web
#include "main.h" //main.h


char userrequestHandle(char state) {
    if (Serial.available() > 0) {     // act only when data received
      int incomingByte = Serial.read(); // read the incoming byte

      switch (incomingByte) {
        case 's':   // write state of the wifi to the console
                wifiStatus();
                break;

        case 'd':    // enable debug output
                Serial.println("At the moment not available");
                break;

        case 'r':    // reset
                Serial.println("RESET");
                return 3;

        case 'l':    // enable and set limit for whatever
                Serial.println("At the moment not available");
                break;

        case '1':
                Serial.println("Deepsleep ON");
                return 1;

        case '2':
                Serial.println("Deepsleep OFF");
                return 2;

        default:
                Serial.print("unknown command: ");
                Serial.println(incomingByte);
                Serial.println("");
                Serial.println(" s: show wiFi state \t d: enable debug mode \t r: reset");
                Serial.println(" 1: deepsleep ON    \t 2: deepsleep OFF     \t l: set new limit");
                Serial.println(" a: toggle alarm");
                break;
      }
    }
    return state;
}
