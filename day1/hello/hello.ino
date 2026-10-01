void setup() {
    Serial.begin(115200);               // PC 쪽 시리얼 모니터도 115200 으로
    delay(500);
    Serial.println("Hello ESP32");
    Serial.printf("Chip  : %s rev %d\n", ESP.getChipModel(), ESP.getChipRevision());
    Serial.printf("Cores : %d\n", ESP.getChipCores());               // → 2
    Serial.printf("CPU   : %lu MHz\n", ESP.getCpuFreqMHz());         // → 240
    Serial.printf("Flash : %lu bytes\n", ESP.getFlashChipSize());    // → 4194304
    Serial.printf("Heap  : %lu bytes free\n", ESP.getFreeHeap());
}

void loop() {
    Serial.printf("uptime %lu ms\n", millis());
    delay(1000);
}