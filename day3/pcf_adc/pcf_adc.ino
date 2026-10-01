#include <Wire.h>
const uint8_t PCF = 0x48;

int pcf_read(uint8_t ch) {
    Wire.beginTransmission(PCF);
    Wire.write(0x40 | (ch & 0x03));          // DAC 켜기 + 채널
    if (Wire.endTransmission() != 0) return -1;
    Wire.requestFrom(PCF, (uint8_t)2);        // 2바이트 요청
    Wire.read();                              // 첫 바이트 = 이전 변환 값 → 버림
    return Wire.read();                       // 0 ~ 255
}

void setup() {
    Serial.begin(115200);
    Wire.begin(21, 22);
}

void loop() {
    int v = pcf_read(0);
    if (v < 0) Serial.println("PCF8591 응답 없음");
    else Serial.printf("ain0:%d\n", v);
    delay(100);
}
// → 손으로 조도 센서를 가리면 값이 작아진다 (0 ~ 255) — 모듈의 IN0 = 칩의 AIN0