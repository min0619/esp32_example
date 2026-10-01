#include <Arduino.h>
#include "sensor.h"

int sensor_read_count = 0;       // 정의는 딱 한 곳에만

void sensor_init(const powered_sensor_t *s) {
    pinMode(s->pwr, OUTPUT);
    digitalWrite(s->pwr, LOW);
}

int sensor_read(const powered_sensor_t *s) {
    digitalWrite(s->pwr, HIGH);
    delay(10);
    int v = analogRead(s->pin);
    digitalWrite(s->pwr, LOW);
    sensor_read_count++;
    return v;
}