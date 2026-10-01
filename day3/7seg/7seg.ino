const int SEG_PINS[8] = {12, 13, 26, 27, 14, 32, 33, 25};   // a b c d e f g dp
const char *NAMES[8] = {"a", "b", "c", "d", "e", "f", "g", "dp"};

void setup() {
    Serial.begin(115200);
    for (int i = 0; i < 8; i++) pinMode(SEG_PINS[i], OUTPUT);
}

void loop() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) digitalWrite(SEG_PINS[j], LOW);
        digitalWrite(SEG_PINS[i], HIGH);            // 하나만 HIGH
        Serial.printf("%s 켜짐\n", NAMES[i]);
        delay(500);
    }
}
// → 공통 음극(CC): 하나씩 순서대로 켜진다
// → 공통 양극(CA): 하나만 꺼지고 나머지가 켜진다 (또는 전부 꺼짐 — COM 을 3V3 로 옮긴다)