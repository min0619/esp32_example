typedef struct { int pin; int period_ms; } blink_cfg_t;

blink_cfg_t red   = {25, 300};                // 전역 — 태스크보다 오래 산다
blink_cfg_t green = {26, 1000};

void taskBlink(void *param) {
    blink_cfg_t *cfg = (blink_cfg_t *)param;         // void * 를 원래 타입으로
    pinMode(cfg->pin, OUTPUT);
    for (;;) {
        digitalWrite(cfg->pin, !digitalRead(cfg->pin));
        vTaskDelay(pdMS_TO_TICKS(cfg->period_ms));
    }
}

void setup() {
    xTaskCreatePinnedToCore(taskBlink, "red", 2048, &red ,   1, NULL, 1);
    xTaskCreatePinnedToCore(taskBlink, "green", 2048, &green, 1, NULL, 1);
}
void loop() { vTaskDelay(portMAX_DELAY); }