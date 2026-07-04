#include "Globals.h"

Adafruit_PWMServoDriver pwmLower = Adafruit_PWMServoDriver(LOWER_PCA_ADDR);
Adafruit_PWMServoDriver pwmUpper = Adafruit_PWMServoDriver(UPPER_PCA_ADDR);

int servoMin[16];
int servoMax[16];
int neutralAngles[16];

bool autonomousMode = false;
bool animationActive = false;
bool oneShotActive = false;
bool isSitting = false;
bool isStanding = false;

String currentMood = "NEUTRAL";
String currentAnimation = "";

int energyLevel = 50;
int boredStretchCount = 0;

unsigned long lastInteractionTime = 0;
unsigned long lastStandTime = 0;
unsigned long lastKevinSeen = 0;
unsigned long lastKevinGreeting = 0;

bool hasSeenKevinSinceBoot = false;

bool noFaceActive = false;
bool noFaceJustLooked = false;
int noFaceCycle = 0;
unsigned long noFaceStart = 0;

int lastKnownHeadPos = neutral_head_yaw;