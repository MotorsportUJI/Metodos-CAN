#ifndef CAN_STRUCTS_H
#define CAN_STRUCTS_H
#include <stdint.h>

// Structs for PCB_FRONT, packed for exact memory layout
typedef struct __attribute__((packed)) {
    uint8_t presion_freno; // brake pressure sensor
} F_001_t;

// Structs for PCB_BACK_RIGHT
typedef struct __attribute__((packed)) {
    uint8_t temp_cable_case;
    uint8_t temp_firewall;
    uint8_t temp_fan1;
    uint8_t temp_fan2;
    uint8_t temp_suelto;
    uint8_t temp_esc_1;
    uint8_t temp_esc_2;
    uint8_t gear;
} BR_011_t;

typedef struct __attribute__((packed)) {
    uint8_t gal_ext_RA_1;
    uint8_t gal_ext_RA_2;
    uint8_t gal_ext_RA_3;
    uint8_t gal_ext_RA_4;
    uint8_t gal_din_right_1;
    uint8_t gal_din_right_2;
    uint8_t gal_din_right_3;
    uint8_t reserved;
} BR_101_t;

typedef struct __attribute__((packed)) {
    uint16_t hall_rear_right; // 2 bytes for hall sensor
    uint16_t rpm_obd;         // 2 bytes for RPM
    uint8_t temp_obd;
    uint8_t throttle;
    uint8_t pres_comprest_air;
    uint8_t reserved;
} BR_021_t;

// Structs for PCB_BACK_LEFT
typedef struct __attribute__((packed)) {
    uint8_t temp_oil;
    uint8_t temp_gas;
    uint8_t temp_refri_1;
    uint8_t temp_refri_2;
    uint8_t gas_level;
    int16_t gyro_x;
} BL_012_t;

typedef struct __attribute__((packed)) {
    uint8_t pres_admision;
    uint8_t pres_oil;
    uint8_t pres_gas;
    uint8_t gal_din_left_1;
    uint8_t gal_din_left_2;
    uint8_t gal_din_left_3;
    int16_t gyro_y;
} BL_022_t;

typedef struct __attribute__((packed)) {
    int16_t accel_x;
    int16_t accel_y;
    int16_t accel_z;
    int16_t gyro_z;
} BL_102_t;

#endif
