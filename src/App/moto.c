#include<include.h>
#include<math.h>
#define  LIN_COUT    100

void SpeedControl()
{
    dir = gpio_get(PTB1);           //D触发器获得目前车轮旋转方向
    motoPID.err2 = motoPID.err1;    //获得上上次误差
    motoPID.err1 = motoPID.err;     //获得上次误差
    if(dir == 0)
      pluseCount = lptmr_pulse_get();
    else
      pluseCount = -lptmr_pulse_get();
    lptmr_counter_clean();      
    speed = pluseCount;             //获得脉冲数
    motoPID.err = motoDuty - speed; //获得当前误差
    motoPID.adjust += ( motoPID.P*(motoPID.err-motoPID.err1) + motoPID.I*motoPID.err + motoPID.D*((motoPID.err-motoPID.err1)-(motoPID.err1-motoPID.err2)))/10000;//增量式PID控制式
    if(motoPID.adjust >  50)        //超限保护
         motoPID.adjust = 50;
     if(motoPID.adjust < -50)
         motoPID.adjust = -50;
    if(motoPID.adjust > 0)          //正转
    {
      TPM_PWM_Duty(TPM2,CH0,motoPID.adjust);
      TPM_PWM_Duty(TPM2,CH1,0);
    }
    else                            //反转
    {
    TPM_PWM_Duty(TPM2,CH1,abs(motoPID.adjust));
    TPM_PWM_Duty(TPM2,CH0,0);
    }
}