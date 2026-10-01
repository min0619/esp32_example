const int PIN_RELAY = 27;
const bool ACTIVE_LOW = true;               // 모듈에 따라 LOW 에서 켜진다

void relay_set(bool on) {
    digitalWrite(PIN_RELAY, ACTIVE_LOW ? !on : on);
}

void setup() {
    Serial.begin(115200);
    pinMode(PIN_RELAY, OUTPUT);
    relay_set(false);
    Serial.println("1 = ON, 0 = OFF");
}

void loop() {
    if (Serial.available()) {
        char c = Serial.read();
        if (c == '1') { relay_set(true);  Serial.println("ON");  }
        if (c == '0') { relay_set(false); Serial.println("OFF"); }
    }
}
// → 1 을 보내면 딸깍 소리와 함께 모듈 LED 가 켜진다