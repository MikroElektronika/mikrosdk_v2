// ------------------------------------------------------------------ INCLUDES
/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#include "mcu.h"
#include "interrupts.h"
#define PWPR_REGISTER_BASE (* ( volatile uint8_t * )0x40040D03UL)

// #define VECTOR_NUMBER_SCI0_RXI ((IRQn_Type)0)  /* SCI0 RXI (Receive data full) */
// #define SCI0_RXI_IRQn          ((IRQn_Type)0)  /* SCI0 RXI (Receive data full) */
// #define VECTOR_NUMBER_SCI0_TXI ((IRQn_Type)1)  /* SCI0 TXI (Transmit data empty) */
// #define SCI0_TXI_IRQn          ((IRQn_Type)1)  /* SCI0 TXI (Transmit data empty) */
// #define VECTOR_NUMBER_SCI0_TEI ((IRQn_Type)2)  /* SCI0 TEI (Transmit end) */
// #define SCI0_TEI_IRQn          ((IRQn_Type)2)  /* SCI0 TEI (Transmit end) */
// #define VECTOR_NUMBER_SCI0_ERI ((IRQn_Type)3)  /* SCI0 ERI (Receive error) */
// #define SCI0_ERI_IRQn          ((IRQn_Type)3)  /* SCI0 ERI (Receive error) */
// #define VECTOR_NUMBER_SCI1_RXI ((IRQn_Type)4)  /* SCI1 RXI (Received data full) */
// #define SCI1_RXI_IRQn          ((IRQn_Type)4)  /* SCI1 RXI (Received data full) */
// #define VECTOR_NUMBER_SCI1_TXI ((IRQn_Type)5)  /* SCI1 TXI (Transmit data empty) */
// #define SCI1_TXI_IRQn          ((IRQn_Type)5)  /* SCI1 TXI (Transmit data empty) */
// #define VECTOR_NUMBER_SCI1_TEI ((IRQn_Type)6)  /* SCI1 TEI (Transmit end) */
// #define SCI1_TEI_IRQn          ((IRQn_Type)6)  /* SCI1 TEI (Transmit end) */
// #define VECTOR_NUMBER_SCI1_ERI ((IRQn_Type)7)  /* SCI1 ERI (Receive error) */
// #define SCI1_ERI_IRQn          ((IRQn_Type)7)  /* SCI1 ERI (Receive error) */
// #define VECTOR_NUMBER_SCI2_RXI ((IRQn_Type)8)  /* SCI2 RXI (Received data full) */
// #define SCI2_RXI_IRQn          ((IRQn_Type)8)  /* SCI2 RXI (Received data full) */
// #define VECTOR_NUMBER_SCI2_TXI ((IRQn_Type)9)  /* SCI2 TXI (Transmit data empty) */
// #define SCI2_TXI_IRQn          ((IRQn_Type)9)  /* SCI2 TXI (Transmit data empty) */
// #define VECTOR_NUMBER_SCI2_TEI ((IRQn_Type)10)  /* SCI2 TEI (Transmit end) */
// #define SCI2_TEI_IRQn          ((IRQn_Type)10)  /* SCI2 TEI (Transmit end) */
// #define VECTOR_NUMBER_SCI2_ERI ((IRQn_Type)11)  /* SCI2 ERI (Receive error) */
// #define SCI2_ERI_IRQn          ((IRQn_Type)11)  /* SCI2 ERI (Receive error) */
// #define VECTOR_NUMBER_RTC_ALARM ((IRQn_Type)12)  /* RTC ALARM (Alarm interrupt) */
// #define RTC_ALARM_IRQn          ((IRQn_Type)12)  /* RTC ALARM (Alarm interrupt) */
// #define VECTOR_NUMBER_RTC_PERIOD ((IRQn_Type)13)  /* RTC PERIOD (Periodic interrupt) */
// #define RTC_PERIOD_IRQn          ((IRQn_Type)13)  /* RTC PERIOD (Periodic interrupt) */
// #define VECTOR_NUMBER_RTC_CARRY ((IRQn_Type)14)  /* RTC CARRY (Carry interrupt) */
// #define RTC_CARRY_IRQn          ((IRQn_Type)14)  /* RTC CARRY (Carry interrupt) */
// #define VECTOR_NUMBER_AGT0_INT ((IRQn_Type)15)  /* AGT0 INT (AGT interrupt) */
// #define AGT0_INT_IRQn          ((IRQn_Type)15)  /* AGT0 INT (AGT interrupt) */
// #define VECTOR_NUMBER_ICU_IRQ0 ((IRQn_Type)16)  /* ICU IRQ0 (External pin interrupt 0) */
// #define ICU_IRQ0_IRQn          ((IRQn_Type)16)  /* ICU IRQ0 (External pin interrupt 0) */
// #define VECTOR_NUMBER_SPI0_RXI ((IRQn_Type)17)  /* SPI0 RXI (Receive buffer full) */
// #define SPI0_RXI_IRQn          ((IRQn_Type)17)  /* SPI0 RXI (Receive buffer full) */
// #define VECTOR_NUMBER_SPI0_TXI ((IRQn_Type)18)  /* SPI0 TXI (Transmit buffer empty) */
// #define SPI0_TXI_IRQn          ((IRQn_Type)18)  /* SPI0 TXI (Transmit buffer empty) */
// #define VECTOR_NUMBER_SPI0_TEI ((IRQn_Type)19)  /* SPI0 TEI (Transmission complete event) */
// #define SPI0_TEI_IRQn          ((IRQn_Type)19)  /* SPI0 TEI (Transmission complete event) */
// #define VECTOR_NUMBER_SPI0_ERI ((IRQn_Type)20)  /* SPI0 ERI (Error) */
// #define SPI0_ERI_IRQn          ((IRQn_Type)20)  /* SPI0 ERI (Error) */

