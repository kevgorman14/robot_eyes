#include <Arduino.h>

#include "Servos.h"
#include "Motion.h"
#include "Animations.h"
#include "Eyes.h"
#include "Mood.h"
#include"SerialCommands.h"

void setup() {
  Serial.begin(115200);
  delay(500);

  eyesInit();
  servoInit();
  
  moodInit();

  poseSit();
  serialCommandsInit();

  setMood(MOOD_NEUTRAL);

  Serial.println("Nano ready");
}

void loop() {
  serialCommandsUpdate();
  moodUpdate();
}