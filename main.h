#ifndef MAIN_H
#define MAIN_H

#include "LPC13xx.h"                    // Device header
#include "gpio_lpc.h"
#include "gpio.h"

#include <stdio.h>

#define MACRO_FLASHREG      3
#define MACRO_FLASHARRAY    4
#define MACRO_I2C           5
#define MACRO_GPIO          6
#define MACRO_CT16B0        7
#define MACRO_CT16B1        8
#define MACRO_CT32B0        9
#define MACRO_CT32B1        10
#define MACRO_IOCON         16

#define A_ON            LPC_GPIO0->DATA |= 0x20;
#define A_OFF           LPC_GPIO0->DATA &= ~0x20;

#define B_ON            LPC_GPIO0->DATA |= 0x200; 
#define B_OFF           LPC_GPIO0->DATA &= ~0x200; 

#define C_ON            LPC_GPIO0->DATA |= 0x100;
#define C_OFF           LPC_GPIO0->DATA &= ~0x100;

#define D_ON            LPC_GPIO0->DATA |= 0x80;
#define D_OFF           LPC_GPIO0->DATA &= ~0x80;

#define E_ON            LPC_GPIO0->DATA |= 0x4;
#define E_OFF           LPC_GPIO0->DATA &= ~0x4;

#define F_ON            LPC_GPIO0->DATA |= 0x8;
#define F_OFF           LPC_GPIO0->DATA &= ~0x8;

#define BLUR_ON         LPC_GPIO2->DATA |= 0x1;   
#define BLUR_OFF        LPC_GPIO2->DATA &= ~0x1;   

#define OFF             A_OFF; B_OFF; C_OFF; D_OFF; E_OFF; F_OFF;
#define ON_ZERO         A_ON; B_ON; C_ON; D_ON; E_ON; F_ON;
#define ON_ONE          A_OFF; B_ON; C_ON; D_OFF; E_OFF; F_OFF;
#define ON_TWO          A_ON; B_ON; C_OFF; D_ON; E_ON; F_OFF;
#define ON_THREE        A_ON; B_ON; C_ON; D_ON; E_OFF; F_OFF;
#define ON_FOUR         A_OFF; B_ON; C_ON; D_OFF; E_OFF; F_ON;
#define ON_FIVE         A_ON; B_OFF; C_ON; D_ON; E_OFF; F_ON;
#define ON_SIX          A_ON; B_OFF; C_ON; D_ON; E_ON; F_ON;
#define ON_SEVEN        A_ON; B_ON; C_ON; D_OFF; E_OFF; F_OFF;
#define ON_EIGHT        A_ON; B_ON; C_ON; D_ON; E_ON; F_ON;
#define ON_NINE         A_ON; B_ON; C_ON; D_ON; E_OFF; F_ON;

#define ON_LEDS0_3      LPC_GPIO3->DATA &= ~0xF;
#define OFF_LEDS0_3     LPC_GPIO3->DATA |= 0xF;

#define ON_LEDS4_7      LPC_GPIO2->DATA &= ~0xF0;
#define OFF_LEDS4_7     LPC_GPIO2->DATA |= 0xF0;

#define ON_ALL_LEDS     LPC_GPIO3->DATA &= ~0xF; LPC_GPIO2->DATA &= ~0xF0;
#define OFF_ALL_LEDS    LPC_GPIO3->DATA |= 0xF; LPC_GPIO2->DATA |= 0xF0; 

void init_pins_with_indicator(void);
void init_hardware(void);
void init_pins_on_phase_shifter(void);
void init_pins_with_buttons(void);
void init_pins_with_leds(void);
void clear_interrupt_flag_gpio(uint8_t port, uint8_t pin);
void init_external_interrupt(uint8_t port, uint8_t pin);
void up_to_external_oscillator(void);
void init_interrupt(void);
void Delay(volatile unsigned long cycles);
void create_array_with_speeds(uint32_t time_count, char prefix);
void set_light_digital_on_indicator(uint8_t val_on_indicator);

#endif