typedef void (* fsp_vector_t)(void);
#define BSP_PLACE_IN_SECTION(x)            __attribute__((section(x))) __attribute__((__used__))
 #define BSP_SECTION_APPLICATION_VECTORS    ".application_vectors"

 /* ISR prototypes */
void ICU_IELSR0_Handler(void) __attribute__((weak, alias("ICU_IELSR23_Handler")));
void ICU_IELSR1_Handler(void) __attribute__((weak, alias("ICU_IELSR23_Handler")));
void ICU_IELSR2_Handler(void) __attribute__((weak, alias("ICU_IELSR23_Handler")));
void ICU_IELSR3_Handler(void) __attribute__((weak, alias("ICU_IELSR23_Handler")));
void ICU_IELSR4_Handler(void) __attribute__((weak, alias("ICU_IELSR23_Handler")));
void ICU_IELSR5_Handler(void) __attribute__((weak, alias("ICU_IELSR23_Handler")));
void ICU_IELSR6_Handler(void) __attribute__((weak, alias("ICU_IELSR23_Handler")));
void ICU_IELSR7_Handler(void) __attribute__((weak, alias("ICU_IELSR23_Handler")));
void ICU_IELSR8_Handler(void) __attribute__((weak, alias("ICU_IELSR23_Handler")));
void ICU_IELSR9_Handler(void) __attribute__((weak, alias("ICU_IELSR23_Handler")));
void ICU_IELSR10_Handler(void) __attribute__((weak, alias("ICU_IELSR23_Handler")));
void ICU_IELSR11_Handler(void) __attribute__((weak, alias("ICU_IELSR23_Handler")));
void ICU_IELSR12_Handler(void) __attribute__((weak, alias("ICU_IELSR23_Handler")));
void ICU_IELSR13_Handler(void) __attribute__((weak, alias("ICU_IELSR23_Handler")));
void ICU_IELSR14_Handler(void) __attribute__((weak, alias("ICU_IELSR23_Handler")));
void ICU_IELSR15_Handler(void) __attribute__((weak, alias("ICU_IELSR23_Handler")));
void ICU_IELSR16_Handler(void) __attribute__((weak, alias("ICU_IELSR23_Handler")));
void ICU_IELSR17_Handler(void) __attribute__((weak, alias("ICU_IELSR23_Handler")));
void ICU_IELSR18_Handler(void) __attribute__((weak, alias("ICU_IELSR23_Handler")));
void ICU_IELSR19_Handler(void) __attribute__((weak, alias("ICU_IELSR23_Handler")));
void ICU_IELSR20_Handler(void) __attribute__((weak, alias("ICU_IELSR23_Handler")));
void ICU_IELSR21_Handler(void) __attribute__((weak, alias("ICU_IELSR23_Handler")));
void ICU_IELSR22_Handler(void);
void ICU_IELSR23_Handler(void);
void ICU_IELSR24_Handler(void) __attribute__((weak, alias("ICU_IELSR23_Handler")));
void ICU_IELSR25_Handler(void) __attribute__((weak, alias("ICU_IELSR23_Handler")));
void ICU_IELSR26_Handler(void) __attribute__((weak, alias("ICU_IELSR23_Handler")));
void ICU_IELSR27_Handler(void) __attribute__((weak, alias("ICU_IELSR23_Handler")));
void ICU_IELSR28_Handler(void) __attribute__((weak, alias("ICU_IELSR23_Handler")));
void ICU_IELSR29_Handler(void) __attribute__((weak, alias("ICU_IELSR23_Handler")));
void ICU_IELSR30_Handler(void) __attribute__((weak, alias("ICU_IELSR23_Handler")));
void ICU_IELSR31_Handler(void) __attribute__((weak, alias("ICU_IELSR23_Handler")));

