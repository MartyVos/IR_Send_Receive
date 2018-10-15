#include "hwlib.hpp"
#include "IR_Send.hpp"

int main(){
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms( 1000 );
    namespace target = hwlib::target;
    
    auto OUT = target::pin_out(target::pins::d33);
    auto end = target::pin_out(target::pins::d31);
    uint8_t ID = 0B10001;
    uint8_t D  = 0B00100;
    IR_Send IR(OUT, ID);
    
    for(int i=0; i<10; i++){
        end.set(1);
        auto data = IR.getPacket(D)+i;
        hwlib::cout << "DATA BIN:\t" << hwlib::bin << data << hwlib::endl;
        hwlib::cout << "DATA HEX:\t" << hwlib::hex << data << hwlib::endl;
        IR.send(data);
        end.set(0);
        hwlib::wait_ms(3);
    }
}