#include <Wire.h>
#include <LiquidCrystal.h>

typedef struct {
    uint8_t addr;
    uint8_t last[4];        // 채널별 마지막 값
    int errors;             // 통신 실패 횟수
} pcf8591_t;

int pcf_read(pcf8591_t *p, uint8_t ch) {
    Wire.beginTransmission(p->addr);
    Wire.write(0x40 | (ch & 0x03));
    if (Wire.endTransmission() != 0) { p->errors++; return -1; }
    if (Wire.requestFrom(p->addr, (uint8_t)2) != 2) { p->errors++; return -1; }
    Wire.read();
    p->last[ch & 0x03] = Wire.read();
    return p->last[ch & 0x03];
}

pcf8591_t pcf = {0x48, {0}, 0};
LiquidCrystal lcd(13, 12, 14, 27, 26, 25);

void setup() {
    Wire.begin(21, 22);
    lcd.begin(16, 2);
}

void loop() {
    int v = pcf_read(&pcf, 0);
    char buf[17];
    snprintf(buf, sizeof(buf), "AIN0:%3d err:%2d", v < 0 ? 0 : v, pcf.errors);
    lcd.setCursor(0, 0);
    lcd.print(buf);
    delay(100);
}