
#include "include.h"
#include "Landzo_Calculation.h"



/*********************************************************** 
�������ƣ�CCD_init
�������ܣ�
��ڲ�����
���ڲ������� 
�� ע�� 
***********************************************************/
//extern uint8  BUFF[500] ;
extern uint8  OriginData[DataLine][DataRow];
extern uint8 SpeedMeasure;

void CCD_INC (void)
{
   gpio_Interrupt_init(PTA17, GPI_UP, FALLING) ;          //���ж�
   gpio_Interrupt_init(PTA13, GPI_UP, FALLING) ;          //���ж� 
   DMA_PORTx2BUFF_Init (DMA_CH0, (void *)&PTD_BYTE0_INT, (void *)&OriginData[0][0], PTA16,DMA_BYTE1, DATACOUNT);
    //DMAͨ��0 ��PTD0-PTD7 ���ݲɼ���ADdata���ݴ洢λ�ã�PTA16����ͨ����DMA_BYTE1  ���ݴ洢���ȣ�DATACOUNT  �����ܸ���
   set_irq_priority((INT_PORTA + INC_IRQ),0);    //�������ȼ�
   setIRQadrr(INT_PORTA,PORTA_IRQHandler);  //�����жϵ�ַ����
}



