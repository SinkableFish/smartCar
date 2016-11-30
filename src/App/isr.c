/***********************************************************
 * 文件名       ：isr.c
 * 说明         ：中断功能模块
 * 作者         ：landzo 蓝电子
 * 淘宝店       ：http://landzo.taobao.com/
 * 公司网站     ：http://www.landzo.com/
 *论坛          ：http://www.landzo.cn
 * 库版本       ：V1.0
 *时间          ：15.5.26
************************************************************/

//#include "isr.h"
#include  "include.h"

uint8 TIME0flag_5ms   ;
uint8 TIME0flag_10ms  ;
uint8 TIME0flag_15ms  ;
uint8 TIME0flag_20ms  ;
uint8 TIME0flag_50ms  ;
uint8 TIME0flag_80ms  ;
uint8 TIME0flag_100ms ;
uint8 TIME0flag_1s;
uint8 TIME1flag_20ms  ;
uint8  TimeCount = 0 ;

/*************************************************************************
*                             蓝宙电子工作室
*
*  函数名称：setIRQadrr
*  功能说明：设置中断地址函数
*  参数说明：IRQInterruptIndex 中断向量表，在芯片的.H文件，比如K60 在"MK60DZ10.h"
*            void IRQAdrr(void)  中断函数
*  函数返回：无
*  修改时间：2015-5-15    已测试
*  备    注：
*************************************************************************/

__RAMFUN void setIRQadrr(IRQInterruptIndex IRQnum,void IRQAdrr(void) ){
  extern uint32 __VECTOR_TABLE[];
  extern uint32 __VECTOR_RAM[];
  vuint32  *Vector_TABl ,Vector_TAB;
  vuint16 temp0 ,temp1;
  vuint32 buf[128];
  Vector_TAB = SCB_VTOR ;
  Vector_TABl = (vuint32  *)Vector_TAB ;
  /**************
  中断向量表在ram区域，可以进行直接擦除
  **************/
  if(Vector_TAB == (uint32)&__VECTOR_RAM){   // 0xE000E000u
    Vector_TABl[IRQnum] = (uint32)(IRQAdrr) ;
   }
  else{
    /*****************************
    向量表在flash中
    *****************************/
    for(temp0 = 0 ; temp0 < 128 ; temp0++){
      buf[temp0] = Vector_TABl[temp0] ;
    }
    buf[IRQnum]  = (uint32)(IRQAdrr) ;  
    hw_flash_init() ;
    flash_erase_sector(0) ;
    flash_write(0,0,1024,(uint8 *)buf) ;
  }
 }



/*************************************************************************
*                             蓝宙电子工作室
*
*  函数名称：USART0_IRQHandler
*  功能说明：串口0 中断 接收 服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2014-8-28    已测试
*  备    注：
*************************************************************************/


void UART0_IRQHandler(void)
{
  uint8 ch;
  DisableInterrupts;		    //关总中断
  //接收一个字节数据并回发
  ch = uart_getchar (UART0);      //接收到一个数据
//  uart_sendStr  (UART0, "\n你发送的数据为：");
  uart_putchar (UART0, ch);       //就发送出去
  
  EnableInterrupts;		    //开总中断
}
/*************************************************************************
*                             蓝宙电子工作室
*
*  函数名称：USART1_IRQHandler
*  功能说明：串口1 中断 接收 服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-14    已测试
*  备    注：
*************************************************************************/


void USART1_IRQHandler(void)
{
/*  uint8 ch;
  
  DisableInterrupts;		    //关总中断
  
  //接收一个字节数据并回发
  ch = uart_getchar (UART1);      //接收到一个数据
  uart_sendStr  (UART1, "\n你发送的数据为：");
  uart_putchar (UART1, ch);       //就发送出去
  
  EnableInterrupts;		    //开总中断 */
}

/*************************************************************************
*                             蓝宙电子工作室
*
*  函数名称：PIT0_IRQHandler
*  功能说明：PIT0 定时中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-18    已测试
*  备    注：
*************************************************************************/



