#include<include.h>
#include<math.h>

extern uint8 TIME0flag_1s ;

uint8_t sqrt_t(uint8_t length)   //简易开方计算
{
  uint8_t p=0x80;
  uint8_t ans=0;
	while(p!=0)
	{
		ans+=p;
		if((ans*ans)>length)
		{
			ans-=p;
		}
		p=(int)(p/2);
	}
        return ans;
}

void judgeBarrier(int i)				//判断障碍物
{
	if(barrierCount >= 10000)
	{
		center = DataRow/2;
		barrierCount = 0;
		barrierFlag = 0;
		ServoPID.P = 85;
		//rightDistance = 0;
		//ServoPID.P = 85;
		// leftDistance = 0;
		// rightDistance = 0;
	}

	// if((!leftBarrier[i]) && (!rightBarrier[i]))
	// {
	// 	center = DataRow/2;
	// 	//leftDistance = 0;
	// 	ServoPID.P = 85;
	// }
	// if((!leftBarrier[i])&&(!rightBarrier[i]))
	// 	center = DataRow/2;
	if(leftBarrier[i] && (!rightBarrier[i]))
	{
		center = DataRow/4;
		barrierFlag = 1;
		ServoPID.P = 50;
		// for(leftDistance=0; leftDistance<80000; leftDistance++)
		// 	;
		// while(1)
		// 	if(TIME0flag_1s == 1)
		// 	{
		// 		TIME0flag_1s = 0;
		// 		break;
		// 	}
		//leftDistance += 1;
		// ServoPID.P = 20;
		// TPM_CnV_REG(TPMx[TPM1], CH1) = MIDSTRING2+1000;
		// delay_ms(20);
	}

	// if(leftBarrier[i] && (!leftBarrier[i+1]) && (!rightBarrier[i]))
	// {
	// 	// center = DataRow/4;
	// 	delay_ms(100);
	// }
	if(rightBarrier[i] && (!leftBarrier[i]))
	{
		center = DataRow*3/4;
		barrierFlag = 1;
		ServoPID.P = 50;
		// while(1)
		// {
		// 	if(TIME0flag_1s == 1)
		// 	{
		// 		TIME0flag_1s = 0;
		// 		break;
		// 	}
		// }
		// for(rightDistance=0; rightDistance<80000; rightDistance++)
		// 	;
		// rightDistance += 1;
		// ServoPID.P = 20;
		// TPM_CnV_REG(TPMx[TPM1], CH1) = MIDSTRING2-2000;
		// delay_ms(20);
	}
	if(barrierFlag == 1)
		barrierCount += speed;
	// if(rightBarrier[i] && (!rightBarrier[i+1]) && (!leftBarrier[i]))
	// {
	// 	// center = (DataRow*3)/4;
	// 	delay_ms(100);
	// }
}

