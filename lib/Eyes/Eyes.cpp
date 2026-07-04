#include "Eyes.h"

#include <Arduino_GFX_Library.h>
#include <LittleFS.h>
#include <PNGdec.h>
#include "Mood.h"

// Static global handles (only one instance needed)
static Arduino_DataBus* leftBus = nullptr;
static Arduino_DataBus* rightBus = nullptr;
static Arduino_GFX* leftEye = nullptr;
static Arduino_GFX* rightEye = nullptr;

static PNG png;

static EyeExpression currentEyeExpression = EYES_NEUTRAL;

// =====================
// PNG DRAW CALLBACK (STATIC)
// =====================
static int _pngDrawCallback(PNGDRAW* pDraw) {
  uint16_t lineBuffer[EYES_WIDTH];

  png.getLineAsRGB565(
    pDraw,
    lineBuffer,
    PNG_RGB565_LITTLE_ENDIAN,
    0xffffffff
  );

  // Draw same line to both eyes
  leftEye->draw16bitRGBBitmap(0, pDraw->y, lineBuffer, pDraw->iWidth, 1);
  rightEye->draw16bitRGBBitmap(0, pDraw->y, lineBuffer, pDraw->iWidth, 1);

  return 1;
}

// =====================
// INIT DISPLAYS AND LITTLEFS
// =====================
bool eyesInit() {


  // Initialize buses
  leftBus = new Arduino_ESP32SPI(LEFT_DC, LEFT_CS, TFT_SCK, TFT_MOSI, -1);
  rightBus = new Arduino_ESP32SPI(RIGHT_DC, RIGHT_CS, TFT_SCK, TFT_MOSI, -1);

  // Initialize displays
  leftEye = new Arduino_GC9A01(leftBus, -1, 0, true, EYES_WIDTH, EYES_HEIGHT);
  rightEye = new Arduino_GC9A01(rightBus, -1, 0, true, EYES_WIDTH, EYES_HEIGHT);

  // Start displays
  leftEye->begin();
  rightEye->begin();

  // Test color
  leftEye->fillScreen(RGB565_RED);
  rightEye->fillScreen(RGB565_RED);
  delay(700);
  leftEye->fillScreen(RGB565_BLACK);
  rightEye->fillScreen(RGB565_BLACK);

  // Mount LittleFS
  if (!LittleFS.begin(false, "/littlefs", 10, "littlefs")) {
    Serial.println("LittleFS mount failed");
    return false;
  }

  Serial.println("Eyes system initialized.");
  return true;
}

// =====================
// INTERNAL PNG DRAWER (called by eyesDrawPNG)
// =====================
void _eyesDrawPNG(const char* filename) {
  if (!LittleFS.exists(filename)) {
    Serial.print("File does not exist: ");
    Serial.println(filename);
    return;
  }

  int rc = png.open(
    filename,
    [](const char* filename, int32_t* size) -> void* {
      File file = LittleFS.open(filename, "r");
      if (!file) {
        Serial.print("Failed to open: ");
        Serial.println(filename);
        return nullptr;
      }
      *size = file.size();
      return new File(file);
    },
    [](void* handle) {
      if (!handle) return;
      File* file = (File*)handle;
      file->close();
      delete file;
    },
    [](PNGFILE* handle, uint8_t* buffer, int32_t length) -> int32_t {
      if (!handle || !handle->fHandle) return 0;
      File* file = (File*)handle->fHandle;
      return file->read(buffer, length);
    },
    [](PNGFILE* handle, int32_t position) -> int32_t {
      if (!handle || !handle->fHandle) return 0;
      File* file = (File*)handle->fHandle;
      file->seek(position);
      return position;
    },
    _pngDrawCallback
  );

  if (rc == PNG_SUCCESS) {
    Serial.print("Drawing: ");
    Serial.println(filename);
    png.decode(nullptr, 0);
    png.close();
  } else {
    Serial.print("PNG open failed: ");
    Serial.print(filename);
    Serial.print(" rc=");
    Serial.println(rc);
  }
}

// =====================
// PUBLIC DRAW FUNCTIONS
// =====================
bool eyesDrawPNG(const char* filename) {
  _eyesDrawPNG(filename);
  return true; // Assume success unless exception
}

// =====================
// ANIMATION UTILITY FUNCTIONS
// =====================
void eyesRestoreMood() {
  switch (getMood())
  {
    case MOOD_HAPPY:
      eyesHappy();
      break;
    
      case MOOD_BORED:
      eyesBored();
      break;

    case MOOD_SLEEPY:
      eyesSleepy();
      break;

    case MOOD_SHY:
      eyesLookLeft();
      break;
    
    default:
      eyesNeutral();
      break;
  }
}

void eyesNeutral() {
  currentEyeExpression = EYES_NEUTRAL;
  eyesDrawPNG("/neutral_open.png");
}

void eyesHappy() {
  currentEyeExpression = EYES_HAPPY;
  eyesDrawPNG("/happy.png");
}

void eyesShy() {
  currentEyeExpression = EYES_SHY;
  eyesDrawPNG("/look_left.png");
}

void eyesBored() {
  currentEyeExpression = EYES_BORED;
  eyesDrawPNG("/slow_blink_1.png");
}

void eyesSleepy() {
  currentEyeExpression = EYES_SLEEPY;
  eyesDrawPNG("/slow_blink_2.png");
}

void eyesSetExpression(EyeExpression expression) {
  switch (expression) {
    case EYES_HAPPY:  eyesHappy();  break;
    case EYES_SHY:    eyesShy();    break;
    case EYES_BORED:  eyesBored();  break;
    case EYES_SLEEPY: eyesSleepy(); break;
    default:          eyesNeutral(); break;
  }
}

void eyesLookLeft()
{
    eyesSetExpression(EYES_SHY);
}

void eyesLookRight()
{
    eyesDrawPNG("/look_right.png");
}

void eyesSlowBlink()
{
    eyesDrawPNG("/slow_blink_1.png");
    delay(300);
    eyesDrawPNG("/slow_blink_2.png");
    delay(300);
    eyesRestoreExpression();
}

void eyesRestoreExpression() {
  EyeExpression saved = currentEyeExpression;
  eyesSetExpression(saved);
}

void eyesBlink() {
  EyeExpression saved = currentEyeExpression;

  eyesDrawPNG("/closed_tight.png");
  delay(100);

  eyesSetExpression(saved);
}

// =====================
// LIST FILES ON LITTLEFS
// =====================
void eyesListFiles() {
  Serial.println("Files on LittleFS:");
  File root = LittleFS.open("/");
  File file = root.openNextFile();

  while (file) {
    Serial.print("  ");
    Serial.print(file.name());
    Serial.print(" size ");
    Serial.println(file.size());
    file = root.openNextFile();
  }
}
