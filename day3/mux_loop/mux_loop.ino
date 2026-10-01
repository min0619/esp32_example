const int PIN_DS = 12, PIN_SH = 13, PIN_ST = 14;
const int DIG[4] = {27, 26, 25, 33};                 // D1 ~ D4
const uint8_t DIGITS[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
uint8_t disp[4] = {DIGITS[1], DIGITS[2], DIGITS[3], DIGITS[4]};   // "1234"

void write595(uint8_t d) {
    digitalWrite(PIN_ST, LOW);
    shiftOut(PIN_DS, PIN_SH, MSBFIRST, d);
    digitalWrite(PIN_ST, HIGH);
}

void show_digit(int k) {
    for (int i = 0; i < 4; i++) digitalWrite(DIG[i], HIGH);   // 전부 끄고 (CC: HIGH = 꺼짐)
    write595(disp[k]);                                        // 모양을 바꾼 뒤
    digitalWrite(DIG[k], LOW);                                // 그 자리만 켠다
}

void setup() {
    pinMode(PIN_DS, OUTPUT); pinMode(PIN_SH, OUTPUT); pinMode(PIN_ST, OUTPUT);
    for (int i = 0; i < 4; i++) pinMode(DIG[i], OUTPUT);
}

void loop() {
    for (int k = 0; k < 4; k++) {
        show_digit(k);
        delay(3);                     // 한 자리 3ms → 4자리 12ms → 약 83Hz
    }
     delay(100);                    // ← 이 줄을 켜면? 한 자리만 오래 켜져 깜빡인다
}