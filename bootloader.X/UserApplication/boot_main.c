/*###############################################################################################################################
 # 文件名称 ： U80711R01_main_h.h																				  #
 # 公司名称 :  TOTEX Technology, Inc.                                                                                           #
 # 芯片型号 ： PIC24FJ64GL302                                                                                                   #
 # 编译工具 :  ccs compiler v5.092                                                                                              #
 # 作    者 :  BenZhang                                                                                                         #
 # 编写日期 :  2020/11/20                                                                                                       #
 # 版    本 :  V1.00                                                                                                            #
 ##############################################################################################################################*/

#include "boot_updateFirmware.h"

/*###############################################################################################################################
# 函数名  :  void interrupt serrvice_isr(void)                                                                                  #
# 功  能  :  全局中断入口函数                                                                                                   #
# 参  数  :  NONE                                                                                                               #
# 说  明  :  NONE                                                                                                               #
###############################################################################################################################*/
#int_default
void isr(void)
{
	jump_to_isr(APPLICATION_ISR_START);
}

/*###############################################################################################################################
# 函数名 :  void main(void)                                                                                                     #
# 功  能 :  主函数                                                                                                              #
# 参  数 :  NONE                                                                                                                #
# 说  明 :  NONE                                                                                                                #
###############################################################################################################################*/
#zero_ram
void main(void) {
    U1MODE &= 0b011111111;                                  //##(0)先关闭串口后再开启串口(清除接收 FIFO)
    #asm NOP #endasm 
    #asm NOP #endasm                                        //##(0)UART重新启动，FIFO 处于清空后的初始状态
    #asm NOP #endasm 
    #asm NOP #endasm 
    U1MODE |= 0b100000000;                                  //##(0)20260206 修改的测试版本  
	setup_wdt(WDT_ON|WDT_8S);								//##(0)看门狗定时器2秒
	VCC_ON;													//##(0)开启VDD输出
	receiver;												//##(0)使能串口接收     
	delay_ms(50);											//##(0)延时10毫秒稳定LED显示驱动芯片电源
    resetRGBLED();                                          //##(0)复位 LED 
    delay_ms(2);
    Turn_off_all_LEDs();                                    //##(0)关闭显示 
	setup_timer1(TMR_INTERNAL | TMR_DIV_BY_8);				//##(0)配置定时器【1】10毫秒定时一次
	set_timer1(65535 - 20000);								//##(0)10ms 溢出一次(分频:8,一个计数 = 2/32Mhz * 8 *20000)
	clear_interrupt(INT_TIMER1);							//##(0)清除中断标志
	disable_interrupts(GLOBAL);								//##(0)关闭中断总闸
	boot.bits.enableBootMode = checking_updata_status();	//##(0)读取更新状态
	boot.LEDsDisplayStatus = ShowGreen;						//##(0)显示白色(在BOOTLOADER模式则显示白色)
	delay_cycles(50); 
	while(TRUE) {
		while(boot.bits.enableBootMode) {
			restart_wdt();									//##(0)复位看门狗定时器
			application_Erase_process();					//##(0)擦除应用区域	
			bootloader_UserApplication();					//##(0)更新代码进程 
		}
		delay_cycles(50);									//##(0)如果没有需要更新或者已经更新完成则进入应用程序
		goto_address(APPLICATION_START);					//##(0)跳入应用程序地址,开始执行应用程序
	}
}

 