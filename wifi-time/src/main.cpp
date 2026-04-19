#include <WiFi.h>
#include "time.h"
#include "secrets.h"

// NTP settings
const char *ntpServer = "bh.pool.ntp.org";
const long gmtOffset_sec = 3 * 60 * 60; // Bahrain GMT+3
const int daylightOffset_sec = 0;

// LED
#define LED_PIN 21

// timing
unsigned long lastBlink = 0;
bool ledState = false;

bool tryConnect(const char *ssid, const char *pass, unsigned long timeoutMs)
{
    WiFi.begin(ssid, pass);
    unsigned long start = millis();
    while (millis() - start < timeoutMs)
    {
        if (WiFi.status() == WL_CONNECTED)
        {
            Serial.printf("\nConnected to %s\n", ssid);
            return true;
        }
        delay(200);
        Serial.print(".");
    }
    Serial.printf("\nFailed to connect to %s\n", ssid);
    return false;
}

void setup()
{
    Serial.begin(115200);
    delay(1000);

    pinMode(LED_PIN, OUTPUT);

    const unsigned long perNetworkTimeout = 5000; // ms
    for (size_t i = 0; i < wifiCredsCount; ++i)
    {
        Serial.printf("Trying network: %s\n", wifiCreds[i].ssid);
        if (tryConnect(wifiCreds[i].ssid, wifiCreds[i].pass, perNetworkTimeout))
            break;
    }

    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("All saved networks failed to connect.");
        // optional: start AP or captive portal here
    }
    else
    {
        configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
        Serial.println("Time initialized");
    }
}

void loop()
{
    // ===== LED behavior =====
    if (WiFi.status() != WL_CONNECTED)
    {
        digitalWrite(LED_PIN, HIGH); // solid ON if not connected
    }
    else
    {
        // blink every 1 second
        if (millis() - lastBlink > 1000)
        {
            ledState = !ledState;
            digitalWrite(LED_PIN, ledState);
            lastBlink = millis();
        }
    }

    // ===== Time print =====
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
