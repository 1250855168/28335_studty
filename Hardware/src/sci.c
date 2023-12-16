/*
 * sci.c
 *
 *  Created on: 2023��12��1��
 *      Author: ych
 */

#include <sci.h>

static Sci_Gpio_Init(void){
    EALLOW;

 /* Enable internal pull-up for the selected pins */
 // Pull-ups can be enabled or disabled disabled by the user.
 // This will enable the pullups for the specified pins.

     GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;    // Enable pull-up for GPIO28 (SCIRXDA)
     GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;    // Enable pull-up for GPIO29 (SCITXDA)

 //  GpioCtrlRegs.GPBPUD.bit.GPIO36 = 0;    // Enable pull-up for GPIO36 (SCIRXDA)
 //  GpioCtrlRegs.GPBPUD.bit.GPIO35 = 0;    // Enable pull-up for GPIO35 (SCITXDA)

 /* Set qualification for selected pins to asynch only */
 // Inputs are synchronized to SYSCLKOUT by default.
 // This will select asynch (no qualification) for the selected pins.

     GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;  // Asynch input GPIO28 (SCIRXDA)
 //  GpioCtrlRegs.GPBQSEL1.bit.GPIO36 = 3;  // Asynch input GPIO28 (SCIRXDA)

 /* Configure SCI-A pins using GPIO regs*/
 // This specifies which of the possible GPIO pins will be SCI functional pins.

     GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;   // Configure GPIO28 for SCIRXDA operation
     GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;   // Configure GPIO29 for SCITXDA operation
 //  GpioCtrlRegs.GPBMUX1.bit.GPIO36 = 1;   // Configure GPIO36 for SCIRXDA operation
 //  GpioCtrlRegs.GPBMUX1.bit.GPIO35 = 1;   // Configure GPIO35 for SCITXDA operation
     EDIS;
}

void Sci_Init(void){

    Sci_Gpio_Init();

    SciaRegs.SCICCR.all=0x07;//һ��λ��ֹͣλ ��У��λ 8������Ϊ

    SciaRegs.SCICTL1.all=0x03;//ʹ�� RX TX SCICLK

    #if(CPU_FRQ_150MHZ)
    SciaRegs.SCIHBAUD=0x0001;// 9600 baud @LSPCLK = 37.5MHz.
    SciaRegs.SCILBAUD=0x00E7;
    #endif

    #if(CPU_FRQ_100MHZ)
    SciaRegs.SCIHBAUD=0x0001;// 9600 baud @LSPCLK = 20MHz.
    SciaRegs.SCILBAUD=0x0044;
    #endif

    SciaRegs.SCICTL2.bit.RXBKINTENA=1;//�������ݼĴ���ʹ��
    SciaRegs.SCICTL2.bit.TXINTENA=1;//�������ݼĴ���ʹ��
    SciaRegs.SCICTL1.bit.SWRESET=1;//SCI �����λλ

    PieCtrlRegs.PIECTRL.bit.ENPIE=1;//����PIE�ж�
    IER|=M_INT9;
    PieCtrlRegs.PIEIER9.bit.INTx1=1;//����SCIA���������ж�


}

void scia_xmit(int a){

    while (SciaRegs.SCICTL2.bit.TXRDY == 0) {}//���ͻ���Ĵ���׼��������־λ 0��ʾ����
    SciaRegs.SCITXBUF=a;

}


void scia_msg(char * msg){

    int i;
    i = 0;
    SciaRegs.SCICTL2.bit.TXINTENA=0;//���ͻ���Ĵ��� �� SCITXBUF�� �жϽ���
    while(msg[i] != '\0')
    {
        scia_xmit(msg[i]);
        i++;
    }
    SciaRegs.SCICTL2.bit.TXINTENA=1;//���ͻ���Ĵ��� �� SCITXBUF�� �ж�ʹ��

}


