/*
  BME280 Sensor header file
 
 */

#ifndef __BME280_SENSOR_INTERFACE
#define __BME280_SENSOR_INTERFACE
 
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// BME280
#define SEALEVELPRESSURE_HPA (1010) //Check Internet for MSL pressure at our place to calc your elevation mASL
#define TEMP_CORR (0)              //Manual correction of temp sensor (mine reads 2 degrees C too high)
#define ELEVATION (296)             //Enter your elevation mASL to calculate MSL pressure (QNH) at your place





bool InitBME();
void forceMeasurement();
float getTemperatureC();
float getTemperatureF();
float getHumidity();
float getAltitude();
float getPreasure();
float getQNHPressure();
#endif //__BME280_SENSOR_INTERFACE