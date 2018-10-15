#include "IR_receive.hpp"

void IR_Receive::decodeData(){
    ID = ((dataIn >> 10) & 0x001F);
    data = ((dataIn >> 5) & 0x001F);
    if(checkXor()){
        invalidXor = false;
    }else{
        invalidXor = true;
    }
}

bool IR_Receive::checkXor(){
    if(uint8_t(dataIn & 0x001F) == (ID ^ data)){
        return true;
    }
    return false;
}

void IR_Receive::getDecodedData(){
    decData[0] = ID;
    decData[1] = data;
}

std::array<uint8_t, 2> IR_Receive::receive(){
    if(pin.get() == 0){
        for(int i=0; i<16; i++){
            dataIn = (pin.get() << i);
        }
        decodeData();
        if(!invalidXor){
            getDecodedData();
            return decData;
        }
    }
    invalidXor = false;
    return {uint8_t(0xFF), uint8_t(0xFF)};
}