#include "sensor.h"

const powered_sensor_t soil  = {34, 14, "soil"};
const powered_sensor_t water = {35, 26, "water"};

void setup() {
    Serial.begin(115200);
    sensor_init(&soil);
    sensor_init(&water);
}

void loop() {
    Serial.printf("soil:%d,water:%d\n", sensor_read(&soil), sensor_read(&water));
    if (sensor_read_count % 20 == 0) Serial.printf("# reads=%d\n", sensor_read_count);
    delay(1000);
}