#include <DHT.h>
DHT dht(27, DHT11);
SemaphoreHandle_t serialLock;

void safe_print(const char *tag, const char *msg) {
    xSemaphoreTake(serialLock, portMAX_DELAY);   // 잠금 — 다른 태스크는 여기서 기다림
    Serial.print("[");
    Serial.print(tag);
    Serial.print("] ");
    Serial.println(msg);
    xSemaphoreGive(serialLock);                  // 해제 — 반드시 짝으로
}

void taskPot(void *p) {
    char buf[32];
    for (;;) {
        snprintf(buf, sizeof(buf), "pot=%d", analogRead(34));
        safe_print("POT", buf);
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

void taskDht(void *p) {
    char buf[32];
    for (;;) {
        float t = dht.readTemperature();
        snprintf(buf, sizeof(buf), "temp=%.1f", t);
        safe_print("DHT", buf);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void setup() {
    Serial.begin(115200);
    dht.begin();
    serialLock = xSemaphoreCreateMutex();
    xTaskCreatePinnedToCore(taskPot, "pot", 3072, NULL, 1, NULL, 1);
    xTaskCreatePinnedToCore(taskDht, "dht", 4096, NULL, 1, NULL, 0);   // 다른 코어
}

void loop() { vTaskDelay(portMAX_DELAY); }
// 뮤텍스 없이: "[POT] pot=[DHT] te2041mp=24.0" 처럼 섞일 수 있다