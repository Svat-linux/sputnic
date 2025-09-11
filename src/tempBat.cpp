#include "tempBat.h"  

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void tempBatStart() {
    sensors.begin();
    pinMode(CURRENT_SENSOR_PIN, INPUT);
}

float tempBatData() {
    sensors.requestTemperatures();
    float temperature = sensors.getTempCByIndex(0);
    
    return temperature;
}

float getCurrent() {
    int adcValue = analogRead(CURRENT_SENSOR_PIN);
    float voltage = (adcValue / ADC_RESOLUTION) * ADC_REFERENCE;
    
    voltage = voltage / VOLTAGE_DIVIDER_RATIO;
    
    float current = (voltage - ACS712_ZERO_CURRENT) / ACS712_SENSITIVITY;
    
    if (abs(current) < 0.05) {
        current = 0.0;
    }
    
    return current;
}