/*###############################################################################################################################
 # 文件名称 ： u85128R01_CONFIG_H.H                                                                                             #
 # 公司名称 :  TOTEX Technology, Inc.                                                                                           #
 # 芯片型号 ： PIC24FJ128GA406                                                                                                  #
 # 编译工具 :  ccs compiler v5.078                                                                                              #
 # 作    者 :  BenZhang                                                                                                         #
 # 编写日期 :  2021/03/20                                                                                                       #
 # 版    本 :  V1.00                                                                                                            #
 ##############################################################################################################################*/
#include "app_config.h"
#include "app_bq76952.h"
#include "app_interrupts.h"
#include "app_tmag3001.h"
#include "app_Display.h"
#include "app_communication.h"

void Display_off(void);
void CheckBatteryState_Process(void);
/*###############################################################################################################################
# 函数名 :  void microcontroller_sleep(void)                                                                                    #
# 功  能 :  微控制器睡眠                                                                                                        #
# 参  数 :  NONE                                                                                                                #
# 说  明 :  NONE                                                                                                                #
###############################################################################################################################*/
void clearRegisters(void) {
	regs.AnimQty = 0;
	regs.flags.MsgPrint= false;				//##(0)禁止打印信息
    regs.flags.ChgProc = false;				//##(0)正在充电标志清零
    regs.flags.sysint  = false;				//##(0)清除"SYSINT"中断标志,ID触发
    regs.flags.Sensor1 = false;				//##(0)传感器"1"中断标志清零
    regs.flags.Sensor2 = false;				//##(0)传感器"1"中断标志清零
    regs.flags.ReqInfoDone = false;			//##(0)请求设备信息完成标志清零(重新请求基本信息)
    regs.flags.TransmitInfo = false;		//##(0)需要重新发送基本信息(版本信息之类)
    regs.flags.ReqAnimsDone = false;		//##(0)请求动画完成标志清零
	regs.recvAnimCnt = 0;					//##(0)接收动画组计数器清零
	regs.HallSensorStatus = 0u;				//##(0)关闭定时发送霍尔传感器数据
    regs.Request.UsrtBusy = false;			//##(0)通讯忙标志清零   
    regs.flags.NoComTmrEn = false;			//##(0)无通讯计时器禁止计数
    regs.NoCommTimeout = 0U;				//##(0)无通讯计时器计数器清零
    regs.DeviceType = 0u;					//##(0)状态切换,需要重新请求信息和动画
    DispBattFull = false;					//##(0)清除刷新电池充满动画
    regs.FaultLive.u16 &= 0x0001;			//##(0)第一时间将临时故障清除
	regs.bqErrorCount = 0;					//##(0)读取"ba76952"失败计数器清零
}
void clearFlaultRegs(void) {
    isShowFault = false;					//##(0)清除正在显示故障标志
    FualtShowDelay = regs.time10ms;       //##(0)记录当前系统计时，作为下一阶段延时起点 
    FaultShowUpdata = false;				//##(0)清除暂停显示故障(使能显示故障)
}

