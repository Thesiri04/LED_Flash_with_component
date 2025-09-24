#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "LED.h"

LED led1(16); 
LED led2(17); 
LED led3(5); 
LED led4(18); 
LED led5(19); 
LED led6(21); 
LED led7(22); 
LED led8(23); 

LED leds[] = {led1, led2, led3, led4, led5, led6, led7, led8};

extern "C" void app_main(void)
{
    int num_leds = sizeof(leds) / sizeof(leds[0]);
    int pattern_len = 8;
    // กำหนด pattern index สำหรับแต่ละ step
    int pattern[8][2] = {
        {0, 7}, // *......*
        {1, 6}, // .*....*.
        {2, 5}, // ..*..*..
        {3, 4}, // ...**...
        {3, 4}, // ...**...
        {2, 5}, // ..*..*..
        {1, 6}, // .*....*.
        {0, 7}  // *......*
    };
    int step = 0;
    while (1)
    {
        // ดับทุกดวงก่อน
        for (int j = 0; j < num_leds; ++j) {
            leds[j].OFF();
        }
        // ติดสองดวงตาม pattern
        leds[pattern[step][0]].ON();
        leds[pattern[step][1]].ON();
        vTaskDelay(100 / portTICK_PERIOD_MS);
        // ไป step ถัดไป
        step = (step + 1) % pattern_len;
    }
}