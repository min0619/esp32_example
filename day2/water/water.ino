const int PIN_WATER = 35, PIN_WATER_PWR = 26;

int read_water(void) {
    digitalWrite(PIN_WATER_PWR, HIGH);
    delay(10);
    int v = analogRead(PIN_WATER);
    digitalWrite(PIN_WATER_PWR, LOW);
    return v;
}

void setup() {
    Serial.begin(115200);
    pinMode(PIN_WATER_PWR, OUTPUT);
}

void loop() {
    Serial.printf("water:%d\n", read_water());
    delay(1000);
}
// → 센서를 물에 조금씩 담글수록 값이 계단식으로 오른다