/*###############################################################################################################################
# 函数名 :  void config_module(void)                                                                                            #
# 功  能 :  配置mcu功能模块                                                                                                     #
# 参  数 :  NONE                                                                                                                #
# 说  明 :  NONE                                                                                                                #
###############################################################################################################################*/
void config_module(void) { 
    VCC_ON;                                             //##(0)开启VDD输出
	PullON;                                             //##(0)使能总线上拉
	SYSBIAS_ON;											//##(0)开启ID测量上拉
	receiver;                                           //##(0)使能串口接收
	delay_ms(20);                                       //##(0)延时10毫秒稳定LED显示驱动芯片电源
//##(0)配置功能模块    
    setup_wdt(WDT_16S);                                //##(0)看门狗定时器131秒【芯片决定不能动态更改WDT分频时间】
	config_timers(Enable);								//##(0)配置定时器【1/2/3/4】全部定时器开启
	config_ExtInterrupts();								//##(0)配置外部中断
//##(0)配置ADC模块     
    setup_adc_ports(sAN1,VSS_VDD);                      //##(0)PIN_C3(sAN7)作为模拟输入测量
    setup_adc(ADC_CLOCK_INTERNAL);                      //##(0)使用内部时钟     
//##(0)使用"DMA"通道"0"/DMA 触发源 = 串口接收就绪/搬运单位是 1 字节/传输完成后 自动重装地址（循环搬运）
    setup_dma(0, DMA_TRIGGER_RDA, DMA_BYTE | DMA_RELOAD_ADDRESS);
//##(0)启动"DMA"传输，
    dma_start(0, DMA_SOURCE_ADDR_UNCHANGED | DMA_INC_DEST_ADDR, uart.buffer, getenv("SFR:U1RXREG"), dmaSize);
//##(0)采用DMA通道"1"发送数据
    setup_dma(1, DMA_TRIGGER_TBE, DMA_BYTE | DMA_RELOAD_ADDRESS);    
//##(0)配置中断总闸    
	enable_interrupts(GLOBAL);
//##(0)关闭LED
	Display_off();                                      //##(0)关闭故障动画		
}
/*###############################################################################################################################
# 函数名 :  void microcontroller_sleep(void)                                                                                    #
# 功  能 :  微控制器睡眠                                                                                                        #
# 参  数 :  NONE                                                                                                                #
# 说  明 :  NONE                                                                                                                #
###############################################################################################################################*/
void config_sleep(uint16_t command) {
    uint8_t retry;
////##(0)U18折叠传感器进入唤醒和睡眠模式【深度睡眠期间需要磁铁靠近/离开唤醒】
////##(0)进入休眠失败且重试不足8次则持续重试
//    retry = 0u;
//    while(Sensor_config(TMAG3001FOLD, DeepSleepMode) && retry<8) { delay_ms(20); retry++;}		
//    delay_ms(10);
////##(0)绑带传感器(U18)则进入深度睡眠模式【深度睡眠期间无需磁铁改变唤醒】 
//    retry = 0u;
//    while(Sensor_config(TMAG3001STRAP,DeepSleepMode) && retry<8) { delay_ms(20); retry++;}		    
#if defined(U80722R01)
    retry = 0u;
    while(Sensor_config(TMAG3001FOLD, DeepSleepMode) && retry<8) { delay_ms(50); retry++;}	//##(0)折叠传感器(U17)进入深度睡眠模式
    delay_ms(10);
    retry = 0u;
    while(Sensor_config(TMAG3001STRAP,DeepSleepMode) && retry<8) { delay_ms(50); retry++;}  //##(0)绑带传感器(U18)进入深度睡眠模式		  
#else 
    retry = 0u;
    while(Sensor_config(TMAG3001STRAP,DeepSleepMode) && retry<8) {delay_ms(50); retry++;}   //##(0)绑带传感器(U18)进入深度睡眠模式
    delay_ms(10);	
    retry = 0u;
    while(Sensor_config(TMAG3001FOLD, DeepSleepMode) && retry<8) {delay_ms(50); retry++;}   //##(0)折叠传感器(U17)进入深度睡眠模式			       
#endif  
//##(0)关闭其它耗电模组
    Display_off();                      //##(0)关闭显示
//##(0)关闭充放电FET
    bq76952_writeWord(AllFETOFF);       //##(0)关闭充放电FET命令  
    delay_ms(1);
    bq76952_writeWord(command);         //##(0)发送命令让"bq76952"进入深度睡眠模式或者是"ShutDown"模式  
//##(0)关闭硬件
    PUST_0;                             //##(0)驱动LED引脚拉低
    receiver;                           //##(0)使能串口接收
    SYSBIAS_OFF;                        //##(0)关闭检测ID电阻偏置,配置为浮空
    PullOFF;                            //##(0)关闭总线上拉
    VCC_OFF;                            //##(0)关闭VDD输出
    i2c_init(false);                    //##(0)关闭I2C模块
    output_low(pin_b14);                //##(0)总线引脚拉低(方便外设读取硬件)
    output_low(pin_b15);                //##(0)总线引脚拉低(方便外设读取硬件)
    output_float(ALERT);                //##(0)浮空输入 
//##(0)配置模块	
    restart_wdt();                      //##(0)复位看门狗定时器
	setup_wdt(WDT_OFF);                 //##(0)关闭看门狗定时器【如需要定时看门狗唤醒则删除此语句】
	setup_adc(ADC_OFF);                 //##(0)关闭ADC模块                       
    setup_adc_ports(NO_ANALOGS);        //##(0)全部端口配置为数字I/O口
	config_timers(Disable);				//##(0)配置定时器【1/2/3/4】全部定时器关闭
	config_ExtInterrupts();				//##(0)配置外部中断
	clear_interrupt(INT_RDA);           //##(0)清除串口中断标志
    enable_interrupts(INT_RDA);         //##(0)开启串口接收数据中断
}

