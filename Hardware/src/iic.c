/*
 * iic.c
 *
 *  Created on: 2023��12��15��
 *      Author: ych
 */


#include<iic.h>

/**
 *  @brief              IICģ�鷢��׼��OK
 *  @parameter              ��
 *  @return_value           ��
 */
Uint16  I2C_xrdy()
{
    Uint16  t;
    t = I2caRegs.I2CSTR.bit.XRDY;   // IICģ�鷢��׼��OK
    return t;
}



/**
 *  @brief              IICģ�����׼��OK
 *  @parameter              ��
 *  @return_value           ��
 */
Uint16  I2C_rrdy()
{
    Uint16  t;
    t = I2caRegs.I2CSTR.bit.RRDY;   //  IICģ�����׼��OK
    return t;
}


/**
 *  @brief                  IICд����
 *  @parameter              SlaveAddress���ӻ���ַ��  RomAddress���Ĵ�����ַ�� number��д�����ݵ��ֽ�����  *Wdata��д�����ݵĵ�ַ
 *  @return_value           ״̬��־
 */
Uint16 WriteData( Uint16 SlaveAddress, Uint16 RomAddress,Uint16 number, Uint8 *Wdata)
{
   Uint16 i;
   if (I2caRegs.I2CSTR.bit.BB == 1)
   {
      return I2C_BUS_BUSY_ERROR;   //��������æ����״̬
   }
   while(!I2C_xrdy());      //�ȴ����ݷ��;�����XRDY=1,�������ͼĴ����Ѿ�׼���ý����µ�����
   I2caRegs.I2CSAR = SlaveAddress&0xff;    //�豸�ӵ�ַ
   I2caRegs.I2CCNT = number + 1;   //��Ҫ���͵��ֽ���
   I2caRegs.I2CDXR = RomAddress&0xff;    //��һ�������ֽ�Ϊ�������ݵ�Ŀ��Ĵ�����ַ
   DELAY_US(1);//�ȴ�������ȫ��ֵ��I2CDXR����ʹ��IIC������Ҫ���ϣ�
   I2caRegs.I2CMDR.all = 0x6E20;    //������ʼ�źţ��ڲ����ݼ���������0ʱ������ֹͣ�źţ���������ģʽ��ʹ��IICģʽ��
   for (i=0; i<number; i++)
   {
      while(!I2C_xrdy());   //�ȴ����ݷ��;�����������һ������
      I2caRegs.I2CDXR = *Wdata&0xFF;
      Wdata++;
      if (I2caRegs.I2CSTR.bit.NACK == 1)    //�͵���Ӧ���źŷ��ش���
          return    I2C_BUS_BUSY_ERROR;
   }
   return I2C_SUCCESS;         //���ͳɹ�
}

void IIC_Ack() {
    // ���Ӧ��λ
    I2caRegs.I2CMDR.bit.NACKMOD = 0;
}

void IIC_NoAck() {
    I2caRegs.I2CMDR.bit.NACKMOD = 1;
}



/**
 *  @brief                  IICд����
 *  @parameter              SlaveAddress���ӻ���ַ��  RomAddress���Ĵ�����ַ�� number��д�����ݵ��ֽ�����  *RamAddr���������ݴ�ŵĵ�ַ
 *  @return_value           ״̬��־
 */
Uint16 ReadData( Uint16 SlaveAddress, Uint16 RomAddress,Uint16 number, Uint16  *RamAddr)
{
   Uint16  i,Temp;

   if (I2caRegs.I2CSTR.bit.BB == 1)  //��������æ����״̬
   {
       return I2C_BUS_BUSY_ERROR;
   }
   while(!I2C_xrdy());
   I2caRegs.I2CSAR = SlaveAddress&0xff;      //�豸�ӵ�ַ
   I2caRegs.I2CCNT = 1;        //����һ���ֽ�ΪҪ��ȡ���ݵļĴ�����ַ
   I2caRegs.I2CDXR = RomAddress&0xff;
   DELAY_US(1);//�ȴ�������ȫ��ֵ��I2CDXR����ʹ��IIC������Ҫ���ϣ�
   I2caRegs.I2CMDR.all = 0x6620;   //��������ģʽ���Զ����ֹͣλ������ֹͣ�ź�
   if (I2caRegs.I2CSTR.bit.NACK == 1)    //�͵���Ӧ���źŷ��ش���
        return  I2C_BUS_BUSY_ERROR;
   DELAY_US(50);
   while(!I2C_xrdy());                  //���Թ�������ʱ�Ῠ����һ��,��ʾͨѶ������
   I2caRegs.I2CSAR = SlaveAddress&0xff;
   I2caRegs.I2CCNT = number;
   DELAY_US(10);//�ȴ�������ȫ��ֵ��I2CDXR����ʹ��IIC������Ҫ���ϣ�
   I2caRegs.I2CMDR.all = 0x6C20;   //��������ģʽ��������ֹͣ�ź�
   if (I2caRegs.I2CSTR.bit.NACK == 1)
        return  I2C_BUS_BUSY_ERROR;
   for(i=0;i<number;i++)
   {
         //while(!I2C_rrdy());
      Temp = I2caRegs.I2CDRR;
      if(i==number-1){
              IIC_NoAck();
              *RamAddr = Temp;
              RamAddr++;
              return   I2C_SUCCESS;

      }
              IIC_Ack();
//      if (I2caRegs.I2CSTR.bit.NACK == 1)
//          return    I2C_BUS_BUSY_ERROR;
      *RamAddr = Temp;
      RamAddr++;
   }
   return I2C_SUCCESS;    //�������ݳɹ�
}



/**
 *  @brief                 IIC��Ĵ�����ĳһλд����
 *  @parameter              SlaveAddress���ӻ���ַ��  regaddress���Ĵ�����ַ�� bitNum��ĳһλ��  data��д������
 *  @return_value           ��
 */
void IICwriteBit(Uint16 slaveaddress, Uint16 regaddress, Uint8 bitNum, Uint8 data)
{
    Uint16 a;
    Uint8 b;
    DELAY_US(50);
    ReadData(slaveaddress,regaddress,1,&a);
    b=(Uint8 )(a&0xff);
    b = (data != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));
    DELAY_US(50);
    WriteData(slaveaddress,regaddress,1,&b);
}



/**
 *  @brief                 IIC��Ĵ�����ĳ��λд����
 *  @parameter              SlaveAddress���ӻ���ַ��  regaddress���Ĵ�����ַ�� bitStart����ʼλ��  length�����ȣ�data��д������
 *  @return_value           ��
 */
void IICwriteBits(Uint16 slaveaddress,Uint16 regaddress,Uint8 bitStart,Uint8 length,Uint8 data)
{

    Uint8 b,mask;
    Uint16 a;
    DELAY_US(50);
    ReadData(slaveaddress,regaddress,1,&a);
    b=(Uint8 )(a&0xff);
    mask = (0xFF << (bitStart + 1)) | 0xFF >> ((8 - bitStart) + length - 1);
    data <<= (8 - length);
    data >>= (7 - bitStart);
    b &= mask;
    b |= data;
    DELAY_US(50);
    WriteData(slaveaddress,regaddress,1, &b);
}


