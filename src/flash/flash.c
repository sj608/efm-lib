#include "flash.h"

uint32_t flash_init(void)
{
    MSC_Init();
    return MSC->LOCK;
}


/*
Return codes for writing/erasing Flash.
typedef enum {
  mscReturnOk          =  0, < Flash write/erase successful. 
  mscReturnInvalidAddr = -1, < Invalid address. Write to an address that is not Flash. 
  mscReturnLocked      = -2, < Flash address is locked. 
  mscReturnTimeOut     = -3, < Timeout while writing to Flash. 
  mscReturnUnaligned   = -4  < Unaligned access to Flash. 
} MSC_Status_TypeDef;

*/
int flash_write(uint32_t *address, const void *data, uint32_t numBytes)
{
    return MSC_WriteWord(address, data, numBytes);
}

int flash_erase_page(uint32_t *address)
{
    return MSC_ErasePage(address);
}

uint32_t flash_deinit(void)
{
    MSC_Deinit();
    return MSC->LOCK;
}