#pragma once

#include "CAN_ids.h"
#include <FlexCAN_T4.h>
#include <stdint.h>

// ID 0x011 - temperatures + gear (8 bytes)
struct BR_011_t {
  uint8_t temp_cable_case; // 0
  uint8_t temp_firewall;   // 1
  uint8_t temp_fan1;       // 2
  uint8_t temp_fan2;       // 3
  uint8_t temp_suelto;     // 4
  uint8_t temp_esc_1;      // 5
  uint8_t temp_esc_2;      // 6
  uint8_t gear;            // 7
};

// ID 0x101 - fuel/gal sensors (7 useful bytes, pad to 8)
struct BR_101_t {
  uint8_t gal_ext_RA_1;    // 0
  uint8_t gal_ext_RA_2;    // 1
  uint8_t gal_ext_RA_3;    // 2
  uint8_t gal_ext_RA_4;    // 3
  uint8_t gal_din_right_1; // 4
  uint8_t gal_din_right_2; // 5
  uint8_t gal_din_right_3; // 6
  uint8_t _pad;            // 7
};

// ID 0x021 - mixed: hall (uint16), rpm (uint16 used as uint8+pad here), temps, throttle, pres
struct BR_021_t {
  uint16_t hall_rear_right; // bytes 0..1 (little-endian)
  uint16_t rpm_obd;         // bytes 2..3 (we keep as 16-bit for future)
  uint8_t temp_obd;         // 4
  uint8_t throttle;         // 5
  uint8_t pres_comprest_air; // 6
  uint8_t _pad;             // 7
};

void setupBackRight();
void loopBackRight();
void sendBR_011(const BR_011_t &d);
void sendBR_101(const BR_101_t &d);
void sendBR_021(const BR_021_t &d);