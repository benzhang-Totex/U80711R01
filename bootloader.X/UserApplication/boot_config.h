/*###############################################################################################################################
 # 文件名称 ： U80711R01_CONFIG_H.H                                                                                             #
 # 公司名称 :  TOTEX Technology, Inc.                                                                                           #
 # 芯片型号 ： PIC24FJ128GA302                                                                                                  #
 # 编译工具 :  ccs compiler v5.118                                                                                              #
 # 作    者 :  BenZhang                                                                                                         #
 # 编写日期 :  2025/11/10                                                                                                       #
 # 版    本 :  v1.00                                                                                                            #
 ##############################################################################################################################*/
#ifndef BOOT_CONFIG_H 				//##(0)
#define	BOOT_CONFIG_H

#define _bootloader                 //##(0)声明为引导程序(屏蔽则为应用程序段/否则为BOOTLOADER程序段)
#define updata_address  0x01A00     //##(0)保存升级标识地址
/*###############################################################################################################################
# 版本信息和编译日期                                                                                                           #
###############################################################################################################################*/
const char *CompilationDate = "2026/05/08";       //##(0)固件生成日期
const char *FirmwareVersion = "bootloader";       //##(0)版本号
/*###############################################################################################################################
# 库文件                                                                                                                        #
###############################################################################################################################*/
#define  PIC24FJ                //##(0)芯片类别
#include <24FJ128GL302.h>       //##(0)芯片型号
#device  ADC = 12               //##(0)ADC 读取结果 = 12位
//#device  ICD = 3                //##(0)启动端口PGD3仿真
#include <stdlib.h>             //##(0)标准库头文件
#include <stdbool.h>            //##(0)布尔类型
#include <stdio.h>              //##
#include <stdlib.h>             //##
#include <stdint.h>             //##
#include <string.h>             //##
#include "pcd_bootloader.h"     //##
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
#FUSES NOIESO                   //##(0)0 = 禁止 IESO 模式（双速启动）
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
//#FUSES ICSP3                    //##(0)ICD通信通道选择位(通过PGC3/PGD3进行通信)
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
typedef union{ uint32_t U32; uint16_t U16[2];  uint8_t U8[4]; }bufferU32;	
typedef union{ uint16_t U16; uint8_t U8[2]; }bufferU16;

/*###############################################################################################################################
#  引脚声明和LED驱动时许时间声明                                                                                                #
###############################################################################################################################*/
#define BTN2        PIN_B0          //##(0)按钮"2"(中断触发)
#define BTN1        PIN_G7          //##(0)按钮"1"(中断触发)
#define LED_STRIP   PIN_G8          //##(0)LED驱动引脚
#define SENSOR1     PIN_B6          //##(0)传感器"1"检测引脚(中断触发)
#define SENSOR2     PIN_B7          //##(0)传感器"2"检测引脚(中断触发)
#define ALERT       PIN_B10         //##(0)bq76952警告引脚检测(中断触发)
#define SDA         PIN_B14         //##(0)I2C总线数据引脚
#define SCL         PIN_B15         //##(0)I2C总线时钟引脚
#define RS485_RE    PIN_E3          //##(0)RS485串口接收使能控制引脚(0=使能接收)
#define RS485_DE    PIN_C15         //##(0)RS485串口发送使能控制引脚(1=使能发送)
#define VCC_EN      PIN_C13         //##(0)3.3V使能控制引脚(1=使能VCC)
#define RX          PIN_C14         //##(0)串口接收引脚
#define TX          PIN_F1          //##(0)串口发送引脚
#define I2C_EN      PIN_E0          //##(0)I2C总线上拉使能控制引脚(0=使能总线上拉)
#define RST_SHUT    PIN_E2          //##(0)bq76952进入关机使能控制引脚

#define T0H         3               //##(0)发送"0"高电平延时时间
#define T1H         T0H*2           //##(0)发送"1"高电平延时时间
#define T0L         T1H             //##(0)发送"0"低电平延时时间  
#define T1L         T0H             //##(0)发送"1"低电平延时时间

                                    //##(0)绿色 -> 红色 -> 蓝色
#define BLACK       0x00000000      //##(0)黑色
#define Green       0x000000FF      //##(0)绿色
#define RED         0x0000FF00      //##(0)红色
#define Blue        0x00FF0000      //##(0)蓝色
#define White       0x00FFFFFF      //##(0)白色

#define Purple      0x00FFFF00      //##(0)紫色

#define ShowNull    0x00            //##(0)关闭显示
#define ShowRed     0x01            //##(0)显示红色,更新失败
#define ShowGreen   0x02            //##(0)显示绿色,更新完成
#define ShowWhite   0x03            //##(0)显示白色,BOOT模式
#define ShowMarquee 0x04            //##(0)跑马灯显示,更新代码过程
#define ShowPurple  0x05

#byte U1MODE = 0x398                //##(0)串口模式寄存器地址
/*###############################################################################################################################
#  引脚驱动宏                                                                                                                   #
###############################################################################################################################*/
#define VCC_ON          output_bit(VCC_EN,1)                                //##(0)使能VCC
#define VCC_OFF         output_bit(VCC_EN,0)                                //##(0)关闭VCC

