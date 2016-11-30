#include<include.h>

void menu0()//第0级菜单，舵机PID，目标速度
{
	OLED_Fill(0x00);  
	OLED_P6x8Str(0,option1,">");
	OLED_P6x8Str(20,0,"S.P");
	OLED_Print_Num(60,0,ServoPID.P);
	OLED_P6x8Str(20,3,"S.D");
	OLED_Print_Num(60,3,ServoPID.D);
	OLED_P6x8Str(20,6,"speed");
	OLED_Print_Num(60,6,motoDuty);

	if (key_press(KEY_B))    //选择行
      { 
          option1 += 3;
          if(option1>7) option1=0;
      }
      if (key_press(KEY_A))
      { 
          option1 -= 3;
          if (option1<0) option1=6;
      }
      if (option1==0)     //数值加减
      {
        if (key_press(KEY_C))
        { 
            ServoPID.P-=1;
            if (ServoPID.P<0) ServoPID.P=0;
        }
        if (key_press(KEY_D))
        { 
             ServoPID.P+=1;
        }

      }
      else if(option1==3)   //数值加减
      {
        if(key_press(KEY_C))
        {
          ServoPID.D -= 10;
          if(ServoPID.D<0)
            ServoPID.D = 0;
        }
        if(key_press(KEY_D))
        {
          ServoPID.D += 10; 
        }
      }
       else if (option1==6)
      {
        if (key_press(KEY_C))
        { 
          motoDuty-=5;
          if (motoDuty<0) motoDuty=0;
        }
        if (key_press(KEY_D))
        { 
            motoDuty+=5;
        }
      }
}

void menu1()
{
  OLED_Fill(0x00);  
  OLED_P6x8Str(0,option1,">");
  OLED_P6x8Str(20,0,"M.P");
  OLED_Print_Num(60,0,motoPID.P);
  OLED_P6x8Str(20,3,"M.I");
  OLED_Print_Num(60,3,motoPID.I);
  OLED_P6x8Str(20,6,"M.D");
  OLED_Print_Num(60,6,motoPID.D);

  if (key_press(KEY_B))
  { 
    option1 += 3;
    if(option1>7) option1=0;
  }
  if (key_press(KEY_A))
  { 
      option1 -= 3;
      if (option1<0) option1=6;
  }

   if (option1==0)
  {
    if (key_press(KEY_C))
    { 
        motoPID.P-=100;
        if (motoPID.P<0) motoPID.P=0;
    }
    if (key_press(KEY_D))
    { 
         motoPID.P+=100;
    }

  }
  else if(option1==3)
  {
    if(key_press(KEY_C))
    {
      motoPID.I -= 10;
      if(motoPID.I<0)
        motoPID.I = 0;
    }
    if(key_press(KEY_D))
    {
      motoPID.I += 10; 
    }
  }
   else if (option1==6)
  {
    if (key_press(KEY_C))
    { 
        motoPID.D-=5;
        if (motoPID.D<0) motoPID.D=0;
    }
    if (key_press(KEY_D))
    { 
        motoPID.D+=5;
    }
  }
}

void menu2()
{
  OLED_Fill(0x00);  
  OLED_P6x8Str(0,option1,">");
  OLED_P6x8Str(20,0,"threshold");
  OLED_Print_Num(100,0,threshold);
  OLED_P6x8Str(20,3,"solution");
  OLED_Print_Num(100,3,solution);

  if (key_press(KEY_B))
  { 
    option1 += 3;
    if(option1>7) option1=0;
  }
  if (key_press(KEY_A))
  { 
      option1 -= 3;
      if (option1<0) option1=6;
  }

   if (option1==0)
  {
    if (key_press(KEY_C))
    { 
        threshold-=10;
        if (threshold<0) threshold=0;
    }
    if (key_press(KEY_D))
    { 
         threshold+=10;
    }

  }
}

void menu3()
{
  OLED_Fill(0x00);
  datatoBMP();
  Draw_BMP(25, 0, DataRow+25, 7, imageBMP[0]);datatoBMP();
}


void menuDisplay()
{
        if (key_press(KEY_F))
        {
           menu++;
           if (menu>3) menu=0;
        }
        if (key_press(KEY_E))
        {
           menu--;
           if (menu<0) menu=3;
        }
        switch (menu)
        {
           case 0:menu0();break;
           case 1:menu1();break;
           case 2:menu2();break;
           case 3:menu3();break;
        }
}