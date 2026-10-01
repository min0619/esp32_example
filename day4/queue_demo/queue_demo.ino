void setup() {
  // put your setup code here, to run once:

}

void loop() {typedef struct {
    int raw;
    uint32_t t_ms;
} sample_t;

QueueHandle_t q;

void taskSensor(void *p) {                      // 생산자
    for (;;) {
        sample_t s = { analogRead(34), millis() };
        if (xQueueSend(q, &s, 0) != pdTRUE)     // 0 = 가득 차면 기다리지 않음
            Serial.println("큐 가득 — 버림");
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void taskShow(void *p) {                        // 소비자
    sample_t s;
    for (;;) {
        xQueueReceive(q, &s, portMAX_DELAY);    // 올 때까지 잠 — CPU 를 안 쓴다
        ledcWrite(25, s.raw / 16);              // 0~4095 → 0~255
        Serial.printf("raw:%d,age:%lu\n", s.raw, millis() - s.t_ms);
    }
}

void setup() {
    Serial.begin(115200);
    ledcAttach(25, 5000, 8);
    q = xQueueCreate(8, sizeof(sample_t));      // sample_t 8개 칸
    xTaskCreatePinnedToCore(taskSensor, "sensor", 3072, NULL, 2, NULL, 1);
    xTaskCreatePinnedToCore(taskShow,   "show",   3072, NULL, 1, NULL, 1);
}

void loop() { vTaskDelay(portMAX_DELAY); }
  // put your main code here, to run repeatedly:

}
