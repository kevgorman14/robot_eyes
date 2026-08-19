#pragma once

#include<Arduino.h>

enum MoodState {
    MOOD_NEUTRAL,
    MOOD_HAPPY,
    MOOD_EXCITED,
    MOOD_SHY,
    MOOD_SLEEPY,
    MOOD_BORED,
    MOOD_ASLEEP
};

void moodInit();
void moodUpdate();

void updateSleepTimer();

void setMood(MoodState mood);
MoodState getMood();
const char* moodName();

void moodKevinSeen();
void moodUnknownSeen();
void moodNoFace();