// sdram_init.cpp
#include "sdram_init.h"
#include "stm32h7xx.h"

void SDRAM_Init(void) {
    // Enable FMC and GPIO clocks
    __HAL_RCC_FMC_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();

    // Use the correct register for GIGA
    FMC_Bank1_R->BTCR[0] = 0x000030D2;  // Example: configure bank1
    FMC_Bank1_R->BTCR[1] = 0x00000201;  // timing example

    // Delay for FMC clock to stabilize
    for (volatile int i = 0; i < 100000; i++);

    // Minimal SDRAM init sequence (very basic)
    // Normally you would do precharge, auto-refresh, mode register set
    // Here we just enable the bank so LVGL can access it
}
