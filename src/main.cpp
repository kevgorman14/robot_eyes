#include <Arduino.h>
#include <Eyes.h>
#include <Animations.h>
#include <Wire.h>

const int I2C_SDA = 4;
const int I2C_SCL = 5;

void setup() {
  Wire.begin(I2C_SDA, I2C_SCL);

  setupServoLimits();

  pwmLower.begin();
  pwmLower.setPWMFreq(SERVO_FREQ);
  pwmUpper.begin();
  pwmUpper.setPWMFreq(SERVO_FREQ);

  animExcited(10);

  eyesInit();  // Initialize everything

  // Test
  eyesNeutral();
  delay(1000);

  eyesHappy();
  delay(1000);

  eyesBlink();
  delay(1000);

  eyesLookLeft();
  delay(1000);

  eyesLookRight();
  delay(1000);

  eyesSlowBlink();

}

void loop() {
  eyesBlink();
  delay(5000);
}
