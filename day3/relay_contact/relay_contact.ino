const int PIN_RELAY = 27;
const bool ACTIVE_LOW = true;               // ① 에서 확인한 값

void relay_set(bool on) {
    digitalWrite(PIN_RELAY, ACTIVE_LOW ? !on : on);
}

void setup() {
    Serial.begin(115200);
    pinMode(PIN_RELAY, OUTPUT);
    relay_set(false);
}

void loop() {
    relay_set(true);
    Serial.println("코일 ON  → COM–NO 연결 → 빨강");
    delay(1500);
    relay_set(false);
    Serial.println("코일 OFF → COM–NC 연결 → 초록");
    delay(1500);
}