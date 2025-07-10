// ------------------------------------------------------------------ INCLUDES
/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#include "mcu.h"
#include "interrupts_mcu.h"
#define PWPR_REGISTER_BASE (* ( volatile uint8_t * )0x40040D03UL)

// Startup file should have this (from bsp_elc.h file)
// void NMI_Handler(void) WEAK_REF_ATTRIBUTE;
// void HardFault_Handler(void) WEAK_REF_ATTRIBUTE;
// void MemManage_Handler(void) WEAK_REF_ATTRIBUTE;
// void BusFault_Handler(void) WEAK_REF_ATTRIBUTE;
// void UsageFault_Handler(void) WEAK_REF_ATTRIBUTE;
// void SecureFault_Handler(void) WEAK_REF_ATTRIBUTE;
// void SVC_Handler(void) WEAK_REF_ATTRIBUTE;
// void DebugMon_Handler(void) WEAK_REF_ATTRIBUTE;
// void PendSV_Handler(void) WEAK_REF_ATTRIBUTE;
// void SysTick_Handler(void) WEAK_REF_ATTRIBUTE;
// void ICU_IRQ0_Handler(void) WEAK_REF_ATTRIBUTE;
// void ICU_IRQ1_Handler(void) WEAK_REF_ATTRIBUTE;
// void ICU_IRQ2_Handler(void) WEAK_REF_ATTRIBUTE;
// void ICU_IRQ3_Handler(void) WEAK_REF_ATTRIBUTE;
// void ICU_IRQ4_Handler(void) WEAK_REF_ATTRIBUTE;
// void ICU_IRQ5_Handler(void) WEAK_REF_ATTRIBUTE;
// void ICU_IRQ6_Handler(void) WEAK_REF_ATTRIBUTE;
// void ICU_IRQ7_Handler(void) WEAK_REF_ATTRIBUTE;
// void ICU_IRQ8_Handler(void) WEAK_REF_ATTRIBUTE;
// void ICU_IRQ9_Handler(void) WEAK_REF_ATTRIBUTE;
// void ICU_IRQ10_Handler(void) WEAK_REF_ATTRIBUTE;
// void ICU_IRQ11_Handler(void) WEAK_REF_ATTRIBUTE;
// void ICU_IRQ12_Handler(void) WEAK_REF_ATTRIBUTE;
// void ICU_IRQ14_Handler(void) WEAK_REF_ATTRIBUTE;
// void ICU_IRQ15_Handler(void) WEAK_REF_ATTRIBUTE;
// void DMAC0_INT_Handler(void) WEAK_REF_ATTRIBUTE;
// void DMAC1_INT_Handler(void) WEAK_REF_ATTRIBUTE;
// void DMAC2_INT_Handler(void) WEAK_REF_ATTRIBUTE;
// void DMAC3_INT_Handler(void) WEAK_REF_ATTRIBUTE;
// void DTC_COMPLETE_Handler(void) WEAK_REF_ATTRIBUTE;
// void DTC_END_Handler(void) WEAK_REF_ATTRIBUTE;
// void ICU_SNOOZE_CANCEL_Handler(void) WEAK_REF_ATTRIBUTE;
// void FCU_FRDYI_Handler(void) WEAK_REF_ATTRIBUTE;
// void LVD_LVD1_Handler(void) WEAK_REF_ATTRIBUTE;
// void LVD_LVD2_Handler(void) WEAK_REF_ATTRIBUTE;
// void LVD_VBATT_Handler(void) WEAK_REF_ATTRIBUTE;
// void CGC_MOSC_STOP_Handler(void) WEAK_REF_ATTRIBUTE;
// void LPM_SNOOZE_REQUEST_Handler(void) WEAK_REF_ATTRIBUTE;
// void AGT0_INT_Handler(void) WEAK_REF_ATTRIBUTE;
// void AGT0_COMPARE_A_Handler(void) WEAK_REF_ATTRIBUTE;
// void AGT0_COMPARE_B_Handler(void) WEAK_REF_ATTRIBUTE;
// void AGT1_INT_Handler(void) WEAK_REF_ATTRIBUTE;
// void AGT1_COMPARE_A_Handler(void) WEAK_REF_ATTRIBUTE;
// void AGT1_COMPARE_B_Handler(void) WEAK_REF_ATTRIBUTE;
// void IWDT_UNDERFLOW_Handler(void) WEAK_REF_ATTRIBUTE;
// void WDT_UNDERFLOW_Handler(void) WEAK_REF_ATTRIBUTE;
// void RTC_ALARM_Handler(void) WEAK_REF_ATTRIBUTE;
// void RTC_PERIOD_Handler(void) WEAK_REF_ATTRIBUTE;
// void RTC_CARRY_Handler(void) WEAK_REF_ATTRIBUTE;
// void ADC0_SCAN_END_Handler(void) WEAK_REF_ATTRIBUTE;
// void ADC0_SCAN_END_B_Handler(void) WEAK_REF_ATTRIBUTE;
// void ADC0_WINDOW_A_Handler(void) WEAK_REF_ATTRIBUTE;
// void ADC0_WINDOW_B_Handler(void) WEAK_REF_ATTRIBUTE;
// void ADC0_COMPARE_MATCH_Handler(void) WEAK_REF_ATTRIBUTE;
// void ADC0_COMPARE_MISMATCH_Handler(void) WEAK_REF_ATTRIBUTE;
// void ACMPLP0_INT_Handler(void) WEAK_REF_ATTRIBUTE;
// void ACMPLP1_INT_Handler(void) WEAK_REF_ATTRIBUTE;
// void USBFS_FIFO_0_Handler(void) WEAK_REF_ATTRIBUTE;
// void USBFS_FIFO_1_Handler(void) WEAK_REF_ATTRIBUTE;
// void USBFS_INT_Handler(void) WEAK_REF_ATTRIBUTE;
// void USBFS_RESUME_Handler(void) WEAK_REF_ATTRIBUTE;
// void IIC0_RXI_Handler(void) WEAK_REF_ATTRIBUTE;
// void IIC0_TXI_Handler(void) WEAK_REF_ATTRIBUTE;
// void IIC0_TEI_Handler(void) WEAK_REF_ATTRIBUTE;
// void IIC0_ERI_Handler(void) WEAK_REF_ATTRIBUTE;
// void IIC0_WUI_Handler(void) WEAK_REF_ATTRIBUTE;
// void IIC1_RXI_Handler(void) WEAK_REF_ATTRIBUTE;
// void IIC1_TXI_Handler(void) WEAK_REF_ATTRIBUTE;
// void IIC1_TEI_Handler(void) WEAK_REF_ATTRIBUTE;
// void IIC1_ERI_Handler(void) WEAK_REF_ATTRIBUTE;
// void SSI0_TXI_Handler(void) WEAK_REF_ATTRIBUTE;
// void SSI0_RXI_Handler(void) WEAK_REF_ATTRIBUTE;
// void SSI0_INT_Handler(void) WEAK_REF_ATTRIBUTE;
// void CTSU_WRITE_Handler(void) WEAK_REF_ATTRIBUTE;
// void CTSU_READ_Handler(void) WEAK_REF_ATTRIBUTE;
// void CTSU_END_Handler(void) WEAK_REF_ATTRIBUTE;
// void KEY_INT_Handler(void) WEAK_REF_ATTRIBUTE;
// void DOC_INT_Handler(void) WEAK_REF_ATTRIBUTE;
// void CAC_FREQUENCY_ERROR_Handler(void) WEAK_REF_ATTRIBUTE;
// void CAC_MEASUREMENT_END_Handler(void) WEAK_REF_ATTRIBUTE;
// void CAC_OVERFLOW_Handler(void) WEAK_REF_ATTRIBUTE;
// void CAN0_ERROR_Handler(void) WEAK_REF_ATTRIBUTE;
// void CAN0_FIFO_RX_Handler(void) WEAK_REF_ATTRIBUTE;
// void CAN0_FIFO_TX_Handler(void) WEAK_REF_ATTRIBUTE;
// void CAN0_MAILBOX_RX_Handler(void) WEAK_REF_ATTRIBUTE;
// void CAN0_MAILBOX_TX_Handler(void) WEAK_REF_ATTRIBUTE;
// void IOPORT_EVENT_1_Handler(void) WEAK_REF_ATTRIBUTE;
// void IOPORT_EVENT_2_Handler(void) WEAK_REF_ATTRIBUTE;
// void IOPORT_EVENT_3_Handler(void) WEAK_REF_ATTRIBUTE;
// void IOPORT_EVENT_4_Handler(void) WEAK_REF_ATTRIBUTE;
// void ELC_SOFTWARE_EVENT_0_Handler(void) WEAK_REF_ATTRIBUTE;
// void ELC_SOFTWARE_EVENT_1_Handler(void) WEAK_REF_ATTRIBUTE;
// void POEG0_EVENT_Handler(void) WEAK_REF_ATTRIBUTE;
// void POEG1_EVENT_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT0_CAPTURE_COMPARE_A_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT0_CAPTURE_COMPARE_B_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT0_COMPARE_C_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT0_COMPARE_D_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT0_COMPARE_E_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT0_COMPARE_F_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT0_COUNTER_OVERFLOW_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT0_COUNTER_UNDERFLOW_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT1_CAPTURE_COMPARE_A_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT1_CAPTURE_COMPARE_B_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT1_COMPARE_C_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT1_COMPARE_D_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT1_COMPARE_E_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT1_COMPARE_F_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT1_COUNTER_OVERFLOW_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT1_COUNTER_UNDERFLOW_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT2_CAPTURE_COMPARE_A_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT2_CAPTURE_COMPARE_B_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT2_COMPARE_C_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT2_COMPARE_D_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT2_COMPARE_E_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT2_COMPARE_F_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT2_COUNTER_OVERFLOW_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT2_COUNTER_UNDERFLOW_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT3_CAPTURE_COMPARE_A_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT3_CAPTURE_COMPARE_B_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT3_COMPARE_C_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT3_COMPARE_D_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT3_COMPARE_E_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT3_COMPARE_F_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT3_COUNTER_OVERFLOW_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT3_COUNTER_UNDERFLOW_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT4_CAPTURE_COMPARE_A_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT4_CAPTURE_COMPARE_B_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT4_COMPARE_C_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT4_COMPARE_D_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT4_COMPARE_E_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT4_COMPARE_F_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT4_COUNTER_OVERFLOW_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT4_COUNTER_UNDERFLOW_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT5_CAPTURE_COMPARE_A_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT5_CAPTURE_COMPARE_B_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT5_COMPARE_C_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT5_COMPARE_D_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT5_COMPARE_E_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT5_COMPARE_F_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT5_COUNTER_OVERFLOW_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT5_COUNTER_UNDERFLOW_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT6_CAPTURE_COMPARE_A_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT6_CAPTURE_COMPARE_B_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT6_COMPARE_C_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT6_COMPARE_D_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT6_COMPARE_E_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT6_COMPARE_F_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT6_COUNTER_OVERFLOW_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT6_COUNTER_UNDERFLOW_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT7_CAPTURE_COMPARE_A_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT7_CAPTURE_COMPARE_B_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT7_COMPARE_C_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT7_COMPARE_D_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT7_COMPARE_E_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT7_COMPARE_F_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT7_COUNTER_OVERFLOW_Handler(void) WEAK_REF_ATTRIBUTE;
// void GPT7_COUNTER_UNDERFLOW_Handler(void) WEAK_REF_ATTRIBUTE;
// void OPS_UVW_EDGE_Handler(void) WEAK_REF_ATTRIBUTE;
// void SCI0_RXI_Handler(void) WEAK_REF_ATTRIBUTE;
// void SCI0_TXI_Handler(void) WEAK_REF_ATTRIBUTE;
// void SCI0_TEI_Handler(void) WEAK_REF_ATTRIBUTE;
// void SCI0_ERI_Handler(void) WEAK_REF_ATTRIBUTE;
// void SCI0_AM_Handler(void) WEAK_REF_ATTRIBUTE;
// void SCI0_RXI_OR_ERI_Handler(void) WEAK_REF_ATTRIBUTE;
// void SCI1_RXI_Handler(void) WEAK_REF_ATTRIBUTE;
// void SCI1_TXI_Handler(void) WEAK_REF_ATTRIBUTE;
// void SCI1_TEI_Handler(void) WEAK_REF_ATTRIBUTE;
// void SCI1_ERI_Handler(void) WEAK_REF_ATTRIBUTE;
// void SCI1_AM_Handler(void) WEAK_REF_ATTRIBUTE;
// void SCI2_RXI_Handler(void) WEAK_REF_ATTRIBUTE;
// void SCI2_TXI_Handler(void) WEAK_REF_ATTRIBUTE;
// void SCI2_TEI_Handler(void) WEAK_REF_ATTRIBUTE;
// void SCI2_ERI_Handler(void) WEAK_REF_ATTRIBUTE;
// void SCI2_AM_Handler(void) WEAK_REF_ATTRIBUTE;
// void SCI9_RXI_Handler(void) WEAK_REF_ATTRIBUTE;
// void SCI9_TXI_Handler(void) WEAK_REF_ATTRIBUTE;
// void SCI9_TEI_Handler(void) WEAK_REF_ATTRIBUTE;
// void SCI9_ERI_Handler(void) WEAK_REF_ATTRIBUTE;
// void SCI9_AM_Handler(void) WEAK_REF_ATTRIBUTE;
// void SPI0_RXI_Handler(void) WEAK_REF_ATTRIBUTE;
// void SPI0_TXI_Handler(void) WEAK_REF_ATTRIBUTE;
// void SPI0_IDLE_Handler(void) WEAK_REF_ATTRIBUTE;
// void SPI0_ERI_Handler(void) WEAK_REF_ATTRIBUTE;
// void SPI0_TEI_Handler(void) WEAK_REF_ATTRIBUTE;
// void SPI1_RXI_Handler(void) WEAK_REF_ATTRIBUTE;
// void SPI1_TXI_Handler(void) WEAK_REF_ATTRIBUTE;
// void SPI1_IDLE_Handler(void) WEAK_REF_ATTRIBUTE;
// void SPI1_ERI_Handler(void) WEAK_REF_ATTRIBUTE;
// void SPI1_TEI_Handler(void) WEAK_REF_ATTRIBUTE;

