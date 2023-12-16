/*
 * oled.h
 *
 *  Created on: 2023��12��15��
 *      Author: ych
 */

#ifndef HARDWARE_INCLUDE_OLED_H_
#define HARDWARE_INCLUDE_OLED_H_

#include"DSP2833x_Project.h"

/**
 *  @brief             oledд����
 *  @parameter              ��
 *  @return_value           ��
 */
void WriteCmd(Uint16 IIC_Command) ;

/**
 *  @brief             oledд����
 *  @parameter              ��
 *  @return_value           ��
 */
void WriteDat(Uint16 IIC_Data) ;


/**
*  @brief             OELD��Ļ��ʼ��
*  @parameter              ��
*  @return_value           ��
*/
void OLED_Init(void);


/**
*  @brief             �����������
*  @parameter              ��
*  @return_value           ��
*/
void SetPos(unsigned char x,unsigned char y);


/**
*  @brief             ȫ�����
*  @parameter              ��
*  @return_value           ��
*/
void OLED_Fill(unsigned char Fill_Data);


/**
*  @brief              ����
*  @parameter              ��
*  @return_value           ��
*/
void OLED_Clean(void);

/**
*  @brief               ��OLED
*  @parameter              ��
*  @return_value           ��
*/
void OLED_ON(void);

/**
*  @brief               �ر�OLED
*  @parameter              ��
*  @return_value           ��
*/
void OLED_OFF(void);



/**
*  @brief               ��ʾ�ַ���
*  @parameter              ��
*  @return_value           ��
*/
void OLED_ShowStr(unsigned char x,unsigned char y,unsigned char ch[],unsigned TextSize);


#endif /* HARDWARE_INCLUDE_OLED_H_ */
