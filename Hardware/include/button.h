/*
 * button.h
 *
 *  Created on: 2023��12��1��
 *      Author: ych
 */

#ifndef SRC_BUTTON_H_
#define SRC_BUTTON_H_


//�����е�GPIO�궨��
#define   L5     GpioDataRegs.GPADAT.bit.GPIO26  //�궨��
#define   L4    GpioDataRegs.GPADAT.bit.GPIO25  //�궨��
#define   L2    GpioDataRegs.GPBDAT.bit.GPIO48  //�궨��
#define   L3    GpioDataRegs.GPADAT.bit.GPIO24  //�궨��

#define  V1_H  GpioDataRegs.GPASET.bit.GPIO21=1;//��������ߵ�ƽ
#define  V2_H  GpioDataRegs.GPASET.bit.GPIO20=1;//��������ߵ�ƽ
#define  V3_H  GpioDataRegs.GPASET.bit.GPIO27=1;//��������ߵ�ƽ

#define  V1_L GpioDataRegs.GPACLEAR.bit.GPIO21=1;//��������͵�ƽ
#define  V2_L GpioDataRegs.GPACLEAR.bit.GPIO20=1;//��������͵�ƽ
#define  V3_L GpioDataRegs.GPACLEAR.bit.GPIO27=1;//��������͵�ƽ

void InitExInt(void);

void Button_Matrix_Config(void);

unsigned char Button_Martix_Scan(void);


#endif /* SRC_BUTTON_H_ */
