/*###############################################################################################################################
 # 文件名称 ： u80711R01_BQ76952_H                                                                                              #
 # 公司名称 :  TOTEX Technology, Inc.                                                                                           #
 # 芯片型号 ： PIC24FJ128GA302                                                                                                  #
 # 编译工具 :  ccs compiler v5.118                                                                                              #
 # 作    者 :  BenZhang                                                                                                         #
 # 编写日期 :  2025/11/10                                                                                                       #
 # 版    本 :  v1.00                                                                                                            #
 ##############################################################################################################################*/
#ifndef APPS_DRIVE_H
#define	APPS_DRIVE_H
/*###############################################################################################################################
# 包含文件                                                                                                                      #
###############################################################################################################################*/
#include "app_Display.h"
#include "app_config.h"
#include "app_bq76952.h"
/*###############################################################################################################################
# 声明开始                                                                                                                      #
###############################################################################################################################*/
#ifdef	__cplusplus
extern "C"
{
#endif
/*###############################################################################################################################
# CRC16 Modbus 查表（0x8005 反转多项式 0xA001）                                                                                 #
###############################################################################################################################*/    
static const uint16_t crc16_table[256] = {
    0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
    0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
    0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
    0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
    0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
    0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
    0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
    0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
    0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
    0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
    0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
    0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
    0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
    0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
    0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
    0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
    0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
    0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
    0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
    0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
    0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
    0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
    0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
    0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
    0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
    0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
    0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
    0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
    0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
    0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
    0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
    0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040
};
/*###############################################################################################################################
# CRC8 校验码表格                                                                                                               #
###############################################################################################################################*/     
const uint8_t crc8_table_0x07[256] = {
    0x00,0x07,0x0E,0x09,0x1C,0x1B,0x12,0x15,0x38,0x3F,0x36,0x31,0x24,0x23,0x2A,0x2D,
    0x70,0x77,0x7E,0x79,0x6C,0x6B,0x62,0x65,0x48,0x4F,0x46,0x41,0x54,0x53,0x5A,0x5D,
    0xE0,0xE7,0xEE,0xE9,0xFC,0xFB,0xF2,0xF5,0xD8,0xDF,0xD6,0xD1,0xC4,0xC3,0xCA,0xCD,
    0x90,0x97,0x9E,0x99,0x8C,0x8B,0x82,0x85,0xA8,0xAF,0xA6,0xA1,0xB4,0xB3,0xBA,0xBD,
    0xC7,0xC0,0xC9,0xCE,0xDB,0xDC,0xD5,0xD2,0xFF,0xF8,0xF1,0xF6,0xE3,0xE4,0xED,0xEA,
    0xB7,0xB0,0xB9,0xBE,0xAB,0xAC,0xA5,0xA2,0x8F,0x88,0x81,0x86,0x93,0x94,0x9D,0x9A,
    0x27,0x20,0x29,0x2E,0x3B,0x3C,0x35,0x32,0x1F,0x18,0x11,0x16,0x03,0x04,0x0D,0x0A,
    0x57,0x50,0x59,0x5E,0x4B,0x4C,0x45,0x42,0x6F,0x68,0x61,0x66,0x73,0x74,0x7D,0x7A,
    0x89,0x8E,0x87,0x80,0x95,0x92,0x9B,0x9C,0xB1,0xB6,0xBF,0xB8,0xAD,0xAA,0xA3,0xA4,
    0xF9,0xFE,0xF7,0xF0,0xE5,0xE2,0xEB,0xEC,0xC1,0xC6,0xCF,0xC8,0xDD,0xDA,0xD3,0xD4,
    0x69,0x6E,0x67,0x60,0x75,0x72,0x7B,0x7C,0x51,0x56,0x5F,0x58,0x4D,0x4A,0x43,0x44,
    0x19,0x1E,0x17,0x10,0x05,0x02,0x0B,0x0C,0x21,0x26,0x2F,0x28,0x3D,0x3A,0x33,0x34,
    0x4E,0x49,0x40,0x47,0x52,0x55,0x5C,0x5B,0x76,0x71,0x78,0x7F,0x6A,0x6D,0x64,0x63,
    0x3E,0x39,0x30,0x37,0x22,0x25,0x2C,0x2B,0x06,0x01,0x08,0x0F,0x1A,0x1D,0x14,0x13,
    0xAE,0xA9,0xA0,0xA7,0xB2,0xB5,0xBC,0xBB,0x96,0x91,0x98,0x9F,0x8A,0x8D,0x84,0x83,
    0xDE,0xD9,0xD0,0xD7,0xC2,0xC5,0xCC,0xCB,0xE6,0xE1,0xE8,0xEF,0xFA,0xFD,0xF4,0xF3
}; 

/*###############################################################################################################################
# 函数声明                                                                                                                      #
###############################################################################################################################*/    
uint8_t Asc_Hex(uint8_t Ascii);
uint8_t AsciiToHex(uint8_t *s);
uint8_t checksum_crc8(uint8_t *ptr, uint8_t len);
uint16_t crc16_modbus(uint8_t *data, uint16_t len);
unsigned long Getword(unsigned char *String);
uint16_t Measure_InnerADC(uint8_t Measure_Port,uint8_t N);

boolean i2c_PutsData(uint8_t chip, uint8_t reg, uint8_t *buffer, uint8_t Length);
boolean i2c_GetsData(uint8_t chip, uint8_t reg, uint8_t *buffer, uint8_t Length);

boolean writeEEPROM(uint8_t reg, uint8_t *buffer, uint8_t Length);
boolean readEEPROM(uint8_t reg, uint8_t *buffer, uint8_t Length);

/*###############################################################################################################################
# 函数名	: unsigned char atoi_b16(char *s)                                                                                     #
# 功  能	: ASCII 转换成HEX                                                                                                     #
# 参  数	: S = 字符串首地址                                                                                                    #
# 说  明	: result = 转换后的数                                                                                                 #
###############################################################################################################################*/
uint8_t Asc_Hex(uint8_t Ascii) {
    if(Ascii>='0'&&  Ascii<='9')
        Ascii = Ascii-'0';
    else if( Ascii>='A'&& Ascii<='F' )
    	Ascii = Ascii-'A' + 10;
    else
        Ascii = 0;
    return Ascii;
}

/*###############################################################################################################################
# 函数名 :  unsigned char atoi_b16(char *s)                                                                                     #
# 功  能 :  ASCII 转换成 HEX                                                                                                    #
# 参  数 :  S = 字符串首地址                                                                                                    #
# 说  明 :  result = 转换后的数                                                                                                 #
###############################################################################################################################*/
uint8_t AsciiToHex(uint8_t *s) {
    uint8_t result = 0,i;
    for(i=0; i<2; i++,s++) {
        if(*s >= 'A')
            result = 16*result + (*s) - 'A' + 10;
        else if(*s >= '0')
            result = 16*result + (*s) - '0';
    }
   return(result);
}

/*###############################################################################################################################
# 函数名 : uint8_t CRC8_Table(uint8_t *buf, uint8_t len)                                                                        #
# 功  能 : CRC8计算                                                                                                             #
# 参  数 : buf = 要计算的数据指针    Length = 要计算CRC的字节数                                                                 #
# 说  明 : 查表法 最省时间、最省 CPU ,PIC指令少：1 字节 ≈ 8 指令周期                                                           #
#                                                                                                                               #
###############################################################################################################################*/ 
uint8_t checksum_crc8(uint8_t *buf, uint8_t len) {
    uint8_t crc = 0x00;
    while(len--) {
        crc = crc8_table_0x07[crc ^ *buf++];
    }
    return crc;
}

/*###############################################################################################################################
# 函数名 : uint16_t crc16_modbus_bit(const uint8_t *data, uint16_t len)                                                         #
# 功  能 : 查表版 CRC16 Modbus 函数                                                                                             #
# 参  数 : data 输入数据缓冲区  len  数据长度（字节数）计算得到的CRC16值                                                        #
# 说  明 : 执行时间比逐位算法效率高8倍                                                                                          #
###############################################################################################################################*/
uint16_t crc16_modbus(uint8_t *buf, uint16_t len) {
    uint16_t crc = 0xFFFF;
    while (len--) {
        crc = (crc >> 8) ^ crc16_table[(crc & 0xFF) ^ *buf++];
    }
    return crc;
}

/*###############################################################################################################################
# 函数名	: unsigned long GetValue_WORD(unsigned char *String)                                                                  #
# 功  能	: 转换字符为2字节16进制                                                                                               #
# 参  数 	: *String = 字符指针                                                                                                  #
# 说  明	: NONE                                                                                                                #
###############################################################################################################################*/
unsigned long Getword(unsigned char *String) {
    unsigned char Ptr = 0;
    unsigned long result = 0x0000;
//##(0)连续转换N个字符，当碰到字符 ',' 和 '\r' 则结束转换
    while(String[Ptr]!=',' & String[Ptr]!='\r') {             
        result = (result<<4) + Asc_Hex(String[Ptr++]);        //##(0)转换单个字符
    }
    return result;
}

/*###############################################################################################################################
# 函数名 : unsigned long Measure_ADC(unsigned char Measure_Port,unsigned char N)                                                #
# 功  能 : MCU内部ADC模块测量                                                                                                   #
# 参  数 : Measure_Port : 要测量的通道   N : 采样次数最多11次(最好按奇数测量)                                                   #
# 说  明 : 转换的ADC量化值(mV)                                                                                                  #                                                                            																								*
###############################################################################################################################*/
uint16_t Measure_InnerADC(uint8_t Measure_Port,uint8_t N) {
    uint16_t result;
    uint32_t accumulate = 0;        
//##(0)设置采样输入端口并启动ADC转换
    set_adc_channel(Measure_Port);          
    delay_us(500);
//##(0)连续转换 N 次ADC
    for(uint8_t Measure_N=0; Measure_N<N; Measure_N++) {
        accumulate = accumulate + read_adc();     
        delay_us(100);
    }
//##(0)计算结果
   result = (accumulate/N)* vref_lsb;
   return(result);
} 

/*###############################################################################################################################
# 函数名  :  BOOLEAN smbus_PutsData(u8 chip,u8 address, u8 *buffer, u8 Length)                                                  #
# 功  能  :  向I2C目标器件，目标地址，写入 N 个数据                                                                             #
# 参  数  :  chip : 目标I2C器件地址                                                                                             #
#             reg : I2C器件中数据存储地址                                                                                       #
#           *data : I2C器件中存入数据指针                                                                                       #
#          Length : 要写入的数据长度                                                                                            #
# 说  明  :  写入成功返回"0"失败返回"1"                                                                                         #
###############################################################################################################################*/
boolean i2c_PutsData(uint8_t chip, uint8_t reg, uint8_t *buffer, uint8_t Length) { 
    uint8_t bytes;
i2c_start:
    i2c_start(i2c,1);                               //##(0)启动总线
    if(i2c_write(i2c,chip)) goto rerror;            //##(0)写芯片地址,如果写失败则转入失败执行处理
    if(i2c_write(i2c,reg))  goto rerror;            //##(0)写寄存器地址,如果写失败则转入失败执行处理  
    for(bytes=0; bytes<Length; bytes++) {           //##(0)写入多个字节数据
        if(i2c_write(i2c,buffer[bytes]))            //##(0)写数据,如果写失败则转入失败执行处理
            goto rerror; 
        delay_us(10);        
    }
    i2c_stop(i2c);                                  //##(0)写完成则发送停止信号
    return(false);                                  //##(0)返回"0"
rerror:
    i2c_start(i2c,1);                               //##(0)重新启动总线
    delay_us(20);
    i2c_stop(i2c);                                  //##(0)发送失败则先发送停止信号
    return(true);                                   //##(0)确认写数据失败则返回"1"
}
/*###############################################################################################################################
# 函数名  :  BOOLEAN smbus_GetsData(u8 chip1,u8 address, u8 *buffer, u8 Length)                                                 #
# 功  能  :  向I2C目标器件，目标地址，读取 N 个数据                                                                             #
# 参  数  :  chip : 目标I2C器件地址                                                                                             #
#             reg : I2C器件中数据存储地址                                                                                       # 
#           *data : I2C器件中存入数据指针                                                                                       #
#          Length : 要写入的数据长度                                                                                            #
# 说  明  :  读取成功返回"0"失败返回"1"                                                                                         #
###############################################################################################################################*/
boolean i2c_GetsData(uint8_t chip, uint8_t reg, uint8_t *buffer, uint8_t Length) {
    uint8_t bytes;                                     
write_start:
    i2c_start(i2c,1);                               //##(0)启动总线
    if(i2c_write(i2c,chip)) goto Werror;            //##(0)写芯片地址,如果写失败则转入失败执行处理
    if(i2c_write(i2c,reg))  goto Werror;            //##(0)写寄存器地址,如果写失败则转入失败执行处理 
    delay_us(10);
    i2c_start(i2c,1);                               //##(0)重新启动总线
    if(i2c_write(i2c,chip|0x01)) goto Werror;       //##(0)失败转处理
    delay_us(10);
    for(bytes=0; bytes<Length-1; bytes++) {         //##(0)连续接收多个字节数据
        buffer[bytes] = i2c_read(i2c,true);         //##(0)接收数据并应答ack
    }
    buffer[bytes] = i2c_read(i2c,false);            //##(0)接收最后一个数据并不应答ack
    i2c_stop(i2c);                                  //##(0)读取完成则发送停止信号
    return(false);                                  //##(0)返回"0"
Werror:
    i2c_start(i2c,1);                               //##(0)重新启动总线
    delay_us(20);
    i2c_stop(i2c);                                  //##(0)读取完成则发送停止信号
    return(true);
}

/*###############################################################################################################################
# 函数名 : boolean writeEEPROM(uint8_t reg, uint8_t *buffer, uint8_t Length)                                                    #
# 功  能 : 写 EEPROM (写多个字节/单个字节)                                                                                      #                                                                       																								*
###############################################################################################################################*/
boolean writeEEPROM_page(uint8_t address, uint8_t *buffer, uint8_t Length) {
//##(0)限制最大16字节 (M24C04 页大小)
    Length = (Length>PageSize)? PageSize:Length; 
//##(0)写一个页面数据,写失败则返回"1"
    if(i2c_PutsData(M24C04,address,buffer,Length)) return(1); 
//##(0)写一个页面成功,如果写下一页面则需要等待 > 5ms 
    delay_ms(6);
//##(0)返回"0"    
    return(0);  
}

/*###############################################################################################################################
# 函数名 : boolean writeEEPROM(uint8_t reg, uint8_t *buffer, uint8_t Length)                                                    #
# 功  能 : 写 EEPROM (写多个字节/单个字节)                                                                                      #                                                                       																								*
###############################################################################################################################*/
boolean m24c04_Write(uint8_t address, uint8_t *buffer, uint8_t Length) {
//##(0)定义一个变量，用来存 当前页还能写多少字节    
    uint8_t bytesInPage;
//##(0)拉低写使能引脚"WC"
    output_bit(M24C04WC,0);
    delay_ms(1);    
//##(0)只要还有数据没写完（Length > 0），就一直循环写
    while(Length > 0) {
//##(0)计算当前页剩余空间(这一页还能写多少字节)
        bytesInPage = PageSize - (address & 0x0F);
//##(0)如果剩下要写的数据长度小于当前页剩余空间，那就只写"Length"这么多，不用写满 16 字节
        if(Length < bytesInPage) { bytesInPage = Length; }
//##(0)调用单页写入函数,写一整页 / 写剩余字节
        if(writeEEPROM_page(address, buffer, bytesInPage)) { output_bit(M24C04WC,1); return(1); }
//##(0)延时5毫秒等待芯片内部烧录完成        
        delay_ms(5);
//##(0)调整
        address += bytesInPage;         //##(0)地址向后移动 刚写入的长度)
         buffer += bytesInPage;         //##(0)数据指针也向后移动
         Length -= bytesInPage;         //##(0)剩余长度减去刚写掉的长度
    }
//##(0)关闭写使能
    output_bit(M24C04WC,1);    
//##(0)写完成则返回"0"    
    return(0);   
}

/*###############################################################################################################################
# 函数名 : boolean readEEPROM(uint8_t reg, uint8_t *buffer, uint8_t Length)                                                     #
# 功  能 : 读 EEPROM (写多个字节/单个字节)                                                                                      #                                                                       																								*
###############################################################################################################################*/
boolean m24c04_read(uint8_t address, uint8_t *buffer, uint8_t Length) {
    return(i2c_GetsData(M24C04, address, buffer, Length));
}

/*###############################################################################################################################
# 函数名 : uint8_t  Keyboard_Button1_Process(void)                                                                              #
# 功  能 : 读取按键[2]状态              																			  #
# 参  数 : NONE                                                                                                                 #
# 说  明 : 状态机架构：稳定、抗干扰、无逻辑 BUG , 非阻塞：不卡主循环，可同时跑其他任务 ,靠定时器 10ms 基准计时(每10ms调用一次)  #
###############################################################################################################################*/
KeyStatus Keyboard_Button_Process(void) {
    static uint16_t key_timer = 0;
    static uint8_t  KeyState = key_state_0;   
    static uint8_t  last_key1press,last_key2press;
    static boolean  key1_press, key2_press, both_press, release_press;
    static boolean  both_long_reported;
    static boolean  long_reported;
    KeyStatus key = KEY_NONE;      
//##(0)读取两个按键,按下="1",没按="0",方便判断
    key1_press = !input_state(BTN1_PIN);                    //##(0)按下按键 key1_press = 1
    key2_press = !input_state(BTN2_PIN);                    //##(0)按下按键 key2_press = 1
    both_press = ( key1_press &&  key2_press);              //##(0)双键同时按下 both_press = 1
 release_press = (!key1_press && !key2_press);              //##(0)双键释放 release_press 1 
//##(0)执行状态机
    switch(KeyState) {
        case key_state_0:                                   //##(0)空闲状态(初始状态)
             if(key1_press || key2_press)          
                KeyState = key_state_1;                     //##(0)任意按键按下 → 进入消抖
             long_reported = false;                         //##(0)长按事件是否已经上报过标志清零
             both_long_reported = false;
             break;                                         //##(0)没有按键按下则返回空闲状态
        case key_state_1:                                   //##(0)按键消抖,如果再次确认按键是没有按下则认为是是干扰抖动 → 回到空闲状态 
             KeyState = (release_press)? key_state_0:key_state_2;   
             last_key1press = key1_press;                   //##(1)保存按下状态
             last_key2press = key2_press;                   //##(1)保存按下状态
             long_reported = false;                         //##(0)长按事件是否已经上报过标志清零
             both_long_reported = false;
             key_timer = 0u;                                //##(0)按键按下计时器清零                        
             break;
        case key_state_2:                                   //##(0)判断双键按下或者短按/长按                                    
             key_timer++;                                   //##(2)按键按下计时器递增
             if(both_press) { key_timer = 0; KeyState = key_state_3; }        //##(2)如果是双键按下则进入双键模式                         
             
             if(release_press == true) {                    //##(0)全部按键松开则判断按下多少时间确认是短按/长按                                                 
                if(key_timer < 1000/10 ) {                   //##(2)如果时间低于0.5S则认为是短按按下弹起
                    if(last_key1press) key = KEY1_SHORT;    //##(2)按键"1"短按  
                    if(last_key2press) key = KEY2_SHORT;    //##(2)按键"2"短按
                }else if(key_timer<5000/10){
                    if(long_reported==true) break;          //##(2)已经确认过是长按则不再执行判断
                    if(last_key1press) key = KEY1_LONG;     //##(2)按键"1"长按
                    if(last_key2press) key = KEY2_LONG;     //##(2)按键"2"长按
                    long_reported = true; 
                }else{
                    if(long_reported==true) break;          //##(2)已经确认过是长按则不再执行判断
                    if(last_key1press) key = KEY1_LLONG;    //##(2)按键"1"超长按
                    if(last_key2press) key = KEY2_LLONG;    //##(2)按键"2"超长按
                    long_reported = true; 
                }     
                KeyState = key_state_0;                     //##(2)返回空闲状态(初始状态) 
             }
             break; 
        case key_state_3:                                   //##(3)双键按下模式
             key_timer++;                                   //##(3)按键按下计时器递增                                                                                 
             if(both_press && !both_long_reported) {        //##(3)双键长按：按住达到2s,立刻上报,不需要松手,只上报一次
                if(key_timer >= 2000/10) {                  //##(3)按住时长达到2秒则为双键长按
                    key = KEY_BOTH_LONG;                    //##(3)返回双键长按值               
                    both_long_reported = true;              //##(3)设置之上报一次
                }
             }
             if(release_press == true) {                    //##(3)双键短按:保留原有逻辑,必须双键同时松开,且时间0.5~1s之间,才上报
                if(key_timer>50 && key_timer<100) {         //##(3)按住到到松开时间在0.5秒~1秒之间则是短按
                    key = KEY_BOTH_SHORT;                   //##(3)返回双键短按值
                }
                KeyState = key_state_0;
             }
             
             if(key_timer<500/10) {                         //##(3)若其中一个按键在短按时长(0.5S)前松开,恢复为仅识别仍按住的按键
                if(!key1_press || !key2_press) 
                    KeyState = key_state_0;                 //##(3) 
             }  
             break;             
        default:
             KeyState = key_state_0;
             break;
    }
    return key;
}

/*###############################################################################################################################
# 函数名 :  void main(void)                                                                                                     #
# 功  能 :  主函数                                                                                                              #
# 参  数 :  NONE                                                                                                                #
# 说  明 :  NONE                                                                                                                #
###############################################################################################################################*/
void read_ID_resistor(void) {
    uint16_t SYSADC;
     uint8_t MeasureCount = 0;
//##(0)测量ID电阻阻值,如果接入的阻值是10KR~30KR则认为是开机
    SYSBIAS_ON;                                             //##(0)输出基准上拉电压(上拉电阻为10KR)
    delay_ms(50);                                           //##(0)延时稳定
//##(0)连续测量5次,每次间隔10毫秒,如果有3次以上阻值在10~30KR之间则认为是接入有效设备
    MeasureCount = 0U;
    for(uint8_t i=0; i<10; i++)  {
        SYSADC = Measure_InnerADC(sys_adc,5)-500;           //##(0)读取电压
        MeasureCount += (SYSADC>800 && SYSADC<1600)? 1:0;   //##(0)在范围内则加"1"
        delay_ms(10);                                       //##(0)间隔延时       
    }
//##(0)判断测量次数来决定开机？否则是睡眠模式
    regs.flags.RunMode = (MeasureCount>5u)? MODE_WORK:MODE_SLEEP;
} 

/*###############################################################################################################################
# 函数名 :  uint8_t writeEeprom(uint8_t address, uint8_t *buff, uint8_t Length)                                                 #
# 功  能 :  写 EEPROM                                                                                                           #
# 参  数 :  NONE                                                                                                                #
# 说  明 :  NONE                                                                                                                #
###############################################################################################################################*/
uint8_t writeEeprom(uint8_t address, uint8_t *buff, uint8_t Length) {
//##(0)写成功则返回"0"不再接着写，失败则接着写     
    if(m24c04_Write(address, buff, Length)==false) return(0);             
    delay_ms(1);
//##(0)写成功则返回"0"不再接着写，失败则接着写    
    if(m24c04_Write(address, buff, Length)==false) return(0);       
    delay_ms(1);
//##(0)写成功则返回"0"不再接着写，失败则接着写    
    if(m24c04_Write(address, buff, Length)==false) return(0);   
//##(0)连续3次写失败则返回"1"    
    return(1);
}

/*###############################################################################################################################
# 函数名 :  uint8_t writeEeprom(uint8_t address, uint8_t *buff, uint8_t Length)                                                 #
# 功  能 :  写 EEPROM                                                                                                           #
# 参  数 :  NONE                                                                                                                #
# 说  明 :  NONE                                                                                                                #
###############################################################################################################################*/
uint8_t readEeprom(uint8_t address, uint8_t *buff, uint8_t Length) {
//##(0)写成功则返回"0"不再接着写，失败则接着写     
    if(m24c04_read(address, buff, Length)==false) return(0);             
    delay_ms(1);
//##(0)写成功则返回"0"不再接着写，失败则接着写    
    if(m24c04_read(address, buff, Length)==false) return(0);       
    delay_ms(1);
//##(0)写成功则返回"0"不再接着写，失败则接着写    
    if(m24c04_read(address, buff, Length)==false) return(0);   
//##(0)连续3次写失败则返回"1"    
    return(1);
}

/*###############################################################################################################################
# 函数名 :  void config_timers(bool Enable_Disable)																	  #
# 功  能 :  配置定时器[1/2/3/4]                                                                                                 #
# 参  数 :  NONE                                                                                                                #
# 说  明 :  NONE                                                                                                                #
###############################################################################################################################*/
void config_timers(bool Enable_Disable) {
//##(0)配置定时器参数
	setup_timer1(TMR_INTERNAL|TMR_DIV_BY_8,20000);      //##(0)配置时钟源和分配系数
    clear_interrupt(INT_TIMER1);                        //##(0)清除中断标志
	#asm nop #endasm
	setup_timer2(TMR_INTERNAL|TMR_DIV_BY_256,62500);	//##(0)配置时钟源和分配系数		
    clear_interrupt(INT_TIMER2);                        //##(0)清除定时器中断标志
	#asm nop #endasm
	setup_timer3(TMR_INTERNAL|TMR_DIV_BY_8,10000);      //##(0)配置时钟源和分配系数		
    clear_interrupt(INT_TIMER3);						//##(0)清除定时器中断标志
	#asm nop #endasm
	setup_timer4(TMR_INTERNAL|TMR_DIV_BY_8,2000);       //##(0)配置时钟源和分配系数,定时1ms(查询串口接收DMA使用)		
    clear_interrupt(INT_TIMER4);						//##(0)清除定时器中断标志
//#(0)如果是需要开启全部定时器
    if(Enable_Disable == Enable) {
        enable_interrupts(INT_TIMER1);					//##(0)使能定时器中断
        enable_interrupts(INT_TIMER2);                  //##(0)使能定时器中断
        enable_interrupts(INT_TIMER3);                  //##(0)使能定时器中断
        enable_interrupts(INT_TIMER4);                  //##(0)使能定时器中断 
    }else{
        setup_timer1(TMR_DISABLED);						//##(0)关闭定时器【1】	
        disable_interrupts(INT_TIMER1);					//##(0)禁止定时器中断
        #asm nop #endasm
        setup_timer2(TMR_DISABLED);						//##(0)关闭定时器【2】	
        disable_interrupts(INT_TIMER2);					//##(0使能定时器中断
        #asm nop #endasm
        setup_timer3(TMR_DISABLED);						//##(0)关闭定时器【3】
        disable_interrupts(INT_TIMER3);					//##(0使能定时器中断
        #asm nop #endasm
        setup_timer4(TMR_DISABLED);						//##(0)关闭定时器【4】
        disable_interrupts(INT_TIMER4);					//##(0使能定时器中断	
    }
}

/*###############################################################################################################################
# 函数名 :  void config_ExtInterrupts(void)																		  #
# 功  能 :  配置外部中断																						  #
# 参  数 :  NONE                                                                                                                #
# 说  明 :  NONE                                                                                                                #
###############################################################################################################################*/
void config_ExtInterrupts(void) {
    ext_int_edge(INT_EXT0,H_TO_L);                      //##(0)"SYS_INT"下降沿触发中断或者唤醒【EXINT0】
    INTCON2 |= 0x0001;			 
    clear_interrupt(INT_EXT0);				//##(0)清除外部中断标志
    enable_interrupts(INT_EXT0);                        //##(1)使能中断
    #asm nop #endasm
    ext_int_edge(INT_EXT1,H_TO_L);                      //##(0)"BTN1"下降沿触发中断或者唤醒【EXINT1】
    INTCON2 |= 0x0002;                                  //##(0)编译器问题需要声明寄存器重设位
    clear_interrupt(INT_EXT1);				//##(0)清除外部中断标志
    enable_interrupts(INT_EXT1);                        //##(1)使能中断
    #asm nop #endasm
    ext_int_edge(INT_EXT2,H_TO_L);                      //##(0)"BTN2"下降沿触发中断或者唤醒【EXINT2】
    INTCON2 |= 0x0004;                                  //##(0)编译器问题需要声明寄存器重设位
    clear_interrupt(INT_EXT2);                          //##(0)清除外部中断标志
    enable_interrupts(INT_EXT2);                        //##(1)使能中断
    #asm nop #endasm
    ext_int_edge(INT_EXT3,H_TO_L);                      //##(0)"SENSOR1"下降沿触发中断或者唤醒【EXINT3】
    INTCON2 |= 0x0008;                                  //##(0)编译器问题需要声明寄存器重设位
    clear_interrupt(INT_EXT3);				//##(0)清除外部中断标志
    enable_interrupts(INT_EXT3);                        //##(1)使能中断
    #asm nop #endasm
    ext_int_edge(INT_EXT4,H_TO_L);                      //##(0)"SENSOR2"下降沿触发中断或者唤醒【EXINT4】
    INTCON2 |= 0x0010;                                  //##(0)编译器问题需要声明寄存器重设位
    clear_interrupt(INT_EXT4);				//##(0)清除外部中断标志 
    enable_interrupts(INT_EXT4);                        //##(1)使能中断    	
}
/*###############################################################################################################################
# 函数名 :  void main(void)                                                                                                     #
# 功  能 :  主函数                                                                                                              #
# 参  数 :  NONE                                                                                                                #
# 说  明 :  NONE                                                                                                                #
###############################################################################################################################*/
void MeasureID_Process(void) {
    static  uint8_t read_count, StateMachine = 0;
    static  uint8_t ChgCounter, ExoCounter, rmvCounter, ErrCounter;
    static  uint8_t lastResult = 0xFF;         //##(0)上一次ADC分类结果
    static uint16_t timeout;
           uint16_t SYSADC;
            uint8_t curResult;
//##(0)执行状态机
    switch(StateMachine) {
        case 0x00:
             SYSBIAS_ON;
             timeout = regs.time10ms;
             StateMachine = 0x01;
             break;
        case 0x01:
             if((regs.time10ms - timeout)<50/10) break;		//##(0)50ms稳定上拉
             timeout = regs.time10ms;
             read_count = 0u;
             ChgCounter = ExoCounter = 0u;
             ErrCounter = rmvCounter = 0u;
             lastResult = 0xFF;					//##(0)初始化为无效值
             StateMachine = 0x02;
             break;
        case 0x02:
             if((regs.time10ms - timeout)<10/10) break;		//##(0)10ms测一次
             timeout = regs.time10ms;
             SYSADC = Measure_InnerADC(sys_adc, 5);
//##(0)分类当前读数
                  if(SYSADC>2300 && SYSADC<2800) curResult = IDCHG;
             else if(SYSADC>1500 && SYSADC<2000) curResult = IDEXO;
             else if(SYSADC>3000)                curResult = IDRMV;
             else                                curResult = IDERR;
//##(0)检测到ID跳变 → 重置计数器，只统计切换后的读数
             if(curResult!=lastResult && lastResult!=0xFF) {
		StateMachine = 0x01; break;					//##(0)重新来过
             }
             lastResult = curResult;						//##(0)更新基点
             if(curResult == IDCHG) ChgCounter++;                               //##(0)累积计数
             if(curResult == IDEXO) ExoCounter++;
             if(curResult == IDRMV) rmvCounter++;
             if(curResult == IDERR) ErrCounter++;
			 
             if(++read_count >= 10u) {						//##(0)10次读完判断接入的"ID"电阻处于何种
                      if(ChgCounter>6u) regs.flags.IDType = IDCHG;
                 else if(ExoCounter>6u) regs.flags.IDType = IDEXO;
                 else if(rmvCounter>6u) regs.flags.IDType = IDRMV;
                 else                   regs.flags.IDType = IDERR;		//## 都不达标→报错
                 SYSBIAS_OFF;
                 StateMachine = 0x00;
             }
             break;
        default:
             StateMachine = 0x00;
             regs.flags.IDType = IDRMV;
             SYSBIAS_OFF;
             break;
    }
}
/*###############################################################################################################################
# 声明结束                                                                                                                      #
###############################################################################################################################*/
#ifdef	__cplusplus
}
#endif
#endif	