void PIT_IRQHandler(void)
{
  PIT_Flag_Clear(PIT0);       //清中断标志位
  
  TimeCount ++ ;
  
  if(TimeCount%1 == 0 )
  {
    TIME0flag_5ms = 1;
  } 
  if(TimeCount%2 == 0 )
  {
    TIME0flag_10ms = 1;    
  } 
  if(TimeCount%3 == 0 )
  {
    TIME0flag_15ms = 1;    
  }     
  if(TimeCount%4 == 0 )
  {
    TIME0flag_20ms = 1;
  }
  if(TimeCount%10 == 0 )
  {
    TIME0flag_50ms = 1;
  }
  if(TimeCount%16 == 0 )
  {
    TIME0flag_80ms = 1;
  }  
  if(TimeCount%20 == 0 )
  {
    TIME0flag_100ms = 1;
  }  
  if(TimeCount%200 == 0 )
  {
    TIME0flag_1s = 1;
    TimeCount = 0 ;
  }
  if(TIME0flag_20ms == 1)
      {
        TIME0flag_20ms = 0;
        findType();
        findCurvature();
        setCenter();
        setDuty();
      }
  if(TIME0flag_10ms == 1)
  {
    if(OTSU_flag == 1)
    {
    //judgeStartLine(18);
    judgeStartLine(19);//起跑线检测
    judgeStartLine(20);
    judgeStartLine(21);
    judgeStartLine(22);
    judgeStartLine(23);
    judgeStartLine(24);
    judgeStartLine(25);
    judgeStartLine(26);
    judgeStartLine(27);
    judgeStartLine(28);
    judgeStartLine(29);
    judgeStartLine(30);
    judgeStartLine(31);
    judgeStartLine(32);
    judgeStartLine(33);
    judgeStartLine(34);
    judgeStartLine(35);
    judgeStartLine(36);
    judgeStartLine(37);
    judgeStartLine(38);
    judgeStartLine(39);
    judgeStartLine(40);
    judgeStartLine(41);
    judgeStartLine(42);    
    judgeStartLine(43);
    }
    TIME0flag_10ms = 0;
  }
  /*if(TIME0flag_5ms == 1)
  {
    TIME0flag_5ms = 0;
    OutData[0] = speed;
    OutPut_Data(); 
  }*/
  
        //Servo_motor_SD5_test();
}
 // if(TIME0flag_50ms == 1)
  //{
   // TIME0flag_50ms == 0;
    //err = (ServoPID.err - ServoPID.err1);
  //}

/*************************************************************************
*                             蓝宙电子工作室
*
*  函数名称：HardFault_Handler
*  功能说明：硬件上访中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-4    已测试
*  备    注：可以用LED闪烁来指示发生了硬件上访
*************************************************************************/
void HardFault_Handler(void)
{
  while (1)
  {
    //printf("\n****硬件上访错误!!!*****\r\n\n");
  }
}

/*************************************************************************
*                             蓝宙电子工作室
*
*  函数名称：PORTD_IRQHandler
*  功能说明：PORTD端口中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-1-25    已测试
*  备    注：引脚号需要自己初始化来清除
*************************************************************************/

void dlay(void){
  volatile uint16_t  dlaycount ;
   
  for(dlaycount = 0 ; dlaycount < 62 ; dlaycount ++){
  }
}
  
/**************************摄像头采用变量***************************/
uint8  DMA_Over_Flg = 0;     //场采集完成标志位
uint16 LinCout;
uint8 LinADCout =0;
uint8 Sample_Flag=0;
extern uint8  OriginData[DataLine][DataRow];

void PORTA_IRQHandler()
{
  if(PORTA_ISFR & 0x2000)         //PTA13触发中断 采集的行中断
  {
    PORTA_ISFR  |= 0x2000;        //写1清中断标志位  
   if((LinCout%(480/DataLine)==0)&&(LinADCout<DataLine))
    {  
      dlay();  //摄像头行中断改为下降沿触发，有效点前面有一段行消隐区，故需要一段延时消除消耗掉，该处的时间，程序里面的需要根据单片机的主频调整。
      DMA_SAR(DMA_CH0) = (uint32_t)(&PTD_BYTE0_INT) ;
      DMA_IRQ_CLEAN(DMA_CH0); //清除通道传输中断标志位(这样才能再次进入中断)
      DMA_DAR(DMA_CH0) = (uint32_t)OriginData[LinADCout];   //数据存储地址变化
      DMA_DSR_BCR(DMA_CH0) =( 0 | DMA_DSR_BCR_BCR(DataRow)); //传输数目  
      DMA_DCR(DMA_CH0) |= DMA_DCR_ERQ_MASK;  
      DMA_EN(DMA_CH0);                                    //使能通道CHn 硬件请求      (这样才能继续触发DMA传输) 
      DMA_IRQ_EN(DMA_CH0);                             //允许DMA通道传输
      LinADCout++;
    }
   
   if(OTSU_flag == 1)
   {
   if((LinCout%(480/DataLine) == 1)&&(LinADCout < DataLine))     //二值化
   {
    	int i;
    	int tempDataLine = LinCout/4;
    	for(i=0; i<DataRow; i++)
    	{
    		if(OriginData[tempDataLine][i] < threshold)
    		{
    			OriginData[tempDataLine][i] = 0;
    		}
    		else
    		{
    			OriginData[tempDataLine][i] = 1;
    		}
    	}
    }
   
   if((LinCout%(480/DataLine) == 2)&&(LinADCout < DataLine)) //去噪
   {
     int i;
     int tempDataLine = LinCout/4;
     for(i=1; i<(DataRow - 1); i++)
      {
        if(OriginData[tempDataLine][i] && !OriginData[tempDataLine][i-1] && !OriginData[tempDataLine][i+1] && !OriginData[tempDataLine-1][i] && !OriginData[tempDataLine+1][i] && !OriginData[tempDataLine+1][i+1] && !OriginData[tempDataLine+1][i-1] && !OriginData[tempDataLine-1][i+1] && !OriginData[tempDataLine-1][i-1])
          OriginData[tempDataLine][i] = 0;
        if(!OriginData[tempDataLine][i] && OriginData[tempDataLine][i-1] && OriginData[tempDataLine][i+1] && OriginData[tempDataLine-1][i] && OriginData[tempDataLine+1][i] && OriginData[tempDataLine+1][i+1] && OriginData[tempDataLine+1][i-1] && OriginData[tempDataLine-1][i+1] && OriginData[tempDataLine-1][i-1])
          OriginData[tempDataLine][i] =1;
      }
    }
  }
    

  LinCout ++;
  if(LinADCout == DataLine)
  {
    LinADCout = 0;
    DMA_Over_Flg = 1;
  }
  } 

 
  if(PORTA_ISFR & 0x20000)         //PTA17触发中断 采集的场中断
  {
    PORTA_ISFR  |= 0x20000;        //写1清中断标志位    
    LinCout = 0 ;
    LinADCout=0;
    gpio_Interrupt_init(PTA13, GPI_UP, FALLING);   //开启行中断  
    PORTA_ISFR  |= 0x2000;        //写1清中断标志位 
  }

}

