const int PIN_FLAME = 34, PIN_SOUND = 35;

void setup() { Serial.begin(115200); }

void loop() {
    int flame = analogRead(PIN_FLAME);
    int sound_max = 0;
    for (int i = 0; i < 200; i++) {            // 소리는 빠르게 흔들리므로 최대값을 본다
        int v = analogRead(PIN_SOUND);
        if (v > sound_max) sound_max = v;
    }
    Serial.printf("flame:%d,sound:%d\n", flame, sound_max);
    delay(50);
}