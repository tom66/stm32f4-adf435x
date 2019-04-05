#include "stm32f4xx.h"
#include "hal.h"
#include "adf435x.h"

int main(void)
{
    hal_init();
    adf435x_init();
    
    while(1) ;
}

