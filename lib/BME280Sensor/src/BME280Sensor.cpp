#include "BME280Sensor.h"

Adafruit_BME280 bme; // I2C

bool InitBME() {
  bool bme_status;
  bme_status = bme.begin(0x76);  //address either 0x76 or 0x77
  if (!bme_status) {
      Serial.println("Could not find a valid BME280 sensor, check wiring!");
  } else {

    //my best way to get correct indoor temperatures
  
    bme.setSampling(Adafruit_BME280::MODE_FORCED,
                    Adafruit_BME280::SAMPLING_X16,  // temperature
                    Adafruit_BME280::SAMPLING_X1, // pressure
                    Adafruit_BME280::SAMPLING_X1,  // humidity
                    Adafruit_BME280::FILTER_X16,
                    Adafruit_BME280::STANDBY_MS_0_5 );
  }
  return bme_status;
}

void forceMeasurement(){
  bme.takeForcedMeasurement();
}

float getTemperatureC(){
  float temp = bme.readTemperature();
  temp = temp + TEMP_CORR;
  return temp;
}

float getTemperatureF(){
  
  return (getTemperatureC() * 9/5) + 32;
}

float getHumidity(){
  return bme.readHumidity();
}

float getAltitude(){
  return bme.readAltitude(SEALEVELPRESSURE_HPA);
}

float getPressure(){
  return bme.readPressure() / 100.0F;
}

float getQNHPressure(){
  return (((getPressure() * 100.0)/pow((1-((float)(ELEVATION))/44330), 5.255))/100.0);

}