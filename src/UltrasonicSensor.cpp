#include "UltrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor(uint8_t trigPin, uint8_t echoPin, const char *name,
                                   uint8_t smoothingSamples, unsigned long timeoutUs)
    : _trigPin(trigPin), _echoPin(echoPin), _name(name),
      _timeoutUs(timeoutUs), _smoothingSamples(smoothingSamples), _historyIndex(0) {
    _history = new float[_smoothingSamples];
    for (uint8_t i = 0; i < _smoothingSamples; i++) {
        _history[i] = -1;
    }
}

void UltrasonicSensor::begin() {
    pinMode(_trigPin, OUTPUT);
    pinMode(_echoPin, INPUT);
}

float UltrasonicSensor::read() {
    float distance = _readRaw();
    _history[_historyIndex] = distance;
    _historyIndex = (_historyIndex + 1) % _smoothingSamples;
    return distance;
}

float UltrasonicSensor::getSmoothedDistance() const {
    return _computeSmoothed();
}

float UltrasonicSensor::_readRaw() {
    digitalWrite(_trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trigPin, LOW);

    long duration = pulseIn(_echoPin, HIGH, _timeoutUs);
    if (duration == 0) return -1;

    return (duration * 0.0343f) / 2.0f;
}

float UltrasonicSensor::_computeSmoothed() const {
    float sum = 0;
    uint8_t count = 0;
    for (uint8_t i = 0; i < _smoothingSamples; i++) {
        if (_history[i] >= 0) {
            sum += _history[i];
            count++;
        }
    }
    return (count > 0) ? sum / count : -1;
}
