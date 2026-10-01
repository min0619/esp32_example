const int LED_R = 27, LED_G = 26;

void taskRed(void *param) {
    for (;;) {                                    // 태스크는 끝나지 않는다
        digitalWrite(LED_R, !digitalRead(LED_R));
        vTaskDelay(pdMS_TO_TICKS(300));           // 300ms 쉬는 동안 다른 태스크가 돈다
    }
}

void taskGreen(void *param) {
    for (;;) {
        digitalWrite(LED_G, !digitalRead(LED_G));
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(LED_R, OUTPUT);
    pinMode(LED_G, OUTPUT);
    //                      함수      이름     스택   매개변수 우선순위 핸들  코어
    xTaskCreatePinnedToCore(taskRed,   "red",   2048, NULL,   1,      NULL, 1);
    xTaskCreatePinnedToCore(taskGreen, "green", 2048, NULL,   1,      NULL, 1);
}

void loop() {
    Serial.printf("loop 도 돈다 %lu\n", millis() / 1000);
    vTaskDelay(pdMS_TO_TICKS(2000));
}
// → 빨강 0.3초, 초록 1초 주기로 따로 깜빡이고, 시리얼에는 2초마다 한 줄