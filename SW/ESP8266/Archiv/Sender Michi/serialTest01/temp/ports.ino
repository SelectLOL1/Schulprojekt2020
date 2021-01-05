
#include "lolinIO.h"
#include "ports.h"


/**
 ******************************************************************************
 * \brief   Main init function. Calls initalization functions of all modules
 *
 * \param   -
 * \return  -
 */
  

void initPorts(void) {
      //outputs
      pinMode(LED1,     OUTPUT);           
      pinMode(LED2,     OUTPUT);           
      pinMode(LED3,     OUTPUT);           
      pinMode(LED4,     OUTPUT);           
      pinMode(LED5,     OUTPUT);           
      pinMode(READ,     OUTPUT);
      pinMode(SHUTTER,  OUTPUT);
      pinMode(CLR_PIX,  OUTPUT);
      // Init inputs
      pinMode(DATA_RDY, INPUT);
      pinMode(TASTER,   INPUT);
  }

  void initSerial(void) {
      Serial.begin(BAUDRATE);      // open the serial port:    
      Serial.print("\t \t Version:");
      Serial.print(VERSION);
      Serial.print("\t");
  }
  

  static void serialTest(void) {
    int incomingByte = 0;
    if (Serial.available() > 0) {
      // read the incoming byte:
      incomingByte = Serial.read();
    
      // say what you got:
      Serial.print("I received: ");
      Serial.println(incomingByte);
    }
  } 
