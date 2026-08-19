#include "Animations.h"
#include "Servos.h"
#include "Config.h"
#include "Motion.h"

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