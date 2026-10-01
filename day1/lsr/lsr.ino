const int PIN_BTN = 25;

volatile uint32_t press_count = 0;
volatile uint32_t last_isr_ms = 0;
portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR onButton() {
    uint32_t now = millis();
    if (now - last_isr_ms > 50) {             // ISR 안의 간단한 디바운스
        portENTER_CRITICAL_ISR(&mux);         // 뮤텍스
        press_count++;
        portEXIT_CRITICAL_ISR(&mux);
        last_isr_ms = now;
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(PIN_BTN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(PIN_BTN), onButton, FALLING);
}

void loop() {
    portENTER_CRITICAL(&mux);
    uint32_t n = press_count;                 // 읽고
    press_count = 0;                          // 비우기를 한 덩어리로
    portEXIT_CRITICAL(&mux);

    if (n) Serial.printf("pressed %lu time(s)\n", n);
    delay(2000);                              // 여전히 바빠도
}
// 2초 사이에 5번 누르면 → pressed 5 time(s)