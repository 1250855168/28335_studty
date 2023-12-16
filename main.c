/*
 * main.c
 *
 *  Created on: 2023��12��1��
 *      Author: ych
 */

#include <button.h>
#include <epwm_led.h>
#include <led.h>
#include <sci.h>
#include <WatchDog.h>
#include<oled.h>
#include"DSP2833x_Project.h"


#define true 1
#define false 0
#define MAX_BUFFER_SIZE 256

extern Uint16 RamfuncsLoadStart;
extern Uint16 RamfuncsLoadEnd;
extern Uint16 RamfuncsRunStart;

Uint16 PWM_count=0;
Uint16 PWM_direction=0;




/**
*   @brief                   1ms�ӳٺ���
 *  @parameter                  t
 *  @return_value               ��
 */
//void delay_1ms(Uint32 t){
//
//    while(t--){
//
//        DELAY_US(1000);
//
//    }
//
//}

//interrupt void xint1_isr(void){
//
//    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;//�����һ�����е��ж�  �����������ж���
//    DELAY_US(1000);//����
//    if(GpioDataRegs.GPADAT.bit.GPIO13 == 0){
//
//        //����
//
//    }
//
//}

//��ʱ��0�жϷ����ӳ���
//interrupt void cpu_timer0_isr(void);{
//
//    //����
//
//    CpuTimer0.InterruptCount++;
//    PieCtrlRegs.PIEACK.all=PIEACK_GROUP1;//�ж���Ӧ�𣬿��Դ���1���ո����ж�
//
//}

////��ʱ��1�жϷ����ӳ���
//interrupt void cpu_timer1_isr(void){
//
//    //����
//
//    CpuTimer1.InterruptCount++;
//    EDIS;//ֱ��ȷ�ϣ�����PIE
//
//}
//interrupt void cpu_timer2_isr(void);//��ʱ��2�жϷ����ӳ���

Uint32 WakeCount;
Uint32 LoopCount;

