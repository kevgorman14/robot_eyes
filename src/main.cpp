#include <Arduino.h>

#include "Servos.h"
#include "Motion.h"
#include "Animations.h"
#include "Eyes.h"
#include "Mood.h"
#include"SerialCommands.h"
#include "Behaviour.h"

void setup() {
  Serial.begin(115200);
  delay(500);

  eyesInit();
  servoInit();
  
  moodInit();
  behaviourInit();
  poseSit();
  serialCommandsInit();

  setMood(MOOD_NEUTRAL);

  Serial.println("Nano ready");
}

void loop() {
  serialCommandsUpdate();
  behaviourUpdate();
  moodUpdate();
  updateSleepTimer();
}