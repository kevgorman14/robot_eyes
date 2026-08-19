#pragma once

#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include "Config.h"

extern Adafruit_PWMServoDriver pwmLower;
// extern Adafruit_PWMServoDriver pwmUpper;

extern int servoMin[16];
extern int servoMax[16];
extern int neutralAngles[16];

extern bool autonomousMode;
extern bool animationActive;
extern bool oneShotActive;
extern bool isSitting;
extern bool isStanding;

extern String currentMood;
extern String currentAnimation;

extern int energyLevel;
extern int boredStretchCount;

extern unsigned long lastInteractionTime;
extern unsigned long lastStandTime;
extern unsigned long lastKevinSeen;
extern unsigned long lastKevinGreeting;

extern bool hasSeenKevinSinceBoot;

extern bool noFaceActive;
// extern bool noFaceJustLooked;
extern int noFaceCycle;
extern unsigned long noFaceStart;

// extern int lastKnownHeadPos;