/*###############################################################################################################################
# 函数名 :  void microcontroller_sleep(void)                                                                                    #
# 功  能 :  微控制器睡眠                                                                                                        #
# 参  数 :  NONE                                                                                                                #
# 说  明 :  NONE                                                                                                                #
###############################################################################################################################*/
#define T3SEC  3000/10									//##(0)3秒宏定义
void microcontroller_sleep(void) {
    static uint16_t timeout;
            uint8_t count;   
//##(0)执行相应模式
    switch(regs.flags.RunMode) {
        case MODE_WORK:                                 //##(0)处于开机模式则返回
             timeout = regs.time10ms;					//##(0)更新时间基点
             return;
        case MODE_SHUTDOWN:                             //##(0)关机模式[运输模式]
             regs.commands = ShutDownCmd;               //##(0)写关机模式命令【BQ76952】
             writeEeprom(eeprom_DsgCnt,(U8 *)&ulDsgCC,2u);    //##(0)保存放电容量统计数据
             PowerStatusDisplay(powerOff);              //##(0)播放关机动画
			 regs.flags.RunMode = MODE_NULL;			//##(0)设置空模式以免重复执行
             break;    
        case MODE_EnterSLEEP:                           //##(0)命令进入睡眠模式	
             regs.commands = DeepSleepCmd;              //##(0)写深度模式命令【BQ76952】
             PowerStatusDisplay(powerOff);              //##(0)播放关机动画
			 regs.flags.RunMode = MODE_NULL;			//##(0)设置空模式以免重复执行
             break;       
        case MODE_SLEEP:                                //##(0)睡眠模式
             if(regs.flags.AnimEn) { timeout = regs.time10ms; return;}   //##(0)如果有播放动画则更新时间基点并退出
			 #asm nop #endasm
			 regs.FaultLive.u16 = 0;					//##(0)清除临时故障标志
			 IDTypeError = false;						//##(0)清除"ID"错误标志
             if((regs.time10ms-timeout)<T3SEC) return;  //##(0)如果在3秒内无任何动作则进入睡眠,有则退出
             regs.commands = DeepSleepCmd;              //##(0)进入睡眠前写深度睡眠模式命令【BQ76952】 
             break;
        default: 
             timeout = regs.time10ms;					//##(0)更新时间基点
             return;
    }
//##(0)进入"SLEEP"/"SHUTDOWN"前配置相关寄存器
    config_sleep(regs.commands);						//##(0)配置功能模块
	regs.flags.mcuSleep = true;							//##(0)设置进入睡眠标志	
//##(0)进入睡眠
enter_sleep:		
	regs.flags.NoWdtWakeup = false;						//##(0)标志清零,如果不是WDT唤醒则此标志="1"
	restart_wdt();										//##(0)睡眠之前复位看门狗定时器以保证看门狗时间溢出每次都一致
	output_bit(pin_b5,0);								//##(0)测试引脚进入睡眠拉低
    delay_us(10);										//##(0)
    sleep(SLEEP_FULL);									//##(0)进入深度睡眠
    delay_us(10);										//##(0)
	output_bit(pin_b5,1);								//##(0)测试引脚退出睡眠拉高				
//##(0)从睡眠唤醒则需要开启I2C总线上拉以便读取"bq76952"信息
	PullON;												//##(0)使能总线上拉
	i2c_init(true);										//##(0)重新开启总线
	delay_ms(5);										//##(0)延时稳定总线上拉电平
//##(0)正常其它唤醒,开启相关硬件	
	config_module();					//##(0)配置功能模块(激活后)
	bq76952_writeWord(ExitDeepSleep);	//##(0)退出睡眠/深度睡眠模式  
//##(0)重新配置折叠传感器为连续模式
    count = 0u;    
    while( Sensor_config(TMAG3001FOLD,ContinuousMode) && count<8) { delay_ms(10); count++; }    
//##(0)重新配置绑带传感器为连续模式
    count = 0u;    
    while(Sensor_config(TMAG3001STRAP,ContinuousMode) && count<8) { delay_ms(10); count++; }
    delay_ms(5);
//##(0)"BQ76952"累积电荷清零
    RESET_PASSQ_PROCESS();              //##(0)重置累积电荷积分和计时器 
    FG.LastPassQInt = 0u;               //##(0)历史累积清零
    FG.PassQInt = 0u;                   //##(0)当前累积清零
	regs.flags.NoComTmrEn = true;		//##(0)重新使能通讯无应答计时
    timeout = regs.time10ms;			//##(0)更新时间基点
	clearRegisters();					//##(0)将相关寄存器清零
}

