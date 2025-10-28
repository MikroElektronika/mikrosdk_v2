#include <mcu.h>
#include <core_header.h>

#ifndef SysTick_IRQn
    #define SysTick_IRQn -1
#endif

// CMSIS Core macros.
#define SCS_BASE (0xE000E000UL)         /*!< System Control Space Base Address */

#define SCB_BASE (SCS_BASE + 0x0D00UL)  /*!< System Control Block Base Address */
#define SCB ((SCB_Type *)SCB_BASE)      /*!< SCB configuration struct */

#define NVIC_BASE (SCS_BASE + 0x0100UL) /*!< NVIC Base Address */
#define NVIC ((NVIC_Type *)NVIC_BASE)   /*!< NVIC configuration struct */

#define SysTick_BASE (SCS_BASE + 0x0010UL)     /*!< SysTick Base Address */
#define SysTick ((SysTick_Type *)SysTick_BASE) /*!< SysTick configuration struct */

// SysTick settings.
#define TICK_FREQ_10HZ 100U
#define TICK_FREQ_100HZ 10U
#define TICK_FREQ_1KHZ 1U
#define TICK_FREQ_DEFAULT TICK_FREQ_1KHZ
#define GET_TICK_NUMBER_PER_CLOCK ((FOSC_KHZ_VALUE*1000UL) / (1000U / TICK_FREQ_DEFAULT))

// Systick API prototypes.
static inline uint32_t sysTickConfig(uint32_t ticks) __attribute__((always_inline));
static inline void sysTickInit(uint8_t priority) __attribute__((always_inline));

/**
  \brief  Structure type to access the System Control Block (SCB).
 */
typedef struct {
    volatile uint32_t CPUID;                  /*!< Offset: 0x000 (R/ )  CPUID Base Register */
    volatile uint32_t ICSR;                   /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
    volatile uint32_t VTOR;                   /*!< Offset: 0x008 (R/W)  Vector Table Offset Register */
    volatile uint32_t AIRCR;                  /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
    volatile uint32_t SCR;                    /*!< Offset: 0x010 (R/W)  System Control Register */
    volatile uint32_t CCR;                    /*!< Offset: 0x014 (R/W)  Configuration Control Register */
    volatile uint8_t  SHP[12U];               /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
    volatile uint32_t SHCSR;                  /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
    volatile uint32_t CFSR;                   /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register */
    volatile uint32_t HFSR;                   /*!< Offset: 0x02C (R/W)  HardFault Status Register */
    volatile uint32_t DFSR;                   /*!< Offset: 0x030 (R/W)  Debug Fault Status Register */
    volatile uint32_t MMFAR;                  /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register */
    volatile uint32_t BFAR;                   /*!< Offset: 0x038 (R/W)  BusFault Address Register */
    volatile uint32_t AFSR;                   /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register */
    volatile uint32_t PFR[2U];                /*!< Offset: 0x040 (R/ )  Processor Feature Register */
    volatile uint32_t DFR;                    /*!< Offset: 0x048 (R/ )  Debug Feature Register */
    volatile uint32_t ADR;                    /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register */
    volatile uint32_t MMFR[4U];               /*!< Offset: 0x050 (R/ )  Memory Model Feature Register */
    volatile uint32_t ISAR[5U];               /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register */
             uint32_t RESERVED0[5U];
    volatile uint32_t CPACR;                  /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register */
} SCB_Type;

/**
  \brief  Structure type to access the Nested Vectored Interrupt Controller (NVIC).
 */
typedef struct {
  volatile uint32_t ISER[8U];               /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
           uint32_t RESERVED0[24U];
  volatile uint32_t ICER[8U];               /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
           uint32_t RESERVED1[24U];
  volatile uint32_t ISPR[8U];               /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
           uint32_t RESERVED2[24U];
  volatile uint32_t ICPR[8U];               /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
           uint32_t RESERVED3[24U];
  volatile uint32_t IABR[8U];               /*!< Offset: 0x200 (R/W)  Interrupt Active bit Register */
           uint32_t RESERVED4[56U];
  volatile uint8_t  IP[240U];               /*!< Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) */
           uint32_t RESERVED5[644U];
  volatile uint32_t STIR;                   /*!< Offset: 0xE00 ( /W)  Software Trigger Interrupt Register */
} NVIC_Type;

/**
  \brief  Structure type to access the System Timer (SysTick).
 */
typedef struct {
    volatile uint32_t CTRL;                   /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
    volatile uint32_t LOAD;                   /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register */
    volatile uint32_t VAL;                    /*!< Offset: 0x008 (R/W)  SysTick Current Value Register */
    volatile uint32_t CALIB;                  /*!< Offset: 0x00C (R/ )  SysTick Calibration Register */
} SysTick_Type;

__attribute__((always_inline)) static uint32_t getEncodedPriorityGrouping(uint8_t preemptPriority, uint8_t subPriority) {
    uint32_t prioritygroup = ((uint32_t)((SCB->AIRCR & (7UL << 8U)) >> 8U));
    uint32_t priorityGroupTmp = (prioritygroup & (uint32_t)0x07UL); /* only values 0..7 are used */
    uint32_t preemptPriorityBits = ((7UL - priorityGroupTmp) > (uint32_t)(4U)) ? (uint32_t)(4U) : (uint32_t)(7UL - priorityGroupTmp);
    uint32_t subPriorityBits = ((priorityGroupTmp + (uint32_t)(4U)) < (uint32_t)7UL) ? (uint32_t)0UL : (uint32_t)((priorityGroupTmp - 7UL) + (uint32_t)(4U));

    return (
                ((preemptPriority & (uint32_t)((1UL << (preemptPriorityBits)) - 1UL)) << subPriorityBits) |
                ((subPriority     & (uint32_t)((1UL << (subPriorityBits    )) - 1UL)))
            );
}

static inline uint32_t sysTickConfig(uint32_t ticks) {
    if ((ticks - 1UL) > 0xFFFFFFUL)  // Reload value impossible.
        return (1UL);                                                   

    // Set reload register.
    SysTick->LOAD = (uint32_t)(ticks - 1UL);   
    // Set priority level MAX.
    SCB->SHP[(((uint32_t)SysTick_IRQn) & 0xFUL)-4UL] = (uint8_t)((15 << (8U - 4U)) & (uint32_t)0xFFUL);
    // Load the SysTick Counter Value.
    SysTick->VAL = 0UL;                                             
    // Enable SysTick IRQ and SysTick Timer.
    SysTick->CTRL = 0x7U;  
    
    return (0UL);
}

static inline void systicInit(uint8_t priority) {
    if (!sysTickConfig(GET_TICK_NUMBER_PER_CLOCK)) {
    SCB->SHP[(((uint32_t)SysTick_IRQn) & 0xFUL)-4UL] = (uint8_t)(((uint32_t)getEncodedPriorityGrouping(priority, 0) << (8U - 4U)) & (uint32_t)0xFFUL);
    } else {
        while(1);
    }
}

static inline void timerInit() {
    systicInit(15);
}

