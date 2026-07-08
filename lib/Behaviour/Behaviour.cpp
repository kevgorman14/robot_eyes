#include "Behaviour.h"

#include "Mood.h"
#include "Animations.h"
#include "Motion.h"
#include "Servos.h"
#include "Globals.h"
#include "Config.h"

static unsigned long lastKevinEvent = 0;
static unsigned long lastUnknownEvent = 0;
static unsigned long lastIdleCheck = 0;

static const unsigned long KEVIN_COOLDOWN = 15000;
static const unsigned long UNKNOWN_COOLDOWN = 10000;
static const unsigned long IDLE_CHECK_TIME = 1000;

void behaviourInit()
{
    lastKevinEvent = 0;
    lastUnknownEvent = 0;
    lastIdleCheck = millis();

    noFaceActive = false;
    noFaceCycle = 0;
    noFaceJustLooked = false;
    noFaceStart = 0;
}

void behaviourSetMood(MoodState mood)
{
    noFaceActive = false;
    lastInteractionTime = millis();
    setMood(mood);
}

void behaviourEventKevin()
{
    unsigned long now = millis();
    lastInteractionTime = now;

    noFaceActive = false;
    noFaceCycle = 0;

    if (now - lastKevinEvent < KEVIN_COOLDOWN) {
        setMood(MOOD_HAPPY);
        return;
    }

    lastKevinEvent = now;

    setMood(MOOD_HAPPY);

    if (random(100) < 50) {
        animHappy(1);
    } else {
        animLegWaveHappy(1);
    }
}

void behaviourEventUnknown()
{
    unsigned long now = millis();
    lastInteractionTime = now;

    noFaceActive = false;

    if (now - lastUnknownEvent < UNKNOWN_COOLDOWN) {
        setMood(MOOD_SHY);
        return;
    }

    lastUnknownEvent = now;

    setMood(MOOD_SHY);
    animShy(1);
}

void behaviourEventNoFace()
{
    unsigned long now = millis();

    if (!noFaceActive) {
        noFaceActive = true;
        noFaceStart = now;
        noFaceCycle = 0;
        noFaceJustLooked = false;

        Serial.println("[BEHAVIOUR] No face active");
    }
}

void behaviourEventTurn(int amount)
{
    noFaceActive = false;
    lastInteractionTime = millis();

    int target = constrain(lastKnownHeadPos + amount, head_left, head_right);

    smoothMove(HEAD_YAW, target, 300);
    lastKnownHeadPos = target;
}

static void handleNoFaceSearch()
{
    if (!noFaceActive) return;

    unsigned long now = millis();

    if (now - noFaceStart < 10000) return;

    int rememberedPos = constrain(lastKnownHeadPos, head_left, head_right);

    if (noFaceCycle == 0) {
        Serial.println("[BEHAVIOUR] No face: looking last known position");

        smoothMove(HEAD_YAW, rememberedPos, 600);

        noFaceCycle++;
        noFaceStart = now;
    }
    else if (noFaceCycle == 1) {
        Serial.println("[BEHAVIOUR] No face: small search");

        smoothMove(HEAD_YAW, constrain(rememberedPos - 15, head_left, head_right), 600);
        smoothMove(HEAD_YAW, constrain(rememberedPos + 15, head_left, head_right), 600);
        smoothMove(HEAD_YAW, rememberedPos, 600);

        noFaceCycle++;
        noFaceStart = now;
    }
    else if (noFaceCycle == 2) {
        Serial.println("[BEHAVIOUR] No face: wide search");

        smoothMove(HEAD_YAW, head_left, 800);
        smoothMove(HEAD_YAW, head_right, 800);
        smoothMove(HEAD_YAW, neutral_head_yaw, 800);

        noFaceCycle++;
        noFaceStart = now;
    }
    else {
        Serial.println("[BEHAVIOUR] No face: bored");

        noFaceActive = false;
        setMood(MOOD_BORED);
    }
}

static void handleIdleBehaviour()
{
    unsigned long now = millis();

    if (now - lastIdleCheck < IDLE_CHECK_TIME) return;
    lastIdleCheck = now;

    unsigned long inactiveTime = now - lastInteractionTime;

    if (inactiveTime > 60000) {
        if (getMood() != MOOD_SLEEPY) {
            setMood(MOOD_SLEEPY);
        }
    }
    else if (inactiveTime > 20000) {
        if (getMood() != MOOD_BORED) {
            setMood(MOOD_BORED);
        }
    }
}

void behaviourUpdate()
{
    handleNoFaceSearch();
    // handleIdleBehaviour();
}