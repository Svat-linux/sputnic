#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <HMC5883L.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_AS726x.h>

#define uvSensorsPin A2

void sensors_init();
String getMagnetometerData();
String getAccelerometerData();
String getGyroscopeData();
float getPressure();
uint8_t getColorTemperature();
String getColorDataFormatted();
String getColorDataRaw();
float uvIndec();

#endif