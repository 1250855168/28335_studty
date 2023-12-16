/*
 * timer.c
 *
 *  Created on: 2023��12��1��
 *      Author: ych
 */


#include <timer.h>
#include"DSP2833x_Project.h"
#define CPU_FRQ_150MHZ 1

void CPU_Timer_Config(void){
    InitCpuTimers();//CPU��ʼ��

    /*����CPU����*/
    #if(CPU_FRQ_150MHZ)
    //ConfigCpuTimer(&CpuTimer0,150,1000000);//<��ʱ��x,ϵͳʱ��Ƶ��MHZ��ʱ��us>,1s�ж�һ��
   ConfigCpuTimer(&CpuTimer1,150,500000);//<��ʱ��x,ϵͳʱ��Ƶ��MHZ��ʱ��us>��0.5s�ж�һ��
   //ConfigCpuTimer(&CpuTimer2,150,100000);//<��ʱ��x,ϵͳʱ��Ƶ��MHZ��ʱ��us>��0.1s�ж�һ��
    #endif

    #if(CPU_FRQ_100MHZ)
    ConfigCpuTimer(&CpuTimer0,100,1000000);//<��ʱ��x,ϵͳʱ��Ƶ��MHZ��ʱ��us>,1s�ж�һ��
    ConfigCpuTimer(&CpuTimer1,100,500000);//<��ʱ��x,ϵͳʱ��Ƶ��MHZ��ʱ��us>��0.5s�ж�һ��
    ConfigCpuTimer(&CpuTimer2,100,100000);//<��ʱ��x,ϵͳʱ��Ƶ��MHZ��ʱ��us>��0.1s�ж�һ��
    #endif

    /*ϵͳ��ʱ����ʼ����*/
    //CpuTimer0Regs.TCR.all=0x4001;
   CpuTimer1Regs.TCR.all=0x4001;
   // CpuTimer2Regs.TCR.all=0x4001;

    /*ʹ��CPU���ж�*/
    //IER|=M_INT1;//ʹ��CPU��INT1�ж�
    IER|=M_INT13;//ʹ��CPU��INT13�ж�
   //IER|=M_INT14;//ʹ��CPU��INT14�ж�

    /*ʹ��PIE���жϣ�ֻ��Timer0�ģ���������Ҫ*/
    //PieCtrlRegs.PIEIER1.bit.INTx7=1;

}
