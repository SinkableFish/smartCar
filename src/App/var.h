#ifndef _INIT_H_
#define _INIT_H_
#define DataLine 100
#define DataRow  75

typedef struct PID
{
   int P;//proportion
   int I;//integral   
   int D;//derivative
   float err;//err[0]
   float err1;//err[-1]
   float err2;//err[-2]
   float adjust;
   int derr[5];
}PID;

extern int8_t menu;
extern int8_t option1;
extern uint8_t solution;

extern uint8_t OriginData[DataLine][DataRow];//图像变量
extern uint8_t BlackLineData[DataLine];
extern uint8_t source[DataRow];
extern uint8_t leftBarrier[DataLine];
extern uint8_t rightBarrier[DataLine];
extern uint8_t imageBMP[DataLine/8+1][DataRow];
extern uint8_t LeftFlag;
extern uint8_t RightFlag;
extern uint8_t threshold ;
extern uint8_t LostLeftFlag ;
extern uint8_t LostRightFlag ;
extern uint8_t ans ;
extern uint8_t length;
extern uint8_t forward;
extern uint8_t leftBarrier[DataLine];
extern uint8_t rightBarrier[DataLine];
extern uint8_t tempMid;
extern float xSum;
extern float ySum; 
extern float xSquSum;
extern float ySquSum;
extern float xySum;
extern float b;
extern float xySumMul;
extern float xSumSqu;
extern uint8_t center;
extern volatile int16_t startLineCount;
extern uint8_t startLineFlag;
extern uint8_t stopFlag;
//extern int16_t rightDistance;
//extern int16_t leftDistance;
extern int16_t barrierFlag;
extern uint16_t barrierCount;
extern int startLineDelay;

extern volatile int16_t speed; 						//速度变量
extern int16_t pluseCount;
extern int16_t motoDuty;
extern uint8_t dir;
extern volatile int targetSpeed;
extern volatile int secondTargetSpeed;

extern volatile float frontCount; 			//OTSU变量
extern volatile float backCount;
extern volatile float frontAverage;
extern volatile float backAverage;
extern float frontSum;
extern float backSum;
extern float p1;
extern float p2;
extern float variance;
extern float max;
extern volatile int OTSU_flag;
extern int err;

extern float ServoDuty ;
extern volatile float   K;
extern float   K_front;
extern float OutData[4];

extern PID ServoPID;
extern PID centerPID;
extern PID motoPID;
#endif