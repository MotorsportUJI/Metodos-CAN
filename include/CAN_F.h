#pragma once

#include "CAN_ids.h"
#include <FlexCAN_T4.h>

struct PCB_Front_t {
  uint8_t presion_freno;    // byte 0
  uint8_t _pad[7];          // bytes 1..7 (reserved / zero)
};

void setupFront();
void loopFront();
void sendFront_presion(const PCB_Front_t &d);