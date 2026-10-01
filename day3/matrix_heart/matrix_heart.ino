const int PIN_DS = 12, PIN_SH = 13, PIN_ST = 14;
const int ROWS[8] = {27, 26, 25, 33, 32, 33, 32, 26};
const int ROW_ON = HIGH;                 // 행 극성 — 뒤집혀 보이면 LOW 로

volatile uint8_t img[8] = {              // 1 = 켜짐, bit7 = 왼쪽 열
    0b00000000,
    0b01100110,
    0b11111111,
    0b11111111,
    0b01111110,
    0b00111100,
    0b00011000,
    0b00000000,
};
volatile int row = 0;
hw_timer_t *timer = NULL;

void IRAM_ATTR write595(uint8_t d) {
    digitalWrite(PIN_ST, LOW);
    for (int i = 0; i < 8; i++) {                 // bit7 → Q0(C1, 왼쪽)
        digitalWrite(PIN_DS, (d >> i) & 1);
        digitalWrite(PIN_SH, HIGH);
        digitalWrite(PIN_SH, LOW);
    }
    digitalWrite(PIN_ST, HIGH);
}

void IRAM_ATTR onTimer() {
    digitalWrite(ROWS[row], !ROW_ON);             // 이전 행 끄기
    row = (row + 1) % 8;
    write595(ROW_ON == HIGH ? ~img[row] : img[row]);   // 열은 행과 반대 극성일 때 켜짐
    digitalWrite(ROWS[row], ROW_ON);              // 다음 행 켜기
}

void setup() {
    pinMode(PIN_DS, OUTPUT); pinMode(PIN_SH, OUTPUT); pinMode(PIN_ST, OUTPUT);
    for (int i = 0; i < 8; i++) { pinMode(ROWS[i], OUTPUT); digitalWrite(ROWS[i], !ROW_ON); }
    timer = timerBegin(1000000);
    timerAttachInterrupt(timer, &onTimer);
    timerAlarm(timer, 1500, true, 0);             // 1.5ms × 8행 = 12ms → 약 83Hz
}

void loop() { }