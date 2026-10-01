const int PIN_DS = 12, PIN_SH = 13, PIN_ST = 14;
const int DIG[4] = {27, 26, 25, 33};
const uint8_t DIGITS[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

volatile uint8_t disp[4];               // ISR 과 loop 가 함께 쓰는 화면 버퍼
volatile int cur = 0;
hw_timer_t *timer = NULL;

void IRAM_ATTR write595(uint8_t d) {
    digitalWrite(PIN_ST, LOW);
    for (int i = 7; i >= 0; i--) {
        digitalWrite(PIN_DS, (d >> i) & 1);
        digitalWrite(PIN_SH, HIGH);
        digitalWrite(PIN_SH, LOW);
    }
    digitalWrite(PIN_ST, HIGH);
}

void IRAM_ATTR onTimer() {              // 2ms 마다 한 자리씩
    digitalWrite(DIG[cur], HIGH);       // 지금 자리 끄고
    cur = (cur + 1) % 4;
    write595(disp[cur]);
    digitalWrite(DIG[cur], LOW);        // 다음 자리 켜기
}

void show_number(int n) {
    for (int k = 3; k >= 0; k--) {      // 오른쪽 자리부터
        disp[k] = DIGITS[n % 10];
        n /= 10;
    }
}

void setup() {
    pinMode(PIN_DS, OUTPUT); pinMode(PIN_SH, OUTPUT); pinMode(PIN_ST, OUTPUT);
    for (int i = 0; i < 4; i++) { pinMode(DIG[i], OUTPUT); digitalWrite(DIG[i], HIGH); }
    timer = timerBegin(1000000);                   // 1MHz → 1틱 = 1µs
    timerAttachInterrupt(timer, &onTimer);
    timerAlarm(timer, 2000, true, 0);              // 2000µs 마다 반복
}

void loop() {
    static int count = 0;
    show_number(count++ % 10000);
    delay(100);                          // loop 가 쉬어도 화면은 깜빡이지 않는다
}