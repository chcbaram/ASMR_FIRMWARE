#include "ap.h"




typedef struct
{
  uint32_t magic_number;
  uint32_t data;
  uint32_t data_inv;
} noinit_data_t;

__attribute__((section(".noinit"))) noinit_data_t reset_count;


void apInit(void)
{
  cliOpen(_DEF_UART1, 115200);

  if (reset_count.magic_number != 0x5555AAAA || 
      reset_count.data != ~reset_count.data_inv)
  {
    // 초기화
    reset_count.magic_number = 0x5555AAAA;
    reset_count.data = 0;
    reset_count.data_inv = ~reset_count.data;
  }

  reset_count.data++;
  reset_count.data_inv = ~reset_count.data;

  cliPrintf("Reset Count : %d\n", reset_count.data);
}

void apMain(void)
{
  uint32_t pre_time;


  pre_time = millis();
  while(1)
  {
    if (millis()-pre_time >= 500)
    {
      pre_time = millis();
      ledToggle(_DEF_LED1);
      ledToggle(_DEF_LED2);
      ledToggle(_DEF_LED3);
    }    

    cliMain();
  }

}
