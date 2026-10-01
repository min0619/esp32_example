typedef enum { ST_RED, ST_GREEN, ST_YELLOW, ST_BLINK } light_t;

const int PIN_R = 25, PIN_Y = 33, PIN_G = 32;

void setLights(int r, int y, int g) {
    digitalWrite(PIN_R, r);
    digitalWrite(PIN_Y, y);
    digitalWrite(PIN_G, g);
}

void setup() {
    Serial.begin(115200);
    pinMode(PIN_R, OUTPUT);
    pinMode(PIN_Y, OUTPUT);
    pinMode(PIN_G, OUTPUT);
}

void loop() {
    static light_t state = ST_RED;            // static: loop 가 끝나도 값 유지
    switch (state) {
        case ST_RED:
            setLights(1, 0, 0); Serial.println("RED");
            delay(3000); state = ST_GREEN;  break;
        case ST_GREEN:
            setLights(0, 0, 1); Serial.println("GREEN");
            delay(3000); state = ST_YELLOW; break;
        case ST_YELLOW:
            setLights(0, 1, 0); Serial.println("YELLOW");
            delay(1000); state = ST_BLINK;    break;
        case ST_BLINK:
            for(int i = 0; i < 3; i++){
                setLights(0,1,0); delay(300);
                setLights(0,0,0); delay(300);
            }
            state = ST_RED;
            break;
    }
}
// → RED / GREEN / YELLOW / RED / ...