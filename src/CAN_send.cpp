#include "CAN_send.h"
#include "CAN_bus.h"
#define freq_F_001 100

#define freq_BL_012 100
#define freq_BL_022 100
#define freq_BL_102 100

#define freq_BR_011 100
#define freq_BR_101 100
#define freq_BR_021 100
//Quitar los define de las que no vaya a enviar en esa pcb



/*void CAN_init_sender() {
    
}*/

// helper function to send any struct over CAN
static void sendFrame(uint32_t id, const void *data, uint8_t len) {
    CAN_message_t msg;
    msg.id = id;
    msg.len = len;
    memcpy(msg.buf, data, len); // copy struct bytes into CAN buffer
    Can0.write(msg);
}

//Quitar en cada pcb la de las otras pcbs
// F sends
void CAN_send_F_001(const F_001_t &d){ sendFrame(ID_F_001, &d, sizeof(d)); }

// BL sends
void CAN_send_BL_012(const BL_012_t &d){ sendFrame(ID_BL_012, &d, sizeof(d)); }
void CAN_send_BL_022(const BL_022_t &d){ sendFrame(ID_BL_022, &d, sizeof(d)); }
void CAN_send_BL_102(const BL_102_t &d){ sendFrame(ID_BL_102, &d, sizeof(d)); }

// BR sends
void CAN_send_BR_011(const BR_011_t &d){ sendFrame(ID_BR_011, &d, sizeof(d)); }
void CAN_send_BR_101(const BR_101_t &d){ sendFrame(ID_BR_101, &d, sizeof(d)); }
void CAN_send_BR_021(const BR_021_t &d){ sendFrame(ID_BR_021, &d, sizeof(d)); }

void CAN_loop_sender() {
    // temporizadores independientes para cada struct, dejar a 0, son para guardar la ultima vez que se miró para poder volverlas a mirar x tiempo despues de haverlas leidos, le ajusta mejor si hay delay en el coche
    static uint32_t t_F_001    = 0;

    static uint32_t t_BL_012   = 0;
    static uint32_t t_BL_022   = 0;
    static uint32_t t_BL_102   = 0;

    static uint32_t t_BR_011   = 0;
    static uint32_t t_BR_101   = 0;
    static uint32_t t_BR_021   = 0;

    uint32_t now = millis();

    //Dejar en la versión de cada PCB solo las que vaya a dejar y Cambiar la variable por la real, tanto los temporizadores de arriba como del codigo de abajo

    // ---------- PCB_FRONT ----------
    if (now - t_F_001 > freq_F_001) {
        F_001_t msg_F{};
        msg_F.presion_freno = 0; // reemplazar por la variable real de sensor
        CAN_send_F_001(msg_F);
        t_F_001 = now;
    }

    // ---------- PCB_BACK_LEFT ----------
    if (now - t_BL_012 > freq_BL_012) {
        BL_012_t msg_BL_012{};
        msg_BL_012.temp_oil     = 60; // sustituir por variable real
        msg_BL_012.temp_gas     = 55;
        msg_BL_012.temp_refri_1 = 45;
        msg_BL_012.temp_refri_2 = 46;
        msg_BL_012.gas_level    = 80;
        msg_BL_012.gyro_x       = 123;
        CAN_send_BL_012(msg_BL_012);
        t_BL_012 = now;
    }

    if (now - t_BL_022 > freq_BL_022) {
        BL_022_t msg_BL_022{};
        msg_BL_022.pres_admision   = 2;// sustituir por variable real
        msg_BL_022.pres_oil        = 3;
        msg_BL_022.pres_gas        = 1;
        msg_BL_022.gal_din_left_1  = 5;
        msg_BL_022.gal_din_left_2  = 6;
        msg_BL_022.gal_din_left_3  = 7;
        msg_BL_022.gyro_y          = -50;
        CAN_send_BL_022(msg_BL_022);
        t_BL_022 = now;
    }

    if (now - t_BL_102 > freq_BL_102) { 
        BL_102_t msg_BL_102{};
        msg_BL_102.accel_x = 100;// sustituir por variable real
        msg_BL_102.accel_y = -100;
        msg_BL_102.accel_z = 50;
        msg_BL_102.gyro_z  = 10;
        CAN_send_BL_102(msg_BL_102);
        t_BL_102 = now;
    }

    // ---------- PCB_BACK_RIGHT ----------
    if (now - t_BR_011 > freq_BR_011) {
        BR_011_t msg_BR_011{};
        msg_BR_011.temp_cable_case = 10;// sustituir por variable real
        msg_BR_011.temp_firewall   = 20;
        msg_BR_011.temp_fan1       = 30;
        msg_BR_011.temp_fan2       = 31;
        msg_BR_011.temp_suelto     = 25;
        msg_BR_011.temp_esc_1      = 40;
        msg_BR_011.temp_esc_2      = 41;
        msg_BR_011.gear            = 3;
        CAN_send_BR_011(msg_BR_011);
        t_BR_011 = now;
    }

    if (now - t_BR_101 > freq_BR_101) {
        BR_101_t msg_BR_101{};
        msg_BR_101.gal_ext_RA_1    = 1;// sustituir por variable real
        msg_BR_101.gal_ext_RA_2    = 2;
        msg_BR_101.gal_ext_RA_3    = 3;
        msg_BR_101.gal_ext_RA_4    = 4;
        msg_BR_101.gal_din_right_1 = 5;
        msg_BR_101.gal_din_right_2 = 6;
        msg_BR_101.gal_din_right_3 = 7;
        CAN_send_BR_101(msg_BR_101);
        t_BR_101 = now;
    }

    if (now - t_BR_021 > freq_BR_021) {
        BR_021_t msg_BR_021{};
        msg_BR_021.hall_rear_right   = 1234;// sustituir por variable real
        msg_BR_021.rpm_obd           = 3000;
        msg_BR_021.temp_obd          = 60;
        msg_BR_021.throttle          = 50;
        msg_BR_021.pres_comprest_air = 2;
        CAN_send_BR_021(msg_BR_021);
        t_BR_021 = now;
    }
}