// BSP_DONT_REMOVE const exc_ptr_t __Vectors[196] BSP_PLACE_IN_SECTION(
//     BSP_SECTION_FIXED_VECTORS) =
// {
//     (exc_ptr_t) (&g_main_stack[0] + BSP_CFG_STACK_MAIN_BYTES), /*      Initial Stack Pointer     */
//     Reset_Handler,                                             /*      Reset Handler             */
//     NMI_Handler,                                               /*      NMI Handler               */
//     HardFault_Handler,                                         /*      Hard Fault Handler        */
//     MemManage_Handler,                                         /*      MPU Fault Handler         */
//     BusFault_Handler,                                          /*      Bus Fault Handler         */
//     UsageFault_Handler,                                        /*      Usage Fault Handler       */
//     SecureFault_Handler,                                       /*      Secure Fault Handler      */
//     0,                                                         /*      Reserved                  */
//     0,                                                         /*      Reserved                  */
//     0,                                                         /*      Reserved                  */
//     SVC_Handler,                                               /*      SVCall Handler            */
//     DebugMon_Handler,                                          /*      Debug Monitor Handler     */
//     0,                                                         /*      Reserved                  */
//     PendSV_Handler,                                            /*      PendSV Handler            */
//     SysTick_Handler,                                           /*      SysTick Handler           */
//     ICU_IRQ0_Handler,                                          /* External pin interrupt 0 */
//     ICU_IRQ1_Handler,                                          /* External pin interrupt 1 */
//     ICU_IRQ2_Handler,                                          /* External pin interrupt 2 */
//     ICU_IRQ3_Handler,                                          /* External pin interrupt 3 */
//     ICU_IRQ4_Handler,                                          /* External pin interrupt 4 */
//     ICU_IRQ5_Handler,                                          /* External pin interrupt 5 */
//     ICU_IRQ6_Handler,                                          /* External pin interrupt 6 */
//     ICU_IRQ7_Handler,                                          /* External pin interrupt 7 */
//     ICU_IRQ8_Handler,                                          /* External pin interrupt 8 */
//     ICU_IRQ9_Handler,                                          /* External pin interrupt 9 */
//     ICU_IRQ10_Handler,                                         /* External pin interrupt 10 */
//     ICU_IRQ11_Handler,                                         /* External pin interrupt 11 */
//     ICU_IRQ12_Handler,                                         /* External pin interrupt 12 */
//     ICU_IRQ14_Handler,                                         /* External pin interrupt 14 */
//     ICU_IRQ15_Handler,                                         /* External pin interrupt 15 */
//     DMAC0_INT_Handler,                                         /* DMAC0 transfer end */
//     DMAC1_INT_Handler,                                         /* DMAC1 transfer end */
//     DMAC2_INT_Handler,                                         /* DMAC2 transfer end */
//     DMAC3_INT_Handler,                                         /* DMAC3 transfer end */
//     DTC_COMPLETE_Handler,                                          /* DTC transfer complete */
//     DTC_END_Handler,                                           /* DTC transfer end */
//     ICU_SNOOZE_CANCEL_Handler,                                         /* Canceling from Snooze mode */
//     FCU_FRDYI_Handler,                                         /* Flash ready interrupt */
//     LVD_LVD1_Handler,                                          /* Voltage monitor 1 interrupt */
//     LVD_LVD2_Handler,                                          /* Voltage monitor 2 interrupt */
//     LVD_VBATT_Handler,                                         /* VBATT low voltage detect */
//     CGC_MOSC_STOP_Handler,                                         /* Main Clock oscillation stop */
//     LPM_SNOOZE_REQUEST_Handler,                                        /* Snooze entry */
//     AGT0_INT_Handler,                                          /* AGT interrupt */
//     AGT0_COMPARE_A_Handler,                                        /* Compare match A */
//     AGT0_COMPARE_B_Handler,                                        /* Compare match B */
//     AGT1_INT_Handler,                                          /* AGT interrupt */
//     AGT1_COMPARE_A_Handler,                                        /* Compare match A */
//     AGT1_COMPARE_B_Handler,                                        /* Compare match B */
//     IWDT_UNDERFLOW_Handler,                                        /* IWDT underflow */
//     WDT_UNDERFLOW_Handler,                                         /* WDT underflow */
//     RTC_ALARM_Handler,                                         /* Alarm interrupt */
//     RTC_PERIOD_Handler,                                        /* Periodic interrupt */
//     RTC_CARRY_Handler,                                         /* Carry interrupt */
//     ADC0_SCAN_END_Handler,                                         /* End of A/D scanning operation */
//     ADC0_SCAN_END_B_Handler,                                           /* A/D scan end interrupt for group B */
//     ADC0_WINDOW_A_Handler,                                         /* Window A Compare match interrupt */
//     ADC0_WINDOW_B_Handler,                                         /* Window B Compare match interrupt */
//     ADC0_COMPARE_MATCH_Handler,                                        /* Compare match */
//     ADC0_COMPARE_MISMATCH_Handler,                                         /* Compare mismatch */
//     ACMPLP0_INT_Handler,                                           /* Low Power Comparator channel 0 interrupt */
//     ACMPLP1_INT_Handler,                                           /* Low Power Comparator channel 1 interrupt */
//     USBFS_FIFO_0_Handler,                                          /* DMA/DTC transfer request 0 */
//     USBFS_FIFO_1_Handler,                                          /* DMA/DTC transfer request 1 */
//     USBFS_INT_Handler,                                         /* USBFS interrupt */
//     USBFS_RESUME_Handler,                                          /* USBFS resume interrupt */
//     IIC0_RXI_Handler,                                          /* Receive data full */
//     IIC0_TXI_Handler,                                          /* Transmit data empty */
//     IIC0_TEI_Handler,                                          /* Transmit end */
//     IIC0_ERI_Handler,                                          /* Transfer error */
//     IIC0_WUI_Handler,                                          /* Wakeup interrupt */
//     IIC1_RXI_Handler,                                          /* Receive data full */
//     IIC1_TXI_Handler,                                          /* Transmit data empty */
//     IIC1_TEI_Handler,                                          /* Transmit end */
//     IIC1_ERI_Handler,                                          /* Transfer error */
//     SSI0_TXI_Handler,                                          /* Transmit data empty */
//     SSI0_RXI_Handler,                                          /* Receive data full */
//     SSI0_INT_Handler,                                          /* Error interrupt */
//     CTSU_WRITE_Handler,                                        /* Write request interrupt */
//     CTSU_READ_Handler,                                         /* Measurement data transfer request interrupt */
//     CTSU_END_Handler,                                          /* Measurement end interrupt */
//     KEY_INT_Handler,                                           /* Key interrupt */
//     DOC_INT_Handler,                                           /* Data operation circuit interrupt */
//     CAC_FREQUENCY_ERROR_Handler,                                           /* Frequency error interrupt */
//     CAC_MEASUREMENT_END_Handler,                                           /* Measurement end interrupt */
//     CAC_OVERFLOW_Handler,                                          /* Overflow interrupt */
//     CAN0_ERROR_Handler,                                        /* Error interrupt */
//     CAN0_FIFO_RX_Handler,                                          /* Receive FIFO interrupt */
//     CAN0_FIFO_TX_Handler,                                          /* Transmit FIFO interrupt */
//     CAN0_MAILBOX_RX_Handler,                                           /* Reception complete interrupt */
//     CAN0_MAILBOX_TX_Handler,                                           /* Transmission complete interrupt */
//     IOPORT_EVENT_1_Handler,                                        /* Port 1 event */
//     IOPORT_EVENT_2_Handler,                                        /* Port 2 event */
//     IOPORT_EVENT_3_Handler,                                        /* Port 3 event */
//     IOPORT_EVENT_4_Handler,                                        /* Port 4 event */
//     ELC_SOFTWARE_EVENT_0_Handler,                                          /* Software event 0 */
//     ELC_SOFTWARE_EVENT_1_Handler,                                          /* Software event 1 */
//     POEG0_EVENT_Handler,                                           /* Port Output disable 0 interrupt */
//     POEG1_EVENT_Handler,                                           /* Port Output disable 1 interrupt */
//     GPT0_CAPTURE_COMPARE_A_Handler,                                        /* Capture/Compare match A */
//     GPT0_CAPTURE_COMPARE_B_Handler,                                        /* Capture/Compare match B */
//     GPT0_COMPARE_C_Handler,                                        /* Compare match C */
//     GPT0_COMPARE_D_Handler,                                        /* Compare match D */
//     GPT0_COMPARE_E_Handler,                                        /* Compare match E */
//     GPT0_COMPARE_F_Handler,                                        /* Compare match F */
//     GPT0_COUNTER_OVERFLOW_Handler,                                         /* Overflow */
//     GPT0_COUNTER_UNDERFLOW_Handler,                                        /* Underflow */
//     GPT1_CAPTURE_COMPARE_A_Handler,                                        /* Capture/Compare match A */
//     GPT1_CAPTURE_COMPARE_B_Handler,                                        /* Capture/Compare match B */
//     GPT1_COMPARE_C_Handler,                                        /* Compare match C */
//     GPT1_COMPARE_D_Handler,                                        /* Compare match D */
//     GPT1_COMPARE_E_Handler,                                        /* Compare match E */
//     GPT1_COMPARE_F_Handler,                                        /* Compare match F */
//     GPT1_COUNTER_OVERFLOW_Handler,                                         /* Overflow */
//     GPT1_COUNTER_UNDERFLOW_Handler,                                        /* Underflow */
//     GPT2_CAPTURE_COMPARE_A_Handler,                                        /* Capture/Compare match A */
//     GPT2_CAPTURE_COMPARE_B_Handler,                                        /* Capture/Compare match B */
//     GPT2_COMPARE_C_Handler,                                        /* Compare match C */
//     GPT2_COMPARE_D_Handler,                                        /* Compare match D */
//     GPT2_COMPARE_E_Handler,                                        /* Compare match E */
//     GPT2_COMPARE_F_Handler,                                        /* Compare match F */
//     GPT2_COUNTER_OVERFLOW_Handler,                                         /* Overflow */
//     GPT2_COUNTER_UNDERFLOW_Handler,                                        /* Underflow */
//     GPT3_CAPTURE_COMPARE_A_Handler,                                        /* Capture/Compare match A */
//     GPT3_CAPTURE_COMPARE_B_Handler,                                        /* Capture/Compare match B */
//     GPT3_COMPARE_C_Handler,                                        /* Compare match C */
//     GPT3_COMPARE_D_Handler,                                        /* Compare match D */
//     GPT3_COMPARE_E_Handler,                                        /* Compare match E */
//     GPT3_COMPARE_F_Handler,                                        /* Compare match F */
//     GPT3_COUNTER_OVERFLOW_Handler,                                         /* Overflow */
//     GPT3_COUNTER_UNDERFLOW_Handler,                                        /* Underflow */
//     GPT4_CAPTURE_COMPARE_A_Handler,                                        /* Capture/Compare match A */
//     GPT4_CAPTURE_COMPARE_B_Handler,                                        /* Capture/Compare match B */
//     GPT4_COMPARE_C_Handler,                                        /* Compare match C */
//     GPT4_COMPARE_D_Handler,                                        /* Compare match D */
//     GPT4_COMPARE_E_Handler,                                        /* Compare match E */
//     GPT4_COMPARE_F_Handler,                                        /* Compare match F */
//     GPT4_COUNTER_OVERFLOW_Handler,                                         /* Overflow */
//     GPT4_COUNTER_UNDERFLOW_Handler,                                        /* Underflow */
//     GPT5_CAPTURE_COMPARE_A_Handler,                                        /* Capture/Compare match A */
//     GPT5_CAPTURE_COMPARE_B_Handler,                                        /* Capture/Compare match B */
//     GPT5_COMPARE_C_Handler,                                        /* Compare match C */
//     GPT5_COMPARE_D_Handler,                                        /* Compare match D */
//     GPT5_COMPARE_E_Handler,                                        /* Compare match E */
//     GPT5_COMPARE_F_Handler,                                        /* Compare match F */
//     GPT5_COUNTER_OVERFLOW_Handler,                                         /* Overflow */
//     GPT5_COUNTER_UNDERFLOW_Handler,                                        /* Underflow */
//     GPT6_CAPTURE_COMPARE_A_Handler,                                        /* Capture/Compare match A */
//     GPT6_CAPTURE_COMPARE_B_Handler,                                        /* Capture/Compare match B */
//     GPT6_COMPARE_C_Handler,                                        /* Compare match C */
//     GPT6_COMPARE_D_Handler,                                        /* Compare match D */
//     GPT6_COMPARE_E_Handler,                                        /* Compare match E */
//     GPT6_COMPARE_F_Handler,                                        /* Compare match F */
//     GPT6_COUNTER_OVERFLOW_Handler,                                         /* Overflow */
//     GPT6_COUNTER_UNDERFLOW_Handler,                                        /* Underflow */
//     GPT7_CAPTURE_COMPARE_A_Handler,                                        /* Capture/Compare match A */
//     GPT7_CAPTURE_COMPARE_B_Handler,                                        /* Capture/Compare match B */
//     GPT7_COMPARE_C_Handler,                                        /* Compare match C */
//     GPT7_COMPARE_D_Handler,                                        /* Compare match D */
//     GPT7_COMPARE_E_Handler,                                        /* Compare match E */
//     GPT7_COMPARE_F_Handler,                                        /* Compare match F */
//     GPT7_COUNTER_OVERFLOW_Handler,                                         /* Overflow */
//     GPT7_COUNTER_UNDERFLOW_Handler,                                        /* Underflow */
//     OPS_UVW_EDGE_Handler,                                          /* UVW edge event */
//     SCI0_RXI_Handler,                                          /* Receive data full */
//     SCI0_TXI_Handler,                                          /* Transmit data empty */
//     SCI0_TEI_Handler,                                          /* Transmit end */
//     SCI0_ERI_Handler,                                          /* Receive error */
//     SCI0_AM_Handler,                                           /* Address match event */
//     SCI0_RXI_OR_ERI_Handler,                                           /* Receive data full/Receive error */
//     SCI1_RXI_Handler,                                          /* Receive data full */
//     SCI1_TXI_Handler,                                          /* Transmit data empty */
//     SCI1_TEI_Handler,                                          /* Transmit end */
//     SCI1_ERI_Handler,                                          /* Receive error */
//     SCI1_AM_Handler,                                           /* Address match event */
//     SCI2_RXI_Handler,                                          /* Receive data full */
//     SCI2_TXI_Handler,                                          /* Transmit data empty */
//     SCI2_TEI_Handler,                                          /* Transmit end */
//     SCI2_ERI_Handler,                                          /* Receive error */
//     SCI2_AM_Handler,                                           /* Address match event */
//     SCI9_RXI_Handler,                                          /* Receive data full */
//     SCI9_TXI_Handler,                                          /* Transmit data empty */
//     SCI9_TEI_Handler,                                          /* Transmit end */
//     SCI9_ERI_Handler,                                          /* Receive error */
//     SCI9_AM_Handler,                                           /* Address match event */
//     SPI0_RXI_Handler,                                          /* Receive buffer full */
//     SPI0_TXI_Handler,                                          /* Transmit buffer empty */
//     SPI0_IDLE_Handler,                                         /* Idle */
//     SPI0_ERI_Handler,                                          /* Error */
//     SPI0_TEI_Handler,                                          /* Transmission complete event */
//     SPI1_RXI_Handler,                                          /* Receive buffer full */
//     SPI1_TXI_Handler,                                          /* Transmit buffer empty */
//     SPI1_IDLE_Handler,                                         /* Idle */
//     SPI1_ERI_Handler,                                          /* Error */
//     SPI1_TEI_Handler                                           /* Transmission complete event */
// };

