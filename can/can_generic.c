/* SPDX-License-Identifier: MIT */
/*
 * Author: Andreas Werner <kernel@andy89.org>
 * Date: 2018
 */
#include <can.h>
#define CAN_PRV
#include <can_prv.h>

int32_t can_generic_init(struct can *t) {
	struct can_generic *can = (struct can_generic *) t;
	if (hal_isInit(can)) {
		return CAN_ALREDY_INITED;
	}
	can->init = true;
	return 0;
}
#ifdef CONFIG_CAPTURE_MULTI
struct can *can_init(uint32_t index, uint8_t bitrate, struct gpio_pin *pin, bool pinHigh);
int32_t can_deinit(struct can *can);
int32_t can_setCallback(struct can *can, struct can_filter *filter, bool (*callback)(struct can *can, struct can_msg *msg, void *data), void *data);
int32_t can_registerFilter(struct can *can, struct can_filter *filter);
int32_t can_deregisterFilter(struct can *can, struct can_filter *filter);
int32_t can_send(struct can *can, struct can_msg *msg, TickType_t waittime);
int32_t can_recv(struct can *can, struct can_filter *filter, struct can_msg *msg, TickType_t waittime);
int32_t can_sendISR(struct can *can, struct can_msg *msg);
int32_t can_recvISR(struct can *can, struct can_filter *filter, struct can_msg *msg);
int32_t can_up(struct can *can);
int32_t can_down(struct can *can);
#endif
