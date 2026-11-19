
/*###############################################################################################################################
 # 文件名称 ： u80711R01_CONFIG_H.H                                                                                             #
 # 公司名称 :  TOTEX Technology, Inc.                                                                                           #
 # 芯片型号 ： PIC24FJ128GA302                                                                                                  #
 # 编译工具 :  ccs compiler v5.118                                                                                              #
 # 作    者 :  BenZhang                                                                                                         #
 # 编写日期 :  2025/11/10                                                                                                       #
 # 版    本 :  v1.00                                                                                                            #
 ##############################################################################################################################*/
#ifndef APP_CONFIG_H
#define	APP_CONFIG_H

//#define _bootloader                                       //##(0)声明为引导声明串口驱动函数库/声明I2C总线驱动函数库（否则为应用程序驱动库）
#define updata_address  0x01A00                     //##(0)保存升级标识地址
/*###############################################################################################################################
# 版本信息和编译日期                                                                                                           #
###############################################################################################################################*/
const char *CompilationDate = "2026/11/04";         //##(0)固件生成日期
const char *FirmwareVersion = "application";        //##(0)版本号
const char MajFW = 1;                               //##(0)主版本
const char MinFW = 1;                               //##(0)次版本
const char PatFW = 7;                               //##(0)补充版本
                                                    //##(0)1.1.6 增加电芯电压低于2.5V后设置PF标志,上电检测到PF标志则禁止输出/输入,除非清除"PF"标志