/*###############################################################################################################################
# 函数名 : void DisplayProcess(void)                                                                                            #
# 功  能 : 显示进行                                                                                                             #
# 参  数 : NONE                                                                                                                 #
# 说  明 : NONE                                                                                                                 #
###############################################################################################################################*/
void AnimDisplayProcess(void) {
    uint8_t ID,i;
    static boolean LastChgDsgState = false;
	static boolean LastFualtPFStatus = false;
		   boolean commFaultShow = false;
//##【0】如果切换到充电则需要先关闭全部LED显示（只关闭一次显示）
    if(LastChgDsgState != regs.flags.ChgProc) {					//##(1)如果充电/放电切换则需要先关闭"LED"再切换到显示模式
        LastChgDsgState = regs.flags.ChgProc;					//##(1)更新模式
        clearFlaultRegs();                                      //##(1)清除和显示故障相关标志和变量
        Display_off();                                          //##(1)关闭显示
		FG.Last_rsoc = !FG.rsoc;                                //##(1)配置本次和上次不一致以便充电闪烁(容量变化更新显示) 
    }
//##【1】显示充电动画/放电动画(按钮按下显示容量),故障动画为最高优先级
    if(regs.FaultLive.u16 || IDTypeError || FualtPFStatus) {		//##(0)
		FaultShowUpdata &= ~(regs.LastFault != regs.FaultLive.u16);	//##(0)如果故障状态改变则需要重新显示故障状态
		FaultShowUpdata &= ~(LastFualtPFStatus != FualtPFStatus);	//##(0)状态改变则重新刷新故障显示
		regs.LastFault = regs.FaultLive.u16;						//##(0)更新故障比较基点							
		LastFualtPFStatus = FualtPFStatus;							//##(0)更新故障比较基点
		FG.Last_rsoc = !FG.rsoc;									//##(2)
		if(FaultShowUpdata == true) return;							//##(2)已经是更新完故障显示则退出
		commFaultShow |= (regs.FaultLive.u16 == 0x8000);	 		//##(0)如果是单纯通讯故障则设置为"1"	regs.FaultLive.COM = 1;
		commFaultShow &= ~(FualtPFStatus);							//##(0)其它故障则立即更新为其它故障显示(高优先级)
		if(commFaultShow == true)									//##(0)刷新故障显示 
			commFaultDisplay();										//##(0)刷新故障显示样式为通讯断连显示
		else
			FaultDisplay();											//##(0)刷新正常的故障显示样式
		FaultShowUpdata = true;										//##(2)设置已经更新故障动画显示
        return;
    }else{
		if(FaultShowUpdata) { Display_off(); }					//##(0)如果上次有播放动画则需要短暂关闭显示以免有残余其它颜色
        clearFlaultRegs();                                      //##(0)清除和显示故障相关标志和变量
    }
//##【2】如果接入的设备类型是外骨骼则由外骨骼操作"LED"显示    
    if(regs.DeviceType==ExoType && regs.flags.ReqAnimsDone && !regs.flags.ChgProc) {
		FG.Last_rsoc = !FG.rsoc;                                //##(1)配置本次和上次不一致以便充电闪烁(容量变化更新显示) 
		regs.flags.button1 = false;								//##(0)按钮按下显示容量禁止
		regs.flags.button2 = false;								//##(0)按钮按下显示容量禁止
		if(regs.AnimationID!=0) {
			regs.LastAnimationID = regs.AnimationID;			//##(0)保存当前动画ID以备切换下一组动画(没有中断切入)
			regs.LastAnimMR1 = regs.AnimMR1;					//##(0)保存当前动画元数据 1
			regs.LastAnimMR2 = regs.AnimMR2;					//##(0)保存当前动画元数据 2
		}
//##(0)如果无需中断切入下一组动画则需要等待播放完正在播放的动画,,否则立即切换到播放需要的动画	
		if(regs.AnimMR2.Enqueue == false){	
			if(regs.flags.AnimEn == true) return;				//##(0)如果没有播放完成则返回 "regs.flags.AnimEn=0"为播放完成动画组
			regs.AnimationID = regs.LastAnimationID;			//##(0)当前动画播放完成则切换到保存的动画组
			regs.AnimMR1 = regs.LastAnimMR1;					//##(0)恢复即将播放的动画元数据 1
			regs.AnimMR2 = regs.LastAnimMR2;					//##(0)恢复即将播放的动画元数据 2	
		}
		if(regs.AnimationID == 0UL) return;						//##(0)如果无任何动画播放则退出							
		Display_off();											//##(0)切入新动画前需要先关闭全部LED
        disable_interrupts(INT_TIMER3);                         //##(0)关闭定时器3中断 
        regs.flags.AnimEn = 0;                                  //##(0)停止刷新显示动画
        AnimationDisplay_Process(&Frame);                       //##(0)清除显示动画暂存
        regs.chain = regs.AnimMR1.Chain;                        //##(0)从第几段链开始播放
        ID = regs.AnimationID - 1;                              //##(0)由于数组是从0"开始故需要减去"1" 
        memcpy(Frame,LEDAnim[ID],sizeof(LEDAnim[ID]));          //##(0)将需要显示的全部帧复制到显示缓冲区中
//##(0)如果将要播放的动画需要加入全局淡出效果则在最后一帧补上淡出帧
		if(regs.AnimMR1.Fade == FadeOut) {									
			for(i=0; i<5 && Frame[i].mode!=0; i++);				//##(0)找到第一个空帧(mode==0)的帧
			#asm nop #endasm 
			if(i >= 2UL)  {													//##(0)如果当前动画的帧数小于1帧则退出
				Frame[i].mode = FADEM;										//##(0)渐变模式
				Frame[i].StartH = Frame[i-2].EndingH|Frame[i-2].StartH;		//##(0)起始色度为上一帧的结束色度
				Frame[i].StartS = Frame[i-2].EndingS|Frame[i-2].StartS;		//##(0)起始饱和度为上一帧的结束饱和度
				Frame[i].StartL = Frame[i-2].EndingL|Frame[i-2].StartL;		//##(0)起始亮度为上一帧的结束亮度
				Frame[i].Duration = regs.FadeOutDuration;					//##(0)淡出时长此值为全局淡出时长
			   (Frame[i-1].mode != BLINKM)?									//##(0)最后一帧是闪烁 ?
			   (Frame[i].LEDS = Frame[i-1].LEDS):							//##(0)如果不是闪烁则按照最后一帧淡出
			   (Frame[i].LEDS = Frame[i-2].LEDS);							//##(0)如果最后一帧是闪烁,则按照闪烁前一帧淡出
			}		
		}
//##(0)增补淡出帧完成		
		regs.LastAnimationID = 0UL;								//##(0)清除保存动画组ID
		regs.LastAnimMR1 = 0UL;									//##(0)清除保存动画元数据 1
		regs.LastAnimMR2 = 0UL;									//##(0)清除保存动画元数据 2
        regs.flags.AnimEn = 1;                                  //##(0)重新开启显示(显示新动画)
        enable_interrupts(INT_TIMER3);                          //##(0)恢复定时器中断
        regs.AnimationID = 0;                                   //##(0)动画ID清零以免频繁重复显示 
        return;
    }
//##【3】电池充电显示动画   
    else if(regs.flags.ChgProc == true) {                      
		regs.flags.button1 = regs.flags.button2 = 0;            //##(3)按钮显示容量禁
		if(FG.Last_rsoc == FG.rsoc) return;						//##(3)容量没有改变则退出
		ChargingDisplay(FG.rsoc);                               //##(3)容量有变化更新显示
		FG.Last_rsoc = FG.rsoc;									//##(3)保存当前值作为下次比较基点
    }
//##【4】待机模式【按钮按下显示故障】    
    else{
        FG.Last_rsoc = !FG.rsoc;
        if(regs.flags.button1 || regs.flags.button2) {
            regs.flags.button1 = regs.flags.button2 = 0;        //##(4)按钮中断标志清零
            StbyDisplay(FG.rsoc);                               //##(4)刷新显示
        }  
    }
}

