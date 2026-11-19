/*###############################################################################################################################
 # 文件名称 ： u80711R01_BQ76952_H                                                                                              #
 # 公司名称 :  TOTEX Technology, Inc.                                                                                           #
 # 芯片型号 ： PIC24FJ128GA302                                                                                                  #
 # 编译工具 :  ccs compiler v5.118                                                                                              #
 # 作    者 :  BenZhang                                                                                                         #
 # 编写日期 :  2025/11/10                                                                                                       #
 # 版    本 :  v1.00                                                                                                            #
 ##############################################################################################################################*/
#ifndef APP_TMAG3001_H
#define	APP_TMAG3001_H
/*###############################################################################################################################
# 包含文件                                                                                                                      #
###############################################################################################################################*/
#include "app_config.h"
#include "apps_drive.h"
/*###############################################################################################################################
# 声明开始                                                                                                                      #
###############################################################################################################################*/
#ifdef	__cplusplus
extern "C" {
#endif     
    
#define U80722R01                   //##(0)声明为 U80711R01/声明U80712R01则需屏蔽即可    
/*###############################################################################################################################
# 霍尔宏定义                                                                                                                    #
###############################################################################################################################*/
#define xLO             20          //##(0)X 轴离开阈值
#define xHI             100         //##(0)X 轴吸附阈值
#define yLO             20          //##(0)Y 轴离开阈值
#define yHI             100         //##(0)Y 轴吸附阈值
#define zLO             20          //##(0)Z 轴离开阈值
#define zHI             100         //##(0)Z 轴吸附阈值
#define DeepSleepMode   0x03        //##(0)睡眠模式
#define ContinuousMode  0x01        //##(0)连续模式
#define DutyCycleMode   0x02        //##(0)占空比模式
#define Normal_Mode     0           //##(0)正常
#define Sleep_Mode      1           //##(0)从睡眠唤醒
#define UNFOLD_STATE    0           //##(0)展开状态
#define FOLD_STATE      1           //##(0)折叠状态
#define STRAP_Bind      1           //##(0)绑上状态
#define STRAP_REM       0           //##(0)移除状态 
	
#if defined(U80722R01)
    #define FOLD_TRIGGER    14.0f   //##(0)超过该值判定外加磁铁靠近【折叠】
    #define FOLD_RELEASE    12.5f   //##(0)低于该值判定外加磁铁离开【折叠】
    #define STRAP_TRIGGER    3.0f   //##(0)超过该值判定外加磁铁靠近【接上】
    #define STRAP_RELEASE    2.0f   //##(0)低于该值判定外加磁铁离开【移除】
#else 
    #define FOLD_TRIGGER    16.0f   //##(0)超过该值判定外加磁铁靠近【折叠】
    #define FOLD_RELEASE    14.0f   //##(0)低于该值判定外加磁铁离开【折叠】
    #define STRAP_TRIGGER    3.0f   //##(0)超过该值判定外加磁铁靠近【接上】
    #define STRAP_RELEASE    2.0f   //##(0)低于该值判定外加磁铁离开【移除】
#endif         		
/*###############################################################################################################################
# 函数使用定义,这些"BITS"定义可用于函数输入                                                                                     #
###############################################################################################################################*/
#define NUM_REGISTERS                       ((uint8_t) 29)      //##(0) 一共有29个寄存器 
#if defined(U80722R01)
    #define TMAG3001FOLD                    ((uint8_t) 0x68)    //##(0) 第一个霍尔传感器地址(U18折叠传感器)      
    #define TMAG3001STRAP                   ((uint8_t) 0x6A)    //##(0) 第二个霍尔传感器地址(U17绑带传感器) 
#else 
    #define TMAG3001FOLD                    ((uint8_t) 0x6A)    //##(0) 第一个霍尔传感器地址(U18折叠传感器)      
    #define TMAG3001STRAP                   ((uint8_t) 0x68)    //##(0) 第二个霍尔传感器地址(U17绑带传感器)  
#endif         
#define TMAG3001_40mT                       ((uint8_t) 0x00)
#define TMAG3001_120mT                      ((uint8_t) 0x02)
#define NO_TRIGGER                          ((uint8_t) 0x00)    //##(0) 0h = 转换从 I2C 命令位开始， 默认设置
#define TRIGGER_CONV                        ((uint8_t) 0x01)    //##(0) 1h = 转换通过 INT 引脚上的触发信号开始
#define MAG_TEMPCO_None                     ((uint8_t) 0x00)    //##(0) 0h = 0%（ 电流传感器应用）
#define MAG_TEMPCO_NdBFe                    ((uint8_t) 0x01)    //##(0) 1h = 0.12%/°C (NdBFe)
#define MAG_TEMPCO_SmCo                     ((uint8_t) 0x02)    //##(0) 2h = 0.03%/°C (SmCo)
#define MAG_TEMPCO_Ceramic                  ((uint8_t) 0x03)    //##(0) 3h = 0.2%/°C（ 陶瓷）

#define CONV_AVG_1xAverage                  ((uint8_t) 0x00)    //##(0) 0h = 1x - 10.5ksps（3 轴）或 22ksps（1 轴）
#define CONV_AVG_2xAverage                  ((uint8_t) 0x01)    //##(0) 1h =  2x - 5.9ksps（3 轴）或 14.3ksps（1 轴）
#define CONV_AVG_4xAverage                  ((uint8_t) 0x02)    //##(0) 2h =  4x - 3.1ksps（3 轴）或 8.3ksps（1 轴）
#define CONV_AVG_8xAverage                  ((uint8_t) 0x03)    //##(0) 3h =  8x - 1.6ksps（3 轴）或 4.5ksps（1 轴）
#define CONV_AVG_16xAverage                 ((uint8_t) 0x04)    //##(0) 4h = 16x - 0.8ksps（3 轴）或 2.4ksps（1 轴）
#define CONV_AVG_32xAverage                 ((uint8_t) 0x05)    //##(0) 5h = 32x - 0.4ksps（3 轴）或 1.2ksps（1 轴）

#define THR_HYST_2LSB                       ((uint8_t) 0x00)    //##(0) 0h =阈值 2LSB， 12 位分辨率（开关模式）| 阈值 1LSB， 8 位分辨率（变化时唤醒模式）
#define THR_HYST_4LSB                       ((uint8_t) 0x01)    //##(0) 1h =阈值 4LSB， 12 位分辨率（开关模式）| 阈值 2LSB， 8 位分辨率（变化时唤醒模式）
#define THR_HYST_8LSB                       ((uint8_t) 0x02)    //##(0) 2h =阈值 8LSB， 12 位分辨率（开关模式）| 阈值 4LSB， 8 位分辨率（变化时唤醒模式）
#define THR_HYST_16LSB                      ((uint8_t) 0x03)    //##(0) 3h =阈值 16LSB，12 位分辨率（开关模式）| 阈值 8LSB， 8 位分辨率（变化时唤醒模式）
#define THR_HYST_32LSB                      ((uint8_t) 0x04)    //##(0) 4h =阈值 32LSB，12 位分辨率（开关模式）| 阈值 16LSB，8 位分辨率（变化时唤醒模式）
#define THR_HYST_64LSB                      ((uint8_t) 0x05)    //##(0) 5h =阈值 64LSB，12 位分辨率（开关模式）| 阈值 32LSB，8 位分辨率（变化时唤醒模式）
#define THR_HYST_128LSB                     ((uint8_t) 0x06)    //##(0) 6h =阈值 128LSB,12 位分辨率（开关模式）| 阈值 64LSB，8 位分辨率（变化时唤醒模式）
#define THR_HYST_256LSB                     ((uint8_t) 0x07)    //##(0) 7h =阈值 256LSB,12 位分辨率（开关模式）| 阈值 128LSB,8 位分辨率（变化时唤醒模式）

#define ANGLE_HYST_1DEG                     ((uint8_t) 0x00)    //##(0) 0h = 1 度（ 开关模式） | 4 度变化触发中断（ 变化时唤醒模式）
#define ANGLE_HYST_2DEG                     ((uint8_t) 0x01)    //##(0) 1h = 2 度（ 开关模式） | 6 度变化触发中断（ 变化时唤醒模式）
#define ANGLE_HYST_4DEG                     ((uint8_t) 0x02)    //##(0) 2h = 4 度（ 开关模式） | 10 度变化触发中断（ 变化时唤醒模式）
#define ANGLE_HYST_8DEG                     ((uint8_t) 0x03)    //##(0) 3h = 8 度（ 开关模式） | 18 度变化触发中断（ 变化时唤醒模式）
 
#define MAG_CH_EN_Off                       ((uint8_t) 0x00)    //##(0) 0h = 所有磁通道关闭,默认设置
#define MAG_CH_EN_X                         ((uint8_t) 0x01)    //##(0) 1h = X 通道启用
#define MAG_CH_EN_Y                         ((uint8_t) 0x02)    //##(0) 2h = Y 通道启用
#define MAG_CH_EN_XY                        ((uint8_t) 0x03)    //##(0) 3h = X,Y 通道启用
#define MAG_CH_EN_Z                         ((uint8_t) 0x04)    //##(0) 4h = Z 通道启用
#define MAG_CH_EN_ZX                        ((uint8_t) 0x05)    //##(0) 5h = Z,X 通道启用
#define MAG_CH_EN_YZ                        ((uint8_t) 0x06)    //##(0) 6h = Y,Z 通道启用
#define MAG_CH_EN_XYZ                       ((uint8_t) 0x07)    //##(0) 7h = X,Y,Z 通道启用
#define MAG_CH_EN_XYX                       ((uint8_t) 0x08)    //##(0) 8h = XYX 通道启用
#define MAG_CH_EN_YXY                       ((uint8_t) 0x09)    //##(0) 9h = YXY 通道启用
#define MAG_CH_EN_YZY                       ((uint8_t) 0x0A)    //##(0) Ah = YZY 通道启用
#define MAG_CH_EN_XZX                       ((uint8_t) 0x0B)    //##(0) Bh = XZX 通道启用
#define MAG_CH_EN_XYZPositiveDiagOffset     ((uint8_t) 0x0C)    //##(0) CH = X,Y,Z 与正极诊断偏移
#define MAG_CH_EN_XYZNegativeDiagOffset     ((uint8_t) 0x0D)    //##(0) Dh = X,Y,Z 与负极诊断偏移
#define MAG_CH_EN_HallResistADCCheck        ((uint8_t) 0x0E)    //##(0) Eh = 霍尔电阻检查 + ADC 检查
#define MAG_CH_EN_HallOffsetAFECheck        ((uint8_t) 0x0F)    //##(0) Fh = 霍尔偏移检查 + AFE 检查

#define MAG_THR_DIR_Above                   ((uint8_t) 0x00)    //##(0) 0h = 为高于阈值的外部磁场设置中断
#define MAG_THR_DIR_Below                   ((uint8_t) 0x01)    //##(0) 1h = 为低于阈值的外部磁场设置中断
    
#define ANGLE_EN_Disabled                   ((uint8_t) 0x00)    //##(0) 0h = 无角度计算
#define ANGLE_EN_X1stY2nd                   ((uint8_t) 0x01)    //##(0) 1h = X 第一,Y 第二
#define ANGLE_EN_Y1stZ2nd                   ((uint8_t) 0x02)    //##(0) 2h = Y 第一,Z 第二
#define ANGLE_EN_X1stZ2nd                   ((uint8_t) 0x03)    //##(0) 3h = X 第一,Z 第二

#define RANGE_40mTor120mT                   ((uint8_t) 0x00)    //##(0) 0h = ±40mT (TMAG3001x1) 或 ±120mT (TMAG3001x2)
#define RANGE_80mTor240mT                   ((uint8_t) 0x01)    //##(0) 1h = ±80mT (TMAG3001x1) 或 ±240mT (TMAG3001x2)

#define WOC_Disabled                        ((uint8_t) 0x00)    //##(0) 0h = 禁用变化时唤醒
#define WOC_Angle                           ((uint8_t) 0x01)    //##(0) 1h = 在相对于先前的角度测量值发生变化时唤醒。 ANGLE_EN 位必须设置为 0h 以外的值。
#define WOC_MagneticField                   ((uint8_t) 0x02)    //##(0) 2h = 单轴先前磁场测量值变化时唤醒。根据 MAG_CH_EN 仅响应首个启用轴（X,Y或Z） 的变化

#define THR_None                            ((uint8_t) 0x00)    //##(0) 0h = 未选择阈值
#define THR_Angle                           ((uint8_t) 0x01)    //##(0) 1h = 选择了角度阈值。 
#define THR_BField                          ((uint8_t) 0x02)    //##(0) 2h = 选择了 B 场阈值。 
#define THR_Magnitude                       ((uint8_t) 0x03)    //##(0) 3h = 选择了幅度阈值

#define INT_STATE_Latched                   ((uint8_t) 0x00)    //##(0) 0h = INT\ 中断被锁存,直到由对器件寻址的控制器清除
#define INT_STATE_Pulse                     ((uint8_t) 0x01)    //##(0) 1h = INT\ 中断脉冲持续 5us

#define INTB_POL_DefaultHigh                ((uint8_t) 0x00)    //##(0)0h = INTB 引脚默认设置为高电平， 在中断事件期间低电平有效
#define INTB_POL_DefaultLow                 ((uint8_t) 0x40)    //##(0)1h = INTB 引脚默认设置为低电平， 在中断事件期间高电平有效

#define Interrupts_Disabled                 ((uint8_t) 0x00)    //##(0) 0h = 无中断
#define I2C_Busy_Interrupt                  ((uint8_t) 0x01)    //##(0) 1h = 通过 INT 实现中断
#define I2C_Busy_Wait                       ((uint8_t) 0x02)    //##(0) 2h = 通过 INT 实现中断,忽略是否正在与目标进行 I2C 通信。转换数据丢失。
#define SCL_Busy_Interrupt                  ((uint8_t) 0x03)    //##(0) 3h = 根据中断宽度通过 SCL 实现中断
#define SCL_Busy_Wait                       ((uint8_t) 0x04)    //##(0) 4h = 通过 SCL 实现中断,忽略是否正在进行 I2C 通信,无论目标地址如何都是如此。转换数据丢失。
#define Unipolar_Switch_Mode                ((uint8_t) 0x05)    //##(0) 5h = 单极开关模式。该模式覆盖任何中断功能（INT 触发器也被禁用）,仅实现开关功能。
#define Omnipolar_Switch_Mode               ((uint8_t) 0x06)    //##(0) 6h = 全极开关模式。该模式覆盖任何中断功能（INT 触发器也被禁用）,仅实现开关功能。

#define SLEEPTIME_1ms                       ((uint8_t) 0x00)    //##(0)0h = 1ms   
#define SLEEPTIME_5ms                       ((uint8_t) 0x01)    //##(0)1h = 5ms
#define SLEEPTIME_10ms                      ((uint8_t) 0x02)    //##(0)2h = 10ms   
#define SLEEPTIME_15ms                      ((uint8_t) 0x03)    //##(0)3h = 15ms
#define SLEEPTIME_20ms                      ((uint8_t) 0x04)    //##(0)4h = 20ms
#define SLEEPTIME_30ms                      ((uint8_t) 0x05)    //##(0)5h = 30ms
#define SLEEPTIME_50ms                      ((uint8_t) 0x06)    //##(0)6h = 50ms
#define SLEEPTIME_100ms                     ((uint8_t) 0x07)    //##(0)7h = 100ms
#define SLEEPTIME_500ms                     ((uint8_t) 0x08)    //##(0)8h = 500ms
#define SLEEPTIME_1000ms                    ((uint8_t) 0x09)    //##(0)9h = 1000ms
#define SLEEPTIME_2000ms                    ((uint8_t) 0x0A)    //##(0)Ah = 2000ms
#define SLEEPTIME_5000ms                    ((uint8_t) 0x0B)    //##(0)Bh = 5000ms
#define SLEEPTIME_20000ms                   ((uint8_t) 0x0C)    //##(0)Ch = 20000ms
    
/*###############################################################################################################################
# 温度电气特性（ECHAR）                                                                                                         #
# 目前，器件的 “典型值” 电气特性（ECHAR）已针对 ECHAR_T_ADC_RES 和 ECHAR_T_SENS_T0 进行设定。                                 #
# 这些数值可能存在个体差异；若通过器件校准获取了特定器件的实际数值，可对其进行更新，以实现更精准的温度测量。                    #
# TMAG3001 芯片的数据手册第 30 页包含温度传感电气特性的详细说明，相关定义名称与文档中的文字描述一一对应。                       #
###############################################################################################################################*/    
#define ECHAR_T_ADC_T0          ((float)17512)          //##(0)温度结果十进制值 @ ECHAR_T_SENS_T0(TADC_T0 为 17512)      
#define ECHAR_T_SENS_T0         ((float)25)             //##(0)数据表提供的典型值,实际值可能不同 (TSENS_T0 为 25°C)  
#define ECHAR_T_ADC_RES         ((float)58.2)           //##(0)温度传感分辨率(有效位/摄氏度), 数据手册提供的典型值，实际值可能存在差异 (TADC_RES 为 58.2LSB/°C)
/*###############################################################################################################################
# 磁传感器偏移校正转换                                                                                                          #
# Offset_Config_1 [7:0] 与 Offset_Config_2 [7:0] 的数据格式保持一致。 寄存器 : Sensor_Config_5/Sensor_Config_6                  #
# 各磁测量范围的 LSB 量级如下：                                                                                                 #
#  40 毫特斯拉（mT）： 19.53125  微特斯拉 / 最低有效位（uT/LSB）                                                                #
#  80 毫特斯拉（mT）： 39.06250  微特斯拉 / 最低有效位（uT/LSB）                                                                #
# 120 毫特斯拉（mT）： 64.94139  微特斯拉 / 最低有效位（uT/LSB）                                                                #
# 240 毫特斯拉（mT）： 129.87013 微特斯拉 / 最低有效位（uT/LSB）                                                                #
###############################################################################################################################*/   
#define VER_1_RANGE_0_OFFSET    ((float)0.01953125)         //##(0) 51.2mT/LSB
#define VER_1_RANGE_1_OFFSET    ((float)0.03906250)         //##(0) 25.6mT/LSB
#define VER_2_RANGE_0_OFFSET    ((float)0.06494139)         //##(0) 15.3985mT/LSB
#define VER_2_RANGE_1_OFFSET    ((float)0.12987013)         //##(0) 7.70mT/LSB    
/*###############################################################################################################################
# 磁传感器数据转换                                                                                                              #
# X_Result [15:0]、Y_Result [15:0] 与 Z_Result [15:0] 的数据格式完全一致。                                                      #
# 各磁测量范围的 LSB 量级如下：                                                                                                 #
#  40 毫特斯拉（mT）：1.19047619 微特斯拉 / 最低有效位（uT/LSB）                                                                #
#  80 毫特斯拉（mT）：2.38095238 微特斯拉 / 最低有效位（uT/LSB）                                                                #
# 120 毫特斯拉（mT）：3.66300366 微特斯拉 / 最低有效位（uT/LSB）                                                                #
# 240 毫特斯拉（mT）：4.14937759 微特斯拉 / 最低有效位（uT/LSB）                                                                #
###############################################################################################################################*/   
#define VER_1_RANGE_0_DATA      ((float)0.00119047619)      //##(0) 885mT/LSB 
#define VER_1_RANGE_1_DATA      ((float)0.00238095238)      //##(0) 446mT/LSB 
#define VER_2_RANGE_0_DATA      ((float)0.00366300366)      //##(0) 273mT/LSB 
#define VER_2_RANGE_1_DATA      ((float)0.00729927006)      //##(0) 137mT/LSB   
/*############################################################################################################################### 
# 幅值数据转换(角度和幅度定义)                                                                                                  # 
# 各磁测量范围的 LSB 量级如下：                                                                                                 # 
#  40 毫特斯拉（mT）：0.30478513 毫特斯拉 / 最低有效位（mT/LSB）                                                                #
#  80 毫特斯拉（mT）：0.60975610 毫特斯拉 / 最低有效位（mT/LSB）                                                                #
# 120 毫特斯拉（mT）：0.93808630 毫特斯拉 / 最低有效位（mT/LSB）                                                                #
# 240 毫特斯拉（mT）：1.86915888 毫特斯拉 / 最低有效位（mT/LSB）                                                                #
###############################################################################################################################*/  
#define VER_1_RANGE_0_MAGNITUDE ((float)0.30478513)         //##(0) 3.280mT/LSB 
#define VER_1_RANGE_1_MAGNITUDE ((float)0.60975610)         //##(0) 1.640mT/LSB 
#define VER_2_RANGE_0_MAGNITUDE ((float)0.93808630)         //##(0) 1.066mT/LSB 
#define VER_2_RANGE_1_MAGNITUDE ((float)1.86915888)         //##(0) 0.535mT/LSB  

/*###############################################################################################################################
#                               寄存器 0x00（Contoso CONFIG_1）定义                                                             #
###############################################################################################################################*/ 
#define DEVICE_CONFIG_1_ADDRESS                         ((uint8_t) 0x00)    //##(0)寄存器地址
#define DEVICE_CONFIG_1_DEFAULT                         ((uint8_t) 0x00)    //##(0)寄存器默认值
#define DEVICE_CONFIG_1_CRC_EN_MASK                     ((uint8_t) 0x80)    //##(0)寄存器字段掩码
#define DEVICE_CONFIG_1_MAG_TEMPCO_MASK                 ((uint8_t) 0x60)
#define DEVICE_CONFIG_1_CONV_AVG_MASK                   ((uint8_t) 0x1C)
#define DEVICE_CONFIG_1_I2C_RD_MASK                     ((uint8_t) 0x03)

#define DEVICE_CONFIG_1_CRC_EN_Disabled                 ((uint8_t) 0x00)    //##(0)禁用 CRC
#define DEVICE_CONFIG_1_CRC_EN_Enabled                  ((uint8_t) 0x80)    //##(0)启用 CRC     

#define DEVICE_CONFIG_1_MAG_TEMPCO_None                 ((uint8_t) 0x00)    //##(0)0h = 0%（ 电流传感器应用）
#define DEVICE_CONFIG_1_MAG_TEMPCO_NdBFe                ((uint8_t) 0x20)    //##(0)1h = 0.12%/°C (NdBFe)
#define DEVICE_CONFIG_1_MAG_TEMPCO_SmCo                 ((uint8_t) 0x40)    //##(0)2h = 0.03%/°C (SmCo)
#define DEVICE_CONFIG_1_MAG_TEMPCO_Ceramic              ((uint8_t) 0x60)    //##(0)3h = 0.2%/°C（ 陶瓷）

#define DEVICE_CONFIG_1_CONV_AVG_1xAverage              ((uint8_t) 0x00)    //##(0)0h = 1x  - 10.5ksps（ 3 轴）或 22ksps（ 1 轴）
#define DEVICE_CONFIG_1_CONV_AVG_2xAverage              ((uint8_t) 0x04)    //##(0)1h = 2x  - 5.9ksps（ 3 轴）或 14.3ksps（ 1 轴）
#define DEVICE_CONFIG_1_CONV_AVG_4xAverage              ((uint8_t) 0x08)    //##(0)2h = 4x  - 3.1ksps（ 3 轴）或 8.3ksps（ 1 轴）
#define DEVICE_CONFIG_1_CONV_AVG_8xAverage              ((uint8_t) 0x0C)    //##(0)3h = 8x  - 1.6ksps（ 3 轴）或 4.5ksps（ 1 轴）
#define DEVICE_CONFIG_1_CONV_AVG_16xAverage             ((uint8_t) 0x10)    //##(0)4h = 16x - 0.8ksps（ 3 轴）或 2.4ksps（ 1 轴）
#define DEVICE_CONFIG_1_CONV_AVG_32xAverage             ((uint8_t) 0x14)    //##(0)5h = 32x - 0.4ksps（ 3 轴）或 1.2ksps（ 1 轴）

#define DEVICE_CONFIG_1_I2C_RD_StandardI2C              ((uint8_t) 0x00)    //##(0)0h = 标准 I2C 3 字节读取命令
#define DEVICE_CONFIG_1_I2C_RD_16BitSensorData          ((uint8_t) 0x01)    //##(0)1h = 16 位传感器数据和转换状态的 1 字节 I2C 读取命令
#define DEVICE_CONFIG_1_I2C_RD_8BitSensorData           ((uint8_t) 0x02)    //##(0)2h = 8 位传感器 MSB 数据和转换状态的 1 字节 I2C 读取命令
#define DEVICE_CONFIG_1_I2C_RD_Reserved                 ((uint8_t) 0x03)    //##(0)3h = 保留
    
/*############################################################################################################################### 
#                               寄存器0x01（Contoso CONFIG_2）定义                                                              #
###############################################################################################################################*/     
#define DEVICE_CONFIG_2_ADDRESS                         ((uint8_t) 0x01)    //##(0)寄存器地址
#define DEVICE_CONFIG_2_DEFAULT                         ((uint8_t) 0x00)    //##(0)寄存器默认值
#define DEVICE_CONFIG_2_THR_HYST_MASK                   ((uint8_t) 0xE0)    //##(0)寄存器字段掩码
#define DEVICE_CONFIG_2_LP_LN_MASK                      ((uint8_t) 0x10)
#define DEVICE_CONFIG_2_I2C_GLITCH_FILTER_MASK          ((uint8_t) 0x08)
#define DEVICE_CONFIG_2_TRIGGER_MODE_MASK               ((uint8_t) 0x04)
#define DEVICE_CONFIG_2_OPERATING_MODE_MASK             ((uint8_t) 0x03)
//##(0)为开关模式（INT_MODE = 5h 或 6h） 或变化时唤醒模式 (WOC_SEL = 2h)下的磁场阈值选择迟滞
#define DEVICE_CONFIG_2_THR_HYST_2LSB                   ((uint8_t) 0x00)    //##(0)0h = 阈值 2LSB，  12 位分辨率（开关模式）| 阈值 1LSB， 8 位分辨率（变化时唤醒模式） 
#define DEVICE_CONFIG_2_THR_HYST_4LSB                   ((uint8_t) 0x20)    //##(0)1h = 阈值 4LSB，  12 位分辨率（开关模式）| 阈值 2LSB， 8 位分辨率（变化时唤醒模式）
#define DEVICE_CONFIG_2_THR_HYST_8LSB                   ((uint8_t) 0x40)    //##(0)2h = 阈值 8LSB，  12 位分辨率（开关模式）| 阈值 4LSB， 8 位分辨率（变化时唤醒模式）
#define DEVICE_CONFIG_2_THR_HYST_16LSB                  ((uint8_t) 0x60)    //##(0)3h = 阈值 16LSB， 12 位分辨率（开关模式）| 阈值 8LSB， 8 位分辨率（变化时唤醒模式）
#define DEVICE_CONFIG_2_THR_HYST_32LSB                  ((uint8_t) 0x80)    //##(0)4h = 阈值 32LSB， 12 位分辨率（开关模式）| 阈值 16LSB，8 位分辨率（变化时唤醒模式）
#define DEVICE_CONFIG_2_THR_HYST_64LSB                  ((uint8_t) 0xA0)    //##(0)5h = 阈值 64LSB， 12 位分辨率（开关模式）| 阈值 32LSB，8 位分辨率（变化时唤醒模式）
#define DEVICE_CONFIG_2_THR_HYST_128LSB                 ((uint8_t) 0xC0)    //##(0)6h = 阈值 128LSB，12 位分辨率（开关模式）| 阈值 64LSB，8 位分辨率（变化时唤醒模式）
#define DEVICE_CONFIG_2_THR_HYST_256LSB                 ((uint8_t) 0xE0)    //##(0)7h = 阈值 256LSB，12 位分辨率（开关模式）| 阈值 128LSB,8 位分辨率（变化时唤醒模式）
//##(0)在低有效电流模式和低噪声模式之间选择                                                                                
#define DEVICE_CONFIG_2_LP_LN_LowCurrent                ((uint8_t) 0x00)    //##(0)0h = 低有效电流模式
#define DEVICE_CONFIG_2_LP_LN_LowNoise                  ((uint8_t) 0x10)    //##(0)1h = 低噪声模式
//##(0)I2C 干扰滤波器
#define DEVICE_CONFIG_2_I2C_GLITCH_FILTER_On            ((uint8_t) 0x00)    //##(0)0h = 干扰滤波器开启
#define DEVICE_CONFIG_2_I2C_GLITCH_FILTER_Off           ((uint8_t) 0x08)    //##(0)1h = 干扰滤波器关闭
//##(0)根据已配置的寄存器选择启动单次转换的条件。正在运行的转换会在执行触发之前完成。冗余触发将被忽略。
#define DEVICE_CONFIG_2_TRIGGER_MODE_I2CCommand         ((uint8_t) 0x00)    //##(0)0h = 转换从I2C命令位开始,默认设置
#define DEVICE_CONFIG_2_TRIGGER_MODE_INTpin             ((uint8_t) 0x04)    //##(0)1h = 转换通过 INT 引脚上的触发信号开始
//##(0)如果器件从唤醒和睡眠模式转换到待机模式,则选择工作模式并根据工作模式更新值。
#define DEVICE_CONFIG_2_OPERATING_MODE_Standby          ((uint8_t) 0x00)    //##(0)0h = 待机模式（在触发事件时开始新的转换）
#define DEVICE_CONFIG_2_OPERATING_MODE_Sleep            ((uint8_t) 0x01)    //##(0)1h = 睡眠模式
#define DEVICE_CONFIG_2_OPERATING_MODE_Continuous       ((uint8_t) 0x02)    //##(0)2h = 连续模式
#define DEVICE_CONFIG_2_OPERATING_MODE_WakeupandSleep   ((uint8_t) 0x03)    //##(0)3h = 唤醒和睡眠模式（占空比模式） 

/*###############################################################################################################################
#                               寄存器0x02 （SENSOR_CONFIG_1）定义                                                              #
###############################################################################################################################*/  
#define SENSOR_CONFIG_1_ADDRESS                         ((uint8_t) 0x02)    //##(0)寄存器地址
#define SENSOR_CONFIG_1_DEFAULT                         ((uint8_t) 0x00)    //##(0)寄存器默认值
#define SENSOR_CONFIG_1_MAG_CH_EN_MASK                  ((uint8_t) 0xF0)    //##(0)寄存器字段掩码
#define SENSOR_CONFIG_1_SLEEPTIME_MASK                  ((uint8_t) 0x0F)
//##(0)启用磁轴通道的数据采集
#define SENSOR_CONFIG_1_MAG_CH_EN_Off                   ((uint8_t) 0x00)    //##(0)0h = 所有磁通道关闭,默认设置
#define SENSOR_CONFIG_1_MAG_CH_EN_X                     ((uint8_t) 0x10)    //##(0)1h = X 通道启用
#define SENSOR_CONFIG_1_MAG_CH_EN_Y                     ((uint8_t) 0x20)    //##(0)2h = Y 通道启用
#define SENSOR_CONFIG_1_MAG_CH_EN_XY                    ((uint8_t) 0x30)    //##(0)3h = X、Y 通道启用
#define SENSOR_CONFIG_1_MAG_CH_EN_Z                     ((uint8_t) 0x40)    //##(0)4h = Z 通道启用
#define SENSOR_CONFIG_1_MAG_CH_EN_ZX                    ((uint8_t) 0x50)    //##(0)5h = Z、 X 通道启用
#define SENSOR_CONFIG_1_MAG_CH_EN_YZ                    ((uint8_t) 0x60)    //##(0)6h = Y、 Z 通道启用
#define SENSOR_CONFIG_1_MAG_CH_EN_XYZ                   ((uint8_t) 0x70)    //##(0)7h = X、 Y、 Z 通道启用
#define SENSOR_CONFIG_1_MAG_CH_EN_XYX                   ((uint8_t) 0x80)    //##(0)8h = XYX 通道启用
#define SENSOR_CONFIG_1_MAG_CH_EN_YXY                   ((uint8_t) 0x90)    //##(0)9h = YXY 通道启用
#define SENSOR_CONFIG_1_MAG_CH_EN_YZY                   ((uint8_t) 0xA0)    //##(0)Ah = YZY 通道启用
#define SENSOR_CONFIG_1_MAG_CH_EN_XZX                   ((uint8_t) 0xB0)    //##(0)Bh = XZX 通道启用
#define SENSOR_CONFIG_1_MAG_CH_EN_XYZPositiveDiagOffset ((uint8_t) 0xC0)    //##(0)CH = X、 Y、 Z 与正极诊断偏移
#define SENSOR_CONFIG_1_MAG_CH_EN_XYZNegativeDiagOffset ((uint8_t) 0xD0)    //##(0)Dh = X、 Y、 Z 与负极诊断偏移
#define SENSOR_CONFIG_1_MAG_CH_EN_HallResistADCcheck    ((uint8_t) 0xE0)    //##(0)Eh = 霍尔电阻检查 + ADC 检查
#define SENSOR_CONFIG_1_MAG_CH_EN_HallOffsetAFEcheck    ((uint8_t) 0xF0)    //##(0)Fh = 霍尔偏移检查 + AFE 检查
//##(0)选择 Operating_Mode[1:0] = 3h 时转换之间处于低功耗模式的时间
#define SENSOR_CONFIG_1_SLEEPTIME_1ms                   ((uint8_t) 0x00)    //##(0)0h = 1ms   
#define SENSOR_CONFIG_1_SLEEPTIME_5ms                   ((uint8_t) 0x01)    //##(0)1h = 5ms
#define SENSOR_CONFIG_1_SLEEPTIME_10ms                  ((uint8_t) 0x02)    //##(0)2h = 10ms   
#define SENSOR_CONFIG_1_SLEEPTIME_15ms                  ((uint8_t) 0x03)    //##(0)3h = 15ms
#define SENSOR_CONFIG_1_SLEEPTIME_20ms                  ((uint8_t) 0x04)    //##(0)4h = 20ms
#define SENSOR_CONFIG_1_SLEEPTIME_30ms                  ((uint8_t) 0x05)    //##(0)5h = 30ms
#define SENSOR_CONFIG_1_SLEEPTIME_50ms                  ((uint8_t) 0x06)    //##(0)6h = 50ms
#define SENSOR_CONFIG_1_SLEEPTIME_100ms                 ((uint8_t) 0x07)    //##(0)7h = 100ms
#define SENSOR_CONFIG_1_SLEEPTIME_500ms                 ((uint8_t) 0x08)    //##(0)8h = 500ms
#define SENSOR_CONFIG_1_SLEEPTIME_1000ms                ((uint8_t) 0x09)    //##(0)9h = 1000ms
#define SENSOR_CONFIG_1_SLEEPTIME_2000ms                ((uint8_t) 0x0A)    //##(0)Ah = 2000ms
#define SENSOR_CONFIG_1_SLEEPTIME_5000ms                ((uint8_t) 0x0B)    //##(0)Bh = 5000ms
#define SENSOR_CONFIG_1_SLEEPTIME_20000ms               ((uint8_t) 0x0C)    //##(0)Ch = 20000ms

/*###############################################################################################################################
#                               寄存器0x03 （SENSOR_CONFIG_2）定义                                                              #
###############################################################################################################################*/ 
#define SENSOR_CONFIG_2_ADDRESS                         ((uint8_t) 0x03)    //##(0)寄存器地址
#define SENSOR_CONFIG_2_DEFAULT                         ((uint8_t) 0x00)    //##(0)寄存器默认值
#define SENSOR_CONFIG_2_T_RATE_MASK                     ((uint8_t) 0x80)    //##(0)寄存器字段掩码
#define SENSOR_CONFIG_2_INTB_POL_MASK                   ((uint8_t) 0x40)
#define SENSOR_CONFIG_2_MAG_THR_DIR_MASK                ((uint8_t) 0x20)
#define SENSOR_CONFIG_2_MAG_GAIN_CH_MASK                ((uint8_t) 0x10)
#define SENSOR_CONFIG_2_ANGLE_EN_MASK                   ((uint8_t) 0x0C)
#define SENSOR_CONFIG_2_X_Y_RANGE_MASK                  ((uint8_t) 0x02)
#define SENSOR_CONFIG_2_Z_RANGE_MASK                    ((uint8_t) 0x01)
#define SENSOR_CONFIG_2_FULL_RANGE_MASK                 ((uint8_t) 0x03)    //##(0)
//##(0)温度均值计算
#define SENSOR_CONFIG_2_T_RATE_SingleTempConv           ((uint8_t) 0x00)    //##(0)0h = 如果 MAG_CH_EN > 0， 则进行单次温度转换
#define SENSOR_CONFIG_2_T_RATE_FilterPerConv            ((uint8_t) 0x80)    //##(0)1h = 根据 Conv_AVG[2:0] 进行滤波
//##(0)选择中断事件的极性
#define SENSOR_CONFIG_2_INTB_POL_DefaultHigh            ((uint8_t) 0x00)    //##(0)0h = INTB 引脚默认设置为高电平， 在中断事件期间低电平有效
#define SENSOR_CONFIG_2_INTB_POL_DefaultLow             ((uint8_t) 0x40)    //##(0)1h = INTB 引脚默认设置为低电平， 在中断事件期间高电平有效
//##(0)选择阈值检查的方向
#define SENSOR_CONFIG_2_MAG_THR_DIR_Above               ((uint8_t) 0x00)    //##(0)0h = 为高于阈值的外部磁场设置中断
#define SENSOR_CONFIG_2_MAG_THR_DIR_Below               ((uint8_t) 0x20)    //##(0)1h = 为低于阈值的外部磁场设置中断
//##(0)为在 Sensor_Config_4 寄存器中输入的幅度增益校正值选择轴。
#define SENSOR_CONFIG_2_MAG_GAIN_CH_1stChannel          ((uint8_t) 0x00)    //##(0)0h = 选择第一个通道进行增益调整
#define SENSOR_CONFIG_2_MAG_GAIN_CH_2ndChannel          ((uint8_t) 0x10)    //##(0)1h = 选择第二个通道进行增益调整
//##(0)启用两个选定磁通道之间的角度计算、磁增益和偏移校正
#define SENSOR_CONFIG_2_ANGLE_EN_Disabled               ((uint8_t) 0x00)    //##(0)0h = 无角度计算
#define SENSOR_CONFIG_2_ANGLE_EN_X1stY2nd               ((uint8_t) 0x04)    //##(0)1h = X 第一， Y 第二
#define SENSOR_CONFIG_2_ANGLE_EN_Y1stZ2nd               ((uint8_t) 0x08)    //##(0)2h = Y 第一， Z 第二
#define SENSOR_CONFIG_2_ANGLE_EN_X1stZ2nd               ((uint8_t) 0x0C)    //##(0)3h = X 第一， Z 第二
//##(0)从 2 个不同的选项中选择 X 轴和 Y 轴磁场范围：
#define SENSOR_CONFIG_2_X_Y_RANGE_DEFAULT               ((uint8_t) 0x00)    //##(0)0h = ±40mT (TMAG3001x1) 或 ±120mT (TMAG3001x2)
#define SENSOR_CONFIG_2_X_Y_RANGE_80mTor240mT           ((uint8_t) 0x02)    //##(0)1h = ±80mT (TMAG3001x1) 或 ±240mT (TMAG3001x2)
//##(0)从 2 个不同的选项中选择 Z 轴磁场范围：
#define SENSOR_CONFIG_2_Z_RANGE_DEFAULT                 ((uint8_t) 0x00)    //##(0)0h = ±40mT (TMAG3001x1) 或 ±120mT (TMAG3001x2)
#define SENSOR_CONFIG_2_Z_RANGE_80mTor240mT             ((uint8_t) 0x01)    //##(0)1h = ±80mT (TMAG3001x1) 或 ±240mT (TMAG3001x2)

/*###############################################################################################################################
#                               寄存器0x04 （THR_CONFIG_1）定义                                                                 #
###############################################################################################################################*/ 
#define THR_CONFIG_1_ADDRESS                            ((uint8_t) 0x04)    //##(0)寄存器地址
#define THR_CONFIG_1_DEFAULT                            ((uint8_t) 0x00)    //##(0)寄存器默认值  
#define THR_CONFIG_1_THRESHOLD1_MASK                    ((uint8_t) 0xFF)    //##(0)寄存器字段掩码
    
/*###############################################################################################################################
#                               寄存器0x05 （THR_CONFIG_2）定义                                                                 #
###############################################################################################################################*/ 
#define THR_CONFIG_2_ADDRESS                            ((uint8_t) 0x05)    //##(0)寄存器地址   
#define THR_CONFIG_2_DEFAULT                            ((uint8_t) 0x00)    //##(0)寄存器默认值 
#define THR_CONFIG_2_THRESHOLD2_MASK                    ((uint8_t) 0xFF)    //##(0)寄存器字段掩码
    
/*###############################################################################################################################
#                               寄存器0x06 （THR_CONFIG_3）定义                                                                 #
###############################################################################################################################*/ 
#define THR_CONFIG_3_ADDRESS                            ((uint8_t) 0x06)    //##(0)寄存器地址
#define THR_CONFIG_3_DEFAULT                            ((uint8_t) 0x00)    //##(0)寄存器默认值 
#define THR_CONFIG_3_THRESHOLD3_MASK                    ((uint8_t) 0xFF)    //##(0)寄存器字段掩码

/*###############################################################################################################################
#                               寄存器0x07 （SENSOR_CONFIG_3）定义                                                              #
###############################################################################################################################*/ 
#define SENSOR_CONFIG_3_ADDRESS                         ((uint8_t) 0x07)    //##(0)寄存器地址
#define SENSOR_CONFIG_3_DEFAULT                         ((uint8_t) 0x00)    //##(0)寄存器默认值 
#define SENSOR_CONFIG_3_WOC_SEL_MASK                    ((uint8_t) 0xC0)    //##(0)寄存器字段掩码
#define SENSOR_CONFIG_3_THR_SEL_MASK                    ((uint8_t) 0x30)
#define SENSOR_CONFIG_3_ANG_HYS_MASK                    ((uint8_t) 0x0C)
#define SENSOR_CONFIG_3_ANG_OFFSET_EN_MASK              ((uint8_t) 0x02)
#define SENSOR_CONFIG_3_ANG_OFFSET_DIR_MASK             ((uint8_t) 0x01)
//##(0)启用当任何测得的磁读数与 THR_HYST 先前的测量值不同时产生中断响应
#define SENSOR_CONFIG_3_WOC_SEL_Disabled                ((uint8_t) 0x00)    //##(0)0h = 禁用变化时唤醒
#define SENSOR_CONFIG_3_WOC_SEL_Angle                   ((uint8_t) 0x40)    //##(0)1h = 在相对于先前的角度测量值发生变化时唤醒.ANGLE_EN 位必须设置为 0h 以外的值。
#define SENSOR_CONFIG_3_WOC_SEL_MagneticField           ((uint8_t) 0x80)    //##(0)2h = 单轴先前磁场测量值变化时唤醒.根据 MAG_CH_EN 仅响应首个启用轴（ X， Y 或 Z） 的变化
#define SENSOR_CONFIG_3_WOC_SEL_Reserved                ((uint8_t) 0xC0)    //##(0)3h = 保留
//##(0)设置 THR_Config_1、 THR_Config_2 和 THR_Config_3 寄存器的功能
#define SENSOR_CONFIG_3_THR_SEL_None                    ((uint8_t) 0x00)    //##(0)0h = 未选择阈值
#define SENSOR_CONFIG_3_THR_SEL_Angle                   ((uint8_t) 0x10)    //##(0)1h = 选择了角度阈值。
#define SENSOR_CONFIG_3_THR_SEL_BField                  ((uint8_t) 0x20)    //##(0)2h = 选择了 B 场阈值。
#define SENSOR_CONFIG_3_THR_SEL_Magnitude               ((uint8_t) 0x30)    //##(0)3h = 选择了幅度阈值（ 按钮按压）。
//##(0)为角度开关模式 (THR_SEL = 1h)或变化时唤醒模式 (WOC_SEL =1h)下的角度阈值选择迟滞
#define SENSOR_CONFIG_3_ANG_HYS_1deg                    ((uint8_t) 0x00)    //##(0)0h = 1 度（开关模式） |  4 度变化触发中断（变化时唤醒模式）
#define SENSOR_CONFIG_3_ANG_HYS_2deg                    ((uint8_t) 0x04)    //##(0)1h = 2 度（开关模式） |  6 度变化触发中断（变化时唤醒模式）
#define SENSOR_CONFIG_3_ANG_HYS_4deg                    ((uint8_t) 0x08)    //##(0)2h = 4 度（开关模式） | 10 度变化触发中断（变化时唤醒模式）
#define SENSOR_CONFIG_3_ANG_HYS_8deg                    ((uint8_t) 0x0C)    //##(0)3h = 8 度（开关模式） | 18 度变化触发中断（变化时唤醒模式）
//##(0)启用将偏移与最终角度值相加
#define SENSOR_CONFIG_3_ANG_OFFSET_EN_None              ((uint8_t) 0x00)    //##(0)0h = 寄存器 Angle_Offset[7:0] 中的值不与最终角度结果相加
#define SENSOR_CONFIG_3_ANG_OFFSET_EN_Add               ((uint8_t) 0x02)    //##(0)1h = 寄存器 Angle_Offset[7:0] 中的值与最终角度结果相加
//##(0)表示将 Angle_Offset[7:0] 中的偏移值与最终角度结果相加或相减。
#define SENSOR_CONFIG_3_ANG_OFFSET_DIR_Add              ((uint8_t) 0x00)    //##(0)0h = Angle_Offset[7:0] 中的值与最终角度结果相加
#define SENSOR_CONFIG_3_ANG_OFFSET_DIR_Subtract         ((uint8_t) 0x01)    //##(0)1h = 从最终角度结果中减去 Angle_Offset[7:0] 中的值

/*###############################################################################################################################
#                               寄存器0x08 （INT_CONFIG_1）定义                                                                 #
###############################################################################################################################*/
#define INT_CONFIG_1_ADDRESS                            ((uint8_t) 0x08)    //##(0)寄存器地址
#define INT_CONFIG_1_DEFAULT                            ((uint8_t) 0x00)    //##(0)寄存器默认值
#define INT_CONFIG_1_RSLT_INT_MASK                      ((uint8_t) 0x80)    //##(0)寄存器字段掩码
#define INT_CONFIG_1_THRSLD_INT_MASK                    ((uint8_t) 0x40)
#define INT_CONFIG_1_INT_STATE_MASK                     ((uint8_t) 0x20)
#define INT_CONFIG_1_INT_MODE_MASK                      ((uint8_t) 0x1C)
#define INT_CONFIG_1_INTB_POL_EN_MASK                   ((uint8_t) 0x02)
#define INT_CONFIG_1_MASK_INTB_MASK                     ((uint8_t) 0x01)
//##(0)启用在转换完成时产生中断响应  
#define INT_CONFIG_1_RSLT_INT_Disabled                  ((uint8_t) 0x00)    //##(0)0h = 当配置的一组转换完成时中断不置为有效
#define INT_CONFIG_1_RSLT_INT_Enabled                   ((uint8_t) 0x80)    //##(0)1h = 当配置的一组转换完成时中断置为有效 
//##(0)启用在预定义的阈值交叉上产生中断响应
#define INT_CONFIG_1_THRSLD_INT_Disabled                ((uint8_t) 0x00)    //##(0)0h = 阈值交叉时中断不置为有效
#define INT_CONFIG_1_THRSLD_INT_Enabled                 ((uint8_t) 0x40)    //##(0)1h = 阈值交叉时中断置为有效 
//##(0)INT 被锁存或发出脉冲
#define INT_CONFIG_1_INT_STATE_Latch                    ((uint8_t) 0x00)    //##(0)0h = INT\ 中断被锁存,直到由对器件寻址的控制器清除
#define INT_CONFIG_1_INT_STATE_Pulse                    ((uint8_t) 0x20)    //##(0)1h = INT\ 中断脉冲持续 5us
//##(0)中断模式选择
#define INT_CONFIG_1_INT_MODE_None                      ((uint8_t) 0x00)    //##(0)0h = 无中断
#define INT_CONFIG_1_INT_MODE_INT                       ((uint8_t) 0x04)    //##(0)1h = 通过INT实现中断
#define INT_CONFIG_1_INT_MODE_INTIgnoreIfI2C            ((uint8_t) 0x08)    //##(0)2h = 通过INT实现中断,忽略是否正在与目标进行I2C通信。转换数据丢失。
#define INT_CONFIG_1_INT_MODE_SCL                       ((uint8_t) 0x0C)    //##(0)3h = 根据中断宽度通过 SCL 实现中断
#define INT_CONFIG_1_INT_MODE_SCLIgnoreIfI2C            ((uint8_t) 0x10)    //##(0)4h = 通过SCL实现中断,忽略是否正在进行I2C通信,无论目标地址如何都是如此。转换数据丢失。
#define INT_CONFIG_1_INT_MODE_Unipolar                  ((uint8_t) 0x14)    //##(0)5h = 单极开关模式,该模式覆盖任何中断功能（INT 触发器也被禁用）,仅实现开关功能。
#define INT_CONFIG_1_INT_MODE_Omnipolar                 ((uint8_t) 0x18)    //##(0)6h = 全极开关模式.该模式覆盖任何中断功能（INT 触发器也被禁用）,仅实现开关功能。
#define INT_CONFIG_1_INT_MODE_Invalid                   ((uint8_t) 0x1C)    //##(0)7h = 无效。默认无中断
//##(0)INT 连接至 GND 时屏蔽 INT 引脚
#define INT_CONFIG_1_MASK_INTB_Enabled                  ((uint8_t) 0x00)    //##(0)0h = 启用 INT 引脚
#define INT_CONFIG_1_MASK_INTB_Disabled                 ((uint8_t) 0x01)    //##(0)1h = INT 引脚无法用作输入或输出

/*###############################################################################################################################
#                               寄存器0x09 （SENSOR_CONFIG_4）定义                                                              #
###############################################################################################################################*/
#define SENSOR_CONFIG_4_ADDRESS                         ((uint8_t) 0x09)    //##(0)寄存器地址
#define SENSOR_CONFIG_4_DEFAULT                         ((uint8_t) 0x00)    //##(0)寄存器默认值
#define SENSOR_CONFIG_4_GAIN_XTHRHI_MASK                ((uint8_t) 0xFF)    //##(0)寄存器字段掩码

/*###############################################################################################################################
#                               寄存器0x0A （SENSOR_CONFIG_5）定义                                                              #
###############################################################################################################################*/
#define SENSOR_CONFIG_5_ADDRESS                         ((uint8_t) 0x0A)    //##(0)寄存器地址
#define SENSOR_CONFIG_5_DEFAULT                         ((uint8_t) 0x00)    //##(0)寄存器默认值
#define SENSOR_CONFIG_5_OFFSET1_YTHRHI_MASK             ((uint8_t) 0xFF)    //##(0)寄存器字段掩码

/*###############################################################################################################################
#                               寄存器0x0B （SENSOR_CONFIG_6）定义                                                              #
###############################################################################################################################*/
#define SENSOR_CONFIG_6_ADDRESS                         ((uint8_t) 0x0B)    //##(0)寄存器地址
#define SENSOR_CONFIG_6_DEFAULT                         ((uint8_t) 0x00)    //##(0)寄存器默认值
#define SENSOR_CONFIG_6_OFFSET2_ZTHRHI_MASK             ((uint8_t) 0xFF)    //##(0)寄存器字段掩码

/*###############################################################################################################################
#                               寄存器0x0C （I2C_ADDRESS）定义                                                                  #
###############################################################################################################################*/
#define I2C_ADDRESS_ADDRESS                             ((uint8_t) 0x0C)    //##(0)寄存器地址
#define I2C_ADDRESS_DEFAULT                             ((uint8_t) 0x00)    //##(0)寄存器默认值
#define I2C_ADDRESS_I2C_ADDRESS_MASK                    ((uint8_t) 0xFE)    //##(0)寄存器字段掩码
#define I2C_ADDRESS_I2C_ADDRESS_UPDATE_EN_MASK          ((uint8_t) 0x01)

#define I2C_ADDRESS_I2C_ADDRESS_UPDATE_EN_Disabled      ((uint8_t) 0x00)    //##(0)0h = 为目标地址使用 ADDR 引脚配置   
#define I2C_ADDRESS_I2C_ADDRESS_UPDATE_EN_Enabled       ((uint8_t) 0x01)    //##(0)1h = 为目标地址使用 I2C_Address[6:0]

/*###############################################################################################################################
#                               寄存器0x0D （DEVICE_ID）定义                                                                    #
###############################################################################################################################*/
#define DEVICE_ID_ADDRESS                               ((uint8_t) 0x0D)    //##(0)寄存器地址
#define DEVICE_ID_DEFAULT                               ((uint8_t) 0x00)    //##(0)寄存器默认值
#define DEVICE_ID_VER_MASK                              ((uint8_t) 0x0C)    //##(0)寄存器字段掩码
//##(0)器件版本
#define DEVICE_ID_VER_TMAG3001A1                        ((uint8_t) 0x00)    //##(0)0h = TMAG3001 ±40 mT
#define DEVICE_ID_VER_TMAG3001A2                        ((uint8_t) 0x08)    //##(0)2h = TMAG3001 ±120mT

/*###############################################################################################################################
#                               寄存器0x0E （Manufacturer_ID_LSB）定义                                                          #
###############################################################################################################################*/
#define MANUFACTURER_ID_LSB_ADDRESS                     ((uint8_t) 0x0E)    //##(0)寄存器地址
#define MANUFACTURER_ID_LSB_DEFAULT                     ((uint8_t) 0x49)    //##(0)寄存器默认值
#define MANUFACTURER_ID_LSB_MANUFACTURER_ID_MASK        ((uint8_t) 0xFF)    //##(0)寄存器字段掩码

/*###############################################################################################################################
#                               寄存器0x0F （MANUFACTURER_ID_MSB）定义                                                          #
###############################################################################################################################*/
#define MANUFACTURER_ID_MSB_ADDRESS                     ((uint8_t) 0x0F)    //##(0)寄存器地址
#define MANUFACTURER_ID_MSB_DEFAULT                     ((uint8_t) 0x54)    //##(0)寄存器默认值
#define MANUFACTURER_ID_MSB_MANUFACTURER_ID_MASK        ((uint8_t) 0xFF)    //##(0)寄存器字段掩码

/*###############################################################################################################################
#                               寄存器0x10 （TEMP_RESULT_MSB）定义                                                              #
# 该寄存器是一个 8 位只读寄存器， 用于存储最近一次温度转换的 MSB 输出 。                                                        #            
###############################################################################################################################*/
#define TEMP_RESULT_MSB_ADDRESS                         ((uint8_t) 0x10)    //##(0)寄存器地址
#define TEMP_RESULT_MSB_DEFAULT                         ((uint8_t) 0x00)    //##(0)寄存器默认值
#define TEMP_RESULT_MSB_TEMP_RESULT_MASK                ((uint8_t) 0xFF)    //##(0)寄存器字段掩码

/*###############################################################################################################################
#                               寄存器0x11 （TEMP_RESULT_LSB）定义                                                              #
# 该寄存器是一个 8 位只读寄存器， 用于存储最近一次温度转换的 LSB 输出 。                                                        #
###############################################################################################################################*/
#define TEMP_RESULT_LSB_ADDRESS                         ((uint8_t) 0x11)    //##(0)寄存器地址
#define TEMP_RESULT_LSB_DEFAULT                         ((uint8_t) 0x00)    //##(0)寄存器默认值
#define TEMP_RESULT_LSB_TEMP_RESULT_MASK                ((uint8_t) 0xFF)    //##(0)寄存器字段掩码

/*###############################################################################################################################
#                               寄存器0x12 （X_RESULT_MSB）定义                                                                 #
# 该寄存器是一个 8 位只读寄存器， 用于存储最近一次 X 通道转换的 MSB 输出 。                                                     #
###############################################################################################################################*/
#define X_RESULT_MSB_ADDRESS                            ((uint8_t) 0x12)    //##(0)寄存器地址
#define X_RESULT_MSB_DEFAULT                            ((uint8_t) 0x00)    //##(0)寄存器默认值
#define X_RESULT_MSB_X_RESULT_MASK                      ((uint8_t) 0xFF)    //##(0)寄存器字段掩码

/*###############################################################################################################################
#                               寄存器0x13 （X_RESULT_LSB）定义                                                                 #
# 该寄存器是一个 8 位只读寄存器， 用于存储最近一次 X 通道转换的 LSB 输出 。                                                     #
###############################################################################################################################*/
#define X_RESULT_LSB_ADDRESS                            ((uint8_t) 0x13)    //##(0)寄存器地址
#define X_RESULT_LSB_DEFAULT                            ((uint8_t) 0x00)    //##(0)寄存器默认值
#define X_RESULT_LSB_X_RESULT_MASK                      ((uint8_t) 0xFF)    //##(0)寄存器字段掩码

/*###############################################################################################################################
#                               寄存器0x14 （Y_RESULT_MSB）定义                                                                 #
# 该寄存器是一个 8 位只读寄存器， 用于存储最近一次 Y 通道转换的 MSB 输出 。                                                     #
###############################################################################################################################*/
#define Y_RESULT_MSB_ADDRESS                            ((uint8_t) 0x14)    //##(0)寄存器地址
#define Y_RESULT_MSB_DEFAULT                            ((uint8_t) 0x00)    //##(0)寄存器默认值
#define Y_RESULT_MSB_Y_RESULT_MASK                      ((uint8_t) 0xFF)    //##(0)寄存器字段掩码

/*###############################################################################################################################
#                               寄存器0x15 （Y_RESULT_LSB）定义                                                                 #
#  该寄存器是一个 8 位只读寄存器， 用于存储最近一次 Y 通道转换的 LSB 输出 。                                                    #
###############################################################################################################################*/
#define Y_RESULT_LSB_ADDRESS                            ((uint8_t) 0x15)    //##(0)寄存器地址
#define Y_RESULT_LSB_DEFAULT                            ((uint8_t) 0x00)    //##(0)寄存器默认值
#define Y_RESULT_LSB_Y_RESULT_MASK                      ((uint8_t) 0xFF)    //##(0)寄存器字段掩码

/*###############################################################################################################################
#                               寄存器0x16 （Z_RESULT_MSB）定义                                                                 #
# 该寄存器是一个 8 位只读寄存器， 用于存储最近一次 Z 通道转换的 MSB 输出。                                                      # 
###############################################################################################################################*/
#define Z_RESULT_MSB_ADDRESS                            ((uint8_t) 0x16)    //##(0)寄存器地址
#define Z_RESULT_MSB_DEFAULT                            ((uint8_t) 0x00)    //##(0)寄存器默认值
#define Z_RESULT_MSB_Z_RESULT_MASK                      ((uint8_t) 0xFF)    //##(0)寄存器字段掩码

/*###############################################################################################################################
#                               寄存器0x17 （Z_RESULT_MSB）定义                                                                 #
# 该寄存器是一个 8 位只读寄存器， 用于存储最近一次 Z 通道转换的 LSB 输出。                                                      #
###############################################################################################################################*/
#define Z_RESULT_LSB_ADDRESS                            ((uint8_t) 0x17)    //##(0)寄存器地址
#define Z_RESULT_LSB_DEFAULT                            ((uint8_t) 0x00)    //##(0)寄存器默认值
#define Z_RESULT_LSB_Z_RESULT_MASK                      ((uint8_t) 0xFF)    //##(0)寄存器字段掩码
    
/*###############################################################################################################################
#                               寄存器0x18 （CONV_STATUS）定义                                                                  #
###############################################################################################################################*/  
#define CONV_STATUS_ADDRESS                             ((uint8_t) 0x18)    //##(0)寄存器地址
#define CONV_STATUS_DEFAULT                             ((uint8_t) 0x10)    //##(0)寄存器默认值
#define CONV_STATUS_SET_COUNT_MASK                      ((uint8_t) 0xE0)    //##(0)寄存器字段掩码
#define CONV_STATUS_POR_MASK                            ((uint8_t) 0x10)
#define CONV_STATUS_DIAG_STATUS_MASK                    ((uint8_t) 0x02)
#define CONV_STATUS_RESULT_STATUS_MASK                  ((uint8_t) 0x01)
//##(0)器件已上电或已经过上电复位,当主机写回“1”时,该位清零。
#define CONV_STATUS_POR_False                           ((uint8_t) 0x00)    //##(0)未发生 POR
#define CONV_STATUS_POR_True                            ((uint8_t) 0x10)    //##(0)发生了 POR
//##(0)检测任何内部诊断失败,包括内部存储器 CRC 错误,INT 引脚错误
#define CONV_STATUS_DIAG_STATUS_NoFail                  ((uint8_t) 0x00)    //##(0)无诊断失败
#define CONV_STATUS_DIAG_STATUS_Fail                    ((uint8_t) 0x02)    //##(0)检测到诊断失败
//##(0)转换数据结果已准备好被读取。
#define CONV_STATUS_RESULT_STATUS_Incomplete            ((uint8_t) 0x00)    //##(0)转换数据未完成
#define CONV_STATUS_RESULT_STATUS_Complete              ((uint8_t) 0x01)    //##(0)转换数据已完成

/*###############################################################################################################################
#                               寄存器0x19 （ANGLE_RESULT_MSB）定义                                                             #
# 该寄存器是一个 8 位只读寄存器， 用于存储最近一次角度转换的 MSB 输出。                                                         #
###############################################################################################################################*/  
#define ANGLE_RESULT_MSB_ADDRESS                        ((uint8_t) 0x19)    //##(0)寄存器地址
#define ANGLE_RESULT_MSB_DEFAULT                        ((uint8_t) 0x00)    //##(0)寄存器默认值
#define ANGLE_RESULT_MSB_ANGLE_RESULT_MASK              ((uint8_t) 0xFF)    //##(0)寄存器字段掩码

/*###############################################################################################################################
#                               寄存器0x1A （ANGLE_RESULT_LSB）定义                                                             #
# 该寄存器是一个 8 位只读寄存器， 用于存储最近一次角度转换的 LSB 输出。                                                         # 
###############################################################################################################################*/ 
#define ANGLE_RESULT_LSB_ADDRESS                        ((uint8_t) 0x1A)    //##(0)寄存器地址
#define ANGLE_RESULT_LSB_DEFAULT                        ((uint8_t) 0x00)    //##(0)寄存器默认值
#define ANGLE_RESULT_LSB_ANGLE_RESULT_MASK              ((uint8_t) 0xFF)    //##(0)寄存器字段掩码

/*###############################################################################################################################
#                               寄存器0x1B （MAGNITUDE_RESULT）定义                                                             #
# 该寄存器是一个 8 位只读寄存器， 用于存储最近一次幅度转换的输出。数据以二进制补码格式表示。                                    # 
###############################################################################################################################*/
#define MAGNITUDE_RESULT_ADDRESS                        ((uint8_t) 0x1B)    //##(0)寄存器地址
#define MAGNITUDE_RESULT_DEFAULT                        ((uint8_t) 0x00)    //##(0)寄存器默认值
#define MAGNITUDE_RESULT_MAGNITUDE_RESULT_MASK          ((uint8_t) 0xFF)    //##(0)寄存器字段掩码
  
/*###############################################################################################################################
#                               寄存器0x1C （DEVICE_STATUS）定义                                                                #
###############################################################################################################################*/
#define DEVICE_STATUS_ADDRESS                           ((uint8_t) 0x1C)    //##(0)寄存器地址
#define DEVICE_STATUS_DEFAULT                           ((uint8_t) 0x00)    //##(0)寄存器默认值
#define DEVICE_STATUS_INTB_RB_MASK                      ((uint8_t) 0x10)    //##(0)寄存器字段掩码
#define DEVICE_STATUS_INT_ER_MASK                       ((uint8_t) 0x04)
#define DEVICE_STATUS_OTP_CRC_ER_MASK                   ((uint8_t) 0x02)
#define DEVICE_STATUS_THR_CROSS_MASK                    ((uint8_t) 0x01)
//##(0)指示器件从 INT 引脚读回的电平。
#define DEVICE_STATUS_INTB_RB_Low                       ((uint8_t) 0x00)    //##(0)INT 引脚被驱动为低电平
#define DEVICE_STATUS_INTB_RB_High                      ((uint8_t) 0x10)    //##(0)INT 引脚处于高电平状态 
//##(0)指示是否检测到 INT 引脚错误,当主机写入1h时,该位清零 。
#define DEVICE_STATUS_INT_ER_NoError                    ((uint8_t) 0x00)    //##(0)未检测到 INT 错误
#define DEVICE_STATUS_INT_ER_INTError                   ((uint8_t) 0x04)    //##(0)检测到 INT 错误
//##(0)指示是否检测到 OTP CRC 错误,当主机写入1h时,该位清零。
#define DEVICE_STATUS_OTP_CRC_ER_NoError                ((uint8_t) 0x00)    //##(0)未检测到 OTP CRC 错误
#define DEVICE_STATUS_OTP_CRC_ER_Error                  ((uint8_t) 0x02)    //##(0)检测到 OTP CRC 错误
//##(0)当检测到阈值交叉时,该位被设置。
#define DEVICE_STATUS_THR_CROSS_False                   ((uint8_t) 0x00)    //##(0)未检测到阈值交叉
#define DEVICE_STATUS_THR_CROSS_True                    ((uint8_t) 0x01)    //##(0)检测到阈值交叉

/*###############################################################################################################################
#  函数声明                                                                                                                     #
###############################################################################################################################*/
bool TMAG3001writeToSingleRegister(uint8_t chipAddr,uint8_t address, uint8_t *data);    
bool TMAG3001readSingleRegister(uint8_t chipAddr,uint8_t address, uint8_t *data); 

bool TMAG3001startup(uint8_t chipAddr);
bool TMAG3001restoreDefaultValues(uint8_t chipAddr);   
bool TMAG3001updateI2Caddress(uint8_t chipAddr, uint8_t i2c_address);
bool TMAG3001intbPolarity(uint8_t chipAddr,uint8_t intb_pol);

//##(0)I2C功能
bool TMAG3001setI2CreadMode(uint8_t chipAddr,uint8_t read_mode);
bool TMAG3001enableCRC(uint8_t chipAddr);
bool TMAG3001disableCRC(uint8_t chipAddr);
bool TMAG3001i2cGlitchFilterEnabled(uint8_t chipAddr);
bool TMAG3001i2cGlitchFilterDisabled(uint8_t chipAddr);

//##(0)更改设备操作模式
bool TMAG3001enterStandbyMode(uint8_t chipAddr);
bool TMAG3001enterContinuousMeasureMode(uint8_t chipAddr);
bool TMAG3001enterSleepMode(uint8_t chipAddr);
bool TMAG3001enterWakeUpAndSleepMode(uint8_t chipAddr);
bool TMAG3001setSLEEPTIME(uint8_t chipAddr,uint8_t sleeptime);
bool TMAG3001setWakeUpAndSleepMode(uint8_t chipAddr,uint8_t sleeptime);
bool TMAG3001exitSleepMode(uint8_t chipAddr);
bool TMAG3001exitWakeAndSleepMode(uint8_t chipAddr);

//##(0)配置触发器设置的功能
bool TMAG3001i2cTriggersConversion(uint8_t chipAddr);
bool TMAG3001intTriggersConversion(uint8_t chipAddr);

//##(0)中断配置
bool TMAG3001interruptThroughINT(uint8_t chipAddr,uint8_t i2c_busy);
bool TMAG3001interruptThroughSCL(uint8_t chipAddr,uint8_t i2c_busy);
bool TMAG3001intPinLatchedPulsed(uint8_t chipAddr,uint8_t int_state);    
bool TMAG3001thrDirCheck(uint8_t chipAddr, uint8_t dir);
bool TMAG3001enableResultReadyInterrupt(uint8_t chipAddr);
bool TMAG3001disableResultReadyInterrupt(uint8_t chipAddr);
bool TMAG3001enableSwitchMode(uint8_t chipAddr,uint8_t switch_type);
bool TMAG3001disableInterrupts(uint8_t chipAddr);
bool TMAG3001enableIntbPin(uint8_t chipAddr);
bool TMAG3001disableIntbPin(uint8_t chipAddr);
bool TMAG3001setAngleHyst(uint8_t chipAddr, uint8_t angle_hys);
bool TMAG3001enableWakeOnAngleChange(uint8_t chipAddr,uint8_t angle_hyst);
bool TMAG3001enableWakeOnFieldChange(uint8_t chipAddr,uint8_t thr_hyst);
bool TMAG3001disableWakeOnChange(uint8_t chipAddr);
bool TMAG3001setAngleThreshold(uint8_t chipAddr,uint8_t angle_offest_en, uint8_t angle_offset_dir, uint8_t angle_ref, uint8_t angle_band, uint8_t angle_offset);
bool TMAG3001setAngleHyst(uint8_t chipAddr,uint8_t angle_hys);
bool TMAG3001setThrHyst(uint8_t chipAddr,uint8_t thr_hys);
bool TMAG3001setFieldThreshold(uint8_t chipAddr,uint8_t x_thr_lo, uint8_t x_thr_hi, uint8_t y_thr_lo, uint8_t y_thr_hi, uint8_t z_thr_lo, uint8_t z_thr_hi);
bool TMAG3001setMagnitudeThreshold(uint8_t chipAddr,uint8_t m_thr_lo, uint8_t m_thr_hi);
bool TMAG3001disableThresholds(uint8_t chipAddr);

//##(0)测量配置功能
bool TMAG3001setTempCoefficient(uint8_t chipAddr,uint8_t temp_coefficient);
bool TMAG3001setSampleRate(uint8_t chipAddr,uint8_t CONV_AVG_bits);
bool TMAG3001enableMagChannels(uint8_t chipAddr,uint8_t mag_ch_en_bits);
bool TMAG3001setTemperatureAveraging(uint8_t chipAddr,uint8_t temp_avg);
bool TMAG3001enableAngleMeasurement(uint8_t chipAddr,uint8_t angle_en_bits);
bool TMAG3001setRanges(uint8_t chipAddr,uint8_t x_y_range_bits, uint8_t z_range_bits);
bool TMAG3001selectLowCurrentNoiseMode(uint8_t chipAddr,uint8_t low_mode);
  
//##(0)偏移和增益校正功能
bool TMAG3001setMagGainConfigIn8Bit(uint8_t chipAddr,uint8_t channel, uint8_t gain_bits);
bool TMAG3001setMagGainConfigInDecimal(uint8_t chipAddr,uint8_t channel, float gain_value);
bool TMAG3001setMagOffsetIn8Bit(uint8_t chipAddr,uint8_t offset1_bits, uint8_t offset2_bits);
bool TMAG3001setMagOffsetInmT(uint8_t chipAddr, float offset1_delta, float offset2_delta);

//##(0)获取结果/测量功能（标准3字节I2C只读）
uint8_t TMAG3001getXMSBresult(uint8_t chipAddr);
uint8_t TMAG3001getXLSBresult(uint8_t chipAddr);
uint8_t TMAG3001getYMSBresult(uint8_t chipAddr);
uint8_t TMAG3001getYLSBresult(uint8_t chipAddr);
uint8_t TMAG3001getZMSBresult(uint8_t chipAddr);
uint8_t TMAG3001getZLSBresult(uint8_t chipAddr);
uint8_t TMAG3001getTempMSBresult(uint8_t chipAddr);
uint8_t TMAG3001getTempLSBresult(uint8_t chipAddr);
uint8_t TMAG3001getAngleMSBresult(uint8_t chipAddr);
uint8_t TMAG3001getAngleLSBresult(uint8_t chipAddr);
uint8_t TMAG3001getMAGresult(uint8_t chipAddr);
void    TMAG3001getMagResultsRegisters(uint8_t chipAddr,int16_t meas_arr[]);
float   TMAG3001getMeasurementX(uint8_t chipAddr);
float   TMAG3001getMeasurementY(uint8_t chipAddr);
float   TMAG3001getMeasurementZ(uint8_t chipAddr);
float   TMAG3001getMeasurementTEMP(uint8_t chipAddr);
float   TMAG3001getMeasurementANGLE(uint8_t chipAddr);
float   TMAG3001getMeasurementMAG(uint8_t chipAddr);
void    TMAG3001getMagMeasurementXYZ(uint8_t chipAddr,float meas_arr[]);

//##(0)获取范围函数
uint16_t TMAG3001getXYrange(uint8_t chipAddr);
uint16_t TMAG3001getZrange(uint8_t chipAddr);

//##(0)获取设备信息功能
uint8_t TMAG3001getVersion(uint8_t chipAddr);
uint8_t TMAG3001isCRCenabled(uint8_t chipAddr);


//##(0)辅助函数
uint8_t TMAG3001getAngleEnValue(uint8_t chipAddr);
uint32_t isqrt32(uint32_t h);
float TMAG3001resultRegisterTomT(int16_t register_bits, uint16_t range);
float TMAG3001angleRegisterToDeg(uint16_t register_bits);
uint8_t TMAG3001calculateCRC(uint8_t chipAddr,uint8_t i2cRead, uint8_t numChannels, uint8_t data[]);
bool TMAG3001verifyCRC(uint8_t chipAddr,uint8_t i2cRead, uint8_t numChannels, uint8_t data[]);
void TMAG3001intPulse(uint8_t chipAddr);

/*###############################################################################################################################
#  霍尔传感器变量声明                                                                                                           #
###############################################################################################################################*/
int16_t STRAPX;            //##(0)绑带磁场强度(mT)X轴,传感器U17
int16_t STRAPY;            //##(0)绑带磁场强度(mT)Y轴,传感器U17
int16_t STRAPZ;            //##(0)绑带磁场强度(mT)Z轴,传感器U17
int16_t STRAP_ANGLE;       //##(0)绑带角度(度),传感器U17 
int16_t STRAP_MAGNITUTE;   //##(0)绑带幅度(mT),传感器U17

int16_t FOLDX;             //##(0)折叠磁场强度(mT)X轴,传感器U18     
int16_t FOLDY;             //##(0)折叠磁场强度(mT)X轴,传感器U18
int16_t FOLDZ;             //##(0)折叠磁场强度(mT)X轴,传感器U18
int16_t FOLD_ANGLE;        //##(0)折叠角度(度),传感器U18
int16_t FOLD_MAGNITUTE;    //##(0)折叠幅度(mT),传感器U18  
/*###############################################################################################################################
# 寄存器写入函数(写单个寄存器数据)                                                                                               #
# 该函数接收待写入的寄存器地址和 8 位数据帧，并将该数据帧写入对应寄存器。                                                       #
# 本函数会用输入数据覆盖整个寄存器，务必确保需保持不变的数值已包含在输入数据中！                                                #
# chipAddr - 芯片地址(0x68/0x6A默认地址), address - 待写入的寄存器地址，为 0x00 至 0x1C 范围内的 uint8_t 类型数值               #
# data - 待写入 address 对应寄存器的 8 位数据帧                                                                                 #
###############################################################################################################################*/ 
bool TMAG3001writeToSingleRegister(uint8_t chipAddr, uint8_t address, uint8_t *data) {
    return(i2c_PutsData(chipAddr, address, data, 1U));
} 
/*###############################################################################################################################
# 读取单个寄存器函数                                                                                                            #
# 该函数接收待读取的寄存器地址，随后创建 dataTx 数组并调用 i2cReceiveArrays 函数，同时解析 dataRx 数组中的数据。                #
# chipAddr - 芯片地址(0x68/0x6A默认地址)                                                                                        #
#  address - 待读取的寄存器地址，为 0x00 至 0x1C 范围内的 uint8_t 类型数值                                                      #
#    *data - 数据指针                                                                                                           #
###############################################################################################################################*/ 
bool TMAG3001readSingleRegister(uint8_t chipAddr,uint8_t address, uint8_t *data) {
    return(i2c_GetsData(chipAddr, address, data, 1U));
}
/*###############################################################################################################################
# 恢复器件寄存器默认值                                                                                                          #
#                                                                                                                               #
# 本函数将所有寄存器设置为其默认值，具体默认值如数据手册第 9 章"寄存器映射(Register Map)"中所述                                 #
###############################################################################################################################*/   
bool TMAG3001restoreDefaultValues(uint8_t chipAddr) {
    int i = 0;
    uint8_t defaultRegisters[NUM_REGISTERS] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                0x49, 0x54, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                0x00 };
//##(0)默认的寄存器数据写入芯片
    for(i=0; i<NUM_REGISTERS; i++) {
       if(TMAG3001writeToSingleRegister(chipAddr, i, &defaultRegisters[i])) return(true);
       delay_ms(1);
    }
    #asm nop #endasm
    return(false); 
}   
/*###############################################################################################################################
# 更新 I2C 地址                                                                                                                 #
# 本函数可用于更新 TMAG3001 的 I2C 地址                                                                                         #
# i2c_address - 7 位 I2C 地址                                                                                                   #
# 注：基于 ADDR 引脚连接配置的出厂默认 7 位 I2C 地址，会在器件首次上电时从 OTP（一次性可编程存储器）中加载；                    #
# 因此每次电源循环（断电再上电）后，都必须重新写入这些位，以避免器件恢复为出厂默认地址                                          #
###############################################################################################################################*/
bool TMAG3001updateI2Caddress(uint8_t chipAddr ,uint8_t i2c_address) {
    uint8_t input;
//##(0)读取出当前地址
    if(TMAG3001readSingleRegister(chipAddr, I2C_ADDRESS_ADDRESS,&input))  return(true);
//##(0)修改为目标地址    
    input &= ~(I2C_ADDRESS_I2C_ADDRESS_MASK);
    input |= (i2c_address << 1) + I2C_ADDRESS_I2C_ADDRESS_UPDATE_EN_Enabled;
//##(0)写入目标地址    
    if(TMAG3001writeToSingleRegister(chipAddr,I2C_ADDRESS_ADDRESS, &input)) return(true);
    #asm nop #endasm
    return(false);
}
/*###############################################################################################################################
# 配置 INTB 引脚极性                                                                                                            #
# 本函数可根据输入值配置 INTB 引脚的极性，使其默认状态为高电平或低电平                                                          #
# intb_pol - 用于确定中断事件触发时 INTB 引脚极性的配置值                                                                       #
# 0x00 = INTB 引脚默认设置为高电平，中断事件触发时为低有效                                                                      #
# 0x01 = INTB 引脚默认设置为低电平，中断事件触发时为高有效                                                                      #
###############################################################################################################################*/
bool TMAG3001intbPolarity(uint8_t chipAddr,uint8_t intb_pol) {
    uint8_t input;
//##(0)读取出当前数据
    if(TMAG3001readSingleRegister(chipAddr, SENSOR_CONFIG_2_ADDRESS,&input))  return(true);
//##(0)修改 INTB 引脚极性
    input &= ~(SENSOR_CONFIG_2_INTB_POL_MASK);
    input |= SENSOR_CONFIG_2_INTB_POL_DefaultHigh + (intb_pol << 6);
//##(0)写入目标数据
    if(TMAG3001writeToSingleRegister(chipAddr,SENSOR_CONFIG_2_ADDRESS, &input))  return(true);
    #asm nop #endasm
    return(false);
}   
/*###############################################################################################################################
# 设置I2C读取模式                                                                                                               #
# read_mode-决定选择哪种读取模式                                                                                                #
# 0x00 = 标准I2C 3字节读取命令                                                                                                  #
# 0x01 = 16位传感器数据的1字节I2C读取命令                                                                                       #
# 0x02 = 8位传感器MSB数据的1字节I2C读取命令                                                                                     #
# 注意：使用1字节读取命令之一时，一旦设置了此模式后面的任何读取命令（单个、多个或其他）只会按以下顺序返回结果寄存器，如果有多个 #
# 启用数据通道，X、Y、Z。结果寄存器将后面是CONV_STATUS寄存器和CRC字节(如果CRC已经启用)。                                        #
###############################################################################################################################*/
bool TMAG3001setI2CreadMode(uint8_t chipAddr,uint8_t read_mode) {
    uint8_t input;
//##(0)读取出当前数据
    if(TMAG3001readSingleRegister(chipAddr,DEVICE_CONFIG_1_ADDRESS, &input))  return(true);
//##(0)修改I2C读取模式    
    input &= ~(DEVICE_CONFIG_1_I2C_RD_MASK);
    input |= DEVICE_CONFIG_1_I2C_RD_StandardI2C + read_mode;
//##(0)写入目标数据
    if(TMAG3001writeToSingleRegister(chipAddr,DEVICE_CONFIG_1_ADDRESS,&input))  return(true); 
    #asm nop #endasm
    return(false);
}        
/*###############################################################################################################################
# 使能CRC校验                                                                                                                   #
###############################################################################################################################*/      
bool TMAG3001enableCRC(uint8_t chipAddr) {
    uint8_t input;
//##(0)读取出当前数据
    if(TMAG3001readSingleRegister(chipAddr,DEVICE_CONFIG_1_ADDRESS, &input))  return(true);
//##(0)配置CRC使能位
    input &= ~(DEVICE_CONFIG_1_CRC_EN_MASK);
    input |= DEVICE_CONFIG_1_CRC_EN_Enabled;
//##(0)写入目标数据    
    if(TMAG3001writeToSingleRegister(chipAddr,DEVICE_CONFIG_1_ADDRESS,&input)) return(true); 
    #asm nop #endasm
    return(false);    
}   
/*###############################################################################################################################
# 禁止CRC校验                                                                                                                   #
###############################################################################################################################*/    
bool TMAG3001disableCRC(uint8_t chipAddr) {
    uint8_t input;
//##(0)读取出当前数
    if(TMAG3001readSingleRegister(chipAddr,DEVICE_CONFIG_1_ADDRESS, &input)) return(true);
//##(0)配置CRC使能位    
    input &= ~(DEVICE_CONFIG_1_CRC_EN_MASK);
    input |= DEVICE_CONFIG_1_CRC_EN_Disabled;
//##(0)写入目标数据    
    if(TMAG3001writeToSingleRegister(chipAddr,DEVICE_CONFIG_1_ADDRESS,&input)) return(true);  
    #asm nop #endasm 
    return(false);
}    
/*###############################################################################################################################
# 开启I2C干扰滤波器                                                                                                             #
###############################################################################################################################*/     
bool TMAG3001i2cGlitchFilterEnabled(uint8_t chipAddr) {
    uint8_t input;
//##(0)读取出当前数据
    if(TMAG3001readSingleRegister(chipAddr,DEVICE_CONFIG_2_ADDRESS, &input)) return(true);
//##(0)配置I2C干扰滤波器使能位 "0h = 干扰滤波器开启"
    input &= ~(DEVICE_CONFIG_2_I2C_GLITCH_FILTER_MASK);
    input |= DEVICE_CONFIG_2_I2C_GLITCH_FILTER_On;
//##(0)写入目标数据    
    if(TMAG3001writeToSingleRegister(chipAddr,DEVICE_CONFIG_2_ADDRESS,&input)) return(true);
    #asm nop #endasm 
    return(false);
}     
/*###############################################################################################################################
# 关闭I2C干扰滤波器                                                                                                             #
###############################################################################################################################*/    
bool TMAG3001i2cGlitchFilterDisabled(uint8_t chipAddr) {
    uint8_t input;
//##(0)读取出当前数据
    if(TMAG3001readSingleRegister(chipAddr,DEVICE_CONFIG_2_ADDRESS, &input)) return(true);
//##(0)配置I2C干扰滤波器使能位"1h = 干扰滤波器关闭" 
    input &= ~(DEVICE_CONFIG_2_I2C_GLITCH_FILTER_MASK);
    input |= DEVICE_CONFIG_2_I2C_GLITCH_FILTER_Off;
//##(0)写入目标数据    
    if(TMAG3001writeToSingleRegister(chipAddr,DEVICE_CONFIG_2_ADDRESS,&input)) return(true); 
    #asm nop #endasm 
    return(false);
}
/*###############################################################################################################################
# 进入待机模式                                                                                                                  #
###############################################################################################################################*/  
bool TMAG3001enterStandbyMode(uint8_t chipAddr) {
    uint8_t input;
//##(0)读取出当前数据
    if(TMAG3001readSingleRegister(chipAddr,DEVICE_CONFIG_2_ADDRESS, &input)) return(true);
//##(0)配置工作模式位"0h = 待机模式（ 在触发事件时开始新的转换）"
    input = (input & ~(DEVICE_CONFIG_2_OPERATING_MODE_MASK)) | DEVICE_CONFIG_2_OPERATING_MODE_Standby;
//##(0)写入目标数据    
    if(TMAG3001writeToSingleRegister(chipAddr,DEVICE_CONFIG_2_ADDRESS,&input)) return(true);  
    #asm nop #endasm 
    return(false);
}
/*###############################################################################################################################
# 进入连续测量模式（连续转换）                                                                                                  #
###############################################################################################################################*/
bool TMAG3001enterContinuousMeasureMode(uint8_t chipAddr) {
    uint8_t input;
//##(0)读取出当前数据
    if(TMAG3001readSingleRegister(chipAddr,DEVICE_CONFIG_2_ADDRESS, &input)) return(true);
//##(0)配置工作模式位"2h = 连续模式"    
    input = (input & ~(DEVICE_CONFIG_2_OPERATING_MODE_MASK)) | DEVICE_CONFIG_2_OPERATING_MODE_Continuous;
//##(0)写入目标数据    
    if(TMAG3001writeToSingleRegister(chipAddr,DEVICE_CONFIG_2_ADDRESS,&input)) return(true);    
    #asm nop #endasm 
    return(false);
}
/*###############################################################################################################################
# 进入睡眠模式                                                                                                                  #
# 注意：此功能必须是与设备的最后一次I2C通信,或者此设备将退出睡眠模式并进入待机模式                                              #
###############################################################################################################################*/
bool TMAG3001enterSleepMode(uint8_t chipAddr) {
    uint8_t input;
//##(0)读取出当前数据
    if(TMAG3001readSingleRegister(chipAddr,DEVICE_CONFIG_2_ADDRESS, &input)) return(true);
//##(0)配置工作模式位"1h = 睡眠模式" 
    input = (input & ~(DEVICE_CONFIG_2_OPERATING_MODE_MASK)) | DEVICE_CONFIG_2_OPERATING_MODE_Sleep;
//##(0)写入目标数据    
    if(TMAG3001writeToSingleRegister(chipAddr,DEVICE_CONFIG_2_ADDRESS,&input)) return(true);
    delay_us(100);  
    return(false);
}
/*###############################################################################################################################
# 进入唤醒和睡眠模式                                                                                                            #
# 不改变睡眠时间位                                                                                                              #
# 注意：此功能必须是与设备的最后一次I2C通信，或者此设备将退出唤醒和睡眠模式并进入待机模式                                       #
###############################################################################################################################*/
bool TMAG3001enterWakeUpAndSleepMode(uint8_t chipAddr) {
    uint8_t input;
//##(0)读取出当前数据
    if(TMAG3001readSingleRegister(chipAddr,DEVICE_CONFIG_2_ADDRESS, &input)) return(true);
//##(0)配置工作模式位"3h = 唤醒和睡眠模式（占空比模式） " 
    input = (input & ~(DEVICE_CONFIG_2_OPERATING_MODE_MASK)) | DEVICE_CONFIG_2_OPERATING_MODE_WakeupandSleep;
//##(0)写入目标数据    
    if(TMAG3001writeToSingleRegister(chipAddr,DEVICE_CONFIG_2_ADDRESS,&input)) return(true);    
    delay_us(100);
    return(false);
}
/*###############################################################################################################################
# 设置睡眠时间                                                                                                                  #
# 接收0x00到0x0C的输入，根据以下公式确定SLEEPTIME字段 , 不会更改操作模式，也不会启动唤醒和睡眠模式                              #
# SLEEPTIME决定设备转换之间在低功耗模式下花费的时间                                                                             #
# 在唤醒和睡眠模式下（操作模式=4h）                                                                                             #
#          SLEEPTIME bits  |  time between convs.                                                                               #
#         _________________|_______________________                                                                             #
#               0x00                   1ms                                                                                      #
#               0x01                   5ms                                                                                      #
#               0x02                  10ms                                                                                      #
#               0x03                  15ms                                                                                      #
#               0x04                  20ms                                                                                      #
#               0x05                  30ms                                                                                      #
#               0x06                  50ms                                                                                      #
#               0x07                 100ms                                                                                      #
#               0x08                 500ms                                                                                      #
#               0x09                1000ms                                                                                      #
#               0x0A                2000ms                                                                                      #
#               0x0B                5000ms                                                                                      #
#               0x0C               20000ms                                                                                      #
###############################################################################################################################*/
bool TMAG3001setSLEEPTIME(uint8_t chipAddr,uint8_t sleeptime) {
    uint8_t input;
//##(0)读取出当前数据
    if(TMAG3001readSingleRegister(chipAddr,SENSOR_CONFIG_1_ADDRESS,&input)) return(true);
//##(0)配置睡眠时间
    input = (input & ~(SENSOR_CONFIG_1_SLEEPTIME_MASK)) | (sleeptime);
//##(0)写入目标数据    
    if(TMAG3001writeToSingleRegister(chipAddr,SENSOR_CONFIG_1_ADDRESS,&input)) return(true);
//##(0)成功/完成则返回"false"
    #asm nop #endasm
    return(false);
}
/*###############################################################################################################################
# 设置睡眠时间的唤醒和睡眠模式                                                                                                  #
# 接受0x00到0x0F的输入，以根据数据表设置SLEEPTIME字段                                                                           #
# 注意：请参阅TMAG3001setSLEEPTIME（）函数以查看可能的睡眠时间值                                                                #
# 注意：此功能必须是与设备的最后一次I2C通信，或者此设备将退出唤醒和睡眠模式并进入待机模式                                       #
###############################################################################################################################*/
bool TMAG3001setWakeUpAndSleepMode(uint8_t chipAddr,uint8_t sleeptime) {
    
    if(TMAG3001setSLEEPTIME(chipAddr,sleeptime)==TRUE) return(true);
    #asm nop #endasm    
    if(TMAG3001enterWakeUpAndSleepMode(chipAddr)==TRUE) return(true);
    #asm nop #endasm
    return(false);
}
/*###############################################################################################################################
# 退出睡眠模式(进入待机模式)                                                                                                    #
# 通过将OPERATION_Mode字段设置为待机模式退出睡眠模式。                                                                          #
###############################################################################################################################*/
bool TMAG3001exitSleepMode(uint8_t chipAddr) {
    uint8_t input;
//##(0)读取出当前数据
    if(TMAG3001readSingleRegister(chipAddr,DEVICE_CONFIG_2_ADDRESS, &input)) return(true);
//##(0)配置工作模式位 
    input = (input & ~(DEVICE_CONFIG_2_OPERATING_MODE_MASK)) | DEVICE_CONFIG_2_OPERATING_MODE_Standby;
//##(0)写入目标数据    
    if(TMAG3001writeToSingleRegister(chipAddr,DEVICE_CONFIG_2_ADDRESS,&input)) return(true);
    delay_us(100);  
    return(false);
}
/*###############################################################################################################################
# 退出唤醒和睡眠模式                                                                                                            #
# 通过将OPERATION_Mode字段设置为待机模式，退出唤醒和睡眠模式。                                                                  #
###############################################################################################################################*/
bool TMAG3001exitWakeAndSleepMode(uint8_t chipAddr) {
    uint8_t input;
//##(0)读取出当前数据
    if(TMAG3001readSingleRegister(chipAddr,DEVICE_CONFIG_2_ADDRESS, &input)) return(true);
//##(0)配置工作模式位 
    input = (input & ~(DEVICE_CONFIG_2_OPERATING_MODE_MASK)) | DEVICE_CONFIG_2_OPERATING_MODE_Standby;
//##(0)写入目标数据    
    if(TMAG3001writeToSingleRegister(chipAddr,DEVICE_CONFIG_2_ADDRESS,&input)) return(true);
    delay_us(100);  
    return(false);    
}
/*###############################################################################################################################
# I2C到触发器转换（转换从 I2C 命令位开始）                                                                                      #
# 配置在I2C读或写命令上激活的转换触发器                                                                                         #
###############################################################################################################################*/
bool TMAG3001i2cTriggersConversion(uint8_t chipAddr)  {
    uint8_t input;
//##(0)读取出当前数据
    if(TMAG3001readSingleRegister(chipAddr,DEVICE_CONFIG_2_ADDRESS, &input)) return(true);
//##(0)配置触发位"0h = 转换从I2C命令位开始,默认设置"
    input &= ~(DEVICE_CONFIG_2_TRIGGER_MODE_MASK);
    input |= DEVICE_CONFIG_2_TRIGGER_MODE_I2CCommand;
//##(0)写入目标数据    
    if(TMAG3001writeToSingleRegister(chipAddr,DEVICE_CONFIG_2_ADDRESS,&input)) return(true);
    delay_us(100);  
    return(false);
}
/*###############################################################################################################################
# INT触发转换（转换通过 INT 引脚上的触发信号开始）                                                                              #
# 将转换触发器配置为在低脉冲至INT时激活。                                                                                       #                                                                                       
###############################################################################################################################*/
bool TMAG3001intTriggersConversion(uint8_t chipAddr)  {
    uint8_t input;
//##(0)读取出当前数据
    if(TMAG3001readSingleRegister(chipAddr,DEVICE_CONFIG_2_ADDRESS, &input)) return(true);
//##(0)配置触发位"1h = 转换通过 INT 引脚上的触发信号开始"
    input &= ~(DEVICE_CONFIG_2_TRIGGER_MODE_MASK);
    input |= DEVICE_CONFIG_2_TRIGGER_MODE_INTpin;
//##(0)写入目标数据    
    if(TMAG3001writeToSingleRegister(chipAddr,DEVICE_CONFIG_2_ADDRESS,&input)) return(true);
    delay_us(100);  
    return(false);
}
/*###############################################################################################################################
# 允许中断通过INT引脚发生                                                                                                       #
# 配置设备，以便在发生中断时，设备将通过INT引脚发出中断信号                                                                     #   
# i2c_busy-输入确定i2c总线繁忙时是否应发生中断                                                                                  #
# 0x00 = 通过INT中断                                                                                                            #
# 0x01 = 通过INT中断，忙碌时除外                                                                                                #
###############################################################################################################################*/
bool TMAG3001interruptThroughINT(uint8_t chipAddr,uint8_t i2c_busy) {
    uint8_t input;
//##(0)读取出当前数据
    if(TMAG3001readSingleRegister(chipAddr,INT_CONFIG_1_ADDRESS, &input)) return(true);
//##(0)配置中断模式选择位
    input &= ~(INT_CONFIG_1_INT_MODE_MASK);
    input |= INT_CONFIG_1_INT_MODE_None + (i2c_busy << 2);
//##(0)写入目标数据    
    if(TMAG3001writeToSingleRegister(chipAddr,INT_CONFIG_1_ADDRESS,&input)) return(true);
    #asm nop #endasm;  
    return(false);
}
/*###############################################################################################################################
# 允许通过SCL引脚发生中断                                                                                                       #
# 配置设备，以便在发生中断时，设备将通过SCL引脚发出固定宽度的中断信号（10us脉冲）                                               #
# i2c_busy-输入确定i2c总线繁忙时是否应发生中断                                                                                  #
# 0x00 = 通过SCL中断                                                                                                            #
# 0x01 = 通过SCL中断，繁忙时除外                                                                                                #
###############################################################################################################################*/
bool TMAG3001interruptThroughSCL(uint8_t chipAddr,uint8_t i2c_busy) {
    uint8_t input;
//##(0)读取出当前数据
    if(TMAG3001readSingleRegister(chipAddr,INT_CONFIG_1_ADDRESS, &input)) return(true);
//##(0)配置中断模式选择位
    input &= ~(INT_CONFIG_1_INT_MODE_MASK);
    input |= INT_CONFIG_1_INT_MODE_SCL + (i2c_busy << 2);
//##(0)写入目标数据    
    if(TMAG3001writeToSingleRegister(chipAddr,INT_CONFIG_1_ADDRESS,&input)) return(true);
    #asm nop #endasm;  
    return(false);
}
/*###############################################################################################################################
# 将INT引脚设置为锁定或脉冲                                                                                                     #
# 配置设备，以便当设备在INT引脚上输出低电平时                                                                                   #
# 它要么保持锁定状态，直到被初级清除，要么发送5us脉冲通过INT引脚。                                                              #
# int_state-确定中断应被锁存还是脉冲化的输入                                                                                    #
# 0x00 = 中断锁定，直到被主寻址设备清除                                                                                         #
# 0x01 = 中断脉冲5us                                                                                                            #
###############################################################################################################################*/
bool TMAG3001intPinLatchedPulsed(uint8_t chipAddr,uint8_t int_state)  {
    uint8_t input;
//##(0)读取出当前数据
    if(TMAG3001readSingleRegister(chipAddr,INT_CONFIG_1_ADDRESS, &input)) return(true);
//##(0)将INT_STATE设置为锁存/脉冲
    input &= ~(INT_CONFIG_1_INT_STATE_MASK);
    input |= INT_CONFIG_1_INT_STATE_Latch + (int_state << 5);
//##(0)写入目标数据    
    if(TMAG3001writeToSingleRegister(chipAddr,INT_CONFIG_1_ADDRESS,&input)) return(true);
    #asm nop #endasm;  
    return(false);
}
/*###############################################################################################################################
# 设置阈值检查的方向                                                                                                            #
# 配置设备，以便在外部设备启动时触发中断                                                                                        #
# 磁场高于/低于设定阈值。                                                                                                       #
# dir-用于选择阈值检查方向的输入                                                                                                #
# 0x00 = 设置高于阈值的外部字段的中断                                                                                           #
# 0x01 = 将外部字段的中断设置为低于阈值                                                                                         #
###############################################################################################################################*/
bool TMAG3001thrDirCheck(uint8_t chipAddr, uint8_t dir) {
    uint8_t input;
//##(0)读取出当前数据
    if(TMAG3001readSingleRegister(chipAddr,SENSOR_CONFIG_2_ADDRESS, &input)) return(true);
//##(0)选择阈值检查的方向(0h = 为高于阈值的外部磁场设置中断/1h = 为低于阈值的外部磁场设置中断)
    input &= ~(SENSOR_CONFIG_2_MAG_THR_DIR_MASK);
    input |= SENSOR_CONFIG_2_MAG_THR_DIR_Above + (dir << 5);
//##(0)写入目标数据    
    if(TMAG3001writeToSingleRegister(chipAddr,SENSOR_CONFIG_2_ADDRESS,&input)) return(true);
    #asm nop #endasm;  
    return(false);
}
/*###############################################################################################################################
# 转换完成时启用中断                                                                                                            #
# 配置设备，以便在完成磁性测量后设备将启用中断。                                                                                #
# 0x00 = 当配置的一组转换完成时中断不置为有效                                                                                   #
# 0x01 = 当配置的一组转换完成时中断置为有效                                                                                     #
###############################################################################################################################*/
bool TMAG3001enableResultReadyInterrupt(uint8_t chipAddr) {
    uint8_t input;
//##(0)读取出当前数据
    if(TMAG3001readSingleRegister(chipAddr,INT_CONFIG_1_ADDRESS, &input)) return(true);
//##(0)启用在转换完成时产生中断响应( 1h = 当配置的一组转换完成时中断置为有效 )
    input &= ~(INT_CONFIG_1_RSLT_INT_MASK);
    input |= INT_CONFIG_1_RSLT_INT_Enabled;
//##(0)写入目标数据    
    if(TMAG3001writeToSingleRegister(chipAddr,INT_CONFIG_1_ADDRESS,&input)) return(true);
    #asm nop #endasm;  
    return(false);    
}
/*###############################################################################################################################
# 启用在预定义的阈值交叉上产生中断响应                                                                                          #
# 配置设备，以便在完成磁性测量后设备将启用中断。                                                                                #
# 0x00 = 阈值交叉时中断不置为有效                                                                                               #
# 0x01 = 阈值交叉时中断置为有效                                                                                                 #
###############################################################################################################################*/
bool TMAG3001enableThresholds(uint8_t chipAddr) {
    uint8_t input;
//##(0)读取出当前数据
    if(TMAG3001readSingleRegister(chipAddr,INT_CONFIG_1_ADDRESS, &input)) return(true);
//##(0)启用在转换完成时产生中断响应( 1h = 当配置的一组转换完成时中断置为有效 )
    input &= ~(INT_CONFIG_1_THRSLD_INT_MASK);
    input |= INT_CONFIG_1_THRSLD_INT_Enabled;
//##(0)写入目标数据    
    if(TMAG3001writeToSingleRegister(chipAddr,INT_CONFIG_1_ADDRESS,&input)) return(true);
    #asm nop #endasm;  
    return(false);    
}
/*###############################################################################################################################
# 转换完成时禁用中断                                                                                                            #
# 配置设备，以便在完成磁性测量后设备将禁用中断。                                                                                #
###############################################################################################################################*/
bool TMAG3001disableResultReadyInterrupt(uint8_t chipAddr) {
    uint8_t input;
//##(0)读取出当前数据
    if(TMAG3001readSingleRegister(chipAddr,INT_CONFIG_1_ADDRESS, &input)) return(true);
//##(0)启用在转换完成时产生中断响应( 0h = 当配置的一组转换完成时中断不置为有效 )
    input &= ~(INT_CONFIG_1_RSLT_INT_MASK);
    input |= INT_CONFIG_1_RSLT_INT_Disabled;
//##(0)写入目标数据    
    if(TMAG3001writeToSingleRegister(chipAddr,INT_CONFIG_1_ADDRESS,&input)) return(true);
    #asm nop #endasm;  
    return(false);    
}
/*###############################################################################################################################
# 配置 TMAG3001开关触发中断模式                                                                                                 #
# 通过INT引脚启用开关模式，其中设备充当智能,切换并在超过阈值时断言中断。                                                        #
# switch_type-确定要启用的开关类型的输入                                                                                        #
# 0x00 = 单极                                                                                                                   #
# 0x01 = 全向                                                                                                                   #
# 注意：此模式覆盖任何中断功能，仅实现开关                                                                                      #
# 函数（禁用INT触发的转换）。                                                                                                   #
###############################################################################################################################*/
bool TMAG3001enableSwitchMode(uint8_t chipAddr,uint8_t switch_type) {
    uint8_t input;
//##(0)读取出当前数据
    if(TMAG3001readSingleRegister(chipAddr,INT_CONFIG_1_ADDRESS, &input)) return(true);
//##(0)中断模式选择( )
    input &= ~(INT_CONFIG_1_INT_MODE_MASK);
    input |= INT_CONFIG_1_INT_MODE_None + (switch_type << 2);
//##(0)写入目标数据    
    if(TMAG3001writeToSingleRegister(chipAddr,INT_CONFIG_1_ADDRESS,&input)) return(true);
    #asm nop #endasm;  
    return(false);    
}
/*###############################################################################################################################
# 禁用中断(模式)                                                                                                                #
# 通过将INT_MODE设置为无中断来禁用所有中断                                                                                      #
###############################################################################################################################*/
bool TMAG3001disableInterrupts(uint8_t chipAddr) {
    uint8_t input;
//##(0)读取出当前数据
    if(TMAG3001readSingleRegister(chipAddr,INT_CONFIG_1_ADDRESS, &input)) return(true);
//##(0)中断模式选择(设定为无中断模式)
    input &= ~(INT_CONFIG_1_INT_MODE_MASK);
    input |= INT_CONFIG_1_INT_MODE_None;
//##(0)写入目标数据    
    if(TMAG3001writeToSingleRegister(chipAddr,INT_CONFIG_1_ADDRESS,&input)) return(true);
    #asm nop #endasm;  
    return(false);    
}
/*###############################################################################################################################
# 启用INTB引脚                                                                                                                  #
# 0 = 启用 INT 引脚                                                                                                             #
# 1 = INT 引脚无法用作输入或输出                                                                                                #
###############################################################################################################################*/
bool TMAG3001enableIntbPin(uint8_t chipAddr) {
    uint8_t input;
//##(0)读取出当前数据
    if(TMAG3001readSingleRegister(chipAddr,INT_CONFIG_1_ADDRESS, &input)) return(true);
//##(0)INT 连接至 GND 时屏蔽 INT 引脚(启用 INT 引脚)
    input &= ~(INT_CONFIG_1_MASK_INTB_MASK);
    input |= INT_CONFIG_1_MASK_INTB_Enabled;
//##(0)写入目标数据    
    if(TMAG3001writeToSingleRegister(chipAddr,INT_CONFIG_1_ADDRESS,&input)) return(true);
    #asm nop #endasm;  
    return(false);    
}
/*###############################################################################################################################
# 禁用INTB引脚                                                                                                                  #
# 0 = 启用 INT 引脚                                                                                                             #
# 1 = INT 引脚无法用作输入或输出                                                                                                # 
###############################################################################################################################*/
bool TMAG3001disableIntbPin(uint8_t chipAddr) {
    uint8_t input;
//##(0)读取出当前数据
    if(TMAG3001readSingleRegister(chipAddr,INT_CONFIG_1_ADDRESS, &input)) return(true);
//##(0)INT 连接至 GND 时屏蔽 INT 引脚 (1h = INT 引脚无法用作输入或输出)
    input &= ~(INT_CONFIG_1_MASK_INTB_MASK);
    input |= INT_CONFIG_1_MASK_INTB_Disabled;
//##(0)写入目标数据    
    if(TMAG3001writeToSingleRegister(chipAddr,INT_CONFIG_1_ADDRESS,&input)) return(true);
    #asm nop #endasm;  
    return(false);    
}
/*###############################################################################################################################
# 选择角度滞后                                                                                                                  #
# 选择设备配置为用作时的角度滞后启用了角度阈值的开关                                                                            #
# angle_hys-设置启用角度阈值时的滞后                                                                                            #
# 0x00 = 1度                                                                                                                    #
# 0x01 = 2度                                                                                                                    #
# 0x02 = 4度                                                                                                                    #
# 0x03 = 8度                                                                                                                    #
###############################################################################################################################*/
bool TMAG3001setAngleHyst(uint8_t chipAddr, uint8_t angle_hys) {
    uint8_t input;
//##(0)读取出当前数据
    if(TMAG3001readSingleRegister(chipAddr,SENSOR_CONFIG_3_ADDRESS, &input)) return(true);
//##(0)将Angle_HYS字段设置为Angle_HYS
    input &= ~(SENSOR_CONFIG_3_ANG_HYS_MASK);
    input |= SENSOR_CONFIG_3_ANG_HYS_1deg | (angle_hys << 2);
//##(0)写入目标数据    
    if(TMAG3001writeToSingleRegister(chipAddr,SENSOR_CONFIG_3_ADDRESS,&input)) return(true);
    #asm nop #endasm;  
    return(false); 
}
/*###############################################################################################################################
# 启用改变角度唤醒                                                                                                              #
# 当任何测量到的磁性读数时，启用中断响应与ANGLE_HYST之前的测量值不同。在此模式下，设备将在检测到角度变化后提供中断响应测量。    #
# angle_hyst-设置启用角度阈值时的滞后                                                                                           #
# 0x00 = 1度                                                                                                                    #
# 0x01 = 2度                                                                                                                    #
# 0x02 = 4度                                                                                                                    #
# 0x03 = 8度                                                                                                                    #
###############################################################################################################################*/
bool TMAG3001enableWakeOnAngleChange(uint8_t chipAddr,uint8_t angle_hyst) {
    uint8_t input;
//##(0)选择角度滞后
    if(TMAG3001setAngleHyst(chipAddr,angle_hyst) == true)  return(true);
    #asm nop #endasm;
//##(0)读取出当前数据
    if(TMAG3001readSingleRegister(chipAddr,SENSOR_CONFIG_3_ADDRESS, &input)) return(true);
//##(0)1h = 在相对于先前的角度测量值发生变化时唤醒。 
    input &= ~(SENSOR_CONFIG_3_WOC_SEL_MASK);
    input |= SENSOR_CONFIG_3_WOC_SEL_Angle;
//##(0)写入目标数据    
    if(TMAG3001writeToSingleRegister(chipAddr,SENSOR_CONFIG_3_ADDRESS,&input)) return(true);
    #asm nop #endasm;  
    return(false); 
}
/*###############################################################################################################################
# 使能磁场变化唤醒功能                                                                                                          #
# 当任意一个测量的磁场读数与之前的测量值相差超过 THR_HYST（阈值滞后）时，触发中断响应。在此模式下，                             #
# 设备在检测到磁场变化后会产生中断响应，可检测的轴（X 轴、Y 轴或 Z 轴）由 MAG_CH_EN（磁场通道使能）配置决定。                   #
# thr_hyst（阈值滞后参数） - 为中断功能选择阈值，具体对应关系如下：                                                             #
# 0x00 = 阈值为   2 个 LSB, 分辨率 12 位                                                                                        #
# 0x01 = 阈值为   4 个 LSB，分辨率 12 位                                                                                        #
# 0x02 = 阈值为   8 个 LSB，分辨率 12 位                                                                                        #
# 0x03 = 阈值为  16 个 LSB，分辨率 12 位                                                                                        #
# 0x04 = 阈值为  32 个 LSB，分辨率 12 位                                                                                        #
# 0x05 = 阈值为  64 个 LSB，分辨率 12 位                                                                                        #
# 0x06 = 阈值为 128 个 LSB，分辨率 12 位                                                                                        #
# 0x07 = 阈值为 256 个 LSB，分辨率 12 位                                                                                        #
###############################################################################################################################*/
bool TMAG3001enableWakeOnFieldChange(uint8_t chipAddr) {
    uint8_t input;
//##(0)读取出当前数据
    if(TMAG3001readSingleRegister(chipAddr,SENSOR_CONFIG_3_ADDRESS, &input)) return(true);
//##(0) 2h = 单轴先前磁场测量值变化时唤醒
    input &= ~(SENSOR_CONFIG_3_WOC_SEL_MASK);
    input |= SENSOR_CONFIG_3_WOC_SEL_MagneticField;
//##(0)写入目标数据    
    if(TMAG3001writeToSingleRegister(chipAddr,SENSOR_CONFIG_3_ADDRESS,&input)) return(true);
    #asm nop #endasm;  
    return(false); 
}
/*###############################################################################################################################
# 禁用更改时唤醒                                                                                                                #
###############################################################################################################################*/
bool TMAG3001disableWakeOnChange(uint8_t chipAddr) {
    uint8_t input;
//##(0)读取出当前数据
    if(TMAG3001readSingleRegister(chipAddr,SENSOR_CONFIG_3_ADDRESS, &input)) return(true);
//##(0) 0h = 禁用变化时唤醒
    input &= ~(SENSOR_CONFIG_3_WOC_SEL_MASK);
    input |= SENSOR_CONFIG_3_WOC_SEL_Disabled;
//##(0)写入目标数据    
    if(TMAG3001writeToSingleRegister(chipAddr,SENSOR_CONFIG_3_ADDRESS,&input)) return(true);
    #asm nop #endasm;  
    return(false); 
}
/*###############################################################################################################################
# 配置 TMAG3001角度阈值检测功能，开启阈值超限中断，设置参考角、角度带宽、角度偏移参数。                                         #
# 将阈值 1（Threshold1）、阈值 2（Threshold2）和阈值 3（Threshold3）的功能用途分别设置为角度参考阈值（A_THR_REF）、             #
# 角度带宽阈值（A_THR_BAND）和角度偏移量（ANGLE_OFFSET）。                                                                      #
#                                                                                                                               #
# angle_offset_en（角度偏移量使能位） - 使能时，将偏移量添加到最终角度值中，具体配置如下：                                      #
# 0x00 = 不将 Angle_Offset [7:0] 寄存器的值添加到最终角度结果中                                                                 #
# 0x01 = 将 Angle_Offset [7:0] 寄存器的值添加到最终角度结果中                                                                   #
#                                                                                                                               #
# angle_offset_dir（角度偏移方向位） - 指示对 Angle_Offset 寄存器中的偏移量执行加法或减法操作，具体配置如下：                   #
# 0x00 = 将 Angle_Offset [7:0] 寄存器的值与最终角度结果相加                                                                     #
# 0x01 = 从最终角度结果中减去 Angle_Offset [7:0] 寄存器的值                                                                     #
#                                                                                                                               #
#   angle_ref（角度参考阈值）  - 8 位数据，分辨率为 2 度，最大范围覆盖 360 度，用作角度检测的参考阈值                           #
#                                                                                                                               #
#   angle_band（角度带宽阈值） - 8 位数据，分辨率为 1 度，最大范围可达 180 度，用作角度检测的带宽阈值                           #
#                                                                                                                               #
# angle_offset（角度偏移量）- 8 位数据，分辨率为 1 度/LSB,可实现 - 128~255 度范围内的角度偏移修正，用作角度值的偏移补偿参数     #
###############################################################################################################################*/
bool TMAG3001setAngleThreshold(uint8_t chipAddr,uint8_t angle_offest_en, uint8_t angle_offset_dir, uint8_t angle_ref, uint8_t angle_band, uint8_t angle_offset) {
    uint8_t input;
//##(0)设置THR_SEL字段以选择角度阈值    
    if(TMAG3001readSingleRegister(chipAddr,SENSOR_CONFIG_3_ADDRESS, &input)) return(true);
    input &= ~(SENSOR_CONFIG_3_THR_SEL_MASK) & ~(SENSOR_CONFIG_3_ANG_OFFSET_EN_MASK) & ~(SENSOR_CONFIG_3_ANG_OFFSET_DIR_MASK);
    input |= SENSOR_CONFIG_3_THR_SEL_Angle | (angle_offest_en << 1) | (angle_offset_dir);
    if(TMAG3001writeToSingleRegister(chipAddr,SENSOR_CONFIG_3_ADDRESS,&input)) return(true);   
//##(0)设置THRSLD_INT字段以在超过阈值时断言中断（1h）
    if(TMAG3001readSingleRegister(chipAddr,INT_CONFIG_1_ADDRESS, &input)) return(true);
    input &= ~(INT_CONFIG_1_THRSLD_INT_MASK);
    input |= INT_CONFIG_1_THRSLD_INT_Enabled;
    if(TMAG3001writeToSingleRegister(chipAddr,INT_CONFIG_1_ADDRESS,&input)) return(true);
//##(0)设定阈值参数
    if(TMAG3001writeToSingleRegister(chipAddr,THR_CONFIG_1_ADDRESS,&angle_ref))    return(true);
    if(TMAG3001writeToSingleRegister(chipAddr,THR_CONFIG_2_ADDRESS,&angle_band))   return(true);
    if(TMAG3001writeToSingleRegister(chipAddr,THR_CONFIG_3_ADDRESS,&angle_offset)) return(true);   
//##(0)操作成功     
    #asm nop #endasm;  
    return(false);   
}
/*###############################################################################################################################
# 选择阈值滞后                                                                                                                  #
# 选择设备配置时的阈值滞后                                                                                                      #
# 充当启用B字段阈值的开关                                                                                                       #
# thr_hyst-选择中断函数的阈值                                                                                                   #
# 0x00 = 阈值的2 LSB，12位分辨率                                                                                                #
# 0x01 =   4 LSB阈值，12位分辨率                                                                                                #
# 0x02 =   8 LSB阈值，12位分辨率                                                                                                #
# 0x03 =  16 LSB阈值，12位分辨率                                                                                                #
# 0x04 =  32 LSB阈值，12位分辨率                                                                                                #
# 0x05 =  64 LSB阈值，12位分辨率                                                                                                #
# 0x06 = 128 LSB阈值，12位分辨率                                                                                                #
# 0x07 = 256 LSB阈值，12位分辨率                                                                                                #
###############################################################################################################################*/
bool TMAG3001setThrHyst(uint8_t chipAddr,uint8_t thr_hys) {
    uint8_t input;
//##(0)读取出当前数据
    if(TMAG3001readSingleRegister(chipAddr,DEVICE_CONFIG_2_ADDRESS, &input)) return(true);
//##(0)配置阈值
    input &= ~(DEVICE_CONFIG_2_THR_HYST_MASK);
    input |= DEVICE_CONFIG_2_THR_HYST_2LSB + (thr_hys << 5);
//##(0)写入目标数据    
    if(TMAG3001writeToSingleRegister(chipAddr,DEVICE_CONFIG_2_ADDRESS,&input)) return(true);
    #asm nop #endasm;  
    return(false); 
}
/*###############################################################################################################################
//! 选择磁场阈值功能                                                                                                            #
//!                                                                                                                             #
//! 将阈值 1（Threshold1）、阈值 2（Threshold2）、阈值 3（Threshold3）的功能分别设置为 X 轴低阈值（X_THR_LO）、                 #
//! Y 轴低阈值（Y_THR_LO）、Z 轴低阈值（Z_THR_LO）,同时将 X 轴高阈值增益（Gain_X_THR_HI）、Y 轴高阈值偏移 1（Offset1_Y_THR_HI） #
//! Z 轴高阈值偏移 2（Offset2_Z_THR_HI）的功能分别设置为 X 轴高阈值（X_THR_HI）、Y 轴高阈值（Y_THR_HI）、X 轴高阈值（X_THR_HI） #
//!                                                                                                                             #
//! x_thr_lo - 8 位二进制补码，为 X 轴的低阈值                                                                                  #
//!                                                                                                                             #
//! x_thr_hi - 8 位二进制补码，为 X 轴的高阈值                                                                                  #
//!                                                                                                                             #
//! y_thr_lo - 8 位二进制补码，为 Y 轴的低阈值                                                                                  #
//!                                                                                                                             #
//! y_thr_hi - 8 位二进制补码，为 Y 轴的高阈值                                                                                  #
//!                                                                                                                             #
//! z_thr_lo - 8 位二进制补码，为 Z 轴的低阈值                                                                                  #
//!                                                                                                                             #
//! z_thr_hi - 8 位二进制补码，为 Z 轴的高阈值                                                                                  #
//!                                                                                                                             #
//! 注意：低阈值不得大于高阈值，否则将不执行阈值比较操作。                                                                      #
//! 注意：必须将角度使能位（ANGLE_EN）设置为 0h，才能禁用磁场增益，并使 0x09 至 0x0B 寄存器被解读为各磁场通道的高阈值。         #
###############################################################################################################################*/
bool TMAG3001setFieldThreshold(uint8_t chipAddr,uint8_t x_thr_lo, uint8_t x_thr_hi, uint8_t y_thr_lo, uint8_t y_thr_hi, uint8_t z_thr_lo, uint8_t z_thr_hi) {
    uint8_t input;
//##(0)设置 THR_Config_1  / THR_Config_2 / THR_Config_3 寄存器的功能 (2h = 选择了 B 场阈值）  
    if(TMAG3001readSingleRegister(chipAddr,SENSOR_CONFIG_3_ADDRESS, &input)) return(true);
    input &= ~(SENSOR_CONFIG_3_THR_SEL_MASK);
    input |= SENSOR_CONFIG_3_THR_SEL_BField;
    if(TMAG3001writeToSingleRegister(chipAddr,SENSOR_CONFIG_3_ADDRESS,&input)) return(true);   
//##(0)启用在预定义的阈值交叉上产生中断响应 (1h = 阈值交叉时中断置为有效) 
    if(TMAG3001readSingleRegister(chipAddr,INT_CONFIG_1_ADDRESS, &input)) return(true);
    input &= ~(INT_CONFIG_1_THRSLD_INT_MASK);
    input |= INT_CONFIG_1_THRSLD_INT_Enabled;
    if(TMAG3001writeToSingleRegister(chipAddr,INT_CONFIG_1_ADDRESS,&input)) return(true);   
//##(0)禁用两个选定磁通道之间的角度计算/磁增益和偏移校正( 0h = 无角度计算 )   
    if(TMAG3001readSingleRegister(chipAddr,SENSOR_CONFIG_2_ADDRESS, &input)) return(true);
    input &= ~(SENSOR_CONFIG_2_ANGLE_EN_MASK);
    input |= SENSOR_CONFIG_2_ANGLE_EN_Disabled;
    if(TMAG3001writeToSingleRegister(chipAddr,SENSOR_CONFIG_2_ADDRESS,&input)) return(true);   
//##(0)设置阈值参数
    if(TMAG3001writeToSingleRegister(chipAddr,THR_CONFIG_1_ADDRESS,&x_thr_lo))    return(true);
    if(TMAG3001writeToSingleRegister(chipAddr,THR_CONFIG_2_ADDRESS,&y_thr_lo))    return(true);
    if(TMAG3001writeToSingleRegister(chipAddr,THR_CONFIG_3_ADDRESS,&z_thr_lo))    return(true);          
    if(TMAG3001writeToSingleRegister(chipAddr,SENSOR_CONFIG_4_ADDRESS,&x_thr_hi)) return(true);
    if(TMAG3001writeToSingleRegister(chipAddr,SENSOR_CONFIG_5_ADDRESS,&y_thr_hi)) return(true);
    if(TMAG3001writeToSingleRegister(chipAddr,SENSOR_CONFIG_6_ADDRESS,&z_thr_hi)) return(true);   
//##(0)操作成功
    #asm nop #endasm;
    return(false); 
}
/*###############################################################################################################################
//! 选择幅值阈值功能                                                                                                            #
//! 将阈值1和阈值2的功能设置为M_THR_LO和M_THR_HI，                                                                              #
//!                                                                                                                             #
//! m_thr_lo - 设置幅度检查的下限阈值。适用于8位数值,阈值条目的可能范围为0至255                                                 #
//!                                                                                                                             #
//! m_thr_hi - 设置幅值检查的高阈值限制。8位数值,门槛条目的可能取值范围为0至255                                                 #
//!                                                                                                                             #
//! 注意：下限阈值的值不能高于上限阈值,否则,将不进行阈值+比较。                                                                  #
###############################################################################################################################*/
bool TMAG3001setMagnitudeThreshold(uint8_t chipAddr,uint8_t m_thr_lo, uint8_t m_thr_hi){
    uint8_t input;
//##(0) 将THR_SEL字段设置为选择磁阈值（3h） 3h = 选择了幅度阈值（ 按钮按压）。   
    if(TMAG3001readSingleRegister(chipAddr,SENSOR_CONFIG_3_ADDRESS, &input)) return(true);
    input &= ~(SENSOR_CONFIG_3_THR_SEL_MASK);
    input |= SENSOR_CONFIG_3_THR_SEL_Magnitude;
    if(TMAG3001writeToSingleRegister(chipAddr,SENSOR_CONFIG_3_ADDRESS,&input)) return(true);      
//##(0)将THRSLD_INT字段设置为当阈值被跨越时触发中断（1h）    
    if(TMAG3001readSingleRegister(chipAddr,INT_CONFIG_1_ADDRESS, &input)) return(true);
    input &= ~(INT_CONFIG_1_THRSLD_INT_MASK);
    input |= INT_CONFIG_1_THRSLD_INT_Enabled;
    if(TMAG3001writeToSingleRegister(chipAddr,INT_CONFIG_1_ADDRESS,&input)) return(true);  
//##(0)设置阈值数据
    if(TMAG3001writeToSingleRegister(chipAddr,THR_CONFIG_1_ADDRESS,&m_thr_lo))    return(true);
    if(TMAG3001writeToSingleRegister(chipAddr,THR_CONFIG_2_ADDRESS,&m_thr_hi))    return(true);
//##(0)操作成功
    #asm nop #endasm;
    return(false);     
}
/*###############################################################################################################################
# 禁用阈值功能                                                                                                                  #
###############################################################################################################################*/
bool TMAG3001disableThresholds(uint8_t chipAddr) {
    uint8_t input;
//##(0)设置THR_SEL字段以禁用阈值选择（0h）
    if(TMAG3001readSingleRegister(chipAddr,SENSOR_CONFIG_3_ADDRESS, &input)) return(true);
    input &= ~(SENSOR_CONFIG_3_THR_SEL_MASK);
    input |= SENSOR_CONFIG_3_THR_SEL_None;
    if(TMAG3001writeToSingleRegister(chipAddr,SENSOR_CONFIG_3_ADDRESS,&input)) return(true);
//##(0)设置THRSLD_INT字段以在超过阈值时禁用中断（0h）    
    if(TMAG3001readSingleRegister(chipAddr,INT_CONFIG_1_ADDRESS, &input)) return(true);
    input &= ~(INT_CONFIG_1_THRSLD_INT_MASK);
    input |= INT_CONFIG_1_THRSLD_INT_Disabled;
    if(TMAG3001writeToSingleRegister(chipAddr,INT_CONFIG_1_ADDRESS,&input)) return(true);
//##(0)操作成功
    #asm nop #endasm;
    #asm nop #endasm;
    return(false);    
}
/*###############################################################################################################################
//！设置磁铁的温度系数                                                                                                          #
//!                                                                                                                             #
//！temp_coefficient-磁体的温度系数                                                                                             #
//！0x00 = 0%（电流传感器应用）                                                                                                 #
//！0x01 = 0.12%/摄氏度（NdBFe）                                                                                                #
//！0x02 = 0.03%/摄氏度（SmCo）                                                                                                 #
//！0x03 = 0.2% /摄氏度（陶瓷）                                                                                                 #
###############################################################################################################################*/
bool TMAG3001setTempCoefficient(uint8_t chipAddr,uint8_t temp_coefficient) {
    uint8_t input;
//##(0)将MAG_TEMPCO设置为temp_coffect(先读取需要求该的值-->修改需要的值--->写入新值)
    if(TMAG3001readSingleRegister(chipAddr,DEVICE_CONFIG_1_ADDRESS, &input)) return(true);
    input &= ~(DEVICE_CONFIG_1_MAG_TEMPCO_MASK);
    input |= DEVICE_CONFIG_1_MAG_TEMPCO_None + (temp_coefficient << 5);
    if(TMAG3001writeToSingleRegister(chipAddr,DEVICE_CONFIG_1_ADDRESS,&input)) return(true);
//##(0)操作成功
    #asm nop #endasm;
    #asm nop #endasm;
    return(false);  
}
/*###############################################################################################################################
//！设置采样率（配置额外采样量以降低噪声/提高分辨率）                                                                           #
//!                                                                                                                             #
//！0x00-1x  10.0Ksps  22Ksps                                                                                                   #
//！0x01-2x  5.7Ksps 14.3Ksps                                                                                                   #
//！0x02-4x  3.1Ksps  8.3Ksps                                                                                                   #
//！0x03-8x  1.6Ksps  4.5Ksps                                                                                                   #
//！0x04-16x 0.8Ksps  2.4Ksps                                                                                                   #
//！0x05-32x 0.4Ksps  1.2Ksps                                                                                                   #
###############################################################################################################################*/
bool TMAG3001setSampleRate(uint8_t chipAddr,uint8_t CONV_AVG_bits){
    uint8_t input;
//##(0)将CONV_AVG设置为CONV_AVG_bits(先读取需要求该的值-->修改需要的值--->写入新值)
    if(TMAG3001readSingleRegister(chipAddr,DEVICE_CONFIG_1_ADDRESS, &input)) return(true);
    input &= ~(DEVICE_CONFIG_1_CONV_AVG_MASK);
    input |= DEVICE_CONFIG_1_CONV_AVG_1xAverage + (CONV_AVG_bits << 2);
    if(TMAG3001writeToSingleRegister(chipAddr,DEVICE_CONFIG_1_ADDRESS,&input)) return(true);
//##(0)操作成功
    #asm nop #endasm;
    return(false);  
}
/*###############################################################################################################################
//! 启用磁轴以进行测量（亦可关闭所有通道）                                                                                      #
//!                                                                                                                             #
//! 接收一个4位数值，用于配置MAG_CH_EN字段                                                                                      #
//!                                                                                                                             #
//!      mag_ch_en_bits（磁通道使能位）| 启用的通道 || mag_ch_en_bits（磁通道使能位）| 启用的通道                               #
//!                                    | + 采样顺序 ||                               | + 采样顺序                               #
//!     _______________________________|____________||_______________________________|_____________________________             #
//!           0x00               无通道启用      ||       0x08           XYX（采样顺序）                                        #
//!           0x01               X轴             ||       0x09           YXY（采样顺序）                                        #
//!           0x02               Y轴             ||       0x0A           YZY（采样顺序）                                        #
//!           0x03               X轴、Y轴        ||       0x0B           XZX（采样顺序）                                        #
//!           0x04               Z轴             ||       0x0C           XYZ正向诊断偏移                                        #
//!           0x05               Z轴、X轴        ||       0x0D           XYZ负向诊断偏移                                        #
//!           0x06               Y轴、Z轴        ||       0x0E           霍尔电阻与ADC检测                                      #
//!           0x07               X轴、Y轴、Z轴   ||       0x0F           霍尔偏移与AFE检测                                      #
###############################################################################################################################*/
bool TMAG3001enableMagChannels(uint8_t chipAddr,uint8_t mag_ch_en_bits) {
    uint8_t input;
//##(0)将MAG ch en设置为MAG ch en位(先读取需要求该的值-->修改需要的值--->写入新值)
    if(TMAG3001readSingleRegister(chipAddr,SENSOR_CONFIG_1_ADDRESS, &input)) return(true);
    input &= ~(SENSOR_CONFIG_1_MAG_CH_EN_MASK);
    input |=  SENSOR_CONFIG_1_MAG_CH_EN_Off + (mag_ch_en_bits << 4);
    if(TMAG3001writeToSingleRegister(chipAddr,SENSOR_CONFIG_1_ADDRESS,&input)) return(true);
//##(0)操作成功
    #asm nop #endasm;
    #asm nop #endasm;
    return(false);  
}
/*###############################################################################################################################
//！设置温度均值计算                                                                                                            #
//!                                                                                                                             #
//！temp_avg-温度平均值                                                                                                         #
//！0x00 = 如果MAG_CH_EN>0，则进行单次温度转换                                                                                  #
//！0x01 = 按卷积_AVG[2:0]进行滤波                                                                                              #
###############################################################################################################################*/
bool TMAG3001setTemperatureAveraging(uint8_t chipAddr,uint8_t temp_avg) {
    uint8_t input;
//##(0)将T_RATE设置为temp_avg(先读取需要求该的值-->修改需要的值--->写入新值)
    if(TMAG3001readSingleRegister(chipAddr,SENSOR_CONFIG_2_ADDRESS, &input)) return(true);
    input &= ~(SENSOR_CONFIG_2_T_RATE_MASK);
    input |= SENSOR_CONFIG_2_T_RATE_SingleTempConv + (temp_avg << 7);
    if(TMAG3001writeToSingleRegister(chipAddr,SENSOR_CONFIG_2_ADDRESS,&input)) return(true);
//##(0)操作成功
    #asm nop #endasm;
    #asm nop #endasm;
    return(false);  
}
/*###############################################################################################################################
//！启用角度测量（也可以关闭角度测量）                                                                                          #
//!                                                                                                                             #
//！启用角度计算、磁增益和偏移校正在两个选定的磁通道之间                                                                        #
//!                                                                                                                             #
//！根据ANGLE_EN设置，将使用第一个轴计算角度作为“水平”轴（轴的正侧为0度），第二个作为“垂直”轴（轴的正侧为90度）             #
//!                                                                                                                             #
//！angle_en_bits可以设置为0x00到0x03，以配置angle_en的这些设置：                                                               #
//！ANGLE_EN值|水平轴|垂直轴                                                                                                    #
//！0x00 none-none--（角度测量已禁用）                                                                                          #
//！0x01 X Y                                                                                                                    #
//！0x02 Y Z                                                                                                                    #
//！0x03 X Z                                                                                                                    #
###############################################################################################################################*/
bool TMAG3001enableAngleMeasurement(uint8_t chipAddr,uint8_t angle_en_bits) {
    uint8_t input;
//##(0)将ANGLE_EN设置为ANGLE_EN_bits(先读取需要求该的值-->修改需要的值--->写入新值)
    if(TMAG3001readSingleRegister(chipAddr,SENSOR_CONFIG_2_ADDRESS, &input)) return(true);
    input &= ~(SENSOR_CONFIG_2_ANGLE_EN_MASK);
    input |= SENSOR_CONFIG_2_ANGLE_EN_Disabled + (angle_en_bits << 2);
    if(TMAG3001writeToSingleRegister(chipAddr,SENSOR_CONFIG_2_ADDRESS,&input)) return(true);
//##(0)操作成功
    #asm nop #endasm;
    #asm nop #endasm;
    return(false);  
}
/*###############################################################################################################################
//！设置X、Y和Z轴的磁场范围                                                                                                     #
//!                                                                                                                             #
//！将SENSOR_CONFIG_2寄存器中的X、Y和Z_RANGE字段设置为位,由函数输入决定。                                                       #
//!                                                                                                                             #
//！xy_range_bits - x_y_range字段的位（必须不大于0x01）                                                                         #
//！z_range_bits - z_range字段的位   （必须不大于0x01）                                                                         #
//!                                                                                                                             #
//！根据使用的TMAG3001版本，比特的mT范围如下 ：                                                                                 #
//!                                                                                                                             #
//！*_range_bits |    TMAG3001A1  | TMAG3001A2                                                                                  #
//！    input    |     mT范围值   |   mT距离值                                                                                  #
//! _____________|________________|________________                                                                             #
//！   0x00      |      40 mT     |    120 mT                                                                                   #
//！   0x01      |      80 mT     |    240 mT                                                                                   #
###############################################################################################################################*/
bool TMAG3001setRanges(uint8_t chipAddr,uint8_t x_y_range_bits, uint8_t z_range_bits) {
    uint8_t input;
//##(0)将X_Y_RANGE设置为xy_RANGE_bits，将Z_RANGE设置为Z_RANGE_bits(先读取需要求该的值-->修改需要的值--->写入新值)
    if(TMAG3001readSingleRegister(chipAddr,SENSOR_CONFIG_2_ADDRESS, &input)) return(true);
    input &= ~(SENSOR_CONFIG_2_FULL_RANGE_MASK);
    input |= (x_y_range_bits << 1) | z_range_bits;
    if(TMAG3001writeToSingleRegister(chipAddr,SENSOR_CONFIG_2_ADDRESS,&input)) return(true);
//##(0)操作成功
    #asm nop #endasm;
    return(false);
}
/*###############################################################################################################################
//！选择低模式(在低有效电流模式和低噪声模式之间选择)                                                                            #
//!                                                                                                                             #
//！low_mode-在低有效电流和低噪声之间选择一种模式                                                                               #
//！0x00 = 低有效电流模式                                                                                                       #
//！0x01 = 低噪声模式                                                                                                           #
###############################################################################################################################*/
bool TMAG3001selectLowCurrentNoiseMode(uint8_t chipAddr,uint8_t low_mode) {
   uint8_t input;
//##(0)将LP_LN设置为低模式(先读取需要求该的值-->修改需要的值--->写入新值)
    if(TMAG3001readSingleRegister(chipAddr,DEVICE_CONFIG_2_ADDRESS, &input)) return(true);
    input &= ~(DEVICE_CONFIG_2_LP_LN_MASK);
    input |= DEVICE_CONFIG_2_LP_LN_LowCurrent + (low_mode << 4);
    if(TMAG3001writeToSingleRegister(chipAddr,DEVICE_CONFIG_2_ADDRESS,&input)) return(true);
//##(0)操作成功
    #asm nop #endasm;
    return(false);
}
/*###############################################################################################################################
//！设置磁增益                                                                                                                  #
//!                                                                                                                             #
//！根据8位输入值配置Sensor_Config_4（0x09）                                                                                    #
//!                                                                                                                             #
//！channel-选择幅度增益校正的轴                                                                                                #
//！0x00 - 第一通道                                                                                                             #
//！0x01 - 第二通道                                                                                                             #
//！gain_bits-用于调整所选轴值的8位增益值                                                                                       #
//！增益计算为（输入值/256）                                                                                                    #
###############################################################################################################################*/
bool TMAG3001setMagGainConfigIn8Bit(uint8_t chipAddr,uint8_t channel, uint8_t gain_bits) {
    uint8_t input;
//##(0)先读取需要求该的值-->修改需要的值--->写入新值
    if(TMAG3001readSingleRegister(chipAddr,SENSOR_CONFIG_2_ADDRESS, &input)) return(true);
    input &= ~(SENSOR_CONFIG_2_MAG_GAIN_CH_MASK);
    input |= SENSOR_CONFIG_2_MAG_GAIN_CH_1stChannel + (channel << 4);
    if(TMAG3001writeToSingleRegister(chipAddr,SENSOR_CONFIG_2_ADDRESS,&input)) return(true);    
//##(0)设置磁增益值    
    if(TMAG3001writeToSingleRegister(chipAddr,SENSOR_CONFIG_4_ADDRESS, &gain_bits)) return(true);
//##(0)操作成功
    #asm nop #endasm;
    return(false);    
}
/*###############################################################################################################################
//！使用十进制输入设置磁增益调整                                                                                                #
//!                                                                                                                             #
//！根据来自的十进制输入值配置Sensor_Config_4（0x09）                                                                           #
//！0到1（不包括）。请参阅第6.5.2.3节磁传感器增益校正                                                                           #
//！有关如何计算磁传感器增益的更多信息，请参阅数据表                                                                            #
//!                                                                                                                             #
//！channel-选择幅度增益校正的轴                                                                                                #
//！0x00-第一通道                                                                                                               #
//！0x01-第二通道                                                                                                               #
//！gain_value-基于0到1（不包括）的所需增益值的浮点输入                                                                         #
//！关闭公式，将分配“用户输入的十进制/256值”                                                                                  #
//！使用所选轴                                                                                                                  #
//!                                                                                                                             #
//！注意：变量gain_value应至少有3位有效数字，除非所需值的精确值小于3位有效数字。                                                #
###############################################################################################################################*/
bool TMAG3001setMagGainConfigInDecimal(uint8_t chipAddr,uint8_t channel, float gain_value) {
//##(0)将gain_value从浮点数转换为8位值
    uint8_t gain_bits = (uint8_t)(gain_value * 256);
//##(0)将GAIN_XTHRHI设置为GAIN_bits    
    return(TMAG3001setMagGainConfigIn8Bit(chipAddr, channel, gain_bits));
}
/*###############################################################################################################################
//！设置磁传感器偏移校正（8位输入）                                                                                             #
//!                                                                                                                             #
//！配置传感器CONFG_5（0x0A）和传感器CONFG_6（0x0B）                                                                            #
//！根据输入值                                                                                                                  #
//!                                                                                                                             #
//！请记住，应用offset1和offset2的轴取决于ANGLE_EN                                                                              #
//！ANGLE_EN值|偏移1轴|偏移2轴                                                                                                  #
//！0x00 无无                                                                                                                   #                                                                                               
//！0x01 X Y                                                                                                                    #
//！0x02 Y Z                                                                                                                    #
//！0x03 X Z                                                                                                                    #
//!                                                                                                                             #
//！offset1_bits-Offset_Config_1的8位设置                                                                                       #
//！offset2_bits-Offset_Config_2的8位设置                                                                                       #
//!                                                                                                                             #
//！MAG_OFFSET_CONFIG寄存器和实际偏移增量之间的转换在数据表上                                                                   #
###############################################################################################################################*/
bool TMAG3001setMagOffsetIn8Bit(uint8_t chipAddr,uint8_t offset1_bits, uint8_t offset2_bits) {
//##(0)将SENSOR_CONFIG_5和SENSOR_CONFIG_6分别设置为offset1_bits和offset2_bits
    if(TMAG3001writeToSingleRegister(chipAddr,SENSOR_CONFIG_5_ADDRESS, &offset1_bits)) return(true);
    #asm nop #endasm;
    if(TMAG3001writeToSingleRegister(chipAddr,SENSOR_CONFIG_6_ADDRESS, &offset2_bits)) return(true); 
//##(0)操作成功
    #asm nop #endasm;
    return(false);        
}
/*###############################################################################################################################
//! 设置磁传感器偏移校正（输入单位为毫特斯拉mT）                                                                                #
//!                                                                                                                             #
//! 根据输入值配置SENSOR_CONFIG_5（0x0A）和SENSOR_CONFIG_6（0x0B）寄存器                                                        #
//!                                                                                                                             #
//! 需注意，offset1和offset2所作用的轴由ANGLE_EN参数决定。                                                                      #
//! 注：ANGLE_EN参数必须为非零值！                                                                                              #
//!              ANGLE_EN参数值 | offset1对应轴 | offset2对应轴                                                                 #
//!                   0x00            无              无                                                                        #
//!                   0x01            X轴             Y轴                                                                       #
//!                   0x02            Y轴             Z轴                                                                       #
//!                   0x03            X轴             Z轴                                                                       #
//!                                                                                                                             #
//! offset1_delta - 所选offset1对应轴的偏移调整量（单位：mT）                                                                   #
//! offset2_delta - 所选offset2对应轴的偏移调整量（单位：mT）                                                                   #
//! （若某轴存在+2mT的误差，需在其偏移变量中输入-2mT的数值进行校正）                                                            #
//!                                                                                                                             #
//! 不同轴量程设置对应的有效偏移值范围：                                                                                        #
//!          轴量程设置       |  有效偏移值范围（mT）                                                                           #
//!            40 mT (A1)               -2.500 至 2.480                                                                         #
//!            80 mT (A1)               -5.000 至 4.961                                                                         #
//!           120 mT (A2)               -8.313 至 8.248                                                                         #
//!           240 mT (A2)              -16.625 至 16.495                                                                        #
//!                                                                                                                             #
//! （上述有效数值已向零取整至百分位，以避免范围中包含无效值；基于MAG_OFFSET_CONFIG寄存器的精确对应偏移值，                     #
###############################################################################################################################*/
bool TMAG3001setMagOffsetInmT(uint8_t chipAddr, float offset1_delta, float offset2_delta) {
    uint16_t delta1_range = 0;
    uint16_t delta2_range = 0;
      int8_t offset1_value = 0;
      int8_t offset2_value = 0;
     uint8_t offset1_bits = 0;  
     uint8_t offset2_bits = 0;
       float offset1_conv = 0;
       float offset2_conv = 0;
//##(0)获取 X 轴和 Y 轴 Z 轴磁场范围
    switch(TMAG3001getAngleEnValue(chipAddr)) {
        case ANGLE_EN_Disabled: 
             return(true);
        case ANGLE_EN_X1stY2nd:
             delta1_range = TMAG3001getXYrange(chipAddr);
             delta2_range = TMAG3001getXYrange(chipAddr);
             break;
        case ANGLE_EN_Y1stZ2nd:
             delta1_range = TMAG3001getXYrange(chipAddr); 
             delta2_range = TMAG3001getZrange(chipAddr);
             break;
        case ANGLE_EN_X1stZ2nd:
             delta1_range = TMAG3001getXYrange(chipAddr);
             delta2_range = TMAG3001getZrange(chipAddr);
             break;
    }
//##(0)获取 X 轴和 Y 轴磁测量范围的 LSB 量级
    switch(delta1_range) {
        case 40:  offset1_conv = VER_1_RANGE_0_OFFSET; break;
        case 80:  offset1_conv = VER_1_RANGE_1_OFFSET; break;
        case 120: offset1_conv = VER_2_RANGE_0_OFFSET; break;
        case 240: offset1_conv = VER_2_RANGE_1_OFFSET; break;
    }
//##(0)获取 Z 轴磁测量范围的 LSB 量级
    switch(delta2_range) {
        case 40:  offset2_conv = VER_1_RANGE_0_OFFSET; break;
        case 80:  offset2_conv = VER_1_RANGE_1_OFFSET; break;
        case 120: offset2_conv = VER_2_RANGE_0_OFFSET; break;
        case 240: offset2_conv = VER_2_RANGE_1_OFFSET; break;
    }
//##(0)计算出校正偏移量值
    offset1_value = (int8_t)(offset1_delta/offset1_conv); 
    offset2_value = (int8_t)(offset2_delta/offset2_conv);
//##(0)配置需要写入寄存器"SENSOR_CONFIG_5_ADDRESS"的值
    offset1_bits = ((uint8_t)offset1_value) & 0x7F ;                            //##(0)转为绝对值,即屏蔽符号位
    offset1_bits = offset1_bits | ((((uint16_t) offset1_value) & 0x100) >> 1);  //##(0)转换为无符号位的8位
//##(0)配置需要写入寄存器"SENSOR_CONFIG_6_ADDRESS"的值   
    offset2_bits = ((uint8_t) offset2_value) & 0x7F ;                           //##(0)转为绝对值,即屏蔽符号位
    offset2_bits = offset2_bits | ((((uint16_t) offset2_value) & 0x100) >> 1);  //##(0)转换为无符号位的8位
//##(0)写入寄存器"SENSOR_CONFIG_5_ADDRESS"/"SENSOR_CONFIG_6_ADDRESS"的值
    if(TMAG3001setMagOffsetIn8Bit(chipAddr, offset1_bits, offset2_bits)) return(true);    
//##(0)操作成功
    #asm nop #endasm;
    return(false);    
}
/*###############################################################################################################################
//！获取并返回 X_Result_MSB 寄存器的值（ 地址 = 12h）                                                                           #
###############################################################################################################################*/
uint8_t TMAG3001getXMSBresult(uint8_t chipAddr) {
    uint8_t result;
    TMAG3001readSingleRegister(chipAddr, X_RESULT_MSB_ADDRESS, &result);
    return(result);
}
/*###############################################################################################################################
//！获取并返回 X_Result_LSB 寄存器的值（ 地址 = 13h）                                                                           #
###############################################################################################################################*/
uint8_t TMAG3001getXLSBresult(uint8_t chipAddr) {
    uint8_t result;
    TMAG3001readSingleRegister(chipAddr, X_RESULT_LSB_ADDRESS, &result);
    return(result);
}
/*###############################################################################################################################
//！获取并返回 Y_Result_MSB 寄存器的值（ 地址 = 14h）                                                                           #
###############################################################################################################################*/
uint8_t TMAG3001getYMSBresult(uint8_t chipAddr) {
    uint8_t result;
    TMAG3001readSingleRegister(chipAddr, Y_RESULT_MSB_ADDRESS, &result);
    return(result);
}
/*###############################################################################################################################
//！获取并返回 Y_Result_LSB 寄存器的值（ 地址 = 15h）                                                                           #
###############################################################################################################################*/
uint8_t TMAG3001getYLSBresult(uint8_t chipAddr) {
    uint8_t result;
    TMAG3001readSingleRegister(chipAddr, Y_RESULT_LSB_ADDRESS, &result);
    return(result);
}
/*###############################################################################################################################
//！获取并返回 Z_Result_MSB 寄存器的值（ 地址 = 16h）                                                                           #
###############################################################################################################################*/
uint8_t TMAG3001getZMSBresult(uint8_t chipAddr) {
    uint8_t result;
    TMAG3001readSingleRegister(chipAddr, Z_RESULT_MSB_ADDRESS, &result);
    return(result);
}
/*###############################################################################################################################
//！获取并返回 Z_Result_LSB 寄存器的值（ 地址 = 16h）                                                                           #
###############################################################################################################################*/
uint8_t TMAG3001getZLSBresult(uint8_t chipAddr) {
    uint8_t result;
    TMAG3001readSingleRegister(chipAddr, Z_RESULT_LSB_ADDRESS, &result);
    return(result); 
}
/*###############################################################################################################################
//！获取并返回 Temp_Result_MSB 寄存器的值（ 地址 = 10h）                                                                        #
###############################################################################################################################*/
uint8_t TMAG3001getTempMSBresult(uint8_t chipAddr) {
    uint8_t result;
    TMAG3001readSingleRegister(chipAddr, TEMP_RESULT_MSB_ADDRESS, &result);
    return(result); 
}
/*###############################################################################################################################
//！获取并返回 Temp_Result_LSB 寄存器的值（ 地址 = 11h）                                                                        #
###############################################################################################################################*/
uint8_t TMAG3001getTempLSBresult(uint8_t chipAddr) {
    uint8_t result;
    TMAG3001readSingleRegister(chipAddr, TEMP_RESULT_LSB_ADDRESS, &result);
    return(result);
}
/*###############################################################################################################################
//！获取并返回 Angle_Result_MSB 寄存器的值（ 地址 = 19h）                                                                       #
###############################################################################################################################*/
uint8_t TMAG3001getAngleMSBresult(uint8_t chipAddr) {
    uint8_t result;
    TMAG3001readSingleRegister(chipAddr, ANGLE_RESULT_MSB_ADDRESS, &result);
    return(result);
}
/*###############################################################################################################################
//！获取并返回 Angle_Result_LSB 寄存器的值（ 地址 = 1Ah）                                                                       #
###############################################################################################################################*/
uint8_t TMAG3001getAngleLSBresult(uint8_t chipAddr) {
    uint8_t result;
    TMAG3001readSingleRegister(chipAddr, ANGLE_RESULT_LSB_ADDRESS, &result);
    return(result);
}
/*###############################################################################################################################
//！获取并返回 Magnitude_Result 寄存器的值（ 地址 = 1Bh）                                                                       #
###############################################################################################################################*/
uint8_t TMAG3001getMAGresult(uint8_t chipAddr) {
    uint8_t result;
    TMAG3001readSingleRegister(chipAddr, MAGNITUDE_RESULT_ADDRESS, &result);
    return(result);
}
/*###############################################################################################################################
//！获取磁性结果寄存器                                                                                                          #
//!                                                                                                                             #
//！接收一个大小为3的int16_t值数组，并将其赋值为                                                                                #
//！三个*_*SB_RESULT寄存器。（订购XYZ）                                                                                         #
//!                                                                                                                             #
//！输入数组的长度必须为 3                                                                                                      #
//!                                                                                                                             #
//！注意：get*结果函数返回的uint16_t变量是强制转换的                                                                            #
//！转换为int16_t变量，以便与其他提供的函数一起使用                                                                             #
//！有符号整数。                                                                                                                #
###############################################################################################################################*/
void TMAG3001getMagResultsRegisters(uint8_t chipAddr, int16_t meas_arr[]) {   
    meas_arr[0] = (((int16_t)TMAG3001getXMSBresult(chipAddr)) << 8) | ((int16_t)TMAG3001getXLSBresult(chipAddr));
    meas_arr[1] = (((int16_t)TMAG3001getYMSBresult(chipAddr)) << 8) | ((int16_t)TMAG3001getYLSBresult(chipAddr));
    meas_arr[2] = (((int16_t)TMAG3001getZMSBresult(chipAddr)) << 8) | ((int16_t)TMAG3001getZLSBresult(chipAddr)); 
}

