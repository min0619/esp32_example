#ifndef SENSOR_H          // include guard: 두 번 포함돼도 한 번만
#define SENSOR_H

typedef struct {
    int pin;              // 아날로그 입력
    int pwr;              // 전원 GPIO
    const char *name;
} powered_sensor_t;

void sensor_init(const powered_sensor_t *s);
int  sensor_read(const powered_sensor_t *s);

extern int sensor_read_count;   // 다른 파일에 정의된 전역 변수

#endif