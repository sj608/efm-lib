#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_usart.h"

volatile uint32_t msTicks = 0;
volatile char rx_char = 0;

char string_1[] = "Hi\r\n";
char string_2[] = "Waiting\r\n";
USART_TypeDef *usart = USART2;

void SysTick_Handler(void)
{
    msTicks++;
}

void Delay(uint32_t dlyTicks)
{
    uint32_t curTicks;
    curTicks = msTicks;
    while((msTicks - curTicks) < dlyTicks);
}

void serial_init();
void send_string(char* tx_buff, uint8_t buff_len);

int main (void)
{
    CMU_ClockEnable(cmuClock_HFPER, true);
    CMU_ClockEnable(cmuClock_GPIO, true);
    CMU_ClockEnable(cmuClock_USART2, true);

    if(SysTick_Config(SystemCoreClock / 1000)){
        while(1);
    }

    serial_init();
    GPIO_PinModeSet(gpioPortC, 0, gpioModePushPull, 0);

    while(1){
        GPIO_PinOutClear(gpioPortC, 0);
        Delay(500);
        GPIO_PinOutSet(gpioPortC, 0);
        Delay(500);
        if(rx_char == 'a'){
            send_string(string_1, (uint8_t)(sizeof(string_1)/sizeof(string_1[0])));
            rx_char = 0;
        }else{
            send_string(string_2, (uint8_t)(sizeof(string_2)/sizeof(string_2[0])));
        }
    }

}

void serial_init()
{
    GPIO_PinModeSet(gpioPortC, 2, gpioModePushPull, 1);
    GPIO_PinModeSet(gpioPortC, 3, gpioModeInput, 0);

    USART_InitAsync_TypeDef init_async = USART_INITASYNC_DEFAULT;

	// Prepare struct for initializing UART in asynchronous mode
	init_async.enable       = usartDisable;   // Don't enable UART upon intialization
	init_async.refFreq      = 0;              // Provide information on reference frequency. When set to 0, the reference frequency is
	init_async.oversampling = usartOVS16;     // Oversampling. Range is 4x, 6x, 8x or 16x, default is 16x
	init_async.databits     = usartDatabits8; // Number of data bits. Range is 4 to 10
	init_async.parity       = usartNoParity;  // Parity mode
	init_async.stopbits     = usartStopbits1; // Number of stop bits. Range is 0 to 2
    init_async.baudrate     = 115200;

    USART_InitAsync(usart, &init_async);

	// Prepare UART Rx and Tx interrupts
	USART_IntClear(usart, _USART_IF_MASK);
	USART_IntEnable(usart, USART_IF_RXDATAV);

	NVIC_ClearPendingIRQ(USART2_RX_IRQn);
	// NVIC_ClearPendingIRQ(USART2_TX_IRQn);
	NVIC_EnableIRQ(USART2_RX_IRQn);
	// NVIC_EnableIRQ(USART2_TX_IRQn);

	NVIC_SetPriority(USART2_RX_IRQn, 0);
	// NVIC_SetPriority(USART2_TX_IRQn, 0);

    usart->ROUTE = USART_ROUTE_RXPEN | USART_ROUTE_TXPEN | _USART_ROUTE_LOCATION_LOC0;

    USART_Enable(usart, usartEnable);
}

void USART2_RX_IRQHandler(void)
{
    USART_IntClear(usart, USART_IF_RXDATAV);
    {
        rx_char = USART_Rx(usart);

    }
}

void send_string(char* tx_buff, uint8_t buff_len)
{
    for (uint8_t i = 0; i<buff_len; i++){
        USART_Tx(usart, *(tx_buff+i));
    }
}
