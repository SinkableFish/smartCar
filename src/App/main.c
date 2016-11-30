#include "include.h" // Include.h 包含用户自定义的头文件

/***********************参数定义***************************/
extern uint8 TIME0flag_5ms   ;
extern uint8 TIME0flag_10ms  ;
extern uint8 TIME0flag_15ms  ;
extern uint8 TIME0flag_20ms  ;
extern uint8 TIME0flag_50ms  ;
extern uint8 TIME0flag_80ms  ;
extern uint8 TIME0flag_100ms ;
extern uint8 TIME0flag_1s ;
int i=0,j=0;
extern uint8  DMA_Over_Flg;   //采集完成标志位
#define  LIN_COUT 100

/***********************参数定义***************************/



/************************主函数****************************/





void main(void)
{
  DisableInterrupts; //禁止总中断
  motoInit();   //电机初始化
  OLED_Init();  //屏幕初始化
  counterInit();//编码器初始化
  initKey();    //键盘初始化
  initSolution();//拨码开关初始化
  getSolution();//获取拨码开关数值
  CCD_INC ();   //图像大小初始化
  set_irq_priority((INT_DMA0+INC_IRQ),0);//设置中断优先级 0
  setIRQadrr(INT_DMA0,DMA_CH0_Handler);  //设置中断地址函数
  initPID();    //PID初始化
  uart_init (UART0, 115200);
  LPTMR0_CMR = 60000; //编码器复位值初始化
  for(i = 0;i < DataLine;i++) //ADdata[i][j] 初始化赋值..
   {
     for(j = 0;j < DataRow;j++)
     {
       OriginData[i][j] = 0;     
     }
   }
  delay_ms(2000);            //延时2s
  EnableInterrupts ;
  while(1)
  {
    //TPM_PWM_Duty(TPM2,CH0,10);
    //TPM_PWM_Duty(TPM2,CH1,0);
    if(DMA_Over_Flg == 1)    //场采集完成标志位
    {
      DMA_Over_Flg = 0;       
      gpio_Interrupt_init(PTA17,GPI_UP,0);//关闭场中断
      gpio_Interrupt_init(PTA13,GPI_UP,0);//关闭行中断 
      //uart_putchar(UART0,0xff);
      //if(OTSU_flag == 0)                              //OTSU大津算法，注意修改起跑
      //{
        //OTSU();
        OTSU_flag = 1;
      //}
      findRoute();            //寻找路径
      getSolution();          //取得拨码开关的数值，获得解决方案
      if(TIME0flag_5ms == 1)  //5ms中断进入
      {
        TIME0flag_5ms = 0;
        SpeedControl();       //速度控制
      }
      menuDisplay();          //显示菜单
      OutData[0] = stopFlag;  //无线串口编辑
      OutPut_Data();          //发动数据

       // for(i=0;i<(DataLine - 1);i++)
       //{
       // for(j=0;j<DataRow;j++)
       //  {
       //    if(OriginData[i][j]==0xff) OriginData[i][j] = 0xfe;
       //    uart_putchar(UART0,OriginData[i][j]);
       //  }
       // }
      

      gpio_Interrupt_init(PTA17, GPI_UP,FALLING); //打开场中断
     }
    if(TIME0flag_100ms == 1) //PTB1 LED闪烁，验证程序是否正常运行
    {
      TIME0flag_100ms = 0;
      PTB0_OUT = ~PTB0_OUT;
    }
  }
}