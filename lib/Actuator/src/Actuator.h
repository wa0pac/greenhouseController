/*
  Actuator.h

  Actuator for Heltec Wifi Lora 32 (v2)
 
 */

#ifndef __ACTUATOR_INTERFACE
#define __ACTUATOR_INTERFACE
 
#define ACTUATOR_STATUS_EXTENDED   3
#define ACTUATOR_STATUS_RETRACTED  0
#define ACTUATOR_STATUS_EXTENDING  2
#define ACTUATOR_STATUS_RETRACTING 1



#define ACTUATOR_EXTEND_PIN 12   // Define the pin for Opening Actuator
#define ACTUATOR_RETRACT_PIN 13 // Define the pin for Closing the Actuator


int getActuatorStatus();
void initActuator();
void extendActuator();
void retractActuator();
void stopActuator();
void checkActuator();

#endif //__ACTUATOR_INTERFACE