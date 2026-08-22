#include <Arduino.h>
#include "Sensors.h"
#include "Config.h"

static bool flexLive = false;
static unsigned long lastFlexPrint = 0;

constexpr unsigned long FLEX_PRINT_INTERVAL = 50;// milliseconds

void sensorsInit() {
    pinMode(RIGHT_KNEE_FLEX_PIN, INPUT);
    pinMode(LEFT_KNEE_FLEX_PIN, INPUT);
}

int readRightKneeFlex() {
    return analogRead(RIGHT_KNEE_FLEX_PIN);
}

int readLeftKneeFlex() {
    return analogRead(LEFT_KNEE_FLEX_PIN);
}

void startFlexLive() {
    flexLive = true;
    Serial.println("[FLEX] Live plotting started.");
}

void stopFlexLive() {
    flexLive = false;
    Serial.println("[FLEX] Live plotting stopped.");
}

void sensorsUpdate() {
    if (!flexLive) return;
    unsigned long now = millis();
    if (now - lastFlexPrint <= FLEX_PRINT_INTERVAL) {
        return;
    }
    lastFlexPrint = now;
    Serial.print("> LeftFlex: ");
    Serial.println(readLeftKneeFlex());
    Serial.print("> RightFlex: ");
    Serial.println(readRightKneeFlex());
}
