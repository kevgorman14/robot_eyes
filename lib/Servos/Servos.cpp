#include <Arduino.h>
#include "Config.h"
#include "Servos.h"
#include "Globals.h"
#include <Wire.h>

// Safety arrays for all 16 PCA9685 channels.
extern int servoMin[16];
extern int servoMax[16];
extern int neutralAngles[16];   // also used as current angle tracker by smoothMove()
extern int lastKnownHeadPos;

void servoInit() {
  Wire.begin(I2C_SDA, I2C_SCL);

  setupServoLimits();

  pwmLower.begin();
  pwmLower.setPWMFreq(SERVO_FREQ);

  pwmUpper.begin();
  pwmUpper.setPWMFreq(SERVO_FREQ);
}

void setupServoLimits() {
  for (int i = 0; i < 16; i++) {
    servoMin[i] = 0;
    servoMax[i] = 180;
    neutralAngles[i] = 90;
  }

  servoMin[L_HIP_PITCH] = 5;
  servoMax[L_HIP_PITCH] = 120;
  neutralAngles[L_HIP_PITCH] = neutral_L_hip_pitch;

  servoMin[L_HIP_ROLL] = 70;
  servoMax[L_HIP_ROLL] = 105;
  neutralAngles[L_HIP_ROLL] = neutral_L_hip_roll;

  servoMin[L_KNEE] = 20;
  servoMax[L_KNEE] = 100;
  neutralAngles[L_KNEE] = neutral_L_knee;

  servoMin[R_HIP_PITCH] = 10;
  servoMax[R_HIP_PITCH] = 130;
  neutralAngles[R_HIP_PITCH] = neutral_R_hip_pitch;

  servoMin[R_HIP_ROLL] = 80;
  servoMax[R_HIP_ROLL] = 130;
  neutralAngles[R_HIP_ROLL] = neutral_R_hip_roll;

  servoMin[R_KNEE] = 50;
  servoMax[R_KNEE] = 150;
  neutralAngles[R_KNEE] = neutral_R_knee;

  servoMin[HEAD_YAW] = head_left;
  servoMax[HEAD_YAW] = head_right;
  neutralAngles[HEAD_YAW] = neutral_head_yaw;

  servoMin[HEAD_PITCH] = head_up;
  servoMax[HEAD_PITCH] = head_down;
  neutralAngles[HEAD_PITCH] = neutral_head_pitch;

  lastKnownHeadPos = neutral_head_yaw;
}

int clampServoAngle(int channel, int angle) {
  if (channel < 0 || channel > 15) return angle;
  return constrain(angle, servoMin[channel], servoMax[channel]);
}

int angleToPWM(int angle) {
  angle = constrain(angle, 0, 180);
  int pulse = map(angle, 0, 180, minPulse, maxPulse);
  int pwmVal = (int)((pulse * 4096.0) / 20000.0);
  return constrain(pwmVal, 0, 4095);
}

void setPWMForChannel(int channel, int pwmVal) {
  if (channel == HEAD_YAW || channel == HEAD_PITCH) {
    pwmUpper.setPWM(channel, 0, pwmVal);
  } else {
    pwmLower.setPWM(channel, 0, pwmVal);
  }
}

bool isConfiguredChannel(int channel) {
  return channel == L_HIP_PITCH || channel == L_HIP_ROLL || channel == L_KNEE ||
         channel == R_HIP_PITCH || channel == R_HIP_ROLL || channel == R_KNEE ||
         channel == HEAD_YAW || channel == HEAD_PITCH;
}

void smoothMove(int channel, int target, int duration) {
  if (channel < 0 || channel > 15 || !isConfiguredChannel(channel)) {
    Serial.print("[ERROR] Bad smooth channel: ");
    Serial.println(channel);
    return;
  }

  target = clampServoAngle(channel, target);

  int start = neutralAngles[channel];
  int delta = target - start;
  int steps = max(1, duration / 20);
  float stepVal = (float)delta / (float)steps;

  for (int i = 1; i <= steps; i++) {
    int val = start + (int)(stepVal * i);
    val = clampServoAngle(channel, val);
    int pwmVal = angleToPWM(val);
    setPWMForChannel(channel, pwmVal);
    delay(30);
  }

  neutralAngles[channel] = target;

  if (channel == HEAD_YAW) {
    lastKnownHeadPos = target;
  }
}
int clampServoAngle(int channel, int angle);
bool isConfiguredChannel(int channel);
int angleToPWM(int angle);
void setPWMForChannel(int channel, int pwmVal);
