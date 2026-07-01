#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include <Arduino_GFX.h>
#include <LittleFS.h>
#include <PNGdec.h>

#include <Eyes.h>

// =====================
// NANO PNG EYE TEST
// GC9A01 240x240 round display
// XIAO ESP32-C5
// Arduino_GFX + LittleFS + PNGdec
// =====================

Arduino_GFX *currentEye;

// Shared display pins
#define TFT_SCK   D8
#define TFT_MOSI  D10
#define TFT_RST   D3

// Left eye pins
#define LEFT_CS   D1
#define LEFT_DC   D2

// Right eye pins
#define RIGHT_CS  D6
#define RIGHT_DC  D7

Arduino_DataBus *leftBus = new Arduino_ESP32SPI(
  LEFT_DC,
  LEFT_CS,
  TFT_SCK,
  TFT_MOSI,
  -1
);

Arduino_DataBus *rightBus = new Arduino_ESP32SPI(
  RIGHT_DC,
  RIGHT_CS,
  TFT_SCK,
  TFT_MOSI,
  -1
);

Arduino_GFX *leftEye = new Arduino_GC9A01(
  leftBus,
  -1,
  0,
  true,
  240,
  240
);

Arduino_GFX *rightEye = new Arduino_GC9A01(
  rightBus,
  -1,
  0,
  true,
  240,
  240
);

PNG png;

// =====================
// PNG DRAW CALLBACK
// =====================
int PNGDraw(PNGDRAW *pDraw)
{
  uint16_t lineBuffer[240];

  png.getLineAsRGB565(
    pDraw,
    lineBuffer,
    PNG_RGB565_LITTLE_ENDIAN,
    0xffffffff
  );

  leftEye->draw16bitRGBBitmap(
    0,
    pDraw->y,
    lineBuffer,
    pDraw->iWidth,
    1
  );

  rightEye->draw16bitRGBBitmap(
    0,
    pDraw->y,
    lineBuffer,
    pDraw->iWidth,
    1
  );

  return 1;
}

// =====================
// FILE LIST DEBUG
// =====================
void listFiles()
{
  Serial.println("Files on LittleFS:");

  File root = LittleFS.open("/");
  File file = root.openNextFile();

  while (file)
  {
    Serial.print("  ");
    Serial.print(file.name());
    Serial.print(" size ");
    Serial.println(file.size());
    file = root.openNextFile();
  }
}

// =====================
// DRAW PNG FROM LITTLEFS
// =====================
void drawEyePNG(const char *filename)
{
  //currentEye->fillScreen(RGB565_BLACK);

  if (!LittleFS.exists(filename))
  {
    Serial.print("File does not exist: ");
    Serial.println(filename);
    return;
  }

  int rc = png.open(
    filename,

    [](const char *filename, int32_t *size) -> void *
    {
      File file = LittleFS.open(filename, "r");

      if (!file)
      {
        Serial.print("Failed to open: ");
        Serial.println(filename);
        return NULL;
      }

      *size = file.size();
      return (void *)new File(file);
    },

    [](void *handle)
    {
      if (!handle) return;

      File *file = (File *)handle;
      file->close();
      delete file;
    },

    [](PNGFILE *handle, uint8_t *buffer, int32_t length) -> int32_t
    {
      if (!handle || !handle->fHandle) return 0;

      File *file = (File *)handle->fHandle;
      return file->read(buffer, length);
    },

    [](PNGFILE *handle, int32_t position) -> int32_t
    {
      if (!handle || !handle->fHandle) return 0;

      File *file = (File *)handle->fHandle;
      file->seek(position);
      return position;
    },

    PNGDraw
  );

  if (rc == PNG_SUCCESS)
  {
    Serial.print("Drawing: ");
    Serial.println(filename);

    png.decode(NULL, 0);
    png.close();
  }
  else
  {
    Serial.print("PNG open failed: ");
    Serial.print(filename);
    Serial.print(" rc=");
    Serial.println(rc);
  }
}


// =====================
// SETUP
// =====================
void setup()
{
  Serial.begin(115200);
  delay(1000);

  leftEye->begin();
  rightEye->begin();

  leftEye->fillScreen(RGB565_RED);
  rightEye->fillScreen(RGB565_RED);
  delay(700);
  leftEye->fillScreen(RGB565_BLACK);
  rightEye->fillScreen(RGB565_BLACK);

  if (!LittleFS.begin(false, "/littlefs", 10, "littlefs"))
  {
    Serial.println("LittleFS mount failed");
    while (true);
  }

  Serial.println("LittleFS mounted");

  File root = LittleFS.open("/");
  File file = root.openNextFile();

  Serial.println("Listing files:");

  while (file)
  {
    Serial.print("Found: ");
    Serial.print(file.name());
    Serial.print("  ");
    Serial.println(file.size());

    file = root.openNextFile();
  }

  drawEyePNG("/neutral_open.png");

  draw_eyes();
}

// =====================
// LOOP DEMO
// =====================
void loop()
{
  drawEyePNG("/neutral_open.png");
  delay(3000);

  drawEyePNG("/closed_tight.png");
  delay(100);

  drawEyePNG("/happy.png");
  delay(3000);

  drawEyePNG("/closed_tight.png");
  delay(100);

  drawEyePNG("/look_left.png");
  delay(3000);

  drawEyePNG("/closed_tight.png");
  delay(100);

  drawEyePNG("/look_right.png");
  delay(3000);

  drawEyePNG("/closed_tight.png");
  delay(100);

  drawEyePNG("/slow_blink_1.png");
  delay(3000);

  drawEyePNG("/slow_blink_2.png");
  delay(3000);

  drawEyePNG("/closed_tight.png");
  delay(100);
}
