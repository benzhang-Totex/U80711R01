/*###############################################################################################################################
 # 文件名称 ： U85117R01_CONFIG_H.H                                                                                             #
 # 公司名称 :  TOTEX Technology, Inc.                                                                                           #
 # 芯片型号 ： PIC24FJ128GA310                                                                                                  #
 # 编译工具 :  ccs compiler v5.092                                                                                              #
 # 作    者 :  BenZhang                                                                                                         #
 # 编写日期 :  2020/11/20                                                                                                       #
 # 版    本 :  V1.00                                                                                                            #
 ##############################################################################################################################*/
#ifndef __BOOTLOADER_H__
#define __BOOTLOADER_H__

#define _ROMW_BPA 2

#ifndef LOADER_PAGES
 #if getenv("FLASH_ERASE_SIZE") == 128
  #define LOADER_PAGES 19
 #else
  #define LOADER_PAGES 2
 #endif
#endif

#ifndef BOOTLOADER_AT_START
 #define BOOTLOADER_AT_START
#endif

#define PROGRAM_MEMORY_FIND_PAGE_START(address) ((__ADDRESS__)address & ~(((__ADDRESS__)getenv("FLASH_ERASE_SIZE")/2)-(__ADDRESS__)1))

// getenv("PROGRAM_MEMORY") won't return the true size as it removes some things like config bits.
// this define gives true program memory size
#define PROGRAM_MEMORY_SIZE   PROGRAM_MEMORY_FIND_PAGE_START(getenv("PROGRAM_MEMORY")) + (getenv("FLASH_ERASE_SIZE")/2)

#ifdef BOOTLOADER_AT_START
 #define LOADER_SIZE            ((LOADER_PAGES * (getenv("FLASH_ERASE_SIZE")*1)) - 1)
 #define LOADER_END              LOADER_SIZE
 #define LOADER_ADDR             0
 #define APPLICATION_START      (LOADER_END + 1)
 #define APPLICATION_END        (PROGRAM_MEMORY_SIZE-1)
 #define APPLICATION_ISR_START  (LOADER_END + 5)
#else
 #if ((getenv("PROGRAM_MEMORY") % (getenv("FLASH_ERASE_SIZE")/2)) !=0 )
    #define LOADER_SIZE (((getenv("PROGRAM_MEMORY") % (getenv("FLASH_ERASE_SIZE")/2)) - 1) + ((LOADER_PAGES - 1) * (getenv("FLASH_ERASE_SIZE")/2)))
 #else
    #define LOADER_SIZE ((LOADER_PAGES * (getenv("FLASH_ERASE_SIZE")/2)) - 1)
 #endif
 #define LOADER_END         (getenv("PROGRAM_MEMORY") - 1)
 #define LOADER_ADDR        (PROGRAM_MEMORY_SIZE - LOADER_SIZE)
 #define APPLICATION_START   0
 #define APPLICATION_END    (LOADER_ADDR-1)
#endif

#ifndef _bootloader
 #ifdef BOOTLOADER_AT_START
  #build (reset=APPLICATION_START,interrupt=APPLICATION_ISR_START)
 #endif
 #org LOADER_ADDR, LOADER_END {}
#else
 #ifdef BOOTLOADER_AT_START
    #org APPLICATION_START, (getenv("PROGRAM_MEMORY")-1) {}
 #else
    #org 0, APPLICATION_START-1
 #endif
#endif

#endif
/*###############################################################################################################################
#  应用声明结束                                                                                                                 #
###############################################################################################################################*/