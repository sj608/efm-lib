#ifndef FLASH_H
#define FLASH_H

#include "em_msc.h"

void flash_init(void);
int flash_write(uint32_t *address, const void *data, u_int32_t numBytes);
int flash_erase_page(uint32_t *address);

#endif