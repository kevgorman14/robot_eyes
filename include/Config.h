#pragma once

#include <Arduino.h>

// =====================
// I2C pins
// =====================
constexpr uint8_t I2C_SDA = D4;
constexpr uint8_t I2C_SCL = D5;

// =====================
// PCA9685 servo settings
// =====================
constexpr uint8_t LOWER_PCA_ADDR = 0x40;
constexpr uint8_t UPPER_PCA_ADDR = 0x41;
constexpr int SERVO_FREQ = 50;
constexpr int minPulse = 500;
constexpr int maxPulse = 2500;

// =====================
// Servo channels
// =====================
constexpr int L_HIP_PITCH = 0;
constexpr int L_HIP_ROLL  = 1;
constexpr int L_KNEE      = 2;

constexpr int R_HIP_PITCH = 4;
constexpr int R_HIP_ROLL  = 5;
constexpr int R_KNEE      = 6;

constexpr int HEAD_PITCH = 14;
constexpr int HEAD_YAW   = 15;

// =====================
// Left leg angles
// =====================
constexpr int neutral_L_hip_pitch = 90;  // standing
constexpr int L_pitch_forward = 10;      // sitting
constexpr int L_pitch_back = 120;

constexpr int neutral_L_hip_roll = 90;   // standing
constexpr int L_roll_left = 105;         // inwards/towards body
constexpr int L_roll_right = 70;         // outwards/away from body

constexpr int neutral_L_knee = 100;      // standing
constexpr int L_knee_up = 20;            // sitting/up

// =====================
// Right leg angles
// =====================
constexpr int neutral_R_hip_pitch = 30;  // standing
constexpr int R_pitch_forward = 120;     // sitting
constexpr int R_pitch_back = 10;

constexpr int neutral_R_hip_roll = 100;  // standing
constexpr int R_roll_left = 130;         // inwards/towards body
constexpr int R_roll_right = 80;         // outwards/away from body

constexpr int neutral_R_knee = 50;       // standing
constexpr int R_knee_up = 150;           // sitting/up

// =====================
// Head angles
// =====================
constexpr int neutral_head_yaw = 90;
constexpr int head_left = 45;
constexpr int head_right = 135;

constexpr int neutral_head_pitch = 90;
constexpr int head_up = 60;
constexpr int head_down = 120;
