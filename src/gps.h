#ifndef GPS_H
#define GPS_H

#include <Arduino.h>
#include <TinyGPS++.h>

void gps_init();
void gps_update();
float gps_get_latitude();
float gps_get_longitude();
float gps_get_altitude();
int gps_get_satellites();
float gps_get_speed_kmh();
String gps_get_raw_data();
String gps_get_time();
String gps_get_date();

#endif