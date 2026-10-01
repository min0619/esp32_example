const int LED_PINS[] = {25, 33, 32};           // 빨강, 노랑, 초록
const int N_LED = sizeof(LED_PINS) / sizeof(LED_PINS[0]);

void setup() {
    for (int i = 0; i < N_LED; i++) {
        pinMode(LED_PINS[i], OUTPUT);
    }
}

void loop() {
    for (int i = 0; i < N_LED; i++) {
        digitalWrite(LED_PINS[i], HIGH);       // 3.3V 출력
        delay(1000);
        digitalWrite(LED_PINS[i], LOW);        // 0V 출력
    }
}