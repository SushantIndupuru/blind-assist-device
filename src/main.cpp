#include <Arduino.h>
#include "config.h"
#include "UltrasonicSensor.h"
#include "HapticMotor.h"

// ── Objects ───────────────────────────────────────────────────────────────────

UltrasonicSensor leftSensor(LEFT_TRIG_PIN, LEFT_ECHO_PIN, "LEFT", SMOOTHING_SAMPLES);
UltrasonicSensor rightSensor(RIGHT_TRIG_PIN, RIGHT_ECHO_PIN, "RIGHT", SMOOTHING_SAMPLES);

HapticMotor leftMotor(LEFT_MOTOR_PIN_1, LEFT_MOTOR_PIN_2);
HapticMotor rightMotor(RIGHT_MOTOR_PIN_1, RIGHT_MOTOR_PIN_2);

// ── Helpers ───────────────────────────────────────────────────────────────────

// Map a smoothed distance (cm) to a PWM vibration level.
uint8_t distanceToVibration(float distanceCm) {
  if (distanceCm < 0) return MIN_VIBRATION;
  if (distanceCm <= MIN_DISTANCE_CM) return MAX_VIBRATION;
  if (distanceCm >= MAX_DISTANCE_CM) return MIN_VIBRATION;
  return map(distanceCm, MIN_DISTANCE_CM, MAX_DISTANCE_CM, MAX_VIBRATION, MIN_VIBRATION);
}

void updateStatusLed() {
  bool leftClose = leftMotor.getLevel() > CLOSE_THRESHOLD;
  bool rightClose = rightMotor.getLevel() > CLOSE_THRESHOLD;
  digitalWrite(STATUS_LED_PIN, (leftClose || rightClose) ? HIGH : LOW);
}

void printStatus() {
  bool leftClose = leftMotor.getLevel() > CLOSE_THRESHOLD;
  bool rightClose = rightMotor.getLevel() > CLOSE_THRESHOLD;

  Serial.print(" | L=");
  Serial.print(leftMotor.getLevel());
  Serial.print(" R=");
  Serial.print(rightMotor.getLevel());

  if (leftClose && rightClose) Serial.println(" | BOTH SIDES CLOSE");
  else if (leftClose) Serial.println(" | LEFT CLOSE");
  else if (rightClose) Serial.println(" | RIGHT CLOSE");
  else Serial.println(" | CLEAR");
}

void testMotors() {
  Serial.println("Testing motors...");
  leftMotor.setLevel(100);
  rightMotor.setLevel(100);
  delay(300);
  leftMotor.setLevel(0);
  rightMotor.setLevel(0);
  Serial.println("Motor test done.");
}

// ── Setup ─────────────────────────────────────────────────────────────────────

void setup() {
  Serial.begin(9600);
  Serial.println("=== Sonar Haptic Device ===");

  leftSensor.begin();
  rightSensor.begin();
  leftMotor.begin();
  rightMotor.begin();

  pinMode(STATUS_LED_PIN, OUTPUT);

  // Startup blink
  for (int i = 0; i < 3; i++) {
    digitalWrite(STATUS_LED_PIN, HIGH);
    delay(100);
    digitalWrite(STATUS_LED_PIN, LOW);
    delay(100);
  }

  testMotors();

  Serial.println("Running. Each sensor alternates every " + String(SENSOR_POLL_INTERVAL_MS) + "ms.");
  Serial.println("----------------------------");
}

// ── Loop ──────────────────────────────────────────────────────────────────────

void loop() {
  static unsigned long lastPollTime = 0;
  static bool readLeftNext = true;

  unsigned long now = millis();
  if (now - lastPollTime < SENSOR_POLL_INTERVAL_MS) return;
  lastPollTime = now;

  if (readLeftNext) {
    leftSensor.read();
    float dist = leftSensor.getSmoothedDistance();
    leftMotor.setLevel(distanceToVibration(dist));

    Serial.print("LEFT: ");
    if (dist < 0) Serial.print("TIMEOUT");
    else {
      Serial.print(dist, 1);
      Serial.print("cm");
    }
    Serial.print(" -> vib=");
    Serial.print(leftMotor.getLevel());
  } else {
    rightSensor.read();
    float dist = rightSensor.getSmoothedDistance();
    rightMotor.setLevel(distanceToVibration(dist));

    Serial.print("RIGHT: ");
    if (dist < 0) Serial.print("TIMEOUT");
    else {
      Serial.print(dist, 1);
      Serial.print("cm");
    }
    Serial.print(" -> vib=");
    Serial.print(rightMotor.getLevel());
  }

  printStatus();
  updateStatusLed();

  readLeftNext = !readLeftNext;
}
