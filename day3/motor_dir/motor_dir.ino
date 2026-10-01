const int PIN_EN = 13, PIN_IN1 = 12, PIN_IN2 = 14;

void motor_dir(int in1, int in2, const char *msg) {
    digitalWrite(PIN_IN1, in1);
    digitalWrite(PIN_IN2, in2);
    Serial.println(msg);
}

void setup() {
    Serial.begin(115200);
    pinMode(PIN_EN, OUTPUT); pinMode(PIN_IN1, OUTPUT); pinMode(PIN_IN2, OUTPUT);
    digitalWrite(PIN_EN, HIGH);              // 속도 최대 (PWM 은 다음 예제)
}

void loop() {
    motor_dir(HIGH, LOW,  "정방향");  delay(2000);
    motor_dir(LOW,  LOW,  "정지");    delay(1000);      // 반대로 돌리기 전에 멈춘다
    motor_dir(LOW,  HIGH, "역방향");  delay(2000);
    motor_dir(HIGH, HIGH, "브레이크"); delay(1000);
}