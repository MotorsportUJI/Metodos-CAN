#include "CAN_BR.h"
#include <Arduino.h>

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can0;

static void handle_incoming(const CAN_message_t &msg) {
  // central dispatcher - decode messages addressed to this board if needed
  switch (msg.id) {
    case ID_BACKR_011: {
      BR_011_t rx;
      if (msg.len >= 8) memcpy(&rx, msg.buf, sizeof(rx));
      // process rx
      break;
    }
    case ID_BACKR_101: {
      BR_101_t rx;
      if (msg.len >= 8) memcpy(&rx, msg.buf, sizeof(rx));
      // process rx
      break;
    }
    case ID_BACKR_021: {
      BR_021_t rx;
      if (msg.len >= 8) memcpy(&rx, msg.buf, sizeof(rx));
      // process rx
      break;
    }
    default:
      break;
  }
}

void CAN_BR_setup() {
  Serial.begin(9600); delay(200);
  pinMode(6, OUTPUT); digitalWrite(6, LOW); //Ajustar PIN

  Can0.begin();
  Can0.setBaudRate(1000000);
  Can0.setMaxMB(16);
  Can0.enableFIFO();
  Can0.enableFIFOInterrupt();
  Can0.onReceive(handle_incoming);
  Can0.mailboxStatus();
}

void sendBR_011(const BR_011_t &d) {
  CAN_message_t msg;
  msg.id = ID_BACKR_011;
  msg.len = 8;
  memcpy(msg.buf, &d, sizeof(d));
  Can0.write(msg);
}

void sendBR_101(const BR_101_t &d) {
  CAN_message_t msg;
  msg.id = ID_BACKR_101;
  msg.len = 8;
  memcpy(msg.buf, &d, sizeof(d));
  Can0.write(msg);
}

void sendBR_021(const BR_021_t &d) {
  CAN_message_t msg;
  msg.id = ID_BACKR_021;
  msg.len = 8;
  memcpy(msg.buf, &d, sizeof(d));
  Can0.write(msg);
}

void CAN_BR_loop() {
  Can0.events();

  // Example periodic sends (replace with real readings)
  static uint32_t t = 0;
  if (millis() - t > 100) {
    BR_011_t a{}; a.temp_cable_case = 10; a.temp_firewall = 20; a.temp_fan1 = 30; a.temp_fan2 = 31; a.temp_suelto = 25; a.temp_esc_1 = 40; a.temp_esc_2 = 41; a.gear = 3;
    sendBR_011(a);

    BR_101_t b{}; b.gal_ext_RA_1 = 1; b.gal_ext_RA_2 = 2; b.gal_ext_RA_3 = 3; b.gal_ext_RA_4 = 4; b.gal_din_right_1 = 5; b.gal_din_right_2 = 6; b.gal_din_right_3 = 7;
    sendBR_101(b);

    BR_021_t c{}; c.hall_rear_right = 1234; c.rpm_obd = 3000; c.temp_obd = 60; c.throttle = 50; c.pres_comprest_air = 2;
    sendBR_021(c);

    t = millis();
  }
}

#if defined(COMPILE_AS_SKETCH_PCB_BACK_RIGHT)
void setup() { CAN_BR_setup(); }
void loop() { CAN_BR_loop(); }
#endif