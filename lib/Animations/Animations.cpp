#include "Animations.h"

Adafruit_PWMServoDriver pwmLower = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwmUpper = Adafruit_PWMServoDriver(0x41);

int servoMin[16];
int servoMax[16];
int neutralAngles[16]; // also used as current angle tracker by smoothMove()
int lastKnownHeadPos = neutral_head_yaw;

void setupServoLimits() {
  for (int i = 0; i < 16; i++) {
    servoMin[i] = 0;
    servoMax[i] = 180;
    neutralAngles[i] = 90;
  }

  // Left hip pitch: min 5, max 120, standing 90
  servoMin[L_HIP_PITCH] = 5;
  servoMax[L_HIP_PITCH] = 120;
  neutralAngles[L_HIP_PITCH] = neutral_L_hip_pitch;

  // Left hip roll: numeric clamp must be low to high: 70 to 105
  servoMin[L_HIP_ROLL] = 70;
  servoMax[L_HIP_ROLL] = 105;
  neutralAngles[L_HIP_ROLL] = neutral_L_hip_roll;

  // Left knee: min 20, max 100, standing 100
  servoMin[L_KNEE] = 20;
  servoMax[L_KNEE] = 100;
  neutralAngles[L_KNEE] = neutral_L_knee;

  // Right hip pitch: min 10, max 130, standing 30
  servoMin[R_HIP_PITCH] = 10;
  servoMax[R_HIP_PITCH] = 130;
  neutralAngles[R_HIP_PITCH] = neutral_R_hip_pitch;

  // Right hip roll: numeric clamp must be low to high: 80 to 130
  servoMin[R_HIP_ROLL] = 80;
  servoMax[R_HIP_ROLL] = 130;
  neutralAngles[R_HIP_ROLL] = neutral_R_hip_roll;

  // Right knee: min 50, max 150, standing 50
  servoMin[R_KNEE] = 50;
  servoMax[R_KNEE] = 150;
  neutralAngles[R_KNEE] = neutral_R_knee;

  // Head
  servoMin[HEAD_YAW] = head_left;
  servoMax[HEAD_YAW] = head_right;
  neutralAngles[HEAD_YAW] = neutral_head_yaw;

  servoMin[HEAD_PITCH] = head_up;
  servoMax[HEAD_PITCH] = head_down;
  neutralAngles[HEAD_PITCH] = neutral_head_pitch;

  lastKnownHeadPos = neutral_head_yaw;
}

void animExcited(int cycles)
{
  for (int i = 0; i < cycles; i++)
  {
    smoothMove(L_KNEE, L_knee_up, 150);
    smoothMove(R_KNEE, R_knee_up, 150);

    smoothMove(L_KNEE, neutral_L_knee, 150);
    smoothMove(R_KNEE, neutral_R_knee, 150);

    smoothMove(L_HIP_ROLL, L_roll_left, 120);
    smoothMove(L_HIP_ROLL, L_roll_right, 120);
    smoothMove(L_HIP_ROLL, neutral_L_hip_roll, 120);
  }
}

void animSleepy(int cycles)
{
  for (int i = 0; i < cycles; i++)
  {
    smoothMove(L_HIP_PITCH, L_pitch_back + 6, 600);
    smoothMove(R_HIP_PITCH, R_pitch_back + 6, 600);

    smoothMove(L_KNEE, neutral_L_knee + 6, 500);
    smoothMove(R_KNEE, neutral_R_knee + 6, 500);

    smoothMove(L_HIP_ROLL, L_roll_left + 4, 800);
    smoothMove(R_HIP_ROLL, neutral_R_hip_roll, 800);
    delay(200);

    smoothMove(R_HIP_ROLL, neutral_R_hip_roll + 6, 800);
    smoothMove(L_HIP_ROLL, neutral_L_hip_roll, 800);
    delay(200);

    smoothMove(L_HIP_ROLL, neutral_L_hip_roll, 700);
    smoothMove(R_HIP_ROLL, neutral_R_hip_roll, 700);

    smoothMove(L_HIP_PITCH, L_pitch_back + 2, 500);
    smoothMove(R_HIP_PITCH, R_pitch_back + 2, 500);

    delay(150);
  }
}

void animShy(int cycles)
{
  for (int i = 0; i < cycles; i++)
  {
    smoothMove(L_HIP_ROLL, L_roll_right, 300);
    smoothMove(L_KNEE, L_knee_up - 5, 300);

    smoothMove(L_HIP_PITCH, L_pitch_forward + 10, 250);
    smoothMove(L_HIP_PITCH, L_pitch_back - 10, 250);

    smoothMove(L_HIP_ROLL, neutral_L_hip_roll, 300);
  }
}

