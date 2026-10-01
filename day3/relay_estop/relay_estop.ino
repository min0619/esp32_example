typedef struct { int pin; int stable; int last_raw; uint32_t changed_at; } button_t;

int button_pressed(button_t *b) {
    int raw = digitalRead(b->pin);
    if (raw != b->last_raw) { b->last_raw = raw; b->changed_at = millis(); }
    if (millis() - b->changed_at > 30 && raw != b->stable) {
        b->stable = raw;
        return (raw == LOW);
    }
    return 0;
}

const int PIN_EN = 13, PIN_IN1 = 12, PIN_IN2 = 14;
const int PIN_RELAY = 27, PIN_BTN = 26;
const bool ACTIVE_LOW = true;

typedef enum { ST_STOP, ST_RUN } run_t;
run_t state = ST_STOP;
int speed = 0;
button_t btn = {PIN_BTN, HIGH, HIGH, 0};

void relay_set(bool on) { digitalWrite(PIN_RELAY, ACTIVE_LOW ? !on : on); }

void motor_set(int s) {                      // 예제 7-2
    if (s > 255) s = 255;
    if (s < -255) s = -255;
    digitalWrite(PIN_IN1, s > 0);
    digitalWrite(PIN_IN2, s < 0);
    ledcWrite(PIN_EN, abs(s));
}

void setup() {
    Serial.begin(115200);
    pinMode(PIN_IN1, OUTPUT); pinMode(PIN_IN2, OUTPUT);
    pinMode(PIN_RELAY, OUTPUT); pinMode(PIN_BTN, INPUT_PULLUP);
    ledcAttach(PIN_EN, 20000, 8);
    motor_set(0);
    relay_set(false);                        // 시작은 항상 주전원 차단
    Serial.println("버튼 = 시작 / 비상 정지");
}

void loop() {
    if (button_pressed(&btn)) {
        if (state == ST_RUN) {               // 비상 정지: 주전원부터 끊는다
            relay_set(false);
            motor_set(0);
            speed = 0;
            state = ST_STOP;
            Serial.println("비상 정지 — 주전원 차단");
        } else {                             // 시작: 속도 0 에서 전원 → 천천히 가속
            motor_set(0);
            relay_set(true);
            delay(100);                      // 접점이 완전히 붙을 때까지
            state = ST_RUN;
            Serial.println("주전원 ON — 가속");
        }
    }
    static uint32_t t_ramp = 0;
    if (state == ST_RUN && speed < 200 && millis() - t_ramp >= 20) {
        t_ramp = millis();
        speed += 5;
        motor_set(speed);
    }
}