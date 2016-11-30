#include<include.h>
#include "KL2x_uart.h"

#define  LIN_COUT 100
 
unsigned short CRC_CHECK(unsigned char *Buf, unsigned char CRC_CNT)
{
    unsigned short CRC_Temp;
    unsigned char i,j;
    CRC_Temp = 0xffff;

    for (i=0;i<CRC_CNT; i++)
		{      
        CRC_Temp ^= Buf[i];//逐位异或  去取反
        for (j=0;j<8;j++) 
				{
            if (CRC_Temp & 0x01)//如果地位为1
                CRC_Temp = (CRC_Temp >>1 ) ^ 0xa001;
            else
                CRC_Temp = CRC_Temp >> 1;
        }
    }
// 		Buf[8] = CRC_Temp & 0x00ff;  //将第9个数据赋上CRC的低字节
//     Buf[9] = CRC_Temp >>8;//第10数据上是CRC的高字节
    return(CRC_Temp);
}

void OutPut_Data(void)
{
  int temp[4] = {0};
  unsigned int temp1[4] = {0};
  unsigned char databuf[10] = {0};
  unsigned char i;
  unsigned short CRC16 = 0;
  for(i=0;i<4;i++)
  {
    
    temp[i]  = (int)OutData[i];
    temp1[i] = (unsigned int)temp[i];
    
  }
   
  for(i=0;i<4;i++) 
  {
    databuf[i*2]   = (unsigned char)(temp1[i]%256);
    databuf[i*2+1] = (unsigned char)(temp1[i]/256);
  }
  
  CRC16 = CRC_CHECK(databuf,8);
  databuf[8] = CRC16%256;
  databuf[9] = CRC16/256;
  
  for(i=0;i<10;i++)
   uart_putchar(UART0,databuf[i]);
}


void initPID()
{
  if(solution == 0)
  {
    ServoPID.P = 85;
    ServoPID.D = 500;
    motoPID.P = 2000;
    motoPID.I = 50;
    motoPID.D = 0;
    motoDuty = 300;
    targetSpeed = motoDuty;
    secondTargetSpeed = motoDuty-30;
  }

  if(solution == 1)
  {
    ServoPID.P = 80;
    ServoPID.D = 500;
    motoPID.P = 2000;
    motoPID.I = 50;
    motoPID.D = 0;
    motoDuty = 270;
    targetSpeed = motoDuty;
    secondTargetSpeed = motoDuty;
  }
  if(solution == 100)
  {
    ServoPID.P = 80;
    ServoPID.D = 500;
    motoPID.P = 2000;
    motoPID.I = 50;
    motoPID.D = 0;
    motoDuty = 270;
    targetSpeed = motoDuty;
    secondTargetSpeed = motoDuty-20;
  }

  if(solution == 11)
  {
    ServoPID.P = 85;
    ServoPID.D = 500;
    motoPID.P = 2000;
    motoPID.I = 50;
    motoPID.D = 0;
    motoDuty = 250;
    targetSpeed = motoDuty;
    secondTargetSpeed = 250;
  }  
  if(solution == 111)
  {
    ServoPID.P = 85;
    ServoPID.D = 500;
    motoPID.P = 2000;
    motoPID.I = 50;
    motoPID.D = 0;
    motoDuty = 200;
    targetSpeed = motoDuty;
    secondTargetSpeed = motoDuty;
  }
    if(solution == 10)
  {
    ServoPID.P = 85;
    ServoPID.D = 500;
    motoPID.P = 2000;
    motoPID.I = 50;
    motoPID.D = 0;
    motoDuty = 280;
    targetSpeed = motoDuty;
    secondTargetSpeed = motoDuty;
  }
  if(solution == 110)
  {
    ServoPID.P = 90;
    ServoPID.D = 500;
    motoPID.P = 2000;
    motoPID.I = 50;
    motoPID.D = 0;
    motoDuty = 310;
    targetSpeed = motoDuty;
    secondTargetSpeed = motoDuty-30;
  }
  if(solution == 101)
  {
    ServoPID.P = 90;
    ServoPID.D = 500;
    motoPID.P = 2000;
    motoPID.I = 50;
    motoPID.D = 0;
    motoDuty = 320;
    targetSpeed = motoDuty;
    secondTargetSpeed = motoDuty-30;
  }
}

void initKey()
{
  uart_init (UART0, 115200);//串口初始化
  gpio_init (PTB0, GPO, 1);//LED GPIO引脚初始化配置 推挽输出 输出为高电平
  gpio_init (PTB2, GPO, 1);
  gpio_init (PTB1, GPI, 0);
  gpio_init (PTB8, GPI, 0);
  gpio_init (PTB9, GPI, 0);
  gpio_init (PTB17, GPI, 0);
  gpio_init (PTB18, GPI, 0);
  gpio_init (PTB19, GPI, 0);
  gpio_init (PTB20, GPI, 0);
  gpio_init (PTB21, GPI, 0);
  gpio_init (PTB22, GPI, 0);
  
}

void initSolution()
{
    gpio_init (PTA4, GPI, 0);
    gpio_init (PTA5, GPI, 0);
    gpio_init (PTA6, GPI, 0);
    gpio_init (PTA7, GPI, 0);
}

void counterInit()
{
    lptmr_counter_init(LPT0_ALT2, LIN_COUT, 2, LPT_Rising);//初始化脉冲计数器 PTC5输入捕获脚
    set_irq_priority((INT_LPTimer + INC_IRQ), 0);//设置中断优先级 0
    setIRQadrr(INT_LPTimer, LPT_Handler);  //设置中断地址函数
    lptmr_counter_clean();  //清空脉冲计数器计算值
}

void motoInit()
{
  Servo_motor_SD5_init();
  pit_init_ms(PIT0, 5); //初始化PIT0，定时时间为：5ms
  set_irq_priority((INT_PIT + INC_IRQ),2); //设置中断优先级 2
  setIRQadrr(INT_PIT,PIT_IRQHandler); //设置PIT0定时器中断地址函数 
  TPM_PWM_init(TPM2, CH0, 10000,0); //PTC1 电机占空比设置初始化 
  TPM_PWM_init(TPM2, CH1, 10000,0); //PTC2 电机占空比设置初始化
}