#include <Arduino.h>
#include "CAN_send.h"
#include "CAN_receive.h"

void setup() {
    CAN_init_sender(); // initialize sending CAN
    CAN_init_receiver(); // initialize receiving CAN
}

void loop() {
    CAN_loop_sender(); // handle scheduled sending
    CAN_handle_receive(); // handle incoming CAN messages
}