const fsp_vector_t g_vector_table[32] BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) =
{
	ICU_IELSR0_Handler,
	ICU_IELSR1_Handler,
	ICU_IELSR2_Handler,
    ICU_IELSR3_Handler,
	ICU_IELSR4_Handler,
    ICU_IELSR5_Handler,
    ICU_IELSR6_Handler,
 	ICU_IELSR7_Handler,
	ICU_IELSR8_Handler,
	ICU_IELSR9_Handler,
    ICU_IELSR10_Handler,
    ICU_IELSR11_Handler,
    ICU_IELSR12_Handler,
    ICU_IELSR13_Handler,
	ICU_IELSR14_Handler,
	ICU_IELSR15_Handler,
	ICU_IELSR16_Handler,
	ICU_IELSR17_Handler,
	ICU_IELSR18_Handler, 
	ICU_IELSR19_Handler,                                                          
	ICU_IELSR20_Handler,
    ICU_IELSR21_Handler,
	ICU_IELSR22_Handler,
 	ICU_IELSR23_Handler,                                                                          
	ICU_IELSR24_Handler,
	ICU_IELSR25_Handler,
    ICU_IELSR26_Handler,
    ICU_IELSR27_Handler,
    ICU_IELSR28_Handler,
    ICU_IELSR29_Handler,
	ICU_IELSR30_Handler,
    ICU_IELSR31_Handler
};

