#include <Wire.h>
const uint8_t PCF = 0x48;

bool pcf_write_dac(uint8_t value) {
    Wire.beginTransmission(PCF);
    Wire.write(0x40);                         // DAC 켜기
    Wire.write(value);                        // 0 ~ 255 → 0 ~ VCC
    return Wire.endTransmission() == 0;
}

void setup() { Wire.begin(21, 22); }

void loop() {
    for (int v = 0; v < 256; v += 4)   { pcf_write_dac(v); delay(15); }
    for (int v = 255; v >= 0; v -= 4) { pcf_write_dac(v); delay(15); }
}
// → 모듈 위 Aout LED 가 부드럽게 밝아졌다 어두워진다 — PWM 이 아니라 진짜 전압