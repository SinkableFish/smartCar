#include<include.h>
extern uint8 TIME0flag_100ms;

void findType()				//速度选择
{
	if(K_front<6 && K_front>-6)
	{
		motoDuty = targetSpeed;
		ServoPID.P = 85;
		ServoPID.D = 500;
	}
	else
	{
		motoDuty = secondTargetSpeed;
		ServoPID.P = 85;
		//ServoPID.P = 20;
		ServoPID.D = 500;
	}
	//findCurvature();
}

/*void setDuty()
{
        static unsigned char i;
        int temp_d;
	if(K>-2 && K<2)
	  TPM_CnV_REG(TPMx[TPM1], CH1) = MIDSTRING2;
	else
	{
          ServoPID.derr[i] = ServoPID.err;
 
         temp_d =  (ServoPID.err-ServoPID.derr[(i == 4) ? 0 : (i + 1)]);
         ServoDuty = ServoPID.P*ServoPID.err+ServoPID.D*temp_d;
	  if(ServoDuty > 2000)
	    ServoDuty = 2000;
	  if(ServoDuty < -2000)
	    ServoDuty = -2000;
	  TPM_CnV_REG(TPMx[TPM1], CH1) = MIDSTRING2 + ServoDuty;
          OutData[0] =temp_d;
          OutData[1] = ServoPID.err;
          OutPut_Data();
          i++;
          if(i == 5)
            i = 0;
          
    }
}*/
void setDuty()
{
	if(K>-2 && K<2)
	  TPM_CnV_REG(TPMx[TPM1], CH1) = MIDSTRING2;   //直道滤波
	else
	{
	  ServoDuty = ServoPID.P*ServoPID.err+ServoPID.D*(ServoPID.err-ServoPID.err1);//舵机PD式
          if(ServoDuty<0)
            ServoDuty = ServoDuty;
	  if(ServoDuty > 2000)				//超限保护
	    ServoDuty = 2000;
	  if(ServoDuty < -2000)
	    ServoDuty = -2000;
	  TPM_CnV_REG(TPMx[TPM1], CH1) = MIDSTRING2 + ServoDuty;
    }
}