typedef enum e_elc_event_ra4m1
{
    ELC_EVENT_NONE                          = (0x0),   // Link disabled
    ELC_EVENT_ICU_IRQ0                      = (0x001), // External pin interrupt 0
    ELC_EVENT_ICU_IRQ1                      = (0x002), // External pin interrupt 1
    ELC_EVENT_ICU_IRQ2                      = (0x003), // External pin interrupt 2
    ELC_EVENT_ICU_IRQ3                      = (0x004), // External pin interrupt 3
    ELC_EVENT_ICU_IRQ4                      = (0x005), // External pin interrupt 4
    ELC_EVENT_ICU_IRQ5                      = (0x006), // External pin interrupt 5
    ELC_EVENT_ICU_IRQ6                      = (0x007), // External pin interrupt 6
    ELC_EVENT_ICU_IRQ7                      = (0x008), // External pin interrupt 7
    ELC_EVENT_ICU_IRQ8                      = (0x009), // External pin interrupt 8
    ELC_EVENT_ICU_IRQ9                      = (0x00A), // External pin interrupt 9
    ELC_EVENT_ICU_IRQ10                     = (0x00B), // External pin interrupt 10
    ELC_EVENT_ICU_IRQ11                     = (0x00C), // External pin interrupt 11
    ELC_EVENT_ICU_IRQ12                     = (0x00D), // External pin interrupt 12
    ELC_EVENT_ICU_IRQ14                     = (0x00F), // External pin interrupt 14
    ELC_EVENT_ICU_IRQ15                     = (0x010), // External pin interrupt 15
    ELC_EVENT_DMAC0_INT                     = (0x011), // DMAC0 transfer end
    ELC_EVENT_DMAC1_INT                     = (0x012), // DMAC1 transfer end
    ELC_EVENT_DMAC2_INT                     = (0x013), // DMAC2 transfer end
    ELC_EVENT_DMAC3_INT                     = (0x014), // DMAC3 transfer end
    ELC_EVENT_DTC_COMPLETE                  = (0x015), // DTC transfer complete
    ELC_EVENT_DTC_END                       = (0x016), // DTC transfer end
    ELC_EVENT_ICU_SNOOZE_CANCEL             = (0x017), // Canceling from Snooze mode
    ELC_EVENT_FCU_FRDYI                     = (0x018), // Flash ready interrupt
    ELC_EVENT_LVD_LVD1                      = (0x019), // Voltage monitor 1 interrupt
    ELC_EVENT_LVD_LVD2                      = (0x01A), // Voltage monitor 2 interrupt
    ELC_EVENT_LVD_VBATT                     = (0x01B), // VBATT low voltage detect
    ELC_EVENT_CGC_MOSC_STOP                 = (0x01C), // Main Clock oscillation stop
    ELC_EVENT_LPM_SNOOZE_REQUEST            = (0x01D), // Snooze entry
    ELC_EVENT_AGT0_INT                      = (0x01E), // AGT interrupt
    ELC_EVENT_AGT0_COMPARE_A                = (0x01F), // Compare match A
    ELC_EVENT_AGT0_COMPARE_B                = (0x020), // Compare match B
    ELC_EVENT_AGT1_INT                      = (0x021), // AGT interrupt
    ELC_EVENT_AGT1_COMPARE_A                = (0x022), // Compare match A
    ELC_EVENT_AGT1_COMPARE_B                = (0x023), // Compare match B
    ELC_EVENT_IWDT_UNDERFLOW                = (0x024), // IWDT underflow
    ELC_EVENT_WDT_UNDERFLOW                 = (0x025), // WDT underflow
    ELC_EVENT_RTC_ALARM                     = (0x026), // Alarm interrupt
    ELC_EVENT_RTC_PERIOD                    = (0x027), // Periodic interrupt
    ELC_EVENT_RTC_CARRY                     = (0x028), // Carry interrupt
    ELC_EVENT_ADC0_SCAN_END                 = (0x029), // End of A/D scanning operation
    ELC_EVENT_ADC0_SCAN_END_B               = (0x02A), // A/D scan end interrupt for group B
    ELC_EVENT_ADC0_WINDOW_A                 = (0x02B), // Window A Compare match interrupt
    ELC_EVENT_ADC0_WINDOW_B                 = (0x02C), // Window B Compare match interrupt
    ELC_EVENT_ADC0_COMPARE_MATCH            = (0x02D), // Compare match
    ELC_EVENT_ADC0_COMPARE_MISMATCH         = (0x02E), // Compare mismatch
    ELC_EVENT_ACMPLP0_INT                   = (0x02F), // Low Power Comparator channel 0 interrupt
    ELC_EVENT_ACMPLP1_INT                   = (0x030), // Low Power Comparator channel 1 interrupt
    ELC_EVENT_USBFS_FIFO_0                  = (0x031), // DMA/DTC transfer request 0
    ELC_EVENT_USBFS_FIFO_1                  = (0x032), // DMA/DTC transfer request 1
    ELC_EVENT_USBFS_INT                     = (0x033), // USBFS interrupt
    ELC_EVENT_USBFS_RESUME                  = (0x034), // USBFS resume interrupt
    ELC_EVENT_IIC0_RXI                      = (0x035), // Receive data full
    ELC_EVENT_IIC0_TXI                      = (0x036), // Transmit data empty
    ELC_EVENT_IIC0_TEI                      = (0x037), // Transmit end
    ELC_EVENT_IIC0_ERI                      = (0x038), // Transfer error
    ELC_EVENT_IIC0_WUI                      = (0x039), // Wakeup interrupt
    ELC_EVENT_IIC1_RXI                      = (0x03A), // Receive data full
    ELC_EVENT_IIC1_TXI                      = (0x03B), // Transmit data empty
    ELC_EVENT_IIC1_TEI                      = (0x03C), // Transmit end
    ELC_EVENT_IIC1_ERI                      = (0x03D), // Transfer error
    ELC_EVENT_SSI0_TXI                      = (0x03E), // Transmit data empty
    ELC_EVENT_SSI0_RXI                      = (0x03F), // Receive data full
    ELC_EVENT_SSI0_INT                      = (0x041), // Error interrupt
    ELC_EVENT_CTSU_WRITE                    = (0x042), // Write request interrupt
    ELC_EVENT_CTSU_READ                     = (0x043), // Measurement data transfer request interrupt
    ELC_EVENT_CTSU_END                      = (0x044), // Measurement end interrupt
    ELC_EVENT_KEY_INT                       = (0x045), // Key interrupt
    ELC_EVENT_DOC_INT                       = (0x046), // Data operation circuit interrupt
    ELC_EVENT_CAC_FREQUENCY_ERROR           = (0x047), // Frequency error interrupt
    ELC_EVENT_CAC_MEASUREMENT_END           = (0x048), // Measurement end interrupt
    ELC_EVENT_CAC_OVERFLOW                  = (0x049), // Overflow interrupt
    ELC_EVENT_CAN0_ERROR                    = (0x04A), // Error interrupt
    ELC_EVENT_CAN0_FIFO_RX                  = (0x04B), // Receive FIFO interrupt
    ELC_EVENT_CAN0_FIFO_TX                  = (0x04C), // Transmit FIFO interrupt
    ELC_EVENT_CAN0_MAILBOX_RX               = (0x04D), // Reception complete interrupt
    ELC_EVENT_CAN0_MAILBOX_TX               = (0x04E), // Transmission complete interrupt
    ELC_EVENT_IOPORT_EVENT_1                = (0x04F), // Port 1 event
    ELC_EVENT_IOPORT_EVENT_2                = (0x050), // Port 2 event
    ELC_EVENT_IOPORT_EVENT_3                = (0x051), // Port 3 event
    ELC_EVENT_IOPORT_EVENT_4                = (0x052), // Port 4 event
    ELC_EVENT_ELC_SOFTWARE_EVENT_0          = (0x053), // Software event 0
    ELC_EVENT_ELC_SOFTWARE_EVENT_1          = (0x054), // Software event 1
    ELC_EVENT_POEG0_EVENT                   = (0x055), // Port Output disable 0 interrupt
    ELC_EVENT_POEG1_EVENT                   = (0x056), // Port Output disable 1 interrupt
    ELC_EVENT_GPT0_CAPTURE_COMPARE_A        = (0x057), // Capture/Compare match A
    ELC_EVENT_GPT0_CAPTURE_COMPARE_B        = (0x058), // Capture/Compare match B
    ELC_EVENT_GPT0_COMPARE_C                = (0x059), // Compare match C
    ELC_EVENT_GPT0_COMPARE_D                = (0x05A), // Compare match D
    ELC_EVENT_GPT0_COMPARE_E                = (0x05B), // Compare match E
    ELC_EVENT_GPT0_COMPARE_F                = (0x05C), // Compare match F
    ELC_EVENT_GPT0_COUNTER_OVERFLOW         = (0x05D), // Overflow
    ELC_EVENT_GPT0_COUNTER_UNDERFLOW        = (0x05E), // Underflow
    ELC_EVENT_GPT1_CAPTURE_COMPARE_A        = (0x05F), // Capture/Compare match A
    ELC_EVENT_GPT1_CAPTURE_COMPARE_B        = (0x060), // Capture/Compare match B
    ELC_EVENT_GPT1_COMPARE_C                = (0x061), // Compare match C
    ELC_EVENT_GPT1_COMPARE_D                = (0x062), // Compare match D
    ELC_EVENT_GPT1_COMPARE_E                = (0x063), // Compare match E
    ELC_EVENT_GPT1_COMPARE_F                = (0x064), // Compare match F
    ELC_EVENT_GPT1_COUNTER_OVERFLOW         = (0x065), // Overflow
    ELC_EVENT_GPT1_COUNTER_UNDERFLOW        = (0x066), // Underflow
    ELC_EVENT_GPT2_CAPTURE_COMPARE_A        = (0x067), // Capture/Compare match A
    ELC_EVENT_GPT2_CAPTURE_COMPARE_B        = (0x068), // Capture/Compare match B
    ELC_EVENT_GPT2_COMPARE_C                = (0x069), // Compare match C
    ELC_EVENT_GPT2_COMPARE_D                = (0x06A), // Compare match D
    ELC_EVENT_GPT2_COMPARE_E                = (0x06B), // Compare match E
    ELC_EVENT_GPT2_COMPARE_F                = (0x06C), // Compare match F
    ELC_EVENT_GPT2_COUNTER_OVERFLOW         = (0x06D), // Overflow
    ELC_EVENT_GPT2_COUNTER_UNDERFLOW        = (0x06E), // Underflow
    ELC_EVENT_GPT3_CAPTURE_COMPARE_A        = (0x06F), // Capture/Compare match A
    ELC_EVENT_GPT3_CAPTURE_COMPARE_B        = (0x070), // Capture/Compare match B
    ELC_EVENT_GPT3_COMPARE_C                = (0x071), // Compare match C
    ELC_EVENT_GPT3_COMPARE_D                = (0x072), // Compare match D
    ELC_EVENT_GPT3_COMPARE_E                = (0x073), // Compare match E
    ELC_EVENT_GPT3_COMPARE_F                = (0x074), // Compare match F
    ELC_EVENT_GPT3_COUNTER_OVERFLOW         = (0x075), // Overflow
    ELC_EVENT_GPT3_COUNTER_UNDERFLOW        = (0x076), // Underflow
    ELC_EVENT_GPT4_CAPTURE_COMPARE_A        = (0x077), // Capture/Compare match A
    ELC_EVENT_GPT4_CAPTURE_COMPARE_B        = (0x078), // Capture/Compare match B
    ELC_EVENT_GPT4_COMPARE_C                = (0x079), // Compare match C
    ELC_EVENT_GPT4_COMPARE_D                = (0x07A), // Compare match D
    ELC_EVENT_GPT4_COMPARE_E                = (0x07B), // Compare match E
    ELC_EVENT_GPT4_COMPARE_F                = (0x07C), // Compare match F
    ELC_EVENT_GPT4_COUNTER_OVERFLOW         = (0x07D), // Overflow
    ELC_EVENT_GPT4_COUNTER_UNDERFLOW        = (0x07E), // Underflow
    ELC_EVENT_GPT5_CAPTURE_COMPARE_A        = (0x07F), // Capture/Compare match A
    ELC_EVENT_GPT5_CAPTURE_COMPARE_B        = (0x080), // Capture/Compare match B
    ELC_EVENT_GPT5_COMPARE_C                = (0x081), // Compare match C
    ELC_EVENT_GPT5_COMPARE_D                = (0x082), // Compare match D
    ELC_EVENT_GPT5_COMPARE_E                = (0x083), // Compare match E
    ELC_EVENT_GPT5_COMPARE_F                = (0x084), // Compare match F
    ELC_EVENT_GPT5_COUNTER_OVERFLOW         = (0x085), // Overflow
    ELC_EVENT_GPT5_COUNTER_UNDERFLOW        = (0x086), // Underflow
    ELC_EVENT_GPT6_CAPTURE_COMPARE_A        = (0x087), // Capture/Compare match A
    ELC_EVENT_GPT6_CAPTURE_COMPARE_B        = (0x088), // Capture/Compare match B
    ELC_EVENT_GPT6_COMPARE_C                = (0x089), // Compare match C
    ELC_EVENT_GPT6_COMPARE_D                = (0x08A), // Compare match D
    ELC_EVENT_GPT6_COMPARE_E                = (0x08B), // Compare match E
    ELC_EVENT_GPT6_COMPARE_F                = (0x08C), // Compare match F
    ELC_EVENT_GPT6_COUNTER_OVERFLOW         = (0x08D), // Overflow
    ELC_EVENT_GPT6_COUNTER_UNDERFLOW        = (0x08E), // Underflow
    ELC_EVENT_GPT7_CAPTURE_COMPARE_A        = (0x08F), // Capture/Compare match A
    ELC_EVENT_GPT7_CAPTURE_COMPARE_B        = (0x090), // Capture/Compare match B
    ELC_EVENT_GPT7_COMPARE_C                = (0x091), // Compare match C
    ELC_EVENT_GPT7_COMPARE_D                = (0x092), // Compare match D
    ELC_EVENT_GPT7_COMPARE_E                = (0x093), // Compare match E
    ELC_EVENT_GPT7_COMPARE_F                = (0x094), // Compare match F
    ELC_EVENT_GPT7_COUNTER_OVERFLOW         = (0x095), // Overflow
    ELC_EVENT_GPT7_COUNTER_UNDERFLOW        = (0x096), // Underflow
    ELC_EVENT_OPS_UVW_EDGE                  = (0x097), // UVW edge event
    ELC_EVENT_SCI0_RXI                      = (0x098), // Receive data full
    ELC_EVENT_SCI0_TXI                      = (0x099), // Transmit data empty
    ELC_EVENT_SCI0_TEI                      = (0x09A), // Transmit end
    ELC_EVENT_SCI0_ERI                      = (0x09B), // Receive error
    ELC_EVENT_SCI0_AM                       = (0x09C), // Address match event
    ELC_EVENT_SCI0_RXI_OR_ERI               = (0x09D), // Receive data full/Receive error
    ELC_EVENT_SCI1_RXI                      = (0x09E), // Receive data full
    ELC_EVENT_SCI1_TXI                      = (0x09F), // Transmit data empty
    ELC_EVENT_SCI1_TEI                      = (0x0A0), // Transmit end
    ELC_EVENT_SCI1_ERI                      = (0x0A1), // Receive error
    ELC_EVENT_SCI1_AM                       = (0x0A2), // Address match event
    ELC_EVENT_SCI2_RXI                      = (0x0A3), // Receive data full
    ELC_EVENT_SCI2_TXI                      = (0x0A4), // Transmit data empty
    ELC_EVENT_SCI2_TEI                      = (0x0A5), // Transmit end
    ELC_EVENT_SCI2_ERI                      = (0x0A6), // Receive error
    ELC_EVENT_SCI2_AM                       = (0x0A7), // Address match event
    ELC_EVENT_SCI9_RXI                      = (0x0A8), // Receive data full
    ELC_EVENT_SCI9_TXI                      = (0x0A9), // Transmit data empty
    ELC_EVENT_SCI9_TEI                      = (0x0AA), // Transmit end
    ELC_EVENT_SCI9_ERI                      = (0x0AB), // Receive error
    ELC_EVENT_SCI9_AM                       = (0x0AC), // Address match event
    ELC_EVENT_SPI0_RXI                      = (0x0AD), // Receive buffer full
    ELC_EVENT_SPI0_TXI                      = (0x0AE), // Transmit buffer empty
    ELC_EVENT_SPI0_IDLE                     = (0x0AF), // Idle
    ELC_EVENT_SPI0_ERI                      = (0x0B0), // Error
    ELC_EVENT_SPI0_TEI                      = (0x0B1), // Transmission complete event
    ELC_EVENT_SPI1_RXI                      = (0x0B2), // Receive buffer full
    ELC_EVENT_SPI1_TXI                      = (0x0B3), // Transmit buffer empty
    ELC_EVENT_SPI1_IDLE                     = (0x0B4), // Idle
    ELC_EVENT_SPI1_ERI                      = (0x0B5), // Error
    ELC_EVENT_SPI1_TEI                      = (0x0B6)  // Transmission complete event
} elc_event_t;