/*************************************************************************
*                             蓝宙电子工作室
*
*  函数名称：PORTD_IRQHandler
*  功能说明：PORTD端口中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-1-25    已测试
*  备    注：引脚号需要根据自己初始化来修改
*************************************************************************/
void PORTD_IRQHandler(void)
{
  uint8_t  n = 0;    //引脚号
  n=5;
  if(PORTD_ISFR & (1 << n))         //PTD5触发中断
  {
    PORTD_ISFR  |= (1 << n);        //写1清中断标志位
  
  }
}

/*************************************************************************
*                             蓝宙电子工作室
*
*  函数名称：FTM0_IRQHandler
*  功能说明：FTM0输入捕捉中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-25
*  备    注：引脚号需要根据自己初始化来修改，参考现有的代码添加自己的功能
*************************************************************************/
void FTM0_IRQHandler()
{
  
  
}

/*************************************************************************
*                             蓝宙电子工作室
*
*  函数名称：FTM1_IRQHandler
*  功能说明：FTM1输入捕捉中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-25
*  备    注：引脚号需要根据自己初始化来修改，参考现有的代码添加自己的功能
*************************************************************************/
//static int32 CNT = 0; // (base)->STATUS
void FTM1_IRQHandler()
{
  uint8_t s = TPM_STATUS_REG(TPMx[TPM1]);             //读取捕捉和比较状态  All CHnF bits can be checked using only one read of STATUS.
  uint8_t n;
  TPM_STATUS_REG(TPMx[TPM1]) = 0x00;               //清中断标志位
 
  n = 1;
  if( s & (1 << n))
  {
   // TPM_CnSC_REG(TPM1_BASE_PTR, n) &= ~TPM_CnSC_CHIE_MASK; // 禁止输入捕捉中断
    //     用户任务       //    
    //不建议在这里开启输入捕捉中断
   // TPM_CnSC_REG(TPM1_BASE_PTR,n) |= TPM_CnSC_CHIE_MASK;   // 开启输入捕捉中断
  }
}


/*************************************************************************
*                             蓝宙电子工作室
*
*  函数名称：DMA_CH0_Handler
*  功能说明：DMA通道0的中断服务函数
*  参数说明：是采集摄像头数据，本数据位摄像头AD数据，可以采集到300个点。
设置标志位能够及时搬移。
*  函数返回：无
*  修改时间：2012-3-18    已测试
*  备    注：
*************************************************************************/
void DMA_CH0_Handler(void)
{
  DMA_IRQ_CLEAN(DMA_CH0) ;
  DMA_IRQ_DIS(DMA_CH0);
  DMA_DIS(DMA_CH0); 
}

/*************************************************************************
*                             蓝宙电子工作室
*
*  函数名称：DMA_CH3_Handler
*  功能说明：DMA通道3的中断服务函数
*  参数说明：是采集摄像头数据，本数据位摄像头AD数据，可以采集到300个点。
设置标志位能够及时搬移。
*  函数返回：无
*  修改时间：2012-3-18    已测试
*  备    注：
*************************************************************************/
void DMA_CH3_Handler(void)
{
//  printf("DMA_CH0_Handler\n");
/*  DMA_IRQ_CLEAN(DMA_CH0);                             //清除通道传输中断标志位    (这样才能再次进入中断)
  DMA_EN(DMA_CH0);  */                                  //使能通道CHn 硬件请求      (这样才能继续触发DMA传输)
}



volatile uint8_t LPT_INT_count = 0;
void  LPT_Handler(void)
{
  LPTMR0_CSR |= LPTMR_CSR_TCF_MASK;   //清除LPTMR比较标志
  LPT_INT_count++;                    //中断溢出加1
}