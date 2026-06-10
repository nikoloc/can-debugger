#include "can.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "main.h"

void
test_send(void) {
    printf("this is an uart test\n");
}

void
can_send(CAN_HandleTypeDef *handle, size_t size, uint8_t *msg) {
    assert(size < 8);

    CAN_TxHeaderTypeDef header = {
            .IDE = CAN_ID_STD,
            .StdId = 0x123,
            .RTR = CAN_RTR_DATA,
            .DLC = size,
    };

    uint32_t mailbox;
    HAL_CAN_AddTxMessage(handle, &header, msg, &mailbox);
}

void
HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *handle) {
    CAN_RxHeaderTypeDef header;
    uint8_t buffer[16] = {0};

    if(HAL_CAN_GetRxMessage(handle, CAN_RX_FIFO0, &header, buffer) == HAL_OK) {
        printf("received message\t\t%s\n", buffer);
    }

    char *resp = "this is a response";
    can_send(handle, strlen(resp), (uint8_t *)resp);
}

void
can_init(CAN_HandleTypeDef *handle) {
    assert(HAL_CAN_Start(handle) == HAL_OK);

    CAN_FilterTypeDef filter = {
            .FilterBank = 0,
            .FilterMode = CAN_FILTERMODE_IDMASK,
            .FilterScale = CAN_FILTERSCALE_32BIT,
            .FilterIdHigh = 0x0000,
            .FilterIdLow = 0x0000,
            .FilterMaskIdHigh = 0x0000,
            .FilterMaskIdLow = 0x0000,
            .FilterFIFOAssignment = CAN_FILTER_FIFO0,
            .FilterActivation = ENABLE,
    };

    assert(HAL_CAN_ConfigFilter(handle, &filter) == HAL_OK);
    assert(HAL_CAN_ActivateNotification(handle, CAN_IT_RX_FIFO0_MSG_PENDING) == HAL_OK);
}
