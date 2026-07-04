#pragma once

#include<Arduino.h>

enum MoodState {
    MOOD_NEUTRAL,
    MOOD_HAPPY,
    MOOD_EXCITED,
    MOOD_SHY,
    MOOD_SLEEPY,
    MOOD_BORED
};

void moodInit();
void moodUpdate();

void setMood(MoodState mood);
MoodState getMood();
const char* moodName();

void moodKevinSeen();
void moodUnknownSeen();
void moodNoFace();