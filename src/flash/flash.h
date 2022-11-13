#ifndef FLASH_H
#define FLASH_H

#include "em_msc.h"

uint32_t flash_init(void);
int flash_write(uint32_t *address, const void *data, uint32_t numBytes);
int flash_erase_page(uint32_t *address);
uint32_t flash_deinit(void);
uint32_t flash_read_address(uint32_t * address);

#endif