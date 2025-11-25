#ifndef CAN_SEND_H
#define CAN_SEND_H
#include <Arduino.h>
#include <FlexCAN_T4.h>
#include "CAN_structs.h"
#include "CAN_ids.h"

void CAN_init_sender(); // initialize CAN sender
void CAN_loop_sender(); // periodic sending scheduler

// send functions for all PCBs
void CAN_send_BL_012(const BL_012_t &d);
void CAN_send_BL_022(const BL_022_t &d);
void CAN_send_BL_102(const BL_102_t &d);
void CAN_send_BR_011(const BR_011_t &d);
void CAN_send_BR_101(const BR_101_t &d);
void CAN_send_BR_021(const BR_021_t &d);
void CAN_send_F_001(const F_001_t &d);

#endif