/*###############################################################################################################################
# 函数名 :  void NextAction_Process(void)                                                                                       #
# 功  能 :  执行动作                                                                                                            #
# 参  数 :  NONE                                                                                                                #
# 说  明 : 【 0=无操作/1=关机/2=引导程序/3=请求读取/4=清除永久故障寄存器/5=请求读取电池序列号】                                 #
###############################################################################################################################*/
void NextAction_Process(void) {
	uint8_t buff;
//##(0)如果"Exo"没有请求动作则返回
    if(regs.NextAction == 0u) return;
//##(0)执行相应动作
    switch(regs.NextAction) {
        case PowerOff_cmd:
			 regs.flags.RunMode = MODE_SHUTDOWN;	//##(0)运输"SHUTDOWN"
             break;
        case brightness_cmd:						//##(0)"EXO"请求全局亮度  
			 regs.flags.ReqBright = true;			//##(0)使能发送全局亮度数据
             break;
        case clearfault_cmd:						//##(0)清除持久故障命令
			 FualtPFStatus = false;
			 buff = 0u;
			 regs.FaultHistory.u16 = 0u;            //##(0)
			 regs.LastFaultPersist.u16 = 0UL;		//##(0)
			 writeEeprom(eeprom_FaultPersist,(U8 *)&regs.FaultHistory.u16, 2UL);	//##(0)保存到"EEPROM"中
			 writeEeprom(eeprom_FulatPF,(U8 *)&buff, 1UL);							//##(0)保存到"EEPROM"中
             break;
        case serialreq_cmd:							//##(0)"EXO"请求序列号
             regs.flags.RequestSN = true;           //##(0)使能发送序列号数据
             break;
    }
//##(0)清零下一动作以免重复执行    
    regs.NextAction = 0;   
} 

