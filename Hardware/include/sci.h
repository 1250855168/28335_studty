/*
 * sci.h
 *
 *  Created on: 2023��12��1��
 *      Author: ych
 */

#ifndef SRC_SCI_H_
#define SRC_SCI_H_

#include"DSP2833x_Project.h"


void Sci_Init(void);
void scia_xmit(int a);//�����ֽڵĺ���
void scia_msg(char * msg);//��������ĺ���


#endif /* SRC_SCI_H_ */
