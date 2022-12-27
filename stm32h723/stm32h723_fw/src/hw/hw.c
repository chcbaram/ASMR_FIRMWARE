#include "hw.h"


typedef struct  
{
  uint32_t magic_number;
  char version_str[32];
} version_info_t;



__attribute__((section(".tag"))) version_info_t version_info = 
{
  .magic_number = 0x5555AAAA,
  .version_str = "V221117R1"
};

__attribute__((section(".noinit"))) fault_log_t fault_log;


const version_info_t *p_version_info = (version_info_t *)0x08000400;


extern uint32_t _fw_flash_begin;
extern uint32_t _fw_flash_end;



bool hwInit(void)
{
  bspInit();

  cliInit();
  logInit();
  ledInit();
  uartInit();
  logOpen(_DEF_UART1, 115200);
  
  logPrintf("\r\n[ Firmware Begin... ]\r\n");
  logPrintf("Booting..Name \t\t: %s\r\n", _DEF_BOARD_NAME);
  logPrintf("Booting..Ver  \t\t: %s\r\n", _DEF_FIRMWATRE_VERSION);  
  logPrintf("\n");

  logPrintf("FW Addr Begin \t\t: 0x%X\r\n", &_fw_flash_begin);  
  logPrintf("FW Addr End   \t\t: 0x%X\r\n", &_fw_flash_end);  
  logPrintf("FW Addr Size  \t\t: %d bytes\r\n", (uint32_t)&_fw_flash_end - (uint32_t)&_fw_flash_begin);  
  logPrintf("\n");

  if (p_version_info->magic_number == 0x5555AAAA)
  {
    logPrintf("FW Version    \t\t: %s\n", p_version_info->version_str);
  }

  if (fault_log.magic_number == 0x5555AAAA)
  {
    fault_log.magic_number = 0;

    logPrintf("Fault Message\n");
    logPrintf("  Type : %d\n",     fault_log.type);
    logPrintf("  R0   : 0x%08X\n", fault_log.REG_R0);
    logPrintf("  R1   : 0x%08X\n", fault_log.REG_R1);
    logPrintf("  R2   : 0x%08X\n", fault_log.REG_R2);
    logPrintf("  R3   : 0x%08X\n", fault_log.REG_R3);
    logPrintf("  R12  : 0x%08X\n", fault_log.REG_R12);
    logPrintf("  LR   : 0x%08X\n", fault_log.REG_LR);
    logPrintf("  PC   : 0x%08X\n", fault_log.REG_PC);
    logPrintf("  PSR  : 0x%08X\n", fault_log.REG_PSR);
  }
  return true;
}