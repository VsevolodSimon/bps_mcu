#include "main.h"

#define DELAY_DEBOUNCE      100000
#define QUANTITY_SPEEDS     3

uint32_t arr_val_in_reg[QUANTITY_SPEEDS];
uint8_t napr = 1;

void create_array_with_speeds(uint32_t time_count, char prefix)
{ 
    static int i = 0;
    uint32_t divider = (prefix == 'm') ? 1000 : 1000000;
    arr_val_in_reg[i++] = (uint32_t)(((long double)time_count / ((long double)64 * (long double)divider)) * (long double)SystemCoreClock);
}

void SysTick_Handler(void)
{
    static uint8_t counting_n = 0;
    if (napr == 1)
        (counting_n == 63) ? counting_n = 0 : counting_n++;
    else if (napr == 2)
        (counting_n == 0) ? counting_n = 63 : counting_n--;
    LPC_GPIO1->DATA = (counting_n << 5);     //write value in port
}

// BUT1 PIO2_9
void PIOINT2_IRQHandler(void)
{ 
    while( !(LPC_GPIO2->DATA & 0x200) ){};
    Delay(DELAY_DEBOUNCE); 
    switch (napr)
    {
        case 1: napr = 2;   
        OFF_ALL_LEDS;
        BLUR_OFF;
        break; 

        case 2: napr = 1;
        ON_ALL_LEDS;
        BLUR_ON;
        break;
    }
    clear_interrupt_flag_gpio(2, 9);
}

void PIOINT1_IRQHandler(void)
{
    static int j = 0;
    while( !(LPC_GPIO1->DATA & 0x10) ){};
    Delay(DELAY_DEBOUNCE);         // Wait BUT1 mechanical vibrations to be set. 
    __disable_irq();
    set_light_digital_on_indicator(j);
    SysTick_Config(arr_val_in_reg[j++]);
    if(j == QUANTITY_SPEEDS)
        j = 0;
    __enable_irq();
    clear_interrupt_flag_gpio(1, 4);
}

int main (void)
{   
    init_hardware();
    init_interrupt();
    OFF;
    BLUR_OFF; 
    create_array_with_speeds(2, 'm');
    create_array_with_speeds(1, 'm');
    create_array_with_speeds(500, 'u');
    while(1)
    {      
        
    }
}

void set_light_digital_on_indicator(uint8_t val_on_indicator)
{
    switch(val_on_indicator)
    {
        case 0: OFF; ON_ZERO;   break;
        case 1: OFF; ON_ONE;    break;
        case 2: OFF; ON_TWO;    break;
        case 3: OFF; ON_THREE;  break;
        case 4: OFF; ON_FOUR;   break;
        case 5: OFF; ON_FIVE;   break;
        case 6: OFF; ON_SIX;    break;
        case 7: OFF; ON_SEVEN;  break;
        case 8: OFF; ON_EIGHT;  break;
        case 9: OFF; ON_NINE;   break;
    }
}

void init_interrupt(void)
{
    init_external_interrupt(2, 9);
    init_external_interrupt(1, 4);
    NVIC_EnableIRQ(EINT2_IRQn);
    NVIC_EnableIRQ(EINT1_IRQn);
    __enable_irq();
}

void Delay(volatile unsigned long cycles)
{
  while(cycles)
  {
    cycles--;
  }
}

void up_to_external_oscillator(void)
{
    LPC_SYSCON->MAINCLKSEL &= ~0x3;     //main clock->irc если pll не заработает
    
    LPC_SYSCON->MAINCLKUEN &= ~0x1;      //clear update main clock
    LPC_SYSCON->MAINCLKUEN |= 0x1;      //update main clock
    
    LPC_SYSCON->SYSPLLCLKSEL |= 0x1;    //use system oscillator
    
    LPC_SYSCON->SYSPLLCLKUEN &= ~0x1;    //clear update pll main clock
    LPC_SYSCON->SYSPLLCLKUEN |= 0x1;    //update pll main clock
    
    LPC_SYSCON->SYSAHBCLKDIV = 0x1;     //divider clk for core
    LPC_SYSCON->PDRUNCFG |= (1UL<<7);   //system pll powered down
    LPC_SYSCON->SYSPLLCTRL = 0x25;
    LPC_SYSCON->PDRUNCFG &= ~(1UL<<7);  //system pll powered
    while((LPC_SYSCON->SYSPLLSTAT & 0x1) == 0)  //wait unlocked pll
        ;
    LPC_SYSCON->MAINCLKSEL |= 0x3;
    
    LPC_SYSCON->MAINCLKUEN &= ~0x1; 
    LPC_SYSCON->MAINCLKUEN |= 0x1;    
}

void clear_interrupt_flag_gpio(uint8_t port, uint8_t pin)
{
    LPC_GPIO[port]->IC = (1UL << pin);
}

void init_external_interrupt(uint8_t port, uint8_t pin)
{
    LPC_GPIO[port]->IS  &= ~(1UL << pin);
    LPC_GPIO[port]->IEV |= (1UL << pin);
    LPC_GPIO[port]->IE  |= (1UL << pin);
    LPC_GPIO[port]->IC  |= (1UL << pin);
}

void init_hardware(void)
{
    up_to_external_oscillator();
    SystemCoreClockUpdate();
    LPC_SYSCON->SYSAHBCLKCTRL |= (1UL<<MACRO_IOCON);
    GPIOInit();
    init_pins_on_phase_shifter();
    init_pins_with_indicator();
    init_pins_with_buttons();
    init_pins_with_leds();
    LPC_GPIO1->DATA = 0xFC0;
}


void init_pins_with_indicator(void)
{
    GPIOSetDir(PORT0, PIN_7, OUTPUT);
    GPIOSetDir(PORT0, PIN_8, OUTPUT);
    GPIOSetDir(PORT0, PIN_9, OUTPUT);
    GPIOSetDir(PORT0, PIN_4, OUTPUT);
    GPIOSetDir(PORT0, PIN_3, OUTPUT);
    GPIOSetDir(PORT0, PIN_2, OUTPUT);
    GPIOSetDir(PORT0, PIN_5, OUTPUT);
    GPIOSetDir(PORT2, PIN_0, OUTPUT);      
}

void init_pins_on_phase_shifter(void)
{
    GPIOSetDir(PORT1, PIN_5, OUTPUT);
    GPIOSetDir(PORT1, PIN_6, OUTPUT);
    GPIOSetDir(PORT1, PIN_7, OUTPUT);
    GPIOSetDir(PORT1, PIN_8, OUTPUT);
    GPIOSetDir(PORT1, PIN_9, OUTPUT);
    GPIOSetDir(PORT1, PIN_10, OUTPUT);
}

void init_pins_with_buttons(void)
{
    GPIOSetDir(PORT2, PIN_9, INPUT);
    GPIOSetDir(PORT1, PIN_4, INPUT);
}

void init_pins_with_leds(void)
{
    GPIOSetDir(PORT3, PIN_0, OUTPUT);
    GPIOSetDir(PORT3, PIN_1, OUTPUT);
    GPIOSetDir(PORT3, PIN_2, OUTPUT);
    GPIOSetDir(PORT3, PIN_3, OUTPUT);
    GPIOSetDir(PORT2, PIN_4, OUTPUT);
    GPIOSetDir(PORT2, PIN_5, OUTPUT);
    GPIOSetDir(PORT2, PIN_6, OUTPUT);
    GPIOSetDir(PORT2, PIN_7, OUTPUT);   
}
