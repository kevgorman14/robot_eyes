#include "Motion.h"
#include "Servos.h"
#include "Config.h"

void poseSit() {
  smoothMove(L_HIP_PITCH, L_pitch_forward, 500);
  smoothMove(R_HIP_PITCH, R_pitch_forward, 500);
  smoothMove(L_HIP_ROLL, neutral_L_hip_roll, 400);
  smoothMove(R_HIP_ROLL, neutral_R_hip_roll, 400);
  smoothMove(L_KNEE, L_knee_up, 500);
  smoothMove(R_KNEE, R_knee_up, 500);
}

void poseStand() {
  smoothMove(L_HIP_PITCH, neutral_L_hip_pitch, 700);
  smoothMove(R_HIP_PITCH, neutral_R_hip_pitch, 700);
  smoothMove(L_HIP_ROLL, neutral_L_hip_roll, 500);
  smoothMove(R_HIP_ROLL, neutral_R_hip_roll, 500);
  smoothMove(L_KNEE, neutral_L_knee, 700);
  smoothMove(R_KNEE, neutral_R_knee, 700);
}

// void centreHead() {
//   smoothMove(HEAD_YAW, neutral_head_yaw, 400);
//   smoothMove(HEAD_PITCH, neutral_head_pitch, 400);
// }

// void lookLeft() {
//   smoothMove(HEAD_YAW, head_left, 400);
// }

// void lookRight() {
//   smoothMove(HEAD_YAW, head_right, 400);
// }

// void lookUp() {
//   smoothMove(HEAD_PITCH, head_up, 400);
// }

// void lookDown() {
//   smoothMove(HEAD_PITCH, head_down, 400);
// }
