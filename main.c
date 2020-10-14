#include <stdio.h>
#include <stdlib.h>

#include "covid.c"

#define AREA "Dover"
#define DAY (60*60*24)

int* bin(int n){
    int* binary = calloc(8, sizeof(int));
    
    if(n > pow(2, 8)-1){
        return binary;
    }
  
    int i = 0;
    while (n > 0) { 
        binary[7-i] = n % 2; 
        n = n / 2; 
        i++; 
    }
    
    return binary;
}

void set_leds(int* values){

}

int main(){
    time_t secs = time(NULL)-DAY;

    struct covid_data data = get_data(AREA, localtime(&secs));

    printf("New Cases: %d\n", data.today_cases);
    
    int* binary = bin(data.today_cases);

    set_leds(binary);

    return 0;
}
