/*
  BatteryMonitor.h

  BatteryMonitor for Heltec Wifi Lora 32 (v2)
 
 */
#include <Arduino.h>
#ifndef __BATTERY_MONITOR_INTERFACE
#define __BATTERY_MONITOR_INTERFACE
 
#include "HAL.h"

#define BATTERY_MONITOR_PIN 37   // Define the pin for the on board battery monitor
#define FullBattery 3700 //liPo battery is 3700mv when battery is fully charged.



uint16_t getBatteryVoltage();

#endif //__BATTERY_MONITOR_INTERFACE