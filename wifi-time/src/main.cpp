#include <WiFi.h>
#include "time.h"
#include "secrets.h"

// NTP settings
const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3 * 60 * 60; // Bahrain GMT+3
const int daylightOffset_sec = 0;

void setup()
{
    Serial.begin(115200);
    delay(1000);

    WiFi.begin(ssid, password);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected!");

    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    Serial.println("Time initialized");
}

void loop()
{
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Failed to get time");
        delay(1000);
        return;
    }
    Serial.println(&timeinfo, "%Y-%m-%d %H:%M:%S");
    delay(1000);
}