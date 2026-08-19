// #ifndef Eyes_h
// #define Eyes_h

// #pragma once

// #include <Arduino.h>

// // Display configuration
// #define EYES_WIDTH  240
// #define EYES_HEIGHT 240

// // Pin definitions
// #define TFT_SCK   D8
// #define TFT_MOSI  D10
// #define TFT_RST   D3
// #define LEFT_CS   D1
// #define LEFT_DC   D2
// #define RIGHT_CS  D6
// #define RIGHT_DC  D7

// // Colors
// //#define RGB565_BLACK  0x0000
// //#define RGB565_RED    0xF800


// enum EyeExpression {
//   EYES_NEUTRAL,
//   EYES_HAPPY,
//   EYES_SHY,
//   EYES_BORED,
//   EYES_SLEEPY,
//   EYES_ASLEEP
// };

// void eyesSetExpression(EyeExpression expression);
// void eyesRestoreExpression();

// void eyesBored();
// void eyesSleepy();
// void eyesAsleep();

// // Public API Functions
// bool eyesInit();
// bool eyesDrawPNG(const char* filename);
// void eyesBlink();
// void eyesLookLeft();
// void eyesLookRight();
// void eyesNeutral();
// void eyesHappy();
// void eyesSlowBlink();
// void eyesListFiles();


// // Internal helper (not for direct use in sketch)
// void _eyesDrawPNG(const char* filename);

// #endif
