/*
 * led.c
 *
 *  Created on: 2023��12��1��
 *      Author: ych
 */

#include <led.h>


void LED_GPIO_Config(void){
    EALLOW;
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0; // GPIO0����ΪGPIO����
    GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;  // GPIO0����Ϊ���
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0; // GPIO1����ΪGPIO����
    GpioCtrlRegs.GPADIR.bit.GPIO1 = 1;  // GPIO1����Ϊ���
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0; // GPIO2����ΪGPIO����
    GpioCtrlRegs.GPADIR.bit.GPIO2 = 1;  // GPIO2����Ϊ���
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0; // GPIO3����ΪGPIO����
    GpioCtrlRegs.GPADIR.bit.GPIO3 = 1;  // GPIO3����Ϊ���
    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 0; // GPIO4����ΪGPIO����
    GpioCtrlRegs.GPADIR.bit.GPIO4 = 1;  // GPIO4����Ϊ���
    EDIS;
}


