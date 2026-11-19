/*###############################################################################################################################
 # 文件名称 ： u80711R01_BQ76952_H                                                                                              #
 # 公司名称 :  TOTEX Technology, Inc.                                                                                           #
 # 芯片型号 ： PIC24FJ128GA302                                                                                                  #
 # 编译工具 :  ccs compiler v5.118                                                                                              #
 # 作    者 :  BenZhang                                                                                                         #
 # 编写日期 :  2025/11/10                                                                                                       #
 # 版    本 :  v1.00                                                                                                            #
 ##############################################################################################################################*/
#ifndef APP_COMMUNICATION_H
#define	APP_COMMUNICATION_H
/*###############################################################################################################################
# 包含文件                                                                                                                      #
###############################################################################################################################*/
#include "app_config.h"
#include "apps_drive.h"
#include "app_Display.h"
#include "app_bq76952.h"
/*###############################################################################################################################
# 声明结束                                                                                                                      #
###############################################################################################################################*/
#ifdef	__cplusplus
extern "C"
{
#endif
/*###############################################################################################################################
# 函数声明                                                                                                                      #
###############################################################################################################################*/    
void TransmitRequestData(bufferu16 StartAddr, bufferu16 Quantity);
void TransmitEventData(bufferu16 StartAddr, bufferu16 data);
void StartupRequestInfo_Process(void);
void RequestAnims_process(void);
void PeriodicPolling_500ms(void);
void Timer50ms_transmit_debug(void);

/*###############################################################################################################################
# 函数名 : void StartupRequestInfo_Process(void)                                                                                #
# 功  能 : 电池上电请求设备信息（表明设备是否存在）                                                                             #
# 参  数 : NONE                                                                                                                 #
# 说  明 : regs.flags.IsDeviceInfo = 1 为从机设备存在                                                                           #
###############################################################################################################################*/
void TransmitRequestData(bufferu16 StartAddr, bufferu16 Quantity) {
    uint8_t transmit[16] = {0};
  bufferu16 crc16;
//##(0)格式化发送数据包
    transmit[0] = ServerAddress;                    //##(0)从机地址
    transmit[1] = MB_FC_READ_REGISTERS;             //##(0)功能代码,读取保持寄存器或模拟输出量
    transmit[2] = StartAddr.u8[1];                  //##(0)起始地址高字节
    transmit[3] = StartAddr.u8[0];                  //##(0)起始地址低字节
    transmit[4] = Quantity.u8[1];                   //##(0)待读寄存器个数高字节
    transmit[5] = Quantity.u8[0];                   //##(0)待读寄存器个数低字节
    crc16.u16 = crc16_modbus(&transmit,6);          //##(0)计算校验码
    transmit[6] = crc16.u8[0];                      //##(0)校验码低字节
    transmit[7] = crc16.u8[1];                      //##(0)校验码高字节
//##(0)源地址(buf)自增/目的地址(U1TXREG)固定/单次发送/启动"DMA"传输(强制立即发送)/目的地址(送到串口)/源地址(从内存取)/发送字节数
//##(0)发送数据前切换到Tx模式需要延时(否则会丢失最起始的字节),发送后切换到Rx模式也需要延时(否则丢失最后字节)
    transmission;
    delay_us(100); 
    dma_start(1,DMA_INC_SOURCE_ADDR | DMA_DEST_ADDR_UNCHANGED | DMA_ONE_SHOT | DMA_FORCE_NOW, getenv("SFR:U1TXREG"),transmit,8);  
    delay_us(500);
    receiver; 
//##(0)保存发送的数据包相关信息(以备从机应答比较)
    regs.Request.StartAddress = StartAddr.u16;      //##(0)发送到从机的地址
    regs.Request.Quantity = Quantity.u16;           //##(0)发送到从机的请求读取寄存器数量
    regs.Request.Function = MB_FC_READ_REGISTERS;   //##(0)发送到从机的功能码
    regs.Request.UsrtBusy = true;                   //##(0)已经发送完成则将等待标志设置为"1"（等待从机应答阶段）       
}
/*###############################################################################################################################
# 函数名 : void TransmitEventData(void)                                                                                         #
# 功  能 : 发送单个寄存器数据(功能代码 = 0x06)                                                                                  #
# 参  数 : NONE                                                                                                                 #
# 说  明 : NONE                                                                                                                 #
###############################################################################################################################*/
void TransmitEventData(bufferu16 StartAddr, bufferu16 data) {
    bufferu16 crc16;
      uint8_t transmit[16]={0}; 	  
//##(0)准备好需要发送的数据
    transmit[0] = ServerAddress;                    //##(0)第一个字节为主机地址
    transmit[1] = MB_FC_WRITE_REGISTER;             //##(0)功能代码（写单个寄存器数据）
    transmit[2] = StartAddr.u8[1];                  //##(0)起始地址高字节 
    transmit[3] = StartAddr.u8[0];                  //##(0)起始地址低字节
    transmit[4] = data.u8[1];                       //##(0)数据的高字节  
    transmit[5] = data.u8[0];                       //##(0)数据的低字节
//##(0)计算出校验码    
    crc16 = crc16_modbus(&transmit,6);
    transmit[6] = make8(crc16,0);                   //##(0)校验码低字节
    transmit[7] = make8(crc16,1);              
//##(0)源地址(buf)自增/目的地址(U1TXREG)固定/单次发送/启动"DMA"传输(强制立即发送)/目的地址(送到串口)/源地址(从内存取)/发送字节数
//##(0)发送数据前切换到Tx模式需要延时(否则会丢失最起始的字节),发送后切换到Rx模式也需要延时(否则丢失最后字节)
    transmission;
    delay_us(100); 
    dma_start(1,DMA_INC_SOURCE_ADDR | DMA_DEST_ADDR_UNCHANGED | DMA_ONE_SHOT | DMA_FORCE_NOW, getenv("SFR:U1TXREG"),transmit,8);  
    delay_us(500);
    receiver; 
//##(0)保存发送的数据包相关信息(以备从机应答比较)
    regs.Request.StartAddress = StartAddr.u16;      //##(0)发送到从机的地址
    regs.Request.Function = MB_FC_WRITE_REGISTER;   //##(0)发送到从机的功能码
    regs.Request.UsrtBusy = true;                   //##(0)已经发送完成则将等待标志设置为"1"（等待从机应答阶段）          
}
/*###############################################################################################################################
# 函数名 : void StartupRequestInfo_Process(void)                                                                                #
# 功  能 : 电池上电请求设备信息（表明设备是否存在）                                                                             #
# 参  数 : NONE                                                                                                                 #
# 说  明 : regs.flags.IsDeviceInfo = 1 为从机设备存在                                                                           #
###############################################################################################################################*/
void StartupRequestInfo_Process(void) {
    static uint16_t timeout;
          bufferu16 StartAddress,Quantity;		  
//##(0)如果设备类型不是"EXO"或者请求信息完成则退出
    if(regs.DeviceType == ExoType && regs.flags.ReqInfoDone == false) {
        if(regs.time10ms-timeout<500/10) return;            //##(0)500ms请求一次              
        timeout = regs.time10ms;                            //##(0)更新时间比较基点
        StartAddress.u16 = MB_REG_EXO_VERSION_MAJ;          //##(0)起始寄存器地址 1 -- 11
        Quantity.u16 = 11;                                  //##(0)待读寄存器个数 
        TransmitRequestData(StartAddress.u16,Quantity.u16); //##(0)发送请求     
    } 
}
/*###############################################################################################################################
# 函数名 : void RequesDeviceType_Process(void)                                                                                  #
# 功  能 : 请求设备类型                                                                                                         #
# 参  数 : NONE                                                                                                                 #
# 说  明 : 设备存在则发送请求动画数组                                                                                           #
###############################################################################################################################*/
void RequesDeviceType_Process(void) {
    static uint16_t timeout;
    bufferu16 StartAddress,Quantity;
//##(0)如果设备不是外骨骼则重新请求设备信息,是外骨骼并且请求完成则不再请求 
    if(regs.DeviceType != ExoType) {
        if(regs.time10ms-timeout<500/10) return;            //##(0)500ms请求一次
        StartAddress.u16 = MB_REG_DEVICE_TYPE;              //##(0)请求设备类型
        Quantity.u16 = 0x0001;                              //##(0)待读1个寄存器
        TransmitRequestData(StartAddress.u16,Quantity.u16); //##(0)发送请求数据包,并设置等待应答"regs.Request.waiting = 1" 
    }
    timeout = regs.time10ms;                                //##(0)更新超时时间基点
}
/*###############################################################################################################################
# 函数名 : void RequestAnims_process(void)                                                                                      #
# 功  能 : 请求动画数组                                                                                                         #
# 参  数 : NONE                                                                                                                 #
# 说  明 : 设备存在则发送请求动画数组                                                                                           #
###############################################################################################################################*/
void RequestAnims_Process(void) {
    static uint16_t ReqAnimsIndex = 0;
    static uint16_t timeout;
          bufferu16 StartAddress,Quantity;
//##(0)如果设备不是"EXO" || 已经请求动画数组 || 动画请求数量为"0" || 超出数量(最大20组动画)则返回
    if(regs.flags.ReqAnimsDone || regs.DeviceType != ExoType || regs.AnimQty<=0u || regs.AnimQty>AnimQy) { 
       ReqAnimsIndex = regs.recvAnimCnt = 0u; return;
    }
//##(0)如果请求处于等待过程,500毫秒后从机没有应答则重新逐条命令请求	  
    if(regs.Request.UsrtBusy==true) {
        if((regs.time10ms-timeout)<200/10) return;
        regs.Request.UsrtBusy = false;                      //##(0)等待标志清零(重新发送请求)
        ReqAnimsIndex = 0u;                                 //##(0)请求索引重新指向起始 
	regs.recvAnimCnt = 0u;                              //##(0)接收动画组计数器清零
    }    
    output_bit(pin_b5,0);                                   //##(0)测试接受完全部动画开始【拉高电平】
    timeout = regs.time10ms;                                //##(0)更新超时时间    
//##(0)没有完成则逐组动画请求
    StartAddress.u16 = 256 + ReqAnimsIndex*40;              //##(0)起始寄存器地址
    regs.ReqAnimsAddress = StartAddress.u16;
    Quantity.u16 = 40u;                                     //##(0)待读寄存器个数 
    TransmitRequestData(StartAddress.u16,Quantity.u16);     //##(0)发送请求数据
    ReqAnimsIndex++;                                        //##(0)准备下一组请求
}
/*###############################################################################################################################
# 函数名 : void RequestSN_Process(void)                                                                                         #
# 功  能 : 电池从外骨骼 128–135 读序列号(请求序列号)                                                                           #
# 参  数 : NONE                                                                                                                 #
# 说  明 : 设备存在则发送请求动画数组                                                                                           #
###############################################################################################################################*/
void RequestSN_Process(void) { 
    bufferu16 StartAddress,Quantity;
//##(0)如果通讯忙则退出
    if(regs.Request.UsrtBusy || !regs.flags.RequestSN) return;
//##(0)配置数据    
    StartAddress.u16 = MB_REG_BAT_SerialNumber;             //##(0)起始寄存器地址
    Quantity.u16 = 8;                                       //##(0)待读寄存器个数
//##(0)发送请求数据包,并设置等待应答"regs.Request.waiting = 1" 
    TransmitRequestData(StartAddress.u16,Quantity.u16);     //##(0)   
//##(0)清除请求使能标志
    regs.flags.RequestSN = false;
}
/*###############################################################################################################################
# 函数名 : void StartupTransmitInfo_Process(void)                                                                               #
# 功  能 : 电池上电后发送本机基本信息                                                                                           #
# 参  数 : NONE                                                                                                                 #
# 说  明 : 全部请求完成后才能发送基本信息                                                                                       #
###############################################################################################################################*/
void StartupTransmitInfo_Process(void) {
    bufferu16 crc16,StartAddr,Quantity;
      uint8_t transmit[64]={0};
//##(0)如果已经发送过数据给从机或者通讯忙则返回    
    if(regs.flags.TransmitInfo || regs.DeviceType != ExoType) return;     
//##(0)等待串口空闲
    if(regs.Request.UsrtBusy) return;  	  
//##(0)准备好数据	  
    StartAddr.u16 = MB_REG_BAT_SerialNumber;        //##(0)从地址128开始写到地址135结束
     Quantity.u16 = 20;                             //##(0)一共需要写20个寄存器数据
//##(0)格式化需要发送的数据        
    transmit[0] = ServerAddress;                    //##(0)第一个字节为主机地址
    transmit[1] = MB_FC_WRITE_MULTIPLE_REGISTERS;   //##(0)功能代码（写多个寄存器数据）
    transmit[2] = StartAddr.u8[1];                  //##(0)起始地址高字节 
    transmit[3] = StartAddr.u8[0];                  //##(0)起始地址低字节
    transmit[4] = Quantity.u8[1];                   //##(0)数据的高字节  
    transmit[5] = Quantity.u8[0];                   //##(0)数据的低字节 
    transmit[6] = (uint8_t)(Quantity.u16*2);        //##(0)发送的有效字节数   
    #asm nop #endasm
    memcpy(&transmit[7],FG.SN,16u);                 //##(0)电池序列号,地址 128~135 共8个寄存器16个字节（ascii）
//##(0)高字节在前低字节灾后    
    transmit[23]= FG.MajFW.u8[1];                   //##(0)电池固件版本(主) , 地址:136~138共3个寄存器6个字节
    transmit[24]= FG.MajFW.u8[0];              
    transmit[25]= FG.MinFW.u8[1];                   //##(0)电池固件版本(次)
    transmit[26]= FG.MinFW.u8[0];  
    transmit[27]= FG.PatFW.u8[1];                   //##(0)电池固件版本(补丁)            
    transmit[28]= FG.PatFW.u8[0];       
    transmit[29]= FG.BMSHW_ID.u8[1];                //##(0)硬件版本(厂商ID), 地址:139~140共2个寄存器4个字节 
    transmit[30]= FG.BMSHW_ID.u8[0];           
    transmit[31]= FG.BMSHW_Ver.u8[1];               //##(0)硬件版本(版本号)
    transmit[32]= FG.BMSHW_Ver.u8[0];           
    transmit[33]= make8(FG.StateOfHealth,1);        //##(0)电池健康度,地址:141共1个寄存器2个字节
    transmit[34]= make8(FG.StateOfHealth,0); 
    transmit[35]= make8(FG.CCC,1);                  //##(0)充电循环次数,地址:142共1个寄存器2个字节
    transmit[36]= make8(FG.CCC,0);
    transmit[37]= make8(FG.DCC,1);                  //##(0)放电循环次数,地址:143共1个寄存器2个字节                   
    transmit[38]= make8(FG.DCC,0);
    transmit[39]= make8(FG.BSTATE,1);               //##(0)电池状态,地址:144共1个寄存器2个字节 
    transmit[40]= make8(FG.BSTATE,0);        
    transmit[41]= make8(regs.Insertion.u16,1);      //##(0)插入检测,地址:145共1个寄存器2个字节 
    transmit[42]= make8(regs.Insertion.u16,0);        
    transmit[43]= make8(regs.FaultLive.u16,1);      //##(0)电池故障状态(实时),146共1个寄存器2个字节 
    transmit[44]= make8(regs.FaultLive.u16,0);         
    transmit[45]= make8(regs.FaultHistory.u16,1);   //##(0)电池故障状态(持续),147共1个寄存器2个字节 
    transmit[46]= make8(regs.FaultHistory.u16,0);   
//##(0)计算出校验码    
    crc16 = crc16_modbus(&transmit,47);
    transmit[47] = make8(crc16,0);                  //##(0)校验码低字节
    transmit[48] = make8(crc16,1);                  
//##(0)源地址(buf)自增/目的地址(U1TXREG)固定/单次发送/启动"DMA"传输(强制立即发送)/目的地址(送到串口)/源地址(从内存取)/发送字节数
//##(0)发送数据前切换到Tx模式需要延时(否则会丢失最起始的字节),发送后切换到Rx模式也需要延时(否则丢失最后字节)
    transmission;
    delay_us(100); 
    dma_start(1,DMA_INC_SOURCE_ADDR | DMA_DEST_ADDR_UNCHANGED | DMA_ONE_SHOT | DMA_FORCE_NOW, getenv("SFR:U1TXREG"),transmit,49);  
    delay_ms(2);
    receiver; 
//##(0)保存发送的数据包相关信息(以备从机应答比较)
    regs.Request.StartAddress = StartAddr.u16;      //##(0)发送到从机的地址
    regs.Request.Function = MB_FC_WRITE_REGISTER;   //##(0)发送到从机的功能码
    regs.Request.UsrtBusy = true;                   //##(0)已经发送完成则将等待标志设置为"1"（等待从机应答阶段） 
    regs.flags.TransmitInfo = 1;                    //##(0)设置已经发送过标志 
}
/*###############################################################################################################################
# 函数名 : void ButtonEventProcess(void)                                                                                        #
# 功  能 : 按钮事件发送状态（前提是设备有接入）                                                                                 #
# 参  数 : NONE                                                                                                                 #
# 说  明 : NONE                                                                                                                 #
###############################################################################################################################*/
void ButtonEvent_Process(void) {
    bufferu16 StartAddr, Data;      
//##(0)按钮没有状态则退出
    if(regs.keyState==KEY_NONE) return;
//##(0)配置数据并发送    
    StartAddr.u16 = MB_REG_BAT_BUTTON_PRESSED;      //##(0)起始地址,范围:150
       Data.u8[1] = 0x00;                           //##(0)由于按钮状态时一个字节,故高字节填充"0"
       Data.u8[0] = regs.keyState;                  //##(0)按钮状态
    TransmitEventData(StartAddr.u16, Data.u16);     //##(0)调用"DMA"发送数据 
//##(0)发送完按钮事件后将按钮状态清零以免重复发送
    regs.keyState = 0;
}
/*###############################################################################################################################
# 函数名 : void FaultEventTransmit(void)                                                                                        #
# 功  能 : 电池故障事件发送数据（前提是设备有接入）                                                                             #
# 参  数 : NONE                                                                                                                 #
# 说  明 : NONE                                                                                                                 #
###############################################################################################################################*/
void FaultEvent_Process(void) {
    static uint16_t lastFaultLive = 0u;
           uint16_t buffer;
          bufferu16 StartAddr,Quantity,crc16;   
            uint8_t transmit[16]={0}; 
//##(0)如果没有实时故障或者故障和上次不一致则退出(无需发送事件) 
    if(regs.FaultLive.u16==0U || lastFaultLive == regs.FaultLive.u16) return;
//##(0)有故障则将实时故障保存下来作为下次比较
    lastFaultLive = regs.FaultLive.u16;
//##(0)如果通讯正忙则返回            
    if(regs.Request.UsrtBusy) return;
//##(0)读取保存在EEPROM中的记录
    readEeprom(eeprom_FaultPersist,(U8 *)&buffer, sizeof(buffer));      
    regs.FaultHistory.u16 = buffer;  
//##(0)配置起始地址                  
    StartAddr.u16 = MB_REG_BAT_FaultStatus;         //##(0)故障地址 146/147 共
    Quantity.u16  = 2;                              //##(0)发送2个寄存器数据,每个寄存器占用2个字节数据    
//##(0)准备好需要发送的数据 
    transmit[0] = ServerAddress;                    //##(0)第一个字节为主机地址
    transmit[1] = MB_FC_WRITE_MULTIPLE_REGISTERS;   //##(0)功能代码【写多个寄存器】
    transmit[2] = StartAddr.u8[1];                  //##(0)起始地址高字节 
    transmit[3] = StartAddr.u8[0];                  //##(0)起始地址低字节
    transmit[4] = Quantity.u8[1];                   //##(0)起始地址高字节 
    transmit[5] = Quantity.u8[0];                   //##(0)起始地址低字节
    transmit[6] = (uint8_t)(Quantity.u16*2);        //##(0)发送的有效字节数
    #asm nop #endasm      
    transmit[7] = make8(regs.FaultLive.u16,1);      //##(0)电池故障状态(实时),146共1个寄存器2个字节 
    transmit[8] = make8(regs.FaultLive.u16,0);         
    transmit[9] = make8(regs.FaultHistory.u16,1);   //##(0)电池故障状态(持续),147共1个寄存器2个字节 
    transmit[10]= make8(regs.FaultHistory.u16,0);   
//##(0)计算出校验码    
    crc16 = crc16_modbus(&transmit,11);
    transmit[11] = make8(crc16,0);                  //##(0)校验码低字节
    transmit[12] = make8(crc16,1);                  
//##(0)源地址(buf)自增/目的地址(U1TXREG)固定/单次发送/启动"DMA"传输(强制立即发送)/目的地址(送到串口)/源地址(从内存取)/发送字节数
//##(0)发送数据前切换到Tx模式需要延时(否则会丢失最起始的字节),发送后切换到Rx模式也需要延时(否则丢失最后字节)
    transmission;
    delay_us(100); 
    dma_start(1,DMA_INC_SOURCE_ADDR | DMA_DEST_ADDR_UNCHANGED | DMA_ONE_SHOT | DMA_FORCE_NOW, getenv("SFR:U1TXREG"),transmit,13);  
    delay_us(500);
    receiver;     
//##(0)保存发送的数据包相关信息(以备从机应答比较)
    regs.Request.StartAddress = StartAddr.u16;      //##(0)发送到从机的地址
    regs.Request.Quantity = Quantity.u16;           //##(0)发送到从机的请求读取寄存器数量
    regs.Request.Function = MB_REG_BAT_FaultStatus; //##(0)发送到从机的功能码
    regs.Request.UsrtBusy = true;                   //##(0)已经发送完成则将等待标志设置为"1"（等待从机应答阶段）
}

/*###############################################################################################################################
# 函数名 : void FaultEventTransmit(void)                                                                                        #
# 功  能 : 电池故障事件发送数据（前提是设备有接入）                                                                             #
# 参  数 : NONE                                                                                                                 #
# 说  明 : NONE                                                                                                                 #
###############################################################################################################################*/
void FaultEventError_Process(void) {
    static uint16_t last_ErrorCode = 0u;
          bufferu16 StartAddr, Data;        
//##(0)如果通讯正忙则返回 
    if(regs.Request.UsrtBusy) return;
//##(0)如果故障一致则无需发送
    #asm nop #endasm    
    if(regs.ErrorCode == last_ErrorCode) return;    //##(0)如果2次故障一样则返回
    last_ErrorCode = regs.ErrorCode;                //##(0)保存本次故障代码作为下一次比较
//##(0)配置数据并发送    
    StartAddr.u16 = MB_REG_BAT_ERROR_CODE;          //##(0)起始地址,范围:151
         Data.u16 = regs.ErrorCode;                 //##(0)电池故障代码
    TransmitEventData(StartAddr.u16, Data.u16);     //##(0)调用"DMA"发送数据    
}

/*###############################################################################################################################
# 函数名 : BmsToExoComm_Process();                                                                                              #
# 功  能 : 霍尔感应器（折叠）触发事件发送数据                                                                                   #
# 参  数 : NONE                                                                                                                 #
# 说  明 : NONE                                                                                                                 # 
###############################################################################################################################*/ 
void FOLD_EventProcess(void) {
    static uint16_t lastFOLD;                       //##(0)静态局部变量：记录上一次的折叠状态，函数多次调用数值不丢失
    bufferu16 StartAddr, Data;                      //##(0)共用体变量：拆分16位地址、16位数据为高低字节，方便填充通讯报文     
//##(0)如果状态没有改变则返回
    if(lastFOLD == regs.FOLD)  return;              //##(0)如果当前折叠状态和上次记录状态一致，说明无变化，直接退出不发送报文
//##(0)配置数据并发送   
    StartAddr.u16 = MB_REG_BAT_FOLD_DETECTED;       //##(0)配置Modbus事件上报寄存器起始地址 153
       Data.u8[1] = 0x00;                           //##(0)16位数据高8位填0，只使用低8位存放状态
       Data.u8[0] = regs.FOLD;                      //##(0)把当前折叠状态写入数据低字节
    TransmitEventData(StartAddr.u16, Data.u16);     //##(0)调用发送接口，DMA硬件方式上报寄存器地址+状态数据
//##(0)发送完事件后将状态保存       
    lastFOLD = regs.FOLD;                           //##(0)更新历史状态缓存，标记本次状态已上报，避免重复发送 
}

/*###############################################################################################################################
# 函数名 : BmsToExoComm_Process();                                                                                              #
# 功  能 : 霍尔感应器（绑带）触发事件发送数据                                                                                   #
# 参  数 : NONE                                                                                                                 #
# 说  明 : NONE                                                                                                                 # 
###############################################################################################################################*/ 
void STRAP_EventProcess(void) {
    static uint16_t lastFOLD;                       //##(0)静态局部变量：记录上一次的绑带状态，函数多次调用数值不丢失
    bufferu16 StartAddr, Data;                      //##(0)共用体变量：拆分16位地址、16位数据为高低字节，方便填充通讯报文     
//##(0)如果状态没有改变则返回
    if(lastFOLD == regs.STRAP)  return;             //##(0)如果当前绑带状态和上次记录状态一致，说明无变化，直接退出不发送报文
//##(0)配置数据并发送   
    StartAddr.u16 = MB_REG_BAT_STRAP_DETECTED;      //##(0)配置Modbus事件上报寄存器起始地址 153
       Data.u8[1] = 0x00;                           //##(0)16位数据高8位填0，只使用低8位存放状态
       Data.u8[0] = regs.STRAP;                     //##(0)把当前绑带状态写入数据低字节
    TransmitEventData(StartAddr.u16, Data.u16);     //##(0)调用发送接口，DMA硬件方式上报寄存器地址+状态数据
//##(0)发送完事件后将状态保存       
    lastFOLD = regs.STRAP;                          //##(0)更新历史状态缓存，标记本次状态已上报，避免重复发送 
}

/*###############################################################################################################################
# 函数名 : void PeriodicPolling_500ms(void)                                                                                     #
# 功  能 : 正常运行：周期性轮询响应（500ms）                                                                                    #
# 参  数 : NONE                                                                                                                 #
# 说  明 : 电池每 500ms 轮询寄存器 64–67,从机通过设置这些值控制电池行为                                                        #
###############################################################################################################################*/
void PeriodicPolling_500ms(void) {
    static uint16_t timeout;
    bufferu16 StartingAddress,Quantity;
//##(0)如果500毫秒时间没到则退出  
    if((regs.time10ms-timeout)<500/10) return;
    timeout = regs.time10ms; 
//##(0)配置发送的数据包
    StartingAddress.u16 = 0x0040;                           //##(0)起始地址
    Quantity.u16 = 0x0004;                                  //##(0)请求4个寄存器数据(64~67)
//##(0)调用发送函数
    TransmitRequestData(StartingAddress.u16,Quantity.u16);  
}
/*###############################################################################################################################
# 函数名 : void TransmitBMS_Telemetry(void)                                                                                     #
# 功  能 : 发送电池段的常用信息(电流,温度之类信息)                                                                              #
# 参  数 : NONE                                                                                                                 #
# 说  明 : 电池每 1000ms 发送一次（前提从机存在并且是外骨骼从设备）                                                             #
###############################################################################################################################*/
void TransmitBMS_1000ms(void) {
    static uint16_t timeout;
          bufferu16 StartAddr,Quantity,crc16;
            uint8_t transmit[64]={0};   
		   uint16_t Temperature;
//##(0)不是外骨骼设备或者串口忙则退出
    if(regs.Request.UsrtBusy) return;
//##(0)如果500毫秒时间没到则退出  
    if((regs.time10ms-timeout)<1000/10) return;
    timeout = regs.time10ms;
//##(0)配置起始地址    
    StartAddr.u16 = MB_REG_BAT_SOC;                 //##(0)起始地址,范围:160----->181
    Quantity.u16 = 22;                              //##(0)发送22个寄存器数据,每个寄存器占用2个字节数据
//##(0)准备好需要发送的数据
    transmit[0] = ServerAddress;                    //##(0)第一个字节为主机地址
    transmit[1] = MB_FC_WRITE_MULTIPLE_REGISTERS;   //##(0)功能代码
    transmit[2] = StartAddr.u8[1];                  //##(0)起始地址高字节 
    transmit[3] = StartAddr.u8[0];                  //##(0)起始地址低字节     
    transmit[4] = Quantity.u8[1];                   //##(0)寄存器数量高字节
    transmit[5] = Quantity.u8[0];                   //##(0)寄存器数量低字节
    transmit[6] = (uint8_t)(Quantity.u16*2);        //##(0)发送的有效字节数
    #asm nop #endasm                                //##(0)以下为实际数据  
    transmit[7]  = make8(FG.rsoc,1);                //##(0)160,相对容量百分比高字节    
    transmit[8]  = make8(FG.rsoc,0);
    transmit[9]  = make8(FG.current,1);             //##(0)161,电流高字节 
    transmit[10] = make8(FG.current,0);
    transmit[11] = make8(FG.stackvoltage,1);        //##(0)162,电池堆积电压高字节
    transmit[12] = make8(FG.stackvoltage,0); 
    transmit[13] = make8(FG.imbalance,1);           //##(0)163,电池平衡状态高字节
    transmit[14] = make8(FG.imbalance,0);
    Temperature = FG.FetTemperature/10.0-273;
    transmit[15] = make8(Temperature,1);            //##(0)164,温度报告
    transmit[16] = make8(Temperature,0);        
    transmit[17] = make8(FG.AverageCurrent,1);      //##(0)165,平均电流
    transmit[18] = make8(FG.AverageCurrent,0);  
    transmit[19] = make8(FG.CellV[0],1);            //##(0)166,电芯"1"电压高字节
    transmit[20] = make8(FG.CellV[0],0);        
    transmit[21] = make8(FG.CellV[1],1);            //##(0)167,电芯"2"电压高字节
    transmit[22] = make8(FG.CellV[1],0);        
    transmit[23] = make8(FG.CellV[2],1);            //##(0)168,电芯"3"电压高字节
    transmit[24] = make8(FG.CellV[2],0);     
    transmit[25] = make8(FG.CellV[3],1);            //##(0)169,电芯"4"电压高字节
    transmit[26] = make8(FG.CellV[3],0);    
    transmit[27] = make8(FG.CellV[4],1);            //##(0)170,电芯"5"电压高字节
    transmit[28] = make8(FG.CellV[4],0);
    transmit[29] = make8(FG.CellV[5],1);            //##(0)171,电芯"6"电压高字节
    transmit[30] = make8(FG.CellV[5],0); 
    transmit[31] = make8(FG.CellV[6],1);            //##(0)172,电芯"7"电压高字节 
    transmit[32] = make8(FG.CellV[6],0);   
    transmit[33] = make8(FG.CellV[7],1);            //##(0)173,电芯"8"电压高字节
    transmit[34] = make8(FG.CellV[7],0);  
    transmit[35] = make8(FG.CellV[8],1);            //##(0)174,电芯"9"电压高字节
    transmit[36] = make8(FG.CellV[8],0);  
    transmit[37] = make8(FG.CellV[9],1);            //##(0)175,电芯"10"电压高字节
    transmit[38] = make8(FG.CellV[9],0);     
    transmit[39] = make8(FG.CellV[10],1);           //##(0)176,电芯"11"电压高字节
    transmit[40] = make8(FG.CellV[10],0);        
    transmit[41] = make8(FG.CellV[11],1);           //##(0)177,电芯"12"电压高字节
    transmit[42] = make8(FG.CellV[11],0);   
    Temperature = FG.TS1Temperature/10.0-273;
    transmit[43] = make8(Temperature,1);            //##(0)178,温度传感器"1"高字节
    transmit[44] = make8(Temperature,0);      
    Temperature = FG.TS2Temperature/10.0-273;
    transmit[45] = make8(Temperature,1);            //##(0)179,温度传感器"2"高字节
    transmit[46] = make8(Temperature,0);
    Temperature = FG.TS3Temperature/10.0-273;
    transmit[47] = make8(Temperature,1);            //##(0)180,温度传感器"3"高字节
    transmit[48] = make8(Temperature,0);
    Temperature = FG.TS4Temperature/10.0-273;
    transmit[49] = make8(Temperature,1);            //##(0)181,温度传感器"4"高字节,芯片内部温度
    transmit[50] = make8(Temperature,0);      
//##(0)计算出校验码    
    crc16 = crc16_modbus(&transmit,51);
    transmit[51] = make8(crc16,0);                  //##(0)校验码低字节
    transmit[52] = make8(crc16,1);    
//##(0)源地址(buf)自增/目的地址(U1TXREG)固定/单次发送/启动"DMA"传输(强制立即发送)/目的地址(送到串口)/源地址(从内存取)/发送字节数
//##(0)发送数据前切换到Tx模式需要延时(否则会丢失最起始的字节),发送后切换到Rx模式也需要延时(否则丢失最后字节)
    transmission;
    delay_ms(1); 
    dma_start(1,DMA_INC_SOURCE_ADDR | DMA_DEST_ADDR_UNCHANGED | DMA_ONE_SHOT | DMA_FORCE_NOW, getenv("SFR:U1TXREG"),transmit,53);  
    delay_ms(4);
    receiver; 
//##(0)保存发送的数据包相关信息(以备从机应答比较)
    regs.Request.StartAddress = StartAddr.u16;                  //##(0)发送到从机的地址
    regs.Request.Quantity = Quantity.u16;                       //##(0)发送到从机的请求读取寄存器数量
    regs.Request.Function = MB_FC_WRITE_MULTIPLE_REGISTERS;     //##(0)发送到从机的功能码
    regs.Request.UsrtBusy = true;                               //##(0)已经发送完成则将等待标志设置为"1"（等待从机应答阶段）       
}

/*###############################################################################################################################
# 函数名 : void Timer50ms_transmit_debug(void)                                                                                  #
# 功  能 : 每50ms发送数据包一次至主机(调试),执行这段代码耗时 1.2ms                                                              #
# 参  数 : NONE                                                                                                                 #
# 说  明 : 绑带磁场强度(mT)X/Y/Z轴,角度(度)/幅度(mT) 传感器U17                                                                  #
           折叠磁场强度(mT)X/Y/Z轴,角度(度)/幅度(mT) 传感器U18                                                                  #
###############################################################################################################################*/
void TransmitHall_50ms(void) {
    static uint16_t timeout;   
            uint8_t transmit[32] = {0};   
           uint16_t crc16; 
          bufferu16 StartingAddress,registers;      
//##(0)如果霍尔数据流使能位处于禁止状态或者从机没有在线则不发送数据,
    if(regs.HallSensorStatus==0u) return;     
//##(0)周期时间是否已到?没到则返回
    if((regs.time10ms-timeout)<50/10) return;   
    timeout = regs.time10ms;
//##(0)如果忙则返回	
    if(regs.Request.UsrtBusy) return;
//##(0)配置起始地址    
    StartingAddress.u16 = MB_REG_BAT_HALL_STRAPX;   //##(0)起始地址,范围:190----->199
    registers.u16 = 10;                             //##(0)发送10个寄存器数据,每个寄存器占用2个字节数据
//##(0)配置帧组装代码   
    transmit[0] = ServerAddress;                    //##(0)第一个字节为主机地址
    transmit[1] = MB_FC_WRITE_MULTIPLE_REGISTERS;   //##(0)功能代码
    transmit[2] = StartingAddress.u8[1];            //##(0)起始地址高字节 
    transmit[3] = StartingAddress.u8[0];            //##(0)起始地址低字节  
    transmit[4] = registers.u8[1];                  //##(0)寄存器数量高字节
    transmit[5] = registers.u8[0];                  //##(0)寄存器数量低字节
    transmit[6]  = (uint8_t)(registers.u16*2);      //##(0)发送的有效字节数     
//##(0)以下为寄存器实际数据,遵循 H-->L
    transmit[7]  = make8(STRAPX,1);                 //##(0)绑带磁场强度(mT)X轴,传感器U17【高字节】
    transmit[8]  = make8(STRAPX,0);      
    transmit[9]  = make8(STRAPY,1);                 //##(0)绑带磁场强度(mT)Y轴,传感器U17【高字节】
    transmit[10] = make8(STRAPY,0);                            
    transmit[11] = make8(STRAPZ,1);                 //##(0)绑带磁场强度(mT)Z轴,传感器U17【高字节】
    transmit[12] = make8(STRAPZ,0);
    transmit[13] = make8(STRAP_ANGLE,1);            //##(0)绑带角度(度),传感器U17【高字节】  
    transmit[14] = make8(STRAP_ANGLE,0); 
    transmit[15] = make8(STRAP_MAGNITUTE,1);        //##(0)绑带幅度(mT),传感器U17【高字节】
    transmit[16] = make8(STRAP_MAGNITUTE,0);   
    transmit[17] = make8(FOLDX,1);                  //##(0)折叠磁场强度(mT)X轴,传感器U18【高字节】  
    transmit[18] = make8(FOLDX,0); 
    transmit[19] = make8(FOLDY,1);                  //##(0)折叠磁场强度(mT)X轴,传感器U18【高字节】       
    transmit[20] = make8(FOLDY,0);  
    transmit[21] = make8(FOLDZ,1);                  //##(0)折叠磁场强度(mT)X轴,传感器U18【高字节】
    transmit[22] = make8(FOLDZ,0);
    transmit[23] = make8(FOLD_ANGLE,1);             //##(0)折叠角度(度),传感器U18【高字节】
    transmit[24] = make8(FOLD_ANGLE,0);  
    transmit[25] = make8(FOLD_MAGNITUTE,1);         //##(0)折叠幅度(mT),传感器U18【高字节】
    transmit[26] = make8(FOLD_MAGNITUTE,0);      
//##(0)计算出校验码 
    crc16 = crc16_modbus(&transmit,27); 
    transmit[27] = make8(crc16,0);                  //##(0)校验码低字节
    transmit[28] = make8(crc16,1);
//##(0)发送数据,先将"RS422"切换到发射模式-->发送数据-->切换到接收模式 
    transmission;
    delay_us(100); 
    dma_start(1,DMA_INC_SOURCE_ADDR | DMA_DEST_ADDR_UNCHANGED | DMA_ONE_SHOT | DMA_FORCE_NOW, getenv("SFR:U1TXREG"),transmit,29);  
    delay_ms(2);
    receiver;  
//##(0)保存发送的数据包相关信息(以备从机应答比较)
    regs.Request.StartAddress = StartingAddress.u16;         //##(0)发送到从机的地址
    regs.Request.Quantity = registers.u16;                   //##(0)发送到从机的请求读取寄存器数量
    regs.Request.Function = MB_FC_WRITE_MULTIPLE_REGISTERS;  //##(0)发送到从机的功能码
    regs.Request.UsrtBusy = true;                             //##(0)已经发送完成则将等待标志设置为"1"（处于等待从机应答阶段）      
}
/*###############################################################################################################################
# 函数名 : BmsToExoComm_Process();                                                                                              #
# 功  能 : 电池和外骨架(Exo)通讯                                                                                                #
# 参  数 : NONE                                                                                                                 #
# 说  明 : NONE                                                                                                                 # 
###############################################################################################################################*/ 
void BmsToExoComm_Process(void)  {	
//##(0)如果有数据打印(调试模式)则停止和"EXO"通讯 
    if(regs.flags.MsgPrint==true) { regs.DeviceType = 0u; return;}
//##(0)正常和"EXO"通讯    
    if(regs.flags.IDType == IDEXO) {        //##(0)如果接入的ID是"EXO"设备需要请求动画信息
        RequesDeviceType_Process();         //##(0)请求设备
	StartupRequestInfo_Process();       //##(0)电池上电请求设备信息(如果从机) 
	RequestAnims_Process();             //##(0)接入的是外骨架则开始请求动画数据
    }else{                                  //##(1)如果接入的不是"EXO"设备则需要清除通讯超时故障标志和计时器							
	regs.NoCommTimeout = 0u;            //##(1)无通讯超时计时器清零(检查通讯故障)
	regs.FaultLive.COM = false;         //##(1)通讯故障清除
	regs.Request.UsrtBusy = false;      //##(1)从机应答则将认为是处于空闲状态(可以发送数据)		
    }
//##(0)以下为事件触发上报和定时发送	
    StartupTransmitInfo_Process();          //##(2)电池动上报电池/设备状态报文  
    ButtonEvent_Process();                  //##(2)按钮事件  
    FaultEvent_Process();                   //##(2)电池故障事件
    FaultEventError_Process();              //##(2)电池故障代码事件
    FOLD_EventProcess();                    //##(2)折叠事件
    STRAP_EventProcess();                   //##(2)绑带事件
    #asm nop #endasm 
    if(regs.DeviceType!=ExoType) return;    //##(0)确认到接入的设备类型不是外骨架则退出 
    if(!regs.flags.ReqAnimsDone) return;
    #asm nop #endasm  
    PeriodicPolling_500ms();                //##(3)周期性轮询响应（500ms）轮询寄存器"64/67"
    TransmitBMS_1000ms();                   //##(3)发送电池的动态信息(电流,温度之类信息)1000ms循环发送    
    TransmitHall_50ms();                    //##(3)每50ms发送霍尔传感器数据至EXo(调试)
    RequestSN_Process();                    //##(3)请求序列号   
}

/*###############################################################################################################################
# 函数名 : void dmaDataReceptionTask(void)                                                                                      #
# 功  能 : DMA 接收数据任务(包含判断数据正确)                                                                                   #
# 参  数 : NONE                                                                                                                 #
# 说  明 : NONE                                                                                                                 # 
###############################################################################################################################*/ 
bool dmaDataReceptionTask(void) {
    bufferu16 checksum,crc16;
      uint8_t dummy;
         bool crcPass = false;
//##(0)判断是否接收帧完成 ? 如果完成则将数据复制到暂存器中
    if(uart.ReceiveCompleted == false) return(false);
    uart.ReceiveCompleted = false;
//##(0)如果"DMA"没有收到字节则返回"0"
    uart.buffidx = dmaSize - DMACNT0;                                   //##(0)已经接收到的字节数
//##(0)计算并限制合法长度(如果溢出则复位DMA)   
    if(uart.buffidx<=0u || uart.buffidx>=dmaSize-2) {
        uint8_t _dmaFlushDummy;
        while((U1STA&0x0003)!=0u) { _dmaFlushDummy = U1RXREG; }  
        dma_start(0,DMA_SOURCE_ADDR_UNCHANGED|DMA_INC_DEST_ADDR,uart.buffer,getenv("SFR:U1RXREG"),dmaSize);
        regs.rxTimeout = 0; 
        return(false);
    }
//##(0)接收完成数据,将检查数据正确标志全部清零    
    uart.bootFormat = uart.normalFormat = false;
//##(0)如果是"BOOTLOADER"数格式则判断是否接收够数据?
    if(uart.buffer[0]=='#') {
        if(uart.buffer[3]==',' && uart.buffer[uart.buffidx-1]=='\r' && uart.buffidx>=7u) {
           uart.bootFormat = true;
        } 
    }else if(uart.buffer[0]==ServerAddress) {                           //##(1)如果第一个字节是服务端地址则正常通讯格式 。
        if(uart.buffer[1] == 0x03) {                                    //##(1) Function Code(0x03) 
            uint16_t Length = uart.buffer[2] + 5;                       //##(1)实际需要接收的数据长度
            if(uart.buffidx >= Length && Length <= dmaSize) {
                checksum.u8[0] = uart.buffer[uart.buffer[2]+3];         //##(1)提取接收到的校验码(低字节)
                checksum.u8[1] = uart.buffer[uart.buffer[2]+4];         //##(1)提取接收到的校验码(高字节)
                crc16.u16 = crc16_modbus(uart.buffer,uart.buffer[2]+3); //##(1)计算出接收数据的校验码 
            }
        }else if(uart.buffer[1]==0x06 || uart.buffer[1]==0x10) {        //##(2)Function Code(0x06/0x10)
            if(uart.buffidx>=8u) {
                checksum.u8[0] = uart.buffer[6];                        //##(2)提取接收到的校验码(低字节)
                checksum.u8[1] = uart.buffer[7];                        //##(2)提取接收到的校验码(高字节)
                crc16.u16 = crc16_modbus(uart.buffer,0x06);             //##(2)计算出接收数据的校验码,参与计算的字节位6个字节
            }
        }
        crcPass = (checksum.u16 == crc16.u16);                          //##(2)数据正确则设置标志位"1"  
        uart.normalFormat = crcPass;                                    //##(2)数据正确则设置标志位"1"
    }
//##(0)如果接收先进先出缓冲区"FIFO"有数据则需要先清除(以免有残余数据导致数据错位)
    while((U1STA&0x0003)!=0u) { dummy = U1RXREG; }       
//##(0)解释完重启DMA,关闭"DMA"强制复位指针
    dma_start(0,DMA_SOURCE_ADDR_UNCHANGED|DMA_INC_DEST_ADDR,uart.buffer,getenv("SFR:U1RXREG"),dmaSize);
    regs.rxTimeout = 0;       
//##(0)返回状态,无论何种格式接收完成都返回"1"
    return(uart.normalFormat | uart.bootFormat);  
}

/*###############################################################################################################################
# 函数名 : void commands_process(void)                                                                                          #
# 功  能 : 命令执行进程                                                                                                         #
# 参  数 : NONE                                                                                                                 #
# 说  明 : NONE                                                                                                                 # 
###############################################################################################################################*/ 
void writeSerialNumber(void) {
    if(m24c04_Write(eeprom_SN, FG.SN,16)) {         //##(0)第一次写
        delay_ms(1);
        if(m24c04_Write(eeprom_SN,FG.SN,16)) {       //##(0)不成功写第二次
            delay_ms(1);
            m24c04_Write(eeprom_SN,FG.SN,16);       //##(0)不成功写第三次
        } 
    }
}

/*###############################################################################################################################
# 函数名 : void commands_process(void)                                                                                          #
# 功  能 : 命令执行进程                                                                                                         #
# 参  数 : NONE                                                                                                                 #
# 说  明 : NONE                                                                                                                 # 
###############################################################################################################################*/ 
void commands_Process(void) {
    uint8_t backups[dmaSize]={0},updata_status[8];
    uint8_t address,index;
   uint16_t command;
       bool commandFormat;
//##(0)如果没有接收到正常命令信息和升级命令信息则退出 
	receiver;
    if(dmaDataReceptionTask()==false) return;
//##(0)如果没有接收到正确数据则返回
    if(!uart.bootFormat && !uart.normalFormat && !uart.testFormat) return;
//##(1)接受完成的正确数据包则将缓冲数组的数据拷贝到备份数组中,并将接收串口结构体全部清零
    memcpy(backups,uart.buffer,sizeof(uart.buffer));            //##(0)将接收缓冲区的数据拷贝到即将处理的数据备份中   
//##(2)判断接收到的是何种类型的数据包 ? "Finish1"是特殊数据格式(升级固件数据格式),"Finish2"是正常数据格式
    if(uart.bootFormat == true) {                               //##(0)是接收升级数据格式    
        address = AsciiToHex((uint8_t*)&backups[1]);            //##(0)获取上位机发送来的地址(升级模式应答格式特有)
        command = AsciiToHex((uint8_t*)&backups[4]);            //##(0)提取程序升级命令
        uart.bootFormat = false;                                //##(0)接收完成标志清零
        commandFormat = true;                                   //##(0)是升级模式
        uart.normalFormat = false;                              //##(0)正常通讯格式标志清零
    }else if(uart.normalFormat == true){                        //##(1)接收到正确的应用命令数据
        uart.normalFormat = false;                              //##(1)清除接收数据完成标志
        uart.bootFormat = false;                                //##(1)引导通讯格式清零
        commandFormat = false;                                  //##(1)是正常模式
        if(backups[1] != regs.Request.Function) return;         //##(1)如果请求的功能码和应答的功能码不一致则退出
        regs.Request.UsrtBusy = false;                          //##(1)从机应答则将认为是处于空闲状态(可以发送数据)
        regs.NoCommTimeout = 0u;                                //##(1)无通讯超时计时器清零(检查通讯故障)
        regs.FaultLive.COM = false;								//##(0)通讯故障清除
        if(regs.Request.Function != 0x03) return;               //##(0)以下是功能码 = 0x03(读保持寄存器),从机应答有数据
        if(regs.Request.Quantity*2 != backups[2]) return;       //##(0)如果请求的和应答的字节数是否一样 ? 不一样则返回
        command = regs.Request.StartAddress;                    //##(0)请求的起始地址作为命令
//##(0)如果是请求的是动画地址(256~1016)则将动画数据存入动画数组中 
        if(command >= MB_REG_BAT_LED_ANIMATION0 && command <= MB_REG_BAT_LED_ANIMATION19) {
            index = (uint8_t)((regs.ReqAnimsAddress - MB_REG_BAT_LED_ANIMATION0)/40);  
            memcpy(LEDAnim[index],&backups[3],backups[2]);
            if(++regs.recvAnimCnt>=regs.AnimQty) {		//##(0)如果接受的动画组数量等于或者大于动画总数则为接收动画完成
                regs.flags.ReqAnimsDone = true;			//##(0)设置接收完成标志
                regs.recvAnimCnt = 0u;				//##(0)接收动画组计数器清零	
                output_bit(pin_b5,1);				//##(0)测试接受完全部动画结束【拉高电平】
            }			
        }  
    }                                                       
//##(0)发送数据使能(采用"DMA"发送)
    transmission;
    delay_ms(1); 
    switch(command) {
//##(0)以下是升级程序命令
        case 0xA0:
             fprintf(rs485,"@%02x,application,v1.00,000000,%s\r", address, CompilationDate);
             break;
        case 0xAD:
             fprintf(rs485,"@%02x,%s\r",address,&FirmwareVersion);
             break;
        case 0xA5:
             fprintf(rs485,"@%02x,FFFF,FFFF,FFFF,FFFF\r",address);
             break;
        case 0xAE: 
             fprintf(rs485,"@%2X\r",address);  
             memset(updata_status,0xFF,sizeof(updata_status));                        
             erase_program_memory(updata_address);                                     
             write_program_memory(updata_address,updata_status,0x08); 
             delay_ms(20); 
             reset_cpu();
             break;  
//##(0)进入睡眠和关机命令   
        case 0xB0:
             if(memcmp(&backups[7],(U8*)"U80711R01 messages Print",24)==0) { 
                regs.PrintDelay = Getword((U8*)&backups[32]) ;
                regs.flags.MsgPrint = 1;
                regs.flags.ImmedPrint = 1;          //##(0)立即打印信息,无需设定还要等待时间才打印
             }else{ 
                regs.flags.MsgPrint = 0;            //##(0)停止打印信息
             }  
             break;  
        case 0xB3:
             if(memcmp(&backups[7],(uint8_t*)"Sleep Microcontroller",21)!=0) break;  
             fprintf(rs485,"Sleep MCU\r"); 
             delay_ms(5);
             regs.flags.RunMode = MODE_EnterSLEEP;
             break;	
        case 0xB4:
             if(memcmp(&backups[7],(uint8_t*)"Battery ShutDown",16)!=0) break;  
             fprintf(rs485,"Battery ShutDown\r");
             delay_ms(5);
             regs.flags.RunMode = MODE_SHUTDOWN;
             break;
        case 0xB5:
             if(memcmp(&backups[7],(uint8_t*)"SN = ",5)!=0) break;      //##(0)不是写序列号
             memcpy(FG.SN, &backups[12],16U);                           //##(0)提取序列号(16个字节)
             writeSerialNumber();                                       //##(0)序列号写入"EEPROM"中
             fprintf(rs485,"Pass\r");
             break;  
        case 0xB6:                                                      
             if(memcmp(&backups[7],(uint8_t*)"reset mcu",9)!=0) break;  
             fprintf(rs485,"Reset the MCU\r");
             delay_ms(10);
             reset_cpu();
             break;
        default: 
             if(commandFormat==false) break;                           //##(0)不是升级模式命令则不应答                   
             fprintf(rs485,"@%02x,%02x\r",address,command);           
             break;
//##(0)以下全部命令属于从机服务端应答(不带数据) 
        case MB_REG_DEVICE_TYPE:
             regs.DeviceType = make16(backups[3],backups[4]);           //##(0)接入的设备类型
             break;    
        case MB_REG_EXO_VERSION_MAJ:                                    //##(0)Address 1 to 11, 合并一起读取
             regs.GlobalBright     = make16(backups[15],backups[16]);   //##(0)全局亮度 
             regs.FadeOutDuration  = make16(backups[18],backups[17]);   //##(0)淡出时长
             regs.FadeInDuration   = make16(backups[20],backups[19]);   //##(0)淡入时长      
             regs.HallSensorStatus = make16(backups[21],backups[22]);   //##(0)启用/禁用霍尔传感器数据流到 190+ 寄存器
             regs.AnimQty          = make16(backups[23],backups[24]);   //##(0)动画数量(一共有几组动画)
             regs.flags.ReqInfoDone = true;                             //##(0)请求信息完成
             return;
        case MB_REG_BAT_NextAction:
             regs.NextAction  = make16(backups[3],backups[4]);          //##(0)周期性轮询响应, 
             regs.AnimationID = make16(backups[5],backups[6]);          //##(0)动画ID  
             regs.AnimMR1.u16 = make16(backups[7],backups[8]);          //##(0)动画元数据 1
             regs.AnimMR2.u16 = make16(backups[9],backups[10]);         //##(0)动画元数据 2
             break;
        case MB_REG_BAT_SerialNumber:                                   //##(0)从机应答的序列号
             memcpy(FG.SN,&backups[3],backups[2]);                      //##(0)接收到的序列号更新到寄存器中
             writeSerialNumber();                                       //##(0)序列号写入"EEPROM"中
             break;            
    }
//##(0)重新开启接收
    delay_ms(2);
    receiver;      
}

/*###############################################################################################################################
# 函数名 : void MsgPrintf_Process(void)                                                                                         #
# 功  能 : 信息打印进程                                                                                                         #
# 参  数 : NONE                                                                                                                 #
# 说  明 : NONE                                                                                                                 # 
###############################################################################################################################*/ 
void MsgPrintf_Process(void) {
    static uint16_t timeout;
    static  uint8_t LastkeyState = 0;
            uint8_t txBuff[500];
           uint16_t len;
              float Temperature;  
//##(0)如果没有打印信息使能则更新时间基点并返回    
    if(regs.flags.MsgPrint == false)  { timeout = regs.time10ms; return; }
//##(0)需要将应答故障清零【通讯故障】,和计时器清零			  
    regs.NoCommTimeout = 0u;                                    //##(1)无通讯超时计时器清零(检查通讯故障)
    regs.FaultLive.COM = false;					//##(0)通讯故障清除		  
//##(0)如果有按键按下则发送按键状态(无需定时)
    if(regs.keyState!=LastkeyState && regs.keyState!=0) { LastkeyState = regs.keyState; }      
//##(0)打印使能,判断周期延时是否已到？ 没到则返回(如果有立即输出打印信息则无需等到时间)
    if(regs.flags.ImmedPrint == false) {
        if((regs.time10ms-timeout)<regs.PrintDelay/10) return;            
        timeout = regs.time10ms; 
    }           
    regs.flags.ImmedPrint = false;     
//##(0)格式和全部数据为"ascii"格式
    len = 0;
    len += sprintf(txBuff + len, "#,");                         //##(0)起始码
    len += sprintf(txBuff + len, "%s,",  FG.SN);                 //##(0)序列号
    len += sprintf(txBuff + len, "%lu,", FG.ChargingVoltage);   //##(0)充电电压
    len += sprintf(txBuff + len, "%lu,", FG.ChargingCurrent);   //##(0)充电电流 
//##(0)各种温度   
    Temperature = (float)FG.TS1Temperature/10.0-273.15;
    len += sprintf(txBuff + len, "%f,", Temperature);		//##(0)温度1【TS1】
    Temperature = (float)FG.TS2Temperature/10.0-273.15;
    len += sprintf(txBuff + len, "%f,", Temperature);		//##(0)温度1【TS3】  
    Temperature = (float)FG.TS3Temperature/10.0-273.15;
    len += sprintf(txBuff + len, "%f,", Temperature);		//##(0)温度1【DCHG】 
    Temperature = (float)FG.TS4Temperature/10.0-273.15;
    len += sprintf(txBuff + len, "%f,", Temperature);		//##(0)温度1【DDSG】    
    Temperature = (float)FG.Temperature/10.0-273.15;
    len += sprintf(txBuff + len, "%f,", Temperature);		//##(0)平均电芯温度作为报告温度  
//##(0)各种电压数据
    len += sprintf(txBuff + len, "%u,", FG.stackvoltage);       //##(0)堆积电压
    len += sprintf(txBuff + len, "%u,", FG.packvoltage);        //##(0)PACK 电压   
    len += sprintf(txBuff + len, "%u,", FG.Pinvoltage);         //##(0)Pin引脚电压
    len += sprintf(txBuff + len, "%u,", FG.CellV[0]);           //##(0)电芯【1】电压
    len += sprintf(txBuff + len, "%u,", FG.CellV[1]);           //##(0)电芯【2】电压
    len += sprintf(txBuff + len, "%u,", FG.CellV[2]);           //##(0)电芯【3】电压
    len += sprintf(txBuff + len, "%u,", FG.CellV[3]);           //##(0)电芯【4】电压
    len += sprintf(txBuff + len, "%u,", FG.CellV[4]);           //##(0)电芯【5】电压
    len += sprintf(txBuff + len, "%u,", FG.CellV[5]);           //##(0)电芯【6】电压
    len += sprintf(txBuff + len, "%u,", FG.CellV[6]);           //##(0)电芯【7】电压
    len += sprintf(txBuff + len, "%u,", FG.CellV[7]);           //##(0)电芯【8】电压
    len += sprintf(txBuff + len, "%u,", FG.CellV[8]);           //##(0)电芯【9】电压
    len += sprintf(txBuff + len, "%u,", FG.CellV[9]);           //##(0)电芯【10】电压
    len += sprintf(txBuff + len, "%u,", FG.CellV[10]);          //##(0)电芯【11】电压
    len += sprintf(txBuff + len, "%u,", FG.CellV[11]);          //##(0)电芯【12】电压    
    len += sprintf(txBuff + len, "%u,", FG.CellV[12]);          //##(0)电芯【13】电压
    len += sprintf(txBuff + len, "%u,", FG.CellV[13]);          //##(0)电芯【14】电压
    len += sprintf(txBuff + len, "%u,", FG.CellV[14]);          //##(0)电芯【15】电压
    len += sprintf(txBuff + len, "%u,", FG.CellMax);            //##(0)电芯最高电压
    len += sprintf(txBuff + len, "%u,", FG.CellMin);            //##(0)电芯最低电压
    len += sprintf(txBuff + len, "%u,", FG.imbalance);          //##(0)电芯最高/最低电压差 
//##(0)各种电压数据
    len += sprintf(txBuff + len, "%ld,", FG.current);           //##(0)电流
    len += sprintf(txBuff + len, "%ld,", FG.AverageCurrent);    //##(0)平均电流
    len += sprintf(txBuff + len, "%ld,", FG.RemCap);            //##(0)剩余容量  
    len += sprintf(txBuff + len, "%ld,", FG.FCC);               //##(0)充满容量      
    len += sprintf(txBuff + len, "%ld,", FG.CCC);               //##(0)充放电次数
    len += sprintf(txBuff + len, "%4X,", FG.BatteryStatus.word); //##(0)电池状态
//##(0)各种状态标志
    len += sprintf(txBuff + len, "%d,", regs.FaultLive.CUV);    //##(0)电池欠压故障    
    len += sprintf(txBuff + len, "%d,", regs.FaultLive.COV);    //##(0)电池过压故障
    len += sprintf(txBuff + len, "%d,", regs.FaultLive.OCC);    //##(0)充电过流故障
    len += sprintf(txBuff + len, "%d,", regs.FaultLive.OCD);    //##(0)放电过流故障
    len += sprintf(txBuff + len, "%d,", regs.FaultLive.SCD);    //##(0)放电短路故障
    len += sprintf(txBuff + len, "%d,", regs.FaultLive.UTC);    //##(0)充电欠温故障
    len += sprintf(txBuff + len, "%d,", regs.FaultLive.UTD);    //##(0)放电欠温故障 
    len += sprintf(txBuff + len, "%d,", regs.FaultLive.OTC);    //##(0)放电过热故障 
    len += sprintf(txBuff + len, "%d,", regs.FaultLive.OTD);    //##(0)放电过热故障	
	len += sprintf(txBuff + len, "%d,", regs.FaultLive.bqxxx);  //##(0)无法与管理芯片通讯	
//##(0)持久故障  
    len += sprintf(txBuff + len, "%d,", PFStatusA.SUV);		//##(0)电芯欠压安全永久失效
    len += sprintf(txBuff + len, "%d,", PFStatusA.SOV);		//##(0)电芯过压安全永久失效
    len += sprintf(txBuff + len, "%d,", PFStatusA.SOCC);	//##(0)充电过流安全永久失效
    len += sprintf(txBuff + len, "%d,", PFStatusA.SOCD);	//##(0)放电过流安全永久失效 
    len += sprintf(txBuff + len, "%d,", PFStatusA.SOT);		//##(0)过热安全永久失效 
    len += sprintf(txBuff + len, "%d,", PFStatusA.SOTF);	//##(0)FET 过热安全永久失效
    len += sprintf(txBuff + len, "%d,", PFStatusA.CUDEP);       //##(0)铜沉积永久失效
    len += sprintf(txBuff + len, "%d,", PFStatusB.CFETF);	//##(0)充电 FET 永久失效
    len += sprintf(txBuff + len, "%d,", PFStatusB.DFETF);	//##(0)放电 FET 永久失效
    len += sprintf(txBuff + len, "%d,", PFStatusB._2LVL);	//##(0)二级保护器永久失效
    len += sprintf(txBuff + len, "%d,", PFStatusB.VIMR);	//##(0)静态模式电压不平衡永久失效
    len += sprintf(txBuff + len, "%d,", PFStatusB.VIMA);	//##(0)激活模式电压不平衡永久失效
    len += sprintf(txBuff + len, "%d,", SafetyStatusC.SCDL);	//##(0)放电短路锁存永久失效
//##(0)按键状态/霍尔传感器状态
    len += sprintf(txBuff + len, "%X,", LastkeyState);          //##(0)按键历史
    len += sprintf(txBuff + len, "%X,", regs.FOLD);		//##(0)折叠霍尔传感器状态折叠/展开 
    len += sprintf(txBuff + len, "%X,", regs.STRAP);		//##(0)绑带霍尔传感器状态绑住/松开 
//##(0)结束字符    
    len += sprintf(txBuff + len, "\r");  
//##(0)源地址(buf)自增/目的地址(U1TXREG)固定/单次发送/启动"DMA"传输(强制立即发送)/目的地址(送到串口)/源地址(从内存取)/发送字节数
//##(0)发送数据前切换到Tx模式需要延时(否则会丢失最起始的字节),发送后切换到Rx模式也需要延时(否则丢失最后字节)
    transmission;
    delay_us(100); 
    dma_start(1,DMA_INC_SOURCE_ADDR | DMA_DEST_ADDR_UNCHANGED | DMA_ONE_SHOT | DMA_FORCE_NOW, getenv("SFR:U1TXREG"),txBuff,len);  
    delay_ms(5);
    receiver;    
}
/*###############################################################################################################################
# 声明结束                                                                                                                      #
###############################################################################################################################*/
#ifdef	__cplusplus
}
#endif
#endif

