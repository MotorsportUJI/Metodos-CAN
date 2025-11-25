#include <Arduino.h>
#include "CAN_send.h"
#include "CAN_receive.h"

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can0;

void setup() {
    Can0.begin();
    Can0.setBaudRate(1000000);
    //No se hace CAN_init_sender() porque lo que habia dentro lo he migrado en setup del main
    CAN_init_receiver(); // initialize receiving CAN
}

void loop() {
    CAN_loop_sender(); // handle scheduled sending
    CAN_handle_receive(); // handle incoming CAN messages
}