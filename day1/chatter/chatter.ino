const int PIN_BTN = 27;
int last = HIGH;
int edges = 0;

void setup() {
    Serial.begin(115200);
    pinMode(PIN_BTN, INPUT_PULLUP);
}

void loop() {
    int now = digitalRead(PIN_BTN);
    if (last == HIGH && now == LOW) {        // 눌리는 순간(하강 엣지)
        edges++;
        Serial.printf("press #%d\n", edges);
    }
    last = now;
}
// 한 번 눌렀는데 → press #1 / press #2 / press #3 가 찍히는 경우가 있음