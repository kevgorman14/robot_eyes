#pragma  once

#include <Arduino.h>
#include "Mood.h"

void behaviourInit();
void behaviourUpdate();

void behaviourSetMood(MoodState mood);

void behaviourEventKevin();
void behaviourEventUnknown();
void behaviourEventNoFace();
void behaviourEventTurn(int amount);