void findRoute()				//寻找路径
{
	int mid, rightMid, leftMid, i, LineCount = 0;
	int tempDataLine;
	tempDataLine = DataLine-1;
	for(tempDataLine=(DataLine-1); tempDataLine>=0; tempDataLine--)
		{
			if(tempDataLine == (DataLine-1))
			{
				for(i=(DataRow/2); i<DataRow; i++)
				{
					if(OriginData[tempDataLine][i] == 0)
					{
						RightFlag = i;
						break;
					}
				}
				if(i == DataRow) 
				{
					LostRightFlag = 1;
					//RightFlag  = DataRow;
				}
				for(i=(DataRow/2); i>0; i--)
				{
					if(OriginData[tempDataLine][i] == 0)
					{
						LeftFlag= i;
						break;
					}
				}
				if(i == 0)
				{
					LostLeftFlag = 1;
					//LeftFlag = 0;
				}
			}
			else
			{
			if(OriginData[tempDataLine][RightFlag+1] == 1)          //判断是右侧否出现外拐
			{
				for(i=(RightFlag+1); i<DataRow; i++)
				{
					if(OriginData[tempDataLine][i] == 0)
					{
						RightFlag = (i+RightFlag)/2;
						break;
					}
				}
				if(i == DataRow)
					LostRightFlag = 1;
			}
			else
			{
				for(i=RightFlag; i>(DataRow/2); i--)
				{
					if(OriginData[tempDataLine][i] == 1)
					{
						RightFlag = (i+RightFlag)/2;
						break;
					}
				}
			}

			if(OriginData[tempDataLine][LeftFlag-1] == 1)           //判断左侧是否出现了外拐
			{
				for(i=(LeftFlag-1); i>0; i--)
				{
					if(OriginData[tempDataLine][i] == 0)
					{
						LeftFlag = (i+LeftFlag)/2;
						break;
					}
				}
				if(i == 0) 
					LostLeftFlag = 1;
			}
			else
			{
				for(i=LeftFlag; i<(DataRow/2); i++)
				{
					if(OriginData[tempDataLine][i] == 1)
					{
						LeftFlag = (i+LeftFlag)/2;
						break;
					}
				}
			}
		}
		// if(LostLeftFlag && (!LostRightFlag))
		// 	mid = RightFlag-DataRow/2;
		// if((!LostLeftFlag) && LostRightFlag)
		// 	mid = LeftFlag+DataRow/2;
		// if((!LostLeftFlag) && (!LostRightFlag))
		// 	mid = (LeftFlag+RightFlag)/2;
		// if(LostRightFlag && LostLeftFlag)
		// 	mid = DataRow/2;
		if(LostLeftFlag && (!LostRightFlag))
        {
         //LeftFlag = (117-tempDataLine)/4;
         //OriginData[tempDataLine][LeftFlag] = 0;
         //mid = (LeftFlag + RightFlag)/2;
         mid = RightFlag-DataRow/2;
          //mid = 0;
         tempMid = mid;
        }
		if((!LostLeftFlag) && LostRightFlag)
        {
          //RightFlag = (451+tempDataLine)/8;
          //OriginData[tempDataLine][RightFlag] = 0;
          //mid = (LeftFlag+DataRow)/2;
          mid = LeftFlag+DataRow/2;
          tempMid = mid;
        }
		if((!LostLeftFlag) && (!LostRightFlag))
			mid = (LeftFlag+RightFlag)/2;
		if(LostRightFlag && LostLeftFlag)
		{
			LeftFlag = (117-tempDataLine)/4;
			OriginData[tempDataLine][LeftFlag] = 0;
			RightFlag = (451+tempDataLine)/8;
			OriginData[tempDataLine][RightFlag] = 0;
			mid = (LeftFlag + RightFlag)/2;
			tempMid = mid;
			//mid = DataRow/2;
		}
		rightMid = (RightFlag + mid)/2;
		leftMid  = (LeftFlag + mid)/2;
		if(!LostRightFlag)
			if((!OriginData[tempDataLine][rightMid]) && (!OriginData[tempDataLine][rightMid+1]) && (!OriginData[tempDataLine][rightMid-1]))
			{
				tempMid = (LeftFlag+mid)/2;
				if((OriginData[tempDataLine][tempMid+1]) && (OriginData[tempDataLine][tempMid-1]))
					rightBarrier[LineCount] = 1;
				else 
					rightBarrier[LineCount] = 0;
			}
		if(!LostLeftFlag)
			if((!OriginData[tempDataLine][leftMid]) && (!OriginData[tempDataLine][leftMid+1]) && (!OriginData[tempDataLine][leftMid-1]))
			{
				tempMid = (RightFlag+mid)/2;
				if((OriginData[tempDataLine][tempMid+1])&&(OriginData[tempDataLine][tempMid-1]))
					leftBarrier[LineCount] = 1;//左侧障碍
				else
					rightBarrier[LineCount] = 0;
			
			}
		if((OriginData[tempDataLine][rightMid]!=0)&&(OriginData[tempDataLine][leftMid]!=0))
		{
			leftBarrier[LineCount] = 0;
			rightBarrier[LineCount] = 0;
		}
		OriginData[tempDataLine][mid] = 0;
		BlackLineData[LineCount] = mid;
		LostRightFlag = LostLeftFlag = 0;
		// leftBarrier = 0;
		// rightBarrier = 0;
		LineCount++;
	}
}


// void findCurvature()
// {
// 	int y1 = forward, y2 = forward*3/2, y3 = forward*2;
// 	int x1 = BlackLineData[y1], x2 = BlackLineData[y2], x3 = BlackLineData[y3];
//         int Lab, Lbc, Lac;
// 	int Tsquare;

// 	Lab = (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1);
// 	Lbc = (x3-x2)*(x3-x2) + (y3-y2)*(y3-y2);
// 	Lac = (x3-x1)*(x3-x1) + (y3-y1)*(y3-y1);
        
