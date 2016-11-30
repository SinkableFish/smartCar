#include  "Landzo_servomotor.h"


/*************************************************************************
*                           蓝宙电子工作室
*
*  函数名称：Servo_motor_S3010_init
*  功能说明：S3010伺服机初始化程序
*  参数说明：
*  函数返回：无
*  修改时间：2014-9-12
*  备    注：
*************************************************************************/
void Servo_motor_S3010_init(void)
{
   TPM_PWM_init(TPM1, CH0 , 100,23);                           //舵机占空比设置初始化   MOD =19531 ;
   TPM_PWM_init(TPM1, CH1 , 100,23);                           //舵机占空比设置初始化   MOD =19531 ; 
   TPM_CnV_REG(TPMx[TPM1], CH0) = MIDSTRING1;         //舵机对中 让舵机保持在中位（就比如汽车方向盘打直）
   TPM_CnV_REG(TPMx[TPM1], CH1) = MIDSTRING1;         //舵机对中 让舵机保持在中位（就比如汽车方向盘打直
}

/*************************************************************************
*                           蓝宙电子工作室
*
*  函数名称：Servo_motor_SD5_init
*  功能说明：SD5伺服机初始化程序
*  参数说明：
*  函数返回：无
*  修改时间：2014-9-12
*  备    注：
*************************************************************************/
void Servo_motor_SD5_init(void)
{
   TPM_PWM_init(TPM1, CH1 , 75,0);                           //舵机占空比设置初始化   MOD =19531 ;
   TPM_PWM_init(TPM1, CH0 , 75,0);
   TPM_CnV_REG(TPMx[TPM1], CH0) = MIDSTRING2;                 //舵机对中 让舵机保持在中位（就比如汽车方向盘打直）
   TPM_CnV_REG(TPMx[TPM1], CH1) = MIDSTRING2;
   //舵机占空比设置初始化   MOD =19531 ; 
}

/*************************************************************************
*                           蓝宙电子工作室
*
*  函数名称：Servo_motor_S3010_centre
*  功能说明：S3010伺服机对中程序
*  参数说明：
*  函数返回：无
*  修改时间：2014-9-12
*  备    注：
*************************************************************************/
void Servo_motor_S3010_centre(void)
{
  uint16_t TurnPWM;
  TurnPWM = MIDSTRING1 ;
  TPM_CnV_REG(TPMx[TPM1], CH1) = TurnPWM ; 
  TPM_CnV_REG(TPMx[TPM1], CH0) = TurnPWM ; 
  
}

/*************************************************************************
*                           蓝宙电子工作室
*
*  函数名称：Servo_motor_SD5_centre
*  功能说明：SD5伺服机对中程序
*  参数说明：
*  函数返回：无
*  修改时间：2014-9-12
*  备    注：
*************************************************************************/
void Servo_motor_SD5_centre(void)
{
  uint16_t TurnPWM;
  TurnPWM = MIDSTRING2 ;
  TPM_CnV_REG(TPMx[TPM1], CH1) = TurnPWM ; 
  TPM_CnV_REG(TPMx[TPM1], CH0) = TurnPWM ; 
  
}

/*************************************************************************
*                           蓝宙电子工作室
*
*  函数名称：Servo_motor_S3010_test
*  功能说明：S3010伺服机测试程序
*  参数说明：
*  函数返回：无
*  修改时间：2014-9-12
*  备    注：
*************************************************************************/
void Servo_motor_S3010_test(void)
{
  static int8_t tep=0;
  static uint8_t Turnflag=0;
  uint16_t TurnPWM;
  if(tep==10)  Turnflag=1;
  else if(tep==-10) Turnflag=0;
  
  if(Turnflag==0)
  {   
    tep ++ ;       
    TurnPWM = MIDSTRING1 + tep*30 ;
    TPM_CnV_REG(TPMx[TPM1], CH1) = TurnPWM ; 
  TPM_CnV_REG(TPMx[TPM1], CH0) = TurnPWM ; 
  } 
  else if(Turnflag==1)
  {
    tep--;
    TurnPWM = MIDSTRING1 + tep*30 ;
    TPM_CnV_REG(TPMx[TPM1], CH1) = TurnPWM ; 
  TPM_CnV_REG(TPMx[TPM1], CH0) = TurnPWM ;           
  }
  else
  {
    TurnPWM = MIDSTRING1 ;
    TPM_CnV_REG(TPMx[TPM1], CH1) = TurnPWM ; 
  TPM_CnV_REG(TPMx[TPM1], CH0) = TurnPWM ;    
  }
  
}
/*************************************************************************
*                           蓝宙电子工作室
*
*  函数名称：Servo_motor_SD5_test
*  功能说明：SD5伺服机测试程序
*  参数说明：
*  函数返回：无
*  修改时间：2014-9-12
*  备    注：
*************************************************************************/
void Servo_motor_SD5_test(void)
{
  static int8_t tep=0;
  static uint8_t Turnflag=0;
  uint16_t TurnPWM;
  if(tep==10)  Turnflag=1;
  else if(tep==-10) Turnflag=0;
  
  if(Turnflag==0)
  {   
    tep ++ ;       
    TurnPWM = MIDSTRING2 + tep*200 ;
    TPM_CnV_REG(TPMx[TPM1], CH1) = TurnPWM ; 
  TPM_CnV_REG(TPMx[TPM1], CH0) = TurnPWM ; 
  } 
  else if(Turnflag==1)
  {
    tep--;
    TurnPWM = MIDSTRING2 + tep*200 ;
    TPM_CnV_REG(TPMx[TPM1], CH1) = TurnPWM ; 
  TPM_CnV_REG(TPMx[TPM1], CH0) = TurnPWM ;       
  }
  else
  {
    TurnPWM = MIDSTRING2 ;
    TPM_CnV_REG(TPMx[TPM1], CH1) = TurnPWM ; 
  TPM_CnV_REG(TPMx[TPM1], CH0) = TurnPWM ;    
  }
  
}
