/*
 * epwm_led.c
 *
 *  Created on: 2023��12��2��
 *      Author: ych
 */

#include <epwm_led.h>


static epwm1_gpio_init(void){

    EALLOW;

    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;    // Enable pull-up on GPIO0 (EPWM1A)
    GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;    // Enable pull-up on GPIO1 (EPWM1B)

    GpioCtrlRegs.GPADIR.bit.GPIO0=1;//���ó����
    GpioCtrlRegs.GPADIR.bit.GPIO1=1;//���ó����

    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;   // Configure GPIO0 as EPWM1A
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;   // Configure GPIO1 as EPWM1B

    EDIS;
}

void epwm1_led_init(void){

    epwm1_gpio_init();

    EPwm1Regs.TBSTS.all=0;
    EPwm1Regs.TBPHS.half.TBPHS=0;
    EPwm1Regs.TBCTR=0;

    //EPwm1Regs.CMPCTL.all=0x50;        // Immediate mode for CMPA and CMPB
    EPwm1Regs.CMPCTL.bit.LOADAMODE = 2; //�����ȽϼĴ��� A ��CMPA�� ��Ӱ�ӼĴ���װ��ģʽѡ��λ
    EPwm1Regs.CMPCTL.bit.LOADBMODE = 2; // �����ȽϼĴ��� B ��CMPB�� ��Ӱ�ӼĴ���װ��ģʽѡ��λ
    //EPwm1Regs.CMPCTL.bit.SHDWAFULL    //�ж�Ӱ�ӼĴ����Ƿ������ȥ
    //EPwm1Regs.CMPCTL.bit.SHDWAMODE = 0; // Ӱ��ģʽ  1����װ��ģʽ
    //EPwm1Regs.CMPCTL.bit.SHDWBFULL    //�ж�Ӱ�ӼĴ����Ƿ������ȥ
    //EPwm1Regs.CMPCTL.bit.SHDWBMODE = 0; // Ӱ��ģʽ  1����װ��ģʽ
    EPwm1Regs.CMPA.half.CMPA =5000;      //ʱ�������� ��TBCTR�� ��ֵ��Ƚ�
//    EPwm1Regs.CMPB=500;                 //ʱ�������� ��TBCTR�� ��ֵ��Ƚ�


    //EPwm1Regs.AQCTLA.all=0x60;        // EPWMxA = 1 when CTR=CMPA and counter inc
                                      // EPWMxA = 0 when CTR=CMPA and counter dec
    EPwm1Regs.AQCTLA.bit.CAD = 1;
    EPwm1Regs.AQCTLA.bit.CAU = 2;
    //EPwm1Regs.AQCTLB.all=0x60;
    EPwm1Regs.AQCTLB.bit.CAD = 1;
    EPwm1Regs.AQCTLB.bit.CAU = 2;
//  EPwm1Regs.AQCTLB.all=0;
//  EPwm1Regs.AQSFRC.all=0;
//  EPwm1Regs.AQCSFRC.all=0;

//  EPwm1Regs.DBCTL.all=0x23;          // EPWMxB is inverted
    EPwm1Regs.DBRED=0;
    EPwm1Regs.DBFED=0;

    EPwm1Regs.TZSEL.all=0;
    EPwm1Regs.TZCTL.all=0;
    EPwm1Regs.TZEINT.all=0;
    EPwm1Regs.TZFLG.all=0;
    EPwm1Regs.TZCLR.all=0;
    EPwm1Regs.TZFRC.all=0;

    EPwm1Regs.ETSEL.all=0;            // Interrupt when TBCTR = 0x0000
    EPwm1Regs.ETFLG.all=0;
    EPwm1Regs.ETCLR.all=0;
    EPwm1Regs.ETFRC.all=0;

    EPwm1Regs.PCCTL.all=0;

    //EPwm1Regs.TBCTL.all=0x0010+TBCTLVAL;          // Enable Timer
    EPwm1Regs.TBCTL.bit.PHSDIR = 1;
    EPwm1Regs.TBCTL.bit.SYNCOSEL = 1;
    EPwm1Regs.TBCTL.bit.PRDLD = 1;
    EPwm1Regs.TBCTL.bit.PHSEN = 1;
    EPwm1Regs.TBCTL.bit.CTRMODE = 2;
    EPwm1Regs.TBPRD=SP;

    EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;       // ��CTR=TBPRDʱ�������ж�
    EPwm1Regs.ETSEL.bit.INTEN = 1;                 // ʹ���ж�
    EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;            // ÿһ�������ж������Ͳ���һ���ж�

}

