//C
#include "cache_model.c"
#include <math.h>

int main(){
    cm_init();
    cm_enable_cache();

    float avg = 0;
    int address = rand_int(CM_ADDRESS_SPACE_SIZE);
    for (int i = 0; i < 100000; i++){
        int prob_next_addr_dist = 97;//rand_int(100);
        if (prob_next_addr_dist < 60) {
            if (address + 1 < CM_ADDRESS_SPACE_SIZE){
                address = address + 1;
            } 
            else {
                address = address - 1;
            }
        } 
        else if (prob_next_addr_dist >= 60 && prob_next_addr_dist < 95){
            if (address + 40 < CM_ADDRESS_SPACE_SIZE) {
                address = address + (2 + rand_int(39));
            } 
            else {
                address = address - (2 + rand_int(39));
            }
        } 
        else {
            int temp_addr = rand_int(CM_ADDRESS_SPACE_SIZE);
            while (abs(temp_addr-address) <= 40) {
                temp_addr = rand_int(CM_ADDRESS_SPACE_SIZE);
            }
            address = temp_addr;
        }
        cm_do_access(address);
        avg += cm_get_last_access_cycles();        
    }    

    avg = avg/100000;
    printf("%f",(avg));

    return 0;
}