void uart_init(void)
{
    // 1. Enable SCI0 in the Module Stop Register
    R_SYSTEM->PRCR = 0xa502;
    R_MSTP->MSTPCRB_b.MSTPB31 = 0; // Enable SCI0 (MSTPB31 = 0)
    R_SYSTEM->PRCR = 0xa500;

    // 2. Configure P411 as TXD0 and P410 as RXD0 via IOPORT
    // TXD0 (P411) = Peripheral function: 0x0A
    // RXD0 (P410) = Peripheral function: 0x0A

    // Clear the B0WI bit in the PWPR register. This enables writing to the PFSWE bit in the PWPR register.
    PWPR_REGISTER_BASE &= ~0x80; // Clear B0WI bit
    // Set 1 to the PFSWE bit in the PWPR register. This enables writing to the PmnPFS register.
    PWPR_REGISTER_BASE |= 0x40; // Set PFSWE bit

    // Write PFS registers directly (PFS write-protected by default)
    // ra_gpio_config(pin, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_LOW_POWER, af);
    R_PFS->PORT[4].PIN[11].PmnPFS_b.PMR = 0; // TXD0
    R_PFS->PORT[4].PIN[11].PmnPFS_b.PCR = 1; // TXD0
    R_PFS->PORT[4].PIN[11].PmnPFS_b.PSEL = 0x04; // TXD0
    R_PFS->PORT[4].PIN[11].PmnPFS_b.PMR = 1; // TXD0

    // ra_gpio_config(pin, GPIO_MODE_INPUT, GPIO_PULLUP, GPIO_LOW_POWER, af);
    R_PFS->PORT[4].PIN[10].PmnPFS_b.PMR = 0; // RXD0
    R_PFS->PORT[4].PIN[10].PmnPFS_b.PCR = 1; // RXD0
    R_PFS->PORT[4].PIN[10].PmnPFS_b.PSEL = 0x04; // RXD0
    R_PFS->PORT[4].PIN[10].PmnPFS_b.PMR = 1; // RXD0

    // Clear the PFSWE bit in the PWPR register. This disables writing to the PmnPFS register.
    PWPR_REGISTER_BASE &= ~0x40; // Set PFSWE bit
    // Set 1 to the B0WI bit in the PWPR register. This disables writing to the PFSWE bit in the PWPR register
    PWPR_REGISTER_BASE |= 0x80; // Set B0WI bit

    // 3. Initialize SCI1 registers

    // Disable TE and RE
    R_SCI0->SCR = 0x00;
    while (R_SCI0->SCR != 0);

    // R_SCI0->SMR = 0x00;
    // R_SCI0->SCMR = 0xF3;
    // R_SCI0->SEMR = 0xC0;

    R_SCI0->FCR_b.FM = 1;
    R_SCI0->FCR_b.TFRST = 1;
    R_SCI0->FCR_b.RFRST = 1;
    R_SCI0->FCR_b.TTRG = 0;
    R_SCI0->FCR_b.RTRG = 0;
    R_SCI0->FCR_b.RSTRG = 0;

    R_SCI0->SCR_b.CKE = 0x00;
    R_SCI0->SMR_b.CKS = 0x00;
    R_SCI0->BRR = 106;
    
    // Async, 8N1, PCLK/1
    


    R_SCI0->FCR_b.TFRST = 0;
    R_SCI0->FCR_b.RFRST = 0;


    // Delay at least 1 bit time (~8.6 us at 115200 baud)
    // for (volatile int i = 0; i < 1000; ++i) { __asm__("nop"); }

    // Enable transmit and receive
    R_SCI0->SCR_b.RE = 0x01;
    R_SCI0->SCR_b.TE = 0x01;

    R_SCI0->SCR_b.TIE = 1; // Transmit Interrupt Enable (TXI0)
    R_SCI0->SCR_b.RIE = 1; // Receive Interrupt Enable (RXI0)
    NVIC_EnableIRQ(INTERRUPTS_IELSR22); // Transmit interrupt
    NVIC_EnableIRQ(INTERRUPTS_IELSR23); // Receive interrupt
    __enable_irq();
}

