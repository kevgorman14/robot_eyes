#include "Mood.h"
#include "Animations.h"
#include "Motion.h"
#include "Eyes.h"
#include "Globals.h"

static MoodState currentMoodState = MOOD_NEUTRAL;

static unsigned long lastMoodChange = 0;
static unsigned long lastIdleAction = 0;

static const unsigned long BORED_TIME  = 20000;
static const unsigned long SLEEPY_TIME = 60000;
static const unsigned long IDLE_ACTION_TIME = 20000;

void moodInit() {
  currentMoodState = MOOD_NEUTRAL;
  lastMoodChange = millis();
  lastIdleAction = millis();

  currentMood = "NEUTRAL";
  lastInteractionTime = millis();
  energyLevel = 50;
}

void setMood(MoodState mood)
{
    currentMoodState = mood;
    lastMoodChange = millis();
    lastInteractionTime = millis();   // add this line

    switch (mood)
    {
        case MOOD_HAPPY:
            currentMood = "HAPPY";
            eyesSetExpression(EYES_HAPPY);
            break;

        case MOOD_EXCITED:
            currentMood = "EXCITED";
            eyesSetExpression(EYES_HAPPY);
            break;

        case MOOD_SHY:
            currentMood = "SHY";
            eyesSetExpression(EYES_SHY);
            break;

        case MOOD_SLEEPY:
            currentMood = "SLEEPY";
            eyesSetExpression(EYES_SLEEPY);
            break;

        case MOOD_BORED:
            currentMood = "BORED";
            eyesSetExpression(EYES_BORED);
            break;

        case MOOD_NEUTRAL:
        default:
            currentMood = "NEUTRAL";
            eyesSetExpression(EYES_NEUTRAL);
            break;
    }

    Serial.print("[MOOD] ");
    Serial.println(currentMood);
}

MoodState getMood() {
  return currentMoodState;
}

const char* moodName() {
  switch (currentMoodState) {
    case MOOD_HAPPY:   return "HAPPY";
    case MOOD_EXCITED: return "EXCITED";
    case MOOD_SHY:     return "SHY";
    case MOOD_SLEEPY:  return "SLEEPY";
    case MOOD_BORED:   return "BORED";
    default:           return "NEUTRAL";
  }
}

void moodKevinSeen() {
  lastInteractionTime = millis();
  energyLevel = min(100, energyLevel + 20);

  setMood(MOOD_HAPPY);
  animHappy(1);
}

void moodUnknownSeen() {
  lastInteractionTime = millis();
  energyLevel = max(0, energyLevel - 5);

  setMood(MOOD_SHY);
  animShy(1);
}

void moodNoFace() {
  noFaceActive = true;
  noFaceStart = millis();

  setMood(MOOD_BORED);
}

void moodUpdate() {
  unsigned long now = millis();
  unsigned long inactiveTime = now - lastInteractionTime;

  if (energyLevel > 0 && now - lastMoodChange > 30000) {
    energyLevel--;
    lastMoodChange = now;
  }

  if (inactiveTime > SLEEPY_TIME) {
    if (currentMoodState != MOOD_SLEEPY) {
      setMood(MOOD_SLEEPY);
    }

    if (now - lastIdleAction > IDLE_ACTION_TIME) {
      animSleepy(1);
      lastIdleAction = now;
    }

    return;
  }

  if (inactiveTime > BORED_TIME) {
    if (currentMoodState != MOOD_BORED) {
      setMood(MOOD_BORED);
    }

    if (now - lastIdleAction > IDLE_ACTION_TIME) {
      animStretch(1);
      boredStretchCount++;
      lastIdleAction = now;
    }

    return;
  }
}