/*###############################################################################################################################
//！以mT为单位获取X轴磁通量测量值                                                                                               #
//!                                                                                                                             #
//！返回一个浮点数，其中包含从X_MSP_RESULT和X_LSB_RESULT寄存器。                                                                #
###############################################################################################################################*/
float TMAG3001getMeasurementX(uint8_t chipAddr) {
    int16_t data;
//##(0)获取X轴的通量测量值  
    data = ((int16_t)TMAG3001getXMSBresult(chipAddr) << 8) | ((int16_t) TMAG3001getXLSBresult(chipAddr));                                                                                           
//##(0)返回计算后的磁通量(mT数值)
    return TMAG3001resultRegisterTomT(data, TMAG3001getXYrange(chipAddr));
}
/*###############################################################################################################################
//！以mT为单位获取Y轴磁通量测量值                                                                                               #
//!                                                                                                                             #
//！返回一个浮点数，其中包含从                                                                                                  #
//！Y_MSP_RESULT和Y_LSB_RESULT寄存器。                                                                                          #
###############################################################################################################################*/
float TMAG3001getMeasurementY(uint8_t chipAddr) {
    int16_t data;
//##(0)获取Y轴的通量测量值 
    data = ((int16_t) TMAG3001getYMSBresult(chipAddr) << 8) | ((int16_t) TMAG3001getYLSBresult(chipAddr)); 
//##(0)返回计算后的磁通量(mT数值)                                                                                          
    return TMAG3001resultRegisterTomT(data, TMAG3001getXYrange(chipAddr));
}
/*###############################################################################################################################
//！以mT为单位获取Y轴磁通量测量值                                                                                               #
//!                                                                                                                             #
//！返回一个浮点数，其中包含从                                                                                                  #
//！Z_MSP_RESULT和Z_LSB_RESULT寄存器。                                                                                          #
###############################################################################################################################*/
float TMAG3001getMeasurementZ(uint8_t chipAddr) {
    int16_t data;
//##(0)获取Y轴的通量测量值 
    data = ((int16_t) TMAG3001getZMSBresult(chipAddr) << 8) | ((int16_t) TMAG3001getZLSBresult(chipAddr)); 
//##(0)返回计算后的磁通量(mT数值)                                                                                          
    return TMAG3001resultRegisterTomT(data, TMAG3001getZrange(chipAddr));
}
/*###############################################################################################################################
//！获取以摄氏度为单位的温度测量值                                                                                              #
//!                                                                                                                             #
//！目前已设置设备的“典型”电气特性（ECHAR）,在头文件中。如果设备已经校准，并且ECHAR值不同                                     #
//！找到，请编辑头文件中的ECHAR值以获得更准确的结果                                                                             #
//！温度测量。头文件还包含有关ECHAR值的更多信息。                                                                               #
###############################################################################################################################*/
float TMAG3001getMeasurementTEMP(uint8_t chipAddr) {
    uint16_t tADC_T;
       float temp_val;       
//##(0)获取温度通道的测量值
    tADC_T = ((uint16_t) TMAG3001getTempMSBresult(chipAddr) << 8) | ((uint16_t) TMAG3001getTempLSBresult(chipAddr));
//##(0)转换为摄氏度温度值)
    temp_val = ECHAR_T_SENS_T0 + ((((float) tADC_T) - ECHAR_T_ADC_T0) / ECHAR_T_ADC_RES);
//##(0)返回结果  
    return temp_val;   
}
/*###############################################################################################################################
//！以度为单位获取内角测量值                                                                                                    #
//!                                                                                                                             #
//！返回一个浮点数，其中包含从ANGLE_RESULT寄存器转换的度数值 。                                                                 #                                  
//！该值对应于两个磁通轴产生的计算角度                                                                                          #
//！由ANGLE_EN位选择的测量值。                                                                                                  #
//!                                                                                                                             #
//！为了正确测量角度，angle_EN选择的两个轴必须共享                                                                              #
//！所选范围相同。                                                                                                              #
###############################################################################################################################*/
float TMAG3001getMeasurementANGLE(uint8_t chipAddr) {
    uint16_t data;
      float angle;
//##(0)获取角度的测量值            
    data = ((uint16_t) TMAG3001getAngleMSBresult(chipAddr) << 8) | ((uint16_t) TMAG3001getAngleLSBresult(chipAddr));
//##(0)计算出角度值,LSB 大小为0.0625°    
    angle = ((float)data * 0.0625);
//##(0)返回结果    
    return angle;
}
/*###############################################################################################################################
//！获取以mT为单位的内部震级测量值                                                                                              #
//!                                                                                                                             #
//！返回一个浮点数，其中包含从MAGNITUDE_RESULT寄存器转换的mT值。                                                                #
//！该值对应于两个磁通量轴产生的计算量                                                                                          #
//！由ANGLE_EN位选择的测量值 。                                                                                                 #                                                          
//!                                                                                                                             #
//！为了正确测量幅度，ANGLE_EN选择的两个轴必须共享                                                                              #
//！所选范围相同 。                                                                                                             #                                                                                          
###############################################################################################################################*/
float TMAG3001getMeasurementMAG(uint8_t chipAddr) {
    uint16_t data;
      float range = 0;
      float magnitude;
//##(0)获取幅度测量值
    data = TMAG3001getMAGresult(chipAddr);
//##(0)获取并返回轴的X_Y_RANGE位的整数值    
    switch(TMAG3001getXYrange(chipAddr)) {
        case 40  : range = VER_1_RANGE_0_MAGNITUDE; break;
        case 80  : range = VER_1_RANGE_1_MAGNITUDE; break;
        case 120 : range = VER_2_RANGE_0_MAGNITUDE; break;
        case 240 : range = VER_2_RANGE_1_MAGNITUDE; break;
    }
//##(0)计算出幅度值(mT)
    magnitude = ((float)data) * range;
//##(0)返回结果
    return magnitude;
}
/*###############################################################################################################################
//！以mT为单位获取磁性测量值XYZ                                                                                                 #
//!                                                                                                                             #
//！接收大小为3的浮点数组，并更新其对                                                                                           #
//！三个磁轴，单位为mT（XYZ顺序）                                                                                               #
//!                                                                                                                             #
//！输入数组的大小必须为3（或至少在范围内具有meas_arr到meas_arr+2）                                                             #
###############################################################################################################################*/
void TMAG3001getMagMeasurementXYZ(uint8_t chipAddr,float meas_arr[]) {
//##(0)计算出磁性数值,单位 mT    
    meas_arr[0] = TMAG3001getMeasurementX(chipAddr);      //##(0)X轴
    meas_arr[1] = TMAG3001getMeasurementY(chipAddr);      //##(0)Y轴
    meas_arr[2] = TMAG3001getMeasurementZ(chipAddr);      //##(0)Z轴
}
/*###############################################################################################################################
//！获取并返回轴的X_Y_RANGE位的整数值                                                                                           #
//!                                                                                                                             #
//！返回X轴范围的无符号16位整数值，单位为mT。                                                                                   #
###############################################################################################################################*/
uint16_t TMAG3001getXYrange(uint8_t chipAddr) {
    uint8_t config;
   uint16_t range;
//##(0)获取SENSOR_CONFIG_2并保留 X_Y_RANGE 位。    
    TMAG3001readSingleRegister(chipAddr,SENSOR_CONFIG_2_ADDRESS, &config);
    config = (config & SENSOR_CONFIG_2_X_Y_RANGE_MASK) >> 1;
//##(0)根据当前芯片版本返回 X 轴和 Y 轴磁场范围
    if(TMAG3001getVersion(chipAddr)==TMAG3001_40mT) {   
        range = (config==RANGE_80mTor240mT)? 80 : 40;       //##(0)芯片版本"TMAG3001A1"的范围值
    }else{
        range = (config==RANGE_80mTor240mT)? 240:120;       //##(0)芯片版本"TMAG3001A2"的范围值
    }
//##(0)操作成功
    #asm nop #endasm;
    return(range);
}
/*###############################################################################################################################
//！获取并返回轴的Z_RANGE位的整数值                                                                                             #
//!                                                                                                                             #
//！返回Z轴范围的无符号16位整数值，单位为mT。                                                                                   #
###############################################################################################################################*/
uint16_t TMAG3001getZrange(uint8_t chipAddr) {
    uint8_t config;
   uint16_t range;
//##(0)获取SENSOR_CONFIG_2并保留 X_Y_RANGE 位。    
    TMAG3001readSingleRegister(chipAddr,SENSOR_CONFIG_2_ADDRESS, &config);
    config = config & SENSOR_CONFIG_2_Z_RANGE_MASK;
//##(0)根据当前芯片版本返回 Z 轴磁场范围
    if(TMAG3001getVersion(chipAddr)==TMAG3001_40mT) { 
        range = (config==RANGE_80mTor240mT)? 80 : 40;       //##(0)芯片版本"TMAG3001A1"的范围值
    }else{
        range = (config==RANGE_80mTor240mT)? 240:120;       //##(0)芯片版本"TMAG3001A2"的范围值
    }
//##(0)操作成功
    #asm nop #endasm;
    return(range);
}
/*###############################################################################################################################
//！获取TMAG3001版本（A1或A2）                                                                                                  #
//!                                                                                                                             #
//！发送一个用于Contoso ID的读取命令，并返回VER字段位。                                                                         #
//！VER==0x00-->TMAG3001A1                                                                                                      #
//！VER==0x08-->TMAG3001A2                                                                                                      #
###############################################################################################################################*/
uint8_t TMAG3001getVersion(uint8_t chipAddr) {
    uint8_t version;
//##(0)读取寄存器"DEVICE_ID_ADDRESS"信息
    TMAG3001readSingleRegister(chipAddr,DEVICE_ID_ADDRESS, &version);
//##(0)保留Version[1:0]
    version = (version & DEVICE_ID_VER_MASK) >> 2;
//##(0)操作成功
    #asm nop #endasm;
    return(version);   
}
/*###############################################################################################################################
//！检查CRC是否已启用                                                                                                           #
//!                                                                                                                             #
//！发送TEST_CONFG的读取命令，并返回是否为CRC_DIS字段                                                                           #
//！是否对应启用的CRC。（1b==已启用）                                                                                           #
###############################################################################################################################*/
uint8_t TMAG3001isCRCenabled(uint8_t chipAddr) {
    uint8_t result;
    TMAG3001readSingleRegister(chipAddr, DEVICE_CONFIG_1_ADDRESS, &result);  
    result = (result & DEVICE_CONFIG_1_CRC_EN_MASK) >> 7;
    #asm nop #endasm;
    return(result);
}
/*###############################################################################################################################
# TMAG3001获取启用两个选定磁通道之间的角度计算、磁增益和偏移校正                                                                #
#                                                                                                                               #
# 0h = 无角度计算                                                                                                               #																												#
# 1h = X 第一, Y 第二                                                                                                           #															#
# 2h = Y 第一, Z 第二                                                                                                           #																#
# 3h = X 第一, Z 第二                                                                                                           #																#
###############################################################################################################################*/
uint8_t TMAG3001getAngleEnValue(uint8_t chipAddr) {
    uint8_t output;
//##(0)读取地址“SENSOR_CONFIG_2_ADDRESS”的值	
    if(TMAG3001readSingleRegister(chipAddr,SENSOR_CONFIG_2_ADDRESS, &output)) return(0x00);
//##(0)保留Angle_EN[1:0]
    output = (output & SENSOR_CONFIG_2_ANGLE_EN_MASK) >> 2; 
//##(0)操作成功
    #asm nop #endasm;
    return(output);  
}
/*###############################################################################################################################
//！计算32位无符号整数的整数平方根（向下取整）                                                                                  #
//! x = 输入的32位无符号整数                                                                                                    #
//！x 的整数平方根（满足 result < x < (result+1))                                                                               #
###############################################################################################################################*/
uint32_t isqrt32(uint32_t h)  {
    uint32_t  low = 1;              //##(0)查找下界
    uint32_t high = 0xFFFF;         //##(0)查找上界（优化：2^16=65536，因为65536??=2^32，是uint32_t的最大值+1）
    uint32_t result = 0;            //##(0)最终结果
    uint32_t mid;
//##(0)特殊情况：h = 0 或 h = 1,直接返回自身
    if(h == 0 || h == 1) { return(h); }
//##(0)计算平方根      
    while(low <= high) {
        mid = low + ((high - low) >> 1);    //##(0)计算中间值（等价于 (low + high) / 2，避免溢出）
        if(mid <= h / mid) {                //##(0)避免 mid*mid 溢出：用 x / mid 代替 mid*mid 与 x 比较
            result = mid;                   //##(0)mid ≤ x，记录当前mid为候选，尝试更大的值
            low  = mid + 1;
        } else {
            high = mid - 1;                 //##(0)mid > x，尝试更小的值
        }
    }
//##(0)返回计算结果    
    return(result);
}
/*###############################################################################################################################
//！将轴测量结果寄存器转换为mT值                                                                                                #
//!                                                                                                                             #
//！记录其中一个磁轴结果和范围                                                                                                  #
//！该特定轴，并计算寄存器表示的mT值 。                                                                                         #                                                                     
###############################################################################################################################*/
float TMAG3001resultRegisterTomT(int16_t register_bits, uint16_t range)  {
    float rangeConv = 0.0;
    switch(range) {
        case 40  : rangeConv = VER_1_RANGE_0_DATA; break;
        case 80  : rangeConv = VER_1_RANGE_1_DATA; break;
        case 120 : rangeConv = VER_2_RANGE_0_DATA; break;
        case 240 : rangeConv = VER_2_RANGE_1_DATA; break;
    }
    return((float) register_bits) * rangeConv;
}
/*###############################################################################################################################
//！将角度结果寄存器转换为度数值                                                                                                #
//!                                                                                                                             #
//！接收角度结果寄存器的位并将其转换为度值 。                                                                                   #                                                
###############################################################################################################################*/
float TMAG3001angleRegisterToDeg(uint16_t register_bits){
    return((float)register_bits*0.0625);
}
/*###############################################################################################################################
//！脉冲INT功能                                                                                                                 #
//!                                                                                                                             #
//！此功能在连接到TMAG3001 INT引脚的GPIO引脚上发出低脉冲                                                                        #
//！为2个us。（之后将引脚设置为HIGH）                                                                                           #
//!                                                                                                                             #
//！可用于触发trigger_MODE设置为“INT脉冲”的转换                                                                               #
//!                                                                                                                             #
//！注意：如果INT引脚初始化为输入引脚，则此函数将不起作用。INT引脚必须初始化为输出引脚 ！                                       #
###############################################################################################################################*/
void TMAG3001intPulse(uint8_t chipAddr) { 
//##(0) 第二个霍尔传感器地址(U17绑带传感器)    
    if(chipAddr == TMAG3001STRAP) {
        output_bit(SENSOR1_PIN,0); delay_us(5);
        output_bit(SENSOR1_PIN,1);
    }
//##(0)第一个霍尔传感器地址(U18折叠传感器)    
    if(chipAddr == TMAG3001FOLD) {
        output_bit(SENSOR2_PIN,0); delay_us(5);
        output_bit(SENSOR2_PIN,1);
    }  
}
/*###############################################################################################################################
//! 功能：读取单个寄存器，并**同时触发一次新的AD转换**                                                                          #
//!                                                                                                                             #
//! 输入：address - 要读取的寄存器地址 (0x00 ~ 0x1C)                                                                            #
//! 返回：读到的寄存器值                                                                                                        #
###############################################################################################################################*/
uint8_t TMAG3001readSingleRegisterWithTrigger(uint8_t chipAddr, uint8_t address) {
    uint8_t result; 
    
    if(TMAG3001readSingleRegister(chipAddr, address|0x80,&result)) return(1);
    #asm nop #endasm
    return(false);
}

