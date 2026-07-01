#ifndef Animations_h
#define Animations_h

#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

// PCA9685 servo settings
const int SERVO_FREQ = 50;
const int minPulse = 500;
const int maxPulse = 2500;

// Servo channels
const int L_HIP_PITCH = 0;
const int L_HIP_ROLL  = 1;
const int L_KNEE      = 2;

const int R_HIP_PITCH = 4;
const int R_HIP_ROLL  = 5;
const int R_KNEE      = 6;

const int HEAD_YAW   = 15;  // left/right
const int HEAD_PITCH = 14;  // up/down (example)

// LEFT LEG
const int neutral_L_hip_pitch = 90;   // standing
const int L_pitch_forward = 10;      // sitting
const int L_pitch_back = 120;

const int neutral_L_hip_roll = 90;   // standing
const int L_roll_left = 105;         // inwards/towards body
const int L_roll_right = 70;         // outwards/away from body

const int neutral_L_knee = 100;      // standing
const int L_knee_up = 20;            // sitting/up

// RIGHT LEG
const int neutral_R_hip_pitch = 30;  // standing
const int R_pitch_forward = 120;     // sitting
const int R_pitch_back = 10;

const int neutral_R_hip_roll = 100;  // standing
const int R_roll_left = 130;         // inwards/towards body
const int R_roll_right = 80;         // outwards/away from body

const int neutral_R_knee = 50;       // standing
const int R_knee_up = 150;           // sitting/up

// Head Left/Right
const int neutral_head_yaw = 90;
const int head_left = 45;
const int head_right = 135;

// Head Up/Down
const int neutral_head_pitch = 90;
const int head_up = 60;
const int head_down = 120;

extern Adafruit_PWMServoDriver pwmLower;
extern Adafruit_PWMServoDriver pwmUpper;

// Safety arrays for all 16 PCA9685 channels.
extern int servoMin[16];
extern int servoMax[16];
extern int neutralAngles[16];   // also used as current angle tracker by smoothMove()

extern int lastKnownHeadPos;

void setupServoLimits();

// Public animation functions
void animExcited(int cycles);
void animSleepy(int cycles);
void animShy(int cycles);
void animHappy(int cycles);
void animStretch(int cycles);
void animWakeUp();
void animLegWaveFB(int cycles);
void animLegWaveFB_Right(int cycles);
void animLegWaveSide(int cycles);
void animLegWaveSide_Right(int cycles);
void animLegWaveDouble(int cycles);
void animLegWaveHappy(int cycles);
void animSwing(int cycles);
void animKick(int cycles);
void animTap(int cycles);

// Internal utility functions (safe to call from sketch if needed)
void smoothMove(int channel, int target, int duration);
int clampServoAngle(int channel, int angle);
bool isConfiguredChannel(int channel);
int angleToPWM(int angle);
void setPWMForChannel(int channel, int pwmVal);

#endif