void uart_send_char(char c)
{
    // Wait until there is space in the transmit FIFO (TDFE = 1)
    while (!(R_SCI0->SSR_b.TDRE));
    R_SCI0->TDR = c;

    // Clear TDFE by writing 0
    R_SCI0->SSR_b.TDRE = 0;
}

char uart_receive_char(void)
{
    // Wait until there is data in the receive FIFO (RDF = 1)
    while (!(R_SCI0->SSR_b.RDRF));
    char c = R_SCI0->RDR;

    // Clear RDF by writing 0
    R_SCI0->SSR_b.RDRF = 0;

    return c;
}

void SCI0_RXI_Handler(void)
{
    if (R_SCI0->SSR_b.RDRF)
    {
        char received = R_SCI0->RDR;
        R_SCI0->SSR_b.RDRF = 0; // Clear RDRF
        // Echo back or process
        uart_send_char(received);
    }
}

volatile const char *tx_buffer = "Hello World\r\n";
volatile uint8_t tx_index = 0;

void SCI0_TXI_Handler(void)
{
    if (R_SCI0->SSR_b.TDRE)
    {
        if (tx_buffer[tx_index] != '\0')
        {
            R_SCI0->TDR = tx_buffer[tx_index++];
            R_SCI0->SSR_b.TDRE = 0; // Clear TDRE
        }
        else
        {
            R_SCI0->SCR_b.TIE = 0; // Disable TX interrupt
            tx_index = 0;
        }
    }
}

int main( void ) {
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    uart_init();

    uart_send_char('H');
    uart_send_char('i');
    uart_send_char('!');
    uart_send_char('\n');

    while (1)
    {
        char c = uart_receive_char();
        uart_send_char(c); // Echo received char
    }

    return 0;
}

// ----------------------------------------------------------------------- END
