const int PIN_SOIL = 34, PIN_SOIL_PWR = 14;

int read_soil(void) {
    digitalWrite(PIN_SOIL_PWR, HIGH);      // 전원 ON
    delay(10);                             // 안정될 때까지 잠깐
    int v = analogRead(PIN_SOIL);
    digitalWrite(PIN_SOIL_PWR, LOW);       // 바로 OFF
    return v;
}

void setup() {
    Serial.begin(115200);
    pinMode(PIN_SOIL_PWR, OUTPUT);
    digitalWrite(PIN_SOIL_PWR, LOW);
}

void loop() {
    Serial.printf("soil:%d\n", read_soil());
    delay(1000);                           // 1초에 10ms 만 켜짐 → 1%
}
// → 공기 중: 0 근처 / 젖은 휴지나 물컵: 값이 크게 오른다