/*###############################################################################################################################
# 函数名 : boolean readEEPROM(uint8_t reg, uint8_t *buffer, uint8_t Length)                                                     #
# 功  能 : 读 EEPROM (写多个字节/单个字节)                                                                                      #                                                                       																								*
###############################################################################################################################*/
void read_information_eeprom(void) {
    uint8_t buffer[16];
   uint16_t BUFF;
//##(0)从"EEPROM"中读取保存的序列号   
    readEeprom(eeprom_SN, buffer, sizeof(buffer));         
    #asm nop #endasm
    if(memchr(buffer,0xFF,sizeof(buffer))!= NULL) {         //##(0)如果读取的数组中有一个数据是: 0xFF(没有写过)
       memset(FG.SN, '0', 16);                              //##(0)"EEPROM"没有写过序列号则序列号为全"0"
    }else{
       memcpy(FG.SN, buffer, 16);                           //##(0)读取到的序列号更新到序列号寄存器中
    }
//##(0)读取"PF"状态
	if(readEeprom(eeprom_FulatPF, buffer, 1u) == false) {
		FualtPFStatus = (buffer[0]==0xAA)? 1:0;				//##(0)如果标识==AA则为曾经PF过
	}
//##(0)读取循环放电次数
    readEeprom(eeprom_cyc,(U8 *)&BUFF, sizeof(BUFF));      
    FG.CCC = (BUFF != 0xffff)? BUFF:0U;                      //##(0)如果EEPROM是没有保存过则设置为0
//##(0)读取放电累积容量,关机之后开机需要这个数据
    readEeprom(eeprom_DsgCnt,(U8 *)&BUFF,sizeof(BUFF));
    ulDsgCC = (buffer <= E2DesignCapacity)? BUFF:0U;		//##(0)如果读取的累积容量超过设计容量则清零
//##(0)读取保存在EEPROM中的历史故障
	readEeprom(eeprom_FaultPersist,(U8 *)&BUFF, sizeof(BUFF));  //##(0)
    regs.FaultHistory.u16 = (BUFF==0xffff)? 0:BUFF;  
//##(0)设计容量    
    FG.DesignCapacity = E2DesignCapacity;                   //##(0)	
}

/*###############################################################################################################################
# 函数名 :  void reg_initialize(void)                                                                                           #
# 功  能 :  变量初始化                                                                                                          #
# 参  数 :  NONE                                                                                                                #
# 说  明 :  NONE                                                                                                                #
###############################################################################################################################*/
void reg_initialize(void) {
	regs.FadeOutDuration = 250;			//##(0)淡出默认时间 = 250ms
	regs.FadeInDuration  = 250;			//##(0)淡入默认时间 = 250ms
    FG.BMSHW_ID.u16 = 0x0001;			
    FG.BMSHW_Ver.u16 = 0x0002;
    FG.MajFW.u16 = MajFW;				//##(0)主版本
    FG.MinFW.u16 = MinFW;               //##(0)次版本
    FG.PatFW.u16 = PatFW;               //##(0)补充版本
}

/*###############################################################################################################################
# 函数名 :  void FaultControlFET_Process(void)                                                                                  #
# 功  能 :  故障则关闭FET,没有故障则开启FET                                                                                     #
# 参  数 :  NONE                                                                                                                #
# 说  明 :  NONE                                                                                                                #
###############################################################################################################################*/
void FaultControlFET_Process(void) {
    static uint16_t timeout;
    uint8_t FET_STATUS;  
	uint16_t FaultState;
//##(0)1秒钟时间没到则退出    
    if((regs.time10ms-timeout)<1000/10) return;
    timeout = regs.time10ms;
//##(0)读取"FET"状态,读取失败则返回    
    if(i2c_GetsData(bq76952,0x7F,&FET_STATUS,sizeof(FET_STATUS))) return;   
//##(0)保留指示"CHG/DSG FET"的状态标志    
    FET_STATUS &= 0b00000001;  
	FaultState = regs.FaultLive.u16 & 0x7fff;		//##(0)屏蔽通讯故障
//##(0)控制"FET"	
    if((FaultState != 0U && regs.flags.ChgProc && SafetyStatusB.OTC) || FualtPFStatus==true) {
        if(FET_STATUS == 0b00000000)  return;       //##(0)如果已经关闭则返回,无需重复操作
        bq76952_writeWord(AllFETOFF);
    }else if(regs.flags.RunMode==MODE_WORK) {      
        if(FET_STATUS == 0b00000001)  return;       //##(0)如果已经开启则返回,无需重复操作
        bq76952_writeWord(AllFETON);
    }
} 

/*###############################################################################################################################
# 函数名 :  void configErrorCode_Process(void)                                                                                  #
# 功  能 :  根据故障类型配置故障代码                                                                                            #
# 参  数 :  NONE                                                                                                                #
# 说  明 :  NONE                                                                                                                #
###############################################################################################################################*/
void configErrorCode_Process(void) {
//##(0)如果没有故障则退出
    if(regs.FaultLive.u16==0U) return;
//##(0)如果是通讯故障则退出(不上报没有意义)
    if(regs.FaultLive.COM == true) return;
//##(0)先将故障代码清零    
    regs.ErrorCode = 0u;
//##(0)根据故障类型配置故障代码,持久故障为最高优先级
	regs.ErrorCode = regs.FaultLive.u16;
}

