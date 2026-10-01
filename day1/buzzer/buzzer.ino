void setup() {
    pinMode(12, OUTPUT);
    ledcAttach(14, 1000, 10);
}

void loop() {
    digitalWrite(12, HIGH); delay(200); digitalWrite(19, LOW);   // 삐
    delay(500);
    ledcWriteTone(14, 440); delay(200); ledcWriteTone(23, 0);    // 라(A4)
    delay(1500);
}