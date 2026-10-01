const int PIN_PIR = 12, PIN_LED = 25;

void setup() {
    Serial.begin(115200);
    pinMode(PIN_PIR, INPUT);
    pinMode(PIN_LED, OUTPUT);
    Serial.println("PIR 예열 중 (약 30초 — 움직이지 마세요)");
    delay(30000);
    Serial.println("준비 완료");
}

void loop() {
    int m = digitalRead(PIN_PIR);
    digitalWrite(PIN_LED, m);
    Serial.printf("motion:%d\n", m);
    delay(100);
}