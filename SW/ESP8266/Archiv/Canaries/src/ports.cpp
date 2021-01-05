
#include "ports.h"
#include "lolinIO.h"
#include "Arduino.h"

/**
 ******************************************************************************
 * \brief   Main init function. Calls initalization functions of all modules
 *
 * \param   -
 * \return  -
 */


  void portsInit(void) {
        //outputs

        pinMode(LED_OB,OUTPUT); //Onboard LED_OB
        //pinMode(WHATEVER1, OUTPUT);
        // Init inputs
        //pinMode(WHATEVER2, INPUT);
  }