// 	Tsquare = ((x2-x1)*(y3-y1)-(x3-x1)*(y2-y1))/2;

// 	K = 4*Tsquare/(sqrt_t(Lab) + sqrt_t(Lbc) + sqrt_t(Lac));
//         ServoPID.err = K;
//         //  K = BlackLineData[20] - DataRow/2;
// }


void OTSU()					//动态阈值
{
    int i, j, tempThreshold, targetThreshold;
    for(tempThreshold=0x64; tempThreshold<0xFF; tempThreshold++)
    {
    	frontCount = 0;backCount = 0;frontSum = 0;backSum = 0;frontSum = 0;backSum = 0;
    	for(i = 0; i < DataLine; i++)
    	{
    		for(j = 0; j < DataRow; j++)
    		{
    			if(OriginData[i][j] > tempThreshold)
    			{
    				frontSum += OriginData[i][j];
    				frontCount++;
    			}
    			else
    			{
    				backSum += OriginData[i][j];
    				backCount++;
    			}
    		}
    	}
    	p1 = frontCount/(DataLine*DataRow);
    	p2 = backCount/(DataLine*DataRow);
    	frontAverage = frontSum/frontCount;
    	backAverage = backSum/backCount;
    	variance = p1*p2*(frontAverage-backAverage)*(frontAverage+backAverage);
    	if(variance > max)
    	{
    		targetThreshold = tempThreshold;
    		max = variance;
    	}
    }
    threshold = targetThreshold - 70;
}


void findCurvature()
{
  int sum = 0, i;
  for(i=15; i<55; i++)
  {
    sum += BlackLineData[i];
  }
  judgeBarrier(56);
  judgeBarrier(57);
  judgeBarrier(58);
  judgeBarrier(59);
  judgeBarrier(60);
  judgeBarrier(61);
  judgeBarrier(62);
  judgeBarrier(63);
  judgeBarrier(64);
  judgeBarrier(65);
  judgeBarrier(66);
  judgeBarrier(67);
  judgeBarrier(68);
  judgeBarrier(69);
  judgeBarrier(70);
  // judgeBarrier(71);
  // judgeBarrier(72);
  // judgeBarrier(73);
  // judgeBarrier(74);
  // judgeBarrier(75);
  // judgeBarrier(76);
  // judgeBarrier(77);
  
  ServoPID.err1 = ServoPID.err;
  K_front = sum/40 - center;
}



void setCenter() 				//调正车身姿态
{
  int sum = 0, i;
  ServoPID.err1 = ServoPID.err;
  findCurvature();
  K = BlackLineData[0] - center;
  //if(K_front<-15 || K_front>15)
  //	K = K_front;
  //else
  //{
  	for(i=38; i<99; i++)
  		sum += BlackLineData[i];
  	K = sum/61 - center;
  //}
  ServoPID.err = K;
}


void datatoBMP()
{
  for (int i=0;i<DataLine;i++)
  {    
      for (int j=0;j<DataRow;j++)
          if (OriginData[i][j]==1) 
            imageBMP[i/8][j]&=~(1<<(i%8));
          else  
            imageBMP[i/8][j]|=(1<<(i%8));
  }
}

void judgeStartLine(int i) 			//判断起跑线
{
  if((rightBarrier[i]||rightBarrier[i+1]||rightBarrier[i-1]||rightBarrier[i+2]||rightBarrier[i-2]||rightBarrier[i+3]||rightBarrier[i-3])&&(leftBarrier[i]||leftBarrier[i-1]||leftBarrier[i+1]||leftBarrier[i+2]||leftBarrier[i-2]||leftBarrier[i+3]||leftBarrier[i-3]))
	{
		startLineFlag = 1;
		//if(stopFlag == 0)
			//stopFlag = 1;
	}
	if(startLineFlag == 1)
	{
		startLineCount += abs(speed);
	}
	if(stopFlag == 0)
		startLineDelay += 1;
	if(startLineCount >= 1000 && startLineDelay > 10000)
	{
		startLineFlag = 0;
		stopFlag += 1;
		startLineCount = 0;
		center = DataRow/2;
		barrierCount = 0;
		barrierFlag = 0;
		//ServoPID.P = 75;
	}
	if(stopFlag >= 2)
	{
		motoDuty = 0;
	}
} 

