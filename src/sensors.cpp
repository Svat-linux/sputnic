#include "sensors.h"

MPU6050 accelgyro;
HMC5883L mag;
Adafruit_BMP085 bmp;
Adafruit_AS726x ams;

int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t mx, my, mz;

uint16_t sensorValues[AS726x_NUM_CHANNELS];

void sensors_init() {
    Wire.begin();
    
    accelgyro.setI2CMasterModeEnabled(false);
    accelgyro.setI2CBypassEnabled(true);
    accelgyro.setSleepEnabled(false);
    
    accelgyro.initialize();
    mag.initialize();
    bmp.begin();
    ams.begin();

    pinMode(uvSensorsPin, INPUT);
}

String getMagnetometerData() {
    mag.getHeading(&mx, &my, &mz);
    return String(mx) + ", " + String(my) + ", " + String(mz);
}

String getAccelerometerData() {
    accelgyro.getAcceleration(&ax, &ay, &az);
    return String(ax) + ", " + String(ay) + ", " + String(az);
}

String getGyroscopeData() {
    accelgyro.getRotation(&gx, &gy, &gz);
    return String(gx) + ", " + String(gy) + ", " + String(gz);
}

float getPressure() {
    return bmp.readPressure();
}

uint8_t getColorTemperature() {
    return ams.readTemperature();
}

String getColorDataFormatted() {
    ams.startMeasurement();
    
    bool rdy = false;
    while(!rdy) {
        delay(5);
        rdy = ams.dataReady();
    }
    
    ams.readRawValues(sensorValues);
    
    String result = "Violet: " + String(sensorValues[AS726x_VIOLET]) +
                   ", Blue: " + String(sensorValues[AS726x_BLUE]) +
                   ", Green: " + String(sensorValues[AS726x_GREEN]) +
                   ", Yellow: " + String(sensorValues[AS726x_YELLOW]) +
                   ", Orange: " + String(sensorValues[AS726x_ORANGE]) +
                   ", Red: " + String(sensorValues[AS726x_RED]);
    
    return result;
}

String getColorDataRaw() {
    ams.startMeasurement();
    
    bool rdy = false;
    while(!rdy) {
        delay(5);
        rdy = ams.dataReady();
    }
    
    ams.readRawValues(sensorValues);
    
    String result = String(sensorValues[AS726x_VIOLET]) + "," +
                   String(sensorValues[AS726x_BLUE]) + "," +
                   String(sensorValues[AS726x_GREEN]) + "," +
                   String(sensorValues[AS726x_YELLOW]) + "," +
                   String(sensorValues[AS726x_ORANGE]) + "," +
                   String(sensorValues[AS726x_RED]);
    
    return result;
}

float uvIndec(){
    int sensorValue = analogRead(uvSensorsPin);
    float uvVoltage = sensorValue * (5.0 / 1023.0);
    float uvIndex = uvVoltage / 0.1;
    return uvIndex;
}