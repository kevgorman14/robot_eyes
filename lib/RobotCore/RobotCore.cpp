#pragma once
#include <Arduino.h>

void handleMoodAndDecay();
bool runAnimationNow(String name, int cycles);
void handleAnimations();
int readNumberAfter(String text, int startIndex, int &nextIndex);
bool handleManualServoCommand(String cmd);
void stopAllBehaviour();
void processCommand(String cmd);