/*###############################################################################################################################
# 函数名 :  void AccessID_OperationMode(void)                                                                                   #
# 功  能 :  根据接入的ID电阻执行何种模式                                                                                        #
# 参  数 :  NONE                                                                                                                #
# 说  明 :  NONE                                                                                                                #
###############################################################################################################################*/
void AccessID_OperationMode(void) {
//##(0)调用测量接入"ID"电阻	
	MeasureID_Process();	
//##(0)保留和"regs.flags.IDType"一样有效位数		
	regs.LastIDType &= 0b00000111;						
	if(regs.LastIDType == regs.flags.IDType && regs.LastIDType!=0) return;	//##(0)如果接入的ID类型没有变化则返回	
//##(0)上报事件"MB_REG_BAT_InsertionDetection = 145 "
	regs.Insertion.u16 = regs.flags.IDType;			//##(0)更新插入ID类型
	TransmitEventData(145, regs.Insertion.u16);     //##(0)调用"DMA"发送数据 
//##(0)设置相关变量和标志	
	IDTypeError = false;							//##(0)ID 出错清除
	regs.NoCommTimeout = 0u;						//##(0)由于模式切换需要将通讯超时计时器清零
//##(0)根据插入的ID电阻类型执行相应工作模式
	switch(regs.flags.IDType) {
		case IDEXO:                                 //##(0)接入的是"EXO"设备需要播放开机动画
             bq76952_writeWord(ExitDeepSleep);      //##(0)退出深度睡眠模式
             delay_ms(2);
			 if(FualtPFStatus==false) {				//##(0)
				bq76952_writeWord(AllFETON);        //##(0)无"PF"故障开启充放电FET命令,否则保持关闭状态
				PowerStatusDisplay(powerOn);        //##(0)无"PF"故障执行开机显示
			 }else{
				FaultShowUpdata = false;			//##(0)"PF"故障则显示故障  
			 }
			 bPowerOffAnimDone = false;				//##(0)播放开机动画则需要将播放过关机动画标志清零
			 config_Hall();                         //##(0)配置霍尔传感器【每次插入都初始化一次】
             regs.flags.RunMode = MODE_WORK;        //##(0)设置为工作模式
			 regs.flags.NoComTmrEn = true;			//##(0)启动通讯无应答超时计时【这又在这模式下开启通讯超时计时】
             break;                                             
        case IDCHG:                                 //##(0)不播放开机动画
             bq76952_writeWord(ExitDeepSleep);      //##(0)退出深度睡眠模式
             delay_ms(2);
			 if(FualtPFStatus==false) {
				bq76952_writeWord(AllFETON);        //##(0)无"PF"故障开启充放电FET命令
			 }else{
				FaultShowUpdata = false;			//##(0)"PF=1"则显示故障 
			 }
             regs.flags.RunMode = MODE_WORK;        //##(0)设置为工作模式
             break;
        case IDRMV:
			 clearRegisters();						//##(0)清除相关寄存器和标志
             bq76952_writeWord(AllFETOFF);          //##(0)关闭充放电FET
			 if(regs.LastIDType == IDEXO) {			//##(0)如果从"EXO"脱离则需要播放关机动画
				PowerStatusDisplay(powerOff);		//##(0)执行关机机显示
			 }else if(regs.LastIDType==IDCHG) {									
				regs.flags.button1 = 1;				//##(0)是从充电器脱离则播放当前容量
			 }
             regs.flags.RunMode = MODE_SLEEP;       //##(0)进入睡眠模式
             break;
        case IDERR:
             IDTypeError = true;					//##(0)设置显示故障动画 
             bq76952_writeWord(AllFETOFF);          //##(0)关闭充放电FET命令
             regs.flags.RunMode = MODE_SLEEP;       //##(0)进入睡眠模式【播放完故障动画则睡眠】 
             break;
	}
	regs.LastIDType = regs.flags.IDType;			//##(0)保存当前状态作为基点以备下次比较【即作为历史记录保存】
}

/*###############################################################################################################################
# 函数名 :  void Keyboard_Process(void)																		       #
# 功  能 :  主函数                                                                                                              #
# 参  数 :  NONE                                                                                                                #
# 说  明 :  NONE                                                                                                                #
###############################################################################################################################*/
void Keyboard_Process(void) {
//##(0)如果按钮同时按下则使能重新设定ID状态判断
	switch(regs.keyCurrState) {
		case KEY_BOTH_LONG:											//##(0)同时长按双键	
			 if(regs.flags.IDType==IDEXO && !bPowerOffAnimDone) {	//##(0)如果当前接入的是"EXO"
				PowerStatusDisplay(powerOff);						//##(0)执行关机机显示
				regs.flags.RunMode = MODE_SLEEP;					//##(0)进入睡眠模式
				bPowerOffAnimDone = true;							//##(0)设置已经播放过关机动画
			 }else{
				regs.LastIDType = 255;						//##(0)重新进行接入的"ID"判断
			 }
			 break;
		case KEY1_SHORT:									//##(0)短按
		case KEY2_SHORT:	
			 if(FaultShowUpdata && !regs.flags.AnimEn) 
				FaultShowUpdata = false;                    //##(0)如果当前是故障显示暂停则按下按钮则重新激活故障显示  
			 else
				regs.flags.button1 = true;                  //##(0)没有故障则按钮"1"按下触发中断标志 = 1
			 break;
	}
//##(0)将按钮状态设置为	KEY_NONE,以免重复执行
	regs.keyCurrState = KEY_NONE;	
}

