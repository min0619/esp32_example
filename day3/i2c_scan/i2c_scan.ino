#include <Wire.h>

void setup() {
    Serial.begin(115200);
    Wire.begin(21, 22);                     // SDA, SCL
}

void loop() {
    int found = 0;
    for (uint8_t addr = 1; addr < 127; addr++) {
        Wire.beginTransmission(addr);
        uint8_t err = Wire.endTransmission();     // 0 = 응답(ACK) 있음
        if (err == 0) {
            Serial.printf("발견: 0x%02X\n", addr);
            found++;
        }
    }
    Serial.printf("총 %d개\n\n", found);
    delay(3000);
}
// → 발견: 0x48