const int SEG_PINS[8] = {12, 13, 26, 27, 14, 32, 33, 25};   // a b c d e f g dp
const bool COMMON_ANODE = false;                            // CA 면 true

//                         dp g f e d c b a
const uint8_t DIGITS[10] = {
    0x3F,   // 0  0 0 1 1 1 1 1 1
    0x06,   // 1  0 0 0 0 0 1 1 0
    0x5B,   // 2  0 1 0 1 1 0 1 1
    0x4F,   // 3
    0x66,   // 4
    0x6D,   // 5
    0x7D,   // 6
    0x07,   // 7
    0x7F,   // 8
    0x6F,   // 9
};

void seg_show(uint8_t pattern) {
    if (COMMON_ANODE) pattern = ~pattern;           // CA 는 뒤집는다
    for (int i = 0; i < 8; i++) {
        digitalWrite(SEG_PINS[i], (pattern >> i) & 1);   // i 번째 비트
    }
}

void setup() {
    for (int i = 0; i < 8; i++) pinMode(SEG_PINS[i], OUTPUT);
}

void loop() {
    for (int d = 0; d < 10; d++) {
        seg_show(DIGITS[d]);
        delay(700);
    }
    seg_show(0x80);                                  // 점만
    delay(700);
}