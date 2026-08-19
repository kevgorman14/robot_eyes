#pragma once
#include <Arduino.h>

void setupServoLimits();
int angleToPWM(int angle);
String jointName(int channel);
bool isConfiguredChannel(int channel);
int clampServoAngle(int channel, int angle);
void setPWMForChannel(int channel, int pwmVal);
void writeServo(int channel, int angle);
void moveNow(int channel, int angle);
void smoothMove(int channel, int target, int duration);
void printHelp();
void printLimits();
void poseSit();
void poseStand();
// void turnHeadLeft(int amount);
// void turnHeadRight(int amount);
// void lookUp(int amount);
// void lookDown(int amount);
void processEvent(String evt);
void greetKevin(unsigned long awayTime);
void addEnergy(int amount);
void updateEnergy();
void ensureSittingForSittingAnim();
void handleSafety();
void wave();
void hide();
void idle();
