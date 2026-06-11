#include "app.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

#include "can.h"
#include "main.h"

extern CAN_HandleTypeDef hcan;
extern UART_HandleTypeDef huart2;

extern volatile bool can_msg_recv;
extern uint8_t can_buffer[8];

int
__io_putchar(int ch) {
    HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;
}

void
app(void) {
    if(!can_init(&hcan)) {
        return;
    }

    HAL_GPIO_WritePin(OUTPUT_LED_GPIO_Port, OUTPUT_LED_Pin, 1);

    while(1) {
        if(can_msg_recv) {
            can_msg_recv = false;

            printf("can msg\n");
            for(size_t i = 0; i < 8; i++) {
                printf("-> %" PRIu8 "\n", can_buffer[i]);
            }

            // TODO: uncomment this after the first part is tested
            // uint16_t resp = 69;
            // can_send(&hcan, 0x420, sizeof(resp), (uint8_t *)&resp);
        }
    }
}
