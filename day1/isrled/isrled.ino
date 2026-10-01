const int PIN_BTN = 25, PIN_LED = 33;
volatile bool flag = false;
volatile uint32_t last_ms = 0;

void  IRAM_ATTR onButton() {
    uint32_t now = millis();
    if (now - last_ms > 50) {
        flag = true;
        last_ms = now;
    }
}

void setup() {
    pinMode(PIN_BTN, INPUT_PULLUP);
    pinMode(PIN_LED, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(PIN_BTN), onButton, FALLING );
}

void loop() {
    if (flag) {
        flag = false;
        digitalWrite(PIN_LED, !digitalRead(PIN_LED));
    }
}