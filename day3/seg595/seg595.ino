const int PIN_DS = 27, PIN_SH = 25, PIN_ST = 26;
const uint8_t DIGITS[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

void write595(uint8_t data) {
    digitalWrite(PIN_ST, LOW);
    shiftOut(PIN_DS, PIN_SH, MSBFIRST, data);    // Arduino 내장 함수 — my_shift_out 과 같다
    digitalWrite(PIN_ST, HIGH);
}

void setup() {
    pinMode(PIN_DS, OUTPUT); pinMode(PIN_SH, OUTPUT); pinMode(PIN_ST, OUTPUT);
}

void loop() {
    for (int d = 0; d < 10; d++) {
        write595(DIGITS[d]);
        delay(600);
    }
}