///*
// * AT24C01.c
// *
// *  Created on: 2023��12��13��
// *      Author: ych
// */
//
#include <AT24C01.h>
#include<DSP2833x_I2c.h>

#define READ_CMD                1
#define WRITE_CMD               0

#define x24C02//�������ƣ�x24C01��x24C02

#define DEV_ADDR                0xA0                    //�豸Ӳ����ַ

#ifdef x24C01
    #define PAGE_NUM            16                      //ҳ��
    #define PAGE_SIZE           8                       //ҳ���С(�ֽ�)
    #define CAPACITY_SIZE       (PAGE_NUM * PAGE_SIZE)  //������(�ֽ�)
    #define ADDR_BYTE_NUM       1                       //��ַ�ֽڸ���
#endif

#ifdef x24C02
    #define PAGE_NUM            32                      //ҳ��
    #define PAGE_SIZE           8                       //ҳ���С(�ֽ�)
    #define CAPACITY_SIZE       (PAGE_NUM * PAGE_SIZE)  //������(�ֽ�)
    #define ADDR_BYTE_NUM       1                       //��ַ�ֽڸ���
#endif


extern __interrupt void i2c_int1a_isr(void);


/*
void IIC_Start(){

    // ����I2C������Ϊ��ģʽ��������ʼ����
    I2caRegs.I2CMDR.bit.STT = 1;

    // �ȴ��������

    while ((I2caRegs.I2CSTR.bit.BB) != 0);
}


// ����豸д��һ���ֽ�����
void IIC_WriteByte(Uint32 data) {
    // ����Ҫ���͵������ֽ�
    I2caRegs.I2CDXR = data;

    // �ȴ����ݷ������
    while ((I2caRegs.I2CSTR.bit.XRDY) == 0);
}

// �ȴ����豸��Ӧ���ź�
Uint16 IIC_WaitAck() {
    // �ȴ�Ӧ���ź�

    while ((I2caRegs.I2CSTR.bit.ARDY) == 0);

    // ���Ӧ��λ
    if (I2caRegs.I2CSTR.bit.NACK) {
        // Ӧ�����
        return I2C_ERROR;
    } else {
        // Ӧ��ɹ�
        return I2C_SUCCESS;
    }
}

// �Ӵ��豸��ȡһ���ֽ�����
Uint32 IIC_ReadByte() {
    // ����I2C������Ϊ����ģʽ
    I2caRegs.I2CMDR.bit.MST = 1; //��ģʽλ
    I2caRegs.I2CMDR.bit.TRX = 1;


    // �ȴ����ݽ������
    while ((I2caRegs.I2CSTR.bit.RRDY) == 0);

    // ��ȡ���յ��������ֽ�
    Uint32 data = I2caRegs.I2CDRR;

    return data;
}

// ������Ӧ���ź�
void IIC_NoAck() {
    // ���Ӧ��λ
    I2caRegs.I2CMDR.bit.NACKMOD = 1;

}

// ����Ӧ���ź�
void IIC_Ack() {
    // ���Ӧ��λ
    I2caRegs.I2CMDR.bit.NACKMOD = 0;
}


// ����ֹͣ����
void IIC_Stop() {
    // ����I2C����������ֹͣ����
    I2caRegs.I2CMDR.bit.STP = 1;

    // �ȴ�ֹͣ�����������
    while ((I2caRegs.I2CMDR.bit.STP) == 1);
}
*/

/*******************************************************************************
  * ��������x24C01_ReadByte
  * ��  �ܣ���һ���ֽ�
  * ��  ����u16AddrҪ��ȡ�ĵ�ַ
  * ����ֵ��u8Data����������
  * ˵  ������
*******************************************************************************/
/*
Uint16 x24Cxx_ReadByte(Uint16 u16Addr)
{
    Uint16 u8Data = 0;
    IIC_Start();//��ʼ�ź�
    IIC_WriteByte(DEV_ADDR | WRITE_CMD);//����Ѱַ+д
    IIC_WaitAck();//�ȴ�Ӧ��
    IIC_WriteByte((Uint16)(u16Addr & 0xFF));//ֻȡ��ַ�ĵ��ֽ�
    IIC_WaitAck();//�ȴ�Ӧ��
    IIC_Start();//��ʼ�ź�
    IIC_WriteByte(DEV_ADDR | READ_CMD);//����Ѱַ+��
    IIC_WaitAck();//�ȴ�Ӧ��
    u8Data = IIC_ReadByte();
    IIC_NoAck();
    IIC_Stop();
    return u8Data;
}
*/


/**
 *  @brief              AT24C01�ĳ�ʼ��
 *  @parameter              ��
 *  @return_value           ��
 */
void At24c01_Init(){

    EALLOW;
    GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;    // ʹ��(SDAA)����
    GpioCtrlRegs.GPBPUD.bit.GPIO33 = 0;    //  ʹ�� (SCLA)����
    GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = 3;  // ͬ�� (SDAA)
    GpioCtrlRegs.GPBQSEL1.bit.GPIO33 = 3;  // ͬ�� (SCLA)
    GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 1;   // ���� GPIO32Ϊ SDAA
    GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 1;   // ����GPIO33 ΪSCLA
    EDIS;

    // Initialize I2C
    I2caRegs.I2CSAR = 0x00A0;        // Slave address - EEPROM control code

    #if (CPU_FRQ_150MHZ)             // Default - For 150MHz SYSCLKOUT
         I2caRegs.I2CPSC.all = 14;   // Prescaler - need 7-12 Mhz on module clk (150/15 = 10MHz)
    #endif
    #if (CPU_FRQ_100MHZ)             // For 100 MHz SYSCLKOUT
      I2caRegs.I2CPSC.all = 9;       // Prescaler - need 7-12 Mhz on module clk (100/10 = 10MHz)
    #endif
    //Master Clock(SCL) = 10MHz / (10 + 5) + (5 + 5) = 400KHz
    I2caRegs.I2CCLKL = 10;           // NOTE: must be non zero
    I2caRegs.I2CCLKH = 5;            // NOTE: must be non zero
                                     // Enable ASS & SCD & ARDY & RRDY interrupts
    I2caRegs.I2CIER.all = 0x6E;      // Enable ASS & SCD & XRDY & ARDY & RRDY & NACK interrupts

    I2caRegs.I2CMDR.all = 0x0020;    // Take I2C out of reset
                                     // Stop I2C when suspended

    I2caRegs.I2CFFTX.all = 0x6000;   // Enable FIFO mode and TXFIFO
    I2caRegs.I2CFFRX.all = 0x2040;   // Enable RXFIFO, clear RXFFINT,

     // Interrupts that are used in this example are re-mapped to
     // ISR functions found within this file.
    EALLOW;  // This is needed to write to EALLOW protected registers
   // PieVectTable.I2CINT1A = &i2c_int1a_isr;
    EDIS;   // This is needed to disable write to EALLOW protected registers

     // Enable I2C interrupt 1 in the PIE: Group 8 interrupt 1
    PieCtrlRegs.PIEIER8.bit.INTx1 = 1;

     // Enable CPU INT8 which is connected to PIE group 8
    IER |= M_INT8;

}






