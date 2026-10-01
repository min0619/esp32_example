typedef struct {
    int pin;
    int stable;            // 확정된 상태
    int last_raw;          // 직전에 읽은 원시 값
    uint32_t changed_at;   // 원시 값이 마지막으로 바뀐 시각
} button_t;

// 눌림(HIGH → LOW)이 확정되는 순간에만 1 을 반환
int button_pressed(button_t *b) {
    int raw = digitalRead(b->pin);
    if (raw != b->last_raw) {                 // 값이 흔들리면 타이머 재시작
        b->last_raw = raw;
        b->changed_at = millis();
    }
    if (millis() - b->changed_at > 30 && raw != b->stable) {
        b->stable = raw;                      // 30ms 동안 그대로면 확정
        return (raw == LOW);
    }
    return 0;
}
button_t tilt = {26, HIGH,HIGH, 0};
button_t btn = {27, HIGH, HIGH, 0};
const int PIN_LED = 25;
int led = 0;

void setup() {
    Serial.begin(115200);
    pinMode(btn.pin, INPUT_PULLUP);
    pinMode(tilt.pin, INPUT_PULLUP);
    pinMode(PIN_LED, OUTPUT);
    pinMode(32,OUTPUT);
}

void loop() {
        if (button_pressed(&btn)) {
        led = !led;
        digitalWrite(PIN_LED, led);
        Serial.printf("LED %s\n", led ? "ON" : "OFF");
    }
    if (button_pressed(&btn))  Serial.println("button");
    if (button_pressed(&tilt)) Serial.println("tilted");
    digitalWrite(32, tilt.stable == LOW);     // 기울어져 있는 동안 초록 LED
}
// → 한 번 누를 때마다 정확히 한 줄: LED ON / LED OFF / ...