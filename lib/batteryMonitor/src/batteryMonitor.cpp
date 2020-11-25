

#include "batteryMonitor.h"

float batteryConversion = 0.0029825; // 0.001953125;
uint16_t MUL = 1000;
uint16_t MMUL = 100;

uint16_t getBatteryVoltage()
{
  Heltec.VextON();
  uint16_t volts = analogRead( BATTERY_MONITOR_PIN ) * batteryConversion  * MUL; // convert to millivolts
  Heltec.VextOFF();
  return volts;
}