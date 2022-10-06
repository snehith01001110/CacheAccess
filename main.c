//A
#include <stdio.h>
#include <stdlib.h>
#include "cache_model.c"

int main(){
    cm_init();
    cm_enable_cache();
    float average = 0;
    
    int hist[4] = {19,0,1,0};

    for (int i = 0; i < 100000; ++i){
        int randint = rand_int(CM_ADDRESS_SPACE_SIZE);
        cm_do_access(randint);
        long cycle = cm_get_last_access_cycles();

        if (cycle != 19 && cycle != 1){
            printf("%ld", cycle);
        }

        average = average + cycle;

        if (cycle == hist[0]){
            hist[1] = hist[1] + 1;
        }
        else{
            hist[3] = hist[3] + 1;
        }
    }

    for (int j = 0; j < 4; j++ ) {
      printf("Element[%d] = %d\n", j, hist[j] );
    }


    average = average / 100000;
    printf("%f", average);
    return 0;

}

//18.443621    enable cache
//11.999780    disable cache 

//made an array to hold values of cache cycle and enter repeating numbers 
//compare values and form decimals to make a plot of cdf 
//later this is used to form the ratios that are useful when creating the limits.