typedef elc_event_t bsp_interrupt_event_t;

const bsp_interrupt_event_t g_interrupt_event_link_select[32] =
{
    [0] = ELC_EVENT_SCI0_RXI,         /* SCI0 RXI (Receive data full) */
    [1] = ELC_EVENT_SCI0_TXI,         /* SCI0 TXI (Transmit data empty) */
    [2] = ELC_EVENT_SCI0_TEI,         /* SCI0 TEI (Transmit end) */
    [3] = ELC_EVENT_SCI0_ERI,         /* SCI0 ERI (Receive error) */
    [4] = ELC_EVENT_SCI1_RXI,         /* SCI1 RXI (Received data full) */
    [5] = ELC_EVENT_SCI1_TXI,         /* SCI1 TXI (Transmit data empty) */
    [6] = ELC_EVENT_SCI1_TEI,         /* SCI1 TEI (Transmit end) */
    [7] = ELC_EVENT_SCI1_ERI,         /* SCI1 ERI (Receive error) */
    [8] = ELC_EVENT_SCI2_RXI,         /* SCI2 RXI (Received data full) */
    [9] = ELC_EVENT_SCI2_TXI,         /* SCI2 TXI (Transmit data empty) */
    [10] = ELC_EVENT_SCI2_TEI,         /* SCI2 TEI (Transmit end) */
    [11] = ELC_EVENT_SCI2_ERI,         /* SCI2 ERI (Receive error) */
    [12] = ELC_EVENT_RTC_ALARM,         /* RTC ALARM (Alarm interrupt) */
    [13] = ELC_EVENT_RTC_PERIOD,         /* RTC PERIOD (Periodic interrupt) */
    [14] = ELC_EVENT_RTC_CARRY,         /* RTC CARRY (Carry interrupt) */
    [15] = ELC_EVENT_AGT0_INT,         /* AGT0 INT (AGT interrupt) */
    [16] = ELC_EVENT_ICU_IRQ0,         /* ICU IRQ0 (External pin interrupt 0) */
    [17] = ELC_EVENT_SPI0_RXI,         /* SPI0 RXI (Receive buffer full) */
    [18] = ELC_EVENT_SPI0_TXI,         /* SPI0 TXI (Transmit buffer empty) */
    [19] = ELC_EVENT_SPI0_TEI,         /* SPI0 TEI (Transmission complete event) */
    [20] = ELC_EVENT_SPI0_ERI,         /* SPI0 ERI (Error) */
};

