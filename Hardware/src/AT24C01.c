///*
// * AT24C01.c
// *
// *  Created on: 2023年12月13日
// *      Author: ych
// */
//
#include <AT24C01.h>
#include<DSP2833x_I2c.h>

#define READ_CMD                1
#define WRITE_CMD               0

#define x24C02//器件名称，x24C01或x24C02

#define DEV_ADDR                0xA0                    //设备硬件地址

#ifdef x24C01
    #define PAGE_NUM            16                      //页数
    #define PAGE_SIZE           8                       //页面大小(字节)
    #define CAPACITY_SIZE       (PAGE_NUM * PAGE_SIZE)  //总容量(字节)
    #define ADDR_BYTE_NUM       1                       //地址字节个数
#endif

#ifdef x24C02
    #define PAGE_NUM            32                      //页数
    #define PAGE_SIZE           8                       //页面大小(字节)
    #define CAPACITY_SIZE       (PAGE_NUM * PAGE_SIZE)  //总容量(字节)
    #define ADDR_BYTE_NUM       1                       //地址字节个数
#endif


extern __interrupt void i2c_int1a_isr(void);


/*
void IIC_Start(){

    // 设置I2C控制器为主模式，发送起始条件
    I2caRegs.I2CMDR.bit.STT = 1;

    // 等待传输完成

    while ((I2caRegs.I2CSTR.bit.BB) != 0);
}


// 向从设备写入一个字节数据
void IIC_WriteByte(Uint32 data) {
    // 设置要发送的数据字节
    I2caRegs.I2CDXR = data;

    // 等待数据发送完成
    while ((I2caRegs.I2CSTR.bit.XRDY) == 0);
}

// 等待从设备的应答信号
Uint16 IIC_WaitAck() {
    // 等待应答信号

    while ((I2caRegs.I2CSTR.bit.ARDY) == 0);

    // 检查应答位
    if (I2caRegs.I2CSTR.bit.NACK) {
        // 应答错误
        return I2C_ERROR;
    } else {
        // 应答成功
        return I2C_SUCCESS;
    }
}

// 从从设备读取一个字节数据
Uint32 IIC_ReadByte() {
    // 设置I2C控制器为接收模式
    I2caRegs.I2CMDR.bit.MST = 1; //主模式位
    I2caRegs.I2CMDR.bit.TRX = 1;


    // 等待数据接收完成
    while ((I2caRegs.I2CSTR.bit.RRDY) == 0);

    // 读取接收到的数据字节
    Uint32 data = I2caRegs.I2CDRR;

    return data;
}

// 不发送应答信号
void IIC_NoAck() {
    // 清除应答位
    I2caRegs.I2CMDR.bit.NACKMOD = 1;

}

// 发送应答信号
void IIC_Ack() {
    // 清除应答位
    I2caRegs.I2CMDR.bit.NACKMOD = 0;
}


// 发送停止条件
void IIC_Stop() {
    // 设置I2C控制器发送停止条件
    I2caRegs.I2CMDR.bit.STP = 1;

    // 等待停止条件发送完成
    while ((I2caRegs.I2CMDR.bit.STP) == 1);
}
*/

/*******************************************************************************
  * 函数名：x24C01_ReadByte
  * 功  能：读一个字节
  * 参  数：u16Addr要读取的地址
  * 返回值：u8Data读出的数据
  * 说  明：无
*******************************************************************************/
/*
Uint16 x24Cxx_ReadByte(Uint16 u16Addr)
{
    Uint16 u8Data = 0;
    IIC_Start();//起始信号
    IIC_WriteByte(DEV_ADDR | WRITE_CMD);//器件寻址+写
    IIC_WaitAck();//等待应答
    IIC_WriteByte((Uint16)(u16Addr & 0xFF));//只取地址的低字节
    IIC_WaitAck();//等待应答
    IIC_Start();//起始信号
    IIC_WriteByte(DEV_ADDR | READ_CMD);//器件寻址+读
    IIC_WaitAck();//等待应答
    u8Data = IIC_ReadByte();
    IIC_NoAck();
    IIC_Stop();
    return u8Data;
}
*/


/**
 *  @brief              AT24C01的初始化
 *  @parameter              无
 *  @return_value           无
 */
void At24c01_Init(){

    EALLOW;
    GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;    // 使能(SDAA)上拉
    GpioCtrlRegs.GPBPUD.bit.GPIO33 = 0;    //  使能 (SCLA)上拉
    GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = 3;  // 同步 (SDAA)
    GpioCtrlRegs.GPBQSEL1.bit.GPIO33 = 3;  // 同步 (SCLA)
    GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 1;   // 配置 GPIO32为 SDAA
    GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 1;   // 配置GPIO33 为SCLA
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






