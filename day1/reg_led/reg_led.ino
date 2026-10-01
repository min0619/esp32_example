#include "soc/soc.h"
#include "soc/gpio_reg.h"

#define LED_MASK ((1UL << 25))
#define LED_MASK_1 ((1UL << 1)|(1UL<<0))

void setup() {
    pinMode(25, OUTPUT);             // 방향 설정은 그대로 필요
    pinMode(33, OUTPUT);
    pinMode(32, OUTPUT);
}

void loop() {
    REG_WRITE(GPIO_OUT_W1TS_REG, LED_MASK);   // 3개 동시에 ON
    REG_WRITE(GPIO_OUT1_W1TS_REG, LED_MASK_1);
    delay(500);
    REG_WRITE(GPIO_OUT_W1TC_REG, LED_MASK);   // 3개 동시에 OFF
    REG_WRITE(GPIO_OUT1_W1TC_REG, LED_MASK_1);
    delay(500);
}