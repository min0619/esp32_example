const int PIN_BTN = 25;
int count = 0;

void setup() {
    Serial.begin(115200);
    pinMode(PIN_BTN, INPUT_PULLUP);
}

void loop() {
    if (digitalRead(PIN_BTN) == LOW) count++;
    Serial.printf("count = %d\n", count);
    delay(2000);                    // 다른 일을 하느라 바쁜 상황
}
// 2초 사이에 버튼을 빠르게 5번 눌러도 → count 는 0 또는 1 만 증가