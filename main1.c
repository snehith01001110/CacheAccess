//B
#include "cache_model.c"
#include <math.h>

int main(){
    cm_init();
    cm_disable_cache();

    int output_twelve = 0;

    float avg = 0;
    int address = rand_int(CM_ADDRESS_SPACE_SIZE);

    int hist[4] = {12,0,1,0};
    int cyclesper;

    for (int i = 0; i < 100000; i++){
        int prob_next_addr_dist = rand_int(100);
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
//19 and 1 




        avg += cm_get_last_access_cycles(); 
        cyclesper = cm_get_last_access_cycles();
        if (cyclesper != 12){
            printf("%d", cyclesper);
        }
        if (cyclesper == hist[0]){
            hist[1] = hist[1] + 1;
        }
        else{
            hist[3] = hist[3] + 1;
        }
           




    }   

    for (int x = 0; x< 4; x++ ) {
      printf("Element[%d] = %d\n", x, hist[x] );
    } 

    avg = avg/100000;

    printf("%f",(avg));

    return 0;
}