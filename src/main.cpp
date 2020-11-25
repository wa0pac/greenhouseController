/*
Example, how to read data from a BME280 (here: GY-BME280 5V/3.3V) and display the values on a HELTEC WIFI Kit 32 display
by 3KU_Delta (https://github.com/3KUdelta)
CREDITS:
Basic solution provided by itofficeeu https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series/issues/62 because Pin21 and Pin22
do not work for this purpose.
Adafrit´s library: 
  This is a library for the BME280 humidity, temperature & pressure sensor
  Designed specifically to work with the Adafruit BME280 Breakout
  ----> http://www.adafruit.com/products/2650
  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface. The device's I2C address is either 0x76 or 0x77.
  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!
  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
Libraries needed:
ThingPulse SSD1306 (https://github.com/ThingPulse/esp8266-oled-ssd1306)
General Adafruit Sensor (Arduino Library Manager)
Adafruit BME280 (Arduino Library Manager)
SoftwWire Steve Marple (Arduino Library Manager)
AsyncDelay Steve Marple (Arduino Library Manager)
Hardware settings Mac:
Heltec_WFIF_Kit_32,80MHz,921600 on /dev/cu.SLAB_USBtoUART
*/

#include <Arduino.h>
#include "HAL.h"
#include <SoftWire.h>
#include "batteryMonitor.h"
#include "BME280Sensor.h"
#include "Actuator.h"
#include "LoRaInterface.h"

#define PIN_SDA 4
#define PIN_SCL 15

SoftWire sw(PIN_SDA, PIN_SCL);
//SSD1306 display(0x3C, PIN_SDA, PIN_SCL);

AsyncDelay EnvDelay;


void setup() 
{
  configureBoard();
  Serial.begin(9600);
  Serial.printf("Starting...\r\n");
  configureLoRa();


  displayString( 0, 0, "Starting up ...");
  displayString( 0,1, "- and initializing.");
  delay(500);

  if(!InitBME()){
    clearDisplay();
    displayString( 0, 0, "No valid BME280 found");
    displayString( 0, 1, "Please check wiring!");
  }

  initActuator();
  EnvDelay.start(0, AsyncDelay::MILLIS);

}

void loop() 
{
  if( EnvDelay.isExpired() ) {
    clearDisplay();  // clear display buffer
    forceMeasurement();

    String message;
  
    // Print Board Voltage
    float batvolt = getBatteryVoltage();
    String tempvarbat = String("Batt: ") + (batvolt) + (" mv");
    //Serial.println(tempvarbat);
    float batVoltPlot = batvolt/1000.0;
    message = String(batVoltPlot) + " ";
    displayString( 0, 0, tempvarbat.c_str(), false);
    
    // Print temperature
    float tempF = getTemperatureF();
    String tempvar = String("Temp: ") + (tempF) + (" °F");
    //Serial.println(tempvar);
    message = message + String(tempF) + " ";
    displayString( 0, 1, tempvar.c_str(),false);
    
    // Print humidity
    float humi = getHumidity();
    tempvar = String("Hum: ") + (humi) + (" %");
    //Serial.println(tempvar);
    message = message + String(humi) + " ";
    displayString( 0, 2, tempvar.c_str(), false);

    //Display status of Actuator
    String tempStatus;
    switch( getActuatorStatus() ) {
      case ACTUATOR_STATUS_EXTENDED:
        tempStatus = "Window Open";
      break;
      case ACTUATOR_STATUS_EXTENDING:
        tempStatus = "Window Opening";
      break;
      case ACTUATOR_STATUS_RETRACTING:
        tempStatus = "Window Closing";
      break;
      case ACTUATOR_STATUS_RETRACTED:
        tempStatus = "Window Closed";
      break;
      default:
      break;
    }

    displayString(0,4, tempStatus.c_str(), true);
    

    message = message + String( getActuatorStatus() );
    sendLoRaMessage(message);
    Serial.println(message);

    //Open or close the Window based on temperature
    if( tempF > 80) {
      extendActuator();
    }
    if (tempF < 75) {
      retractActuator();
    }

    
    EnvDelay.start(5000, AsyncDelay::MILLIS);;
  }

  checkActuator();
//  delay(250);
 
}