interrupt void wakeint_isr(void)
{
    WakeCount++;

    // Acknowledge this interrupt to get more from group 1
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

//BRR = LSPCLK/(BAUD �� 8)-1������

Uint16 ReceivedData[MAX_BUFFER_SIZE];
Uint16 DataLength = 0;
Uint16 DataIndex = 0;
Uint16 IsReceiving = false;


/**
 * ���ܵĸ�ʽΪ16����  �磺01 11  ����11
 *                  ��: 02  11 22 ���� 11 22
 *
 *
 */
interrupt void scia_Rx_isr()
{
    Uint16 receivedByte = SciaRegs.SCIRXBUF.all;

    if (!IsReceiving)
    {
        // �������ݳ���
        DataLength = receivedByte;
        DataIndex = 0;
        IsReceiving = true;
    }
    else
    {
        // ����ʵ������
        ReceivedData[DataIndex++] = receivedByte;

        if (DataIndex >= DataLength)
        {
            // ������ȫ
            IsReceiving = false;
        }
    }

    // ����жϱ�־
    SciaRegs.SCIFFRX.bit.RXFFOVRCLR = 1;
    SciaRegs.SCIFFRX.bit.RXFFINTCLR = 1;

    PieCtrlRegs.PIEACK.all = M_INT9;
}


interrupt void epwm1_isr(void){


    if(EPwm1Regs.TBSTS.bit.CTRDIR==1)//��ǰPWM_count�����Ƿ�=0 (=0��ʾ���ϣ�=1��ʾ����)
    {
        PWM_count=PWM_count+50;//PWM_count�������������CMPA�Ƚ�ֵ�� ����PWM_count
    }else{
        PWM_count=PWM_count-50;
    }

   EPwm1Regs.CMPA.half.CMPA = PWM_count;//����EPWM1��CMPA�Ƚ�ֵ

   // ����жϱ�־λ����ֹ�ظ������ж�
   EPwm1Regs.ETCLR.bit.INT = 1;

   // Ӧ����жϣ�ʹ�ôӵ�3����ո��������жϣ������жϵڼ��飬����鿴�ж�������
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}


//__interrupt void i2c_int1a_isr(void)     // I2C-A
//{
//   Uint16 IntSource;
//
//   // Read interrupt source
//   IntSource = I2caRegs.I2CISRC.bit.INTCODE & 0x7;  //��ȡIIC�жϵ�״̬
//
// Uint32  Interrupts_Mask= IER;//ֻ����ʵʱ����ϵͳ�������ʱ���ж�  ���������ж�ȫ������
//   IER &= 0x2000;
//   IFR &= ~0x2000;
//   EINT;  //�������ж�ʹ��
//
//   switch(IntSource)
//      {
//          case I2C_NO_ISRC:   // =0  ��
//              break;
//
//          case I2C_ARB_ISRC:  // =1 �ٲö�ʧ
//              break;
//
//          case I2C_NACK_ISRC: // =2 ��⵽��Ӧ������
//              break;
//
//          case I2C_ARDY_ISRC: // =3 �Ĵ�����ȡ׼�����
//              break;
//
//          case I2C_RX_ISRC:   // =4 ��������׼�����
//              break;
//
//          case I2C_TX_ISRC:   // =5 ��������׼�����
//              break;
//
//          case I2C_SCD_ISRC:  // =6 ��⵽ֹͣ(STOP)����
//              break;
//
//          case I2C_AAS_ISRC:  // =7   //����Ϊ��
//              break;
//
//      }
//
//   DINT;//�����ж�
//   IER = Interrupts_Mask;//�ָ�֮ǰ���жϱ�־
//
//   // Enable future I2C (PIE Group 8) interrupts
//   PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
//}



void main(void){


//��һ����ʼ��ϵͳʱ��
    InitSysCtrl();

//�ڶ�����ʼ��GPIO��
   // InitGpio();

//��������������жϺͳ�ʼ��PIE�ж�������
    DINT;//����CPU�ж�
    InitPieCtrl();//PIE ���ƼĴ�����Ĭ��״̬
    IER = 0X0000;
    IFR = 0X0000;
    InitPieVectTable();//��ʼ���ж������� ��ʼ��

//ע���жϳ������

#if 0
    MemCopy(&RamfuncsLoadStart,&RamfuncsLoadEnd,&RamfuncsRunStart);
    InitFlash();
#endif

//���Ĳ���ʼ������
    //InitPeripherals();

//�û���������

    //led
    //LED_GPIO_Config();


    //button  exteral interrupt
//    EALLOW;
//    PieVectTable.XINT1 = &xint1_isr;
//    EDIS;
//
//    EALLOW;
//    PieVectTable.SCIRXINTA=&scia_Rx_isr;
//    EDIS;
//
//    IER |=  M_INT1;//ʹ�ܵ�һ���ж�
//    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;//ʹ�����ж�
//    PieCtrlRegs.PIEIER1.bit.INTx4 = 1;//ʹ�ܵ�һ����ĸ�
//
//    EINT;//�ж�ʹ��
//    ERTM;//ʹ����ʱ���ж�
//
//
//
//    //button 3*4
//    Button_Matrix_Config();
//
//
//
//    //timer
//    EALLOW;
//    //PieVectTable.TINT0=&cpu_timer0_isr;//����ʱ���жϷ����ӳ���ĵ�ַ��ŵ���Ӧ��������ַ��
//    PieVectTable.XINT13=&cpu_timer1_isr;
//    //PieVectTable.TINT2=&cpu_timer2_isr;
//    EDIS;
//
//
//    //WatchDog
//    InitWatchDog();
//
//
//    //sci
//    Sci_Init();


    //epwm  fan led

//    EALLOW;
//    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
//    SysCtrlRegs.PCLKCR1.bit.EPWM1ENCLK = 1;     // ʹ��ePWM1
//    EDIS;
//
//    EALLOW;
//    PieVectTable.EPWM1_INT = &epwm1_isr;
//    EDIS;
//
//    EALLOW;
//    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;//ֹͣʱ����ʱ��
//    EDIS;
//
//    epwm1_led_init();
//
//    EALLOW;
//    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;//����ʱ����ʱ��
//    EDIS;
//
//    IER |= M_INT3;//ʹ��INT3�ж�
//    PieCtrlRegs.PIEIER3.bit.INTx1 = 1;//ʹ��ePWM1�ж�
//
//    EINT;
//    ERTM;


    //ecap distance_measurement  cap_graph


    //i2c

   //AT42C0x
//    Uint16 temp1[2];
//
//    Uint8 temp2[2]={0X7,0x8};
//
//    At24c01_Init();
//
//    WriteData(0x50,0X00,2,temp2);
//
//    ReadData(0x50,0X00,2,temp1);

    //oled


    OLED_Init();

    OLED_ON();

    OLED_Fill(0);

    unsigned char ch[] = "1234567";

    OLED_ShowStr(1,1,ch,1);
    DELAY_US(100000);
    OLED_ShowStr(1,2,ch,2);


    //adc-DMA  Temp Lighting





    //spi  oled  flash



    //can



    //�û������������


}



