#include "app.h"

#include "can.h"
#include "main.h"

extern CAN_HandleTypeDef hcan;
extern UART_HandleTypeDef huart2;

int
__io_putchar(int ch) {
    HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;
}

void
app(void) {
    // can_init();
    while(1) {
        test_send();
        HAL_GPIO_WritePin(OUTPUT_LED_GPIO_Port, OUTPUT_LED_Pin, 1);
        HAL_Delay(500);
        HAL_GPIO_WritePin(OUTPUT_LED_GPIO_Port, OUTPUT_LED_Pin, 0);
        HAL_Delay(500);
    }
}
