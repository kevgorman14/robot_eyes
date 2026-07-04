#include "SerialCommands.h"

#include <Arduino.h>
#include "Servos.h"
#include "Motion.h"
#include "Animations.h"
#include "Mood.h"
#include "Eyes.h"
#include "Globals.h"
#include "Config.h"

void serialCommandsInit() {
  Serial.println("Serial commands ready. Type HELP.");
}

void printHelp() {
  Serial.println();
  Serial.println("===== NANO COMMANDS =====");
  Serial.println("HELP");
  Serial.println("SIT / POSE SIT");
  Serial.println("STAND / POSE STAND");
  Serial.println("HOME");
  Serial.println("CHx angle       example: CH0 60");
  Serial.println("HEAD angle      example: HEAD 90");
  Serial.println("MOOD HAPPY / EXCITED / SHY / SLEEPY / BORED / NEUTRAL");
  Serial.println("EVENT KEVIN / UNKNOWN / NO_FACE");
  Serial.println("EYES NEUTRAL / HAPPY / BLINK / LEFT / RIGHT / SLOW");
  Serial.println("ANIM EXCITED n / SLEEPY n / SHY n / HAPPY n / STRETCH n");
  Serial.println("ANIM WAVEFB n / WAVEFB_R n / WAVESIDE n / WAVESIDE_R n");
  Serial.println("ANIM WAVEDOUBLE n / WAVEHAPPY n / SWING n / KICK n / TAP n");
  Serial.println("=========================");
  Serial.println();
}

static int getNumberAfterLastSpace(const String& cmd, int defaultValue = 1) {
  int spaceIndex = cmd.lastIndexOf(' ');
  if (spaceIndex < 0) return defaultValue;

  int value = cmd.substring(spaceIndex + 1).toInt();
  if (value <= 0) return defaultValue;

  return value;
}

static void handleMoodCommand(const String& cmd) {
  if (cmd == "MOOD HAPPY") setMood(MOOD_HAPPY);
  else if (cmd == "MOOD EXCITED") setMood(MOOD_EXCITED);
  else if (cmd == "MOOD SHY") setMood(MOOD_SHY);
  else if (cmd == "MOOD SLEEPY") setMood(MOOD_SLEEPY);
  else if (cmd == "MOOD BORED") setMood(MOOD_BORED);
  else if (cmd == "MOOD NEUTRAL") setMood(MOOD_NEUTRAL);
  else Serial.println("[ERROR] Unknown mood");
}

static void handleEventCommand(const String& cmd) {
  if (cmd == "EVENT KEVIN") moodKevinSeen();
  else if (cmd == "EVENT UNKNOWN") moodUnknownSeen();
  else if (cmd == "EVENT NO_FACE") moodNoFace();
  else Serial.println("[ERROR] Unknown event");
}

static void handleEyesCommand(const String& cmd) {
  if (cmd == "EYES NEUTRAL") eyesNeutral();
  else if (cmd == "EYES HAPPY") eyesHappy();
  else if (cmd == "EYES BLINK") eyesBlink();
  else if (cmd == "EYES LEFT") eyesLookLeft();
  else if (cmd == "EYES RIGHT") eyesLookRight();
  else if (cmd == "EYES SLOW") eyesSlowBlink();
  else if (cmd == "EYES LIST") eyesListFiles();
  else Serial.println("[ERROR] Unknown eyes command");
}

static void handleAnimCommand(const String& cmd) {
  int cycles = getNumberAfterLastSpace(cmd, 1);

  if (cmd.startsWith("ANIM EXCITED")) animExcited(cycles);
  else if (cmd.startsWith("ANIM SLEEPY")) animSleepy(cycles);
  else if (cmd.startsWith("ANIM SHY")) animShy(cycles);
  else if (cmd.startsWith("ANIM HAPPY")) animHappy(cycles);
  else if (cmd.startsWith("ANIM STRETCH")) animStretch(cycles);
  else if (cmd.startsWith("ANIM WAVEFB_R")) animLegWaveFB_Right(cycles);
  else if (cmd.startsWith("ANIM WAVEFB")) animLegWaveFB(cycles);
  else if (cmd.startsWith("ANIM WAVESIDE_R")) animLegWaveSide_Right(cycles);
  else if (cmd.startsWith("ANIM WAVESIDE")) animLegWaveSide(cycles);
  else if (cmd.startsWith("ANIM WAVEDOUBLE")) animLegWaveDouble(cycles);
  else if (cmd.startsWith("ANIM WAVEHAPPY")) animLegWaveHappy(cycles);
  else if (cmd.startsWith("ANIM SWING")) animSwing(cycles);
  else if (cmd.startsWith("ANIM KICK")) animKick(cycles);
  else if (cmd.startsWith("ANIM TAP")) animTap(cycles);
  else Serial.println("[ERROR] Unknown animation");
}

static void handleChannelCommand(const String& cmd) {
  int spaceIndex = cmd.indexOf(' ');
  if (spaceIndex < 0) {
    Serial.println("[ERROR] Use CHx angle, example CH0 60");
    return;
  }

  int channel = cmd.substring(2, spaceIndex).toInt();
  int angle = cmd.substring(spaceIndex + 1).toInt();

  smoothMove(channel, angle, 300);
}

static void handleHeadCommand(const String& cmd) {
  int spaceIndex = cmd.indexOf(' ');
  if (spaceIndex < 0) {
    Serial.println("[ERROR] Use HEAD angle, example HEAD 90");
    return;
  }

  int angle = cmd.substring(spaceIndex + 1).toInt();
  smoothMove(HEAD_YAW, angle, 300);
}

static void handleCommand(String cmd) {
  cmd.trim();
  cmd.toUpperCase();

  if (cmd.length() == 0) return;

  Serial.print("[CMD] ");
  Serial.println(cmd);

  if (cmd == "HELP") printHelp();

  else if (cmd == "SIT" || cmd == "POSE SIT") poseSit();
  else if (cmd == "STAND" || cmd == "POSE STAND") poseStand();
  else if (cmd == "HOME") poseSit();

  else if (cmd.startsWith("CH")) handleChannelCommand(cmd);
  else if (cmd.startsWith("HEAD")) handleHeadCommand(cmd);

  else if (cmd.startsWith("MOOD")) handleMoodCommand(cmd);
  else if (cmd.startsWith("EVENT")) handleEventCommand(cmd);
  else if (cmd.startsWith("EYES")) handleEyesCommand(cmd);
  else if (cmd.startsWith("ANIM")) handleAnimCommand(cmd);

  else Serial.println("[ERROR] Unknown command. Type HELP.");
}

void serialCommandsUpdate() {
  if (!Serial.available()) return;

  String cmd = Serial.readStringUntil('\n');
  handleCommand(cmd);
}