#include "sound.h"

uint8_t SND[7][6] = {  {0x7e, 0x04, 0x41, 0x00, 0x01, 0xef},
                       {0x7e, 0x04, 0x41, 0x00, 0x02, 0xef},
                       {0x7e, 0x04, 0x41, 0x00, 0x03, 0xef},
                       {0x7e, 0x04, 0x41, 0x00, 0x04, 0xef},
                       {0x7e, 0x04, 0x41, 0x00, 0x05, 0xef},
                       {0x7e, 0x04, 0x41, 0x00, 0x06, 0xef},
                       {0x7e, 0x04, 0x41, 0x00, 0x07, 0xef}
                    };
uint8_t VOL[5][5]  = { {0x7e, 0x03, 0x31,  0, 0xef},
                       {0x7e, 0x03, 0x31,  7, 0xef},
                       {0x7e, 0x03, 0x31, 15, 0xef},                              
                       {0x7e, 0x03, 0x31, 22, 0xef},                              
                       {0x7e, 0x03, 0x31, 30, 0xef},                             
                      };

void SND_SelectID(uint8_t SndID)
{
   uint8_t id  = 0;
   if(SndID < SND_ID_MIN)
      id  = SND_ID_MIN;
   else if(SndID > SND_ID_MAX)
      id  = SND_ID_MAX;
   else 
      id  = SndID;
      
   UART_Send(UART_2, SND[SndID-1], 6, BLOCKING);
}


void SND_SetVol(uint8_t SndVol)
{
   uint8_t vol  = 0;
   if(SndVol < SND_VOL_MIN)
      vol  = SND_VOL_MIN;
   else if(SndVol > SND_VOL_MAX)
      vol  = SND_VOL_MAX;
   else 
      vol  = SndVol;
      
   UART_Send(UART_2, VOL[vol], 5, BLOCKING);
}


void SND_Stop()
{
   UART_SendByte(UART_2, 0x7e);
   UART_SendByte(UART_2, 0x02);
   UART_SendByte(UART_2, 0x0e);
   UART_SendByte(UART_2, 0xef);
}

void SND_Play()
{
   UART_SendByte(UART_2, 0x7e);
   UART_SendByte(UART_2, 0x01);
   UART_SendByte(UART_2, 0x0e);
   UART_SendByte(UART_2, 0xef);
}
