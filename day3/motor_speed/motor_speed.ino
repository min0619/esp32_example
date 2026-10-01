const int PIN_EN = 13, PIN_IN1 = 12, PIN_IN2 = 14;

void motor_set(int speed) {                  // -255 ~ +255, 부호 = 방향
    if (speed > 255) speed = 255;
    if (speed < -255) speed = -255;
    digitalWrite(PIN_IN1, speed > 0);
    digitalWrite(PIN_IN2, speed < 0);
    ledcWrite(PIN_EN, abs(speed));
}

void ramp_to(int *cur, int target) {         // 한 번에 조금씩
    while (*cur != target) {
        *cur += (target > *cur) ? 5 : -5;
        if (abs(target - *cur) < 5) *cur = target;
        motor_set(*cur);
        delay(20);
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(PIN_IN1, OUTPUT); pinMode(PIN_IN2, OUTPUT);
    ledcAttach(PIN_EN, 20000, 8);            // 20kHz — 귀에 거슬리는 소리가 안 들린다
}

void loop() {
    static int speed = 0;
    ramp_to(&speed, 200);  delay(1500);
    ramp_to(&speed, 0);    delay(500);
    ramp_to(&speed, -200); delay(1500);
    ramp_to(&speed, 0);    delay(500);
}