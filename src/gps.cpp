#include "gps.h"

TinyGPSPlus gps;

#define RAW_DATA_BUFFER_SIZE 200
char rawDataBuffer[RAW_DATA_BUFFER_SIZE + 1];
int rawDataIndex = 0;

void gps_init() {
    Serial3.begin(9600);
    memset(rawDataBuffer, 0, sizeof(rawDataBuffer));
    rawDataIndex = 0;
}

void gps_update() {
    while (Serial3.available() > 0) {
        char c = Serial3.read();
        
        if (rawDataIndex < RAW_DATA_BUFFER_SIZE) {
            rawDataBuffer[rawDataIndex++] = c;
        } else {
            memmove(rawDataBuffer, rawDataBuffer + 1, RAW_DATA_BUFFER_SIZE - 1);
            rawDataBuffer[RAW_DATA_BUFFER_SIZE - 1] = c;
        }
        
        gps.encode(c);
    }
    rawDataBuffer[rawDataIndex] = '\0';
}

float gps_get_latitude() {
    if (gps.location.isValid()) {
        return gps.location.lat();
    }
    return 0.0;
}

float gps_get_longitude() {
    if (gps.location.isValid()) {
        return gps.location.lng();
    }
    return 0.0;
}

float gps_get_altitude() {
    if (gps.altitude.isValid()) {
        return gps.altitude.meters();
    }
    return 0.0;
}

int gps_get_satellites() {
    if (gps.satellites.isValid()) {
        return gps.satellites.value();
    }
    return 0;
}

float gps_get_speed_kmh() {
    if (gps.speed.isValid()) {
        return gps.speed.kmph();
    }
    return 0.0;
}

String gps_get_raw_data() {
    return String(rawDataBuffer);
}

String gps_get_time() {
    if (gps.time.isValid()) {
        char timeStr[9];
        snprintf(timeStr, sizeof(timeStr), "%02d:%02d:%02d", 
                gps.time.hour(), gps.time.minute(), gps.time.second());
        return String(timeStr);
    }
    return "00:00:00";
}

String gps_get_date() {
    if (gps.date.isValid()) {
        char dateStr[11];
        snprintf(dateStr, sizeof(dateStr), "%02d/%02d/%04d", 
                gps.date.day(), gps.date.month(), gps.date.year());
        return String(dateStr);
    }
    return "01/01/2000";
}

bool gps_is_valid() {
    return gps.location.isValid() && gps.time.isValid() && gps.date.isValid();
}

bool gps_location_is_valid() {
    return gps.location.isValid();
}

bool gps_time_is_valid() {
    return gps.time.isValid();
}

bool gps_date_is_valid() {
    return gps.date.isValid();
}

String gps_get_debug_info() {
    String info = "";
    info += "Fix: ";
    info += gps_location_is_valid() ? "YES" : "NO";
    info += " | Sats: ";
    info += String(gps_get_satellites());
    info += " | HDOP: ";
    if (gps.hdop.isValid()) {
        info += String(gps.hdop.value() / 100.0, 1);
    } else {
        info += "N/A";
    }
    info += " | Age: ";
    info += String(gps.location.age());
    return info;
}