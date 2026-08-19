#pragma once

#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>

extern Adafruit_PWMServoDriver pwmLower;
// extern Adafruit_PWMServoDriver pwmUpper;

void servoInit();
void setupServoLimits();

void smoothMove(int channel, int target, int duration);
int clampServoAngle(int channel, int angle);
bool isConfiguredChannel(int channel);
int angleToPWM(int angle);
void setPWMForChannel(int channel, int pwmVal);