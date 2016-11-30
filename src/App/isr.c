/***********************************************************
 * �ļ���       ��isr.c
 * ˵��         ���жϹ���ģ��
 * ����         ��landzo ������
 * �Ա���       ��http://landzo.taobao.com/
 * ��˾��վ     ��http://www.landzo.com/
 *��̳          ��http://www.landzo.cn
 * ��汾       ��V1.0
 *ʱ��          ��15.5.26
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
*                             ������ӹ�����
*
*  �������ƣ�setIRQadrr
*  ����˵���������жϵ�ַ����
*  ����˵����IRQInterruptIndex �ж���������оƬ��.H�ļ�������K60 ��"MK60DZ10.h"
*            void IRQAdrr(void)  �жϺ���
*  �������أ���
*  �޸�ʱ�䣺2015-5-15    �Ѳ���
*  ��    ע��
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
  �ж���������ram���򣬿��Խ���ֱ�Ӳ���
  **************/
  if(Vector_TAB == (uint32)&__VECTOR_RAM){   // 0xE000E000u
    Vector_TABl[IRQnum] = (uint32)(IRQAdrr) ;
   }
  else{
    /*****************************
    ��������flash��
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
*                             ������ӹ�����
*
*  �������ƣ�USART0_IRQHandler
*  ����˵��������0 �ж� ���� ������
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2014-8-28    �Ѳ���
*  ��    ע��
*************************************************************************/


void UART0_IRQHandler(void)
{
  uint8 ch;
  DisableInterrupts;		    //�����ж�
  //����һ���ֽ����ݲ��ط�
  ch = uart_getchar (UART0);      //���յ�һ������
//  uart_sendStr  (UART0, "\n�㷢�͵�����Ϊ��");
  uart_putchar (UART0, ch);       //�ͷ��ͳ�ȥ
  
  EnableInterrupts;		    //�����ж�
}
/*************************************************************************
*                             ������ӹ�����
*
*  �������ƣ�USART1_IRQHandler
*  ����˵��������1 �ж� ���� ������
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-2-14    �Ѳ���
*  ��    ע��
*************************************************************************/


void USART1_IRQHandler(void)
{
/*  uint8 ch;
  
  DisableInterrupts;		    //�����ж�
  
  //����һ���ֽ����ݲ��ط�
  ch = uart_getchar (UART1);      //���յ�һ������
  uart_sendStr  (UART1, "\n�㷢�͵�����Ϊ��");
  uart_putchar (UART1, ch);       //�ͷ��ͳ�ȥ
  
  EnableInterrupts;		    //�����ж� */
}

/*************************************************************************
*                             ������ӹ�����
*
*  �������ƣ�PIT0_IRQHandler
*  ����˵����PIT0 ��ʱ�жϷ�����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-2-18    �Ѳ���
*  ��    ע��
*************************************************************************/



void PIT_IRQHandler(void)
{
  PIT_Flag_Clear(PIT0);       //���жϱ�־λ
  
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
    judgeStartLine(19);//�����߼��
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
*                             ������ӹ�����
*
*  �������ƣ�HardFault_Handler
*  ����˵����Ӳ���Ϸ��жϷ�����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-2-4    �Ѳ���
*  ��    ע��������LED��˸��ָʾ������Ӳ���Ϸ�
*************************************************************************/
void HardFault_Handler(void)
{
  while (1)
  {
    //printf("\n****Ӳ���Ϸô���!!!*****\r\n\n");
  }
}

/*************************************************************************
*                             ������ӹ�����
*
*  �������ƣ�PORTD_IRQHandler
*  ����˵����PORTD�˿��жϷ�����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-1-25    �Ѳ���
*  ��    ע�����ź���Ҫ�Լ���ʼ�������
*************************************************************************/

void dlay(void){
  volatile uint16_t  dlaycount ;
   
  for(dlaycount = 0 ; dlaycount < 62 ; dlaycount ++){
  }
}
  
/**************************����ͷ���ñ���***************************/
uint8  DMA_Over_Flg = 0;     //���ɼ���ɱ�־λ
uint16 LinCout;
uint8 LinADCout =0;
uint8 Sample_Flag=0;
extern uint8  OriginData[DataLine][DataRow];

void PORTA_IRQHandler()
{
  if(PORTA_ISFR & 0x2000)         //PTA13�����ж� �ɼ������ж�
  {
    PORTA_ISFR  |= 0x2000;        //д1���жϱ�־λ  
   if((LinCout%(480/DataLine)==0)&&(LinADCout<DataLine))
    {  
      dlay();  //����ͷ���жϸ�Ϊ�½��ش�������Ч��ǰ����һ����������������Ҫһ����ʱ�������ĵ����ô���ʱ�䣬�����������Ҫ���ݵ�Ƭ������Ƶ������
      DMA_SAR(DMA_CH0) = (uint32_t)(&PTD_BYTE0_INT) ;
      DMA_IRQ_CLEAN(DMA_CH0); //���ͨ�������жϱ�־λ(���������ٴν����ж�)
      DMA_DAR(DMA_CH0) = (uint32_t)OriginData[LinADCout];   //���ݴ洢��ַ�仯
      DMA_DSR_BCR(DMA_CH0) =( 0 | DMA_DSR_BCR_BCR(DataRow)); //������Ŀ  
      DMA_DCR(DMA_CH0) |= DMA_DCR_ERQ_MASK;  
      DMA_EN(DMA_CH0);                                    //ʹ��ͨ��CHn Ӳ������      (�������ܼ�������DMA����) 
      DMA_IRQ_EN(DMA_CH0);                             //����DMAͨ������
      LinADCout++;
    }
   
   if(OTSU_flag == 1)
   {
   if((LinCout%(480/DataLine) == 1)&&(LinADCout < DataLine))     //��ֵ��
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
   
   if((LinCout%(480/DataLine) == 2)&&(LinADCout < DataLine)) //ȥ��
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

 
  if(PORTA_ISFR & 0x20000)         //PTA17�����ж� �ɼ��ĳ��ж�
  {
    PORTA_ISFR  |= 0x20000;        //д1���жϱ�־λ    
    LinCout = 0 ;
    LinADCout=0;
    gpio_Interrupt_init(PTA13, GPI_UP, FALLING);   //�������ж�  
    PORTA_ISFR  |= 0x2000;        //д1���жϱ�־λ 
  }

}

/*************************************************************************
*                             ������ӹ�����
*
*  �������ƣ�PORTD_IRQHandler
*  ����˵����PORTD�˿��жϷ�����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-1-25    �Ѳ���
*  ��    ע�����ź���Ҫ�����Լ���ʼ�����޸�
*************************************************************************/
void PORTD_IRQHandler(void)
{
  uint8_t  n = 0;    //���ź�
  n=5;
  if(PORTD_ISFR & (1 << n))         //PTD5�����ж�
  {
    PORTD_ISFR  |= (1 << n);        //д1���жϱ�־λ
  
  }
}

/*************************************************************************
*                             ������ӹ�����
*
*  �������ƣ�FTM0_IRQHandler
*  ����˵����FTM0���벶׽�жϷ�����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-2-25
*  ��    ע�����ź���Ҫ�����Լ���ʼ�����޸ģ��ο����еĴ�������Լ��Ĺ���
*************************************************************************/
void FTM0_IRQHandler()
{
  
  
}

/*************************************************************************
*                             ������ӹ�����
*
*  �������ƣ�FTM1_IRQHandler
*  ����˵����FTM1���벶׽�жϷ�����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-2-25
*  ��    ע�����ź���Ҫ�����Լ���ʼ�����޸ģ��ο����еĴ�������Լ��Ĺ���
*************************************************************************/
//static int32 CNT = 0; // (base)->STATUS
void FTM1_IRQHandler()
{
  uint8_t s = TPM_STATUS_REG(TPMx[TPM1]);             //��ȡ��׽�ͱȽ�״̬  All CHnF bits can be checked using only one read of STATUS.
  uint8_t n;
  TPM_STATUS_REG(TPMx[TPM1]) = 0x00;               //���жϱ�־λ
 
  n = 1;
  if( s & (1 << n))
  {
   // TPM_CnSC_REG(TPM1_BASE_PTR, n) &= ~TPM_CnSC_CHIE_MASK; // ��ֹ���벶׽�ж�
    //     �û�����       //    
    //�����������￪�����벶׽�ж�
   // TPM_CnSC_REG(TPM1_BASE_PTR,n) |= TPM_CnSC_CHIE_MASK;   // �������벶׽�ж�
  }
}


/*************************************************************************
*                             ������ӹ�����
*
*  �������ƣ�DMA_CH0_Handler
*  ����˵����DMAͨ��0���жϷ�����
*  ����˵�����ǲɼ�����ͷ���ݣ�������λ����ͷAD���ݣ����Բɼ���300���㡣
���ñ�־λ�ܹ���ʱ���ơ�
*  �������أ���
*  �޸�ʱ�䣺2012-3-18    �Ѳ���
*  ��    ע��
*************************************************************************/
void DMA_CH0_Handler(void)
{
  DMA_IRQ_CLEAN(DMA_CH0) ;
  DMA_IRQ_DIS(DMA_CH0);
  DMA_DIS(DMA_CH0); 
}

/*************************************************************************
*                             ������ӹ�����
*
*  �������ƣ�DMA_CH3_Handler
*  ����˵����DMAͨ��3���жϷ�����
*  ����˵�����ǲɼ�����ͷ���ݣ�������λ����ͷAD���ݣ����Բɼ���300���㡣
���ñ�־λ�ܹ���ʱ���ơ�
*  �������أ���
*  �޸�ʱ�䣺2012-3-18    �Ѳ���
*  ��    ע��
*************************************************************************/
void DMA_CH3_Handler(void)
{
//  printf("DMA_CH0_Handler\n");
/*  DMA_IRQ_CLEAN(DMA_CH0);                             //���ͨ�������жϱ�־λ    (���������ٴν����ж�)
  DMA_EN(DMA_CH0);  */                                  //ʹ��ͨ��CHn Ӳ������      (�������ܼ�������DMA����)
}



volatile uint8_t LPT_INT_count = 0;
void  LPT_Handler(void)
{
  LPTMR0_CSR |= LPTMR_CSR_TCF_MASK;   //���LPTMR�Ƚϱ�־
  LPT_INT_count++;                    //�ж������1
}