/*********************************************************************
 * 函数名称：TMAG3001_Clear_Fold_Interrupt
 * 功能描述：清除折叠传感器角度中断标志
 ********************************************************************/
bool TMAG3001_Clear_Fold_Interrupt(uint8_t chipAddr) {   
//##(0)读取状态寄存器即可清除锁存中断  
    uint8_t status;
    return(TMAG3001readSingleRegister(chipAddr, DEVICE_STATUS_ADDRESS, &status));
}

/*###############################################################################################################################
# 函数名 :  void SensorFOLD_Process(void)                                                                                       #
# 功  能 :  判断折叠或者是展开                                                                                                  #
# 参  数 :  NONE                                                                                                                #
# 说  明 :  每100毫秒读取一次XYZ磁场／角度／幅度                                                                                #
###############################################################################################################################*/
void SensorFOLD_Process(void) {
    static uint16_t timeout;
    static float filter_total = 0.0f;       //##(0)滤波缓存变量，对总磁场做一阶低通滤波，消除采样抖动、干扰毛刺
           float currX, currY, currZ;       //##(0)存储三轴原始磁场分量（单位mT）
		   float Angle;						//##(0)角度值
		   float Magnitude;										//##(0)三轴磁场的合成幅值
           float totalMag;										//##(0)三轴合成总磁场强度模长
//##(0)100ms才执行一次采集判断   
    if((regs.time10ms-timeout)<100/10) return;      
    timeout = regs.time10ms;									//##(0)更新计时起点,下一次判断以当前系统时间为基准       
//##(0)读取三轴数据,
    currX = TMAG3001getMeasurementX(TMAG3001FOLD);              //##(0)读取"X"轴磁场数值
    currY = TMAG3001getMeasurementY(TMAG3001FOLD);              //##(0)读取"Y"轴磁场数值
    currZ = TMAG3001getMeasurementZ(TMAG3001FOLD);              //##(0)读取"Z"轴磁场数值
	Angle = TMAG3001getMeasurementANGLE(TMAG3001FOLD);
	Magnitude = TMAG3001getMeasurementMAG(TMAG3001FOLD);	
    #asm nop #endasm                                            //##(0)空间矢量合成总磁场：勾股定理求模长 
    totalMag = sqrt(currX*currX + currY*currY + currZ*currZ);   //##(0)X+Y+Z 开根号,得到空间综合磁场强度 
//##(0)如果不是睡眠唤醒则需要滤波    
    filter_total = filter_total * 0.2f + totalMag * 0.8f;		//##(0)一阶低通滤波算法：历史滤波值占70%，本次新采样值占30%
    totalMag = filter_total;									//##(0)将滤波后平滑的值赋值回总磁场变量，后续判断使用平滑后数据               
//##(0)判断磁铁离开/靠近
    if(regs.FOLD == UNFOLD_STATE) {         //##(0)当前状态处于离开状态(展开)
        if(totalMag > FOLD_TRIGGER) {         //##(0)判断是否达到靠近(折叠)阈值
            regs.FOLD = FOLD_STATE;         //##(0)设置为折叠状态
		}
    }else{                                  //##(0)当前状态处于靠近(折叠)
        if(totalMag < FOLD_RELEASE) {       //##(0)判断是否达到离开(展开)阈值
            regs.FOLD = UNFOLD_STATE;       //##(0)设置为展开状态
            regs.flags.button1 = 1;         //##(0)
        }
    }
//##(0)将数据更新到发送缓冲器中
	FOLDX = (int16_t)currX;
	FOLDY = (int16_t)currY;
    FOLDZ = (int16_t)currZ;
	FOLD_ANGLE = (int16_t)Angle;
	FOLD_MAGNITUTE = (int16_t)Magnitude;
}