/*###############################################################################################################################
# 函数名 :  void FaultProcessTask(void)                                                                                         #
# 功  能 :  变量初始化                                                                                                          #
# 参  数 :  NONE                                                                                                                #
# 说  明 :  NONE                                                                                                                #
###############################################################################################################################*/
void CheckBatteryState_Process(void) {
    boolean FaultFlagBit;
	static uint16_t LAST_BSTATE = 0;
	static uint16_t timeout;
//##(0)100毫秒检查一次状态是否改变 ? 	
	if((regs.time10ms-timeout)<200/10) return;            
    timeout = regs.time10ms; 
//##(0)合并故障状态
	FaultFlagBit = false;
	FaultFlagBit |= ((regs.FaultLive.u16 & 0xFFFE)!=0);
//##(0)如果充电重则返回
	     if(FaultFlagBit== true) FG.BSTATE = ERR_STATE;			//##(0)电池状态/错误[最高优先级]
	else if(FG.b.CHGING == true) FG.BSTATE = CHG_STATE;			//##(0)电池状态/充电中	
	else if(FG.b.DSGING == true) FG.BSTATE = DSG_STATE;			//##(0)电池状态/放电中
	else if(FG.AlarmStatus.CB)   FG.BSTATE = BAL_STATE;			//##(0)电池状态/均衡中
	else						 FG.BSTATE = NULL_STATE;		//##(0)电池状态/空闲
//##(0)如果状态没有改变则返回	
	if(LAST_BSTATE == FG.BSTATE) return;  
//##(0)如果串口忙则退出，下一次循环发送	
	if(regs.Request.UsrtBusy) return;	
    TransmitEventData(MB_REG_BAT_STATE,FG.BSTATE);				//##(0)调用"DMA"发送数据 
	LAST_BSTATE = FG.BSTATE;
}
  
/*###############################################################################################################################
# 函数名 :  void main(void)                                                                                                     #
# 功  能 :  主函数                                                                                                              #
# 参  数 :  NONE                                                                                                                #
# 说  明 :  NONE                                                                                                                #
###############################################################################################################################*/
#zero_ram 
void main(void) {
    U1MODE &= 0b011111111;                  //##(0)先清空串口"FIFO"缓冲区,以免缓冲区有残余影响接收
    #asm nop #endasm 
    #asm nop #endasm                        //##(0)UART重新启动，FIFO 处于清空后的初始状态
    U1MODE |= 0b100000000;                  //##(0)初始化
    #asm nop #endasm 
    delay_ms(2000);                         //##(0)延时200毫秒
    config_module();                        //##(0)配置功能模块
    reg_initialize();                       //##(0)初始化变量
    read_information_eeprom();              //##(0)读取电池序列号
    config_Hall();                          //##(0)配置霍尔传感器
    InitializeCapacity();                   //##(0)初始化电池容量(根据"OCV"计算当前电池容量)
    InitializeCapacity();                   //##(0)初始化电池容量(根据"OCV"计算当前电池容量)
	regs.FaultLive.u16 = 0;					//##(0)临时故障清零
    FG.Last_rsoc = !FG.rsoc;                //##(0)初始化历史容量和当前容量必须设置为不一致(以免上电同时为"0"导致无法刷新充电显示)
    FG.LastTemperature = FG.Temperature;    //##(0)当前温度作为基点,以备比较
    #asm nop #endasm
//##(0)锟斤拷锟斤拷      
	while(TRUE) {
		restart_wdt();                      //##(0)复位看门狗定时器 
		AccessID_OperationMode();			//##(0)根据接入的ID电阻执行何种模式
        Keyboard_Process();					//##(0)执行按键操作进程
		AnimDisplayProcess();               //##(0)显示进行
		BmsToExoComm_Process();             //##(0)电池和外骨架通讯
		commands_Process();                 //##(0)执行串口命令进程
		MsgPrintf_Process();                //##(0)信息打印进程【调试】
		NextAction_Process();               //##(0)执行Exo请求的下一步动作
		BMS_GaugeManage_Task();             //##(0)电池电量计任务(阻抗跟踪)
		CheckBatteryState_Process();		//##(0)检查电池状态进程
        FaultControlFET_Process();          //##(0)FET控制近进程 
        configErrorCode_Process();          //##(0)根据故障类型配置故障代码进程   
        SensorFOLD_Process();				//##(0)折叠/展开霍尔传感器进程
        SensorSTRAP_Process();              //##(0)绑带传感器进程
        microcontroller_sleep();			//##(0)判断是否进入睡眠模 � 
    }
}