#define PUST_0          output_bit(LED_STRIP,0)                             //##(0)拉低"LED_STRIP"引脚
#define PUST_1          output_bit(LED_STRIP,1)                             //##(0)拉高"LED_STRIP"引脚

#define transmission    output_bit(RS485_RE,1); output_bit(RS485_DE,1)      //##(0)发送使能
#define receiver        output_bit(RS485_DE,0); output_bit(RS485_RE,0)      //##(0)接受使能

/*###############################################################################################################################
# 内部包含驱动                                                                                                                  #
###############################################################################################################################*/
#pin_select U1TX = PIN_F1                   //##(1)串口【1】驱动
#pin_select U1RX = PIN_C14
#use delay(internal=32MHz,restart_wdt)      //##(0)延时包含库
#ifdef _bootloader
#use rs232(UART1,stream=rs485,baud=500000,errors,parity=n,bits=8,stop=1,receive_buffer=0, timeout=100, brgh1ok, restart_wdt)
#else
#use rs232(UART1,stream=rs232,baud=115200,errors,parity=n,bits=8,stop=1,RECEIVE_BUFFER=64,BRGH1OK)
#endif

/*###############################################################################################################################
 # 变量和标志                                                                                                                   #
 ##############################################################################################################################*/
volatile struct{
    union{
        uint16_t word;                      //##(0)占用2个字节
        struct{
            uint8_t enableBootMode :1;      //##(0)是否进入更新代码标志 "1" = 进入更新代码
            uint8_t EraseEnableROM :1;      //##(0)使能擦除ROM标志,"1"=使能擦除
            uint8_t EraseFinishROM :1;      //##(0)用户区域擦除完成标志,"1"=擦除完成
            uint8_t receiveStart   :1;      //##(0)串口接收数据开始标志(收到有效起始码)
            uint8_t receiveFinish  :1;      //##(0)串口接收数据完成标志
        };        
    }bits;
    uint8_t buffidx;                        //##(0)接收数据字节索引(字节数)
    uint8_t buffer[64];                     //##(0)接收数据缓冲区
   uint16_t code_crc16;                     //##(0)整个"Hex"文件计算的校验码
    uint8_t checksum;                       //##(0)行代码计算的校验和
    uint8_t wlength;                        //##(0)每行代码有效数据长度(不包含地址和行代码类型)
    uint8_t code_type;                      //##(0)代码行的类型
  bufferU32 WriteAdress;                    //##(0)编程地址(线性定位地址)32bit
   uint16_t time10ms;                       //##(0)定时10毫秒计数器
    uint8_t LEDsDisplayStatus;              //##(0)LED状态显示
    uint8_t LEDsLocation;                   //##(0)跑马灯显示当前显示LED位置  
}boot;

/*###############################################################################################################################
 # LED                                                                                                                         #
 ##############################################################################################################################*/

typedef union{
    bufferU32 word;                         //##(0)三基色数据
    struct{
	uint8_t B:8;                        //##(0)LED 红色
	uint8_t R:8;                        //##(0)LED 绿色
	uint8_t G:8;                        //##(0)LED 蓝色
    };
}color;                                     //##(0)单个LED颜色

//##(0)跑马灯颜色表格	
const uint32_t MarqueeLeds_Tab[16][8] = {   
    { Purple, BLACK,  BLACK,  BLACK,  BLACK,  BLACK,  BLACK,  BLACK  },
    { Purple, Purple, BLACK,  BLACK,  BLACK,  BLACK,  BLACK,  BLACK  },
    { Purple, Purple, Purple, BLACK,  BLACK,  BLACK,  BLACK,  BLACK  },
    { Purple, Purple, Purple, Purple, BLACK,  BLACK,  BLACK,  BLACK  },
    { Purple, Purple, Purple, Purple, Purple, BLACK,  BLACK,  BLACK  },
    { Purple, Purple, Purple, Purple, Purple, Purple, BLACK,  BLACK  },
    { Purple, Purple, Purple, Purple, Purple, Purple, Purple, BLACK  },
    { Purple, Purple, Purple, Purple, Purple, Purple, Purple, Purple },
    { BLACK,  Purple, Purple, Purple, Purple, Purple, Purple, Purple },
    { BLACK,  BLACK,  Purple, Purple, Purple, Purple, Purple, Purple },
    { BLACK,  BLACK,  BLACK,  Purple, Purple, Purple, Purple, Purple },
    { BLACK,  BLACK,  BLACK,  BLACK,  Purple, Purple, Purple, Purple },
    { BLACK,  BLACK,  BLACK,  BLACK,  BLACK,  Purple, Purple, Purple },
    { BLACK,  BLACK,  BLACK,  BLACK,  BLACK,  BLACK,  Purple, Purple },
    { BLACK,  BLACK,  BLACK,  BLACK,  BLACK,  BLACK,  BLACK,  Purple }, 
    { BLACK,  BLACK,  BLACK,  BLACK,  BLACK,  BLACK,  BLACK,  BLACK  }
};	

/*###############################################################################################################################
#  应用声明结束                                                                                                                 #
###############################################################################################################################*/
#ifdef	__cplusplus
}
#endif
#endif