/*###############################################################################################################################
# 函数名 :  void SensorFOLD_Process(void)                                                                                       #
# 功  能 :  判断折叠或者是展开                                                                                                  #
# 参  数 :  NONE                                                                                                                #
# 说  明 :  每100毫秒读取一次XYZ磁场／角度／幅度                                                                                #
###############################################################################################################################*/
void SensorSTRAP_Process(void) {
    static uint16_t timeout;
    static float filter_total = 0.0f;						//##(0)滤波缓存变量，对总磁场做一阶低通滤波，消除采样抖动、干扰毛刺
           float currX, currY, currZ;						//##(0)存储三轴原始磁场分量（单位mT）
		   float Angle;										//##(0)角度值
		   float Magnitude;									//##(0)三轴磁场的合成幅值
           float totalMag;									//##(0)三轴合成总磁场强度模长
//##(0)100ms才执行一次采集判断   
    if((regs.time10ms-timeout)<100/10) return;      
    timeout = regs.time10ms;								//##(0)更新计时起点,下一次判断以当前系统时间为基准          
//##(0)读取三轴数据(X/Y/Z),角度值,幅值
    currX = TMAG3001getMeasurementX(TMAG3001STRAP);         //##(0)读取"X"轴磁场数值
    currY = TMAG3001getMeasurementY(TMAG3001STRAP);         //##(0)读取"Y"轴磁场数值
    currZ = TMAG3001getMeasurementZ(TMAG3001STRAP);         //##(0)读取"Z"轴磁场数值
    Angle = TMAG3001getMeasurementANGLE(TMAG3001STRAP);     //##(0)读取角度值
    Magnitude = TMAG3001getMeasurementMAG(TMAG3001STRAP);   //##(0)读取幅值
//##(0)X+Y+Z 开根号,得到空间综合磁场强度 
    totalMag = sqrt(currX*currX + currY*currY + currZ*currZ);   
//##(0)如果不是睡眠唤醒则需要滤波    
//##(0)平滑磁场数值,防止电压波动、震动导致数值频繁跳变                           
    filter_total = filter_total * 0.3f + totalMag * 0.7f;   //##(0)一阶低通滤波算法：历史滤波值占30%，本次新采样值占70%
    totalMag = filter_total;                                //##(0)将滤波后平滑的值赋值回总磁场变量，后续判断使用平滑后数据               
//##(0)判断磁铁离开/靠近
    if(regs.STRAP == STRAP_REM) {							//##(0)当前状态处于移除状态
        if(totalMag > STRAP_TRIGGER) {						//##(0)判断是否达到靠近(绑上)阈值
            regs.STRAP = STRAP_Bind;						//##(0)设置为绑上状态
		}
    }else{													//##(0)当前状态处于靠近(绑上)
        if(totalMag < STRAP_RELEASE) {						//##(0)判断是否达到移除(离开)阈值
            regs.STRAP = STRAP_REM;							//##(0)设置为移除状态
			if(regs.flags.mcuSleep == true) {				//##(0)如果之前是睡眠则磁场离开需要显示容量
				regs.flags.mcuSleep = false;				//##(0)清除标志以免重复
				regs.flags.button1 |= 1;					//##(0)显示容量使能
			}
		}
    }
//##(0)将数据更新到发送缓冲器中,浮点数转为长整形
	STRAPX = (int16_t)currX;		
	STRAPY = (int16_t)currY;
    STRAPZ = (int16_t)currZ;
	STRAP_ANGLE = (int16_t)Angle;
	STRAP_MAGNITUTE = (int16_t)Magnitude;	
}

