#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_gpio.h"

int main (void)
{
    CMU_ClockEnable(cmuClock_HFPER, true);
}