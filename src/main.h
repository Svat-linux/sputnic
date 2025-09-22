#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include <Wire.h>
#include <Servo.h>
#include "tempBat.h" 
#include "gps.h"
#include "sensors.h"

const int escPin = 2;
const int MIN_SIGNAL = 1000;
const int WORK_SIGNAL = 1350;
const unsigned long WORK_DURATION = 10000;
const unsigned long WORK_INTERVAL = 5 * 60 * 1000;

extern Servo esc;
extern unsigned long previousMotorMillis;
extern bool motorRunning;
extern unsigned long motorStartTime;
extern bool firstStart;

void scanI2C();
void motorControl();

#endif