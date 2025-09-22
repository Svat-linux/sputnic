#include "main.h"

Servo esc;
unsigned long previousMotorMillis = 0;
bool motorRunning = false;
unsigned long motorStartTime = 0;
bool firstStart = true;

void setup() {
  Serial.begin(9600);

  esc.attach(escPin);
  delay(10);
  esc.writeMicroseconds(MIN_SIGNAL);
  delay(5000);
  
  previousMotorMillis = millis() - WORK_INTERVAL;

  tempBatStart();
  gps_init();
  sensors_init();
  scanI2C();

  Serial1.begin(9600);
  Serial2.begin(9600);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop() {
  motorControl();

  gps_update();

  float temperature = tempBatData();
  float current = getCurrent();  

  String magData = getMagnetometerData();
  String accelData = getAccelerometerData();
  String gyroData = getGyroscopeData();

  float pressure = getPressure();
  float altitude = getAltitude();

  uint8_t colorTemp = getColorTemperature();
  String colorFormatted = getColorDataFormatted();
  String colorRaw = getColorDataRaw();

  // // if (temperature <= 16)
  // // {
  // //   digitalWrite(BatHeatCtrl, 1);
  // // }
  // // else if (temperature >= 20)
  // // {
  // //   digitalWrite(BatHeatCtrl, 0);
  // // }

  // Serial.print("Temperature: ");
  // Serial.print(temperature);
  // Serial.print(" C, Current: ");
  // Serial.print(current, 3); 
  // Serial.println(" A");

  // // // Serial.println("gg");

  // Serial.print("Latitude: "); Serial.println(gps_get_latitude(), 6);
  // Serial.print("Longitude: "); Serial.println(gps_get_longitude(), 6);
  // Serial.print("Altitude: "); Serial.println(gps_get_altitude());
  // // Serial.print("Speed: "); Serial.println(gps_get_speed_kmh());
  // // Serial.print("Satellites: "); Serial.println(gps_get_satellites());
  // // Serial.print("Time: "); Serial.println(gps_get_time());
  // // Serial.print("Date: "); Serial.println(gps_get_date());
  // // Serial.print("Raw data: "); Serial.println(gps_get_raw_data());

  // Serial.print("Magnetometer: "); Serial.println(magData);
  // Serial.print("Accelerometer: "); Serial.println(accelData);
  // Serial.print("Gyroscope: "); Serial.println(gyroData);
  // Serial.print("Pressure: "); Serial.print(pressure); Serial.println(" Pa");
  // Serial.print("getAltitude: "); Serial.print(altitude); Serial.println(" M");

  
  // Serial.print("Color Temp: "); Serial.print(colorTemp); Serial.println(" C");
  // // Serial.print("Color Formatted: "); Serial.println(colorFormatted);
  // Serial.print("Color Raw: "); Serial.println(colorRaw);

  // Serial.print("UV IDENCITY: "); Serial.println(uvIndec());

  Serial2.print("T:" + String(temperature, 2) + ";C:" + String(current, 3) + ";");
  Serial2.print("La:" + String(gps_get_latitude(), 6) + ";Lo:" + String(gps_get_longitude(), 6));

  Serial1.print("T:" + String(temperature, 2) + ";C:" + String(current, 3) + ";");
  Serial1.print("La:" + String(gps_get_latitude(), 6) + ";Lo:" + String(gps_get_longitude(), 6));
  delay(1000);

  Serial2.print("Al:" + String(altitude, 2) + ";M:" + String(magData) + ";");

  Serial1.print("Al:" + String(altitude, 2) + ";M:" + String(magData) + ";");
  delay(1000);

  Serial2.print("A:" + String(accelData) + ";G:" + String(gyroData));

  Serial1.print("A:" + String(accelData) + ";G:" + String(gyroData));
  delay(1000);

  Serial2.print("P:" + String(pressure, 2) + ";CT:" + String(colorTemp) + ";");
  Serial2.print("CR:" + String(colorRaw) + ";UV:" + String(uvIndec(), 2));

  Serial1.print("P:" + String(pressure, 2) + ";CT:" + String(colorTemp) + ";");
  Serial1.print("CR:" + String(colorRaw) + ";UV:" + String(uvIndec(), 2));
  delay(1000);
}

void motorControl() {
  unsigned long currentMillis = millis();
  
  if ((currentMillis - previousMotorMillis >= WORK_INTERVAL || firstStart) && !motorRunning) {
    esc.writeMicroseconds(WORK_SIGNAL);
    motorRunning = true;
    motorStartTime = currentMillis;
    previousMotorMillis = currentMillis;
  }
  
  if (motorRunning && (currentMillis - motorStartTime >= WORK_DURATION)) {
    esc.writeMicroseconds(MIN_SIGNAL);
    motorRunning = false;
    firstStart = false;
  }
}

void scanI2C() {
    byte error, address;
    int nDevices = 0;
    
    Serial.println("Scanning I2C bus...");
    
    for(address = 1; address < 127; address++ ) {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
        
        if (error == 0) {
            Serial.print("I2C device found at address 0x");
            if (address < 16) Serial.print("0");
            Serial.print(address, HEX);
            
            Serial.println();
            nDevices++;
        }
    }
    
    if (nDevices == 0) {
        Serial.println("No I2C devices found - check wiring!");
    }
}