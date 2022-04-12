#include "pico/stdlib.h"
#include <stdio.h>
#include "pico/time.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"

#define red_pin 6
#define bl_pin 7
#define gr_pin 28

void on_pwm_wrap() {
    static int fade = 0;
    static bool going_up = true;
    static bool once = true;
    pwm_set_wrap(3, 1000);

    while(once){
        if (going_up) {
            ++fade;
            if (fade > 1000) {
                fade = 1000;
                going_up = false;
            }
        } else {
            --fade;
            if (fade < 0) {
                fade = 0;
                going_up = true;
            }
        }
        sleep_ms(1);
        pwm_set_gpio_level(bl_pin, fade);

        if (fade == 0){
            break;
        }
    }
}


void on_pwm_wrap2() {
    static int fade = 0;
    static bool going_up = true;
    static bool once = true;
    pwm_set_wrap(6, 1000);
 
    while(once){
        if (going_up) {
            ++fade;
            if (fade > 1000) {
                fade = 1000;
                going_up = false;
            }
        } else {
            --fade;
            if (fade < 0) {
                fade = 0;
                going_up = true;
            }
        }
        sleep_ms(1);

        pwm_set_gpio_level(gr_pin, fade);

        if (fade == 0){
                break;
        }
    }
}

void on_pwm_wrap3() {
    static int fade = 0;
    static bool going_up = true;
    static bool once = true;
    pwm_set_wrap(3, 1000);

    while(once){
        if (going_up) {
            ++fade;
            if (fade > 1000) {
                fade = 1000;
                going_up = false;
            }
        } else {
            --fade;
            if (fade < 0) {
                fade = 0;
                going_up = true;
            }
        }
        sleep_ms(1);
        pwm_set_gpio_level(red_pin, fade);

        if (fade == 0){
            break;
        }
    }
}

void change_color(){
    on_pwm_wrap();
    sleep_ms(20);
    on_pwm_wrap2();
    sleep_ms(20);
    on_pwm_wrap3();
}

int main() {

    stdio_init_all();
    gpio_init(red_pin);
    gpio_init(bl_pin);
    gpio_init(gr_pin);
    gpio_set_function(red_pin, GPIO_FUNC_PWM);
    gpio_set_function(bl_pin, GPIO_FUNC_PWM);
    gpio_set_function(gr_pin, GPIO_FUNC_PWM);    

// 設定三色燈, GPIO6=PWM3A, GPIO7=PWM3B, GPIO28=PWM6A
// 根據GPIO所屬的slice來定義enable的位置
    pwm_set_enabled(3, true);
    pwm_set_enabled(6, true);     

    while (1) {
        change_color();
}
