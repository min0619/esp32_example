void print_bits(uint32_t v) {
    for (int i = 31; i >= 0; i--) {
        Serial.print((v >> i) & 1);
        if (i % 8 == 0 && i) Serial.print('_');
    }
    Serial.println();
}

void setup() {
    Serial.begin(115200);
    delay(500);
    uint32_t reg = 0;
    reg |= (1UL << 25);              // 25번 비트 켜기
    reg |= (1UL << 27);              // 27번 비트 켜기
    print_bits(reg);                 // → 00001010_00000000_00000000_00000000
    reg &= ~(1UL << 25);             // 25번 비트 끄기
    print_bits(reg);                 // → 00001000_00000000_00000000_00000000
    Serial.println((reg >> 27) & 1); // → 1  (27번 비트 검사)
}

void loop() {}