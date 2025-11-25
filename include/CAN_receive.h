#ifndef CAN_RECEIVE_H
#define CAN_RECEIVE_H
#include <Arduino.h>
#include <FlexCAN_T4.h>
#include "CAN_structs.h"
#include "CAN_ids.h"

void CAN_init_receiver(); // initialize CAN receiver
void CAN_handle_receive(); // process incoming messages

// storage for last received messages from each PCB
extern F_001_t recv_F_001;
extern BL_012_t recv_BL_012;
extern BL_022_t recv_BL_022;
extern BL_102_t recv_BL_102;
extern BR_011_t recv_BR_011;
extern BR_101_t recv_BR_101;
extern BR_021_t recv_BR_021;

#endif