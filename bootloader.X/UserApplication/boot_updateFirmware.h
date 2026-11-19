/*###############################################################################################################################
# 文件名称 :  BurnIn_FirmwareLoader.h                                                                                           #
# 公司名称 :  TOTEX Technology, Inc.                                                                                            #
# 芯片型号 :  PIC24FJ128GL302                                                                                                   #
# 编译  器 :  ccs compiler v5.092                                                                                               #
# 作    者 :  BenZhang                                                                                                          #
# 编写日期 :  2025/10/20                                                                                                        #
# 版本  号 :  固件升级函数模块                                                                                                  #
# 说明     :  一个INHX32格式的.HEX文件的每一行都是下面这种格式 ： :BBAAAATTHHHH....HHHHCC                                       #
#                  即开始是9个字符组成的前缀“:BBAAAATT”，加上若干个4字符的“HHHH”数据，结尾是2个字符的校验字“CC” 。        #
#                  这里所说的“字符”是指组成文件的ASCII字符，而一个16进制“字节”必须用两个“字符”表示。                      #
#                  各个部分的意义是：                                                                                           #
#                                    : 一行的开始符。                                                                           #
#                                   BB 数据部分的字节数，即“HHHH”部分的字节数。                                               #
#                                 AAAA 代码开始存放的地址的2倍。仅在代码数据行中有意义，在其余两种类型的                        #
#                                   TT 行的类型。                                                                               #
#                                               00 代码数据行                                                                   #
#                                               01 结尾标志行                                                                   #
#                                               02 段地址定位行（PIC16F87X单片机的.HEX文件中没有用到）                          #
#                                               04 线性地址定位行                                                               #
#                                 HHHH 在代码数据行中，表示一条14-bit的指令代码，其中低字节在前，高字节在后 ，                  #
#                                   CC 校验字。校验规则是，本行中前面所有的字节（两个字符）表示的16进制数相加 ，再加上CC表示的  #
#                                     16进制数，所得的和必须是256的整数倍，即用16进制表示时末尾两位都为0。                      #
#################################################################################################################################
#                                                                                                                               #
# Memory Map                                                                                                                    #
#    _______________                                                                                                            #
#   |    0x0000     | --> 芯片复位地址                                                                                          #
#   |               |                                                                                                           #
#   |    0x0004     | --> 中断地址(高优先级)                                                                                    #
#   |               |                                                                                                           #
#   |    0x0014     | --> 中断地址(低优先级)                                                                                    #
#   |               |                                                                                                           #
#   |  Boot Block   |   (this program)                                                                                          #
#   |               |                                                                                                           #
#   |    0x4000     | --> 应用程序开始地址                                                                                      #
#   |    0x1008     | --> 应用程序中断地址(高优先级)                                                                            #
#   |    0x1018     | --> 应用程序中断地址(低优先级)                                                                            #
#   |       |       |                                                                                                           #
#   |               |                                                                                                           #
#   |  Code Space   |   User program space                                                                                      #
#   |               |                                                                                                           #
#   |       |       |                                                                                                           #
#   |               |                                                                                                           #
#   | End of Flash  |                                                                                                           #
#   |_______________|                                                                                                           #
#                                                                                                                               #
###############################################################################################################################*/
#ifndef BOOT_UPDATEFIRMWARE_H
#define	BOOT_UPDATEFIRMWARE_H

/*###############################################################################################################################
#  库文件                                                                                                                       #
###############################################################################################################################*/
#include "boot_config.h"

