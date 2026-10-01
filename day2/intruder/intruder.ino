// 전체 코드 — 앞 예제의 함수를 포함했으므로 그대로 업로드
const int PIN_TRIG = 13, PIN_ECHO = 14;

float read_cm(void) {
    digitalWrite(PIN_TRIG, LOW);  delayMicroseconds(2);
    digitalWrite(PIN_TRIG, HIGH); delayMicroseconds(10);   // 10µs 펄스 = 측정 시작
    digitalWrite(PIN_TRIG, LOW);
    unsigned long us = pulseIn(PIN_ECHO, HIGH, 30000);     // 최대 30ms 기다림
    if (us == 0) return -1;                                // 타임아웃 = 측정 실패
    return us / 58.0f;                                     // 왕복 58µs ≈ 1cm
}

const int PIN_PIR = 12, PIN_LED = 25;

void setup() {
    Serial.begin(115200);
    pinMode(PIN_TRIG, OUTPUT);
    pinMode(PIN_ECHO, INPUT);
    pinMode(PIN_PIR, INPUT);
    pinMode(PIN_LED, OUTPUT);
}

void loop() {
    bool moving = digitalRead(PIN_PIR);
    float cm = read_cm();
    bool near = (cm > 0 && cm < 30);
    digitalWrite(PIN_LED, moving && near);             // 움직임 + 30cm 이내
    Serial.printf("cm:%.0f,moving:%d,alert:%d\n", cm, moving * 50, (moving && near) * 100);
    delay(100);
}