/*###############################################################################################################################
 *         初始化TMAG3001磁场靠近中断（磁铁靠近→磁场超标→INT拉低，MCU下降沿中断）
 *  chipAddr : 传感器I2C地址 TMAG3001FOLD / TMAG3001STRAP
 *  axisEn   : 启用检测轴 MAG_CH_EN_X / MAG_CH_EN_Y / MAG_CH_EN_Z（单轴检测）
 *  thrLsb   : 阈值LSB数值(0~255)，根据量程换算磁场阈值
 *  hystSel  : 阈值迟滞 THR_HYST_2LSB ~ THR_HYST_256LSB
 *     false = 初始化成功 true=I2C读写失败
 ###############################################################################################################################*/
bool Sensor_config(uint8_t tmag, uint8_t ConfigMode) {
    uint8_t WriteSleepCount = 0;
    boolean write_passed = false;
//##(0)如果没有配置模式则返回"1"    
    if(ConfigMode==0U) return(1);
	delay_ms(10);
//##(0)有配置则先将全部寄存器恢复到默认值(上电状态值),
    if(TMAG3001restoreDefaultValues(tmag)) return(1);
//##(0)启用X/Y/Z磁轴以进行测量   
    if(TMAG3001enableMagChannels(tmag, MAG_CH_EN_XYZ)) return(1);                   
//##(0)设置量程【X/Y 轴选择基础小量程/Z 轴同步选择基础小量程】       
    if(TMAG3001setRanges(tmag, RANGE_40mTor120mT, RANGE_40mTor120mT)) return(1); 
//##(0)低电流低噪声模式
    if(TMAG3001selectLowCurrentNoiseMode(tmag,0x00)) return(true);
//##(0)4倍平均滤波抑制杂磁噪声
    if(TMAG3001setSampleRate(tmag, CONV_AVG_8xAverage)) return(true);    
//##(0)设置X/Y/Z轴高低阈值：过滤微小磁场噪声,防止无磁频繁误中断    
    if(TMAG3001setThrHyst(tmag,THR_HYST_16LSB)) return(1);     
//##(0)配置"INTB"引脚极性,默认设置为高电平,中断事件触发时为低,     
    if(TMAG3001intbPolarity(tmag, INTB_POL_DefaultHigh)) return(1);                   
//##(0)如果是0x01则为连续测量模式
    if(ConfigMode == ContinuousMode) {                                          //##(0)连续模式
        if(TMAG3001enableAngleMeasurement(tmag,ANGLE_EN_X1stY2nd)) return(1);   //##(0)启用角度测量1h = X 第一,Y 第二
//        if(TMAG3001setFieldThreshold(tmag,xLO,xHI,yLO,yHI,zLO,zHI)) return(1);			//##(0)设置阈值,按需调整 XYZ 阈值
//        if(TMAG3001enableSwitchMode(tmag, Omnipolar_Switch_Mode)) return(1);				//##(0)全极开关模式：有磁持续输出低(直接关闭角度硬件)
        if(TMAG3001intPinLatchedPulsed(tmag,INT_STATE_Pulse))  return(1);		//##(0)INT中断被锁存,直到由对器件寻址的控制器清除
        if(TMAG3001enterContinuousMeasureMode(tmag)) return(1);                 //##(0)进入连续实时采样【不用休眠,实时监测磁场绝对值】
    }else if(ConfigMode == DutyCycleMode) {                                     //##(1)唤醒和睡眠模式【占空比模式】
        if(TMAG3001enableAngleMeasurement(tmag,ANGLE_EN_Disabled)) return(1);   //##(1)关闭角度计算
        if(TMAG3001disableThresholds(tmag)) return(1);                          //##(1)禁用固定阈值，防止冲突)
        if(TMAG3001enableWakeOnFieldChange(tmag)) return(1);                    //##(1)磁场变化唤醒WOC   
        if(TMAG3001intPinLatchedPulsed(tmag,INT_STATE_Pulse)) return(1);        //##(1)中断采用脉冲（5us）
        if(TMAG3001interruptThroughINT(tmag,0x02)) return(1);                   //##(1)INT引脚输出中断
        if(TMAG3001enableThresholds(tmag)) return(1);                           //##(1)使能WOC阈值中断)
        if(TMAG3001setWakeUpAndSleepMode(tmag,SLEEPTIME_500ms)) return(1);		//##(1)关键：进入W&S休眠模式,0x08=500ms休眠周期,必须最后调用 
    }else if(ConfigMode == DeepSleepMode) {                                     //##(2)深度睡眠模式
        for(WriteSleepCount=0; WriteSleepCount<5U; WriteSleepCount++) {
            if(TMAG3001enterSleepMode(tmag)==false) { 
                write_passed = 1; break;                                        //##(3)如果写成功命令则直接退出循环
            }     
            restart_wdt();
            delay_ms(50);
        }
        if(write_passed == false) return(1);                                    //##(3)连续5次都写入失败则返回"1"
    }                                                       
    return(false);  
}

/*###############################################################################################################################
# 函数名 :  void config_Hall(void)                                                                                              #
# 功  能 :  配置绑带/折叠霍尔传感器                                                                                             #
# 参  数 :  NONE                                                                                                                #
# 说  明 :  NONE                                                                                                                #
###############################################################################################################################*/
void config_Hall(void) {
    Sensor_config(TMAG3001FOLD,ContinuousMode);     //##(0)配置为连续采样模式【磁场感应】
    Sensor_config(TMAG3001STRAP,ContinuousMode);    //##(0)配置为连续采样模式【磁场感应】	
}

/*###############################################################################################################################
# 声明结束                                                                                                                      #
###############################################################################################################################*/
#ifdef	__cplusplus
}
#endif
#endif

