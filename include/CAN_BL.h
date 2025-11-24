#pragma once

#include "CAN_ids.h"
#include <FlexCAN_T4.h>
#include <stdint.h>

// ID 0x012
struct BL_012_t {
  uint8_t temp_oil;      // 0
  uint8_t temp_gas;      // 1
  uint8_t temp_refri_1;  // 2
  uint8_t temp_refri_2;  // 3
  uint8_t gas_level;     // 4
  uint8_t _pad;          // 5
  int16_t gyro_x;        // bytes 6..7 (little-endian)
};

// ID 0x022
struct BL_022_t {
  uint8_t pres_admision; // 0
  uint8_t pres_oil;      // 1
  uint8_t pres_gas;      // 2
  uint8_t gal_din_left_1;// 3
  uint8_t gal_din_left_2;// 4
  uint8_t gal_din_left_3;// 5
  int16_t gyro_y;        // 6..7
};

// ID 0x102 - IMU accelerations + gyro_z (all int16_t, 8 bytes total)
struct BL_102_t {
  int16_t accel_x;       // 0..1
  int16_t accel_y;       // 2..3
  int16_t accel_z;       // 4..5
  int16_t gyro_z;        // 6..7
};

void setupBackLeft();
void loopBackLeft();
void sendBL_012(const BL_012_t &d);
void sendBL_022(const BL_022_t &d);
void sendBL_102(const BL_102_t &d);