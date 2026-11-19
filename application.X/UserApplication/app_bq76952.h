/*###############################################################################################################################
 # 文件名称 ： u80711R01_BQ76952_H                                                                                              #
 # 公司名称 :  TOTEX Technology, Inc.                                                                                           #
 # 芯片型号 ： PIC24FJ128GA302                                                                                                  #
 # 编译工具 :  ccs compiler v5.118                                                                                              #
 # 作    者 :  BenZhang                                                                                                         #
 # 编写日期 :  2025/11/10                                                                                                       #
 # 版    本 :  v1.00                                                                                                            #
 *             1.1.6 增加充满电进入睡眠(关闭充放电FET)                                                                          #
 ##############################################################################################################################*/
#ifndef APP_BQ76952_H
#define	APP_BQ76952_H

#include "app_config.h"
#include "app_interrupts.h"
/*###############################################################################################################################
# 声明开始                                                                                                                      #
###############################################################################################################################*/
#ifdef	__cplusplus
extern "C" {
#endif
/*###############################################################################################################################
#  BQ76952 命令宏定义                                                                                                           #
###############################################################################################################################*/
#define bq76952             0x10      
#define control()           0x00
#define SafetyAlertA()      0x02    
#define SafetyStatusA()     0x03
#define SafetyAlertB()      0x04
#define SafetyStatusB()     0x05
#define SafetyAlertC()      0x06    
#define SafetyStatusC()     0x07     
#define PFAlertA()          0x0A
#define PFStatusA()         0x0B
#define PFAlertB()          0x0C
#define PFStatusB()         0x0D
#define PFAlertC()          0x0E
#define PFStatusC()         0x0F
#define PFAlertD()          0x10
#define PFStatusD()         0x11
#define BattStatus()        0x12
#define cell1()             0x14
#define cell2()             0x16
#define cell3()             0x18
#define cell4()             0x1A
#define cell5()             0x1C
#define cell6()             0x1E
#define cell7()             0x20 
#define cell8()             0x22
#define cell9()             0x24   
#define cell10()            0x26
#define cell11()            0x28
#define cell12()            0x2A   
#define cell13()            0x2C
#define cell14()            0x2E
#define cell15()            0x30
#define cell16()            0x32   
#define StackVoltage()      0x34     
#define PackVoltage()       0x36   
#define LDPinVoltage        0x38   
#define CC2Current()        0x3A 
#define AlarmStatus()       0x62
#define AlarmRawStatus()    0x64
#define AlarmEnable()       0x66
#define INTemperature()     0x68
#define TS1Temperature()    0x70 
#define TS2Temperature()    0x72 
#define TS3Temperature()    0x74 
#define FETStatus()         0x7F 
//#define ExitDeepSleep       0x000E      //##(0)退出深度睡眠
//#define DeepSleepCmd        0x000F      //##(0)进入深度睡眠
    
#define DeepSleepCmd        0x0099      //##(0)SLEEP_ENABLE()
#define ExitDeepSleep       0x009A      //##(0)SLEEP_DISABLE()
#define AllFETOFF           0x0095      //##(0)关闭全部重放前MOSFET
#define AllFETON            0x0096      //##(0)开启全部重放前MOSFET
#define ShutDownCmd         0x0010       
#define RESET_PASSQ         0x0082      //##(0)子命令重置累积电荷积分和计时器
/*###############################################################################################################################
# 各个温度常数（K值）                                                                                                           #
###############################################################################################################################*/
#define NegTempConst20      2531        //##(0)温度 -20℃ 的温度常数（K值）
#define NegTempConst15      2581        //##(0)温度 -15℃ 的温度常数（K值） 
#define NegTempConst10      2631        //##(0)温度 -10℃ 的温度常数（K值）
#define NegTempConst5       2681        //##(0)温度  -5℃ 的温度常数（K值）
#define ZeroTempConst       2731        //##(0)温度   0℃ 的温度常数（K值）  
#define PosTempConst5       2781        //##(0)温度   5℃ 的温度常数（K值）   
#define PosTempConst10      2831        //##(0)温度  10℃ 的温度常数（K值）  
#define PosTempConst20      2931        //##(0)温度  20℃ 的温度常数（K值）   
#define PosTempConst25      2981        //##(0)温度  25℃ 的温度常数（K值）    
#define PosTempConst30      3031        //##(0)温度  30℃ 的温度常数（K值）
#define PosTempConst40      3131        //##(0)温度  40℃ 的温度常数（K值）     
#define PosTempConst50      3231        //##(0)温度  50℃ 的温度常数（K值）   
#define PosTempConst60      3331        //##(0)温度  60℃ 的温度常数（K值）        
/*###############################################################################################################################
# 各个温度的FCC默认值(mA/h)                                                                                                     #
###############################################################################################################################*/
#define DefNegTemp20FCC     596        //##(0)温度 -20℃ 的FCC初始数值
#define DefNegTemp15FCC     657        //##(0)温度 -15℃ 的FCC初始数值
#define DefNegTemp10FCC     987        //##(0)温度 -10℃ 的FCC初始数值     
#define DefNegTemp5FCC      704        //##(0)温度  -5℃ 的FCC初始数值    
#define DefZeroTempFCC      711        //##(0)温度   0℃ 的FCC初始数值
#define DefPosTemp5FCC      723        //##(0)温度   5℃ 的FCC初始数值 
#define DefPosTemp10FCC     719        //##(0)温度  10℃ 的FCC初始数值
#define DefPosTemp20FCC     736        //##(0)温度  20℃ 的FCC初始数值   
#define DefPosTemp25FCC     741        //##(0)温度  25℃ 的FCC初始数值
#define DefPosTemp30FCC     732        //##(0)温度  30℃ 的FCC初始数值       
#define DefPosTemp40FCC     735        //##(0)温度  40℃ 的FCC初始数值   
#define DefPosTemp50FCC     731        //##(0)温度  50℃ 的FCC初始数值       
#define DefPosTemp60FCC     728        //##(0)温度  60℃ 的FCC初始数值     
/*###############################################################################################################################
# 保存数据所对应的"EEPROM"地址(每个温度占用4个字节,FCC/电芯阻抗)                                                                #
###############################################################################################################################*/    
#define eeprom_NegTemp20    0x00        //##(0)温度 -20℃ 的FCC初始数值
#define eeprom_NegTemp15    0x04        //##(0)温度 -15℃ 的FCC初始数值
#define eeprom_NegTemp10    0x08        //##(0)温度 -10℃ 的FCC初始数值
#define eeprom_NegTemp5     0x0C        //##(0)温度  -5℃ 的FCC初始数值
#define eeprom_ZeroTemp     0x10        //##(0)温度   0℃ 的FCC初始数值  
#define eeprom_PosTemp5     0x14        //##(0)温度   5℃ 的FCC初始数值  
#define eeprom_PosTemp10    0x18        //##(0)温度  10℃ 的FCC初始数值  
#define eeprom_PosTemp20    0x1C        //##(0)温度  20℃ 的FCC初始数值 
#define eeprom_PosTemp25    0x20        //##(0)温度  25℃ 的FCC初始数值  
#define eeprom_PosTemp30    0x24        //##(0)温度  30℃ 的FCC初始数值
#define eeprom_PosTemp40    0x28        //##(0)温度  40℃ 的FCC初始数值    
#define eeprom_PosTemp50    0x2C        //##(0)温度  50℃ 的FCC初始数值   
#define eeprom_PosTemp60    0x30        //##(0)温度  60℃ 的FCC初始数值 
#define eeprom_FinishMark   0x60        //##(0)保存参数的标识(如果读取的内容 = 0x55,则认为保存过相关数据)    
#define eeprom_SN           0x70        //##(0)保存电池序列号占用16个字节  
#define eeprom_cyc          0x80        //##(0)保存电池循环次数地址 
#define eeprom_rc           0x82        //##(0)保存电池剩余容量地址 
#define eeprom_DsgCnt       0x84        //##(0)放电累积容量地址  
#define eeprom_FaultPersist 0xA0        //##(0)保存持久故障地址   
#define eeprom_FulatPF      0xA8        //##(0)保存电芯低于2.5V状态标志"PF"
/*###############################################################################################################################
# 其它常数声明                                                                                                                  #
###############################################################################################################################*/
#define resttimerTerm       7200        //##(0)休息时间 7200
#define StartUpdata         20          //##(0)启动FCC库仑计容量百分比数值 (20%)
#define E2ucChgEndDelay1    40          //##(0)设置"FC"标志判断延时时间
#define E2ucChgEndDelay2    5           //##(0)清除"FC"标志判断延时时间
#define E2ucDsgEndDelay     3           //##(0)电池放空检测延时时间阈值           
#define E2siDfilterCur      50          //##(0)充放电检测阈值(+/-50mA)      
#define E2DesignCapacity    750         //##(0)即设计容量 
#define E2ChargingCurrent   5000        //##(0)标准充电电流
#define E2ChargingVoltage   4100*12     //##(0)标准充电电压(12串)    
#define E2PChargingCurrent  500         //##(0)预充电电流
#define E2siChgEndCur       100         //##(0)充满电流终止阈值     
#define E2uiChgTermVoltage  4100        //##(0)充满电压终止阈值(单个电芯电压,以最低电芯电压为准)      
#define E2uiDsgTermVoltage  2800        //##(0)放电电芯终止电压(单个电芯电压,以最高电芯电压为准,强制将容量变为3%）   
#define E2PchgThrVoltage    2900        //##(0)预充电电压门槛值,低于此值则充电电流为预充电电流(以最高电芯电压为准) 
#define E2SchgThrVoltage    3000        //##(0)标准充电电压门槛值,低于此值则充电电流为标准充电电流(以最高电芯电压为准) 
    
/*###############################################################################################################################
# 各个温度的剩余容量所对应的电压                                                                                                #
###############################################################################################################################*/    
const uint16_t ocvTab[21][13]={                                                                   
//    -20℃  -15℃  -10℃  -5℃    0℃    5℃    10℃   20℃   25℃   30℃   40℃   50℃   60℃ 
    {4285, 4285, 4283, 4279, 4284, 4284, 4281, 4286, 4277, 4282, 4279, 4274, 4269},     //##(0) 100
    {4233, 4230, 4228, 4222, 4229, 4228, 4225, 4229, 4220, 4224, 4223, 4218, 4213},     //##(0)  95
    {4184, 4179, 4175, 4169, 4176, 4173, 4170, 4174, 4164, 4169, 4166, 4163, 4158},     //##(0)  90
    {4137, 4128, 4122, 4114, 4124, 4118, 4118, 4121, 4110, 4116, 4113, 4109, 4105},     //##(0)  85
    {4090, 4079, 4074, 4065, 4077, 4069, 4072, 4074, 4062, 4067, 4063, 4058, 4053},     //##(0)  80
    {4050, 4024, 4009, 3997, 4009, 4002, 4009, 4015, 4004, 4013, 4010, 4008, 4005},     //##(0)  75
    {3981, 3958, 3951, 3946, 3954, 3949, 3954, 3960, 3950, 3960, 3959, 3956, 3951},     //##(0)  70
    {3938, 3925, 3919, 3913, 3916, 3914, 3913, 3914, 3906, 3912, 3910, 3908, 3905},     //##(0)  65
    {3911, 3895, 3887, 3881, 3882, 3880, 3879, 3879, 3872, 3878, 3875, 3873, 3872},     //##(0)  60
    {3884, 3866, 3858, 3853, 3854, 3851, 3851, 3851, 3845, 3849, 3847, 3845, 3843},     //##(0)  55
    {3856, 3839, 3832, 3828, 3831, 3828, 3828, 3828, 3822, 3826, 3824, 3822, 3819},     //##(0)  50
    {3831, 3816, 3810, 3806, 3810, 3806, 3808, 3809, 3803, 3807, 3804, 3801, 3798},     //##(0)  45
    {3808, 3794, 3791, 3788, 3793, 3788, 3791, 3791, 3784, 3789, 3785, 3779, 3771},     //##(0)  40
    {3787, 3776, 3775, 3772, 3778, 3771, 3774, 3771, 3761, 3764, 3755, 3749, 3740},     //##(0)  35
    {3771, 3761, 3761, 3758, 3764, 3755, 3757, 3751, 3743, 3743, 3735, 3728, 3719},     //##(0)  30
    {3758, 3749, 3746, 3741, 3747, 3735, 3738, 3732, 3723, 3724, 3716, 3708, 3697},     //##(0)  25
    {3749, 3738, 3730, 3722, 3725, 3711, 3714, 3710, 3696, 3701, 3692, 3683, 3673},     //##(0)  20
    {3738, 3726, 3717, 3709, 3707, 3699, 3699, 3694, 3689, 3687, 3680, 3672, 3663},     //##(0)  15
    {3723, 3702, 3688, 3652, 3674, 3580, 3630, 3633, 3556, 3614, 3592, 3574, 3535},     //##(0)  10
    {3699, 3650, 3580, 3419, 3453, 3292, 3297, 3296, 3156, 3252, 3192, 3171, 3127},     //##(0)  5
    {3660, 3537, 3352, 3230, 3139, 3164, 3080, 3078, 3034, 3068, 3027, 3018, 2994}      //##(0)  0
};
/*###############################################################################################################################
# 各个温度所对应的电芯阻抗                                                                                                      #
###############################################################################################################################*/   
const uint16_t impTab[21][13]={  
//    -20℃   -15℃ -10℃  -5℃   -0℃    5℃   10℃  20℃  25℃  30℃  40℃  50℃  60℃  
    {2675, 1746, 1312, 838,  551,  407,  274,  71, 	51,  50,  37,  33, 	38},            //##(0) 100
    {2619, 1734, 1292, 829,  555,  403,  269,  72, 	61,  54,  41,  35, 	39},            //##(0)  95
    {2559, 1708, 1276, 811,  554,  391,  269,  70, 	61,  46,  36,  38, 	40},            //##(0)  90
    {2588, 1692, 1248, 806,  541,  381,  266,  75, 	61,  50,  37,  34, 	39},            //##(0)  85
    {2711, 1683, 1228, 803,  542,  371,  266,  70, 	57,  54,  40,  34, 	40},            //##(0)  80
    {2685, 1684, 1219, 789,  541,  371,  264,  71, 	61,  50,  35,  36, 	39},            //##(0)  75
    {2678, 1692, 1209, 780,  543,  340,  268,  76, 	59,  50,  37,  38, 	39},            //##(0)  70
    {2678, 1713, 1217, 779,  557,  341,  270,  71, 	63,  51,  39,  36, 	35},            //##(0)  65
    {2651, 1752, 1233, 800,  570,  346,  265,  75, 	61,  50,  37,  34, 	35},            //##(0)  60
    {2651, 1736, 1251, 807,  584,  342,  266,  73, 	63,  51,  35,  36, 	38},            //##(0)  55
    {2652, 1733, 1274, 818,  595,  347,  260,  75, 	64,  51,  39,  38, 	38},            //##(0)  50
    {2684, 1734, 1300, 826,  603,  341,  274,  78, 	61,	 51,  40,  34, 	37},            //##(0)  45
    {2696, 1751, 1317, 842,  619,  350,  275,  78, 	64,  49,  36,  35, 	40},            //##(0)  40
    {2717, 1769, 1340, 861,  621,  359,  283,  73, 	66,  53,  39,  36, 	36},            //##(0)  35
    {2732, 1774, 1359, 873,  637,  363,  289,  81, 	61,  50,  40,  39, 	35},            //##(0)  30
    {2806, 1780, 1383, 894,  653,  380,  290,  80, 	66,  56,  42,  35, 	39},            //##(0)  25
    {2803, 1871, 1405, 928,  673,  391,  298,  78, 	67,  60,  39,  35, 	35},            //##(0)  20
    {2814, 1900, 1421, 953,  683,  402,  310,  86, 	72,  56,  42,  35, 	40},            //##(0)  15
    {2823, 1921, 1450, 983,  704,  415,  316,  92, 	73,  63,  41,  38, 	34},            //##(0)  10
    {2846, 1947, 1479, 1022, 735,  451,  337,  93, 	77,  58,  41,  36, 	42},            //##(0)  5
    {2867, 1978, 1566, 1177, 854,  565,  430,  129, 131, 84,  61,  51, 	57}             //##(0)  0
};        

/*###############################################################################################################################
# 变量定义                                                                                                                      #
###############################################################################################################################*/
volatile union{
    uint8_t word;               //##(0)占用1个字节
    struct{
        uint8_t     :2;         //##(0)保留位
        uint8_t CUV :1;         //##(0)电芯欠压保护
        uint8_t COV :1;         //##(0)电芯过压保护
        uint8_t OCC :1;         //##(0)充电过流保护
        uint8_t OCD1:1;         //##(0)放电过流 1 级保护
        uint8_t OCD2:1;         //##(0)放电过流 2 级保护
        uint8_t SCD :1;         //##(0)放电短路保护
    };
}SafetyAlertA,SafetyStatusA;    //##(0)警告寄存器声明【A】/状态寄存器声明【A】 

volatile union{
    uint8_t word;               //##(0)占用1个字节
    struct{
        uint8_t UTC  :1;        //##(0)充电欠温
        uint8_t UTD  :1;        //##(0)放电欠温
        uint8_t UTINT:1;        //##(0)内部欠温
        uint8_t      :1;        //##(0)保留位
        uint8_t OTC  :1;        //##(0)充电过热
        uint8_t OTD  :1;        //##(0)放电过热
        uint8_t OTINT:1;        //##(0)内部过热
        uint8_t OTF  :1;        //##(0)FET 过热
    };
}SafetyAlertB,SafetyStatusB;    //##(0)警告寄存器声明【B】/状态寄存器声明【B】 

volatile union{
    uint8_t word;               //##(0)占用1个字节
    struct{
        uint8_t     :3;         //##(0)保留位
        uint8_t PTOS:1;         //##(0)预充电超时暂停
        uint8_t COVL:1;         //##(0)电芯过压锁存
        uint8_t OCDL:1;         //##(0)放电过流锁存
        uint8_t SCDL:1;         //##(0)放电短路锁存
        uint8_t OCD3:1;         //##(0)放电过流 3 级保护
    };
}SafetyAlertC;                  //##(0)警告寄存器声明【C】

volatile union{
    uint8_t word;               //##(0)占用1个字节
    struct{
        uint8_t     :1;         //##(0)保留位
        uint8_t HWDF:1;         //##(0)主机看门狗故障
        uint8_t PTO :1;         //##(0)预充电超时
        uint8_t     :1;         //##(0)保留位
        uint8_t COVL:1;         //##(0)电芯过压锁存
        uint8_t OCDL:1;         //##(0)放电过流锁存 
        uint8_t SCDL:1;         //##(0)放电短路锁存
        uint8_t OCD3:1;         //##(0)放电过流 3 级保护
    };
}SafetyStatusC;                 //##(0)状态寄存器声明【C】 

volatile union{
    uint8_t word;               //##(0)占用1个字节
    struct{
        uint8_t SUV :1;         //##(0)电芯欠压安全永久失效
        uint8_t SOV :1;         //##(0)电芯过压安全永久失效
        uint8_t SOCC:1;         //##(0)充电过流安全永久失效
        uint8_t SOCD:1;         //##(0)放电过流安全永久失效
        uint8_t SOT :1;         //##(0)过热安全永久失效 
        uint8_t     :1;         //##(0)保留位
        uint8_t SOTF:1;         //##(0)FET 过热安全永久失效
        uint8_t CUDEP:1;        //##(0)铜沉积永久失效
    };
}PFAlertA,PFStatusA;            //##(0)PF 警告寄存器声明【A】/PF 状态寄存器声明【A】

volatile union{
    uint8_t word;               //##(0)占用1个字节
    struct{
        uint8_t CFETF:1;        //##(0)充电 FET 永久失效
        uint8_t DFETF:1;        //##(0)放电 FET 永久失效
        uint8_t _2LVL:1;        //##(0)二级保护器永久失效
        uint8_t VIMR :1;        //##(0)静态模式电压不平衡永久失效
        uint8_t VIMA :1;        //##(0)激活模式电压不平衡永久失效
        uint8_t      :2;        //##(0)保留位
        uint8_t SCDL :1;        //##(0)放电短路锁存永久失效
    };
}PFAlertB,PFStatusB;            //##(0)PF 警告寄存器声明【B】/PF 状态寄存器声明【B】                           

volatile union{
    uint8_t word;               //##(0)占用1个字节
    struct{
        uint8_t     :3;         //##(0)保留位
        uint8_t LFOF:1;         //##(0)内部 LFO 永久失效
        uint8_t VREF:1;         //##(0)内部电压基准永久失效
        uint8_t VSSF:1;         //##(0)内部 VSS 测量永久失效
        uint8_t HWMX:1;         //##(0)硬件多路复用器永久失效
        uint8_t     :1;
    };
}PFAlertC;                      //##(0)PF 警告寄存器声明【C】

volatile union{
    uint8_t word;               //##(0)占用1个字节
    struct{
        uint8_t OTPF:1;         //##(0)OTP 存储器永久失效
        uint8_t DRMF:1;         //##(0)数据 ROM 永久失效
        uint8_t IRMF:1;         //##(0)指令 ROM 永久失效
        uint8_t LFOF:1;         //##(0)内部 LFO 永久失效
        uint8_t VREF:1;         //##(0)内部电压基准永久失效
        uint8_t VSSF:1;         //##(0)内部 VSS 测量永久失效     
        uint8_t HWMX:1;         //##(0)硬件多路复用器永久失效
        uint8_t CMDF:1;         //##(0)命令的永久失效
    };
}PFStatusC;                     //##(0)PF 状态寄存器声明【C】  

volatile union{
    uint8_t word;               //##(0)占用1个字节
    struct{
        uint8_t TOSF:1;         //##(0)比较电池组顶部电压与电芯电压和永久失效
        uint8_t :7;
    };
}PFAlertD,PFStatusD;           //##(0)PF 状态寄存器声明【D】  

volatile union{
    uint16_t word;              //##(0)占用2个字节
    struct{
        uint8_t CFGUPDATE:1;    //##(0)该位指示器件是否处于 CONFIG_UPDATE 模式
        uint8_t PCHG_MODE:1;    //##(0)该位指示器件是否处于 PRECHARGE 模式
        uint8_t SLEEP_EN :1;    //##(0)该位根据配置和命令提示是否允许 SLEEP 模式
        uint8_t POR      :1;    //##(0)当器件完全复位时,会设置该位
        uint8_t WD       :1;    //##(0)该位指示上一次器件复位是否由内部看门狗计时器引起
        uint8_t COW_CHK  :1;    //##(0)该位指示何时正在进行电芯开路检查。
        uint8_t OTPW     :1;    //##(0)该位指示在正常操作期间是否有一些数据正在等待写入 OTP
        uint8_t OTPB     :1;    //##(0)该位指示电压和温度条件是否对 OTP 编程有效
        uint8_t SEC0     :1;    //##(0)
        uint8_t SEC1     :1;    //##(0)
        uint8_t FUSE     :1;    //##(0)该位报告最近观察到的 FUSE 引脚状态， 每秒更新一次。
        uint8_t SS       :1;    //##(0)该位指示是否触发了启用的安全故障。
        uint8_t PF       :1;    //##(0)该位指示是否触发了启用的永久失效故障。
        uint8_t SD_CMD   :1;    //##(0)当由于接收到命令或 RST_SHUT 引脚生效至少一秒钟而导致关断挂起时， 会设置该位。   
        uint8_t          :1;    //##(0)保留位
        uint8_t SLEEP    :1;    //##(0)该位指示器件当前是否处于 SLEEP 模式 
    };
}BatteryStatus;                 //##(0)状态寄存器声明

volatile struct{ 
    union{                           
        uint16_t word;                  //##(0)联合体
        struct{
            uint8_t StartupdateFCC:1;   //##(0)启动FCC更新有效容量统计数据(充电统计)
            uint8_t CHGING:1;           //##(0)充电状态标志
            uint8_t DSGING:1;           //##(0)放电状态标志
            uint8_t OCC   :1;           //##(0)充电过流标志
            uint8_t SCD   :1;           //##(0)放电短路标志        
            uint8_t OCD   :1;           //##(0)放电过流标志
            uint8_t FD    :1;           //##(0)放电截止标志
            uint8_t FC    :1;           //##(0)充电截止标志
            uint8_t CUV   :1;           //##(0)电池欠压标志
            uint8_t COV   :1;           //##(0)电池过压标志
            uint8_t OC    :1;           //##(0)电池过充标志(采用4.2V充电)
        };
    }b;                                 //##(0)标志位声明 
    
    union{
        uint16_t word;                  //##(0)占用2个字节
        struct{
            uint8_t WAKE:1;		//##(0)当器件从 SLEEP 模式唤醒时会设置该位
            uint8_t ADSCAN:1;		//##(0)电压 ADC 扫描完成
            uint8_t CB:1;		//##(0)当电芯平衡处于活动状态时会设置该位
            uint8_t FUSE:1;		//##(0)驱动 FUSE 引脚。 FUSE 引脚由器件或次级保护器驱动。
            uint8_t SHUTV:1;		//##(0)电池组电压低于 Power:Shutdown:Shutdown Stack Voltage。	
            uint8_t XDSG:1;		//##(0)当 DSG FET 关断时会设置该位	
            uint8_t XCHG:1;		//##(0)当 CHG FET 关断时会设置该位。	
            uint8_t FULLSCAN:1;		//##(0)完整电压扫描完成
            uint8_t INITCOMP:1;		//##(0)初始化已完成（ 在器件通电并完成一次测量扫描后设置） 。
            uint8_t INITSTART:1;	//##(0)初始化已开始（ 器件上电后快速设置） 。
            uint8_t MSK_PFALERT:1;      //##(0)当永久失效警报被触发， 
            uint8_t MSK_SFALERT:1;      //##(0)当安全警报被触发		
            uint8_t PF:1;		//##(0)当触发启用的永久失效故障时， 会设置该位。	
            uint8_t SSA:1;		//##(0)当 Safety Status A() 中设置了某个位时， 会设置该位。 
            uint8_t SSBC:1;		//##(0)当 Safety Status B() 或 Safety Status C() 中设置了某个位时， 会设置该位。
        };
    }AlarmStatus;			//##(0)警报状态寄存器

    union{                           
        uint16_t word;                  //##(0)联合体
         uint8_t u8[2];                 //##(0)占用2个字节
        struct{
            uint8_t EC   :4;            //##(0)Error Code
            uint8_t FD   :1;            //##(0)Fully Discharged
            uint8_t FC   :1;            //##(0)Fully Charged
            uint8_t DSG  :1;            //##(0)Discharging
            uint8_t INIT :1;            //##(0)Initialization
            uint8_t RTA  :1;            //##(0)Remaining Time Alarm
            uint8_t RCA  :1;            //##(0)Remaining Capacity Alarm
            uint8_t RSVD0:1;            //##(0)Reserved
            uint8_t TDA  :1;            //##(0)Terminate Discharge Alarm
            uint8_t OTA  :1;            //##(0)Overtemperature Alarm
            uint8_t RSVD1:1;            //##(0)Reserved
            uint8_t TCA  :1;            //##(0)Terminate Charge Alarm
            uint8_t OCA  :1;            //##(0)Overcharged Alarm
        };
    }BatteryStatus;                     //##(0)Battery_status 
    
    union{
        uint16_t word;
        struct{
            uint8_t CUV:1;              //##(0)电池欠压故障
            uint8_t COV:1;              //##(0)电池过压故障
            uint8_t OCC:1;              //##(0)充电过流故障
            uint8_t OCD:1;              //##(0)放电过流故障
            uint8_t SCD:1;              //##(0)放电短路故障
            uint8_t UTC:1;              //##(0)充电欠温故障
            uint8_t UTD:1;              //##(0)放电欠温故障
            uint8_t OTC:1;              //##(0)充电过热故障
            uint8_t OTD:1;              //##(0)放电过热故障
            uint8_t BUS:1;              //##(0)通讯故障
            uint8_t    :6;              //##(0)保留位            
        };        
    }BatteryFault;                      //##(0)电池故障
	
    int32_t LastPassQInt;               //##(0)保存上一轮定时任务读到的总累积电荷 PassQInt,作为差值计算基准
    int32_t PassQInt;                   //##(0)累积电荷整数【报告累计通过的电荷的整数部分(单位为 mA/h)】
   uint16_t Battery_Status;             //##(0)"bq76952"电池状态寄存器 
    int16_t TS1Temperature;             //##(0)温度传感器"TS1"温度   
    int16_t TS2Temperature;             //##(0)温度传感器"TS2"温度
    int16_t TS3Temperature;             //##(0)温度传感器"TS3"温度【"DCHG"温度】
    int16_t TS4Temperature;             //##(0)温度传感器"TS3"温度【"DDSG"温度】
    int16_t FetTemperature;             //##(0)FET 温度    
    int16_t Temperature;                //##(0)电池包温度值(需要报告信息)
    int16_t LastTemperature;            //##(0)历史"FCC"温度
    int16_t current;                    //##(0)电流
    int16_t AverageCurrent;             //##(0)平均电流
   uint16_t voltage;                    //##(0)电压(电芯电压总和) 
   uint16_t CellV[16];                  //##(0)12串电芯【原始带载电压】单位：mV
   uint16_t CellMax;                    //##(0)最大电芯电压 
   uint16_t CellMin;                    //##(0)最小电芯电压
    int16_t CellTempMax;                //##(0)最高电芯温度
    int16_t CellTempMin;                //##(0)最低电芯温度
   uint16_t imbalance;                  //##(0)电池平衡状态
   uint16_t packvoltage;                //##(0)PACK电压 
   uint16_t Pinvoltage;                 //##(0)引脚电压 
   uint16_t stackvoltage;               //##(0)堆积电压
   uint16_t RemTimeAlarm;               //##(0)剩余时间警告
   uint16_t RemCapAlarm;                //##(0)剩余容量警告
   uint16_t RunTimeToEmpty;             //##(0)放空时间所需时间
   uint16_t AverageTimeToEmpty;         //##(0)平均防空所需时间
   uint16_t AverageTimeToFull;          //##(0)充满剩余时间
   uint16_t rsoc;                       //##(0)相对充电状态
   uint16_t Last_rsoc;                  //##(0)历史容量
   uint16_t asoc;                       //##(0)绝对剩余容量百分比
   uint16_t RemCap;                     //##(0)剩余容量
   uint16_t FCC;                        //##(0)充满容量
   uint16_t StateOfHealth;              //##(0)电池健康度
   uint16_t ChargingCurrent;            //##(0)充电电流(预充电流/快充电流)
   uint16_t ChargingVoltage;            //##(0)充电电压(预充电压/快充电压)
   uint16_t CCC;                        //##(0)周期计数
   uint16_t DesignCapacity;             //##(0)设计容量
   uint16_t DesignVoltage;              //##(0)设计电压
   uint16_t ManufactureDate;            //##(0)生产日期
   uint16_t SerialNumber;               //##(0)序列号
    uint8_t FETStatus;                  //##(6)
   uint16_t DCC;                        //##(0)放电循环次数
   uint8_t  SN[17];                     //##(0)电池序列号,16个字节
   uint16_t BSTATE;                     //##(0)电池状态标志【16*1 0=Idle/1=Charging/2=Balancing/3=Discharge/4=Error】 
  bufferu16 MajFW;                      //##(0)电池固件版本(主版本号)
  bufferu16 MinFW;                      //##(0)电池固件版本(次版本号)
  bufferu16 PatFW;                      //##(0)电池固件版本(补丁版本号)
  bufferu16 BMSHW_ID;                   //##(0)电池硬件版本(厂商ID)
  bufferu16 BMSHW_Ver;                  //##(0)电池硬件版本(版本号) 
}FG;

volatile uint16_t cycleEndCapacity;     //##(0)单词放电终止容量门槛
volatile uint16_t ulDsgCC;              //##(0)放电容量统计数据,用于更新E2uiCycleCount
volatile uint16_t ulSaveFCC;            //##(0)CC更新有效容量统计数据(充电统计)，用于更新E2ulFCC
volatile uint16_t impedance;            //##(0)电池包阻抗
volatile uint16_t ucFCC[14];            //##(0)13个温度的FCC数值
volatile uint8_t  ucChgSetupTimeCntFC;  //##(0)电池充满设置"FC"延时时间
volatile uint8_t  ucChgClearTimeCntFC;  //##(0)电池充满后重新恢复充电(清除FC)延时时间 
volatile uint8_t  ucDsgSetupTimeCntFD;  //##(0)电池放空设置"FD"延时时间
volatile uint8_t  ucDsgClearTimeCntFD;  //##(0)电池放空后(清除FD)延时时间 
volatile uint8_t  ucDsgTermTimeCnt;     //##(0)放电终止检测延时时间（强制剩余容量变为"0"）   
/*###############################################################################################################################
# EEPROM 温度地址表（指针查表用）                                                                                               #
# 每项：{ EEPROM起始地址, 默认的FCC, ucFCC对应存储位置指针}                                                                     #
###############################################################################################################################*/
uint16_t *ucfccTab[][3] = { 
    { (uint16_t*)eeprom_NegTemp20, (uint16_t*)DefNegTemp20FCC, (uint16_t*)&ucFCC[0] },     //##(0)-20℃ 的"FCC"数值
    { (uint16_t*)eeprom_NegTemp15, (uint16_t*)DefNegTemp15FCC, (uint16_t*)&ucFCC[1] },     //##(0)-15℃ 的"FCC"数值
    { (uint16_t*)eeprom_NegTemp10, (uint16_t*)DefNegTemp10FCC, (uint16_t*)&ucFCC[2] },     //##(0)-10℃ 的"FCC"数值
    { (uint16_t*)eeprom_NegTemp5,  (uint16_t*)DefNegTemp5FCC,  (uint16_t*)&ucFCC[3] },     //##(0) -5℃ 的"FCC"数值
    { (uint16_t*)eeprom_ZeroTemp,  (uint16_t*)DefZeroTempFCC,  (uint16_t*)&ucFCC[4] },     //##(0)  0℃ 的"FCC"数值
    { (uint16_t*)eeprom_PosTemp5,  (uint16_t*)DefPosTemp5FCC,  (uint16_t*)&ucFCC[5] },     //##(0)  5℃ 的"FCC"数值
    { (uint16_t*)eeprom_PosTemp10, (uint16_t*)DefPosTemp10FCC, (uint16_t*)&ucFCC[6] },     //##(0) 10℃ 的"FCC"数值
    { (uint16_t*)eeprom_PosTemp20, (uint16_t*)DefPosTemp20FCC, (uint16_t*)&ucFCC[7] },     //##(0) 20℃ 的"FCC"数值
    { (uint16_t*)eeprom_PosTemp25, (uint16_t*)DefPosTemp25FCC, (uint16_t*)&ucFCC[8] },     //##(0) 25℃ 的"FCC"数值
    { (uint16_t*)eeprom_PosTemp30, (uint16_t*)DefPosTemp30FCC, (uint16_t*)&ucFCC[9] },     //##(0) 30℃ 的"FCC"数值
    { (uint16_t*)eeprom_PosTemp40, (uint16_t*)DefPosTemp40FCC, (uint16_t*)&ucFCC[10]},     //##(0) 40℃ 的"FCC"数值
    { (uint16_t*)eeprom_PosTemp50, (uint16_t*)DefPosTemp50FCC, (uint16_t*)&ucFCC[11]},     //##(0) 50℃ 的"FCC"数值
    { (uint16_t*)eeprom_PosTemp60, (uint16_t*)DefPosTemp60FCC, (uint16_t*)&ucFCC[12]}      //##(0) 60℃ 的"FCC"数值
};
//##(0)表项总数
#define TabLength  (sizeof(ucfccTab)/6)    

/*###############################################################################################################################
# 函数声明                                                                                                                      #
###############################################################################################################################*/
boolean i2c_PutsData(uint8_t chip, uint8_t reg, uint8_t *buffer, uint8_t Length);
boolean i2c_GetsData(uint8_t chip, uint8_t reg, uint8_t *buffer, uint8_t Length);

void read_eeprom_ucFCC(void);
void bq76952_CONTROL_FETS(uint16_t word);
void bq76952_writeWord(uint16_t word);
void read_ProtectionStatus(void);
boolean charging_discharge_Manage(void); 
/*###############################################################################################################################
# 函数名 :  void read_eeprom_ucFCC(void)                                                                                        #
# 功  能 :  读取保存在"eeprom"中温度对应的"FCC"值                                                                               #
# 参  数 :  NONE                                                                                                                #
# 说  明 :  和默认值比较的差值超出范围则设置为默认值,否则是读取的结果                                                           #
###############################################################################################################################*/
void read_eeprom_ucFCC(void) {
    uint16_t MaxMinLimit,*pDst, BUFF;   //##(0)上/下最大值,
     int16_t Delta;                     //##(0)差值 = 存储在"EEPROM"中的容量 - 标准容量 
    uint16_t StandardCapacity;          //##(0)标准容量暂存器
     uint8_t address;  
//##(0)读取温度对应的"FCC"数值,如果
    for(uint8_t i=0; i<TabLength; i++) {
        address = (uint8_t)ucfccTab[i][0];
        if(!m24c04_read(address,(uint8_t *)&BUFF, sizeof(BUFF))) {
            StandardCapacity = ucfccTab[i][1];                      //##(0)取得标准容量
            Delta = BUFF - StandardCapacity;                        //##(0)差值
            Delta = abs(Delta);                                     //##(0)差值的绝对值
            MaxMinLimit = (StandardCapacity * 3u + 5u)/10;          //##(0)标准值的0.3倍 ,四舍五入,纯整数运算,无浮点
            pDst = ucfccTab[i][2];                                  //##(0)指向"ucFCC"地址
           *pDst = (Delta>MaxMinLimit)? StandardCapacity:BUFF;      //##(0)如果范围在标准值的 0.7倍~1.3倍则将读取到的更新到"ucFCC"
        }
    }
}         
/*###############################################################################################################################
# 函数名 :  void save_eeprom_ucFCC(void)                                                                                        #
# 功  能 :  温度对应的"FCC"值保存在"eeprom"中                                                                                   #
# 参  数 :  NONE                                                                                                                #
# 说  明 :  NONE                                                                                                                #
###############################################################################################################################*/
void save_eeprom_ucFCC(void) {
    uint16_t address;
//##(0)根据当前温度值对应到"ucFCC"
         if(FG.Temperature<=NegTempConst20)  { address = eeprom_NegTemp20; ucFCC[0] = FG.FCC;}
    else if(FG.Temperature<=NegTempConst15)  { address = eeprom_NegTemp15; ucFCC[1] = FG.FCC;}  
    else if(FG.Temperature<=NegTempConst10)  { address = eeprom_NegTemp10; ucFCC[2] = FG.FCC;}
    else if(FG.Temperature<=NegTempConst5 )  { address = eeprom_NegTemp5;  ucFCC[3] = FG.FCC;}
    else if(FG.Temperature<=ZeroTempConst )  { address = eeprom_ZeroTemp;  ucFCC[4] = FG.FCC;}
    else if(FG.Temperature<=PosTempConst5 )  { address = eeprom_PosTemp5;  ucFCC[5] = FG.FCC;}
    else if(FG.Temperature<=PosTempConst10)  { address = eeprom_PosTemp10; ucFCC[6] = FG.FCC;}
    else if(FG.Temperature<=PosTempConst20)  { address = eeprom_PosTemp20; ucFCC[7] = FG.FCC;}
    else if(FG.Temperature<=PosTempConst25)  { address = eeprom_PosTemp25; ucFCC[8] = FG.FCC;}
    else if(FG.Temperature<=PosTempConst30)  { address = eeprom_PosTemp30; ucFCC[9] = FG.FCC;}
    else if(FG.Temperature<=PosTempConst40)  { address = eeprom_PosTemp40; ucFCC[10]= FG.FCC;}
    else if(FG.Temperature<=PosTempConst50)  { address = eeprom_PosTemp50; ucFCC[11]= FG.FCC;}
    else if(FG.Temperature<=PosTempConst60)  { address = eeprom_PosTemp60; ucFCC[12]= FG.FCC;}  
    else                                     { address = eeprom_PosTemp60; ucFCC[12]= FG.FCC;}
//##(0)将数据写入到指定对应的温度地址中
    if(m24c04_Write(address, (uint8_t *)&FG.FCC, sizeof(FG.FCC))) {
        delay_ms(1);
        if(m24c04_Write(address, (uint8_t *)&FG.FCC, sizeof(FG.FCC))) {
            delay_ms(1);
            m24c04_Write(address, (uint8_t *)&FG.FCC, sizeof(FG.FCC));      
        }
    } 
}
/*###############################################################################################################################
# 函数名 : void BQ76952_ALL_FETS_OFF(void)                                                                                      #
# 功  能 : 开启 CHG、 DSG、 PCHG 和 PDSG FET 驱动器                                                                             #
###############################################################################################################################*/
void bq76952_CONTROL_FETS(uint16_t word) {
    bufferu16 cmd;
//##(2)写入控制"FET"命令,连续写3次失败则返回
    cmd.u16 = word;
    if(i2c_PutsData(bq76952,control(),&cmd.u8,sizeof(cmd.u8))) {           
        delay_ms(1); 
        if(i2c_PutsData(bq76952,control(),&cmd.u8,sizeof(cmd.u8))) {       
            delay_ms(1);
            i2c_PutsData(bq76952,control(),&cmd.u8,sizeof(cmd.u8));       
        }   
    }  
} 
/*###############################################################################################################################
# 函数名 : void BQ76952_ALL_FETS_OFF(void)                                                                                      #
# 功  能 : 进入深度睡眠模式                                                                                                     #
###############################################################################################################################*/
void bq76952_writeWord(uint16_t word) {
    bufferu16 cmd;
//##(2)进入深度睡眠,发送第一次
    cmd.u16 = word;
    if(i2c_PutsData(bq76952,control(),&cmd.u8,sizeof(cmd.u8))) {           
        delay_ms(1); 
        if(i2c_PutsData(bq76952,control(),&cmd.u8,sizeof(cmd.u8))) {        
            delay_ms(1);
            i2c_PutsData(bq76952,control(),&cmd.u8,sizeof(cmd.u8));         
        }   
    }  
    delay_ms(1);
//##(0)发送第二次    
    cmd.u16 = word; 
    if(i2c_PutsData(bq76952,control(),&cmd.u8,sizeof(cmd.u8))) {          
        delay_ms(1); 
        if(i2c_PutsData(bq76952,control(),&cmd.u8,sizeof(cmd.u8))) {      
            delay_ms(1);
            i2c_PutsData(bq76952,control(),&cmd.u8,sizeof(cmd.u8));         
        }   
    }  
}
/*###############################################################################################################################
# 函数名 : void RESET_PASSQ(void)                                                                                               #
# 功  能 : 重置累积电荷积分和计时器                                                                                             #
# 参  数 : NONE                                                                                                                 #
# 说  明 : NONE                                                                                                                 # 
###############################################################################################################################*/
void RESET_PASSQ_PROCESS(void) {
    bufferu16 cmd;
//##(0)重置累积电荷积分和计时器命令   
    cmd.u16 = RESET_PASSQ;
//##(0)写入命令到"bq76952中"    
    if(i2c_PutsData(bq76952,control(),&cmd.u8,sizeof(cmd.u8))) {          
        delay_ms(1); 
        if(i2c_PutsData(bq76952,control(),&cmd.u8,sizeof(cmd.u8))) {      
            delay_ms(1);
            i2c_PutsData(bq76952,control(),&cmd.u8,sizeof(cmd.u8));         
        }   
    }  
}
/*###############################################################################################################################
# 函数名 : void read_bq76952_regs(void)                                                                                         #
# 功  能 : 读取"bq76952"全部寄存器数据                                                                                          #
# 参  数 : NONE                                                                                                                 #
# 说  明 : NONE                                                                                                                 #
###############################################################################################################################*/
bool READ_BQ76952_PROCESS(void) {
    uint8_t buffer[64];
  bufferu16 buff;
  static uint8_t ShutDownCnt,PFStatusCnt;
//##(0)读取各个电芯电压,先读取全部电芯电压再分别移入寄存器中
    memset(buffer,0x00,sizeof(buffer));                                             //##(0)暂存器清零
    if(i2c_GetsData(bq76952,SafetyAlertA(),&buffer, sizeof(buffer))) return(1);     //##(0)读取失败返回"1"
    #asm NOP #endasm
    SafetyAlertA.word = buffer[0];                          //##(0)安全警报"A"
   SafetyStatusA.word = buffer[1];                          //##(0)安全故障"A"
    SafetyAlertB.word = buffer[2];                          //##(0)安全警报"B"
   SafetyStatusB.word = buffer[3];                          //##(0)安全故障"B"                         
    SafetyAlertC.word = buffer[4];                          //##(0)安全警报"C"
   SafetyStatusC.word = buffer[5];                          //##(0)安全故障"C"
        PFAlertA.word = buffer[8];                          //##(0)永久失效警报"A"
       PFStatusA.word = buffer[9];                          //##(0)永久失效故障"A"
        PFAlertB.word = buffer[10];                         //##(0)永久失效警报"B"
       PFStatusB.word = buffer[11];                         //##(0)永久失效故障"B"
        PFAlertC.word = buffer[12];                         //##(0)永久失效警报"C"
       PFStatusC.word = buffer[13];                         //##(0)永久失效故障"C"
        PFAlertD.word = buffer[14];                         //##(0)永久失效警报"C"
       PFStatusD.word = buffer[15];                         //##(0)永久失效故障"C"     
   BatteryStatus.word = make16(buffer[17],buffer[16]);      //##(0)电池状态寄存器
    FG.CellV[0] = make16(buffer[19],buffer[18]);            //##(0)第"1"串电芯电压   
    FG.CellV[1] = make16(buffer[21],buffer[20]);            //##(0)第"2"串电芯电压   
    FG.CellV[2] = make16(buffer[23],buffer[22]);            //##(0)第"3"串电芯电压
    FG.CellV[3] = make16(buffer[25],buffer[24]);            //##(0)第"4"串电芯电压
    FG.CellV[4] = make16(buffer[27],buffer[26]);            //##(0)第"5"串电芯电压
    FG.CellV[5] = make16(buffer[29],buffer[28]);            //##(0)第"6"串电芯电压
    FG.CellV[6] = make16(buffer[31],buffer[30]);            //##(0)第"7"串电芯电压  
    FG.CellV[7] = make16(buffer[33],buffer[32]);            //##(0)第"8"串电芯电压   
    FG.CellV[8] = make16(buffer[35],buffer[34]);            //##(0)第"9"串电芯电压  
    FG.CellV[9] = make16(buffer[37],buffer[36]);            //##(0)第"10"串电芯电压   
    FG.CellV[10]= make16(buffer[39],buffer[38]);            //##(0)第"11"串电芯电压 
    FG.CellV[11]= make16(buffer[49],buffer[48]);            //##(0)第"12"串电芯电压
//##(0)读取堆积电压/PACK电压/引脚电压/CC2电流
    memset(buffer,0x00,sizeof(buffer));  
    if(i2c_GetsData(bq76952,StackVoltage(),&buffer,8u)) return(1);      //##(0)读取失败返回"1"
    FG.stackvoltage = make16(buffer[1],buffer[0]) * 10;     //##(0)堆积电压
     FG.packvoltage = make16(buffer[3],buffer[2]) * 10;     //##(0)PACK电压
     FG.Pinvoltage  = make16(buffer[5],buffer[4]) * 10;     //##(0)引脚电压
    FG.current = (int16_t)make16(buffer[7],buffer[6]);      //##(0)CC2电流 
//##(0)读取命令:0x62~0x7A数据并更新到相应寄存器中
    memset(buffer,0x00,sizeof(buffer)); 
    if(i2c_GetsData(bq76952,INTemperature(),&buffer,22u)) return(true);   //##(0)读取失败返回"1"
    FG.FetTemperature = make16(buffer[5],buffer[4]);        //##(0)内部温度   0x6C【THFET】 	
    FG.TS1Temperature = make16(buffer[9],buffer[8]);        //##(0)"TS1"温度  0x70【RT1】
    FG.TS2Temperature = make16(buffer[13],buffer[12]);      //##(0)"TS3"温度  0x74【RT2】
    FG.TS3Temperature = make16(buffer[19],buffer[18]);      //##(0)"DDSG"温度 0x7A【RT3】
    FG.TS4Temperature = make16(buffer[17],buffer[16]);      //##(0)"DCHG"温度 0x78【RT4】  
//##(0)读取扩展命令0075内容,一共读取32个字节数据再分别移入寄存器中
    memset(buffer,0x00,sizeof(buffer));                                 //##(0)暂存器清零
    buff.u16 = 0x0075;
    if(i2c_PutsData(bq76952,0x3E,&buff.u8,sizeof(buff.u8))) return(1);  //##(0)写命令失败返回"1"      
    delay_ms(2);
    if(i2c_GetsData(bq76952,0x40,&buffer, sizeof(buffer)))  return(1);  //##(0)读取失败返回"1"
    #asm NOP #endasm
    FG.CellMax        = make16(buffer[5], buffer[4]);       //##(0)最大电芯电压 
    FG.CellMin        = make16(buffer[7], buffer[6]);       //##(0)最小电芯电压   
    FG.CellTempMax    = make16(buffer[15],buffer[14]);      //##(0)最高电芯温度。
    FG.CellTempMin    = make16(buffer[17],buffer[16]);      //##(0)最低电芯温度。
    FG.Temperature    = make16(buffer[19],buffer[18]);      //##(0)平均电芯温度作为报告温度
    FG.AverageCurrent = make16(buffer[21],buffer[20]);      //##(0)平均电流
    FG.imbalance      = abs(FG.CellMax - FG.CellMin);       //##(0)最高电芯电压和最低电芯电压的差值     
    #asm NOP #endasm
//##(0)读取扩展命令0075内容,一共读取32个字节数据再分别移入寄存器中
    memset(buffer,0x00,sizeof(buffer)); 
    buff.u16 = 0x0076;
    if(i2c_PutsData(bq76952,0x3E,&buff.u8,sizeof(buff.u8))) return(1);  //##(0)写命令失败返回"1"      
    delay_ms(2);
    if(i2c_GetsData(bq76952,0x40,&buffer,8u)) return(1);                //##(0)读取失败返回"1"
    #asm NOP #endasm    
    FG.PassQInt = make32(buffer[3],buffer[2],buffer[1],buffer[0]);      //##(0)累积电荷【整数部分】
//##(0)读取"FET"状态
    if(i2c_GetsData(bq76952,FETStatus(),&buff.u8,sizeof(buff.u8))) return(1);
    FG.FETStatus = buff.u8[0];
//##(0)读取"Alarm Raw Status"	
    if(i2c_GetsData(bq76952,AlarmRawStatus(),&buff.u8,sizeof(buff.u8))) return(1);
    FG.AlarmStatus.word = buff.u16;
//##(0)临时故障标志/可自行恢复
    regs.FaultLive.TS1  = FALSE;
    regs.FaultLive.TS2  = FALSE;
    regs.FaultLive.TS3  = FALSE;
    regs.FaultLive.TS4  = FALSE;
    regs.FaultLive.TS5  = FALSE;	
    regs.FaultLive.OCD  = FALSE;                    //##(0)
    regs.FaultLive.COV  = SafetyStatusA.COV;        //##(0)电芯过压
    regs.FaultLive.CUV  = SafetyStatusA.CUV;        //##(0)电芯欠压     
    regs.FaultLive.OCC  = SafetyStatusA.OCC;        //##(0)充电过流
    regs.FaultLive.SCD  = SafetyStatusA.SCD;        //##(0)放电短路
    regs.FaultLive.OCD |= SafetyStatusA.OCD1;       //##(0)放电过电流保护1
    regs.FaultLive.OCD |= SafetyStatusA.OCD2;       //##(0)放电过电流保护2
    regs.FaultLive.OTC  = SafetyStatusB.OTC;        //##(0)充电过温
    regs.FaultLive.OTD  = SafetyStatusB.OTD;        //##(0)放电过温
    regs.FaultLive.UTC  = SafetyStatusB.UTC;        //##(0)充电欠温
    regs.FaultLive.UTD  = SafetyStatusB.UTD;        //##(0)放电欠温
//##(0)细分那个温度故障
    if(SafetyStatusB.OTC || SafetyStatusB.UTC) {									//##(0)充电过温/欠温
        regs.FaultLive.TS1 |= (FG.TS1Temperature>3182 || FG.TS1Temperature<2731);	//##(0)>45 || < 0
        regs.FaultLive.TS2 |= (FG.TS2Temperature>3182 || FG.TS2Temperature<2731);	//##(0)>45 || < 0
        regs.FaultLive.TS3 |= (FG.TS3Temperature>3182 || FG.TS3Temperature<2731);	//##(0)>45 || < 0
        regs.FaultLive.TS4 |= (FG.TS4Temperature>3182 || FG.TS4Temperature<2731);	//##(0)>45 || < 0
    }
    if(SafetyStatusB.OTD || SafetyStatusB.UTD) {									//##(0)放电过温/欠温
        regs.FaultLive.TS1 |= (FG.TS1Temperature>3331 || FG.TS1Temperature<2481);	//#(0)>60 || < -25	
        regs.FaultLive.TS2 |= (FG.TS2Temperature>3331 || FG.TS2Temperature<2481);	//#(0)>60 || < -25
        regs.FaultLive.TS3 |= (FG.TS3Temperature>3331 || FG.TS3Temperature<2481);	//#(0)>60 || < -25
        regs.FaultLive.TS4 |= (FG.TS4Temperature>3331 || FG.TS4Temperature<2481);	//#(0)>60 || < -25
    }	
    regs.FaultLive.TS5 |= (FG.FetTemperature>3731); //##(0)>100
//##(0)持久故障标志/不可恢复(需要命令清零)
    regs.FaultHistory.TS1 |= regs.FaultLive.TS1;    //##(10)第【1】路"NTC"温度传感器持久故障
    regs.FaultHistory.TS2 |= regs.FaultLive.TS2;    //##(10)第【1】路"NTC"温度传感器持久故障
    regs.FaultHistory.TS3 |= regs.FaultLive.TS3;    //##(10)第【1】路"NTC"温度传感器持久故障
    regs.FaultHistory.TS4 |= regs.FaultLive.TS4;    //##(10)第【1】路"NTC"温度传感器持久故障
    regs.FaultHistory.TS5 |= regs.FaultLive.TS5;    //##(10)第【1】路"NTC"温度传感器持久故障	
    regs.FaultHistory.COV |= regs.FaultLive.COV;    //##(0)电芯过压持久故障【历史记录】
    regs.FaultHistory.CUV |= regs.FaultLive.CUV;    //##(0)电芯欠压持久故障【历史记录】     
    regs.FaultHistory.OCC |= regs.FaultLive.OCC;    //##(0)充电过流持久故障【历史记录】
    regs.FaultHistory.SCD |= regs.FaultLive.SCD;    //##(0)放电短路持久故障【历史记录】
    regs.FaultHistory.OCD |= regs.FaultLive.OCD;    //##(0)放电过电流保护持久故障
    regs.FaultHistory.OTC |= regs.FaultLive.OTC;    //##(0)充电过温持久故障【历史记录】
    regs.FaultHistory.OTD |= regs.FaultLive.OTD;    //##(0)放电过温持久故障【历史记录】
    regs.FaultHistory.UTC |= regs.FaultLive.UTC;    //##(0)充电欠温持久故障【历史记录】
    regs.FaultHistory.UTD |= regs.FaultLive.UTD;    //##(0)放电欠温持久故障【历史记录】
    regs.FaultHistory.COM |= regs.FaultLive.COM;    //##(0)通讯故障【历史记录】  
//##(0)如果故障类型一样或者没有故障则无需写入"EEPROM"中
    if(regs.FaultHistory.u16 != 0UL && regs.LastFaultPersist.u16 != regs.FaultHistory.u16) {
        regs.LastFaultPersist.u16 = regs.FaultHistory.u16;
        writeEeprom(eeprom_FaultPersist,(U8 *)&regs.FaultHistory.u16, 2UL);   //##(0)保存到"EEPROM"中    
    }
//##(0)如果连续2次最低电芯电压低于2.9V则进入"ShutDown",充电过程不作判断
    if(FG.CellMin<3000 && FG.current>E2siDfilterCur) {
        if(++ShutDownCnt>=2U) {
            regs.flags.RunMode = MODE_SHUTDOWN;     //##(0)设置进入"ShutDown"模式
        }     
    }else{
        ShutDownCnt = 0U;
    }
//##(0)如果最低电芯电芯电压低于2500mV连续3次则设置"FualtPFStatus=1"
    if(FG.CellMin < 2500) {
        if(++PFStatusCnt>=3u) {
            buffer[0] = 0xAA;
            writeEeprom(eeprom_FulatPF,(U8 *)&buffer, 1U);      //##(0)EEPROM 写入"PF"故障标识"AA"
            FualtPFStatus = true;                               //##(0)设置故障标志
        }
    }else{
        PFStatusCnt = 0u;                           
    }
//##(0)返回"0"    
    return(0);   
}

/*###############################################################################################################################
# 函数名 : void InitializeCapacity(void)                                                                                        #
# 功  能 : 初始化容量(按照开路电压计算容量)                                                                                     #
# 参  数 : NONE                                                                                                                 #
# 说  明 : NONE                                                                                                                 #
###############################################################################################################################*/
void InitializeCapacity(void) {
    uint16_t impedance,ocv,ocvDelta;
     uint8_t i,y,Tab,count;
//##(0)读取保存在"EEPROM"中6个温度对应的"FCC"数值
    count = 0U;    
    while(read_eeprom_ucFCC() && count<8) { restart_wdt(); delay_ms(20); count++;} 
//##(0)读取"BQ76952"信息数据
    READ_BQ76952_PROCESS(); 
//##(0)根据当前温度设定当前对应的"FCC"值
         if(FG.Temperature<=NegTempConst20)  { Tab = 0;  FG.FCC = ucFCC[0];  }
    else if(FG.Temperature<=NegTempConst15)  { Tab = 1;  FG.FCC = ucFCC[1];  } 
    else if(FG.Temperature<=NegTempConst10)  { Tab = 2;  FG.FCC = ucFCC[2];  }
    else if(FG.Temperature<=NegTempConst5 )  { Tab = 3;  FG.FCC = ucFCC[3];  }
    else if(FG.Temperature<=ZeroTempConst )  { Tab = 4;  FG.FCC = ucFCC[4];  }
    else if(FG.Temperature<=PosTempConst5 )  { Tab = 5;  FG.FCC = ucFCC[5];  }
    else if(FG.Temperature<=PosTempConst10)  { Tab = 6;  FG.FCC = ucFCC[6];  }
    else if(FG.Temperature<=PosTempConst20)  { Tab = 7;  FG.FCC = ucFCC[7];  }
    else if(FG.Temperature<=PosTempConst25)  { Tab = 8;  FG.FCC = ucFCC[8];  }
    else if(FG.Temperature<=PosTempConst30)  { Tab = 9;  FG.FCC = ucFCC[9];  }
    else if(FG.Temperature<=PosTempConst40)  { Tab = 10; FG.FCC = ucFCC[10]; }
    else if(FG.Temperature<=PosTempConst50)  { Tab = 11; FG.FCC = ucFCC[11]; }
    else if(FG.Temperature<=PosTempConst60)  { Tab = 12; FG.FCC = ucFCC[12]; }
    else                                     { Tab = 13; FG.FCC = ucFCC[12]; }
//##(0)按照当前温度查表并获得电芯阻抗和电芯电压(并不是开路电芯电压)
    for(i=0; i<(sizeof(impTab)/26); i++) {
        if(FG.CellMin >= ocvTab[i][Tab]) {
            impedance = impTab[i][Tab];     //##(0)查表获取当前温度的电芯阻抗值
            break;
        }   
    }
//##(0)计算出当前电芯"OCV"(最低电芯电电压),
    ocv = (uint16_t)((int32_t)FG.CellMin - ((int32_t)FG.current*impedance)/1000);
//##(0)超过"4400mV"时,直接使用原电芯电压   
    if(ocv<=0u)    ocv = 0u;
    if(ocv>=4400u) ocv = FG.CellMin;
//##(0)按照百分5增量计算出大致剩余容量百分比  
    for(i=0; i<(sizeof(ocvTab)/26); i++) {
        if(ocv >= ocvTab[i][Tab]) {
            ocvDelta = (ocvTab[i-1][Tab] - ocvTab[i][Tab]) / 5;           //##(0)表格每个点之间细分5个(即按照1%再次细分)
            for(y=0; y<5u; y++) {                                         //##(0)每百分5细分为百分之一  
                if(ocv <= ( ocvTab[i][Tab] + ocvDelta *y )) 
                    break;                                                  //##(0)
            } 
            break; 
        }
    }    
//##(0)计算出剩余容量百分比
      FG.rsoc = (i<=21)? ((100-i*5) + y):(0);     
      FG.rsoc = (FG.rsoc>100)? 100 : FG.rsoc;
    FG.RemCap = (uint16_t)((uint32_t)FG.FCC*FG.rsoc/100);
//##(0)判断电池是否空 ?
    if(FG.rsoc<3u) { FG.b.FD = FG.BatteryStatus.FD = 1; }
//##(0)重置累积电荷积分和计时器      
    RESET_PASSQ_PROCESS();
    FG.LastPassQInt = FG.PassQInt = 0u;
    #asm nop #endasm
}

/*###############################################################################################################################
# 函数名 : boolean charging_discharge_Manage(void)                                                                              #
# 功  能 : 充放电管理                                                                                                           #
# 参  数 : NONE                                                                                                                 #
# 说  明 : NONE                                                                                                                 # 
###############################################################################################################################*/
void chargingDischargeManage(void) {
    int16_t CapDelta; 
//##(0)判断充电/放电(确认充电检测到+40mA则认为是充电/确认放电-40mA则认为是放电)
    FG.b.CHGING  =  FG.b.DSGING = false;  
    FG.b.CHGING |= (FG.AverageCurrent >  E2siDfilterCur);       //##(0)平均电流大于充电门槛电流则为充电状态
    FG.b.DSGING |= (FG.AverageCurrent < (-E2siDfilterCur));     //##(0)平均电流低于放电门槛电流则为放电状态
//##(0)是否需要设置充电显示【如果处于开机状态并且有电流流入】则使能充电显示    
    regs.flags.ChgProc = (FG.b.CHGING && regs.flags.RunMode == MODE_WORK)? 1:0; 	
//##(0)如果在充电状态下计算平均充满时间,没有充电则这时间为 65535
    if(FG.b.CHGING) {
        CapDelta = FG.FCC - FG.RemCap;
        FG.AverageTimeToFull = (CapDelta>0)? ((int32_t)CapDelta*60)/(abs(FG.AverageCurrent)) : 0u;
    }else{
        FG.AverageTimeToFull = 65535;           //##(0)没有充电则这时间为 65535
    } 
//##(0)如果在放电状态下则计算平均放空所需时间,没有放电则这时间为 65535
    if(FG.b.DSGING) {
        FG.AverageTimeToEmpty = ((uint32_t)FG.RemCap*60)/(abs(FG.AverageCurrent));
    }else{
        FG.AverageTimeToEmpty = 65535;          //##(0)没有放电则这时间为 65535
    }
//##(0)如果在放电状态下计算放空所需时间【实时】 
    if(FG.b.DSGING) {
        FG.RunTimeToEmpty = ((uint32_t)FG.RemCap*60)/(abs(FG.current));
    }else{
        FG.RunTimeToEmpty = 65535;
    }
//##(0)判断电池是否充满,充满条件 : 正在充电 && 平均电流低于截至电流 && 电芯电压(最低)大于截至电压持续40S
    if(FG.b.CHGING && !FG.b.FC && FG.AverageCurrent<E2siChgEndCur && FG.CellMin>E2uiChgTermVoltage) {
        FG.b.FC |= (++ucChgSetupTimeCntFC>=E2ucChgEndDelay1)? 1:0;  //##(0)电池充满
    }else if(FG.rsoc<95 || FG.CellMin<3950u) {
        FG.b.FC &= (++ucChgClearTimeCntFC>=E2ucChgEndDelay2)? 0:1;  //##(0)恢复充电
    }else{
        ucChgSetupTimeCntFC = ucChgClearTimeCntFC = 0u;             //##(0)计时器清零
    }
//##(0)如果放电中并且最大电芯电压低于终止电压持续5S则强行将容量变为3%(并且将FD标志设置为"1")
//##(0)判断是否清除"FD"标志,如果剩余容量百分比高于5%则设定FD标志为"0"     
    if(FG.b.DSGING && FG.CellMax < E2uiDsgTermVoltage) {
        if(++ucDsgSetupTimeCntFD >= E2ucDsgEndDelay) 
            FG.rsoc = 3;                                            //##(0)强行将容量设置为 3%
    }else{
        ucDsgSetupTimeCntFD = 0u;
    }
//##(0)如果剩余容量百分比低于3%则设定FD标志为"1"    
    if(FG.rsoc<=3u) { ucDsgClearTimeCntFD = 0; FG.b.FD = 1; }       //##(0)  
//##(0)如果剩余容量百分比高于5%则设定FD标志为"0"
    if(FG.rsoc>=5u) { 
        if(++ucDsgClearTimeCntFD >= E2ucDsgEndDelay) 
            FG.b.FD = 0;
    }
//##(0)设定电池状态标识
    FG.BatteryStatus.word = 0b0000000000000000;                     //##(0)初始化全部标志为"0"
    FG.BatteryStatus.OCA |= SafetyStatusA.COV;                      //##(0)Over Charged Alarm
    FG.BatteryStatus.TCA |= SafetyStatusA.OCC;                      //##(0)充电过流警告 
    FG.BatteryStatus.TCA |= SafetyStatusA.COV;                      //##(0)电芯过压警告
    FG.BatteryStatus.TCA |= SafetyStatusB.OTC;                      //##(0)充电过热警告 
    FG.BatteryStatus.OTA |= SafetyStatusB.OTD;                      //##(0)Over temperature Alarm  放电过热
    FG.BatteryStatus.OTA |= SafetyStatusB.OTC;                      //##(0)充电过热
    FG.BatteryStatus.DSG |= !FG.b.CHGING;                           //##(0)如果没有充电则设置放电标志 
    FG.BatteryStatus.FC  |= FG.b.FC;                                //##(0)电池充满标志(真实充满)
    FG.BatteryStatus.FD  |= FG.b.FD;                                //##(0)电池放空标志
    FG.BatteryStatus.RCA |= (FG.RemCapAlarm>FG.RemCap);             //##(0)剩余容量警告标志
    FG.BatteryStatus.RTA |= (FG.RemTimeAlarm>FG.RunTimeToEmpty);    //##(0)剩余时间警告标志
    FG.BatteryStatus.TDA |= (FG.rsoc<=6)? 1:0;                      //##(0)如果相对容量小于6%则将"TDA"标志设置为"1"
    FG.BatteryStatus.TDA &= (FG.rsoc>=8)? 0:1;                      //##(0)如果相对容量大于8%则将"TDA"标志设置为"0"
    FG.BatteryStatus.INIT = 1;                                      //##(0)默认
//##(3)根据充满设定充电电流和放电电流
    if(FG.BatteryStatus.FC || FG.BatteryStatus.TCA) {
        FG.ChargingCurrent = FG.ChargingVoltage = 0u;               //##(0)电池充满或者充电终止警告则将充电电流/电压设置为"0"
    }else if(FG.CellMax<E2PchgThrVoltage) {                                                       
        FG.ChargingCurrent = E2PChargingCurrent;                    //##(0)如果最低电芯电压小于2.8V则将充电电流设置为预充电电流
        FG.ChargingVoltage = E2ChargingVoltage;                     //##(0)正常充电电压
    }else if(FG.CellMin>E2SchgThrVoltage) {                         
        FG.ChargingCurrent = E2ChargingCurrent;                     //##(0)如果最高电芯电压大于3V则将充电电流设置为标准充电电流                       
        FG.ChargingVoltage = E2ChargingVoltage;                     //##(0)正常充电电压
    }else{
        ;
    }  
}

/*###############################################################################################################################
# 函数名 : void GaugeManage(void)                                                                                               #
# 功  能 : 计算电池充放电容量                                                                                                   #
# 参  数 : NONE                                                                                                                 #
# 说  明 : FCC 充满则更新                                                                                                       #
###############################################################################################################################*/
void GaugeManage_Process(void) { 
     int16_t tempComp;
    uint16_t u1MaxCap;              //##(0)更新容量最大限制变量寄存器
    uint16_t u1MinCap;              //##(0)更新容量最小限制变量寄存器
    uint16_t buffer;                //##(0)
      int32 delta_Q,TempRemaCap;
//##(0)判断休息时间【没有充放电状态下计时】    
    if(FG.b.DSGING==false && FG.b.CHGING==false) {
        if(regs.resttimer >= resttimerTerm) {
            tempComp = FG.Temperature - FG.LastTemperature;     //##(0)当前温度减去上一次休息温度
            tempComp = abs(tempComp);                           //##(0)差值绝对值
            if(tempComp>=50) {                                  //##(0)如果温度相差超过5℃则需要重新做OCV容量初始
                InitializeCapacity();                           //##(0)容量初始化
                FG.LastTemperature = FG.Temperature;            //##(0)当前温度作为基点,以备下次比较
            }
            if(FG.rsoc<StartUpdata && !FG.b.StartupdateFCC) {   //##(0)如果容量低于20%则开启充电"FCC"更新
                FG.b.StartupdateFCC = true;                     //##(0)启动FCC容量统计计数
                ulSaveFCC = FG.FCC;                             //##(0)保存当前"FCC"
                RESET_PASSQ_PROCESS();                          //##(0)重置累积电荷积分和计时器 
                FG.LastPassQInt = 0u;                           //##(0)历史累积清零
                FG.PassQInt = 0u;                               //##(0)当前累积清零
            }
        }
    }else if(FG.b.DSGING || FG.b.SCD) {                         //##(3)如果放电或者放电短路
        FG.b.StartupdateFCC = 0;                                //##(3)停止FCC充电容量统计
        regs.resttimer = 0;                                     //##(4)有充放电则将休息时间清零
    }else{
        regs.resttimer = 0;                                     //##(4)有充放电则将休息时间清零
    }
//##(0)电量计算
    delta_Q = FG.PassQInt - FG.LastPassQInt;                    //##(0)计算本次充放电电荷差值(单位:mA/h) 
    FG.LastPassQInt = FG.PassQInt;                              //##(0)更新基准点
	if(abs(delta_Q)<50) {
            TempRemaCap = (int32)FG.RemCap + delta_Q;               //##(0)计算当前容量(带符号)
	}else{
            TempRemaCap = (int32)FG.RemCap;
	}
//##(0)下限限制
    if(TempRemaCap<0) TempRemaCap = 0;                        //##(0)如果当前容量是负数则设置剩余容量为"0mA/h"
//##(0)上限限制【如果是需要更新"FCC"则不做上限处理】
    if(!FG.b.StartupdateFCC && TempRemaCap >= FG.FCC) {
        TempRemaCap =(int32_t)FG.FCC;                           //##(0)如果超出"FCC"则按照"FCC"值
    }
//##(0)最后值更新到剩余容量中    
    FG.RemCap = (uint16_t)TempRemaCap;                          //##(0)转换为无符号更新到剩余容量中  
//##(0)判断是否需要更新"FCC"     
    if(FG.b.FC && FG.b.StartupdateFCC) {                        //##(0)
        u1MinCap = (uint16_t)((uint32_t)ulSaveFCC*80/100);      //##(0)估算流入的电流容量值(95更改为60)
		u1MaxCap = (uint16_t)((uint32_t)ulSaveFCC*110/100);     //##(0)估算流入的电流容量值(从版本SW02393_2R08后更改为110%,
        if(FG.RemCap<u1MaxCap && FG.RemCap>u1MinCap) {          //##(0)容量必须在范围内则才更新
            FG.FCC = FG.RemCap;                                 //##(0)当前剩余容量作为"FCC"
            FG.b.StartupdateFCC = false;                        //##(0)更新完成则禁止FCC容量统计等下一次放开到充满
            save_eeprom_ucFCC();                                //##(0)存储当前FCC(需要关闭中断写EEPROM)
        } 
    }
//##(0)放电处理,如果放电统计容量超过一次循环电量阈值则更新放电次数
    if(FG.b.DSGING) {
        ulDsgCC += abs(delta_Q);                                //##(0)放电累积
        cycleEndCapacity = (uint16_t)((uint32_t)FG.FCC*95/100); //##(0)单次放电终止用来为FCC*0.95
        while(ulDsgCC >= cycleEndCapacity) {
            ulDsgCC -= cycleEndCapacity;                        //##(0)放电统计容量 =（放电统计容量 - 设计容量）  
            FG.CCC++;                                           //##(0)达到一个循环放电则放电次数递增
            writeEeprom(eeprom_cyc,(U8 *)&FG.CCC, 2);           //##(0)保存到"EEPROM"中
        }
    }
//##(4)计算剩余容量百分比,如果容量达到"FCC"则按照100%,否则计算 
    buffer = (uint16_t)((uint32_t)(FG.RemCap)*100/FG.FCC);      //##(0)计算出相对容量
    FG.rsoc = (FG.RemCap<FG.FCC)? buffer:100;                   //##(0)如果剩余容量小于充满容量则按照计算的值,否则是100%；
//##(6)电池充电终止或者电池过压,更新剩余容量为满充容量 ,剩余容量百分比为 100%
    if(FG.b.CHGING && (FG.b.FC || SafetyStatusA.COV) && FG.current<=E2siChgEndCur) {
        FG.RemCap = FG.FCC;   
        FG.rsoc = 100;
        regs.flags.RunMode = MODE_SLEEP;                        //##(0)充满进入睡眠(1.1.6版本开始增加)
    }
//##(7)如果电池欠压则将剩余容量和百分比设置为"0"
    if(SafetyStatusA.CUV || (FG.b.FD && FG.CellMin<E2uiDsgTermVoltage)) {
        if(++ucDsgTermTimeCnt>=E2ucDsgEndDelay) {
            FG.RemCap = FG.rsoc = 0;
        } 
    }else{
        ucDsgTermTimeCnt = 0x00;
    }
//##(8)计算出绝对容量
    FG.asoc = (uint32_t)FG.RemCap*100/FG.DesignCapacity;   
//##(9)健康度,如果健康度超过100%则按照100%
    FG.StateOfHealth = (uint32_t)FG.FCC*100/FG.DesignCapacity;
    if(FG.StateOfHealth>=100) { 
        FG.StateOfHealth = 100;
    } 
}
/*###############################################################################################################################
# 函数名 : void BMS_Task(void)                                                                                                  #
# 功  能 : BMS主业务任务函数                                                                                                    #
# 参  数 : NONE                                                                                                                 #
# 说  明 : 1000ms执行一次                                                                                                       #
###############################################################################################################################*/
void BMS_GaugeManage_Task(void) {
    static uint16_t timeout;  
//##(0)1秒钟时间没到则退出    
    if((regs.time10ms-timeout)<1000/10) return;
    timeout = regs.time10ms;
//##(0)读取数据，如果连续20次【20秒】读取失败则为故障
    if(READ_BQ76952_PROCESS()) {
        if(++regs.bqErrorCount>=10u)
            regs.FaultLive.bqxxx = true;		
    }else{
        regs.bqErrorCount = 0u;
        regs.FaultLive.bqxxx = false;
    }
//##(0)充电/放电管理	
    chargingDischargeManage();				
//##(0)容量计(主要时库仑计)	
    GaugeManage_Process(); 
}

/*###############################################################################################################################
# 声明结束                                                                                                                      #
###############################################################################################################################*/
#ifdef	__cplusplus
}
#endif
#endif