/*###############################################################################################################################
# 库文件                                                                                                                        #
###############################################################################################################################*/
#define  PIC24FJ                //##(0)芯片类别
#include <24FJ128GL302.h>       //##(0)芯片型号
#device  ADC = 12               //##(0)ADC 读取结果 = 12位
#device  ICD = 3                //##(0)启动端口PGD3仿真
#include <stdlib.h>             //##(0)标准库头文件
#include <stdbool.h>            //##(0)布尔类型
#include <stdio.h>              //##
#include <stdlib.h>             //##
#include <stdint.h>             //##
#include <string.h>             //##
#include <math.h>               //##
//#include "pcd_bootloader.h"     //##(0)声明为引导程序(屏蔽则为应用程序段/否则为BOOTLOADER程序段)
/*###############################################################################################################################
#  芯片配置位[1]                                                                                                                #
###############################################################################################################################*/
#FUSES NOAIVT                   //##(0)禁止备用中断向量表
#FUSES PROTECT_CFG              //##(0)配置段(CS)代码保护级别位(标准安全性)
#FUSES WPCFG                    //##(0)配置段被写保护(配置段被写保护)
#FUSES NOPROTECT                //##(0)通用段（GS）代码保护级别位(无保护（GWRP写保护除外）)
#FUSES NOPROTECT                //##(0)通用段程序写保护位(通用段不被写保护)
#FUSES NOBSS                    //##(0)引导段（BS）控制位(未使能引导段)
#FUSES NOWRTB                   //##(0)引导段代码保护级别位(无保护（BWRP写保护除外）)
//##
#FUSES NOIESO                   //##(0)   0 = 禁止 IESO 模式（双速启动）
#FUSES PLL8X                    //##(0)1110 = 选择 8x PLL
#FUSES FRC_PLL                  //##(0)带后分频器和 PLL 模块的快速 RC 振荡器（FRCPLL）
//##
#FUSES NOCKSNOFSM               //##(0)禁止时钟切换和故障保护时钟监视器 
#FUSES NOIOL1WAY                //##(0)IOLOCK位可根据需要置1和清零（需要解锁序列）
#FUSES PLL_FROM_FRC             //##(0)PLL辅助选择配置位 (PLL由片上快速RC（FRC）振荡器提供时钟)
#FUSES SOSC_DIG                 //##(0)SOSC选择配置位 (数字（SCLKI）外部提供的时钟模式)
#FUSES OSCIO                    //##(0)CLKO使能配置位 (禁止CLKO输出 )
//#FUSES HS                          //##(0)主振荡器配置位 (选择HS振荡器模式（10 MHz-32 MHz))
//##
#FUSES WINDIS                   //##(0)窗口看门狗定时器禁止位(禁止窗口WDT)
#FUSES WDT_SW                   //##(0)软件开启/关闭
#FUSES WDT32                    //##(0)看门狗定时器预分频比位(WDT预分频比为1:32)
#FUSES WPOSTS13                 //##(0)看门狗定时器后分频比选择位(1:4096)
//##
#FUSES NOBROWNOUT               //##(0)欠压复位使能位(通过硬件禁止欠压复位；禁止SBOREN位)
#FUSES NOLVR                    //##(0)低功耗稳压器控制位(保持功能不可用)
#FUSES DNVP                     //##(0)欠压保护使能位(BOR无效时使能欠压保护)
//##
#FUSES NOJTAG                   //##(0)禁止JTAG端口
//#FUSES ICSP3                      //##(0)ICD通信通道选择位(通过PGC3/PGD3进行通信)
//##
#FUSES SMBEN                    //##(0)SMBus 3.0电平使能位(SMBus 3.0输入电平)
#FUSES ALTI2C1                  //##(0)备用I2C1位(RB5和RB4上的ASDA1和ASCL1)
#FUSES SOSC_HIGH                //##(0)SOSC高功耗使能位（仅当SOSCSEL = 1时有效）/(使能SOSC高功耗模式)
#FUSES NOTMPRPIN                //##(0)篡改引脚使能位(禁止TMPRN引脚功能)
#FUSES NOALTCMPI                //##(0)备用比较器输入使能位( C2INC和C3INC位于标准引脚位置上)
/*###############################################################################################################################
#  应用声明开始                                                                                                                 #
###############################################################################################################################*/
#ifdef	__cplusplus
extern "C" {
#endif
/*###############################################################################################################################
#  数据类型声明                                                                                                                 #
###############################################################################################################################*/
typedef union{ uint32_t u32; uint16_t u16[2];  uint8_t u8[4]; }bufferu32;	
typedef union{ uint16_t u16; uint8_t u8[2]; }bufferu16;
typedef uint8_t  U8;
typedef uint16_t U16;
typedef uint32_t U32;
#define SWAP_U16(val)  ((((val)>>8)&0x00FF)|(((val)&0x00FF)<<8))      //##(0)高低字节交换
/*###############################################################################################################################
#  引脚声明和LED驱动时许时间声明                                                                                                #
###############################################################################################################################*/
#define BTN2_PIN    PIN_B0          //##(0)按钮"2"(中断触发)
#define BTN1_PIN    PIN_G7          //##(0)按钮"1"(中断触发)
#define LED_STRIP   PIN_G8          //##(0)LED驱动引脚
#define SENSOR1_PIN PIN_B6          //##(0)传感器"1"检测引脚(中断触发)
#define SENSOR2_PIN PIN_B7          //##(0)传感器"2"检测引脚(中断触发)
#define ALERT       PIN_B10         //##(0)bq76952警告引脚检测(中断触发)
#define I2C_SDA     PIN_B14         //##(0)I2C总线数据引脚
#define I2C_SCL     PIN_B15         //##(0)I2C总线时钟引脚
#define RS485_RE    PIN_E3          //##(0)RS485串口接收使能控制引脚(0=使能接收)
#define RS485_DE    PIN_C15         //##(0)RS485串口发送使能控制引脚(1=使能发送)
#define VCC_EN      PIN_C13         //##(0)3.3V使能控制引脚(1=使能VCC)
#define RX          PIN_C14         //##(0)串口接收引脚
#define TX          PIN_F1          //##(0)串口发送引脚
#define I2C_EN      PIN_E0          //##(0)I2C总线上拉使能控制引脚(0=使能总线上拉)
#define RST_SHUT    PIN_E2          //##(0)bq76952进入关机使能控制引脚
#define SYS_INT     PIN_G3          //##(0)外部设备接入检测引脚
#define SYS_BIAS    PIN_E1          //##(0)判断外部设备接入的电阻阻值上拉基准输入
#define M24C04WC    PIN_C12         //##(0)存储器写使能引脚

#define T0H         3               //##(0)发送"0"高电平延时时间
#define T1H         T0H*2           //##(0)发送"1"高电平延时时间
#define T0L         T1H             //##(0)发送"0"低电平延时时间  
#define T1L         T0H             //##(0)发送"1"低电平延时时间

#define vref_lsb    0.800           //##(0)基准电压(每bit)
#define sys_adc     0x01            //##(0)ADC采样端口编号"SYS_ADC" 
#define i2c_ok      false           //##(0)I2C读写正确
#define i2c_Error   true            //##(0)I2C读写失败
 
#BYTE INTCON2 = 0x082               //##(0)中断控制寄存器2,由于编译器问题导致设定外部中断下降沿触发设置不了
#byte U1MODE = 0x398                //##(0)UxSTA:串口模式寄存器地址
#WORD U1STA = 0x039A                //##(0)UxSTA:状态和控制寄存器
#WORD U1RXREG = 0x39E               //##(0)UxSTA:接收寄存器
#WORD DMACNT0 = 0x4D4               //##(0)传输剩余计数寄存器,作用是 : 记录本次 DMA 还剩下多少个数据未传，每传一个自动减"1"
#WORD DMACON = 0x4C4                //##(0)DMA控制寄存器 
    #bit DMAEN = DMACON.15          //##(0)DMA使能位，DMAEN = 1：开启当前 DMA 通道,通道就绪,可响应触发信号,执行数据传输。
                                    //##(0)           DMAEN = 0：关闭当前 DMA 通道,通道停止工作,暂停/终止传输。
#WORD DMADST0 = 0x4D2               //##(0)DMA通道0目标地址寄存器。
#WORD RCON = 0x0110                  //##(0)复位控制寄存器
    #bit MSLEEP = RCON.3            //##(0)从休眠模式唤醒标志位,1 = 器件处于休眠模式
    #bit WDTO =  RCON.4             //##(0)看门狗定时器超时标志位,1 = 发生了WDT超时

/*###############################################################################################################################
#  引脚驱动宏                                                                                                                   #
###############################################################################################################################*/
#define VCC_ON          output_bit(VCC_EN,1)        //##(0)使能VCC
#define VCC_OFF         output_bit(VCC_EN,0)        //##(0)关闭VCC

#define PUST_0          output_bit(LED_STRIP,0)     //##(0)拉低"LED_STRIP"引脚
#define PUST_1          output_bit(LED_STRIP,1)     //##(0)拉高"LED_STRIP"引脚

#define SYSBIAS_ON      output_bit(SYS_BIAS,1)      //##(0)开启测量ID电阻接入阻值(输出高)
#define SYSBIAS_OFF     output_float(SYS_BIAS);     //##(0)关闭测量ID电阻接入阻值(浮空)

#define PullON          output_bit(I2C_EN,0)        //##(0)使能总线上拉
#define PullOFF         output_bit(I2C_EN,1)        //##(0)关闭总线上拉

#define transmission    output_bit(RS485_RE,1); output_bit(RS485_DE,1)      //##(0)发送使能
#define receiver        output_bit(RS485_DE,0); output_bit(RS485_RE,0)      //##(0)接受使能

/*###############################################################################################################################
# 按键宏定义声明                                                                                                                #
###############################################################################################################################*/
#define ExoType             1       //##(1)外骨架类型定义
#define NoClick_key         0       //##(1)无键按下  
#define SingleClick_key     1       //##(1)单击按下  
#define DoubleClick_key     2       //##(1)双击按下  
#define LongClick_key       3       //##(1)长按按下   
#define key_state_0         0       //##(1)按键状态0
#define key_state_1         1       //##(1)按键状态1
#define key_state_2         2       //##(1)按键状态2
#define key_state_3         3       //##(1)按键状态2
#define powerOn             1       //##(1)开机
#define powerOff            0       //##(1)关机
#define M24C04              0xA0    //##(0)M24C04-FMH6TG 设备地址
#define PageSize            16      //##(0)一个页面的字节数
#define Enable              1       //##(0)使能
#define Disable             0       //##(0)禁止
#define IDEXO               1       //##(0)插入"EXO"设备ID
#define IDCHG               2       //##(0)插入是充电器ID
#define IDERR               3       //##(0)错误的ID电阻
#define IDRMV               0       //##(0)移除ID
#define NULL_STATE          0       //##(0)电池状态/空闲
#define CHG_STATE           1       //##(0)电池状态/充电中
#define BAL_STATE           2       //##(0)电池状态/均衡中
#define DSG_STATE           3       //##(0)电池状态/放电中
#define ERR_STATE           4       //##(0)电池状态/错误
#define MODE_NULL           0       //##(0)无任何模式
#define MODE_SLEEP          1       //##(0)睡眠模式
#define	MODE_SHUTDOWN       2       //##(0)运输模式
#define MODE_EnterSLEEP     3       //##(0)命令进入睡眠模式
#define	MODE_WORK           4       //##(0)工作模式
#define MODE_ERROR          5       //##(0)错误ID模式 
                                    //##(0)阈值定义，根据你的实测值配置
#define PowerOff_cmd        1       //##(0)关机命令(SHUTDOWN)
#define brightness_cmd      2       //##(0)明度命令
#define clearfault_cmd      3       //##(0)清除故障标志
#define serialreq_cmd       4       //##(0)序列号设置命令
#define null_cmd            0       //##(0)空命令
/*###############################################################################################################################
# 内部包含驱动                                                                                                                  #
###############################################################################################################################*/
#pin_select U1TX = PIN_F1           //##(1)串口发送数据引脚
#pin_select U1RX = PIN_C14          //##(0)串口接收数据引脚
#pin_select INT1 = BTN1_PIN         //##(0)按钮"1"(中断触发)
#pin_select INT2 = BTN2_PIN         //##(0)按钮"2"(中断触发)
#pin_select INT3 = SENSOR1_PIN      //##(0)传感器"1"检测引脚(中断触发)
#pin_select INT4 = SENSOR2_PIN      //##(0)传感器"2"检测引脚(中断触发)
/*###############################################################################################################################
# 函数库                                                                                                                        #
###############################################################################################################################*/
//##(0)声明延时包含库
#use delay(internal=32MHz,restart_wdt)   
//##(0)声明串口驱动函数库/声明I2C总线驱动函数库
#ifdef _bootloader
    #use rs232(UART1,stream=rs485,baud=500000,errors,parity=n,bits=8,stop=1,receive_buffer=128,brgh1ok,restart_wdt)
    #use i2c(MASTER,  SDA=I2C_SDA, SCL=I2C_SCL, FAST=100000, FORCE_HW, stream=i2c)
#else
    #use rs232(UART1,stream=rs485,baud=500000,errors,parity=n,bits=8,stop=1,RECEIVE_BUFFER=128,brgh1ok)
    #use i2c(MASTER, I2C2, SDA=I2C_SDA, SCL=I2C_SCL, FAST=300000, FORCE_HW, stream=i2c)
#endif

/*###############################################################################################################################
 # 数据类型                                                                                                                     #
 ##############################################################################################################################*/
typedef enum{ 
    KEY_NONE = 0x00,                //##(0)无按键            
    KEY1_SHORT = 0x01,              //##(0)"+" 短按
    KEY1_LONG  = 0x02,              //##(0)"+" 长按
    KEY2_SHORT = 0x03,              //##(0)"-" 短按
    KEY2_LONG  = 0x04,              //##(0)"-" 长按
    KEY_BOTH_SHORT = 0x05,          //##(0)双键短按
    KEY_BOTH_LONG  = 0x06,          //##(0)双键长按       
    KEY1_LLONG = 0x07,              //##(0)"+" 超长按    
    KEY2_LLONG = 0x08               //##(0)"-" 超长按     
}KeyStatus;                         //##(0)按键状态枚举
/*###############################################################################################################################
 # 变量和标志                                                                                                                   #
 ##############################################################################################################################*/
typedef struct {                    //##(0)Modbus 上下文：记录当前发送的地址/数量，用于接收匹配
    uint16_t StartAddress;          //##(0)起始地址
    uint16_t Quantity;              //##(0)待读寄存器个数
     uint8_t Function;              //##(0)功能吗
     boolean UsrtBusy;              //##(0)串口忙标志
     uint8_t timeout;               //##(0)请求超时应答计时器
}mb_ctx_t;

typedef union{
    uint16_t u16;                   //##(0)占用2个字节
    struct{
        uint8_t Chain;              //##(0)链起始位置(低字节)
        uint8_t Fade;               //##(0)渐变类型(高字节) 
    };
}AnimMetadata1;                     //##(0)动画元数据1 66

typedef union{
    uint16_t u16;                   //##(0)占用2个字节
    struct{
        uint8_t Enqueue;            //##(0)入队动画(低字节)
    };
}AnimMetadata2;                     //##(0)动画元数据2 67

typedef union{
    uint16_t u16;                   //##(0)占用2个字节
    struct{
        uint8_t Status;             //##(0)入队动画(低字节)
    };
}Insertion_t;                       //##(0)插入检测,0x00 = 未插入； 0x01 = 已插入

typedef union{
    uint16_t u16;                   //##(0)占用2个字节
     uint8_t u8[2];                 //##(0)  
    struct{
        uint8_t CUV:1;              //##(0)电池欠压故障
        uint8_t COV:1;              //##(1)电池过压故障
        uint8_t OCC:1;              //##(2)充电过流故障
        uint8_t OCD:1;              //##(3)放电过流故障
        
        uint8_t SCD:1;              //##(4)放电短路故障
        uint8_t UTC:1;              //##(5)充电欠温故障
        uint8_t UTD:1;              //##(6)放电欠温故障
        uint8_t OTC:1;              //##(7)充电过热故障
        
        uint8_t OTD:1;              //##(8)放电过热故障
        uint8_t bqxxx:1;            //##(9)无法与管理芯片通讯
        uint8_t TS1:1;              //##(10)第【1】路"NTC"温度传感器故障
        uint8_t TS2:1;              //##(11)第【2】路"NTC"温度传感器故障
        
        uint8_t TS3:1;              //##(12)第【3】路"NTC"温度传感器故障
        uint8_t TS4:1;              //##(13)第【4】路"NTC"温度传感器故障
        uint8_t TS5:1;              //##(14)BMS电路板自身温度检测故障
        uint8_t COM:1;              //##(15)通讯无应答故障
    };   
}FauluLive_t;                       //##(0)电池故障状态(实时)

typedef union{
    uint16_t u16;                   //##(0)占用2个字节
     uint8_t u8[2];                 //##(0)    
    struct{
        uint8_t SUV  :1;            //## 电芯欠压安全永久失效
        uint8_t SOV  :1;            //## 电芯过压安全永久失效
        uint8_t SOCC :1;            //## 充电过流安全永久失效
        uint8_t SOCD :1;            //## 放电过流安全永久失效
        uint8_t SOT  :1;            //## 过热安全永久失效 
        uint8_t      :1;            //## 保留位
        uint8_t SOTF :1;            //## FET 过热安全永久失效
        uint8_t CUDEP:1;            //## 铜沉积永久失效
        
        uint8_t CFETF:1;            //## 充电 FET 永久失效
        uint8_t DFETF:1;            //## 放电 FET 永久失效
        uint8_t _2LVL:1;            //## 二级保护器永久失效
        uint8_t VIMR :1;            //## 静态模式电压不平衡永久失效
        uint8_t VIMA :1;            //## 激活模式电压不平衡永久失效
        uint8_t      :2;            //## 保留位
        uint8_t SCDL :1;            //## 放电短路锁存永久失效
    };   
}FaultPersist_t;                    //##(0)电池持久故障寄存器

volatile struct{
    union{
        uint32_t word;              //##(0)全局标志占用4个字节
        struct{
            uint8_t MsgPrint:1;     //##(0)打印信息使能标志"1"=打印/"0"=不打印
            uint8_t ImmedPrint:1;   //##(0)立即打印信息
            uint8_t IDType  :3;     //##(0)ID电阻类型         
            uint8_t RunMode :3;     //##(0)运行模式"powerOn" = 开机 ， powerOff = 关机
            uint8_t button1 :1;     //##(0)按钮"1"中断标志
            uint8_t button2 :1;     //##(0)按钮"2"中断标志
            uint8_t Sensor1 :1;     //##(0)传感器"1"中断标志.
            uint8_t Sensor2 :1;     //##(0)传感器"1"中断标志
            uint8_t ChgProc :1;     //##(0)电池充电显示 "1" = 正在充电
            uint8_t sysint  :1;     //##(0)SYS_INT引脚唤醒标志
            uint8_t AnimEn  :1;     //##(0)动画显示使能标志,"1" = 显示响应动画
            uint8_t BattFull:1;     //##(0)电池满电   
            uint8_t RequestSN:1;    //##(0)"1"=使能请求序列号
            uint8_t ReqBright:1;    //##(0)"1"=使能请求全局亮度	
            uint8_t NoComTmrEn:1;   //##(0)无通讯计时使能标志
            uint8_t ReqInfoDone :1; //##(0)开机/上电请求信息完成标志"1"=完成请求   
            uint8_t ReqAnimsDone:1; //##(0)请求动画完成,"1"= 请求完成,"0"=请求未完成
            uint8_t TransmitInfo:1; //##(0)"1"=已经发送过基本信息,"0"=没有发送过 , 启动发送一次
            uint8_t mcuSleep:1;     //##(0)MCU进入睡眠
            uint8_t AnimFinish:1;   //##(0)动画播放完成标志 0 = 播放完成
            uint8_t NoWdtWakeup:1;  //##(0)不是看门狗唤醒,1 = 不是看门狗唤醒
            };
    }flags;
//##(0)按键状态寄存器 
     uint8_t bqErrorCount;          //##(0)读取"ba76952"失败计数器
    uint16_t PrintDelay;            //##(0)打印信息周期延时
     uint8_t LastMode;              //##(0)上次运行模式
     uint8_t LastIDType;            //##(0)历史"ID"错误【比较使用】
    uint16_t LastFault;             //##(0)历史临时故障【比较使用】
    uint16_t NoCommTimeout;         //##(0)没有通讯超时计时器 
    uint16_t system5ms;             //##(0)定时器1定时5毫秒计数器(每次中断递增)
    uint16_t time10ms;              //##(0)定时器1定时10毫秒计数器(每次中断递增)
    uint16_t system1000ms;          //##(0)定时器2定时1000毫秒计数器(每次中断递增)
    uint16_t resttimer;
    uint16_t commands;              //##(0)命令暂存器
    uint16_t RunTimeout;            //##(0)测试，开机运行2分钟进入关机模式
     uint8_t rxTimeout;             //##(0)没有收到字节超时计时器,收到字节则清零
     uint8_t keyState;              //##(0)按键状态
     uint8_t keyCurrState;          //##(0)按键状态
     uint8_t FOLD;                  //##(0)折叠状态【0=展开/1=折叠】
     uint8_t STRAP;                 //##(0)绑带状态【0=绑带移除/1=绑带接上】
       float prevAngle;             //##(0)上一次的角度值（保存旧角度）
       float currAngle;             //##(0)当前角度值
     uint8_t angle_hyst;            //##(0)角度变化阈值(1°/ 2°/ 3°/ 8°)
       float lastX;                 //##(0)保存上一次X轴磁场
       float lastY;                 //##(0)保存上一次Y轴磁场
       float lastZ;                 //##(0)保存上一次Z轴磁场
    mb_ctx_t Request;               //##(0)声明一个结构体
     uint8_t chain;                 //##(0)每组动画的链步
     uint8_t FadeType;              //##(0)动画与动画直接过渡渐变类型,【0x01=淡出再淡入/0x02=仅淡出/0x03=直接切帧】
    uint16_t DeviceType;            //##(0)接入的设备类型
    uint16_t GlobalBright;          //##(0)全局亮度（LED 主亮度）
    uint16_t AnimQty;               //##(0)动画数量(有几组动画)
    uint16_t ReqAnimsAddress;       //##(0)请求动画地址
     uint8_t recvAnimCnt;            //##(0)接收动画组计数器
    uint16_t FadeOutDuration;       //##(0)通用淡出时长（ms）
    uint16_t FadeInDuration;        //##(0)通用淡入时长（ms）
    uint16_t HallSensorStatus;      //##(0)霍尔数据流使能/禁止状态
    uint16_t FOLD_STATUS;           //##(0)折叠/展开霍尔传感器当前状态
    uint16_t NextAction;            //##(0)【 0=无操作/1=关机/2=引导程序/3=请求读取/4=清除永久故障寄存器/5=请求读取电池序列号】 64
    uint16_t AnimationID;           //##(0)"LED"动画ID【任意动画 ID 0~N】  65
    uint16_t ErrorCode;             //##(0)故障代码
 FauluLive_t FaultLive;             //##(0)电池故障状态(实时)
 FauluLive_t FaultHistory;          //##(0)电池故障状态(历史)
 FauluLive_t LastFaultPersist;      //##(0)最近一次电池故障状态
      Insertion_t Insertion;        //##(0)插入检测,0x00 = 未插入； 0x01 = 已插入 
    AnimMetadata1 AnimMR1;          //##(0)动画元数据1 66
    AnimMetadata2 AnimMR2;          //##(0)动画元数据2 67,入队动画,当前动画结束后排队播放的动画    
          uint8_t LastAnimationID;  //##(0)保存当前动画ID
    AnimMetadata1 LastAnimMR1;      //##(0)动画元数据1 66
    AnimMetadata2 LastAnimMR2;      //##(0)动画元数据2 67,入队动画,当前动画结束后排队播放的动画  
}regs;                              //##(0)全局变量

 uint8_t SM_StateMachine;           //##(0)静态显示模式状态机)
 uint8_t CM_StateMachine;           //##(0)跑马显示灯模式状态机
 uint8_t FM_StateMachine;           //##(0)渐变显示模式状态机
 uint8_t BM_StateMachine;           //##(0)
 boolean DispBattFull;              //##(0)刷新电池充满动画"1"=刷新过
 boolean isShowFault;               //##(0)是否显示故障/故障显示使能标志
 boolean FaultShowUpdata;           //##(0)故障画面刷新显示
 boolean bPowerOffAnimDone;         //##(0)已经播放过关机动画【1=已经播放过,0=没有播放过】	
 boolean IDTypeError;               //##(0)"ID"电阻类型错误
 boolean FualtPFStatus;             //##(0)"PF"故障状态,电芯低于2.5V则设置此标志为"1",上电检查此标志，如果此标志为"1"则关闭电池充放电FET
uint16_t FualtShowDelay;            //##(0)故障画面显示时长

#define dmaSize 200                 //##(0)串口DMA接收缓冲区大小 = 512个字节
volatile struct{
    uint8_t buffer[dmaSize];        //##(0)接收缓冲区数组长度为300个字节
   uint16_t buffidx;                //##(0)接收字节数累加器
    boolean ReceiveCompleted;       //##(0)串口接收帧完成
    boolean bootFormat;             //##(0)引导数据格式
    boolean normalFormat;           //##(0)正常通讯格式
    boolean testFormat;             //##(0)测试模式通讯格式
}uart;                              //##(0)声明一个串口结构体
/*###############################################################################################################################
# 正常通讯枚举声明                                                                                                              #
# 01 (0x01)	Read DO                 Read Coil Status            Discrete	Read                                                 #
# 02 (0x02)	Read DI                 Read Input Status           Discrete	Read                                                 #
# 03 (0x03)	Read AO                 Read Holding Registers      16 bit	Read                                                 #
# 04 (0x04)	Read AI                 Read Input Registers        16 bit	Read                                                 #
# 05 (0x05)	Write one DO            Force Single Coil           Discrete	Write                                                #
# 06 (0x06)	Write one AO            Preset Single Register      16 bit	Write                                                #
# 15 (0x0F)	Multiple DO recording   Force Multiple Coils        Discrete	Write                                                #
# 16 (0x10)	Multiple AO recording   Preset Multiple Registers   16 bit	Write                                                #
 ##############################################################################################################################*/
#define ServerAddress   0x01                //##(0)主机地址
/*###############################################################################################################################
# 06 (0x06) Write one AO Preset Single Register 16 bit	Write                                                                   #
###############################################################################################################################*/
typedef enum{
    MB_F6_IN_ADDRESS = 0,                   //##(0)设备地址从第 0 个字节算起 
    MB_F6_IN_FUNCTION = 1,                  //##(0)功能代码
    MB_F6_IN_ADDR_HI = 2,                   //##(0)起始地址高字节从第 2 个字节算起
    MB_F6_IN_ADDR_LO = 3,                   //##(0)起始地址低字节从第 3 个字节算起
    MB_F6_IN_DATA_HI = 4,                   //##(0)寄存器数量高字节从第 4 个字节算起
    MB_F6_IN_DATA_LO = 5,                   //##(0)寄存器数量低字节从第 5 个字节算起
}mb_message_f6_in_t;                        //##(0)将值写入单个保持寄存器【设备--->电池,电池作为接收端】

typedef enum{
    MB_F6_OUT_ADDRESS = 0,                  //##(0)设备地址从第 0 个字节算起 
    MB_F6_OUT_FUNCTION = 1,                 //##(0)功能代码
    MB_F6_OUT_ADDR_HI = 2,                  //##(0)起始地址高字节从第 2 个字节算起
    MB_F6_OUT_ADDR_LO = 3,                  //##(0)起始地址低字节从第 3 个字节算起
    MB_F6_OUT_DATA_HI = 4,                  //##(0)寄存器数量高字节从第 4 个字节算起
    MB_F6_OUT_DATA_LO = 5,                  //##(0)寄存器数量低字节从第 5 个字节算起
}mb_message_f6_out_t;                       //##(0)正常响应是请求的回声【电池--->设备,电池作为发送端】
/*###############################################################################################################################
# 16 (0x10) Multiple AO recording  Preset Multiple Registers 16 bit Write                                                       #
###############################################################################################################################*/
typedef enum{
    MB_F16_IN_ADDRESS = 0,                  //##(0)设备地址从第 0 个字节算起 
    MB_F16_IN_FUNCTION = 1,                 //##(0)功能代码
    MB_F16_IN_ADDR_HI = 2,                  //##(0)起始地址高字节从第 2 个字节算起
    MB_F16_IN_ADDR_LO = 3,                  //##(0)起始地址低字节从第 3 个字节算起
    MB_F16_IN_QTY_HI = 4,                   //##(0)寄存器数量高字节从第 4 个字节算起
    MB_F16_IN_QTY_LO = 5,                   //##(0)寄存器数量低字节从第 5 个字节算起
}mb_message_f16_in_t;                       //##(0)输入信息格式【设备--->电池,电池作为接收端】

typedef enum{
    MB_F16_OUT_ADDRESS = 0,                 //##(0)设备地址从第 0 个字节算起     
    MB_F16_OUT_FUNCTION = 1,                //##(0)功能代码从第 1 个字节算起
    MB_F16_OUT_ADDR_HI = 2,                 //##(0)起始地址高字节从第 2 个字节算起
    MB_F16_OUT_ADDR_LO = 3,                 //##(0)起始地址低字节从第 3 个字节算起
    MB_F16_OUT_QTY_HI = 4,                  //##(0)寄存器数量高字节从第 4 个字节算起
    MB_F16_OUT_QTY_LO = 5,                  //##(0)寄存器数量低字节从第 5 个字节算起
    MB_F16_OUT_BYTE_CNT = 6,                //##(0)发送的有效字节数从第 6 个字节算起
    MB_F16_OUT_DATA_START = 7,              //##(0)起始数据从第 7 个字节算起
}mb_message_f16_out_t;                      //##(0)将值写入一系列保持寄存器【电池--->设备,电池作为发送端】
                                          
typedef enum MB_FC{
    MB_FC_READ_COILS = 1,                   //##(0)[Read DO] read coils or digital outputs
    MB_FC_READ_DISCRETE_INPUT = 2,          //##(0)[Read DI] read digital inputs 
    MB_FC_READ_REGISTERS = 3,               //##(0)[Read AO] 读取保持寄存器或模拟输出量
    MB_FC_READ_INPUT_REGISTER = 4,          //##(0)[Read AI] read analog inputs
    MB_FC_WRITE_COIL = 5,                   //##(0)[Write one DO] write single coil or output 
    MB_FC_WRITE_REGISTER = 6,               //##(0)[Write one AO] write single register 
    MB_FC_WRITE_MULTIPLE_COILS = 15,        //##(0)[Multiple DO recording] write multiple coils or outputs 
    MB_FC_WRITE_MULTIPLE_REGISTERS = 16     //##(0)[Multiple AO recording] write multiple registers,写多个寄存器 
}mb_functioncode_t;                         //##(0)功能代码枚举

typedef enum{
    None = 0,                               //##(0)无类型
    FadeOutIn = 1,                          //##(0)淡出再淡入
    FadeOut = 2,                            //##(0)仅淡出
    FadeIntoNext = 3,                       //##(0)直接切帧  
}fade_type;                                 //##(0)渐变类型[0x65高字节]

typedef enum{
    NoAction = 0,                           //##(0)无操作
    Shutdown = 1,                           //##(0)关机
    Bootloader = 2,                         //##(0)引导程序触发
    ReadGlobalBrightnes = 3,                //##(0)请求读取全局亮度
    ClearFaultRegister = 4,                 //##(0)清除永久故障寄存器
    ReadBatterySerialNumber = 5,            //##(0)请求读取电池序列号     
}NextAction;                                //##(0)操作寄存器枚举[0x64]
/*###############################################################################################################################
# 命令ID地址寄存器枚举                                                                                                          #
###############################################################################################################################*/
typedef enum{
//##(0)设备寄存器
    MB_REG_DEVICE_TYPE = 0,                 //##(0)设备类型 0x00 = 无/未知；0x01 = 外骨骼；0x02 = 充电器；0x03 = 调试
    MB_REG_EXO_VERSION_MAJ = 1,             //##(0)外骨骼版本(主)           
    MB_REG_EXO_VERSION_MIN = 2,             //##(0)外骨骼版本(次)
    MB_REG_EXO_VERSION_PAT = 3,             //##(0)外骨骼版本(补丁)
    MB_REG_EXO_FW_VERSION_MAJ = 4,          //##(0)外骨骼固件版本(主)
    MB_REG_EXO_FW_VERSION_MIN = 5,          //##(0)外骨骼固件版本(次)
    MB_REG_EXO_FW_VERSION_PAT = 6,          //##(0)外骨骼固件版本(补丁)
    MB_REG_GB_Brightness = 7,               //##(0)全局亮度
    MB_REG_LED_FADE_OUT_DURATION = 8,       //##(0)通用淡出时长（ms）
    MB_REG_LED_FADE_IN_DURATION = 9,        //##(0)通用淡入时长（ms）
    MB_REG_HALL_STREAM_EN = 10,             //##(0)霍尔传感器流使能 0x00 = 关闭（默认）；0x01 = 开启
    MB_REG_LED_ANIMATION_Qty = 11,          //##(0)动画数量  
//##(0)保留给11-127以供将来使用
    MB_REG_BAT_NextAction = 64,             //##(0)操作寄存器【16*1】
                                            //##(0)【 0=无操作/1=关机/2=引导程序/3=请求读取/4=清除永久故障寄存器/5=请求读取电池序列号】
    MB_REG_BAT_LED_Animation = 65,          //##(0)当前待显示动画 ID 【16*1】
    MB_REG_BAT_AnimationMR = 66,            //##(0)动画过渡,队列参数 66~67【16*2】    
//##(0)电池注册信息【启动时发送,电池主动发送】
    MB_REG_BAT_SerialNumber = 128,          //##(0)唯一的电池序列号【可外部写入,保存在EEPROM中】 128~135【16*6】    
                                            //##(0)开机执行一次
    MB_REG_BAT_BMSFirmwareVersion = 136,    //##(0)BMS 固件版本【主要/次要/批量】136~138【16*3】         
    MB_REG_BAT_BMSHardwareVersion = 139,    //##(0)BMS 硬件版本【厂商ID /主版本，保存在EEPROM中】139~140【16*2】          
//##(1)电池信息命令地址
    MB_REG_BAT_SOH = 141,                   //##(0)电池健康度141【16*1】
    MB_REG_BAT_CCC = 142,                   //##(0)充电循环次数142【16*1】        
    MB_REG_BAT_DCC = 143,                   //##(0)放电循环次数143【16*1】             
    MB_REG_BAT_STATE = 144,                 //##(0)电池状态标志【16*1 0=Idle/1=Charging/2=Balancing/3=Discharge/4=Error】          
    MB_REG_BAT_InsertionDetection = 145,    //##(0)电池插入状态【16*1,已插入/未插入】        
    MB_REG_BAT_FaultStatus = 146,           //##(0)电池故障状态【16*1】  
    MB_REG_BAT_BUTTON_PRESSED = 150,        //##(1)电池按钮按下状态【16*1】        
    MB_REG_BAT_ERROR_CODE = 151,            //##(1)电池错误代码【16*1】   
    MB_REG_BAT_STRAP_DETECTED = 152,        //##(1)霍尔传感器状态【16*1, 0=未连接/1=连接】      
    MB_REG_BAT_FOLD_DETECTED = 153,         //##(0)检测到霍尔传感器变化，折叠检测【0=展开/1=折叠】 
    MB_REG_BAT_SOC = 160,                   //##(0)电池相对容量百分比【16*1】    
    MB_REG_BAT_CURRENT_DISCHARGE = 161,     //##(0)电池充/放电电流【16*1】        
    MB_REG_BAT_STACK_VOLTAGE = 162,         //##(0)电池堆积电压【16*1】        
    MB_REG_BAT_CELL_IMBALANCE = 163,        //##(0)电池平衡状态【16*1】
    MB_REG_BAT_Temperature = 164,           //##(0)电池温度【16*1】
    MB_REG_BAT_FilteredCurrent = 165,       //##(0)滤波电流【16*1】   
    MB_REG_BAT_CELL_VOLT1 = 166,            //##(0)电芯"1"电压【16*1】
    MB_REG_BAT_CELL_VOLT2 = 167,            //##(0)电芯"2"电压【16*1】
    MB_REG_BAT_CELL_VOLT3 = 168,            //##(0)电芯"3"电压【16*1】
    MB_REG_BAT_CELL_VOLT4 = 169,            //##(0)电芯"4"电压【16*1】
    MB_REG_BAT_CELL_VOLT5 = 170,            //##(0)电芯"5"电压【16*1】
    MB_REG_BAT_CELL_VOLT6 = 171,            //##(0)电芯"6"电压【16*1】
    MB_REG_BAT_CELL_VOLT7 = 172,            //##(0)电芯"7"电压【16*1】
    MB_REG_BAT_CELL_VOLT8 = 173,            //##(0)电芯"8"电压【16*1】
    MB_REG_BAT_CELL_VOLT9 = 174,            //##(0)电芯"9"电压【16*1】
    MB_REG_BAT_CELL_VOLT10 = 175,           //##(0)电芯"10"电压【16*1】
    MB_REG_BAT_CELL_VOLT11 = 176,           //##(0)电芯"11"电压【16*1】
    MB_REG_BAT_CELL_VOLT12 = 177,           //##(0)电芯"12"电压【16*1】           
    MB_REG_BAT_ThermistorTemp1 = 178,       //##(0)热敏电阻温度1【16*1】
    MB_REG_BAT_ThermistorTemp2 = 179,       //##(0)热敏电阻温度2【16*1】
    MB_REG_BAT_ThermistorTemp3 = 180,       //##(0)热敏电阻温度3【16*1】
    MB_REG_BAT_ThermistorTemp4 = 181,       //##(0)热敏电阻温度4【16*1】
//##(0)霍尔传感器（绑带）            
    MB_REG_BAT_HALL_STRAPX = 190,           //##(0)绑带磁场强度(mT)X轴,传感器U17【16*1】
    MB_REG_BAT_HALL_STRAPY = 191,           //##(0)绑带磁场强度(mT)Y轴,传感器U17【16*1】
    MB_REG_BAT_HALL_STRAPZ = 192,           //##(0)绑带磁场强度(mT)Z轴,传感器U17【16*1】
    MB_REG_BAT_HALL_STRAP_ANGLE = 193,      //##(0)绑带角度(度),传感器U17           
    MB_REG_BAT_HALL_STRAP_MAGNITUTE = 194,  //##(0)绑带幅度(mT),传感器U17
//##(0)霍尔传感器（折叠）             
    MB_REG_BAT_HALL_FOLDX = 195,            //##(0)折叠磁场强度(mT)X轴,传感器U18【16*1】
    MB_REG_BAT_HALL_FOLDY = 196,            //##(0)折叠磁场强度(mT)X轴,传感器U18【16*1】
    MB_REG_BAT_HALL_FOLDZ = 197,            //##(0)折叠磁场强度(mT)X轴,传感器U18【16*1】
    MB_REG_BAT_HALL_FOLD_ANGLE = 198,       //##(0)折叠角度(度),传感器U18【16*1】
    MB_REG_BAT_HALL_FOLD_MAGNITUTE = 199,   //##(0)折叠幅度(mT),传感器U18【16*1】
//##(0)LED动画寄存器（8个LED对应8个动画）/ 每个动画有5个步骤,每个步骤16个字节 = 80个字节/2 = 40个寄存器)
    MB_REG_BAT_LED_ANIMATION0  = 256,        //##(0)LED"1"动画寄存器【16*40】       
    MB_REG_BAT_LED_ANIMATION1  = 296,        //##(0)LED"2"动画寄存器【16*40】       
    MB_REG_BAT_LED_ANIMATION2  = 336,        //##(0)LED"3"动画寄存器【16*40】
    MB_REG_BAT_LED_ANIMATION3  = 376,        //##(0)LED"4"动画寄存器【16*40】      
    MB_REG_BAT_LED_ANIMATION4  = 416,        //##(0)LED"5"动画寄存器【16*40】        
    MB_REG_BAT_LED_ANIMATION5  = 456,        //##(0)LED"6"动画寄存器【16*40】          
    MB_REG_BAT_LED_ANIMATION6  = 496,        //##(0)LED"7"动画寄存器【16*40】         
    MB_REG_BAT_LED_ANIMATION7  = 536,        //##(0)LED"8"动画寄存器【16*40】 
    MB_REG_BAT_LED_ANIMATION8  = 576,  
    MB_REG_BAT_LED_ANIMATION9  = 616,
    MB_REG_BAT_LED_ANIMATION10 = 656,
    MB_REG_BAT_LED_ANIMATION11 = 696,
    MB_REG_BAT_LED_ANIMATION12 = 736,
    MB_REG_BAT_LED_ANIMATION13 = 776,
    MB_REG_BAT_LED_ANIMATION14 = 816,
    MB_REG_BAT_LED_ANIMATION15 = 856,
    MB_REG_BAT_LED_ANIMATION16 = 896,
    MB_REG_BAT_LED_ANIMATION17 = 936,
    MB_REG_BAT_LED_ANIMATION18 = 976,
    MB_REG_BAT_LED_ANIMATION19 = 1016		//##(0)LED"20"动画寄存器【16*40】 
}mb_registers_t;

//##(0)电池开启后读取一次特定信息,
const uint16_t StartAddr[][2] = {
    {MB_REG_DEVICE_TYPE,          0x0001},      //##(0)设备类型,读取1个寄存器
    {MB_REG_GB_Brightness,        0x0001},      //##(0)全局亮度,读取1个寄存器
    {MB_REG_LED_FADE_OUT_DURATION,0x0002},      //##(0)通用淡出/淡入时长,读取2个寄存器   
    {MB_REG_HALL_STREAM_EN,       0x0001},      //##(0)启用/禁用霍尔传感器数据流到 190+ 寄存器,读取1个寄存器
    {MB_REG_LED_ANIMATION_Qty,    0x0001}       //##(0)告知电池从 256+ 寄存器加载多少个动画块,读取1个寄存器
};
/*###############################################################################################################################
#  应用声明结束                                                                                                                 #
###############################################################################################################################*/
#ifdef	__cplusplus
}
#endif
#endif

