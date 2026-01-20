set(tim_list "")
#############################################################################
## Set Timer Variables and Interrupt handler
#############################################################################
if(${TOOLCHAIN_ID} MATCHES "mchp_xc32")
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/1ms_timer/microchip/pic32)
    list(APPEND tim_list "PIC32_TIMER=1")
    list(APPEND tim_list "CLEAR_FLAG=IFS0bits.T1IF = 0")
    list(APPEND tim_list "CLOCK=${OSC}")
    list(APPEND tim_list "INTERRUPT_ROUTINE=void __attribute__((interrupt(IPL7AUTO), vector(_TIMER_1_VECTOR))) _TIMER_1_HANDLER(void)")
else()
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/1ms_timer/arm)
    list(APPEND tim_list "ARM_TIMER=1")
    list(APPEND tim_list "INTERRUPT_ROUTINE=__attribute__ ((interrupt(\"IRQ\"))) void SysTick_Handler(void)")
    list(APPEND tim_list "CLEAR_FLAG=0")
endif()
