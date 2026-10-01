const int PIN_TRIG = 13, PIN_ECHO = 14;

float read_cm(void) {
    digitalWrite(PIN_TRIG, LOW);  delayMicroseconds(2);
    digitalWrite(PIN_TRIG, HIGH); delayMicroseconds(10);   // 10µs 펄스 = 측정 시작
    digitalWrite(PIN_TRIG, LOW);
    unsigned long us = pulseIn(PIN_ECHO, HIGH, 30000);     // 최대 30ms 기다림
    if (us == 0) return -1;                                // 타임아웃 = 측정 실패
    return us / 58.0f;                                     // 왕복 58µs ≈ 1cm
}

void setup() {
    Serial.begin(115200);
    pinMode(PIN_TRIG, OUTPUT);
    pinMode(PIN_ECHO, INPUT);
}

void loop() {
    float cm = read_cm();
    if (cm < 0) Serial.println("범위 밖");
    else        Serial.printf("cm:%.1f\n", cm);
    delay(100);
}
// → 손을 20cm 앞에 두면 cm:20.3 부근