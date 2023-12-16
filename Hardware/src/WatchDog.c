/*
 * WatchDog.c
 *
 *  Created on: 2023��12��2��
 *      Author: ych
 */


#include <WatchDog.h>
#include"DSP2833x_Project.h"

extern interrupt void wakeint_isr(void);


void InitWatchDog(void){

    EALLOW;
    SysCtrlRegs.SCSR = BIT1;//�����жϿ��Ź�  �رո�λ���Ź�
    EDIS;

    EALLOW;  // This is needed to write to EALLOW protected registers
    PieVectTable.WAKEINT = &wakeint_isr;
    EDIS;   // This is needed to disable write to EALLOW protected registers

    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block
    PieCtrlRegs.PIEIER1.bit.INTx8 = 1;   // Enable PIE Gropu 1 INT8
    IER |= M_INT1;                       // Enable CPU int1
    EINT;                                // Enable Global Interrupts

    ServiceDog();

    EALLOW;
    SysCtrlRegs.WDCR = 0x0028;//�������Ź�
    EDIS;

}