__attribute__((always_inline)) static inline void ra_enable_irq(__attribute__((unused)) uint32_t state) {
    __asm__ volatile ("cpsie f"
        :
        :
        : "memory");
}

__attribute__((always_inline)) static inline uint32_t ra_disable_irq(void) {
    uint32_t state;
    __asm__ volatile ("cpsid f"
        : "=r" (state)
        :
        : "memory");
    return state;
}

uint32_t check;

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

    uint32_t state = ra_disable_irq();

    // Disable TE and RE
    R_SCI0->SCR = 0x00;
    while (R_SCI0->SCR != 0);

    R_SCI0->SMR = 0x00;
    R_SCI0->SCMR = 0xF3;
    R_SCI0->SEMR = 0xC0;

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
    


    // R_SCI0->FCR_b.TFRST = 0;
    // R_SCI0->FCR_b.RFRST = 0;


    // Delay at least 1 bit time (~8.6 us at 115200 baud)
    // for (volatile int i = 0; i < 1000; ++i) { __asm__("nop"); }

    // Enable transmit and receive AND their interrupts
    // NVIC_SetVector((IRQn_Type) INTERRUPTS_IELSR22, (uint32_t) sci_uart_rxi_isr);  // SCI0_RXI_IRQn
    // NVIC_SetVector((IRQn_Type) INTERRUPTS_IELSR23, (uint32_t) sci_uart_txi_isr);  // SCI0_TXI_IRQn
    R_ICU->IELSR[22] = (uint32_t) g_interrupt_event_link_select[0];
    R_ICU->IELSR[23] = (uint32_t) g_interrupt_event_link_select[1];
    NVIC_EnableIRQ(38);
    NVIC_EnableIRQ(39);
    interrupts_enable();
    R_SCI0->SSR_b.RDRF = 0;
    R_SCI0->SSR_b.TDRE = 0;
    R_SCI0->SCR = 0x30; // TE + RE
    R_SCI0->SCR |= 0xC0; // TIE + RIE
}

