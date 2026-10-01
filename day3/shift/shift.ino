const int PIN_DS = 27, PIN_SH = 25, PIN_ST = 26;

void my_shift_out(uint8_t data) {          // MSB(bit7) 먼저
    for (int i = 7; i >= 0; i--) {
        digitalWrite(PIN_DS, (data >> i) & 1);   // 1) 비트를 DS 에 올리고
        digitalWrite(PIN_SH, HIGH);              // 2) 클럭 ↑ → 한 칸 밀림
        digitalWrite(PIN_SH, LOW);
    }
}

void write595(uint8_t data) {
    digitalWrite(PIN_ST, LOW);
    my_shift_out(data);
    digitalWrite(PIN_ST, HIGH);                  // 3) 래치 ↑ → 8개 출력이 동시에 바뀜
}

void setup() {
    Serial.begin(115200);
    pinMode(PIN_DS, OUTPUT); pinMode(PIN_SH, OUTPUT); pinMode(PIN_ST, OUTPUT);
}

void loop() {
    for (int i = 0; i < 8; i++) {
        write595(1 << i);                        // Q0 → Q7 하나씩
        Serial.printf("0x%02X\n", 1 << i);
        delay(400);
    }
}
// → 7-Segment 의 a, b, c, … dp 가 차례로 켜진다