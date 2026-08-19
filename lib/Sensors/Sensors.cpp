#include <Arduino.h>
#include "Sensors.h"
#include "Config.h"

void sensorsInit() {
    pinMode(RIGHT_KNEE_FLEX_PIN, INPUT);
}

int readRightKneeFlex() {
    return analogRead(RIGHT_KNEE_FLEX_PIN);
}