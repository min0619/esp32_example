const int PIN_BTN = 27;

void setup() {
    Serial.begin(115200);
    pinMode(PIN_BTN, INPUT);          // 풀업 없음
}

void loop() {
    Serial.println(digitalRead(PIN_BTN));
    delay(100);
}
// → 0 1 1 0 1 ...  (손을 가까이 대면 더 요동)