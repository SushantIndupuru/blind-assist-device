#pragma once

// ── Sensor pins ──────────────────────────────────────────────────────────────
#define LEFT_TRIG_PIN   8
#define LEFT_ECHO_PIN   9
#define RIGHT_TRIG_PIN  6
#define RIGHT_ECHO_PIN  7

// ── Motor pins ────────────────────────────────────────────────────────────────
#define LEFT_MOTOR_PIN_1  3
#define LEFT_MOTOR_PIN_2  2
#define RIGHT_MOTOR_PIN_1 5
#define RIGHT_MOTOR_PIN_2 4

// ── Status LED ────────────────────────────────────────────────────────────────
#define STATUS_LED_PIN 13

// ── Distance thresholds (cm) ──────────────────────────────────────────────────
#define MIN_DISTANCE_CM  5
#define MAX_DISTANCE_CM  250

// ── Vibration range (PWM 0–255) ───────────────────────────────────────────────
#define MIN_VIBRATION 0
#define MAX_VIBRATION 50

// ── Timing ────────────────────────────────────────────────────────────────────
// How often to poll one sensor (ms). Both sides are read in alternating cycles,
// so each side updates at 2× this interval.
#define SENSOR_POLL_INTERVAL_MS 100

// ── Smoothing ─────────────────────────────────────────────────────────────────
#define SMOOTHING_SAMPLES 3

// ── Alert threshold ───────────────────────────────────────────────────────────
// Vibration level above which we consider an object "close" for LED/Serial warnings.
#define CLOSE_THRESHOLD 100
