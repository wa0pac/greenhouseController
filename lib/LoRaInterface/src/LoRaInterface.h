/*
 * LoRaInterface.ino 
 * 
 * Implements all the LoRa communication functions.
 * 
 * (c) 2019 Lee Dowthwaite. All Rights Reserved.
 */
#include <Arduino.h>
#include <heltec.h>

#ifndef __LORA_INTERFACE
#define __LORA_INTERFACE

#define MAX_LORA_PAYLOAD  256

#define MIN_SPREAD_FACTOR (7)   // technically it's 6 but in EU band all channels use 7-12
#define MAX_SPREAD_FACTOR (12)

#define MAX_TX_POWER      (20)

void configureLoRa();
String *checkRxBuffer();
int rssi();
void sendIfReady();
void sendLoRaMessage( String message );

#endif //  __LORA_INTERFACE