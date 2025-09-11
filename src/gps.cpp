#include "gps.h"

TinyGPSPlus gps;

String rawData = "";

void gps_init() {
    Serial3.begin(9600);  
}

void gps_update() {
    while (Serial3.available() > 0) {
        char c = Serial3.read();
        
        rawData += c;
        if (rawData.length() > 200) {
            rawData = rawData.substring(rawData.length() - 200);
        }
        
        gps.encode(c);
    }
}

float gps_get_latitude() {
    return gps.location.lat();
}

float gps_get_longitude() {
    return gps.location.lng();
}

float gps_get_altitude() {
    return gps.altitude.meters();
}

int gps_get_satellites() {
    return gps.satellites.value();
}

float gps_get_speed_kmh() {
    return gps.speed.kmph();
}

String gps_get_raw_data() {
    return rawData;
}

String gps_get_time() {
    char timeStr[9];
    snprintf(timeStr, sizeof(timeStr), "%02d:%02d:%02d", 
            gps.time.hour(), gps.time.minute(), gps.time.second());
    return String(timeStr);
}

String gps_get_date() {
    char dateStr[11];
    snprintf(dateStr, sizeof(dateStr), "%02d/%02d/%04d", 
            gps.date.day(), gps.date.month(), gps.date.year());
    return String(dateStr);
}