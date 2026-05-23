/**
 * @file  system_stm32f4xx.c
 * @brief System clock configuration for STM32F407VG.
 *
 * Configures the PLL to run the core at 168 MHz from the external 8 MHz
 * HSE crystal (typical on the STM32F4-Discovery board).
 *
 * Clock tree (target):
 *   SYSCLK  = 168 MHz  (PLL, HSE / M = 8, N = 336, P = 2)
 *   HCLK    = 168 MHz  (AHB prescaler = 1)
 *   PCLK1   =  42 MHz  (APB1 prescaler = 4)
 *   PCLK2   =  84 MHz  (APB2 prescaler = 2)
 */

#include "stm32f4xx.h"

/* HSE crystal frequency in Hz — STM32F4-Discovery uses 8 MHz */
#define HSE_VALUE    ((uint32_t)8000000U)

uint32_t SystemCoreClock = 168000000U;

static void set_flash_latency(uint32_t hclk_mhz)
{
    /* FLASH_LATENCY_5WS for 168 MHz on STM32F40x */
    FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN | FLASH_ACR_DCEN
               | FLASH_LATENCY_5WS;
}

static void clock_init(void)
{
    /* 1. Enable HSE and wait for it to stabilise */
    RCC->CR |= RCC_CR_HSEON;
    while ((RCC->CR & RCC_CR_HSERDY) == 0) { __asm volatile ("nop"); }

    /* 2. Configure the main PLL:
     *    PLL_VCO = HSE / M * N  = 8 / 8 * 336 = 336 MHz
     *    SYSCLK = PLL_VCO / P   = 336 / 2   = 168 MHz
     */
    RCC->PLLCFGR = (8U << RCC_PLLCFGR_PLLM_Pos)   /* M = 8   */
                 | (336U << RCC_PLLCFGR_PLLN_Pos)  /* N = 336 */
                 | (0U  << RCC_PLLCFGR_PLLP_Pos)   /* P = 2   */
                 | RCC_PLLCFGR_PLLSRC_HSE          /* HSE source */
                 | (7U  << RCC_PLLCFGR_PLLQ_Pos);  /* Q = 7   */

    /* 3. Set flash latency before switching to PLL */
    set_flash_latency(168);

    /* 4. Enable PLL and wait */
    RCC->CR |= RCC_CR_PLLON;
    while ((RCC->CR & RCC_CR_PLLRDY) == 0) { __asm volatile ("nop"); }

    /* 5. Select PLL as SYSCLK source */
    RCC->CFGR = (RCC_CFGR_SW_PLL << RCC_CFGR_SW_Pos);
    while ((RCC->CFGR & RCC_CFGR_SWS) != (RCC_CFGR_SWS_PLL << RCC_CFGR_SWS_Pos)) {
        __asm volatile ("nop");
    }

    /* 6. APB1 prescaler = 4 (42 MHz), APB2 prescaler = 2 (84 MHz) */
    RCC->CFGR |= (RCC_CFGR_PPRE1_DIV4 | RCC_CFGR_PPRE2_DIV2);

    SystemCoreClock = 168000000U;
}

/**
 * @brief Called by the startup code before main().
 */
void SystemInit(void)
{
    clock_init();

    /* Configure FPU (Cortex-M4 has a single-precision FPU) */
    SCB->CPACR |= (0xF << 20);   /* CP10 + CP11 = full access */
}

/**
 * @brief Update SystemCoreClock variable — call after any clock change.
 */
void SystemCoreClockUpdate(void)
{
    /* Simplified: assumes PLL is always the source at 168 MHz */
    SystemCoreClock = 168000000U;
}
