#ifndef GPIO_LPC_H_
#define GPIO_LPC_H_


#define A_IN_SEGMENT    7
#define B_IN_SEGMENT    8
#define C_IN_SEGMENT    9
#define D_IN_SEGMENT    4
#define E_IN_SEGMENT    3
#define F_IN_SEGMENT    2
#define G_IN_SEGMENT    5
#define H_IN_SEGMENT    0

#define ON_A_IN_SEGMENT LPC_GPIO0->DATA

#define ON_LEDS0_3      LPC_GPIO3->DATA &= ~0xF;
#define OFF_LEDS0_3     LPC_GPIO3->DATA |= 0xF;

#define ON_LEDS4_7      LPC_GPIO2->DATA &= ~0xF0;
#define OFF_LEDS4_7     LPC_GPIO2->DATA |= 0xF0;

#define ON_ALL_LEDS     LPC_GPIO3->DATA &= ~0xF; LPC_GPIO2->DATA &= ~0xF0;
#define OFF_ALL_LEDS    LPC_GPIO3->DATA |= 0xF; LPC_GPIO2->DATA |= 0xF0;             

#define INPUT           0
#define OUTPUT          1

#define PIN_0           0
#define PIN_1           1
#define PIN_2           2
#define PIN_3           3
#define PIN_4           4
#define PIN_5           5
#define PIN_6           6
#define PIN_7           7
#define PIN_8           8
#define PIN_9           9
#define PIN_10          10
#define PIN_11          11

#endif
