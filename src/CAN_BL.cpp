#include "CAN_BL.h"
#include <Arduino.h>

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can0;

static void handleBL_incoming(const CAN_message_t &msg) {
  switch (msg.id) {
    case ID_BACKL_012: {
      BL_012_t rx{};
      if (msg.len >= 8) memcpy(&rx, msg.buf, sizeof(rx));
      // process rx
      break;
    }
    case ID_BACKL_022: {
      BL_022_t rx{};
      if (msg.len >= 8) memcpy(&rx, msg.buf, sizeof(rx));
      // process rx
      break;
    }
    case ID_BACKL_102: {
      BL_102_t rx{};
      if (msg.len >= 8) memcpy(&rx, msg.buf, sizeof(rx));
      // process rx
      break;
    }
    default: break;
  }
}

void CAN_BL_setup() {
  Serial.begin(115200); delay(200);
  pinMode(6, OUTPUT); digitalWrite(6, LOW);

  Can0.begin();
  Can0.setBaudRate(1000000);
  Can0.setMaxMB(16);
  Can0.enableFIFO();
  Can0.enableFIFOInterrupt();
  Can0.onReceive(handleBL_incoming);
  Can0.mailboxStatus();
}

void sendBL_012(const BL_012_t &d) {
  CAN_message_t msg;
  msg.id = ID_BACKL_012;
  msg.len = 8;
  memcpy(msg.buf, &d, sizeof(d));
  Can0.write(msg);
}

void sendBL_022(const BL_022_t &d) {
  CAN_message_t msg;
  msg.id = ID_BACKL_022;
  msg.len = 8;
  memcpy(msg.buf, &d, sizeof(d));
  Can0.write(msg);
}

void sendBL_102(const BL_102_t &d) {
  CAN_message_t msg;
  msg.id = ID_BACKL_102;
  msg.len = 8;
  memcpy(msg.buf, &d, sizeof(d));
  Can0.write(msg);
}

void CAN_BL_loop() {
  Can0.events();

  // Example periodic sends (replace with IMU reads / sensors)
  static uint32_t t = 0;
  if (millis() - t > 50) {
    BL_012_t a{}; a.temp_oil = 60; a.temp_gas = 55; a.temp_refri_1 = 45; a.temp_refri_2 = 46; a.gas_level = 80; a.gyro_x = 123;
    sendBL_012(a);

    BL_022_t b{}; b.pres_admision = 2; b.pres_oil = 3; b.pres_gas = 1; b.gal_din_left_1 = 5; b.gal_din_left_2 = 6; b.gal_din_left_3 = 7; b.gyro_y = -50;
    sendBL_022(b);

    BL_102_t c{}; c.accel_x = 100; c.accel_y = -100; c.accel_z = 50; c.gyro_z = 10;
    sendBL_102(c);

    t = millis();
  }
}

#if defined(COMPILE_AS_SKETCH_PCB_BACK_LEFT)
void setup() { CAN_BL_setup(); }
void loop() { CAN_BL_loop(); }
#endif