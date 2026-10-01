typedef struct {
    int pin;
    int stable;
    int last_raw;
    uint32_t changed_at;
} button_t;

int button_pressed(button_t *b) {            // Day 1 5교시
    int raw = digitalRead(b->pin);
    if (raw != b->last_raw) { b->last_raw = raw; b->changed_at = millis(); }
    if (millis() - b->changed_at > 30 && raw != b->stable) {
        b->stable = raw;
        return (raw == LOW);
    }
    return 0;
}

const int PIN_RELAY = 27, PIN_BTN = 26;
const bool ACTIVE_LOW = true;
const uint32_t MIN_SWITCH_MS = 1000;         // 접점 보호 — 1초 안에 다시 바꾸지 않는다

button_t btn = {PIN_BTN, HIGH, HIGH, 0};
bool motor_on = false;
uint32_t last_switch = 0;
int switch_count = 0;

void relay_set(bool on) {
    digitalWrite(PIN_RELAY, ACTIVE_LOW ? !on : on);
}

bool relay_request(bool on) {                // 요청이 받아들여지면 true
    if (on == motor_on) return true;
    if (switch_count > 0 && millis() - last_switch < MIN_SWITCH_MS) {   // 첫 전환은 허용
        Serial.println("너무 빠름 — 무시");
        return false;
    }
    relay_set(on);
    motor_on = on;
    last_switch = millis();
    switch_count++;
    Serial.printf("모터 %s (전환 %d회)\n", on ? "ON" : "OFF", switch_count);
    return true;
}

void setup() {
    Serial.begin(115200);
    pinMode(PIN_RELAY, OUTPUT);
    pinMode(PIN_BTN, INPUT_PULLUP);
    relay_set(false);
}

void loop() {
    if (button_pressed(&btn)) relay_request(!motor_on);
}
// → 버튼을 누를 때마다 딸깍 · 모터가 최고 속도로 돌거나 멈춘다
//   버튼을 빠르게 연타하면 "너무 빠름 — 무시"