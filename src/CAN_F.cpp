#include "CAN_F.h"
#include <Arduino.h>

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can0; // local bus instance for this PCB

void CAN_F_setup() {
  Serial.begin(9600);
  delay(200);
  pinMode(6, OUTPUT); digitalWrite(6, LOW); // optional transceiver enable. Ajustar PIN

  Can0.begin();
  Can0.setBaudRate(1000000);
  Can0.setMaxMB(16);
  Can0.enableFIFO();
  Can0.enableFIFOInterrupt();
  Can0.onReceive([](const CAN_message_t &msg){
    // simple generic receive handler - expand if needed
    switch (msg.id) {
      case ID_FRONT_001:
        // message from myself/other front units - decode if desired
        break;
      default:
        break;
    }
  });
  Can0.mailboxStatus();
}

void sendFront_presion(const PCB_Front_t &d) {
  CAN_message_t msg;
  msg.id = ID_FRONT_001;
  msg.len = 8; // fixed length on the bus
  // zero the buffer then copy struct bytes (little-endian assumed)
  for (int i = 0; i < 8; ++i) msg.buf[i] = 0;
  memcpy(msg.buf, &d, sizeof(PCB_Front_t));
  Can0.write(msg);
}

void CAN_F_loop() {
  Can0.events();
  // Example periodic send - integrate with your real sensor read
  static uint32_t t = 0;
  if (millis() - t > 100) {
    PCB_Front_t out{};
    // TODO: read real sensor into out.presion_freno
    out.presion_freno = 0; // placeholder
    sendFront_presion(out);
    t = millis();
  }
}