void animHappy(int cycles)
{
  for (int i = 0; i < cycles; i++)
  {
    smoothMove(L_KNEE, L_knee_up, 200);
    smoothMove(R_KNEE, R_knee_up, 200);

    smoothMove(L_KNEE, neutral_L_knee, 200);
    smoothMove(R_KNEE, neutral_R_knee, 200);

    smoothMove(L_HIP_ROLL, L_roll_left, 150);
    smoothMove(L_HIP_ROLL, L_roll_right, 150);
    smoothMove(L_HIP_ROLL, neutral_L_hip_roll, 150);

    smoothMove(L_HIP_PITCH, L_pitch_forward + 10, 150);
    smoothMove(R_HIP_PITCH, R_pitch_forward + 10, 150);

    smoothMove(L_HIP_PITCH, L_pitch_back, 150);
    smoothMove(R_HIP_PITCH, R_pitch_back, 150);
  }
}

void animStretch(int cycles)
{
  for (int i = 0; i < cycles; i++)
  {
    // Start from sitting
    smoothMove(L_HIP_PITCH, L_pitch_forward, 500);
    smoothMove(R_HIP_PITCH, R_pitch_forward, 500);
    smoothMove(L_KNEE, L_knee_up, 500);
    smoothMove(R_KNEE, R_knee_up, 500);

    delay(200);

    // Lift legs a little more than sitting
    smoothMove(L_HIP_PITCH, L_pitch_forward + 8, 600);
    smoothMove(R_HIP_PITCH, R_pitch_forward - 8, 600);

    // Roll legs outward to stretch sideways
    smoothMove(L_HIP_ROLL, L_roll_right, 700);
    smoothMove(R_HIP_ROLL, R_roll_right, 700);

    delay(500);

    // Small knee relax/stretch only
    smoothMove(L_KNEE, L_knee_up + 10, 500);
    smoothMove(R_KNEE, R_knee_up - 10, 500);

    delay(500);

    // Return to sitting
    smoothMove(L_HIP_ROLL, neutral_L_hip_roll, 600);
    smoothMove(R_HIP_ROLL, neutral_R_hip_roll, 600);
    smoothMove(L_HIP_PITCH, L_pitch_forward, 600);
    smoothMove(R_HIP_PITCH, R_pitch_forward, 600);
    smoothMove(L_KNEE, L_knee_up, 600);
    smoothMove(R_KNEE, R_knee_up, 600);
  }
}

void animWakeUp()
{
  smoothMove(L_HIP_PITCH, L_pitch_back + 15, 600);
  smoothMove(R_HIP_PITCH, R_pitch_back + 15, 600);

  smoothMove(L_KNEE, neutral_L_knee + 10, 500);
  smoothMove(R_KNEE, neutral_R_knee + 10, 500);

  smoothMove(L_HIP_PITCH, neutral_L_hip_pitch, 600);
  smoothMove(R_HIP_PITCH, neutral_R_hip_pitch, 600);

  animStretch(1);

  smoothMove(L_HIP_ROLL, L_roll_left, 200);
  smoothMove(L_HIP_ROLL, L_roll_right, 200);
  smoothMove(L_HIP_ROLL, neutral_L_hip_roll, 200);
}

void animLegWaveFB(int cycles)
{
  for (int i = 0; i < cycles; i++)
  {
    smoothMove(L_KNEE, L_knee_up, 250);
    smoothMove(L_HIP_PITCH, L_pitch_forward, 250);
    smoothMove(L_HIP_PITCH, L_pitch_back, 250);
  }
}

void animLegWaveFB_Right(int cycles)
{
  for (int i = 0; i < cycles; i++)
  {
    smoothMove(R_KNEE, R_knee_up, 250);
    smoothMove(R_HIP_PITCH, R_pitch_forward, 250);
    smoothMove(R_HIP_PITCH, R_pitch_back, 250);
  }
}

void animLegWaveSide(int cycles)
{
  // Lift leg first
  smoothMove(L_HIP_PITCH, L_pitch_forward, 500);
  smoothMove(L_KNEE, L_knee_up, 500);
  delay(150);

  for (int i = 0; i < cycles; i++)
  {
    smoothMove(L_HIP_ROLL, L_roll_right, 350); // outward
    smoothMove(L_HIP_ROLL, L_roll_left, 350);  // inward
  }

  smoothMove(L_HIP_ROLL, neutral_L_hip_roll, 400);
}

void animLegWaveSide_Right(int cycles)
{
  // Lift leg first
  smoothMove(R_HIP_PITCH, R_pitch_forward, 500);
  smoothMove(R_KNEE, R_knee_up, 500);
  delay(150);

  for (int i = 0; i < cycles; i++)
  {
    smoothMove(R_HIP_ROLL, R_roll_right, 350); // outward
    smoothMove(R_HIP_ROLL, R_roll_left, 350);  // inward
  }

  smoothMove(R_HIP_ROLL, neutral_R_hip_roll, 400);
}