volatile char tx_buffer[128];
volatile int tx_head = 0, tx_tail = 0;

volatile char rx_buffer[128];
volatile int rx_head = 0, rx_tail = 0;

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

static void ra_sci_isr_rx(uint32_t ch) {
    if (R_SCI0->SSR_b.RDRF)
    {
        char c = R_SCI0->RDR;
        R_SCI0->SSR_b.RDRF = 0;  // Clear flag

        int next = (rx_head + 1) % sizeof(rx_buffer);
        if (next != rx_tail)
        {
            rx_buffer[rx_head] = c;
            rx_head = next;
        }
    }
}

static void ra_sci_isr_tx(uint32_t ch) {
    if (R_SCI0->SSR_b.TDRE)
    {
        if (tx_head != tx_tail)
        {
            R_SCI0->TDR = tx_buffer[tx_tail];
            tx_tail = (tx_tail + 1) % sizeof(tx_buffer);
        }
        else
        {
            R_SCI0->SCR_b.TIE = 0;  // Disable TX interrupt if nothing to send
        }

        R_SCI0->SSR_b.TDRE = 0; // Clear flag
    }
}

/* rx-interrupt */
void ICU_IELSR22_Handler(void) {
    // IRQn_Type irq = R_FSP_CurrentIrqGet();
    uint32_t ch = 0;
    ra_sci_isr_rx(ch);
}

/* tx-interrupt */
void ICU_IELSR23_Handler(void) {
    // IRQn_Type irq = R_FSP_CurrentIrqGet();
    uint32_t ch = 1;
    ra_sci_isr_tx(ch);
}

int main( void ) {
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    SCB->VTOR = (uint32_t)&g_vector_table;

    uart_init();

    check = R_ICU->IELSR[23];
    uart_send_char('H');
    check = R_ICU->IELSR[23];
    uart_send_char('i');
    uart_send_char('\r');
    uart_send_char('\n');

    while (1)
    {
        // char c = uart_receive_char();
        // uart_send_char(c); // Echo received char
    }

    return 0;
}

// ----------------------------------------------------------------------- END
