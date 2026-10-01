const int PIN_LED = 33;

void setup() {
    ledcAttach(PIN_LED, 5000, 8);        // 핀, 주파수 5kHz, 8비트(0~255)
}

void loop() {
    for (int d = 0; d <= 255; d++) { ledcWrite(PIN_LED, d); delay(5); }
    for (int d = 255; d >= 0; d--) { ledcWrite(PIN_LED, d); delay(5); }
}