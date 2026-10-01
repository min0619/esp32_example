const int PIN_GAS = 32;

void setup() { Serial.begin(115200); }

void loop() {
    int mv = analogReadMilliVolts(PIN_GAS);
    int ao_mv = mv * 2;                        // 분압 전 실제 AO 전압
    Serial.printf("gas_mv:%d\n", ao_mv);
    delay(200);
}
// → 깨끗한 공기: 수백 mV / 라이터 가스를 살짝: 2000mV 이상으로 치솟았다가 천천히 복귀