void epwm1_test_init(void){

    epwm1_gpio_init(); //150Mhz
    EALLOW;
    EPwm1Regs.TBSTS.all=0;
   // EPwm1Regs.TBPHS.half.TBPHS=500;//ePWM1ģ���ʱ������������500��ʼ�����������Ǵ�0��ʼ����
    EPwm1Regs.TBCTR=0x0000;          //�Ĵ�����������ʱ����������ֵ
   // EPwm1Regs.TBCTL.all=0x0010+TBCTLVAL;            // Enable Timer
    EPwm1Regs.TBCTL.bit.CLKDIV =  1;                 //��������ʱ����������ʱ�ӷ�Ƶϵ��
    EPwm1Regs.TBCTL.bit.CTRMODE = 0;      //��CTRMODE����Ϊ0ʱ����ʾѡ��"�ϼ���"ģʽ��������ģʽ�£�ʱ����������TBCTR����0��ʼ���ϼ���
   // EPwm1Regs.TBCTL.bit.FREE_SOFT = 0x10;
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = 5;        //�������ø���ʱ�ӷ�Ƶϵ��
   //EPwm1Regs.TBCTL.bit.PHSDIR = 1;  // ��λ����λ�� ��ʱ�������� ��TBCTR�� 0����Ϊ��������ģʽʱ ��ͬ���¼�����ʱ������
    //EPwm1Regs.TBCTL.bit.PHSEN = 0;  //1�ڶ��PWM�ź�֮�䱣�̶ֹ�����λ�� ������ͨ����ͬ��
    EPwm1Regs.TBCTL.bit.PRDLD = 0;  // ��Ծ�Ĵ�������Ӱ�ӼĴ���װ����ֵ
    //EPwm1Regs.TBCTL.bit.SWFSYNC = 0;//���� EPwm1Regs.TBCTL.bit.SWFSYNC = 1����ʹ���ͬ����������
    //EPwm1Regs.TBCTL.bit.SYNCOSEL = 0;   //����ͬ�������������Щ����Ҫ������ePWMģ��ͬ����Ӧ�ã�ÿ��ePWMģ����Զ����ؿ��������
    EPwm1Regs.TBPRD=1000;              //ȷ��  PWM �����Ƶ��  1000

   //EPwm1Regs.CMPCTL.all=0x50;        // Immediate mode for CMPA and CMPB
    EPwm1Regs.CMPCTL.bit.LOADAMODE = 2; //�����ȽϼĴ��� A ��CMPA�� ��Ӱ�ӼĴ���װ��ģʽѡ��λ
    EPwm1Regs.CMPCTL.bit.LOADBMODE = 2; // �����ȽϼĴ��� B ��CMPB�� ��Ӱ�ӼĴ���װ��ģʽѡ��λ
  //  EPwm1Regs.CMPCTL.bit.SHDWAFULL    //�ж�Ӱ�ӼĴ����Ƿ������ȥ
   // EPwm1Regs.CMPCTL.bit.SHDWAMODE = 0; // Ӱ��ģʽ  1����װ��ģʽ
   // EPwm1Regs.CMPCTL.bit.SHDWBFULL    //�ж�Ӱ�ӼĴ����Ƿ������ȥ
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = 0; // Ӱ��ģʽ  1����װ��ģʽ
    EPwm1Regs.CMPA.half.CMPA =500;      //ʱ�������� ��TBCTR�� ��ֵ��Ƚ�
    EPwm1Regs.CMPB=500;                 //ʱ�������� ��TBCTR�� ��ֵ��Ƚ�

   //EPwm1Regs.AQCTLA.all=0x60;        // EPWMxA = 1 when CTR=CMPA and counter inc
                                      // EPWMxA = 0 when CTR=CMPA and counter dec
    //EPwm1Regs.AQCTLA.bit.CAD = 2;              //���������ڼ�����ʱ�� �����������
    EPwm1Regs.AQCTLA.bit.CAU = 2;             //����������������ʱ�� ����������� 2Ϊ�ߵ�ƽ
    //EPwm1Regs.AQCTLA.bit.CBD = 2;            //�Ҽ������ڼ�����ʱ�� �����������
    //EPwm1Regs.AQCTLA.bit.CBU = 2;          //�Ҽ�������������ʱ�� �����������
   // EPwm1Regs.AQCTLA.bit.PRD             //��ʱ�������� ��TBCTR�� ��ֵ��������ֵʱ�� �����������
   // EPwm1Regs.AQCTLA.bit.ZRO             // ��ʱ�������� ��TBCTR�� ��ֵΪ 0 ʱ�� �����������
   //EPwm1Regs.AQCTLB.all=0x60;
    //EPwm1Regs.AQCTLB.bit.CAD = 2;               //���������ڼ�����ʱ�� �����������
    //EPwm1Regs.AQCTLB.bit.CAU = 2;              //����������������ʱ�� �����������
    //EPwm1Regs.AQCTLB.bit.CBD = 2;              //�Ҽ������ڼ�����ʱ�� �����������
    EPwm1Regs.AQCTLB.bit.CBU = 2;              //�Ҽ�������������ʱ�� �����������
   // EPwm1Regs.AQCTLB.bit.PRD
   // EPwm1Regs.AQCTLB.bit.ZRO
   //EPwm1Regs.AQSFRC.all=0;
    //EPwm1Regs.AQSFRC.bit.ACTSFA = 0;           //�� A ���һ�����ǿ���¼�����ʱ�� �Զ�����Ӱ��
    //EPwm1Regs.AQSFRC.bit.ACTSFB = 0;           //�� B ���һ�����ǿ���¼�����ʱ�� �Զ�����Ӱ��
   // EPwm1Regs.AQSFRC.bit.OTSFA = 0;            //A ���һ�����ǿ���¼�
   // EPwm1Regs.AQSFRC.bit.OTSFB = 0;            //B ���һ�����ǿ���¼�
   // EPwm1Regs.AQSFRC.bit.RLDCSF = 2;           // AQSFRC �Ĵ�����Ӱ�ӼĴ�������װ��ֵ
   //EPwm1Regs.AQCSFRC.all=0;
   // EPwm1Regs.AQCSFRC.bit.CSFA = 0;            //�������ǿ���¼����
  //  EPwm1Regs.AQCSFRC.bit.CSFB = 0;            //�������ǿ���¼����


/*
    //EPwm1Regs.DBCTL.all=0x23;          // EPWMxB is inverted 0000 0000 0010 0011
    EPwm1Regs.DBCTL.bit.IN_MODE = 2;         // ��������ģʽ����λ
    EPwm1Regs.DBCTL.bit.OUT_MODE = 3;         //�������ģʽ����λ
    EPwm1Regs.DBCTL.bit.POLSEL = 0;           //����ѡ�����λ
    EPwm1Regs.DBRED = 100;                      //λ 9 �� 0�� DEL�� ��λ�������������ӳ�ʱ��
    EPwm1Regs.DBFED = 100;                     //λ 9 �� 0�� DEL�� ��λ�������������ӳ�ʱ��
*/
    /*
    //EPwm1Regs.TZSEL.all=0;
    EPwm1Regs.TZSEL.bit.CBC1 = 0; // 1�� ʹ��TZ1��Ϊ�ظ��ѿ��ź�Դ�� ����TZ1����Ϊ��ʱ�� ��ʾ�����ظ��ѿ�
    EPwm1Regs.TZSEL.bit.OSHT1 = 0;// 1�� ʹ��TZ1��Ϊ���������ѿ��ź�Դ�� ����TZ1 ����Ϊ��ʱ�� ��ʾ�������������ѿ�

    //EPwm1Regs.TZCTL.all=0;
    EPwm1Regs.TZCTL.bit.TZA = 0;//��һ���ѿ��¼�����ʱ�� ��ο��� ePWMxB ����źţ� �ĸ����Ų����� �ѿ��¼��� TZSEL �Ĵ���ȷ��
    EPwm1Regs.TZCTL.bit.TZB = 0;// ��һ���ѿ��¼�����ʱ�� ��ο��� ePWMxA ����źţ� �ĸ����Ų����� �ѿ��¼��� TZSEL �Ĵ���ȷ��
    //EPwm1Regs.TZEINT.all=0;
    EPwm1Regs.TZEINT.bit.CBC = 0;//�ظ��ѿ������ж�ʹ��λ
    EPwm1Regs.TZEINT.bit.OST = 0;//���������ѿ������ж�ʹ��λ
    //EPwm1Regs.TZFLG.all=0;
    EPwm1Regs.TZFLG.bit.CBC = 0;
    EPwm1Regs.TZFLG.bit.INT = 0;
    EPwm1Regs.TZFLG.bit.OST = 0;
    //EPwm1Regs.TZCLR.all=0;
    EPwm1Regs.TZCLR.bit.CBC = 0;//д 1 ���ظ��ѿ��¼���־λ
    EPwm1Regs.TZCLR.bit.INT = 0;//д1 �� INT �жϱ�־λ
    EPwm1Regs.TZCLR.bit.OST = 0;//д 1 �嵥�������ѿ��¼���־λ
    //EPwm1Regs.TZFRC.all=0;
    EPwm1Regs.TZFRC.bit.CBC = 0;//д 1 ǿ��һ���ظ��ѿ��¼������� ͬʱ��λ�ظ��ѿ��¼���־λ
    EPwm1Regs.TZFRC.bit.OST = 0;//д 1 ǿ��һ�����������ѿ��¼�����
*/
    //EPwm1Regs.ETSEL.all=0;            // Interrupt when TBCTR = 0x0000
    EPwm1Regs.ETSEL.bit.INTEN = 1;//ePWM �ж�ʹ��λ
    EPwm1Regs.ETSEL.bit.INTSEL = 4;// �����ж�ѡ��λ
   // EPwm1Regs.ETSEL.bit.SOCAEN = 0;//���� ePWMxSOCA ����ʱ���� A - D ת����
   // EPwm1Regs.ETSEL.bit.SOCASEL = 0;//ePWMxSOCA ����ѡ��λ
   // EPwm1Regs.ETSEL.bit.SOCBEN = 0;//���� ePWMxSOCB ����ʱ���� A - D ת����
   // EPwm1Regs.ETSEL.bit.SOCBSEL = 0;//ePWMxSOCB ����ѡ��λ
    //EPwm1Regs.ETFLG.all=0;
    EPwm1Regs.ETFLG.bit.INT = 0;//�жϱ�־λ
   // EPwm1Regs.ETFLG.bit.SOCA = 0;//ePWMxSOCA ���� A - D ת����־λ
   // EPwm1Regs.ETFLG.bit.SOCB = 0;//ePWMxSOCB ���� A - D ת����־λ
    //EPwm1Regs.ETCLR.all=0;
   EPwm1Regs.ETCLR.bit.INT = 0;// �жϱ�־���λ
   // EPwm1Regs.ETCLR.bit.SOCA = 0;//ePWMxSOCA ���� A - D ת����־���λ
   // EPwm1Regs.ETCLR.bit.SOCB = 0;//ePWMxSOCB ���� A - D ת����־���λ
    //EPwm1Regs.ETFRC.all=0;
   // EPwm1Regs.ETFRC.bit.INT = 0;//ǿ��ePWM �ж�ʹ��λ
   // EPwm1Regs.ETFRC.bit.SOCA = 0;//ǿ�Ƶ��� ePWMxSOCA ����ʱ���� A - D ת����
   // EPwm1Regs.ETFRC.bit.SOCB = 0;//ǿ�Ƶ��� ePWMxSOCA ����ʱ���� A - D ת����

   //EPwm1Regs.PCCTL.all=0;         //����ôʹ��ն��
    EPwm1Regs.PCCTL.bit.CHPDUTY = 0;//ն��ʱ��ռ�ձ�
    EPwm1Regs.PCCTL.bit.CHPEN = 0;//ն��ʹ��λ
    EPwm1Regs.PCCTL.bit.CHPFREQ = 0;//ն��ʱ��Ƶ��
    EPwm1Regs.PCCTL.bit.OSHTWTH = 0;//����������

    EDIS;

}