void animLegWaveDouble(int cycles)
{

  // Lift both legs first
  smoothMove(L_HIP_PITCH, L_pitch_forward, 500);
  smoothMove(R_HIP_PITCH, R_pitch_forward, 500);

  smoothMove(L_KNEE, L_knee_up, 500);
  smoothMove(R_KNEE, R_knee_up, 500);

  delay(200);

  for (int i = 0; i < cycles; i++)
  {

    smoothMove(L_HIP_ROLL, L_roll_right, 300);
    smoothMove(R_HIP_ROLL, R_roll_right, 300);

    smoothMove(L_HIP_ROLL, L_roll_left, 300);
    smoothMove(R_HIP_ROLL, R_roll_left, 300);
  }

  // Return to centre while keeping legs raised
  smoothMove(L_HIP_ROLL, neutral_L_hip_roll, 300);
  smoothMove(R_HIP_ROLL, neutral_R_hip_roll, 300);

  // Return to sitting
  smoothMove(L_HIP_PITCH, L_pitch_forward, 400);
  smoothMove(R_HIP_PITCH, R_pitch_forward, 400);

  smoothMove(L_KNEE, L_knee_up, 400);
  smoothMove(R_KNEE, R_knee_up, 400);
}

void animLegWaveHappy(int cycles)
{

  // Lift both legs into the air
  smoothMove(L_HIP_PITCH, L_pitch_forward, 500);
  smoothMove(R_HIP_PITCH, R_pitch_forward, 500);

  smoothMove(L_KNEE, L_knee_up, 500);
  smoothMove(R_KNEE, R_knee_up, 500);

  delay(200);

  for (int i = 0; i < cycles; i++)
  {

    smoothMove(L_HIP_ROLL, L_roll_right, 200);
    smoothMove(R_HIP_ROLL, R_roll_right, 200);

    smoothMove(L_HIP_ROLL, L_roll_left, 200);
    smoothMove(R_HIP_ROLL, R_roll_left, 200);

    smoothMove(L_HIP_ROLL, neutral_L_hip_roll, 150);
    smoothMove(R_HIP_ROLL, neutral_R_hip_roll, 150);
  }

  // Return to relaxed sitting
  smoothMove(L_HIP_PITCH, L_pitch_forward, 400);
  smoothMove(R_HIP_PITCH, R_pitch_forward, 400);

  smoothMove(L_KNEE, L_knee_up, 400);
  smoothMove(R_KNEE, R_knee_up, 400);
}

void animSwing(int cycles)
{
  for (int i = 0; i < cycles; i++)
  {
    smoothMove(L_KNEE, L_knee_up, 250);
    smoothMove(R_KNEE, R_knee_up, 250);

    smoothMove(L_KNEE, neutral_L_knee, 250);
    smoothMove(R_KNEE, neutral_R_knee, 250);
  }
}

void animKick(int cycles)
{
  for (int i = 0; i < cycles; i++)
  {
    smoothMove(L_KNEE, neutral_L_knee, 250);
    smoothMove(L_KNEE, L_knee_up, 250);
  }
}

void animTap(int cycles)
{
  for (int i = 0; i < cycles; i++)
  {
    smoothMove(L_KNEE, L_knee_up - 5, 150);
    smoothMove(L_KNEE, L_knee_up, 150);
  }
}

void smoothMove(int channel, int target, int duration)
{
  if (channel < 0 || channel > 15 || !isConfiguredChannel(channel))
  {
    Serial.print("[ERROR] Bad smooth channel: ");
    Serial.println(channel);
    return;
  }

  target = clampServoAngle(channel, target);

  int start = neutralAngles[channel];
  int delta = target - start;
  int steps = max(1, duration / 20);
  float stepVal = (float)delta / (float)steps;

  for (int i = 1; i <= steps; i++)
  {
    int val = start + (int)(stepVal * i);
    val = clampServoAngle(channel, val);
    int pwmVal = angleToPWM(val);
    setPWMForChannel(channel, pwmVal);
    delay(30);
  }

  neutralAngles[channel] = target;

  if (channel == HEAD_YAW)
  {
    lastKnownHeadPos = target;
  }
}

int clampServoAngle(int channel, int angle)
{
  if (channel < 0 || channel > 15)
    return angle;
  return constrain(angle, servoMin[channel], servoMax[channel]);
}

bool isConfiguredChannel(int channel)
{
  return channel == L_HIP_PITCH || channel == L_HIP_ROLL || channel == L_KNEE ||
         channel == R_HIP_PITCH || channel == R_HIP_ROLL || channel == R_KNEE ||
         channel == HEAD_YAW || channel == HEAD_PITCH;
}

int angleToPWM(int angle)
{
  angle = constrain(angle, 0, 180);
  int pulse = map(angle, 0, 180, minPulse, maxPulse);
  int pwmVal = (int)((pulse * 4096.0) / 20000.0);
  return constrain(pwmVal, 0, 4095);
}

void setPWMForChannel(int channel, int pwmVal)
{
  if (channel == HEAD_YAW || channel == HEAD_PITCH)
  {
    pwmUpper.setPWM(channel, 0, pwmVal);
  }
  else
  {
    pwmLower.setPWM(channel, 0, pwmVal);
  }
}
