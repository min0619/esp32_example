TaskHandle_t hWork = NULL;

void taskWork(void *param) {
    for (;;) {
        int raw = analogRead(34);
        char buf[64];                                 // 지역 배열은 스택을 쓴다
        snprintf(buf, sizeof(buf), "pot=%d", raw);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void setup() {
    Serial.begin(115200);
    xTaskCreatePinnedToCore(taskWork, "work", 3072, NULL, 2, &hWork, 1);
}

void loop() {
    UBaseType_t freeStack = uxTaskGetStackHighWaterMark(hWork);   // 가장 적게 남았던 양
    Serial.printf("work 스택 여유 %u 바이트 · 코어 %d · 힙 여유 %u\n",
                  freeStack, xPortGetCoreID(), ESP.getFreeHeap());
    vTaskDelay(pdMS_TO_TICKS(1000));
}
// → work 스택 여유 2140 바이트 · 코어 1 · 힙 여유 290000