/*###############################################################################################################################
#  应用声明开始                                                                                                                 #
###############################################################################################################################*/
#ifdef	__cplusplus
extern "C" {
#endif
/*###############################################################################################################################
#  函数声明                                                                                                                     #
###############################################################################################################################*/
uint8_t AsciiToHex(char *s);
uint16_t crc16_xmodoem(uint8_t *buf, uint16_t crc_default, uint16_t length);
uint8_t check_checksum(uint8_t *string, uint8_t start_string, uint8_t end_string);
void write_E263HEGBK(color *color);
void Turn_off_all_LEDs(void); 
BOOLEAN checking_updata_status(void);
/*###############################################################################################################################
# 函数名 :  unsigned char atoi_b16(char *s)                                                                                     #
# 功  能 :  ASCII 转换成 HEX                                                                                                    #
# 参  数 :  S = 字符串首地址                                                                                                    #
# 说  明 :  result = 转换后的数                                                                                                 #
###############################################################################################################################*/
uint8_t AsciiToHex(char *s) { 
    uint8_t result = 0, i;
    for(i = 0; i < 2; i++, s++) {
        result = (*s >= 'A')?  16 * result + (*s) - 'A' + 10 : 16 * result + (*s) - '0';
    }
    return(result);
}
/*###############################################################################################################################
# 函数名 : uint16_t crc16(uint8_t *data_p, uint16_t length)                                                                     #
# 功  能 : CRC16 校验码计算                                                                                                     #
# 参  数 : NONE                                                                                                                 #
# 说  明 : NONE                                                                                                                 #
###############################################################################################################################*/
uint16_t crc16_xmodoem(uint8_t *buf, uint16_t crc_default, uint16_t length) {
     uint8_t i;
    uint16_t crc = crc_default;
    while(length--) {
        crc ^= (uint16_t)*buf++ << 8;
        for(i=0; i<8; ++i) {
            (crc & 0x8000)? (crc=(crc<<1)^0x1021):(crc<<=1);
        }
    }
    return(crc);
} 

/*###############################################################################################################################
# 函数名 :  BOOLEAN checking_updata_status(void)                                                                                #
# 功  能 :  检查更新状态                                                                                                        #
# 参  数 :  NONE                                                                                                                #
# 说  明 :  ROM地址[0x3C00]~[0x3C08]内容 = 0x6868686868686868(升级完成标识符)                                                   #
###############################################################################################################################*/
BOOLEAN checking_updata_status(void) { 
    bufferU32 updata_bootloader;
      uint8_t buff[8];
//##(0)读取保存在FLASH中的标识编码
    read_program_memory(updata_address, buff, sizeof(buff));
//##(1)提取出更新完成标识编码
    updata_bootloader.U8[0] = buff[0];
    updata_bootloader.U8[1] = buff[1];
    updata_bootloader.U8[2] = buff[2];
//##(0)如果标识码不对则返回"1"
    if(updata_bootloader.U32!=0x686868) return(TRUE);
////##(0)提取出更新完成标识编码
//    updata_bootloader.U8[0] = buff[4];
//    updata_bootloader.U8[1] = buff[5];
//    updata_bootloader.U8[2] = buff[6];
//    if(updata_bootloader.U32!=0x686868) return(TRUE);
//##(0)标识码正确则认为更新完成,返回"0"
    return(FALSE);
}

/*###############################################################################################################################
# 函数名 :  unsigned char check_checksum(unsigned char *hex, unsigned char reclen)                                              #
# 功  能 :  计算校验位                                                                                                          #
# 参  数 :  START_STR = 启起字符地址     END_STR = 结束字符地址    *STR = 字符指针                                              #
# 说  明 :  checksum = 校验码                                                                                                   #
###############################################################################################################################*/
uint8_t check_checksum(uint8_t *string, uint8_t start_string, uint8_t end_string) {
    unsigned char checksum = 0;
    unsigned char i;
//##(0)添加的所有字节值,包括校验数据
    for(i=start_string; i<end_string; i+=2) {
      checksum += AsciiToHex(&string[i]);
    }
    checksum = 0xFF - checksum + 1;
//##(1)返回计算后的校验码 
    return(checksum);
}

/*###############################################################################################################################
# 函数名  :  void resetRGBLED(void)                                                                                             #
# 功  能  :  发送复位RGB信号                                                                                                    #
# 参  数  :  NONE                                                                                                               #
# 说  明  :  按照资料上时许写入(从数据最低位写起)                                                                               #
###############################################################################################################################*/
void resetRGBLED(void) {
    PUST_0;
    delay_us(250);
}
/*###############################################################################################################################
# 函数名  :  void write_E263HEGBK(color *color)                                                                                 #
# 功  能  :  写LED驱动芯片数据（采用曼彻斯特编码,详细参考芯片资料）                                                             #
# 参  数  :  NONE                                                                                                               #
# 说  明  :  按照资料上时许写入(从数据最低位写起)                                                                               #
###############################################################################################################################*/
void write_E263HEGBK(color *color) {
    uint8_t txh_time, txl_time;                 	//##(0)高电平/低电平时间,数据 
    uint8_t bits;                                   //##(0)字节/数据位
//##(0)连续发送24位数据到驱动器芯片中
    for(bits = 0; bits < 24; bits++) {              //##(0)连续写入24位颜色数据,顺序 B->G->R 
        if(!bit_test(color->word.U32,bits)) {       //##(0)判断数据当前循环位是"0"或者"1"?       
            txh_time = T0H;                         //##(0)发送"0"高电平延时时间
            txl_time = T0L;                         //##(0)发送"0"低电平延时时间
        }else{
            txh_time = T1H;                         //##(0)发送"1"高电平延时时间
            txl_time = T1L;                         //##(0)发送"1"低电平延时时间
	}
        PUST_1;                                     //##(2)发送一个bit时序
        delay_cycles(txh_time);                     //##(3)高电平延时
        PUST_0;
        delay_cycles(txl_time);                     //##(4)低电平延时 
    }	
}

/*###############################################################################################################################
# 函数名  :  void Turn_off_all_LEDs(void)                                                                                       #
# 功  能  :  关闭全部LED                                                                                                        #
# 参  数  :  NONE                                                                                                               #
# 说  明  :  NONE                                                                                                               #
###############################################################################################################################*/
void Turn_off_all_LEDs(void) {
    color reset_data;       
//##(0)三基色数据全为"0"
    reset_data.word.U32 = BLACK;                    //##(0)黑色数据（关闭LED）
//##(0)全部LED颜色全部清零,一次性写入8个LED颜色数据
    for(uint8_t i=0; i<8; i++) {                    //##(0)
        write_E263HEGBK(&reset_data);               //##(0)写入一个LED三基色数据
    }    
}  
/*###############################################################################################################################
# 函数名  :  void APPLICATION_ERASE(void)                                                                                       #
# 功  能  :  擦除应用区域                                                                                                       #
# 参  数  :  NONE                                                                                                               #
# 说  明  :  NONE                                                                                                               #
###############################################################################################################################*/
void application_Erase_process(void) {                              
  	uint32_t StartAddress,EndAddress,EraseSizePage,i;
//##(0)如果没有擦除使能或者擦除没有完成则退出
    if(!boot.bits.EraseEnableROM || boot.bits.EraseFinishROM) return;           
//##(0)准备擦除芯片
    StartAddress = APPLICATION_START;               
      EndAddress = APPLICATION_END - 0x400;			
   EraseSizePage = getenv("FLASH_ERASE_SIZE")/2;	
//##(0)连续擦除芯片扇区 
    for(i=StartAddress; i<EndAddress; i+=EraseSizePage) {
        restart_wdt();
        erase_program_memory(i); 
    }   
//##(0)擦除完成则将标志清零,并设置完成标志
    boot.bits.EraseFinishROM = true;      
}

/*###############################################################################################################################
# 函数名 :  void ProgramingProcessShow(void)                                                                                    #
# 功  能 :  编程过程显示状态(紫色跑马灯显示)                                                                                    #
# 参  数 :  NONE                                                                                                                #
# 说  明 :  NONE                                                                                                                #
###############################################################################################################################*/
void ProgramingProcessShow(void) {
    uint8_t bytes;
    color color_data;
//##(0)查表显示当前状态,如果超出跑马灯结束则重新开始
    if(++boot.LEDsLocation>=16) boot.LEDsLocation = 0; 
//##(0)一次性显示8个LED
    for(bytes=0; bytes<8; bytes++) {                                            
        color_data.word.U32 = MarqueeLeds_Tab[boot.LEDsLocation][bytes];              
        write_E263HEGBK(&color_data);                                       
    }
}

/*###############################################################################################################################
# 函数名 :  void ProgramingStatusShow(void)                                                                                     #
# 功  能 :  编程各种状态显示(失败/成功)                                                                                         #
# 参  数 :  NONE                                                                                                                #
# 说  明 :  NONE                                                                                                                #
###############################################################################################################################*/
void ProgramingStatusShow(color color_data) {
    uint8_t bytes;
//##(0)一次写入8个LED三基色数据     
    for(bytes=0; bytes<8; bytes++) {                                                        
        write_E263HEGBK(&color_data);                                         
    } 
}

/*###############################################################################################################################
# 函数名  :  static void Eusart_Receive_Task(Eusart_buff *Eusart)                                                               #
# 功  能  :  串口接收数据任务                                                                                                   #
# 参  数  :  NONE                                                                                                               #
# 说  明  :  NONE                                                                                                               #
###############################################################################################################################*/
void Receive_CodePacket_Task(void) {
    uint8_t rec_buffer;                                         //##(0)接收数据缓冲器
                                                                //##(0)如果接收到数据
    if(interrupt_active(INT_RDA)) {					
        rec_buffer = fgetc(rs485);                              //##(0)将接收到的数据拷贝到暂存器中,读取接收缓冲器则将中断标志清零
        switch(rec_buffer) {
            case '#' :
                 boot.bits.receiveFinish = false;               //##(0)接收数据包完成标志清零
                 boot.bits.receiveStart  = true;                //##(0)设置开始接收数据包
                 boot.buffidx = 0x00;                           //##(0)数据包字节索引清零
                 memset(boot.buffer,0x00,sizeof(boot.buffer));  //##(0)将缓冲区数组清零
                 break;
            case '\r':
                if(boot.bits.receiveStart == false) break;      //##(0)如果没有收到同步码'#'则返回
                if(boot.buffidx < 0x06U) break;                 //##(0)收到同步码但是数据字节数不够则返回
                boot.bits.receiveFinish = true;                 //##(0)接收数据包正确则设置接受数据包完成标志
                boot.bits.receiveStart  = false;                //##(0)开始接收数据包标志清零 
                break;        
        } 
        boot.buffer[boot.buffidx++] = rec_buffer;               //##(0)接收数据送入接收保存数组中
    }      
}  
  
/*###############################################################################################################################
# 函数名  :  static void bootloader_UserApplication(void)                                                                       #
# 功  能  :  BOOTLOADER 函数                                                                                                    #
# 参  数  :  NONE                                                                                                               #
# 说  明  :  NONE     01234567  8                                                                                               #
# 例  子  ：          #2B,AC,:  10     FEE0    00       F2CF36FBF29EF3CAAAFFF2CAA9FFA69C    84                                  #
#                             字节数   地址  行类型            有效数据                   校验码                                #
###############################################################################################################################*/
void bootloader_UserApplication(void) {
    uint8_t usart_address, usart_command,checksum,code_type,i,y,updata_status[8];
    uint8_t code[40]={0};
    static uint8_t updateShowTime;
   uint32_t waddr;
//##(0)执行串口接收数据任务并判断是否接收数据完成 ? 如果接收不完成则启动串口超时
    receiver;
    Receive_CodePacket_Task();
//##(0)判断是否接收完成数据,没有接收完成则直接退出
    if(boot.bits.receiveFinish == false)  return;  
    boot.bits.receiveFinish = false;
//##(0)先判断数据包的数据是否符合包格式
    if(boot.buffer[0] != '#' || boot.buffer[3] != ',') return;
//##(0)提前命令和串口地址
    usart_address = AsciiToHex((char*)&boot.buffer[1]);
    usart_command = AsciiToHex((char*)&boot.buffer[4]);	
//##(4)根据命令执行相应操作
    transmission; 
    delay_ms(1);
    switch(usart_command) {
//##(4.00)获取基本系统信息
	case 0xA0:
             fprintf(rs485, "@%02x,Bootloader Program,v1.00,xxxxxx,%s\r", usart_address, &CompilationDate);
             break;
	case 0xA5:
             fprintf(rs485,"@%02x,FFFF,FFFF,FFFF,FFFF\r", usart_address);
             break;
//##(4.01)获取版本信息版本
	case 0xAD:
             fprintf(rs485,"@%02x,%s\r",usart_address,&FirmwareVersion);
             break;  
//##(4.02)获取应用程序校验码CRC16,获取hex文件校验码(crc16_xmodoem)
	case 0xB0:
             fprintf(rs485,"@%02x,%LX\r",usart_address, boot.code_crc16); 
             break; 
//##(4.03)收到更新代码成功命令(设置标识 0x68686868(升级完成标识符)
	case 0xB1:
             memset(updata_status,0x68,sizeof(updata_status));			//##(0)设置标识 0x686868686868(升级完成标识符)
             erase_program_memory(updata_address);				//##(0)擦除地址0x1A00   
             write_program_memory(updata_address,updata_status,0x08);	
             fprintf(rs485,"@%02x\r",usart_address);		
             break; 
//##(4.04)接收到复位芯片命令
	case 0xAE:
             fprintf(rs485,"@%02x\r",usart_address);
             delay_ms(40);
             reset_cpu();
             break;			  
//##(4.05)擦除代码区域命令
	case 0xAB:
             if(!boot.bits.EraseEnableROM) {
                fprintf(rs485,"@%02x,05\r",usart_address);			//##(0)通知上位机需要的延时时间
                boot.bits.EraseEnableROM = true;                               //##(0)使能擦除
                boot.bits.EraseFinishROM = false;				//##(0)擦除完成标志清零
             }else{
                if(boot.bits.EraseFinishROM) {					//##(0)判断是否擦除完成?
                    fprintf(rs485,"@%02x\r",usart_address);                    //##(0)应答擦除芯片完成信息
                }else{								//##(0)擦除失败
                    fprintf(rs485,"@%02x,00\r",usart_address);                 //##(0)应答擦除芯片失败信息   
                } 
                boot.bits.EraseEnableROM = false;				//##(0)使能擦除标志清零(禁止擦除)
             }
             boot.code_crc16 = 0x0000;						//##(0)初始CRC16校验码（计算整个Hex文档）     
             break;		 
//##(4.06)更新用户代码命令 
	case 0xAC:
             for(y=0,i=8; i<boot.buffidx-1; i+=2)                                           //##(1)计算出这一行的校验码 
                code[y++] = AsciiToHex((char*)&boot.buffer[i]);                             //## 
             boot.code_crc16 = crc16_xmodoem(code, boot.code_crc16,y);                      //##(2)计算出 "crc16_xmodoem" 校验码并保存以便下一次计算
             #asm nop #endasm                                                               //##(3)以下为提取代码数据和命令并更新到FLASH中
             checksum = AsciiToHex((char*)&boot.buffer[boot.buffidx-3]);                    //##(4)提取出本行校验码 最后三个字节开始算起
             boot.checksum = check_checksum((uint8_t*)boot.buffer,0x08,boot.buffidx-3);     //##(5)计算出行代码的校验码   
             if(checksum!=boot.checksum) {
                fprintf(rs485,"@%02x,00\r",usart_address);                          //##(6)应答更新失败信息
                ProgramingStatusShow(RED);                                          //##(0)显示红色状态(更新失败)
                reset_cpu();                                                        //##(0)复位MCU
                break;
             }
             boot.wlength = AsciiToHex((char*)&boot.buffer[8]);                     //##(0)提取数据部分的字节数（字符串9/8） 
             boot.WriteAdress.U8[1] = AsciiToHex((char*)&boot.buffer[10]);          //##(0)提取地址高字节  （字符串11/10）
             boot.WriteAdress.U8[0] = AsciiToHex((char*)&boot.buffer[12]);          //##(0)提取地址高字节  （字符串13/12）
             code_type = AsciiToHex((char*)&boot.buffer[14]);                       //##(0)提取代码行的类型（字符串15/14）
             waddr = boot.WriteAdress.U32 / _ROMW_BPA;                              //##(0)因地址是24位所以除于2 
             memset(code,0x00,sizeof(code));
             for(y=0,i=16; i<boot.buffidx-3; i+=2)                                  //##(0)将接受的有效数据代码转换为 HexCode 
                code[y++] = AsciiToHex((char*)&boot.buffer[i]);                     //##(0)有效数据从代码字符串字符16开始.            
             switch(code_type) {                                                    //##(0)根据行代码类型执行相应操作              
                case 0x04:                                                          //##(0)线性地址定位行
                case 0x02:                                                          //##(0)段地址定位行
                     boot.WriteAdress.U8[3] = AsciiToHex((char*)&boot.buffer[16]);  //##(0)地址高字节
                     boot.WriteAdress.U8[2] = AsciiToHex((char*)&boot.buffer[18]);  //##(0)地址低字节
                     break;
                case 0x01:                                                          //##(0)代码结束行
                     break;
                case 0x00:                                              //##(0)代码数据行 
                     if(waddr<APPLICATION_START) {  
                        fprintf(rs485,"@%2x,02\r",usart_address);       //##(0)应答信息
                        ProgramingStatusShow(RED);                      //##(0)显示红色状态(更新失败)
                        reset_cpu();                                    //##(0)复位MCU
                        break;
                     }
                     #asm nop #endasm                                   //##(0)数据正确和地址匹配则写"FLASH"操作
                     if(waddr > (APPLICATION_END-1)) break;             //##(0)如果地址是写配置位则不操作写,返回
                     #asm nop #endasm
                     if(boot.wlength<=4) { boot.wlength *= 2; }         //##(0)可能是编译器问题导致写字节数低于8个字节作无法写入                    
                     #asm nop #endasm
                     write_program_memory(waddr, code, boot.wlength);   //##(0)将代码数据写入"FLASH"中  //##(0)写入FLASH中
                     #asm nop #endasm
                     if(++updateShowTime>=0x05) {                       //##(0)显示状态(跑马灯),每循环7次则更新一次显示 
                        ProgramingProcessShow(); 
                        updateShowTime = 0;                             //##(0)显示(跑马灯显示)
                     }      
                     break; 
             } 
             fprintf(rs485,"@%02x,01\r",usart_address);			//##(0)更新一行数据正确则应答
             break;
//##(4.07)其它命令则复位MCU
	default:
             fprintf(rs485,"@%02x\r", usart_address);			//##(0)
             break;	
	}
//##(0)重新开启接收
    delay_ms(3);
    receiver;
}

/*###############################################################################################################################
#  应用声明结束                                                                                                                 #
###############################################################################################################################*/
#ifdef	__cplusplus
}
#endif
#endif

