/*
 * iic.h
 *
 *  Created on: 2023��12��15��
 *      Author: ych
 */

#ifndef HARDWARE_INCLUDE_IIC_H_
#define HARDWARE_INCLUDE_IIC_H_
#include"DSP2833x_Project.h"

/**
 *  @brief              IICģ�鷢��׼��OK
 *  @parameter              ��
 *  @return_value           ��
 */
Uint16  I2C_xrdy();

/**
 *  @brief              IICģ�����׼��OK
 *  @parameter              ��
 *  @return_value           ��
 */
Uint16  I2C_rrdy();

/**
 *  @brief                  IICд����
 *  @parameter              SlaveAddress���ӻ���ַ��  RomAddress���Ĵ�����ַ�� number��д�����ݵ��ֽ�����  *Wdata��д�����ݵĵ�ַ
 *  @return_value           ״̬��־
 */
Uint16 WriteData( Uint16 SlaveAddress, Uint16 RomAddress,Uint16 number, Uint8 *Wdata);

/**
 *  @brief                  IICд����
 *  @parameter              SlaveAddress���ӻ���ַ��  RomAddress���Ĵ�����ַ�� number��д�����ݵ��ֽ�����  *RamAddr���������ݴ�ŵĵ�ַ
 *  @return_value           ״̬��־
 */
Uint16 ReadData( Uint16 SlaveAddress, Uint16 RomAddress,Uint16 number, Uint16  *RamAddr);


/**
 *  @brief                 IIC��Ĵ�����ĳһλд����
 *  @parameter              SlaveAddress���ӻ���ַ��  regaddress���Ĵ�����ַ�� bitNum��ĳһλ��  data��д������
 *  @return_value           ��
 */
void IICwriteBit(Uint16 slaveaddress, Uint16 regaddress, Uint8 bitNum, Uint8 data);

/**
 *  @brief                 IIC��Ĵ�����ĳ��λд����
 *  @parameter              SlaveAddress���ӻ���ַ��  regaddress���Ĵ�����ַ�� bitStart����ʼλ��  length�����ȣ�data��д������
 *  @return_value           ��
 */
void IICwriteBits(Uint16 slaveaddress,Uint16 regaddress,Uint8 bitStart,Uint8 length,Uint8 data);


#endif /* HARDWARE_INCLUDE_IIC_H_ */
