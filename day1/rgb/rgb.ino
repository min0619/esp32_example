typedef struct {
    uint8_t r, g, b;
    const char *name;
} color_t;

const color_t COLORS[] = {
    {255,   0,   0, "red"},
    {  0, 255,   0, "green"},
    {  0,   0, 255, "blue"},
    {255, 180,   0, "orange"},
    {160,   0, 255, "purple"},
    {255, 255, 255, "white"},
};
const int N_COLOR = sizeof(COLORS) / sizeof(COLORS[0]);

const int PIN_R = 25, PIN_G = 26, PIN_B = 27;
#define COMMON_ANODE 0                 // 공통 애노드면 1 로

void set_rgb(const color_t *c) {
    uint8_t r = c->r, g = c->g, b = c->b;
#if COMMON_ANODE
    r = 255 - r; g = 255 - g; b = 255 - b;   // 애노드형은 LOW 가 켜짐
#endif
    ledcWrite(PIN_R, r);
    ledcWrite(PIN_G, g);
    ledcWrite(PIN_B, b);
}

void setup() {
    Serial.begin(115200);
    ledcAttach(PIN_R, 5000, 8);
    ledcAttach(PIN_G, 5000, 8);
    ledcAttach(PIN_B, 5000, 8);
}

void loop() {
    for (int i = 0; i < N_COLOR; i++) {
        set_rgb(&COLORS[i]);
        Serial.println(COLORS[i].name);
        delay(800);
    }
}