const int COIL[4] = {13, 12, 14, 27};        // IN1 ~ IN4
const uint8_t SEQ[8] = {                     // bit0 = IN1 … bit3 = IN4
    0b0001, 0b0011, 0b0010, 0b0110,
    0b0100, 0b1100, 0b1000, 0b1001,
};
int phase = 0;

void step_once(int dir) {                    // dir = +1 또는 -1
    phase = (phase + dir + 8) % 8;           // 음수가 되지 않게 +8
    for (int i = 0; i < 4; i++)
        digitalWrite(COIL[i], (SEQ[phase] >> i) & 1);
}

void step_motor(int steps, int us_per_step) {
    int dir = steps > 0 ? 1 : -1;
    for (int s = 0; s < abs(steps); s++) {
        step_once(dir);
        delayMicroseconds(us_per_step);
    }
    for (int i = 0; i < 4; i++) digitalWrite(COIL[i], LOW);   // 멈추면 코일 끄기 (발열 방지)
}

void setup() {
    for (int i = 0; i < 4; i++) pinMode(COIL[i], OUTPUT);
}

void loop() {
    step_motor(4096, 1000);      // 한 바퀴 정방향
    delay(500);
    step_motor(-1024, 1000);     // 90° 역방향
    delay(500);
}