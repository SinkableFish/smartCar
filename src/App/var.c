#include<include.h>

int8_t menu;
int8_t option1=0;
uint8_t solution;

uint8_t OriginData[DataLine][DataRow];		//二值化图像
uint8_t BlackLineData[DataLine];			//路径数组
uint8_t source[DataRow] = {1};
uint8_t leftBarrier[DataLine] = {0};		//左障碍数组
uint8_t rightBarrier[DataLine] = {0};		//右障碍数组
uint8_t imageBMP[DataLine/8+1][DataRow]={0};//液晶显示数组
uint8_t LeftFlag;							//左边界标志
uint8_t RightFlag;							//右边界标志
uint8_t threshold = 100;					//阈值
uint8_t LostLeftFlag = 0;					//左丢线标志
uint8_t LostRightFlag = 0;					//右丢线标志
uint8_t ans = 0;							//开方数
uint8_t length;
uint8_t forward = 10;						//前瞻
uint8_t center = DataRow/2;					//图像中心
uint8_t tempMid;							//暂时图像中心
uint8_t startLineFlag;						//起跑线标志
volatile int16_t startLineCount=0;			//起跑线计数
uint8_t stopFlag=0;							//停车标志
//int16_t leftDistance;
//int16_t rightDistance;
int16_t barrierFlag;						//障碍物标志
uint16_t barrierCount = 0;					//障碍物计数
int startLineDelay;							//第一次识别起跑线延时
// float xSum;
// float ySum; 
// float xSquSum;
// float ySquSum;
// float xySum;
// float b;
// float xySumMul;
// float xSumSqu;

volatile int16_t speed; 					//速度变量
int16_t pluseCount;							//脉冲计数
//uint8_t motoDuty = 225;
int16_t motoDuty;							//目标速度
uint8_t dir;								//当前方向
volatile int targetSpeed;					//直道速度
volatile int secondTargetSpeed;				//弯道速度

volatile float frontCount; 					//OTSU前景
volatile float backCount;					//OTSU后景
volatile float frontAverage;				//前景平均值
volatile float backAverage;					//后景平均值
float frontSum;								//前景和
float backSum;								//后景和
float p1;									
float p2;
float variance;								//方差
float max;									//最大类间差
int volatile OTSU_flag = 0;					//动态阈值计算结束标志
int err;

float ServoDuty = 0;
volatile float   K;							//近处误差
float   K_front;							//远处误差
float OutData[4] = { 0 };

PID ServoPID;
PID centerPID;
PID motoPID;
//ISR中断图像处理
