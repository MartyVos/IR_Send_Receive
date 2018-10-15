#include "IR_Send.hpp"

void IR_Send::generatePacket(uint8_t &data){
    if(player_ID > 31){
        hwlib::cout << "INVALID PLAYER_ID. USING DEFAULT VALUE 0x00" << hwlib::endl;
        player_ID = 0;
    }
    if(data > 31){
        hwlib::cout << "INVALID DATA. USING DEFAULT VALUE 0x00" << hwlib::endl;
        data = 0;
    }
    data_xor = (player_ID ^ data);
    packet += uint16_t(player_ID << 10) + uint16_t(data << 5) + data_xor;
}

void IR_Send::pulse(bool i){
    if(i){
        pin.set(1);
        hwlib::wait_us(1600);
        pin.set(0);
        hwlib::wait_us(800);
    }else{
        pin.set(1);
        hwlib::wait_us(800);
        pin.set(0);
        hwlib::wait_us(1600);
    }
}

uint16_t IR_Send::getPacket(uint8_t &data){
    IR_Send::generatePacket(data);
    return packet;
}

void IR_Send::send(uint16_t D){
    for(int i=15; i>=0; i--){
        IR_Send::pulse((D >> i) & 1);
    }
}