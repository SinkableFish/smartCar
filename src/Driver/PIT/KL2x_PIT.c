/***********************************************************
 * 文件名       ：PTI.c
 * 说明         ：PTI初始化
 * 作者         ：野火嵌入式开发工作室/landzo 蓝电子
 * 淘宝店       ：http://landzo.taobao.com/
 * 公司网站     ：http://www.landzo.com/
 *论坛          ：http://www.landzo.cn
 * 库版本       ：V2.0
 *时间          ：15.5.26
************************************************************/

#include "KL2x_PIT.h"     //周期中断计时器

/*************************************************************************
*                             野火嵌入式开发工作室
*
*  函数名称：pit_init
*  功能说明：PITn定时中断
*  参数说明：PITn        模块号（PIT0~PIT3）
             cnt         延时时间(单位为bus时钟周期)
*  函数返回：无
*  修改时间：2012-1-24
*  备    注：
*************************************************************************/
void pit_init(PITn pitn, uint32_t cnt)
{
    //PIT 用的是 Bus Clock 总线频率
    //溢出计数 = 总线频率 * 时间

    /* 开启时钟*/
    SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;                            //使能PIT时钟

    /* PIT模块控制 PIT Module Control Register (PIT_MCR) */
    PIT_MCR = 0 ;      //使能PIT定时器时钟 ，调试模式下继续运行

    /* 定时器加载值设置 Timer Load Value Register (PIT_LDVALn) */
    PIT_LDVAL(pitn)  = cnt;                                          //设置溢出中断时间
    /* 定时器控制寄存器 Timer Control Register (PIT_TCTRL0) */
    PIT_TCTRL(pitn) = ( PIT_TCTRL_TEN_MASK | PIT_TCTRL_TIE_MASK );   //使能 PITn定时器,并开PITn中断
    //定时时间到了后，TIF 置 1 。写1的时候就会清0
    PIT_Flag_Clear(pitn);   //清中断标志位
    enable_irq(PIT_irq_no);   //开接收引脚的IRQ中断
    
}


/*************************************************************************
*                             野火嵌入式开发工作室
*
*  函数名称：pit_init
*  功能说明：PITn定时中断
*  参数说明：PITn        模块号（PIT0~PIT3）
             cnt         延时时间(单位为bus时钟周期)
*  函数返回：无
*  修改时间：2012-1-24
*  备    注：
*************************************************************************/
void pit_dma_init(PITn pitn, uint32_t cnt)
{
    //PIT 用的是 Bus Clock 总线频率
    //溢出计数 = 总线频率 * 时间

    /* 开启时钟*/
    SIM_SCGC6       |= SIM_SCGC6_PIT_MASK;                            //使能PIT时钟

    /* PIT模块控制 PIT Module Control Register (PIT_MCR) */
    //PIT_MCR         &=~(PIT_MCR_MDIS_MASK | PIT_MCR_FRZ_MASK );       //使能PIT定时器时钟 ，调试模式下继续运行
    PIT_MCR = 0;

    /* 定时器加载值设置 Timer Load Value Register (PIT_LDVALn) */
    PIT_LDVAL(pitn)  = cnt;                                          //设置溢出中断时间

    //定时时间到了后，TIF 置 1 。写1的时候就会清0
    PIT_Flag_Clear(pitn);                                             //清中断标志位

    /* 定时器控制寄存器 Timer Control Register (PIT_TCTRL0) */
    PIT_TCTRL(pitn) |= (0
                        | PIT_TCTRL_TEN_MASK  //使能 PITn定时器
                        | PIT_TCTRL_TIE_MASK  //开PITn中断
                       );

    enable_irq(PIT_irq_no);			                                //开接收引脚的IRQ中断
}