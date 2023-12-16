/*
 * button.c
 *
 *  Created on: 2023��12��1��
 *      Author: ych
 */
#include <button.h>
#include"DSP2833x_Project.h"

extern void delay_1ms(Uint32 t);

void InitExInt(void){

    EALLOW;
    GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 0;//����ΪGPIO����
    GpioCtrlRegs.GPADIR.bit.GPIO13 = 0;//gpio���빦��
    GpioCtrlRegs.GPAQSEL1.bit.GPIO13 = 2;//����6�β���
    GpioCtrlRegs.GPACTRL.bit.QUALPRD1 = 255;//���ò���ʱ��
    GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = 13;//ѡ��GPIO13Ϊ�ⲿ����XINT��������
    XIntruptRegs.XINT1CR.bit.POLARITY= 0;     //�½��ش����ж� 0���½��� 1��������
    XIntruptRegs.XINT1CR.bit.ENABLE = 1;      //ʹ��XINT�ж�
    EDIS;


}



void Button_Matrix_Config(void){

    EALLOW;
    SysCtrlRegs.PCLKCR3.bit.GPIOINENCLK=1;//����GPIOʱ��

    GpioCtrlRegs.GPAMUX2.bit.GPIO21=0;//��ͨIOģʽ
    GpioCtrlRegs.GPAPUD.bit.GPIO21=0;//ʹ���ڲ�����
    GpioCtrlRegs.GPADIR.bit.GPIO21=1;//���ó����

    GpioCtrlRegs.GPAMUX2.bit.GPIO20=0;//��ͨIOģʽ
    GpioCtrlRegs.GPAPUD.bit.GPIO20=0;//ʹ���ڲ�����
    GpioCtrlRegs.GPADIR.bit.GPIO20=1;//���ó����

    GpioCtrlRegs.GPAMUX2.bit.GPIO27=0;//��ͨIOģʽ
    GpioCtrlRegs.GPAPUD.bit.GPIO27=0;//ʹ���ڲ�����
    GpioCtrlRegs.GPADIR.bit.GPIO27=1;//���ó����


    GpioCtrlRegs.GPAMUX2.bit.GPIO26=0;//��ͨIOģʽ
    GpioCtrlRegs.GPAPUD.bit.GPIO26=0;//ʹ���ڲ�����
    GpioCtrlRegs.GPADIR.bit.GPIO26=0;//���ó�����



    GpioCtrlRegs.GPAMUX2.bit.GPIO25=0;//��ͨIOģʽ
    GpioCtrlRegs.GPAPUD.bit.GPIO25=0;//ʹ���ڲ�����
    GpioCtrlRegs.GPADIR.bit.GPIO25=0;//���ó�����


    GpioCtrlRegs.GPBMUX2.bit.GPIO48=0;//��ͨIOģʽ
    GpioCtrlRegs.GPBPUD.bit.GPIO48=0;//ʹ���ڲ�����
    GpioCtrlRegs.GPBDIR.bit.GPIO48=0;//���ó�����


    GpioCtrlRegs.GPAMUX2.bit.GPIO24=0;//��ͨIOģʽ
    GpioCtrlRegs.GPAPUD.bit.GPIO24=0;//ʹ���ڲ�����
    GpioCtrlRegs.GPADIR.bit.GPIO24=0;//���ó�����

    EDIS;

    GpioDataRegs.GPASET.bit.GPIO21=1;//��������ߵ�ƽ
    GpioDataRegs.GPASET.bit.GPIO20=1;//��������ߵ�ƽ
    GpioDataRegs.GPASET.bit.GPIO27=1;//��������ߵ�ƽ


}

/*
 * ����ɨ�跨���ʱ�� ����һ��Ϊ�͵�ƽ�� ���༸��ȫΪ�ߵ�ƽ(��ʱ����ȷ��������)��
 * Ȼ�������������һ�θ����Ƿ��е͵�ƽ�� ����⵽ĳһ��Ϊ�͵�ƽ(��ʱ������ȷ��������)��
 * �����Ǳ��ȷ�ϵ�ǰ�����µļ�����һ����һ�еģ� ��ͬ�����������͸���һ�ε͵�ƽ,
 * ���������һ�θ����Ƿ��Ϊ�͵�ƽ���������ɼ�������еİ�����
 * ���м�������ʱ����жϳ����µļ�����һ��������Ȼ����Ҳ���Խ������õ͵�ƽ��
 * ɨ�����Ƿ��е͵�ƽ�� �Ӷ��ﵽ�������̵ļ�⡣
 * */
unsigned char Button_Martix_Scan(void){

    V1_L;
    V2_H;
    V3_H;
    if(L2==0||L3==0||L4==0||L5==0){
        DELAY_US(10000);
        if(L2==0){
            return 0x21;
        }else if(L3==0){
            return 0x31;
        }else if(L4==0){
            return 0x41;
        }else if(L5==0){
            return 0x51;
        }
    }

    V2_L;
    V1_H;
    V3_H;
    if(L2==0||L3==0||L4==0||L5==0){
        DELAY_US(10000);
        if(L2==0){
            return 0x22;
        }else if(L3==0){
            return 0x32;
        }else if(L4==0){
            return 0x42;
        }else if(L5==0){
            return 0x52;
        }
    }

    V3_L;
    V1_H;
    V2_H;
    if(L2==0||L3==0||L4==0||L5==0){
        DELAY_US(10000);
        if(L2==0){
            return 0x23;
        }else if(L3==0){
            return 0x33;
        }else if(L4==0){
            return 0x43;
        }else if(L5==0){
            return 0x53;
        }
    }

    return 0x00;
}
