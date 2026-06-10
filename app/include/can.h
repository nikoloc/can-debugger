#ifndef _CAN_H
#define _CAN_H

#include "main.h"

void
test_send(void);

void
can_init(CAN_HandleTypeDef *handle);

void
can_send(CAN_HandleTypeDef *handle, size_t size, uint8_t *msg);

#endif
