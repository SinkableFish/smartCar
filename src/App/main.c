#include "include.h" // Include.h �����û��Զ����ͷ�ļ�

/***********************��������***************************/
extern uint8 TIME0flag_5ms   ;
extern uint8 TIME0flag_10ms  ;
extern uint8 TIME0flag_15ms  ;
extern uint8 TIME0flag_20ms  ;
extern uint8 TIME0flag_50ms  ;
extern uint8 TIME0flag_80ms  ;
extern uint8 TIME0flag_100ms ;
extern uint8 TIME0flag_1s ;
int i=0,j=0;
extern uint8  DMA_Over_Flg;   //�ɼ���ɱ�־λ
#define  LIN_COUT 100

/***********************��������***************************/



/************************������****************************/





void main(void)
{
  DisableInterrupts; //��ֹ���ж�
  motoInit();   //�����ʼ��
  OLED_Init();  //��Ļ��ʼ��
  counterInit();//��������ʼ��
  initKey();    //���̳�ʼ��
  initSolution();//���뿪�س�ʼ��
  getSolution();//��ȡ���뿪����ֵ
  CCD_INC ();   //ͼ���С��ʼ��
  set_irq_priority((INT_DMA0+INC_IRQ),0);//�����ж����ȼ� 0
  setIRQadrr(INT_DMA0,DMA_CH0_Handler);  //�����жϵ�ַ����
  initPID();    //PID��ʼ��
  uart_init (UART0, 115200);
  LPTMR0_CMR = 60000; //��������λֵ��ʼ��
  for(i = 0;i < DataLine;i++) //ADdata[i][j] ��ʼ����ֵ..
   {
     for(j = 0;j < DataRow;j++)
     {
       OriginData[i][j] = 0;     
     }
   }
  delay_ms(2000);            //��ʱ2s
  EnableInterrupts ;
  while(1)
  {
    //TPM_PWM_Duty(TPM2,CH0,10);
    //TPM_PWM_Duty(TPM2,CH1,0);
    if(DMA_Over_Flg == 1)    //���ɼ���ɱ�־λ
    {
      DMA_Over_Flg = 0;       
      gpio_Interrupt_init(PTA17,GPI_UP,0);//�رճ��ж�
      gpio_Interrupt_init(PTA13,GPI_UP,0);//�ر����ж� 
      //uart_putchar(UART0,0xff);
      //if(OTSU_flag == 0)                              //OTSU����㷨��ע���޸�����
      //{
        //OTSU();
        OTSU_flag = 1;
      //}
      findRoute();            //Ѱ��·��
      getSolution();          //ȡ�ò��뿪�ص���ֵ����ý������
      if(TIME0flag_5ms == 1)  //5ms�жϽ���
      {
        TIME0flag_5ms = 0;
        SpeedControl();       //�ٶȿ���
      }
      menuDisplay();          //��ʾ�˵�
      OutData[0] = stopFlag;  //���ߴ��ڱ༭
      OutPut_Data();          //��������

       // for(i=0;i<(DataLine - 1);i++)
       //{
       // for(j=0;j<DataRow;j++)
       //  {
       //    if(OriginData[i][j]==0xff) OriginData[i][j] = 0xfe;
       //    uart_putchar(UART0,OriginData[i][j]);
       //  }
       // }
      

      gpio_Interrupt_init(PTA17, GPI_UP,FALLING); //�򿪳��ж�
     }
    if(TIME0flag_100ms == 1) //PTB1 LED��˸����֤�����Ƿ���������
    {
      TIME0flag_100ms = 0;
      PTB0_OUT = ~PTB0_OUT;
    }
  }
}