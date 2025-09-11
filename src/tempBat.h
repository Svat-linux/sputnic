#ifndef TEMPBAT_H
#define TEMPBAT_H

#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 10
#define CURRENT_SENSOR_PIN A11
#define BatHeatCtrl 11

// Параметры датчика тока ACS712
#define VOLTAGE_DIVIDER_RATIO 0.5f    
#define ACS712_SENSITIVITY 0.185f    
#define ACS712_ZERO_CURRENT 2.5f     
#define ADC_REFERENCE 5.0f          
#define ADC_RESOLUTION 1024.0f       

void tempBatStart();
float tempBatData();
float getCurrent();  

#endif