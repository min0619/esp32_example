#include "soc/soc.h"
#include "soc/gpio_reg.h"

const int PIN = 25;
const long N = 100000;

void setup() {
    Serial.begin(115200);
    delay(500);
    pinMode(PIN, OUTPUT);

    uint32_t t0 = micros();
    for (long i = 0; i < N; i++) {
        digitalWrite(PIN, HIGH);
        digitalWrite(PIN, LOW);
    }
    uint32_t t_api = micros() - t0;

    t0 = micros();
    for (long i = 0; i < N; i++) {
        REG_WRITE(GPIO_OUT_W1TS_REG, 1UL << PIN);
        REG_WRITE(GPIO_OUT_W1TC_REG, 1UL << PIN);
    }
    uint32_t t_reg = micros() - t0;

    Serial.printf("digitalWrite : %lu us\n", t_api);
    Serial.printf("register     : %lu us\n", t_reg);
    Serial.printf("ratio        : %.1f x\n", (float)t_api / t_reg);
}

void loop() {}