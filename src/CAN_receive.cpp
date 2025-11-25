#include "CAN_receive.h"

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can0; // CAN receiver instance

// last received values storage
F_001_t recv_F_001;
BL_012_t recv_BL_012;
BL_022_t recv_BL_022;
BL_102_t recv_BL_102;
BR_011_t recv_BR_011;
BR_101_t recv_BR_101;
BR_021_t recv_BR_021;

// callback executed when message arrives
static void can_callback(const CAN_message_t &msg) {
    switch (msg.id) {
        case ID_F_001: memcpy(&recv_F_001, msg.buf, sizeof(F_001_t)); break;
        case ID_BL_012: memcpy(&recv_BL_012, msg.buf, sizeof(BL_012_t)); break;
        case ID_BL_022: memcpy(&recv_BL_022, msg.buf, sizeof(BL_022_t)); break;
        case ID_BL_102: memcpy(&recv_BL_102, msg.buf, sizeof(BL_102_t)); break;
        case ID_BR_011: memcpy(&recv_BR_011, msg.buf, sizeof(BR_011_t)); break;
        case ID_BR_101: memcpy(&recv_BR_101, msg.buf, sizeof(BR_101_t)); break;
        case ID_BR_021: memcpy(&recv_BR_021, msg.buf, sizeof(BR_021_t)); break;
    }
}

void CAN_init_receiver() {
    Can0.begin();
    Can0.setBaudRate(1000000);
    Can0.enableFIFO();
    Can0.onReceive(can_callback); // attach callback to process incoming frames
}

void CAN_handle_receive() {
    Can0.events(); // poll events to trigger callbacks
}