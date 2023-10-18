#ifndef GD32VF103_H
#define GD32VF103_H

#include "bits.h"
#include "const.h"
#include "core_header.h"

#define FLASH_BASE                     _AC(0x08000000,UL)  /*!< main flash base address */
#define SRAM_BASE                      _AC(0x20000000,UL)  /*!< SRAM base address       */

#define ADC0_BASE                      _AC(0x40012400,UL)  /*!< ADC0 base address */
#define ADC1_BASE                      _AC(0x40012800,UL)  /*!< ADC1 base address */

/* register definitions */
#define ADC_STAT                       _AC(0x00,UL)  /*!< ADC status register */
#define ADC_CTL0                       _AC(0x04,UL)  /*!< ADC control register 0 */
#define ADC_CTL1                       _AC(0x08,UL)  /*!< ADC control register 1 */
#define ADC_SAMPT0                     _AC(0x0C,UL)  /*!< ADC sampling time register 0 */
#define ADC_SAMPT1                     _AC(0x10,UL)  /*!< ADC sampling time register 1 */
#define ADC_IOFF0                      _AC(0x14,UL)  /*!< ADC inserted channel data offset register 0 */
#define ADC_IOFF1                      _AC(0x18,UL)  /*!< ADC inserted channel data offset register 1 */
#define ADC_IOFF2                      _AC(0x1C,UL)  /*!< ADC inserted channel data offset register 2 */
#define ADC_IOFF3                      _AC(0x20,UL)  /*!< ADC inserted channel data offset register 3 */
#define ADC_WDHT                       _AC(0x24,UL)  /*!< ADC watchdog high threshold register */
#define ADC_WDLT                       _AC(0x28,UL)  /*!< ADC watchdog low threshold register */
#define ADC_RSQ0                       _AC(0x2C,UL)  /*!< ADC regular sequence register 0 */
#define ADC_RSQ1                       _AC(0x30,UL)  /*!< ADC regular sequence register 1 */
#define ADC_RSQ2                       _AC(0x34,UL)  /*!< ADC regular sequence register 2 */
#define ADC_ISQ                        _AC(0x38,UL)  /*!< ADC inserted sequence register */
#define ADC_IDATA0                     _AC(0x3C,UL)  /*!< ADC inserted data register 0 */
#define ADC_IDATA1                     _AC(0x40,UL)  /*!< ADC inserted data register 1 */
#define ADC_IDATA2                     _AC(0x44,UL)  /*!< ADC inserted data register 2 */
#define ADC_IDATA3                     _AC(0x48,UL)  /*!< ADC inserted data register 3 */
#define ADC_RDATA                      _AC(0x4C,UL)  /*!< ADC regular data register */
#define ADC_OVSAMPCTL                  _AC(0x80,UL)  /*!< ADC oversample control register */

/* ADC_STAT */
#define ADC_STAT_STRC                  _BIT(4,U)     /*!< regular channel start flag */
#define ADC_STAT_STIC                  _BIT(3,U)     /*!< inserted channel start flag */
#define ADC_STAT_EOIC                  _BIT(2,U)     /*!< inserted channel end of conversion */
#define ADC_STAT_EOC                   _BIT(1,U)     /*!< end of conversion */
#define ADC_STAT_WDE                   _BIT(0,U)     /*!< analog watchdog event flag */

/* ADC_CTL0 */
#define ADC_CTL0_RWDEN                 _BIT(23,U)             /*!< analog watchdog enable on regular channels */
#define ADC_CTL0_IWDEN                 _BIT(22,U)             /*!< analog watchdog enable on inserted channels */
#define ADC_CTL0_SYNCM_Pos             16
#define ADC_CTL0_SYNCM_Msk             _AC(0x000f0000,U)      /*!< sync mode selection */
#define ADC_CTL0_SYNCM(x)              ((x) << ADC_CTL0_SYNCM_Pos)
#define ADC_CTL0_SYNCM_FREE            ADC_CTL0_SYNCM(0)      /*!< all the ADCs work independently */
#define ADC_CTL0_SYNCM_RPAR_IPAR       ADC_CTL0_SYNCM(1)      /*!< ADC0 and ADC1 work in combined regular parallel + inserted parallel mode */
#define ADC_CTL0_SYNCM_RPAR_IROT       ADC_CTL0_SYNCM(2)      /*!< ADC0 and ADC1 work in combined regular parallel + trigger rotation mode */
#define ADC_CTL0_SYNCM_IPAR_RFOL_FAST  ADC_CTL0_SYNCM(3)      /*!< ADC0 and ADC1 work in combined inserted parallel + follow-up fast mode */
#define ADC_CTL0_SYNCM_IPAR_RFOL_SLOW  ADC_CTL0_SYNCM(4)      /*!< ADC0 and ADC1 work in combined inserted parallel + follow-up slow mode */
#define ADC_CTL0_SYNCM_IPAR            ADC_CTL0_SYNCM(5)      /*!< ADC0 and ADC1 work in inserted parallel mode only */
#define ADC_CTL0_SYNCM_RPAR            ADC_CTL0_SYNCM(6)      /*!< ADC0 and ADC1 work in regular parallel mode only */
#define ADC_CTL0_SYNCM_RFOL_FAST       ADC_CTL0_SYNCM(7)      /*!< ADC0 and ADC1 work in follow-up fast mode only */
#define ADC_CTL0_SYNCM_RFOL_SLOW       ADC_CTL0_SYNCM(8)      /*!< ADC0 and ADC1 work in follow-up slow mode only */
#define ADC_CTL0_SYNCM_ITRIG_ROT       ADC_CTL0_SYNCM(9)      /*!< ADC0 and ADC1 work in trigger rotation mode only */
#define ADC_CTL0_DISNUM_Pos            13
#define ADC_CTL0_DISNUM_Msk            _AC(0x0000e000,U)      /*!< discontinuous mode channel count */
#define ADC_CTL0_DISNUM(x)             ((x) << ADC_CTL0_DISNUM_Pos)
#define ADC_CTL0_DISIC                 _BIT(12,U)             /*!< discontinuous mode on inserted channels */
#define ADC_CTL0_DISRC                 _BIT(11,U)             /*!< discontinuous mode on regular channels */
#define ADC_CTL0_ICA                   _BIT(10,U)             /*!< automatic inserted group conversion */
#define ADC_CTL0_WDSC                  _BIT(9,U)              /*!< when in scan mode, analog watchdog is effective on a single channel */
#define ADC_CTL0_SM                    _BIT(8,U)              /*!< scan mode */
#define ADC_CTL0_EOICIE                _BIT(7,U)              /*!< interrupt enable for inserted channels */
#define ADC_CTL0_WDEIE                 _BIT(6,U)              /*!< analog watchdog interrupt enable */
#define ADC_CTL0_EOCIE                 _BIT(5,U)              /*!< interrupt enable for EOC */
#define ADC_CTL0_WDCHSEL_Pos           0
#define ADC_CTL0_WDCHSEL_Msk           _AC(0x0000001f,U)      /*!< analog watchdog channel select bits */
#define ADC_CTL0_WDCHSEL(x)            ((x) << ADC_CTL0_WDCHSEL_Pos)

/* ADC_CTL1 */
#define ADC_CTL1_TSVREN                _BIT(23,U)             /*!< channel 16 and 17 enable of ADC0 */
#define ADC_CTL1_SWRCST                _BIT(22,U)             /*!< start on regular channels */
#define ADC_CTL1_SWICST                _BIT(21,U)             /*!< start on inserted channels */
#define ADC_CTL1_ETERC                 _BIT(20,U)             /*!< external trigger enable for regular channels */
#define ADC_CTL1_ETSRC_Pos             17
#define ADC_CTL1_ETSRC_Msk             _AC(0x000e0000,U)      /*!< external trigger select for regular channels */
#define ADC_CTL1_ETSRC(x)              ((x) << ADC_CTL1_ETSRC_Pos)
#define ADC_CTL1_ETSRC_T0_CH0          ADC_CTL1_ETSRC(0)      /*!< TIMER0 CH0 event select */
#define ADC_CTL1_ETSRC_T0_CH1          ADC_CTL1_ETSRC(1)      /*!< TIMER0 CH1 event select */
#define ADC_CTL1_ETSRC_T0_CH2          ADC_CTL1_ETSRC(2)      /*!< TIMER0 CH2 event select */
#define ADC_CTL1_ETSRC_T1_CH1          ADC_CTL1_ETSRC(3)      /*!< TIMER1 CH1 event select */
#define ADC_CTL1_ETSRC_T2_TRGO         ADC_CTL1_ETSRC(4)      /*!< TIMER2 TRGO event select */
#define ADC_CTL1_ETSRC_T3_CH3          ADC_CTL1_ETSRC(5)      /*!< TIMER3 CH3 event select */
#define ADC_CTL1_ETSRC_EXTI_11         ADC_CTL1_ETSRC(6)      /*!< external interrupt line 11 */
#define ADC_CTL1_ETSRC_SWRCST          ADC_CTL1_ETSRC(7)      /*!< software trigger */
#define ADC_CTL1_ETEIC                 _BIT(15,U)             /*!< external trigger enable for inserted channels */
#define ADC_CTL1_ETSIC_Pos             12
#define ADC_CTL1_ETSIC_Msk             _AC(0x00007000,U)      /*!< external trigger select for inserted channels */
#define ADC_CTL1_ETSIC(x)              ((x) << ADC_CTL1_ETSIC_Pos)
#define ADC_CTL1_ETSIC_T0_TRGO         ADC_CTL1_ETSIC(0)      /*!< TIMER0 TRGO event select */
#define ADC_CTL1_ETSIC_T0_CH3          ADC_CTL1_ETSIC(1)      /*!< TIMER0 CH3 event select */
#define ADC_CTL1_ETSIC_T1_TRGO         ADC_CTL1_ETSIC(2)      /*!< TIMER1 TRGO event select */
#define ADC_CTL1_ETSIC_T1_CH0          ADC_CTL1_ETSIC(3)      /*!< TIMER1 CH0 event select */
#define ADC_CTL1_ETSIC_T2_CH3          ADC_CTL1_ETSIC(4)      /*!< TIMER2 CH3 event select */
#define ADC_CTL1_ETSIC_T3_TRGO         ADC_CTL1_ETSIC(5)      /*!< TIMER3 TRGO event select */
#define ADC_CTL1_ETSIC_EXTI_15         ADC_CTL1_ETSIC(6)      /*!< external interrupt line 15 */
#define ADC_CTL1_ETSIC_SWICST          ADC_CTL1_ETSIC(7)      /*!< software trigger */
#define ADC_CTL1_DAL                   _BIT(11,U)             /*!< data alignment */
#define ADC_CTL1_DMA                   _BIT(8,U)              /*!< direct memory access mode */
#define ADC_CTL1_RSTCLB                _BIT(3,U)              /*!< reset calibration */
#define ADC_CTL1_CLB                   _BIT(2,U)              /*!< ADC calibration */
#define ADC_CTL1_CTN                   _BIT(1,U)              /*!< continuous conversion */
#define ADC_CTL1_ADCON                 _BIT(0,U)              /*!< ADC converter on */

/* ADC_SAMPT0 */
#define ADC_SAMPT0_SPT17_Pos           21
#define ADC_SAMPT0_SPT17_Msk           _AC(0x00e00000,U)      /*!< channel 17 sample time selection */
#define ADC_SAMPT0_SPT17(x)            ((x) << ADC_SAMPT0_SPT17_Pos)
#define ADC_SAMPT0_SPT16_Pos           18
#define ADC_SAMPT0_SPT16_Msk           _AC(0x001c0000,U)      /*!< channel 16 sample time selection */
#define ADC_SAMPT0_SPT16(x)            ((x) << ADC_SAMPT0_SPT16_Pos)
#define ADC_SAMPT0_SPT15_Pos           15
#define ADC_SAMPT0_SPT15_Msk           _AC(0x00038000,U)      /*!< channel 15 sample time selection */
#define ADC_SAMPT0_SPT15(x)            ((x) << ADC_SAMPT0_SPT15_Pos)
#define ADC_SAMPT0_SPT14_Pos           12
#define ADC_SAMPT0_SPT14_Msk           _AC(0x00007000,U)      /*!< channel 14 sample time selection */
#define ADC_SAMPT0_SPT14(x)            ((x) << ADC_SAMPT0_SPT14_Pos)
#define ADC_SAMPT0_SPT13_Pos           9
#define ADC_SAMPT0_SPT13_Msk           _AC(0x00000e00,U)      /*!< channel 13 sample time selection */
#define ADC_SAMPT0_SPT13(x)            ((x) << ADC_SAMPT0_SPT13_Pos)
#define ADC_SAMPT0_SPT12_Pos           6
#define ADC_SAMPT0_SPT12_Msk           _AC(0x000001c0,U)      /*!< channel 12 sample time selection */
#define ADC_SAMPT0_SPT12(x)            ((x) << ADC_SAMPT0_SPT12_Pos)
#define ADC_SAMPT0_SPT11_Pos           3
#define ADC_SAMPT0_SPT11_Msk           _AC(0x00000038,U)      /*!< channel 11 sample time selection */
#define ADC_SAMPT0_SPT11(x)            ((x) << ADC_SAMPT0_SPT11_Pos)
#define ADC_SAMPT0_SPT10_Pos           0
#define ADC_SAMPT0_SPT10_Msk           _AC(0x00000007,U)      /*!< channel 10 sample time selection */
#define ADC_SAMPT0_SPT10(x)            ((x) << ADC_SAMPT0_SPT10_Pos)

/* ADC_SAMPT1 */
#define ADC_SAMPT1_SPT9_Pos            27
#define ADC_SAMPT1_SPT9_Msk            _AC(0x38000000,U)      /*!< channel 9 sample time selection */
#define ADC_SAMPT1_SPT9(x)             ((x) << ADC_SAMPT1_SPT9_Pos)
#define ADC_SAMPT1_SPT8_Pos            24
#define ADC_SAMPT1_SPT8_Msk            _AC(0x07000000,U)      /*!< channel 8 sample time selection */
#define ADC_SAMPT1_SPT8(x)             ((x) << ADC_SAMPT1_SPT8_Pos)
#define ADC_SAMPT1_SPT7_Pos            21
#define ADC_SAMPT1_SPT7_Msk            _AC(0x00e00000,U)      /*!< channel 7 sample time selection */
#define ADC_SAMPT1_SPT7(x)             ((x) << ADC_SAMPT1_SPT7_Pos)
#define ADC_SAMPT1_SPT6_Pos            18
#define ADC_SAMPT1_SPT6_Msk            _AC(0x001c0000,U)      /*!< channel 6 sample time selection */
#define ADC_SAMPT1_SPT6(x)             ((x) << ADC_SAMPT1_SPT6_Pos)
#define ADC_SAMPT1_SPT5_Pos            15
#define ADC_SAMPT1_SPT5_Msk            _AC(0x00038000,U)      /*!< channel 5 sample time selection */
#define ADC_SAMPT1_SPT5(x)             ((x) << ADC_SAMPT1_SPT5_Pos)
#define ADC_SAMPT1_SPT4_Pos            12
#define ADC_SAMPT1_SPT4_Msk            _AC(0x00007000,U)      /*!< channel 4 sample time selection */
#define ADC_SAMPT1_SPT4(x)             ((x) << ADC_SAMPT1_SPT4_Pos)
#define ADC_SAMPT1_SPT3_Pos            9
#define ADC_SAMPT1_SPT3_Msk            _AC(0x00000e00,U)      /*!< channel 3 sample time selection */
#define ADC_SAMPT1_SPT3(x)             ((x) << ADC_SAMPT1_SPT3_Pos)
#define ADC_SAMPT1_SPT2_Pos            6
#define ADC_SAMPT1_SPT2_Msk            _AC(0x000001c0,U)      /*!< channel 2 sample time selection */
#define ADC_SAMPT1_SPT2(x)             ((x) << ADC_SAMPT1_SPT2_Pos)
#define ADC_SAMPT1_SPT1_Pos            3
#define ADC_SAMPT1_SPT1_Msk            _AC(0x00000038,U)      /*!< channel 1 sample time selection */
#define ADC_SAMPT1_SPT1(x)             ((x) << ADC_SAMPT1_SPT1_Pos)
#define ADC_SAMPT1_SPT0_Pos            0
#define ADC_SAMPT1_SPT0_Msk            _AC(0x00000007,U)      /*!< channel 0 sample time selection */
#define ADC_SAMPT1_SPT0(x)             ((x) << ADC_SAMPT1_SPT0_Pos)

/* ADC_IOFFx x=0..3 */
#define ADC_IOFFX_IOFF_Pos             0
#define ADC_IOFFX_IOFF_Msk             _AC(0x00000fff,U)      /*!< data offset for inserted channel x */
#define ADC_IOFFX_IOFF(x)              ((x) << ADC_IOFFX_IOFF_Pos)

/* ADC_WDHT */
#define ADC_WDHT_WDHT_Pos              0
#define ADC_WDHT_WDHT_Msk              _AC(0x00000fff,U)      /*!< analog watchdog high threshold */
#define ADC_WDHT_WDHT(x)               ((x) << ADC_WDHT_WDHT_Pos)

/* ADC_WDLT */
#define ADC_WDLT_WDLT_Pos              0
#define ADC_WDLT_WDLT_Msk              _AC(0x00000fff,U)      /*!< analog watchdog low threshold */
#define ADC_WDLT_WDLT(x)               ((x) << ADC_WDLT_WDLT_Pos)

/* ADC_RSQ0 */
#define ADC_RSQ0_RL_Pos                20
#define ADC_RSQ0_RL_Msk                _AC(0x00f00000,U)      /*!< regular channel sequence length */
#define ADC_RSQ0_RL(x)                 ((x) << ADC_RSQ0_RL_Pos)
#define ADC_RSQ0_RSQ15_Pos             15
#define ADC_RSQ0_RSQ15_Msk             _AC(0x000f8000,U)      /*!< 15th conversion in regular sequence */
#define ADC_RSQ0_RSQ15(x)              ((x) << ADC_RSQ0_RSQ15_Pos)
#define ADC_RSQ0_RSQ14_Pos             10
#define ADC_RSQ0_RSQ14_Msk             _AC(0x00007c00,U)      /*!< 14th conversion in regular sequence */
#define ADC_RSQ0_RSQ14(x)              ((x) << ADC_RSQ0_RSQ14_Pos)
#define ADC_RSQ0_RSQ13_Pos             5
#define ADC_RSQ0_RSQ13_Msk             _AC(0x000003e0,U)      /*!< 13th conversion in regular sequence */
#define ADC_RSQ0_RSQ13(x)              ((x) << ADC_RSQ0_RSQ13_Pos)
#define ADC_RSQ0_RSQ12_Pos             0
#define ADC_RSQ0_RSQ12_Msk             _AC(0x0000001f,U)      /*!< 12th conversion in regular sequence */
#define ADC_RSQ0_RSQ12(x)              ((x) << ADC_RSQ0_RSQ12_Pos)

/* ADC_RSQ1 */
#define ADC_RSQ1_RSQ11_Pos             25
#define ADC_RSQ1_RSQ11_Msk             _AC(0x3e000000,U)      /*!< 11th conversion in regular sequence */
#define ADC_RSQ1_RSQ11(x)              ((x) << ADC_RSQ1_RSQ11_Pos)
#define ADC_RSQ1_RSQ10_Pos             20
#define ADC_RSQ1_RSQ10_Msk             _AC(0x01f00000,U)      /*!< 10th conversion in regular sequence */
#define ADC_RSQ1_RSQ10(x)              ((x) << ADC_RSQ1_RSQ10_Pos)
#define ADC_RSQ1_RSQ9_Pos              15
#define ADC_RSQ1_RSQ9_Msk              _AC(0x000f8000,U)      /*!< 9th conversion in regular sequence */
#define ADC_RSQ1_RSQ9(x)               ((x) << ADC_RSQ1_RSQ9_Pos)
#define ADC_RSQ1_RSQ8_Pos              10
#define ADC_RSQ1_RSQ8_Msk              _AC(0x00007c00,U)      /*!< 8th conversion in regular sequence */
#define ADC_RSQ1_RSQ8(x)               ((x) << ADC_RSQ1_RSQ8_Pos)
#define ADC_RSQ1_RSQ7_Pos              5
#define ADC_RSQ1_RSQ7_Msk              _AC(0x000003e0,U)      /*!< 7th conversion in regular sequence */
#define ADC_RSQ1_RSQ7(x)               ((x) << ADC_RSQ1_RSQ7_Pos)
#define ADC_RSQ1_RSQ6_Pos              0
#define ADC_RSQ1_RSQ6_Msk              _AC(0x0000001f,U)      /*!< 6th conversion in regular sequence */
#define ADC_RSQ1_RSQ6(x)               ((x) << ADC_RSQ1_RSQ6_Pos)

/* ADC_RSQ2 */
#define ADC_RSQ2_RSQ5_Pos              25
#define ADC_RSQ2_RSQ5_Msk              _AC(0x3e000000,U)      /*!< 5th conversion in regular sequence */
#define ADC_RSQ2_RSQ5(x)               ((x) << ADC_RSQ2_RSQ5_Pos)
#define ADC_RSQ2_RSQ4_Pos              20
#define ADC_RSQ2_RSQ4_Msk              _AC(0x01f00000,U)      /*!< 4th conversion in regular sequence */
#define ADC_RSQ2_RSQ4(x)               ((x) << ADC_RSQ2_RSQ4_Pos)
#define ADC_RSQ2_RSQ3_Pos              15
#define ADC_RSQ2_RSQ3_Msk              _AC(0x000f8000,U)      /*!< 3rd conversion in regular sequence */
#define ADC_RSQ2_RSQ3(x)               ((x) << ADC_RSQ2_RSQ3_Pos)
#define ADC_RSQ2_RSQ2_Pos              10
#define ADC_RSQ2_RSQ2_Msk              _AC(0x00007c00,U)      /*!< 2nd conversion in regular sequence */
#define ADC_RSQ2_RSQ2(x)               ((x) << ADC_RSQ2_RSQ2_Pos)
#define ADC_RSQ2_RSQ1_Pos              5
#define ADC_RSQ2_RSQ1_Msk              _AC(0x000003e0,U)      /*!< 1st conversion in regular sequence */
#define ADC_RSQ2_RSQ1(x)               ((x) << ADC_RSQ2_RSQ1_Pos)
#define ADC_RSQ2_RSQ0_Pos              0
#define ADC_RSQ2_RSQ0_Msk              _AC(0x0000001f,U)      /*!< 0th conversion in regular sequence */
#define ADC_RSQ2_RSQ0(x)               ((x) << ADC_RSQ2_RSQ0_Pos)

/* ADC_ISQ */
#define ADC_ISQ_IL_Pos                 20
#define ADC_ISQ_IL_Msk                 _AC(0x00300000,U)      /*!< inserted sequence length */
#define ADC_ISQ_IL(x)                  ((x) << ADC_ISQ_IL_Pos)
#define ADC_ISQ_ISQ3_Pos               15
#define ADC_ISQ_ISQ3_Msk               _AC(0x000f8000,U)      /*!< 3rd conversion in inserted sequence */
#define ADC_ISQ_ISQ3(x)                ((x) << ADC_ISQ_ISQ3_Pos)
#define ADC_ISQ_ISQ2_Pos               10
#define ADC_ISQ_ISQ2_Msk               _AC(0x00007c00,U)      /*!< 2nd conversion in inserted sequence */
#define ADC_ISQ_ISQ2(x)                ((x) << ADC_ISQ_ISQ2_Pos)
#define ADC_ISQ_ISQ1_Pos               5
#define ADC_ISQ_ISQ1_Msk               _AC(0x000003e0,U)      /*!< 1st conversion in inserted sequence */
#define ADC_ISQ_ISQ1(x)                ((x) << ADC_ISQ_ISQ1_Pos)
#define ADC_ISQ_ISQ0_Pos               0
#define ADC_ISQ_ISQ0_Msk               _AC(0x0000001f,U)      /*!< 0th conversion in inserted sequence */
#define ADC_ISQ_ISQ0(x)                ((x) << ADC_ISQ_ISQ0_Pos)

/* ADC_IDATAx x=0..3*/
#define ADC_IDATAX_IDATAN_Pos          0
#define ADC_IDATAX_IDATAN_Msk          _AC(0x0000ffff,U)      /*!< inserted data n */
#define ADC_IDATAX_IDATAN(x)           ((x) << ADC_IDATAX_IDATAN_Pos)

/* ADC_RDATA */
#define ADC_RDATA_ADC1RDTR_Pos         16
#define ADC_RDATA_ADC1RDTR_Msk         _AC(0xffff0000,U)      /*!< ADC1 regular channel data */
#define ADC_RDATA_ADC1RDTR(x)          ((x) << ADC_RDATA_ADC1RDTR_Pos)
#define ADC_RDATA_RDATA_Pos            0
#define ADC_RDATA_RDATA_Msk            _AC(0x0000ffff,U)      /*!< regular data */
#define ADC_RDATA_RDATA(x)             ((x) << ADC_RDATA_RDATA_Pos)

/* ADC_OVSAMPCTL */
#define ADC_OVSAMPCTL_DRES_Pos         12
#define ADC_OVSAMPCTL_DRES_Msk         _AC(0x00003000,U)      /*!< ADC data resolution */
#define ADC_OVSAMPCTL_DRES(x)          ((x) << ADC_OVSAMPCTL_DRES_Pos)
#define ADC_OVSAMPCTL_DRES_12B         ADC_OVSAMPCTL_DRES(0)  /*!< 12-bit ADC resolution */
#define ADC_OVSAMPCTL_DRES_10B         ADC_OVSAMPCTL_DRES(1)  /*!< 10-bit ADC resolution */
#define ADC_OVSAMPCTL_DRES_8B          ADC_OVSAMPCTL_DRES(2)  /*!< 8-bit ADC resolution */
#define ADC_OVSAMPCTL_DRES_6B          ADC_OVSAMPCTL_DRES(3)  /*!< 6-bit ADC resolution */
#define ADC_OVSAMPCTL_TOVS             _BIT(9,U)              /*!< triggered oversampling */
#define ADC_OVSAMPCTL_OVSS_Pos         5
#define ADC_OVSAMPCTL_OVSS_Msk         _AC(0x000001e0,U)      /*!< oversampling shift */
#define ADC_OVSAMPCTL_OVSS(x)          ((x) << ADC_OVSAMPCTL_OVSS_Pos)
#define ADC_OVSAMPCTL_OVSS_NONE        ADC_OVSAMPCTL_OVSS(0)  /*!< no oversampling shift */
#define ADC_OVSAMPCTL_OVSS_1B          ADC_OVSAMPCTL_OVSS(1)  /*!< 1-bit oversampling shift */
#define ADC_OVSAMPCTL_OVSS_2B          ADC_OVSAMPCTL_OVSS(2)  /*!< 2-bit oversampling shift */
#define ADC_OVSAMPCTL_OVSS_3B          ADC_OVSAMPCTL_OVSS(3)  /*!< 3-bit oversampling shift */
#define ADC_OVSAMPCTL_OVSS_4B          ADC_OVSAMPCTL_OVSS(4)  /*!< 4-bit oversampling shift */
#define ADC_OVSAMPCTL_OVSS_5B          ADC_OVSAMPCTL_OVSS(5)  /*!< 5-bit oversampling shift */
#define ADC_OVSAMPCTL_OVSS_6B          ADC_OVSAMPCTL_OVSS(6)  /*!< 6-bit oversampling shift */
#define ADC_OVSAMPCTL_OVSS_7B          ADC_OVSAMPCTL_OVSS(7)  /*!< 7-bit oversampling shift */
#define ADC_OVSAMPCTL_OVSS_8B          ADC_OVSAMPCTL_OVSS(8)  /*!< 8-bit oversampling shift */
#define ADC_OVSAMPCTL_OVSR_Pos         2
#define ADC_OVSAMPCTL_OVSR_Msk         _AC(0x0000001c,U)      /*!< oversampling ratio */
#define ADC_OVSAMPCTL_OVSR(x)          ((x) << ADC_OVSAMPCTL_OVSR_Pos)
#define ADC_OVSAMPCTL_OVSR_MUL2        ADC_OVSAMPCTL_OVSR(0)  /*!< oversampling ratio X2 */
#define ADC_OVSAMPCTL_OVSR_MUL4        ADC_OVSAMPCTL_OVSR(1)  /*!< oversampling ratio X4 */
#define ADC_OVSAMPCTL_OVSR_MUL8        ADC_OVSAMPCTL_OVSR(2)  /*!< oversampling ratio X8 */
#define ADC_OVSAMPCTL_OVSR_MUL16       ADC_OVSAMPCTL_OVSR(3)  /*!< oversampling ratio X16 */
#define ADC_OVSAMPCTL_OVSR_MUL32       ADC_OVSAMPCTL_OVSR(4)  /*!< oversampling ratio X32 */
#define ADC_OVSAMPCTL_OVSR_MUL64       ADC_OVSAMPCTL_OVSR(5)  /*!< oversampling ratio X64 */
#define ADC_OVSAMPCTL_OVSR_MUL128      ADC_OVSAMPCTL_OVSR(6)  /*!< oversampling ratio X128 */
#define ADC_OVSAMPCTL_OVSR_MUL256      ADC_OVSAMPCTL_OVSR(7)  /*!< oversampling ratio X256 */
#define ADC_OVSAMPCTL_OVSEN            _BIT(0,U)              /*!< oversampling enable */

/* constants definitions */
#define ADC_SAMPLETIME_1POINT5         _AC(0,U)               /*!< 1.5 sampling cycles */
#define ADC_SAMPLETIME_7POINT5         _AC(1,U)               /*!< 7.5 sampling cycles */
#define ADC_SAMPLETIME_13POINT5        _AC(2,U)               /*!< 13.5 sampling cycles */
#define ADC_SAMPLETIME_28POINT5        _AC(3,U)               /*!< 28.5 sampling cycles */
#define ADC_SAMPLETIME_41POINT5        _AC(4,U)               /*!< 41.5 sampling cycles */
#define ADC_SAMPLETIME_55POINT5        _AC(5,U)               /*!< 55.5 sampling cycles */
#define ADC_SAMPLETIME_71POINT5        _AC(6,U)               /*!< 71.5 sampling cycles */
#define ADC_SAMPLETIME_239POINT5       _AC(7,U)               /*!< 239.5 sampling cycles */

/* ----------------------- BKP ---------------------------- */

#define BKP_BASE                       _AC(0x40006C00,UL)  /*!< BKP base address */

/* register definitions */
#define BKP_DATA0                      _AC(0x04,UL)  /*!< BKP data register 0 */
#define BKP_DATA1                      _AC(0x08,UL)  /*!< BKP data register 1 */
#define BKP_DATA2                      _AC(0x0C,UL)  /*!< BKP data register 2 */
#define BKP_DATA3                      _AC(0x10,UL)  /*!< BKP data register 3 */
#define BKP_DATA4                      _AC(0x14,UL)  /*!< BKP data register 4 */
#define BKP_DATA5                      _AC(0x18,UL)  /*!< BKP data register 5 */
#define BKP_DATA6                      _AC(0x1C,UL)  /*!< BKP data register 6 */
#define BKP_DATA7                      _AC(0x20,UL)  /*!< BKP data register 7 */
#define BKP_DATA8                      _AC(0x24,UL)  /*!< BKP data register 8 */
#define BKP_DATA9                      _AC(0x28,UL)  /*!< BKP data register 9 */
#define BKP_OCTL                       _AC(0x2C,UL)  /*!< RTC signal output control register */
#define BKP_TPCTL                      _AC(0x30,UL)  /*!< tamper pin control register */
#define BKP_TPCS                       _AC(0x34,UL)  /*!< tamper control and status register */
#define BKP_DATA10                     _AC(0x40,UL)  /*!< BKP data register 10 */
#define BKP_DATA11                     _AC(0x44,UL)  /*!< BKP data register 11 */
#define BKP_DATA12                     _AC(0x48,UL)  /*!< BKP data register 12 */
#define BKP_DATA13                     _AC(0x4C,UL)  /*!< BKP data register 13 */
#define BKP_DATA14                     _AC(0x50,UL)  /*!< BKP data register 14 */
#define BKP_DATA15                     _AC(0x54,UL)  /*!< BKP data register 15 */
#define BKP_DATA16                     _AC(0x58,UL)  /*!< BKP data register 16 */
#define BKP_DATA17                     _AC(0x5C,UL)  /*!< BKP data register 17 */
#define BKP_DATA18                     _AC(0x60,UL)  /*!< BKP data register 18 */
#define BKP_DATA19                     _AC(0x64,UL)  /*!< BKP data register 19 */
#define BKP_DATA20                     _AC(0x68,UL)  /*!< BKP data register 20 */
#define BKP_DATA21                     _AC(0x6C,UL)  /*!< BKP data register 21 */
#define BKP_DATA22                     _AC(0x70,UL)  /*!< BKP data register 22 */
#define BKP_DATA23                     _AC(0x74,UL)  /*!< BKP data register 23 */
#define BKP_DATA24                     _AC(0x78,UL)  /*!< BKP data register 24 */
#define BKP_DATA25                     _AC(0x7C,UL)  /*!< BKP data register 25 */
#define BKP_DATA26                     _AC(0x80,UL)  /*!< BKP data register 26 */
#define BKP_DATA27                     _AC(0x84,UL)  /*!< BKP data register 27 */
#define BKP_DATA28                     _AC(0x88,UL)  /*!< BKP data register 28 */
#define BKP_DATA29                     _AC(0x8C,UL)  /*!< BKP data register 29 */
#define BKP_DATA30                     _AC(0x90,UL)  /*!< BKP data register 30 */
#define BKP_DATA31                     _AC(0x94,UL)  /*!< BKP data register 31 */
#define BKP_DATA32                     _AC(0x98,UL)  /*!< BKP data register 32 */
#define BKP_DATA33                     _AC(0x9C,UL)  /*!< BKP data register 33 */
#define BKP_DATA34                     _AC(0xA0,UL)  /*!< BKP data register 34 */
#define BKP_DATA35                     _AC(0xA4,UL)  /*!< BKP data register 35 */
#define BKP_DATA36                     _AC(0xA8,UL)  /*!< BKP data register 36 */
#define BKP_DATA37                     _AC(0xAC,UL)  /*!< BKP data register 37 */
#define BKP_DATA38                     _AC(0xB0,UL)  /*!< BKP data register 38 */
#define BKP_DATA39                     _AC(0xB4,UL)  /*!< BKP data register 39 */
#define BKP_DATA40                     _AC(0xB8,UL)  /*!< BKP data register 40 */
#define BKP_DATA41                     _AC(0xBC,UL)  /*!< BKP data register 41 */

/* BKP_DATA */
#define BKP_DATA_Pos                   0
#define BKP_DATA_Msk                   _AC(0x0000ffff,U)  /*!< backup data */
#define BKP_DATA(x)                    ((x) << BKP_DATA_Pos)

/* BKP_OCTL */
#define BKP_OCTL_ROSEL                 _BIT(9,U)          /*!< RTC output selection */
#define BKP_OCTL_ASOEN                 _BIT(8,U)          /*!< RTC alarm or second signal output enable */
#define BKP_OCTL_COEN                  _BIT(7,U)          /*!< RTC clock calibration output enable */
#define BKP_OCTL_RCCV_Pos              0
#define BKP_OCTL_RCCV_Msk              _AC(0x0000007f,U)  /*!< RTC clock calibration value */
#define BKP_OCTL_RCCV(x)               ((x) << BKP_OCTL_RCCV_Pos)

/* BKP_TPCTL */
#define BKP_TPCTL_TPAL                 _BIT(1,U)          /*!< tamper pin active level */
#define BKP_TPCTL_TPEN                 _BIT(0,U)          /*!< tamper detection enable */

/* BKP_TPCS */
#define BKP_TPCS_TIF                   _BIT(9,U)          /*!< tamper interrupt flag */
#define BKP_TPCS_TEF                   _BIT(8,U)          /*!< tamper event flag */
#define BKP_TPCS_TPIE                  _BIT(2,U)          /*!< tamper interrupt enable */
#define BKP_TPCS_TIR                   _BIT(1,U)          /*!< tamper interrupt reset */
#define BKP_TPCS_TER                   _BIT(0,U)          /*!< tamper event reset */

/* ----------------------- CAN ---------------------------- */

#define CAN0_BASE                      _AC(0x40006400,UL)  /*!< CAN0 base address */
#define CAN1_BASE                      _AC(0x40006800,UL)  /*!< CAN1 base address */

/* register definitions */
#define CAN_CTL                        _AC(0x000,UL)  /*!< CAN control register */
#define CAN_STAT                       _AC(0x004,UL)  /*!< CAN status register */
#define CAN_TSTAT                      _AC(0x008,UL)  /*!< CAN transmit status register*/
#define CAN_RFIFO0                     _AC(0x00C,UL)  /*!< CAN receive FIFO0 register */
#define CAN_RFIFO1                     _AC(0x010,UL)  /*!< CAN receive FIFO1 register */
#define CAN_INTEN                      _AC(0x014,UL)  /*!< CAN interrupt enable register */
#define CAN_ERR                        _AC(0x018,UL)  /*!< CAN error register */
#define CAN_BT                         _AC(0x01C,UL)  /*!< CAN bit timing register */
#define CAN_TMI0                       _AC(0x180,UL)  /*!< CAN transmit mailbox0 identifier register */
#define CAN_TMP0                       _AC(0x184,UL)  /*!< CAN transmit mailbox0 property register */
#define CAN_TMDATA00                   _AC(0x188,UL)  /*!< CAN transmit mailbox0 data0 register */
#define CAN_TMDATA10                   _AC(0x18C,UL)  /*!< CAN transmit mailbox0 data1 register */
#define CAN_TMI1                       _AC(0x190,UL)  /*!< CAN transmit mailbox1 identifier register */
#define CAN_TMP1                       _AC(0x194,UL)  /*!< CAN transmit mailbox1 property register */
#define CAN_TMDATA01                   _AC(0x198,UL)  /*!< CAN transmit mailbox1 data0 register */
#define CAN_TMDATA11                   _AC(0x19C,UL)  /*!< CAN transmit mailbox1 data1 register */
#define CAN_TMI2                       _AC(0x1A0,UL)  /*!< CAN transmit mailbox2 identifier register */
#define CAN_TMP2                       _AC(0x1A4,UL)  /*!< CAN transmit mailbox2 property register */
#define CAN_TMDATA02                   _AC(0x1A8,UL)  /*!< CAN transmit mailbox2 data0 register */
#define CAN_TMDATA12                   _AC(0x1AC,UL)  /*!< CAN transmit mailbox2 data1 register */
#define CAN_RFIFOMI0                   _AC(0x1B0,UL)  /*!< CAN receive FIFO0 mailbox identifier register */
#define CAN_RFIFOMP0                   _AC(0x1B4,UL)  /*!< CAN receive FIFO0 mailbox property register */
#define CAN_RFIFOMDATA00               _AC(0x1B8,UL)  /*!< CAN receive FIFO0 mailbox data0 register */
#define CAN_RFIFOMDATA10               _AC(0x1BC,UL)  /*!< CAN receive FIFO0 mailbox data1 register */
#define CAN_RFIFOMI1                   _AC(0x1C0,UL)  /*!< CAN receive FIFO1 mailbox identifier register */
#define CAN_RFIFOMP1                   _AC(0x1C4,UL)  /*!< CAN receive FIFO1 mailbox property register */
#define CAN_RFIFOMDATA01               _AC(0x1C8,UL)  /*!< CAN receive FIFO1 mailbox data0 register */
#define CAN_RFIFOMDATA11               _AC(0x1CC,UL)  /*!< CAN receive FIFO1 mailbox data1 register */
#define CAN_FCTL                       _AC(0x200,UL)  /*!< CAN filter control register */
#define CAN_FMCFG                      _AC(0x204,UL)  /*!< CAN filter mode register */
#define CAN_FSCFG                      _AC(0x20C,UL)  /*!< CAN filter scale register */
#define CAN_FAFIFO                     _AC(0x214,UL)  /*!< CAN filter associated FIFO register */
#define CAN_FW                         _AC(0x21C,UL)  /*!< CAN filter working register */
#define CAN_F0DATA0                    _AC(0x240,UL)  /*!< CAN filter 0 data 0 register */
#define CAN_F0DATA1                    _AC(0x244,UL)  /*!< CAN filter 0 data 1 register */
#define CAN_F1DATA0                    _AC(0x248,UL)  /*!< CAN filter 1 data 0 register */
#define CAN_F1DATA1                    _AC(0x24C,UL)  /*!< CAN filter 1 data 1 register */
#define CAN_F2DATA0                    _AC(0x250,UL)  /*!< CAN filter 2 data 0 register */
#define CAN_F2DATA1                    _AC(0x254,UL)  /*!< CAN filter 2 data 1 register */
#define CAN_F3DATA0                    _AC(0x258,UL)  /*!< CAN filter 3 data 0 register */
#define CAN_F3DATA1                    _AC(0x25C,UL)  /*!< CAN filter 3 data 1 register */
#define CAN_F4DATA0                    _AC(0x260,UL)  /*!< CAN filter 4 data 0 register */
#define CAN_F4DATA1                    _AC(0x264,UL)  /*!< CAN filter 4 data 1 register */
#define CAN_F5DATA0                    _AC(0x268,UL)  /*!< CAN filter 5 data 0 register */
#define CAN_F5DATA1                    _AC(0x26C,UL)  /*!< CAN filter 5 data 1 register */
#define CAN_F6DATA0                    _AC(0x270,UL)  /*!< CAN filter 6 data 0 register */
#define CAN_F6DATA1                    _AC(0x274,UL)  /*!< CAN filter 6 data 1 register */
#define CAN_F7DATA0                    _AC(0x278,UL)  /*!< CAN filter 7 data 0 register */
#define CAN_F7DATA1                    _AC(0x27C,UL)  /*!< CAN filter 7 data 1 register */
#define CAN_F8DATA0                    _AC(0x280,UL)  /*!< CAN filter 8 data 0 register */
#define CAN_F8DATA1                    _AC(0x284,UL)  /*!< CAN filter 8 data 1 register */
#define CAN_F9DATA0                    _AC(0x288,UL)  /*!< CAN filter 9 data 0 register */
#define CAN_F9DATA1                    _AC(0x28C,UL)  /*!< CAN filter 9 data 1 register */
#define CAN_F10DATA0                   _AC(0x290,UL)  /*!< CAN filter 10 data 0 register */
#define CAN_F10DATA1                   _AC(0x294,UL)  /*!< CAN filter 10 data 1 register */
#define CAN_F11DATA0                   _AC(0x298,UL)  /*!< CAN filter 11 data 0 register */
#define CAN_F11DATA1                   _AC(0x29C,UL)  /*!< CAN filter 11 data 1 register */
#define CAN_F12DATA0                   _AC(0x2A0,UL)  /*!< CAN filter 12 data 0 register */
#define CAN_F12DATA1                   _AC(0x2A4,UL)  /*!< CAN filter 12 data 1 register */
#define CAN_F13DATA0                   _AC(0x2A8,UL)  /*!< CAN filter 13 data 0 register */
#define CAN_F13DATA1                   _AC(0x2AC,UL)  /*!< CAN filter 13 data 1 register */
#define CAN_F14DATA0                   _AC(0x2B0,UL)  /*!< CAN filter 14 data 0 register */
#define CAN_F14DATA1                   _AC(0x2B4,UL)  /*!< CAN filter 14 data 1 register */
#define CAN_F15DATA0                   _AC(0x2B8,UL)  /*!< CAN filter 15 data 0 register */
#define CAN_F15DATA1                   _AC(0x2BC,UL)  /*!< CAN filter 15 data 1 register */
#define CAN_F16DATA0                   _AC(0x2C0,UL)  /*!< CAN filter 16 data 0 register */
#define CAN_F16DATA1                   _AC(0x2C4,UL)  /*!< CAN filter 16 data 1 register */
#define CAN_F17DATA0                   _AC(0x2C8,UL)  /*!< CAN filter 17 data 0 register */
#define CAN_F17DATA1                   _AC(0x2CC,UL)  /*!< CAN filter 17 data 1 register */
#define CAN_F18DATA0                   _AC(0x2D0,UL)  /*!< CAN filter 18 data 0 register */
#define CAN_F18DATA1                   _AC(0x2D4,UL)  /*!< CAN filter 18 data 1 register */
#define CAN_F19DATA0                   _AC(0x2D8,UL)  /*!< CAN filter 19 data 0 register */
#define CAN_F19DATA1                   _AC(0x2DC,UL)  /*!< CAN filter 19 data 1 register */
#define CAN_F20DATA0                   _AC(0x2E0,UL)  /*!< CAN filter 20 data 0 register */
#define CAN_F20DATA1                   _AC(0x2E4,UL)  /*!< CAN filter 20 data 1 register */
#define CAN_F21DATA0                   _AC(0x2E8,UL)  /*!< CAN filter 21 data 0 register */
#define CAN_F21DATA1                   _AC(0x2EC,UL)  /*!< CAN filter 21 data 1 register */
#define CAN_F22DATA0                   _AC(0x2F0,UL)  /*!< CAN filter 22 data 0 register */
#define CAN_F22DATA1                   _AC(0x2F4,UL)  /*!< CAN filter 22 data 1 register */
#define CAN_F23DATA0                   _AC(0x2F8,UL)  /*!< CAN filter 23 data 0 register */
#define CAN_F23DATA1                   _AC(0x2FC,UL)  /*!< CAN filter 23 data 1 register */
#define CAN_F24DATA0                   _AC(0x300,UL)  /*!< CAN filter 24 data 0 register */
#define CAN_F24DATA1                   _AC(0x304,UL)  /*!< CAN filter 24 data 1 register */
#define CAN_F25DATA0                   _AC(0x308,UL)  /*!< CAN filter 25 data 0 register */
#define CAN_F25DATA1                   _AC(0x30C,UL)  /*!< CAN filter 25 data 1 register */
#define CAN_F26DATA0                   _AC(0x310,UL)  /*!< CAN filter 26 data 0 register */
#define CAN_F26DATA1                   _AC(0x314,UL)  /*!< CAN filter 26 data 1 register */
#define CAN_F27DATA0                   _AC(0x318,UL)  /*!< CAN filter 27 data 0 register */
#define CAN_F27DATA1                   _AC(0x31C,UL)  /*!< CAN filter 27 data 1 register */

/* CAN transmit mailbox bank */
#define CAN_TMI(x)                     (_AC(0x180,UL) + ((x) * _AC(0x10,UL)))  /*!< CAN transmit mailbox identifier register */
#define CAN_TMP(x)                     (_AC(0x184,UL) + ((x) * _AC(0x10,UL)))  /*!< CAN transmit mailbox property register */
#define CAN_TMDATA0(x)                 (_AC(0x188,UL) + ((x) * _AC(0x10,UL)))  /*!< CAN transmit mailbox data0 register */
#define CAN_TMDATA1(x)                 (_AC(0x18C,UL) + ((x) * _AC(0x10,UL)))  /*!< CAN transmit mailbox data1 register */

/* CAN receive fifo mailbox bank */
#define CAN_RFIFOMI(x)                 (_AC(0x1B0,UL) + ((x) * _AC(0x10,UL)))  /*!< CAN receive fifo mailbox identifier register */
#define CAN_RFIFOMP(x)                 (_AC(0x1B4,UL) + ((x) * _AC(0x10,UL)))  /*!< CAN receive fifo mailbox property register */
#define CAN_RFIFOMDATA0(x)             (_AC(0x1B8,UL) + ((x) * _AC(0x10,UL)))  /*!< CAN receive fifo mailbox data0 register */
#define CAN_RFIFOMDATA1(x)             (_AC(0x1BC,UL) + ((x) * _AC(0x10,UL)))  /*!< CAN receive fifo mailbox data1 register */

/* CAN filter bank */
#define CAN_FDATA0(x)                  (_AC(0x240,UL) + ((x) * _AC(0x08,UL)))  /*!< CAN filter data 0 register */
#define CAN_FDATA1(x)                  (_AC(0x244,UL) + ((x) * _AC(0x08,UL)))  /*!< CAN filter data 1 register */

/* CAN_CTL */
#define CAN_CTL_DFZ                    _BIT(16,U)         /*!< CAN debug freeze */
#define CAN_CTL_SWRST                  _BIT(15,U)         /*!< CAN software reset */
#define CAN_CTL_TTC                    _BIT(7,U)          /*!< time triggered communication */
#define CAN_CTL_ABOR                   _BIT(6,U)          /*!< automatic bus-off recovery */
#define CAN_CTL_AWU                    _BIT(5,U)          /*!< automatic wakeup */
#define CAN_CTL_ARD                    _BIT(4,U)          /*!< automatic retransmission disable */
#define CAN_CTL_RFOD                   _BIT(3,U)          /*!< receive FIFO overwrite disable */
#define CAN_CTL_TFO                    _BIT(2,U)          /*!< transmit FIFO order */
#define CAN_CTL_SLPWMOD                _BIT(1,U)          /*!< sleep working mode */
#define CAN_CTL_IWMOD                  _BIT(0,U)          /*!< initial working mode */

/* CAN_STAT */
#define CAN_STAT_RXL                   _BIT(11,U)         /*!< CAN rx signal */
#define CAN_STAT_LASTRX                _BIT(10,U)         /*!< last sample value of rx pin */
#define CAN_STAT_RS                    _BIT(9,U)          /*!< receiving state */
#define CAN_STAT_TS                    _BIT(8,U)          /*!< transmitting state */
#define CAN_STAT_SLPIF                 _BIT(4,U)          /*!< status change interrupt flag of sleep working mode entering */
#define CAN_STAT_WUIF                  _BIT(3,U)          /*!< status change interrupt flag of wakeup from sleep working mode */
#define CAN_STAT_ERRIF                 _BIT(2,U)          /*!< error interrupt flag*/
#define CAN_STAT_SLPWS                 _BIT(1,U)          /*!< sleep working state */
#define CAN_STAT_IWS                   _BIT(0,U)          /*!< initial working state */

/* CAN_TSTAT */
#define CAN_TSTAT_TMLS2                _BIT(31,U)         /*!< last sending priority flag for mailbox2 */
#define CAN_TSTAT_TMLS1                _BIT(30,U)         /*!< last sending priority flag for mailbox1 */
#define CAN_TSTAT_TMLS0                _BIT(29,U)         /*!< last sending priority flag for mailbox0 */
#define CAN_TSTAT_TME2                 _BIT(28,U)         /*!< transmit mailbox2 empty */
#define CAN_TSTAT_TME1                 _BIT(27,U)         /*!< transmit mailbox1 empty */
#define CAN_TSTAT_TME0                 _BIT(26,U)         /*!< transmit mailbox0 empty */
#define CAN_TSTAT_NUM_Pos              24
#define CAN_TSTAT_NUM_Msk              _AC(0x0c000000,U)  /*!< mailbox number */
#define CAN_TSTAT_NUM(x)               ((x) << CAN_TSTAT_NUM_Pos)
#define CAN_TSTAT_MST2                 _BIT(23,U)         /*!< mailbox2 stop transmitting */
#define CAN_TSTAT_MTE2                 _BIT(19,U)         /*!< mailbox2 transmit error */
#define CAN_TSTAT_MAL2                 _BIT(18,U)         /*!< mailbox2 arbitration lost */
#define CAN_TSTAT_MTFNERR2             _BIT(17,U)         /*!< mailbox2 transmit finished and no error */
#define CAN_TSTAT_MTF2                 _BIT(16,U)         /*!< mailbox2 transmit finished */
#define CAN_TSTAT_MST1                 _BIT(15,U)         /*!< mailbox1 stop transmitting */
#define CAN_TSTAT_MTE1                 _BIT(11,U)         /*!< mailbox1 transmit error */
#define CAN_TSTAT_MAL1                 _BIT(10,U)         /*!< mailbox1 arbitration lost */
#define CAN_TSTAT_MTFNERR1             _BIT(9,U)          /*!< mailbox1 transmit finished and no error */
#define CAN_TSTAT_MTF1                 _BIT(8,U)          /*!< mailbox1 transmit finished */
#define CAN_TSTAT_MST0                 _BIT(7,U)          /*!< mailbox0 stop transmitting */
#define CAN_TSTAT_MTE0                 _BIT(3,U)          /*!< mailbox0 transmit error */
#define CAN_TSTAT_MAL0                 _BIT(2,U)          /*!< mailbox0 arbitration lost */
#define CAN_TSTAT_MTFNERR0             _BIT(1,U)          /*!< mailbox0 transmit finished and no error */
#define CAN_TSTAT_MTF0                 _BIT(0,U)          /*!< mailbox0 transmit finished */

/* CAN_RFIFO0 */
#define CAN_RFIFO0_RFD0                _BIT(5,U)          /*!< receive FIFO0 dequeue */
#define CAN_RFIFO0_RFO0                _BIT(4,U)          /*!< receive FIFO0 overfull */
#define CAN_RFIFO0_RFF0                _BIT(3,U)          /*!< receive FIFO0 full */
#define CAN_RFIFO0_RFL0_Pos            0
#define CAN_RFIFO0_RFL0_Msk            _AC(0x00000003,U)  /*!< receive FIFO0 length */
#define CAN_RFIFO0_RFL0(x)             ((x) << CAN_RFIFO0_RFL0_Pos)

/* CAN_RFIFO1 */
#define CAN_RFIFO1_RFD1                _BIT(5,U)          /*!< receive FIFO1 dequeue */
#define CAN_RFIFO1_RFO1                _BIT(4,U)          /*!< receive FIFO1 overfull */
#define CAN_RFIFO1_RFF1                _BIT(3,U)          /*!< receive FIFO1 full */
#define CAN_RFIFO1_RFL1_Pos            0
#define CAN_RFIFO1_RFL1_Msk            _AC(0x00000003,U)  /*!< receive FIFO1 length */
#define CAN_RFIFO1_RFL1(x)             ((x) << CAN_RFIFO1_RFL1_Pos)

/* CAN_INTEN */
#define CAN_INTEN_SLPWIE               _BIT(17,U)         /*!< sleep working interrupt enable */
#define CAN_INTEN_WIE                  _BIT(16,U)         /*!< wakeup interrupt enable */
#define CAN_INTEN_ERRIE                _BIT(15,U)         /*!< error interrupt enable */
#define CAN_INTEN_ERRNIE               _BIT(11,U)         /*!< error number interrupt enable */
#define CAN_INTEN_BOIE                 _BIT(10,U)         /*!< bus-off interrupt enable */
#define CAN_INTEN_PERRIE               _BIT(9,U)          /*!< passive error interrupt enable */
#define CAN_INTEN_WERRIE               _BIT(8,U)          /*!< warning error interrupt enable */
#define CAN_INTEN_RFOIE1               _BIT(6,U)          /*!< receive FIFO1 overfull interrupt enable */
#define CAN_INTEN_RFFIE1               _BIT(5,U)          /*!< receive FIFO1 full interrupt enable */
#define CAN_INTEN_RFNEIE1              _BIT(4,U)          /*!< receive FIFO1 not empty interrupt enable */
#define CAN_INTEN_RFOIE0               _BIT(3,U)          /*!< receive FIFO0 overfull interrupt enable */
#define CAN_INTEN_RFFIE0               _BIT(2,U)          /*!< receive FIFO0 full interrupt enable */
#define CAN_INTEN_RFNEIE0              _BIT(1,U)          /*!< receive FIFO0 not empty interrupt enable */
#define CAN_INTEN_TMEIE                _BIT(0,U)          /*!< transmit mailbox empty interrupt enable */

/* CAN_ERR */
#define CAN_ERR_RECNT_Pos              24
#define CAN_ERR_RECNT_Msk              _AC(0xff000000,U)  /*!< receive error count */
#define CAN_ERR_RECNT(x)               ((x) << CAN_ERR_RECNT_Pos)
#define CAN_ERR_TECNT_Pos              16
#define CAN_ERR_TECNT_Msk              _AC(0x00ff0000,U)  /*!< transmit error count */
#define CAN_ERR_TECNT(x)               ((x) << CAN_ERR_TECNT_Pos)
#define CAN_ERR_ERRN_Pos               4
#define CAN_ERR_ERRN_Msk               _AC(0x00000070,U)  /*!< error number */
#define CAN_ERR_ERRN(x)                ((x) << CAN_ERR_ERRN_Pos)
#define CAN_ERR_BOERR                  _BIT(2,U)          /*!< bus-off error */
#define CAN_ERR_PERR                   _BIT(1,U)          /*!< passive error */
#define CAN_ERR_WERR                   _BIT(0,U)          /*!< warning error */

/* CAN_BT */
#define CAN_BT_SCMOD                   _BIT(31,U)         /*!< silent communication mode */
#define CAN_BT_LCMOD                   _BIT(30,U)         /*!< loopback communication mode */
#define CAN_BT_SJW_Pos                 24
#define CAN_BT_SJW_Msk                 _AC(0x03000000,U)  /*!< resynchronization jump width */
#define CAN_BT_SJW(x)                  ((x) << CAN_BT_SJW_Pos)
#define CAN_BT_BS2_Pos                 20
#define CAN_BT_BS2_Msk                 _AC(0x00700000,U)  /*!< bit segment 2 */
#define CAN_BT_BS2(x)                  ((x) << CAN_BT_BS2_Pos)
#define CAN_BT_BS1_Pos                 16
#define CAN_BT_BS1_Msk                 _AC(0x000f0000,U)  /*!< bit segment 1 */
#define CAN_BT_BS1(x)                  ((x) << CAN_BT_BS1_Pos)
#define CAN_BT_BAUDPSC_Pos             0
#define CAN_BT_BAUDPSC_Msk             _AC(0x000003ff,U)  /*!< baudrate prescaler */
#define CAN_BT_BAUDPSC(x)              ((x) << CAN_BT_BAUDPSC_Pos)

/* CAN_TMIx */
#define CAN_TMI_SFID_Pos               21
#define CAN_TMI_SFID_Msk               _AC(0xffe00000,U)  /*!< the frame identifier */
#define CAN_TMI_SFID(x)                ((x) << CAN_TMI_SFID_Pos)
#define CAN_TMI_EFID_Pos               3
#define CAN_TMI_EFID_Msk               _AC(0x001ffff8,U)  /*!< the frame identifier */
#define CAN_TMI_EFID(x)                ((x) << CAN_TMI_EFID_Pos)
#define CAN_TMI_FF                     _BIT(2,U)          /*!< frame format */
#define CAN_TMI_FT                     _BIT(1,U)          /*!< frame type */
#define CAN_TMI_TEN                    _BIT(0,U)          /*!< transmit enable */

/* CAN_TMPx */
#define CAN_TMP_TS_Pos                 16
#define CAN_TMP_TS_Msk                 _AC(0xffff0000,U)  /*!< time stamp */
#define CAN_TMP_TSEN                   _BIT(8,U)          /*!< time stamp enable */
#define CAN_TMP_DLENC_Pos              0
#define CAN_TMP_DLENC_Msk              _AC(0x0000000f,U)  /*!< data length code */
#define CAN_TMP_DLENC(x)               ((x) << CAN_TMP_DLENC_Pos)

/* CAN_TMDATA0x */
#define CAN_TMDATA0_DB3_Pos            24
#define CAN_TMDATA0_DB3_Msk            _AC(0xff000000,U)  /*!< transmit data byte 3 */
#define CAN_TMDATA0_DB3(x)             ((x) << CAN_TMDATA0_DB3_Pos)
#define CAN_TMDATA0_DB2_Pos            16
#define CAN_TMDATA0_DB2_Msk            _AC(0x00ff0000,U)  /*!< transmit data byte 2 */
#define CAN_TMDATA0_DB2(x)             ((x) << CAN_TMDATA0_DB2_Pos)
#define CAN_TMDATA0_DB1_Pos            8
#define CAN_TMDATA0_DB1_Msk            _AC(0x0000ff00,U)  /*!< transmit data byte 1 */
#define CAN_TMDATA0_DB1(x)             ((x) << CAN_TMDATA0_DB1_Pos)
#define CAN_TMDATA0_DB0_Pos            0
#define CAN_TMDATA0_DB0_Msk            _AC(0x000000ff,U)  /*!< transmit data byte 0 */
#define CAN_TMDATA0_DB0(x)             ((x) << CAN_TMDATA0_DB0_Pos)

/* CAN_TMDATA1x */
#define CAN_TMDATA1_DB7_Pos            24
#define CAN_TMDATA1_DB7_Msk            _AC(0xff000000,U)  /*!< transmit data byte 7 */
#define CAN_TMDATA1_DB7(x)             ((x) << CAN_TMDATA1_DB7_Pos)
#define CAN_TMDATA1_DB6_Pos            16
#define CAN_TMDATA1_DB6_Msk            _AC(0x00ff0000,U)  /*!< transmit data byte 6 */
#define CAN_TMDATA1_DB6(x)             ((x) << CAN_TMDATA1_DB6_Pos)
#define CAN_TMDATA1_DB5_Pos            8
#define CAN_TMDATA1_DB5_Msk            _AC(0x0000ff00,U)  /*!< transmit data byte 5 */
#define CAN_TMDATA1_DB5(x)             ((x) << CAN_TMDATA1_DB5_Pos)
#define CAN_TMDATA1_DB4_Pos            0
#define CAN_TMDATA1_DB4_Msk            _AC(0x000000ff,U)  /*!< transmit data byte 4 */
#define CAN_TMDATA1_DB4(x)             ((x) << CAN_TMDATA1_DB4_Pos)

/* CAN_RFIFOMIx */
#define CAN_RFIFOMI_SFID_Pos           21
#define CAN_RFIFOMI_SFID_Msk           _AC(0xffe00000,U)  /*!< the frame identifier */
#define CAN_RFIFOMI_SFID(x)            ((x) << CAN_RFIFOMI_SFID_Pos)
#define CAN_RFIFOMI_EFID_Pos           3
#define CAN_RFIFOMI_EFID_Msk           _AC(0x001ffff8,U)  /*!< the frame identifier */
#define CAN_RFIFOMI_EFID(x)            ((x) << CAN_RFIFOMI_EFID_Pos)
#define CAN_RFIFOMI_FF                 _BIT(2,U)          /*!< frame format */
#define CAN_RFIFOMI_FT                 _BIT(1,U)          /*!< frame type */

/* CAN_RFIFOMPx */
#define CAN_RFIFOMP_TS_Pos             16
#define CAN_RFIFOMP_TS_Msk             _AC(0xffff0000,U)  /*!< time stamp */
#define CAN_RFIFOMP_TS(x)              ((x) << CAN_RFIFOMP_TS_Pos)
#define CAN_RFIFOMP_FI_Pos             8
#define CAN_RFIFOMP_FI_Msk             _AC(0x0000ff00,U)  /*!< filter index */
#define CAN_RFIFOMP_FI(x)              ((x) << CAN_RFIFOMP_FI_Pos)
#define CAN_RFIFOMP_DLENC_Pos          0
#define CAN_RFIFOMP_DLENC_Msk          _AC(0x0000000f,U)  /*!< receive data length code */
#define CAN_RFIFOMP_DLENC(x)           ((x) << CAN_RFIFOMP_DLENC_Pos)

/* CAN_RFIFOMDATA0x */
#define CAN_RFIFOMDATA0_DB3_Pos        24
#define CAN_RFIFOMDATA0_DB3_Msk        _AC(0xff000000,U)  /*!< receive data byte 3 */
#define CAN_RFIFOMDATA0_DB3(x)         ((x) << CAN_RFIFOMDATA0_DB3_Pos)
#define CAN_RFIFOMDATA0_DB2_Pos        16
#define CAN_RFIFOMDATA0_DB2_Msk        _AC(0x00ff0000,U)  /*!< receive data byte 2 */
#define CAN_RFIFOMDATA0_DB2(x)         ((x) << CAN_RFIFOMDATA0_DB2_Pos)
#define CAN_RFIFOMDATA0_DB1_Pos        8
#define CAN_RFIFOMDATA0_DB1_Msk        _AC(0x0000ff00,U)  /*!< receive data byte 1 */
#define CAN_RFIFOMDATA0_DB1(x)         ((x) << CAN_RFIFOMDATA0_DB1_Pos)
#define CAN_RFIFOMDATA0_DB0_Pos        0
#define CAN_RFIFOMDATA0_DB0_Msk        _AC(0x000000ff,U)  /*!< receive data byte 0 */
#define CAN_RFIFOMDATA0_DB0(x)         ((x) << CAN_RFIFOMDATA0_DB0_Pos)

/* CAN_RFIFOMDATA1x */
#define CAN_RFIFOMDATA1_DB7_Pos        24
#define CAN_RFIFOMDATA1_DB7_Msk        _AC(0xff000000,U)  /*!< receive data byte 7 */
#define CAN_RFIFOMDATA1_DB7(x)         ((x) << CAN_RFIFOMDATA1_DB7_Pos)
#define CAN_RFIFOMDATA1_DB6_Pos        16
#define CAN_RFIFOMDATA1_DB6_Msk        _AC(0x00ff0000,U)  /*!< receive data byte 6 */
#define CAN_RFIFOMDATA1_DB6(x)         ((x) << CAN_RFIFOMDATA1_DB6_Pos)
#define CAN_RFIFOMDATA1_DB5_Pos        8
#define CAN_RFIFOMDATA1_DB5_Msk        _AC(0x0000ff00,U)  /*!< receive data byte 5 */
#define CAN_RFIFOMDATA1_DB5(x)         ((x) << CAN_RFIFOMDATA1_DB5_Pos)
#define CAN_RFIFOMDATA1_DB4_Pos        0
#define CAN_RFIFOMDATA1_DB4_Msk        _AC(0x000000ff,U)  /*!< receive data byte 4 */
#define CAN_RFIFOMDATA1_DB4(x)         ((x) << CAN_RFIFOMDATA1_DB4_Pos)

/* CAN_FCTL */
#define CAN_FCTL_HBC1F_Pos             8
#define CAN_FCTL_HBC1F_Msk             _AC(0x00003f00,U)  /*!< header bank of CAN1 filter */
#define CAN_FCTL_HBC1F(x)              ((x) << CAN_FCTL_HBC1F_Pos)
#define CAN_FCTL_FLD                   _BIT(0,U)          /*!< filter lock disable */

/* CAN_FMCFG */
#define CAN_FMCFG_FMOD(x)              _BIT(x,U)          /*!< filter mode, list or mask*/

/* CAN_FSCFG */
#define CAN_FSCFG_FS(x)                _BIT(x,U)          /*!< filter scale, 32 bits or 16 bits*/

/* CAN_FAFIFO */
#define CAN_FAFIFOR_FAF(x)             _BIT(x,U)          /*!< filter associated with FIFO */

/* CAN_FW */
#define CAN_FW_FW(x)                   _BIT(x,U)          /*!< filter working */

/* CAN_FxDATAy */
#define CAN_FDATA_FD(x)                _BIT(x,U)          /*!< filter data */

/* ----------------------- CRC ---------------------------- */

#define CRC_BASE                       _AC(0x40023000,UL)  /*!< CRC base address */

/* register definitions */
#define CRC_DATA                       _AC(0x00,UL)  /*!< CRC data register */
#define CRC_FDATA                      _AC(0x04,UL)  /*!< CRC free data register */
#define CRC_CTL                        _AC(0x08,UL)  /*!< CRC control register */

/* CRC_DATA */
#define CRC_DATA_DATA_Pos              0
#define CRC_DATA_DATA_Msk              _AC(0xffffffff,U)  /*!< CRC calculation result bits */
#define CRC_DATA_DATA(x)               ((x) << CRC_DATA_DATA_Pos)

/* CRC_FDATA */
#define CRC_FDATA_FDATA_Pos            0
#define CRC_FDATA_FDATA_Msk            _AC(0x000000ff,U)  /*!< CRC free data bits */
#define CRC_FDATA_FDATA(x)             ((x) << CRC_FDATA_FDATA_Pos)

/* CRC_CTL */
#define CRC_CTL_RST                    _BIT(0,U)          /*!< CRC reset CRC_DATA register bit */

/* --------------------- CSR -------------------------- */

/* custom CSRs */
#define CSR_MTVT                       0x307
#define CSR_MNXTI                      0x345
#define CSR_MINTSTATUS                 0x346
#define CSR_MSCRATCHCSW                0x348
#define CSR_MSCRATCHCSWL               0x349
#define CSR_MNVEC                      0x7C3
#define CSR_MSUBM                      0x7C4
#define CSR_MMISC_CTL                  0x7D0
#define CSR_MSAVESTATUS                0x7D6
#define CSR_MSAVEPC1                   0x7D7
#define CSR_MSAVECAUSE1                0x7D8
#define CSR_MSAVEPC2                   0x7D9
#define CSR_MSAVECAUSE2                0x7DA
#define CSR_PUSHMSUBM                  0x7EB
#define CSR_MTVT2                      0x7EC
#define CSR_JALMNXTI                   0x7ED
#define CSR_PUSHMCAUSE                 0x7EE
#define CSR_PUSHMEPC                   0x7EF
#define CSR_WFE                        0x810
#define CSR_SLEEPVALUE                 0x811
#define CSR_TXEVT                      0x812

/* custom mtvec bits */
#define CSR_MTVEC_MODE_Pos             0
#define CSR_MTVEC_MODE_Msk             _AC(0x0000003f,UL)
#define CSR_MTVEC_MODE_ECLIC           _AC(0x00000003,UL)

/* custom mcause bits */
#define CSR_MCAUSE_MINHV               _BIT(30,UL)
#define CSR_MCAUSE_MPP_Pos             28
#define CSR_MCAUSE_MPP_Msk             _AC(0x30000000,UL)
#define CSR_MCAUSE_MPP(x)              ((x) << CSR_MCAUSE_MPP_Pos)
#define CSR_MCOUSE_MPIE                _BIT(27,UL)
#define CSR_MCAUSE_MPIL_Pos            16
#define CSR_MCAUSE_MPIL_Msk            _AC(0x00ff0000,UL)
#define CSR_MCAUSE_MPIL(x)             ((x) << CSR_MCAUSE_MPIL_Pos)
#define CSR_MCAUSE_EXCCODE_Pos         0
#define CSR_MCAUSE_EXCCODE_Msk         _AC(0x00000fff,UL)
#define CSR_MCAUSE_EXCCODE(x)          ((x) << CSR_MCAUSE_EXCCODE_Pos)

/* mintstatus bits */
#define CSR_MINTSTATUS_MIL_Pos         24
#define CSR_MINTSTATUS_MIL_Msk         _AC(0xff000000,UL)
#define CSR_MINTSTATUS_MIL(x)          ((x) << CSR_MINTSTATUS_MIL_Pos)
#define CSR_MINTSTATUS_UIL_Pos         0
#define CSR_MINTSTATUS_UIL_Msk         _AC(0x000000ff,UL)
#define CSR_MINTSTATUS_UIL(x)          ((x) << CSR_MINTSTATUS_UIL_Pos)

/* mmisc_ctl bits */
#define CSR_MMISC_CTL_NMI_CAUSE_FFF    _BIT(9,UL)

/* mtvt2 bits */
#define CSR_MTVT2_MTVT2EN              _BIT(0,UL)

/* wfe bits */
#define CSR_WFE_WFE                    _BIT(0,UL)

/* sleepvalue bits */
#define CSR_SLEEPVALUE_SLEEPVALUE      _BIT(0,UL)

/* txevt bits */
#define CSR_TXEVT_TXEVT                _BIT(0,UL)

/* --------------------- DAC -------------------------- */

#define DAC_BASE                       _AC(0x40007400,UL)  /*!< DAC base address */

/* register definitions */
#define DAC_CTL                        _AC(0x00,UL)  /*!< DAC control register */
#define DAC_SWT                        _AC(0x04,UL)  /*!< DAC software trigger register */
#define DAC_R12DH0                     _AC(0x08,UL)  /*!< DAC0 12-bit right-aligned data holding register */
#define DAC_L12DH0                     _AC(0x0C,UL)  /*!< DAC0 12-bit left-aligned data holding register */
#define DAC_R8DH0                      _AC(0x10,UL)  /*!< DAC0 8-bit right-aligned data holding register */
#define DAC_R12DH1                     _AC(0x14,UL)  /*!< DAC1 12-bit right-aligned data holding register */
#define DAC_L12DH1                     _AC(0x18,UL)  /*!< DAC1 12-bit left-aligned data holding register */
#define DAC_R8DH1                      _AC(0x1C,UL)  /*!< DAC1 8-bit right-aligned data holding register */
#define DAC_R12DHC                     _AC(0x20,UL)  /*!< DAC concurrent mode 12-bit right-aligned data holding register */
#define DAC_L12DHC                     _AC(0x24,UL)  /*!< DAC concurrent mode 12-bit left-aligned data holding register */
#define DAC_R8DHC                      _AC(0x28,UL)  /*!< DAC concurrent mode 8-bit right-aligned data holding register */
#define DAC_DO0                        _AC(0x2C,UL)  /*!< DAC0 data output register */
#define DAC_DO1                        _AC(0x30,UL)  /*!< DAC1 data output register */

/* DAC_CTL */
#define DAC_CTL_DDMAEN1                _BIT(28,U)         /*!< DAC1 DMA enable/disable bit */
#define DAC_CTL_DWBW1_Pos              24
#define DAC_CTL_DWBW1_Msk              _AC(0x0f000000,U)  /*!< DAC1 noise wave bit width */
#define DAC_CTL_DWBW1(x)               ((x) << DAC_CTL_DWBW1_Pos)
#define DAC_CTL_DWM1_Pos               22
#define DAC_CTL_DWM1_Msk               _AC(0x00c00000,U)  /*!< DAC1 noise wave mode */
#define DAC_CTL_DWM1(x)                ((x) << DAC_CTL_DWM1_Pos)
#define DAC_CTL_DWM1_DISABLED          DAC_CTL_DWM1(0)    /*!< DAC1 wave disable */
#define DAC_CTL_DWM1_LFSR              DAC_CTL_DWM1(1)    /*!< DAC1 LFSR noise mode */
#define DAC_CTL_DWM1_TRIANGLE          DAC_CTL_DWM1(2)    /*!< DAC1 triangle noise mode */
#define DAC_CTL_DTSEL1_Pos             19
#define DAC_CTL_DTSEL1_Msk             _AC(0x00380000,U)  /*!< DAC1 trigger source selection enable/disable bits */
#define DAC_CTL_DTSEL1(x)              ((x) << DAC_CTL_DTSEL1_Pos)
#define DAC_CTL_DTSEL1_T5_TRGO         DAC_CTL_DTSEL1(0)  /*!< DAC1 TIMER5 TRGO */
#define DAC_CTL_DTSEL1_T2_TRGO         DAC_CTL_DTSEL1(1)  /*!< DAC1 TIMER2 TRGO */
#define DAC_CTL_DTSEL1_T6_TRGO         DAC_CTL_DTSEL1(2)  /*!< DAC1 TIMER6 TRGO */
#define DAC_CTL_DTSEL1_T4_TRGO         DAC_CTL_DTSEL1(3)  /*!< DAC1 TIMER4 TRGO */
#define DAC_CTL_DTSEL1_T1_TRGO         DAC_CTL_DTSEL1(4)  /*!< DAC1 TIMER1 TRGO */
#define DAC_CTL_DTSEL1_T3_TRGO         DAC_CTL_DTSEL1(5)  /*!< DAC1 TIMER3 TRGO */
#define DAC_CTL_DTSEL1_EXTI_9          DAC_CTL_DTSEL1(6)  /*!< DAC1 EXTI interrupt line9 event */
#define DAC_CTL_DTSEL1_SOFTWARE        DAC_CTL_DTSEL1(7)  /*!< DAC1 software trigger */
#define DAC_CTL_DTEN1                  _BIT(18,U)         /*!< DAC1 trigger enable/disable bit */
#define DAC_CTL_DBOFF1                 _BIT(17,U)         /*!< DAC1 output buffer turn on/turn off bit */
#define DAC_CTL_DEN1                   _BIT(16,U)         /*!< DAC1 enable/disable bit */
#define DAC_CTL_DDMAEN0                _BIT(12,U)         /*!< DAC0 DMA enable/disable bit */
#define DAC_CTL_DWBW0_Pos              8
#define DAC_CTL_DWBW0_Msk              _AC(0x00000f00,U)  /*!< DAC0 noise wave bit width */
#define DAC_CTL_DWBW0(x)               ((x) << DAC_CTL_DWBW0_Pos)
#define DAC_CTL_DWM0_Pos               6
#define DAC_CTL_DWM0_Msk               _AC(0x000000c0,U)  /*!< DAC0 noise wave mode */
#define DAC_CTL_DWM0(x)                ((x) << DAC_CTL_DWM0_Pos)
#define DAC_CTL_DWM0_DISABLED          DAC_CTL_DWM0(0)    /*!< DAC0 wave disable */
#define DAC_CTL_DWM0_LFSR              DAC_CTL_DWM0(1)    /*!< DAC0 LFSR noise mode */
#define DAC_CTL_DWM0_TRIANGLE          DAC_CTL_DWM0(2)    /*!< DAC0 triangle noise mode */
#define DAC_CTL_DTSEL0_Pos             3
#define DAC_CTL_DTSEL0_Msk             _AC(0x00000038,U)  /*!< DAC0 trigger source selection enable/disable bits */
#define DAC_CTL_DTSEL0(x)              ((x) << DAC_CTL_DTSEL0_Pos)
#define DAC_CTL_DTSEL0_T5_TRGO         DAC_CTL_DTSEL0(0)  /*!< DAC0 TIMER5 TRGO */
#define DAC_CTL_DTSEL0_T2_TRGO         DAC_CTL_DTSEL0(1)  /*!< DAC0 TIMER2 TRGO */
#define DAC_CTL_DTSEL0_T6_TRGO         DAC_CTL_DTSEL0(2)  /*!< DAC0 TIMER6 TRGO */
#define DAC_CTL_DTSEL0_T4_TRGO         DAC_CTL_DTSEL0(3)  /*!< DAC0 TIMER4 TRGO */
#define DAC_CTL_DTSEL0_T1_TRGO         DAC_CTL_DTSEL0(4)  /*!< DAC0 TIMER1 TRGO */
#define DAC_CTL_DTSEL0_T3_TRGO         DAC_CTL_DTSEL0(5)  /*!< DAC0 TIMER3 TRGO */
#define DAC_CTL_DTSEL0_EXTI_9          DAC_CTL_DTSEL0(6)  /*!< DAC0 EXTI interrupt line9 event */
#define DAC_CTL_DTSEL0_SOFTWARE        DAC_CTL_DTSEL0(7)  /*!< DAC0 software trigger */
#define DAC_CTL_DTEN0                  _BIT(2,U)          /*!< DAC0 trigger enable/disable bit */
#define DAC_CTL_DBOFF0                 _BIT(1,U)          /*!< DAC0 output buffer turn on/turn off bit */
#define DAC_CTL_DEN0                   _BIT(0,U)          /*!< DAC0 enable/disable bit */

/* DAC_SWT */
#define DAC_SWT_SWTR1                  _BIT(1,U)          /*!< DAC1 software trigger bit, cleared by hardware */
#define DAC_SWT_SWTR0                  _BIT(0,U)          /*!< DAC0 software trigger bit, cleared by hardware */

/* DAC_R12DHx, x=0,1 */
#define DAC_R12DHX_DAC_DH_Pos          0
#define DAC_R12DHX_DAC_DH_Msk          _AC(0x00000fff,U)  /*!< DAC 12-bit right-aligned data bits */
#define DAC_R12DHX_DAC_DH(x)           ((x) << DAC_R12DHX_DAC_DH_Pos)

/* DAC_L12DHx, x=0,1 */
#define DAC_L12DHX_DAC_DH_Pos          4
#define DAC_L12DHX_DAC_DH_Msk          _AC(0x0000fff0,U)  /*!< DAC 12-bit left-aligned data bits */
#define DAC_L12DHX_DAC_DH(x)           ((x) << DAC_L12DHX_DAC_DH_Pos)

/* DAC_R8DHx, x=0,1 */
#define DAC_R8DHX_DAC_DH_Pos           0
#define DAC_R8DHX_DAC_DH_Msk           _AC(0x000000ff,U)  /*!< DAC 8-bit right-aligned data bits */
#define DAC_R8DHX_DAC_DH(x)            ((x) << DAC_R8DHX_DAC_DH_Pos)

/* DAC_R12DHC */
#define DAC_R12DHC_DAC1_DH_Pos         16
#define DAC_R12DHC_DAC1_DH_Msk         _AC(0x0fff0000,U)  /*!< DAC concurrent mode DAC1 12-bit right-aligned data bits */
#define DAC_R12DHC_DAC1_DH(x)          ((x) << DAC_R12DHC_DAC1_DH_Pos)
#define DAC_R12DHC_DAC0_DH_Pos         0
#define DAC_R12DHC_DAC0_DH_Msk         _AC(0x00000fff,U)  /*!< DAC concurrent mode DAC0 12-bit right-aligned data bits */
#define DAC_R12DHC_DAC0_DH(x)          ((x) << DAC_R12DHC_DAC0_DH_Pos)

/* DAC_L12DHC */
#define DAC_L12DHC_DAC1_DH_Pos         20
#define DAC_L12DHC_DAC1_DH_Msk         _AC(0xfff00000,U)  /*!< DAC concurrent mode DAC1 12-bit left-aligned data bits */
#define DAC_L12DHC_DAC1_DH(x)          ((x) << DAC_L12DHC_DAC1_DH_Pos)
#define DAC_L12DHC_DAC0_DH_Pos         4
#define DAC_L12DHC_DAC0_DH_Msk         _AC(0x0000fff0,U)  /*!< DAC concurrent mode DAC0 12-bit left-aligned data bits */
#define DAC_L12DHC_DAC0_DH(x)          ((x) << DAC_L12DHC_DAC0_DH_Pos)

/* DAC_R8DHC */
#define DAC_R8DHC_DAC1_DH_Pos          8
#define DAC_R8DHC_DAC1_DH_Msk          _AC(0x0000ff00,U)  /*!< DAC concurrent mode DAC1 8-bit right-aligned data bits */
#define DAC_R8DHC_DAC1_DH(x)           ((x) << DAC_R8DHC_DAC1_DH_Pos)
#define DAC_R8DHC_DAC0_DH_Pos          0
#define DAC_R8DHC_DAC0_DH_Msk          _AC(0x000000ff,U)  /*!< DAC concurrent mode DAC0 8-bit right-aligned data bits */
#define DAC_R8DHC_DAC0_DH(x)           ((x) << DAC_R8DHC_DAC0_DH_Pos)

/* DAC_DOX */
#define DAC_DO_DAC_DO_Pos              0
#define DAC_DO_DAC_DO_Msk              _AC(0x00000fff,U)  /*!< DAC 12-bit output data bits */
#define DAC_DO_DAC_DO(x)               ((x) << DAC_DO_DAC_DO_Pos)

/* --------------------- DBG -------------------------- */

#define DBG_BASE                       _AC(0xe0042000,UL)  /*!< DBG base address */

/* register definitions */
#define DBG_ID                         _AC(0x00,UL)  /*!< DBG_ID code register */
#define DBG_CTL                        _AC(0x04,UL)  /*!< DBG control register */
/* undocumented registers below, names guessed */
#define DBG_CMD                        _AC(0x08,UL)  /*!< DBG command register */
#define DBG_KEY                        _AC(0x0c,UL)  /*!< DBG unlock key register */

/* DBG_ID */
#define DBG_ID_ID_CODE_Pos             0
#define DBG_ID_ID_CODE_Msk             _AC(0xffffffff,U)  /*!< DBG ID code values */
#define DBG_ID_ID_CODE(x)              ((x) << DBG_ID_ID_CODE_Pos)

/* DBG_CTL */
#define DBG_CTL_CAN1_HOLD              _BIT(21,U)         /*!< debug CAN1 kept when core is halted */
#define DBG_CTL_TIMER6_HOLD            _BIT(20,U)         /*!< hold TIMER6 counter when core is halted */
#define DBG_CTL_TIMER5_HOLD            _BIT(19,U)         /*!< hold TIMER5 counter when core is halted */
#define DBG_CTL_TIMER4_HOLD            _BIT(18,U)         /*!< hold TIMER4 counter when core is halted */
#define DBG_CTL_I2C1_HOLD              _BIT(16,U)         /*!< hold I2C1 smbus when core is halted */
#define DBG_CTL_I2C0_HOLD              _BIT(15,U)         /*!< hold I2C0 smbus when core is halted */
#define DBG_CTL_CAN0_HOLD              _BIT(14,U)         /*!< debug CAN0 kept when core is halted */
#define DBG_CTL_TIMER3_HOLD            _BIT(13,U)         /*!< hold TIMER3 counter when core is halted */
#define DBG_CTL_TIMER2_HOLD            _BIT(12,U)         /*!< hold TIMER2 counter when core is halted */
#define DBG_CTL_TIMER1_HOLD            _BIT(11,U)         /*!< hold TIMER1 counter when core is halted */
#define DBG_CTL_TIMER0_HOLD            _BIT(10,U)         /*!< hold TIMER0 counter when core is halted */
#define DBG_CTL_WWDGT_HOLD             _BIT(9,U)          /*!< debug WWDGT kept when core is halted */
#define DBG_CTL_FWDGT_HOLD             _BIT(8,U)          /*!< debug FWDGT kept when core is halted */
#define DBG_CTL_STB_HOLD               _BIT(2,U)          /*!< keep debugger connection during standby mode */
#define DBG_CTL_DSLP_HOLD              _BIT(1,U)          /*!< keep debugger connection during deepsleep mode */
#define DBG_CTL_SLP_HOLD               _BIT(0,U)          /*!< keep debugger connection during sleep mode */

/* DBG_CMD */
#define DBG_CMD_RESET                  _BIT(0,U)          /*!< software reset */

/* DBG_KEY */
#define DBG_KEY_UNLOCK                 _AC(0x4b5a6978,U)  /*!< unlock key */

/* --------------------- DMA -------------------------- */

#define DMA0_BASE                      _AC(0x40020000,UL)  /*!< DMA0 base address */
#define DMA1_BASE                      _AC(0x40020400,UL)  /*!< DMA1 base address */

/* register definitions */
#define DMA_INTF                       _AC(0x00,UL)  /*!< DMA interrupt flag register */
#define DMA_INTC                       _AC(0x04,UL)  /*!< DMA interrupt flag clear register */

#define DMA_CH0CTL                     _AC(0x08,UL)  /*!< DMA channel 0 control register */
#define DMA_CH0CNT                     _AC(0x0C,UL)  /*!< DMA channel 0 counter register */
#define DMA_CH0PADDR                   _AC(0x10,UL)  /*!< DMA channel 0 peripheral base address register */
#define DMA_CH0MADDR                   _AC(0x14,UL)  /*!< DMA channel 0 memory base address register */

#define DMA_CH1CTL                     _AC(0x1C,UL)  /*!< DMA channel 1 control register */
#define DMA_CH1CNT                     _AC(0x20,UL)  /*!< DMA channel 1 counter register */
#define DMA_CH1PADDR                   _AC(0x24,UL)  /*!< DMA channel 1 peripheral base address register */
#define DMA_CH1MADDR                   _AC(0x28,UL)  /*!< DMA channel 1 memory base address register */

#define DMA_CH2CTL                     _AC(0x30,UL)  /*!< DMA channel 2 control register */
#define DMA_CH2CNT                     _AC(0x34,UL)  /*!< DMA channel 2 counter register */
#define DMA_CH2PADDR                   _AC(0x38,UL)  /*!< DMA channel 2 peripheral base address register */
#define DMA_CH2MADDR                   _AC(0x3C,UL)  /*!< DMA channel 2 memory base address register */

#define DMA_CH3CTL                     _AC(0x44,UL)  /*!< DMA channel 3 control register */
#define DMA_CH3CNT                     _AC(0x48,UL)  /*!< DMA channel 3 counter register */
#define DMA_CH3PADDR                   _AC(0x4C,UL)  /*!< DMA channel 3 peripheral base address register */
#define DMA_CH3MADDR                   _AC(0x50,UL)  /*!< DMA channel 3 memory base address register */

#define DMA_CH4CTL                     _AC(0x58,UL)  /*!< DMA channel 4 control register */
#define DMA_CH4CNT                     _AC(0x5C,UL)  /*!< DMA channel 4 counter register */
#define DMA_CH4PADDR                   _AC(0x60,UL)  /*!< DMA channel 4 peripheral base address register */
#define DMA_CH4MADDR                   _AC(0x64,UL)  /*!< DMA channel 4 memory base address register */

#define DMA_CH5CTL                     _AC(0x6C,UL)  /*!< DMA channel 5 control register */
#define DMA_CH5CNT                     _AC(0x70,UL)  /*!< DMA channel 5 counter register */
#define DMA_CH5PADDR                   _AC(0x74,UL)  /*!< DMA channel 5 peripheral base address register */
#define DMA_CH5MADDR                   _AC(0x78,UL)  /*!< DMA channel 5 memory base address register */

#define DMA_CH6CTL                     _AC(0x80,UL)  /*!< DMA channel 6 control register */
#define DMA_CH6CNT                     _AC(0x84,UL)  /*!< DMA channel 6 counter register */
#define DMA_CH6PADDR                   _AC(0x88,UL)  /*!< DMA channel 6 peripheral base address register */
#define DMA_CH6MADDR                   _AC(0x8C,UL)  /*!< DMA channel 6 memory base address register */

/* DMA_INTF */
#define DMA_INTF_ERRIF6                _BIT(27,U)                 /*!< error flag of channel 6 */
#define DMA_INTF_HTFIF6                _BIT(26,U)                 /*!< half transfer finish flag of channel 6 */
#define DMA_INTF_FTFIF6                _BIT(25,U)                 /*!< full transfer finish flag of channel 6 */
#define DMA_INTF_GIF6                  _BIT(24,U)                 /*!< global interrupt flag of channel 6 */
#define DMA_INTF_ERRIF5                _BIT(23,U)                 /*!< error flag of channel 5 */
#define DMA_INTF_HTFIF5                _BIT(22,U)                 /*!< half transfer finish flag of channel 5 */
#define DMA_INTF_FTFIF5                _BIT(21,U)                 /*!< full transfer finish flag of channel 5 */
#define DMA_INTF_GIF5                  _BIT(20,U)                 /*!< global interrupt flag of channel 5 */
#define DMA_INTF_ERRIF4                _BIT(19,U)                 /*!< error flag of channel 4 */
#define DMA_INTF_HTFIF4                _BIT(18,U)                 /*!< half transfer finish flag of channel 4 */
#define DMA_INTF_FTFIF4                _BIT(17,U)                 /*!< full transfer finish flag of channel 4 */
#define DMA_INTF_GIF4                  _BIT(16,U)                 /*!< global interrupt flag of channel 4 */
#define DMA_INTF_ERRIF3                _BIT(15,U)                 /*!< error flag of channel 3 */
#define DMA_INTF_HTFIF3                _BIT(14,U)                 /*!< half transfer finish flag of channel 3 */
#define DMA_INTF_FTFIF3                _BIT(13,U)                 /*!< full transfer finish flag of channel 3 */
#define DMA_INTF_GIF3                  _BIT(12,U)                 /*!< global interrupt flag of channel 3 */
#define DMA_INTF_ERRIF2                _BIT(11,U)                 /*!< error flag of channel 2 */
#define DMA_INTF_HTFIF2                _BIT(10,U)                 /*!< half transfer finish flag of channel 2 */
#define DMA_INTF_FTFIF2                _BIT(9,U)                  /*!< full transfer finish flag of channel 2 */
#define DMA_INTF_GIF2                  _BIT(8,U)                  /*!< global interrupt flag of channel 2 */
#define DMA_INTF_ERRIF1                _BIT(7,U)                  /*!< error flag of channel 1 */
#define DMA_INTF_HTFIF1                _BIT(6,U)                  /*!< half transfer finish flag of channel 1 */
#define DMA_INTF_FTFIF1                _BIT(5,U)                  /*!< full transfer finish flag of channel 1 */
#define DMA_INTF_GIF1                  _BIT(4,U)                  /*!< global interrupt flag of channel 1 */
#define DMA_INTF_ERRIF0                _BIT(3,U)                  /*!< error flag of channel 0 */
#define DMA_INTF_HTFIF0                _BIT(2,U)                  /*!< half transfer finish flag of channel 0 */
#define DMA_INTF_FTFIF0                _BIT(1,U)                  /*!< full transfer finish flag of channel 0 */
#define DMA_INTF_GIF0                  _BIT(0,U)                  /*!< global interrupt flag of channel 0 */
#define DMA_INTF_ERRIF(x)              (_AC(1,U) << (4*(x) + 3))  /*!< error flag of channel x */
#define DMA_INTF_HTFIF(x)              (_AC(1,U) << (4*(x) + 2))  /*!< half transfer finish flag of channel x */
#define DMA_INTF_FTFIF(x)              (_AC(1,U) << (4*(x) + 1))  /*!< full transfer finish flag of channel x */
#define DMA_INTF_GIF(x)                (_AC(1,U) << (4*(x) + 0))  /*!< global interrupt flag of channel x */

/* DMA_INTC */
#define DMA_INTC_ERRIFC6               _BIT(27,U)                 /*!< clear error flag of channel 6 */
#define DMA_INTC_HTFIFC6               _BIT(26,U)                 /*!< clear half transfer finish flag of channel 6 */
#define DMA_INTC_FTFIFC6               _BIT(25,U)                 /*!< clear transfer finish flag of channel 6 */
#define DMA_INTC_GIFC6                 _BIT(24,U)                 /*!< clear global interrupt flag of channel 6 */
#define DMA_INTC_ERRIFC5               _BIT(23,U)                 /*!< clear error flag of channel 5 */
#define DMA_INTC_HTFIFC5               _BIT(22,U)                 /*!< clear half transfer finish flag of channel 5 */
#define DMA_INTC_FTFIFC5               _BIT(21,U)                 /*!< clear transfer finish flag of channel 5 */
#define DMA_INTC_GIFC5                 _BIT(20,U)                 /*!< clear global interrupt flag of channel 5 */
#define DMA_INTC_ERRIFC4               _BIT(19,U)                 /*!< clear error flag of channel 4 */
#define DMA_INTC_HTFIFC4               _BIT(18,U)                 /*!< clear half transfer finish flag of channel 4 */
#define DMA_INTC_FTFIFC4               _BIT(17,U)                 /*!< clear transfer finish flag of channel 4 */
#define DMA_INTC_GIFC4                 _BIT(16,U)                 /*!< clear global interrupt flag of channel 4 */
#define DMA_INTC_ERRIFC3               _BIT(15,U)                 /*!< clear error flag of channel 3 */
#define DMA_INTC_HTFIFC3               _BIT(14,U)                 /*!< clear half transfer finish flag of channel 3 */
#define DMA_INTC_FTFIFC3               _BIT(13,U)                 /*!< clear transfer finish flag of channel 3 */
#define DMA_INTC_GIFC3                 _BIT(12,U)                 /*!< clear global interrupt flag of channel 3 */
#define DMA_INTC_ERRIFC2               _BIT(11,U)                 /*!< clear error flag of channel 2 */
#define DMA_INTC_HTFIFC2               _BIT(10,U)                 /*!< clear half transfer finish flag of channel 2 */
#define DMA_INTC_FTFIFC2               _BIT(9,U)                  /*!< clear transfer finish flag of channel 2 */
#define DMA_INTC_GIFC2                 _BIT(8,U)                  /*!< clear global interrupt flag of channel 2 */
#define DMA_INTC_ERRIFC1               _BIT(7,U)                  /*!< clear error flag of channel 1 */
#define DMA_INTC_HTFIFC1               _BIT(6,U)                  /*!< clear half transfer finish flag of channel 1 */
#define DMA_INTC_FTFIFC1               _BIT(5,U)                  /*!< clear transfer finish flag of channel 1 */
#define DMA_INTC_GIFC1                 _BIT(4,U)                  /*!< clear global interrupt flag of channel 1 */
#define DMA_INTC_ERRIFC0               _BIT(3,U)                  /*!< clear error flag of channel 0 */
#define DMA_INTC_HTFIFC0               _BIT(2,U)                  /*!< clear half transfer finish flag of channel 0 */
#define DMA_INTC_FTFIFC0               _BIT(1,U)                  /*!< clear transfer finish flag of channel 0 */
#define DMA_INTC_GIFC0                 _BIT(0,U)                  /*!< clear global interrupt flag of channel 0 */
#define DMA_INTC_ERRIFC(x)             (_AC(1,U) << (4*(x) + 3))  /*!< clear error flag of channel x */
#define DMA_INTC_HTFIFC(x)             (_AC(1,U) << (4*(x) + 2))  /*!< clear half transfer finish flag of channel x */
#define DMA_INTC_FTFIFC(x)             (_AC(1,U) << (4*(x) + 1))  /*!< clear transfer finish flag of channel x */
#define DMA_INTC_GIFC(x)               (_AC(1,U) << (4*(x) + 0))  /*!< clear global interrupt flag of channel x */

/* DMA_CHxCTL, x=0..6 */
#define DMA_CHXCTL_M2M                 _BIT(14,U)                 /*!< memory to memory mode */
#define DMA_CHXCTL_PRIO_Pos            12
#define DMA_CHXCTL_PRIO_Msk            _AC(0x00003000,U)          /*!< priority level */
#define DMA_CHXCTL_PRIO(x)             ((x) << DMA_CHXCTL_PRIO_Pos)
#define DMA_CHXCTL_PRIO_LOW            DMA_CHXCTL_PRIO(0)         /*!< low priority */
#define DMA_CHXCTL_PRIO_MEDIUM         DMA_CHXCTL_PRIO(1)         /*!< medium priority */
#define DMA_CHXCTL_PRIO_HIGH           DMA_CHXCTL_PRIO(2)         /*!< high priority */
#define DMA_CHXCTL_PRIO_ULTRA_HIGH     DMA_CHXCTL_PRIO(3)         /*!< ultra high priority */
#define DMA_CHXCTL_MWIDTH_Pos          10
#define DMA_CHXCTL_MWIDTH_Msk          _AC(0x00000c00,U)          /*!< transfer data width of memory */
#define DMA_CHXCTL_MWIDTH(x)           ((x) << DMA_CHXCTL_MWIDTH_Pos)
#define DMA_CHXCTL_MWIDTH_8BIT         DMA_CHXCTL_MWIDTH(0)       /*!< transfer data size of memory is 8-bit */
#define DMA_CHXCTL_MWIDTH_16BIT        DMA_CHXCTL_MWIDTH(1)       /*!< transfer data size of memory is 16-bit */
#define DMA_CHXCTL_MWIDTH_32BIT        DMA_CHXCTL_MWIDTH(2)       /*!< transfer data size of memory is 32-bit */
#define DMA_CHXCTL_PWIDTH_Pos          8
#define DMA_CHXCTL_PWIDTH_Msk          _AC(0x00000300,U)          /*!< transfer data width of peripheral */
#define DMA_CHXCTL_PWIDTH(x)           ((x) << DMA_CHXCTL_PWIDTH_Pos)
#define DMA_CHXCTL_PWIDTH_8BIT         DMA_CHXCTL_PWIDTH(0)       /*!< transfer data size of peripheral is 8-bit */
#define DMA_CHXCTL_PWIDTH_16BIT        DMA_CHXCTL_PWIDTH(1)       /*!< transfer data size of peripheral is 16-bit */
#define DMA_CHXCTL_PWIDTH_32BIT        DMA_CHXCTL_PWIDTH(2)       /*!< transfer data size of peripheral is 32-bit */
#define DMA_CHXCTL_MNAGA               _BIT(7,U)                  /*!< next address generation algorithm of memory */
#define DMA_CHXCTL_PNAGA               _BIT(6,U)                  /*!< next address generation algorithm of peripheral */
#define DMA_CHXCTL_CMEN                _BIT(5,U)                  /*!< circular mode enable */
#define DMA_CHXCTL_DIR                 _BIT(4,U)                  /*!< transfer direction */
#define DMA_CHXCTL_ERRIE               _BIT(3,U)                  /*!< enable bit for channel error interrupt */
#define DMA_CHXCTL_HTFIE               _BIT(2,U)                  /*!< enable bit for channel half transfer finish interrupt */
#define DMA_CHXCTL_FTFIE               _BIT(1,U)                  /*!< enable bit for channel full transfer finish interrupt */
#define DMA_CHXCTL_CHEN                _BIT(0,U)                  /*!< channel enable */

/* DMA_CHxCNT, x=0..6 */
#define DMA_CHXCNT_CNT_Pos             0
#define DMA_CHXCNT_CNT_Msk             _AC(0x0000ffff,U)          /*!< transfer counter */
#define DMA_CHXCNT_CNT(x)              ((x) << DMA_CHXCNT_CNT_Pos)

/* DMA_CHxPADDR, x=0..6 */
#define DMA_CHXPADDR_PADDR_Pos         0
#define DMA_CHXPADDR_PADDR_Msk         _AC(0xffffffff,U)          /*!< peripheral base address */
#define DMA_CHXPADDR_PADDR(x)          ((x) << DMA_CHXPADDR_PADDR_Pos)

/* DMA_CHxMADDR, x=0..6 */
#define DMA_CHXPADDR_MADDR_Pos         0
#define DMA_CHXMADDR_MADDR_Msk         _AC(0xffffffff,U)          /*!< memory base address */
#define DMA_CHXPADDR_MADDR(x)          ((x) << DMA_CHXPADDR_MADDR_Pos)

/* --------------------- ECLIC -------------------------- */

#define ECLIC_BASE                     _AC(0xD2000000,UL)  /*!< ECLIC base address */

/* interrupt numbers */
#define RESERVED_IRQn                   0  /*!< RISC-V reserved                           */
#define MSOFTWARE_IRQn                  3  /*!< Software interrupt                        */
#define MTIMER_IRQn                     7  /*!< CPU Timer interrupt                       */
#define MEMACCESS_IRQn                 17  /*!< Bus Error interrupt                       */
#define PMON_IRQn                      18  /*!< Performance Monitor                       */

#define WWDGT_IRQn                     19  /*!< window watchDog timer interrupt           */
#define LVD_IRQn                       20  /*!< LVD through EXTI line detect interrupt    */
#define TAMPER_IRQn                    21  /*!< tamper through EXTI line detect           */
#define RTC_IRQn                       22  /*!< RTC alarm interrupt                       */
#define FMC_IRQn                       23  /*!< FMC interrupt                             */
#define RCU_CTC_IRQn                   24  /*!< RCU and CTC interrupt                     */
#define EXTI0_IRQn                     25  /*!< EXTI line 0 interrupts                    */
#define EXTI1_IRQn                     26  /*!< EXTI line 1 interrupts                    */
#define EXTI2_IRQn                     27  /*!< EXTI line 2 interrupts                    */
#define EXTI3_IRQn                     28  /*!< EXTI line 3 interrupts                    */
#define EXTI4_IRQn                     29  /*!< EXTI line 4 interrupts                    */
#define DMA0_Channel0_IRQn             30  /*!< DMA0 channel0 interrupt                   */
#define DMA0_Channel1_IRQn             31  /*!< DMA0 channel1 interrupt                   */
#define DMA0_Channel2_IRQn             32  /*!< DMA0 channel2 interrupt                   */
#define DMA0_Channel3_IRQn             33  /*!< DMA0 channel3 interrupt                   */
#define DMA0_Channel4_IRQn             34  /*!< DMA0 channel4 interrupt                   */
#define DMA0_Channel5_IRQn             35  /*!< DMA0 channel5 interrupt                   */
#define DMA0_Channel6_IRQn             36  /*!< DMA0 channel6 interrupt                   */
#define ADC0_1_IRQn                    37  /*!< ADC0 and ADC1 interrupt                   */
#define CAN0_TX_IRQn                   38  /*!< CAN0 TX interrupts                        */
#define CAN0_RX0_IRQn                  39  /*!< CAN0 RX0 interrupts                       */
#define CAN0_RX1_IRQn                  40  /*!< CAN0 RX1 interrupts                       */
#define CAN0_EWMC_IRQn                 41  /*!< CAN0 EWMC interrupts                      */
#define EXTI5_9_IRQn                   42  /*!< EXTI[9:5] interrupts                      */
#define TIMER0_BRK_IRQn                43  /*!< TIMER0 break interrupts                   */
#define TIMER0_UP_IRQn                 44  /*!< TIMER0 update interrupts                  */
#define TIMER0_TRG_CMT_IRQn            45  /*!< TIMER0 trigger and commutation interrupts */
#define TIMER0_Channel_IRQn            46  /*!< TIMER0 channel capture compare interrupts */
#define TIMER1_IRQn                    47  /*!< TIMER1 interrupt                          */
#define TIMER2_IRQn                    48  /*!< TIMER2 interrupt                          */
#define TIMER3_IRQn                    49  /*!< TIMER3 interrupts                         */
#define I2C0_EV_IRQn                   50  /*!< I2C0 event interrupt                      */
#define I2C0_ER_IRQn                   51  /*!< I2C0 error interrupt                      */
#define I2C1_EV_IRQn                   52  /*!< I2C1 event interrupt                      */
#define I2C1_ER_IRQn                   53  /*!< I2C1 error interrupt                      */
#define SPI0_IRQn                      54  /*!< SPI0 interrupt                            */
#define SPI1_IRQn                      55  /*!< SPI1 interrupt                            */
#define USART0_IRQn                    56  /*!< USART0 interrupt                          */
#define USART1_IRQn                    57  /*!< USART1 interrupt                          */
#define USART2_IRQn                    58  /*!< USART2 interrupt                          */
#define EXTI10_15_IRQn                 59  /*!< EXTI[15:10] interrupts                    */
#define RTC_ALARM_IRQn                 60  /*!< RTC alarm interrupt EXTI                  */
#define USBFS_WKUP_IRQn                61  /*!< USBFS wakeup interrupt                    */

#define EXMC_IRQn                      67  /*!< EXMC global interrupt                     */

#define TIMER4_IRQn                    69  /*!< TIMER4 global interrupt                   */
#define SPI2_IRQn                      70  /*!< SPI2 global interrupt                     */
#define UART3_IRQn                     71  /*!< UART3 global interrupt                    */
#define UART4_IRQn                     72  /*!< UART4 global interrupt                    */
#define TIMER5_IRQn                    73  /*!< TIMER5 global interrupt                   */
#define TIMER6_IRQn                    74  /*!< TIMER6 global interrupt                   */
#define DMA1_Channel0_IRQn             75  /*!< DMA1 channel0 global interrupt            */
#define DMA1_Channel1_IRQn             76  /*!< DMA1 channel1 global interrupt            */
#define DMA1_Channel2_IRQn             77  /*!< DMA1 channel2 global interrupt            */
#define DMA1_Channel3_IRQn             78  /*!< DMA1 channel3 global interrupt            */
#define DMA1_Channel4_IRQn             79  /*!< DMA1 channel3 global interrupt            */

#define CAN1_TX_IRQn                   82  /*!< CAN1 TX interrupt                         */
#define CAN1_RX0_IRQn                  83  /*!< CAN1 RX0 interrupt                        */
#define CAN1_RX1_IRQn                  84  /*!< CAN1 RX1 interrupt                        */
#define CAN1_EWMC_IRQn                 85  /*!< CAN1 EWMC interrupt                       */
#define USBFS_IRQn                     86  /*!< USBFS global interrupt                    */

/* eclic info - also available in the INFO register */
#define ECLIC_NUM_INTERRUPTS           87
#define ECLIC_INTCTLBITS               4

/* register definitions */
#define ECLIC_CFG                      _AC(0x0000,UL)
#define ECLIC_INFO                     _AC(0x0004,UL)
#define ECLIC_MTH                      _AC(0x000b,UL)
#define ECLIC_IP(x)                    (_AC(0x1000,UL) + 4*(x))
#define ECLIC_IE(x)                    (_AC(0x1001,UL) + 4*(x))
#define ECLIC_ATTR(x)                  (_AC(0x1002,UL) + 4*(x))
#define ECLIC_CTRL(x)                  (_AC(0x1003,UL) + 4*(x))

/* cfg bits */
#define ECLIC_CFG_NLBITS_Pos           1
#define ECLIC_CFG_NLBITS_Msk           0x1e
#define ECLIC_CFG_NLBITS(x)            ((x) << ECLIC_CFG_NLBITS_Pos)

/* info bits */
#define ECLIC_INFO_CLICINTCTLBITS_Pos  21
#define ECLIC_INFO_CLICINTCTLBITS_Msk  _AC(0x01e00000,U)
#define ECLIC_INFO_VERSION_Pos         13
#define ECLIC_INFO_VERSION_Msk         _AC(0x001fe000,U)
#define ECLIC_INFO_NUM_INTERRUPT_Pos   0
#define ECLIC_INFO_NUM_INTERRUPT_Msk   _AC(0x00001fff,U)

/* mth bits */
#define ECLIC_MTH_MTH_Pos              0
#define ECLIC_MTH_MTH_Msk              0xff
#define ECLIC_MTH_MTH(x)               ((x) << ECLIC_MTH_MTH_Pos)

/* ip bits */
#define ECLIC_IP_IP                    0x01

/* ie bits */
#define ECLIC_IE_IE                    0x01

/* attr bits */
#define ECLIC_ATTR_TRIG_Pos            1
#define ECLIC_ATTR_TRIG_Msk            0x06
#define ECLIC_ATTR_TRIG(x)             ((x) << ECLIC_ATTR_TRIG_Pos)
#define ECLIC_ATTR_TRIG_LEVEL          ECLIC_ATTR_TRIG(0)
#define ECLIC_ATTR_TRIG_EDGE_POS       ECLIC_ATTR_TRIG(1)
#define ECLIC_ATTR_TRIG_EDGE_NEG       ECLIC_ATTR_TRIG(3)
#define ECLIC_ATTR_SHV                 0x01

/* ctl bits */
#ifdef ECLIC_INTCTLBITS
    #define ECLIC_CTL_BITS_Pos         (8 - ECLIC_INTCTLBITS)
    #define ECLIC_CTL_BITS_Msk         (0x100 - (1 << ECLIC_CTL_BITS_Pos))
    #define ECLIC_CTL_BITS(x)          ((x) << ECLIC_CTL_BITS_Pos)
#endif

/* constants definitions */
#define ECLIC_PRIGROUP_LEVEL0_PRIO4    0  /*!< 0 bits for level 4 bits for priority */
#define ECLIC_PRIGROUP_LEVEL1_PRIO3    1  /*!< 1 bits for level 3 bits for priority */
#define ECLIC_PRIGROUP_LEVEL2_PRIO2    2  /*!< 2 bits for level 2 bits for priority */
#define ECLIC_PRIGROUP_LEVEL3_PRIO1    3  /*!< 3 bits for level 1 bits for priority */
#define ECLIC_PRIGROUP_LEVEL4_PRIO0    4  /*!< 4 bits for level 0 bits for priority */

/* --------------------- EXMC -------------------------- */

#define EXMC_BASE                      _AC(0xA0000000,UL)  /*!< EXMC register base address */

/* register definitions */
#define EXMC_SNCTL0                    _AC(0x000,UL)  /*!< EXMC SRAM/NOR flash control register 0 */
#define EXMC_SNTCFG0                   _AC(0x004,UL)  /*!< EXMC SRAM/NOR flash timing configuration register 0 */
#define EXMC_SNWTCFG0                  _AC(0x104,UL)  /*!< EXMC SRAM/NOR flash write timing configuration register 0 */

/* EXMC_SNCTLx, x=0 */
#define EXMC_SNCTL_ASYNCWAIT           _BIT(15,U)          /*!< asynchronous wait */
#define EXMC_SNCTL_NRWTEN              _BIT(13,U)          /*!< NWAIT signal enable */
#define EXMC_SNCTL_WREN                _BIT(12,U)          /*!< write enable */
#define EXMC_SNCTL_NRWTPOL             _BIT(9,U)           /*!< NWAIT signal polarity */
#define EXMC_SNCTL_NREN                _BIT(6,U)           /*!< NOR flash access enable */
#define EXMC_SNCTL_NRW_Pos             4
#define EXMC_SNCTL_NRW_Msk             _AC(0x00000030,U)   /*!< NOR bank memory data bus width */
#define EXMC_SNCTL_NRW(x)              ((x) << EXMC_SNCTL_NRW_Pos)
#define EXMC_SNCTL_NRW_8B              EXMC_SNCTL_NRW(0)   /*!< NOR data width 8 bits */
#define EXMC_SNCTL_NRW_16B             EXMC_SNCTL_NRW(1)   /*!< NOR data width 16 bits */
#define EXMC_SNCTL_NRTP_Pos            2
#define EXMC_SNCTL_NRTP_Msk            _AC(0x0000000c,U)   /*!< NOR bank memory type */
#define EXMC_SNCTL_NRTP(x)             ((x) << EXMC_SNCTL_NRTP_Pos)
#define EXMC_SNCTL_NRTP_SRAM           EXMC_SNCTL_NRTP(0)  /*!< SRAM,ROM */
#define EXMC_SNCTL_NRTP_PSRAM          EXMC_SNCTL_NRTP(1)  /*!< PSRAM,CRAM */
#define EXMC_SNCTL_NRTP_NOR            EXMC_SNCTL_NRTP(2)  /*!< NOR flash */
#define EXMC_SNCTL_NRMUX               _BIT(1,U)           /*!< NOR bank memory address/data multiplexing */
#define EXMC_SNCTL_NRBKEN              _BIT(0,U)           /*!< NOR bank enable */

/* EXMC_SNTCFGx, x=0 */
#define EXMC_SNTCFG_BUSLAT_Pos         16
#define EXMC_SNTCFG_BUSLAT_Msk         _AC(0x000f0000,U)   /*!< bus latency */
#define EXMC_SNTCFG_BUSLAT(x)          ((x) << EXMC_SNTCFG_BUSLAT_Pos)
#define EXMC_SNTCFG_DSET_Pos           8
#define EXMC_SNTCFG_DSET_Msk           _AC(0x0000ff00,U)   /*!< data setup time */
#define EXMC_SNTCFG_DSET(x)            ((x) << EXMC_SNTCFG_DSET_Pos)
#define EXMC_SNTCFG_AHLD_Pos           4
#define EXMC_SNTCFG_AHLD_Msk           _AC(0x000000f0,U)   /*!< address hold time */
#define EXMC_SNTCFG_AHLD(x)            ((x) << EXMC_SNTCFG_AHLD_Pos)
#define EXMC_SNTCFG_ASET_Pos           0
#define EXMC_SNTCFG_ASET_Msk           _AC(0x0000000f,U)   /*!< address setup time */
#define EXMC_SNTCFG_ASET(x)            ((x) << EXMC_SNTCFG_ASET_Pos)

/* --------------------- EXTI -------------------------- */

#define EXTI_BASE                      _AC(0x40010400,UL)  /*!< EXTI base address */

/* register definitions */
#define EXTI_INTEN                     _AC(0x00,UL)  /*!< interrupt enable register */
#define EXTI_EVEN                      _AC(0x04,UL)  /*!< event enable register */
#define EXTI_RTEN                      _AC(0x08,UL)  /*!< rising edge trigger enable register */
#define EXTI_FTEN                      _AC(0x0C,UL)  /*!< falling trigger enable register */
#define EXTI_SWIEV                     _AC(0x10,UL)  /*!< software interrupt event register */
#define EXTI_PD                        _AC(0x14,UL)  /*!< pending register */

/* EXTI_INTEN */
#define EXTI_INTEN_INTEN18             _BIT(18,U)         /*!< interrupt from line 18 */
#define EXTI_INTEN_INTEN17             _BIT(17,U)         /*!< interrupt from line 17 */
#define EXTI_INTEN_INTEN16             _BIT(16,U)         /*!< interrupt from line 16 */
#define EXTI_INTEN_INTEN15             _BIT(15,U)         /*!< interrupt from line 15 */
#define EXTI_INTEN_INTEN14             _BIT(14,U)         /*!< interrupt from line 14 */
#define EXTI_INTEN_INTEN13             _BIT(13,U)         /*!< interrupt from line 13 */
#define EXTI_INTEN_INTEN12             _BIT(12,U)         /*!< interrupt from line 12 */
#define EXTI_INTEN_INTEN11             _BIT(11,U)         /*!< interrupt from line 11 */
#define EXTI_INTEN_INTEN10             _BIT(10,U)         /*!< interrupt from line 10 */
#define EXTI_INTEN_INTEN9              _BIT(9,U)          /*!< interrupt from line 9 */
#define EXTI_INTEN_INTEN8              _BIT(8,U)          /*!< interrupt from line 8 */
#define EXTI_INTEN_INTEN7              _BIT(7,U)          /*!< interrupt from line 7 */
#define EXTI_INTEN_INTEN6              _BIT(6,U)          /*!< interrupt from line 6 */
#define EXTI_INTEN_INTEN5              _BIT(5,U)          /*!< interrupt from line 5 */
#define EXTI_INTEN_INTEN4              _BIT(4,U)          /*!< interrupt from line 4 */
#define EXTI_INTEN_INTEN3              _BIT(3,U)          /*!< interrupt from line 3 */
#define EXTI_INTEN_INTEN2              _BIT(2,U)          /*!< interrupt from line 2 */
#define EXTI_INTEN_INTEN1              _BIT(1,U)          /*!< interrupt from line 1 */
#define EXTI_INTEN_INTEN0              _BIT(0,U)          /*!< interrupt from line 0 */
#define EXTI_INTEN_INTEN(x)            _BIT(x,U)

/* EXTI_EVEN */
#define EXTI_EVEN_EVEN18               _BIT(18,U)         /*!< event from line 18 */
#define EXTI_EVEN_EVEN17               _BIT(17,U)         /*!< event from line 17 */
#define EXTI_EVEN_EVEN16               _BIT(16,U)         /*!< event from line 16 */
#define EXTI_EVEN_EVEN15               _BIT(15,U)         /*!< event from line 15 */
#define EXTI_EVEN_EVEN14               _BIT(14,U)         /*!< event from line 14 */
#define EXTI_EVEN_EVEN13               _BIT(13,U)         /*!< event from line 13 */
#define EXTI_EVEN_EVEN12               _BIT(12,U)         /*!< event from line 12 */
#define EXTI_EVEN_EVEN11               _BIT(11,U)         /*!< event from line 11 */
#define EXTI_EVEN_EVEN10               _BIT(10,U)         /*!< event from line 10 */
#define EXTI_EVEN_EVEN9                _BIT(9,U)          /*!< event from line 9 */
#define EXTI_EVEN_EVEN8                _BIT(8,U)          /*!< event from line 8 */
#define EXTI_EVEN_EVEN7                _BIT(7,U)          /*!< event from line 7 */
#define EXTI_EVEN_EVEN6                _BIT(6,U)          /*!< event from line 6 */
#define EXTI_EVEN_EVEN5                _BIT(5,U)          /*!< event from line 5 */
#define EXTI_EVEN_EVEN4                _BIT(4,U)          /*!< event from line 4 */
#define EXTI_EVEN_EVEN3                _BIT(3,U)          /*!< event from line 3 */
#define EXTI_EVEN_EVEN2                _BIT(2,U)          /*!< event from line 2 */
#define EXTI_EVEN_EVEN1                _BIT(1,U)          /*!< event from line 1 */
#define EXTI_EVEN_EVEN0                _BIT(0,U)          /*!< event from line 0 */
#define EXTI_EVEN_EVEN(x)              _BIT(x,U)

/* EXTI_RTEN */
#define EXTI_RTEN_RTEN18               _BIT(18,U)         /*!< rising edge from line 18 */
#define EXTI_RTEN_RTEN17               _BIT(17,U)         /*!< rising edge from line 17 */
#define EXTI_RTEN_RTEN16               _BIT(16,U)         /*!< rising edge from line 16 */
#define EXTI_RTEN_RTEN15               _BIT(15,U)         /*!< rising edge from line 15 */
#define EXTI_RTEN_RTEN14               _BIT(14,U)         /*!< rising edge from line 14 */
#define EXTI_RTEN_RTEN13               _BIT(13,U)         /*!< rising edge from line 13 */
#define EXTI_RTEN_RTEN12               _BIT(12,U)         /*!< rising edge from line 12 */
#define EXTI_RTEN_RTEN11               _BIT(11,U)         /*!< rising edge from line 11 */
#define EXTI_RTEN_RTEN10               _BIT(10,U)         /*!< rising edge from line 10 */
#define EXTI_RTEN_RTEN9                _BIT(9,U)          /*!< rising edge from line 9 */
#define EXTI_RTEN_RTEN8                _BIT(8,U)          /*!< rising edge from line 8 */
#define EXTI_RTEN_RTEN7                _BIT(7,U)          /*!< rising edge from line 7 */
#define EXTI_RTEN_RTEN6                _BIT(6,U)          /*!< rising edge from line 6 */
#define EXTI_RTEN_RTEN5                _BIT(5,U)          /*!< rising edge from line 5 */
#define EXTI_RTEN_RTEN4                _BIT(4,U)          /*!< rising edge from line 4 */
#define EXTI_RTEN_RTEN3                _BIT(3,U)          /*!< rising edge from line 3 */
#define EXTI_RTEN_RTEN2                _BIT(2,U)          /*!< rising edge from line 2 */
#define EXTI_RTEN_RTEN1                _BIT(1,U)          /*!< rising edge from line 1 */
#define EXTI_RTEN_RTEN0                _BIT(0,U)          /*!< rising edge from line 0 */
#define EXTI_RTEN_RTEN(x)              _BIT(x,U)

/* EXTI_FTEN */
#define EXTI_FTEN_FTEN18               _BIT(18,U)         /*!< falling edge from line 18 */
#define EXTI_FTEN_FTEN17               _BIT(17,U)         /*!< falling edge from line 17 */
#define EXTI_FTEN_FTEN16               _BIT(16,U)         /*!< falling edge from line 16 */
#define EXTI_FTEN_FTEN15               _BIT(15,U)         /*!< falling edge from line 15 */
#define EXTI_FTEN_FTEN14               _BIT(14,U)         /*!< falling edge from line 14 */
#define EXTI_FTEN_FTEN13               _BIT(13,U)         /*!< falling edge from line 13 */
#define EXTI_FTEN_FTEN12               _BIT(12,U)         /*!< falling edge from line 12 */
#define EXTI_FTEN_FTEN11               _BIT(11,U)         /*!< falling edge from line 11 */
#define EXTI_FTEN_FTEN10               _BIT(10,U)         /*!< falling edge from line 10 */
#define EXTI_FTEN_FTEN9                _BIT(9,U)          /*!< falling edge from line 9 */
#define EXTI_FTEN_FTEN8                _BIT(8,U)          /*!< falling edge from line 8 */
#define EXTI_FTEN_FTEN7                _BIT(7,U)          /*!< falling edge from line 7 */
#define EXTI_FTEN_FTEN6                _BIT(6,U)          /*!< falling edge from line 6 */
#define EXTI_FTEN_FTEN5                _BIT(5,U)          /*!< falling edge from line 5 */
#define EXTI_FTEN_FTEN4                _BIT(4,U)          /*!< falling edge from line 4 */
#define EXTI_FTEN_FTEN3                _BIT(3,U)          /*!< falling edge from line 3 */
#define EXTI_FTEN_FTEN2                _BIT(2,U)          /*!< falling edge from line 2 */
#define EXTI_FTEN_FTEN1                _BIT(1,U)          /*!< falling edge from line 1 */
#define EXTI_FTEN_FTEN0                _BIT(0,U)          /*!< falling edge from line 0 */
#define EXTI_FTEN_FTEN(x)              _BIT(x,U)

/* EXTI_SWIEV */
#define EXTI_SWIEV_SWIEV18             _BIT(18,U)         /*!< software interrupt/event request from line 18 */
#define EXTI_SWIEV_SWIEV17             _BIT(17,U)         /*!< software interrupt/event request from line 17 */
#define EXTI_SWIEV_SWIEV16             _BIT(16,U)         /*!< software interrupt/event request from line 16 */
#define EXTI_SWIEV_SWIEV15             _BIT(15,U)         /*!< software interrupt/event request from line 15 */
#define EXTI_SWIEV_SWIEV14             _BIT(14,U)         /*!< software interrupt/event request from line 14 */
#define EXTI_SWIEV_SWIEV13             _BIT(13,U)         /*!< software interrupt/event request from line 13 */
#define EXTI_SWIEV_SWIEV12             _BIT(12,U)         /*!< software interrupt/event request from line 12 */
#define EXTI_SWIEV_SWIEV11             _BIT(11,U)         /*!< software interrupt/event request from line 11 */
#define EXTI_SWIEV_SWIEV10             _BIT(10,U)         /*!< software interrupt/event request from line 10 */
#define EXTI_SWIEV_SWIEV9              _BIT(9,U)          /*!< software interrupt/event request from line 9 */
#define EXTI_SWIEV_SWIEV8              _BIT(8,U)          /*!< software interrupt/event request from line 8 */
#define EXTI_SWIEV_SWIEV7              _BIT(7,U)          /*!< software interrupt/event request from line 7 */
#define EXTI_SWIEV_SWIEV6              _BIT(6,U)          /*!< software interrupt/event request from line 6 */
#define EXTI_SWIEV_SWIEV5              _BIT(5,U)          /*!< software interrupt/event request from line 5 */
#define EXTI_SWIEV_SWIEV4              _BIT(4,U)          /*!< software interrupt/event request from line 4 */
#define EXTI_SWIEV_SWIEV3              _BIT(3,U)          /*!< software interrupt/event request from line 3 */
#define EXTI_SWIEV_SWIEV2              _BIT(2,U)          /*!< software interrupt/event request from line 2 */
#define EXTI_SWIEV_SWIEV1              _BIT(1,U)          /*!< software interrupt/event request from line 1 */
#define EXTI_SWIEV_SWIEV0              _BIT(0,U)          /*!< software interrupt/event request from line 0 */
#define EXTI_SWIEV_SWIEV(x)            _BIT(x,U)

/* EXTI_PD */
#define EXTI_PD_PD18                   _BIT(18,U)         /*!< interrupt/event pending status from line 18 */
#define EXTI_PD_PD17                   _BIT(17,U)         /*!< interrupt/event pending status from line 17 */
#define EXTI_PD_PD16                   _BIT(16,U)         /*!< interrupt/event pending status from line 16 */
#define EXTI_PD_PD15                   _BIT(15,U)         /*!< interrupt/event pending status from line 15 */
#define EXTI_PD_PD14                   _BIT(14,U)         /*!< interrupt/event pending status from line 14 */
#define EXTI_PD_PD13                   _BIT(13,U)         /*!< interrupt/event pending status from line 13 */
#define EXTI_PD_PD12                   _BIT(12,U)         /*!< interrupt/event pending status from line 12 */
#define EXTI_PD_PD11                   _BIT(11,U)         /*!< interrupt/event pending status from line 11 */
#define EXTI_PD_PD10                   _BIT(10,U)         /*!< interrupt/event pending status from line 10 */
#define EXTI_PD_PD9                    _BIT(9,U)          /*!< interrupt/event pending status from line 9 */
#define EXTI_PD_PD8                    _BIT(8,U)          /*!< interrupt/event pending status from line 8 */
#define EXTI_PD_PD7                    _BIT(7,U)          /*!< interrupt/event pending status from line 7 */
#define EXTI_PD_PD6                    _BIT(6,U)          /*!< interrupt/event pending status from line 6 */
#define EXTI_PD_PD5                    _BIT(5,U)          /*!< interrupt/event pending status from line 5 */
#define EXTI_PD_PD4                    _BIT(4,U)          /*!< interrupt/event pending status from line 4 */
#define EXTI_PD_PD3                    _BIT(3,U)          /*!< interrupt/event pending status from line 3 */
#define EXTI_PD_PD2                    _BIT(2,U)          /*!< interrupt/event pending status from line 2 */
#define EXTI_PD_PD1                    _BIT(1,U)          /*!< interrupt/event pending status from line 1 */
#define EXTI_PD_PD0                    _BIT(0,U)          /*!< interrupt/event pending status from line 0 */
#define EXTI_PD_PD(x)                  _BIT(x,U)

/* --------------------- FMC -------------------------- */

#define OB_BASE                        _AC(0x1FFFF800,UL)  /*!< OB base address  */
#define FMC_BASE                       _AC(0x40022000,UL)  /*!< FMC base address */

/* register definitions */
#define FMC_WS                         _AC(0x000,UL)  /*!< FMC wait state register */
#define FMC_KEY                        _AC(0x004,UL)  /*!< FMC unlock key register 0 */
#define FMC_OBKEY                      _AC(0x008,UL)  /*!< FMC option bytes unlock key register */
#define FMC_STAT                       _AC(0x00C,UL)  /*!< FMC status register 0 */
#define FMC_CTL                        _AC(0x010,UL)  /*!< FMC control register 0 */
#define FMC_ADDR                       _AC(0x014,UL)  /*!< FMC address register 0 */
#define FMC_OBSTAT                     _AC(0x01C,UL)  /*!< FMC option bytes status register */
#define FMC_WP                         _AC(0x020,UL)  /*!< FMC erase/program protection register */

#define FMC_PID                        _AC(0x100,UL)  /*!< FMC product ID register */

#define OB_SPC                         _AC(0x000,UL)  /*!< option byte security protection value */
#define OB_USER                        _AC(0x002,UL)  /*!< option byte user value*/
#define OB_WP0                         _AC(0x008,UL)  /*!< option byte write protection 0 */
#define OB_WP1                         _AC(0x00A,UL)  /*!< option byte write protection 1 */
#define OB_WP2                         _AC(0x00C,UL)  /*!< option byte write protection 2 */
#define OB_WP3                         _AC(0x00E,UL)  /*!< option byte write protection 3 */

/* FMC_WS */
#define FMC_WS_WSCNT_Pos               0
#define FMC_WS_WSCNT_Msk               _AC(0x00000007,U)  /*!< wait state counter */
#define FMC_WS_WSCNT(x)                ((x) << FMC_WS_WSCNT_Pos)
#define FMC_WS_WSCNT_0                 FMC_WS_WSCNT(0)    /*!< FMC 0 wait */
#define FMC_WS_WSCNT_1                 FMC_WS_WSCNT(1)    /*!< FMC 1 wait */
#define FMC_WS_WSCNT_2                 FMC_WS_WSCNT(2)    /*!< FMC 2 wait */

/* FMC_KEY */
#define FMC_KEY_UNLOCK0                _AC(0x45670123,U)  /*!< fmc unlock key 0 */
#define FMC_KEY_UNLOCK1                _AC(0xCDEF89AB,U)  /*!< fmc unlock key 1 */

/* FMC_OBKEY */
#define FMC_OBKEY_UNLOCK0              _AC(0x45670123,U)  /*!< option bytes unlock key 0 */
#define FMC_OBKEY_UNLOCK1              _AC(0xCDEF89AB,U)  /*!< option bytes unlock key 1 */

/* FMC_STAT */
#define FMC_STAT_ENDF                  _BIT(5,U)          /*!< end of operation flag bit */
#define FMC_STAT_WPERR                 _BIT(4,U)          /*!< erase/program protection error flag bit */
#define FMC_STAT_PGERR                 _BIT(2,U)          /*!< flash program error flag bit */
#define FMC_STAT_BUSY                  _BIT(0,U)          /*!< flash busy flag bit */

/* FMC_CTL */
#define FMC_CTL_ENDIE                  _BIT(12,U)         /*!< end of operation interrupt enable bit */
#define FMC_CTL_ERRIE                  _BIT(10,U)         /*!< error interrupt enable bit */
#define FMC_CTL_OBWEN                  _BIT(9,U)          /*!< option bytes erase/program enable bit */
#define FMC_CTL_LK                     _BIT(7,U)          /*!< FMC_CTL lock bit */
#define FMC_CTL_START                  _BIT(6,U)          /*!< send erase command to FMC bit */
#define FMC_CTL_OBER                   _BIT(5,U)          /*!< option bytes erase command bit */
#define FMC_CTL_OBPG                   _BIT(4,U)          /*!< option bytes program command bit */
#define FMC_CTL_MER                    _BIT(2,U)          /*!< main flash mass erase for bank0 command bit */
#define FMC_CTL_PER                    _BIT(1,U)          /*!< main flash page erase for bank0 command bit */
#define FMC_CTL_PG                     _BIT(0,U)          /*!< main flash program for bank0 command bit */

/* FMC_OBSTAT */
#define FMC_OBSTAT_DATA_Pos            10
#define FMC_OBSTAT_DATA_Msk            _AC(0x03fffc00,U)  /*!< store DATA of option bytes block after system reset. */
#define FMC_OBSTAT_DATA(x)             ((x) << FMC_OBSTAT_DATA_Pos)
#define FMC_OBSTAT_USER_Pos            2
#define FMC_OBSTAT_USER_Msk            _AC(0x000003fc,U)  /*!< store USER of option bytes block after system reset */
#define FMC_OBSTAT_USER(x)             ((x) << FMC_OBSTAT_USER_Pos)
#define FMC_OBSTAT_SPC                 _BIT(1,U)          /*!< option bytes security protection code */
#define FMC_OBSTAT_OBERR               _BIT(0,U)          /*!< option bytes read error bit. */

/* FMC_WSEN */
#define FMC_WSEN_WSEN                  _BIT(0,U)          /*!< FMC wait state enable bit */

/* OB_SPC */
#define OB_SPC_OFF                     0xA5               /*!< no security protection */

/* OB_USER */
#define OB_USER_BB                     0x08               /*!< boot from bank1 */
#define OB_USER_RST_STDBY              0x04               /*!< generate a reset instead of entering standby mode */
#define OB_USER_RST_DPSLP              0x02               /*!< generate a reset instead of entering deepsleep mode */
#define OB_USER_WDG_HW                 0x01               /*!< hardware free watchdog */

/* --------------------- FWDGT -------------------------- */

#define FWDGT_BASE                     _AC(0x40003000,UL)  /*!< FWDGT base address */

/* register definitions */
#define FWDGT_CTL                      _AC(0x00,UL)  /*!< FWDGT control register */
#define FWDGT_PSC                      _AC(0x04,UL)  /*!< FWDGT prescaler register */
#define FWDGT_RLD                      _AC(0x08,UL)  /*!< FWDGT reload register */
#define FWDGT_STAT                     _AC(0x0C,UL)  /*!< FWDGT status register */

/* FWDGT_CTL */
#define FWDGT_CTL_CMD_Pos              0
#define FWDGT_CTL_CMD_Msk              _AC(0x0000ffff,U)  /*!< FWDGT command value */
#define FWDGT_CTL_CMD(x)               ((x) << FWDGT_CTL_CMD_Pos)
#define FWDGT_CTL_CMD_WP_DISABLE       _AC(0x00005555,U)  /*!< disable FWDGT_PSC and FWDGT_RLD write protection */
#define FWDGT_CTL_CMD_WP_ENABLE        _AC(0x00000000,U)  /*!< enable FWDGT_PSC and FWDGT_RLD write protection */
#define FWDGT_CTL_CMD_RELOAD           _AC(0x0000aaaa,U)  /*!< reload watchdog counter */
#define FWDGT_CTL_CMD_START            _AC(0x0000cccc,U)  /*!< start watchdog counter */

/* FWDGT_PSC */
#define FWDGT_PSC_PSC_Pos              0
#define FWDGT_PSC_PSC_Msk              _AC(0x00000003,U)  /*!< FWDGT prescaler divider value */
#define FWDGT_PSC_PSC(x)               ((x) << FWDGT_PSC_PSC_Pos)
#define FWDGT_PSC_PSC_DIV4             FWDGT_PSC_PSC(0)   /*!< FWDGT prescaler set to 4 */
#define FWDGT_PSC_PSC_DIV8             FWDGT_PSC_PSC(1)   /*!< FWDGT prescaler set to 8 */
#define FWDGT_PSC_PSC_DIV16            FWDGT_PSC_PSC(2)   /*!< FWDGT prescaler set to 16 */
#define FWDGT_PSC_PSC_DIV32            FWDGT_PSC_PSC(3)   /*!< FWDGT prescaler set to 32 */
#define FWDGT_PSC_PSC_DIV64            FWDGT_PSC_PSC(4)   /*!< FWDGT prescaler set to 64 */
#define FWDGT_PSC_PSC_DIV128           FWDGT_PSC_PSC(5)   /*!< FWDGT prescaler set to 128 */
#define FWDGT_PSC_PSC_DIV256           FWDGT_PSC_PSC(6)   /*!< FWDGT prescaler set to 256 */

/* FWDGT_RLD */
#define FWDGT_RLD_RLD_Pos              0
#define FWDGT_RLD_RLD_Msk              _AC(0x00000fff,U)  /*!< FWDGT counter reload value */
#define FWDGT_RLD_RLD(x)               ((x) << FWDGT_RLD_RLD_Pos)

/* FWDGT_STAT */
#define FWDGT_STAT_RUD                 _BIT(1,U)          /*!< FWDGT counter reload value update */
#define FWDGT_STAT_PUD                 _BIT(0,U)          /*!< FWDGT prescaler divider value update */

/* --------------------- GPIO -------------------------- */

#define AFIO_BASE                      _AC(0x40010000,UL)  /*!< AFIO base address  */
#define GPIOA_BASE                     _AC(0x40010800,UL)  /*!< GPIOA base address */
#define GPIOB_BASE                     _AC(0x40010C00,UL)  /*!< GPIOB base address */
#define GPIOC_BASE                     _AC(0x40011000,UL)  /*!< GPIOC base address */
#if defined(GD32VF103R4T6) || defined(GD32VF103R6T6) || defined(GD32VF103R8T6) || \
    defined(GD32VF103RBT6) || defined(GD32VF103V8T6) || defined(GD32VF103VBT6)
    #define GPIOD_BASE                 _AC(0x40011400,UL)  /*!< GPIOD base address */
#endif
#if defined(GD32VF103V8T6) || defined(GD32VF103VBT6)
    #define GPIOE_BASE                 _AC(0x40011800,UL)  /*!< GPIOE base address */
#endif

/* register definitions */
#define GPIO_CTL0                      _AC(0x00,UL)  /*!< GPIO port control register 0 */
#define GPIO_CTL1                      _AC(0x04,UL)  /*!< GPIO port control register 1 */
#define GPIO_ISTAT                     _AC(0x08,UL)  /*!< GPIO port input status register */
#define GPIO_OCTL                      _AC(0x0C,UL)  /*!< GPIO port output control register */
#define GPIO_BOP                       _AC(0x10,UL)  /*!< GPIO port bit operation register */
#define GPIO_BC                        _AC(0x14,UL)  /*!< GPIO bit clear register */
#define GPIO_LOCK                      _AC(0x18,UL)  /*!< GPIO port configuration lock register */

#define AFIO_EC                        _AC(0x00,UL)  /*!< AFIO event control register */
#define AFIO_PCF0                      _AC(0x04,UL)  /*!< AFIO port configuration register 0 */
#define AFIO_EXTISS0                   _AC(0x08,UL)  /*!< AFIO port EXTI sources selection register 0 */
#define AFIO_EXTISS1                   _AC(0x0C,UL)  /*!< AFIO port EXTI sources selection register 1 */
#define AFIO_EXTISS2                   _AC(0x10,UL)  /*!< AFIO port EXTI sources selection register 2 */
#define AFIO_EXTISS3                   _AC(0x14,UL)  /*!< AFIO port EXTI sources selection register 3 */
#define AFIO_PCF1                      _AC(0x1C,UL)  /*!< AFIO port configuration register 1 */

/* GPIO_CTL0 */
#define GPIO_CTL0_MD_Pos(x)            (2*(x))
#define GPIO_CTL0_MD_Msk(x)            (_AC(0x3,U) << GPIO_CTL0_MD_Pos(x))
#define GPIO_CTL0_CTL_Pos(x)           (2*(x) + 2)
#define GPIO_CTL0_CTL_Msk(x)           (_AC(0x3,U) << GPIO_CTL0_CTL_Pos(x))
#define GPIO_CTL0_MD0_Pos              GPIO_CTL0_MD_Pos(0)
#define GPIO_CTL0_MD0_Msk              GPIO_CTL0_MD_Msk(0)   /*!< port 0 mode bits */
#define GPIO_CTL0_CTL0_Pos             GPIO_CTL0_CTL_Pos(0)
#define GPIO_CTL0_CTL0_Msk             GPIO_CTL0_CTL_Msk(0)  /*!< pin 0 configuration bits */
#define GPIO_CTL0_MD1_Pos              GPIO_CTL0_MD_Pos(1)
#define GPIO_CTL0_MD1_Msk              GPIO_CTL0_MD_Msk(1)   /*!< port 1 mode bits */
#define GPIO_CTL0_CTL1_Pos             GPIO_CTL0_CTL_Pos(1)
#define GPIO_CTL0_CTL1_Msk             GPIO_CTL0_CTL_Msk(1)  /*!< pin 1 configuration bits */
#define GPIO_CTL0_MD2_Pos              GPIO_CTL0_MD_Pos(2)
#define GPIO_CTL0_MD2_Msk              GPIO_CTL0_MD_Msk(2)   /*!< port 2 mode bits */
#define GPIO_CTL0_CTL2_Pos             GPIO_CTL0_CTL_Pos(2)
#define GPIO_CTL0_CTL2_Msk             GPIO_CTL0_CTL_Msk(2)  /*!< pin 2 configuration bits */
#define GPIO_CTL0_MD3_Pos              GPIO_CTL0_MD_Pos(3)
#define GPIO_CTL0_MD3_Msk              GPIO_CTL0_MD_Msk(3)   /*!< port 3 mode bits */
#define GPIO_CTL0_CTL3_Pos             GPIO_CTL0_CTL_Pos(3)
#define GPIO_CTL0_CTL3_Msk             GPIO_CTL0_CTL_Msk(3)  /*!< pin 3 configuration bits */
#define GPIO_CTL0_MD4_Pos              GPIO_CTL0_MD_Pos(4)
#define GPIO_CTL0_MD4_Msk              GPIO_CTL0_MD_Msk(4)   /*!< port 4 mode bits */
#define GPIO_CTL0_CTL4_Pos             GPIO_CTL0_CTL_Pos(4)
#define GPIO_CTL0_CTL4_Msk             GPIO_CTL0_CTL_Msk(4)  /*!< pin 4 configuration bits */
#define GPIO_CTL0_MD5_Pos              GPIO_CTL0_MD_Pos(5)
#define GPIO_CTL0_MD5_Msk              GPIO_CTL0_MD_Msk(5)   /*!< port 5 mode bits */
#define GPIO_CTL0_CTL5_Pos             GPIO_CTL0_CTL_Pos(5)
#define GPIO_CTL0_CTL5_Msk             GPIO_CTL0_CTL_Msk(5)  /*!< pin 5 configuration bits */
#define GPIO_CTL0_MD6_Pos              GPIO_CTL0_MD_Pos(6)
#define GPIO_CTL0_MD6_Msk              GPIO_CTL0_MD_Msk(6)   /*!< port 6 mode bits */
#define GPIO_CTL0_CTL6_Pos             GPIO_CTL0_CTL_Pos(6)
#define GPIO_CTL0_CTL6_Msk             GPIO_CTL0_CTL_Msk(6)  /*!< pin 6 configuration bits */
#define GPIO_CTL0_MD7_Pos              GPIO_CTL0_MD_Pos(7)
#define GPIO_CTL0_MD7_Msk              GPIO_CTL0_MD_Msk(7)   /*!< port 7 mode bits */
#define GPIO_CTL0_CTL7_Pos             GPIO_CTL0_CTL_Pos(7)
#define GPIO_CTL0_CTL7_Msk             GPIO_CTL0_CTL_Msk(7)  /*!< pin 7 configuration bits */

/* GPIO_CTL1 */
#define GPIO_CTL1_MD_Pos(x)            (2*((x) & 7))
#define GPIO_CTL1_MD_Msk(x)            (_AC(0x3,U) << GPIO_CTL0_MD_Pos(x))
#define GPIO_CTL1_CTL_Pos(x)           (2*((x) & 7) + 2)
#define GPIO_CTL1_CTL_Msk(x)           (_AC(0x3,U) << GPIO_CTL0_CTL_Pos(x))
#define GPIO_CTL1_MD8_Pos              GPIO_CTL1_MD_Pos(8)
#define GPIO_CTL1_MD8_Msk              GPIO_CTL1_MD_Msk(8)   /*!< port 8 mode bits */
#define GPIO_CTL1_CTL8_Pos             GPIO_CTL1_CTL_Pos(8)
#define GPIO_CTL1_CTL8_Msk             GPIO_CTL1_CTL_Msk(8)  /*!< pin 8 configuration bits */
#define GPIO_CTL1_MD9_Pos              GPIO_CTL1_MD_Pos(9)
#define GPIO_CTL1_MD9_Msk              GPIO_CTL1_MD_Msk(9)   /*!< port 9 mode bits */
#define GPIO_CTL1_CTL9_Pos             GPIO_CTL1_CTL_Pos(9)
#define GPIO_CTL1_CTL9_Msk             GPIO_CTL1_CTL_Msk(9)  /*!< pin 9 configuration bits */
#define GPIO_CTL1_MD10_Pos             GPIO_CTL1_MD_Pos(10)
#define GPIO_CTL1_MD10_Msk             GPIO_CTL1_MD_Msk(10)  /*!< port 10 mode bits */
#define GPIO_CTL1_CTL10_Pos            GPIO_CTL1_CTL_Pos(10)
#define GPIO_CTL1_CTL10_Msk            GPIO_CTL1_CTL_Msk(10) /*!< pin 10 configuration bits */
#define GPIO_CTL1_MD11_Pos             GPIO_CTL1_MD_Pos(11)
#define GPIO_CTL1_MD11_Msk             GPIO_CTL1_MD_Msk(11)  /*!< port 11 mode bits */
#define GPIO_CTL1_CTL11_Pos            GPIO_CTL1_CTL_Pos(11)
#define GPIO_CTL1_CTL11_Msk            GPIO_CTL1_CTL_Msk(11) /*!< pin 11 configuration bits */
#define GPIO_CTL1_MD12_Pos             GPIO_CTL1_MD_Pos(12)
#define GPIO_CTL1_MD12_Msk             GPIO_CTL1_MD_Msk(12)  /*!< port 12 mode bits */
#define GPIO_CTL1_CTL12_Pos            GPIO_CTL1_CTL_Pos(12)
#define GPIO_CTL1_CTL12_Msk            GPIO_CTL1_CTL_Msk(12) /*!< pin 12 configuration bits */
#define GPIO_CTL1_MD13_Pos             GPIO_CTL1_MD_Pos(13)
#define GPIO_CTL1_MD13_Msk             GPIO_CTL1_MD_Msk(13)  /*!< port 13 mode bits */
#define GPIO_CTL1_CTL13_Pos            GPIO_CTL1_CTL_Pos(13)
#define GPIO_CTL1_CTL13_Msk            GPIO_CTL1_CTL_Msk(13) /*!< pin 13 configuration bits */
#define GPIO_CTL1_MD14_Pos             GPIO_CTL1_MD_Pos(14)
#define GPIO_CTL1_MD14_Msk             GPIO_CTL1_MD_Msk(14)  /*!< port 14 mode bits */
#define GPIO_CTL1_CTL14_Pos            GPIO_CTL1_CTL_Pos(14)
#define GPIO_CTL1_CTL14_Msk            GPIO_CTL1_CTL_Msk(14) /*!< pin 14 configuration bits */
#define GPIO_CTL1_MD15_Pos             GPIO_CTL1_MD_Pos(15)
#define GPIO_CTL1_MD15_Msk             GPIO_CTL1_MD_Msk(15)  /*!< port 15 mode bits */
#define GPIO_CTL1_CTL15_Pos            GPIO_CTL1_CTL_Pos(15)
#define GPIO_CTL1_CTL15_Msk            GPIO_CTL1_CTL_Msk(15) /*!< pin 15 configuration bits */

/* GPIO_ISTAT */
#define GPIO_ISTAT_ISTAT0              _BIT(0,U)             /*!< pin 0 input status */
#define GPIO_ISTAT_ISTAT1              _BIT(1,U)             /*!< pin 1 input status */
#define GPIO_ISTAT_ISTAT2              _BIT(2,U)             /*!< pin 2 input status */
#define GPIO_ISTAT_ISTAT3              _BIT(3,U)             /*!< pin 3 input status */
#define GPIO_ISTAT_ISTAT4              _BIT(4,U)             /*!< pin 4 input status */
#define GPIO_ISTAT_ISTAT5              _BIT(5,U)             /*!< pin 5 input status */
#define GPIO_ISTAT_ISTAT6              _BIT(6,U)             /*!< pin 6 input status */
#define GPIO_ISTAT_ISTAT7              _BIT(7,U)             /*!< pin 7 input status */
#define GPIO_ISTAT_ISTAT8              _BIT(8,U)             /*!< pin 8 input status */
#define GPIO_ISTAT_ISTAT9              _BIT(9,U)             /*!< pin 9 input status */
#define GPIO_ISTAT_ISTAT10             _BIT(10,U)            /*!< pin 10 input status */
#define GPIO_ISTAT_ISTAT11             _BIT(11,U)            /*!< pin 11 input status */
#define GPIO_ISTAT_ISTAT12             _BIT(12,U)            /*!< pin 12 input status */
#define GPIO_ISTAT_ISTAT13             _BIT(13,U)            /*!< pin 13 input status */
#define GPIO_ISTAT_ISTAT14             _BIT(14,U)            /*!< pin 14 input status */
#define GPIO_ISTAT_ISTAT15             _BIT(15,U)            /*!< pin 15 input status */

/* GPIO_OCTL */
#define GPIO_OCTL_OCTL0                _BIT(0,U)             /*!< pin 0 output bit */
#define GPIO_OCTL_OCTL1                _BIT(1,U)             /*!< pin 1 output bit */
#define GPIO_OCTL_OCTL2                _BIT(2,U)             /*!< pin 2 output bit */
#define GPIO_OCTL_OCTL3                _BIT(3,U)             /*!< pin 3 output bit */
#define GPIO_OCTL_OCTL4                _BIT(4,U)             /*!< pin 4 output bit */
#define GPIO_OCTL_OCTL5                _BIT(5,U)             /*!< pin 5 output bit */
#define GPIO_OCTL_OCTL6                _BIT(6,U)             /*!< pin 6 output bit */
#define GPIO_OCTL_OCTL7                _BIT(7,U)             /*!< pin 7 output bit */
#define GPIO_OCTL_OCTL8                _BIT(8,U)             /*!< pin 8 output bit */
#define GPIO_OCTL_OCTL9                _BIT(9,U)             /*!< pin 9 output bit */
#define GPIO_OCTL_OCTL10               _BIT(10,U)            /*!< pin 10 output bit */
#define GPIO_OCTL_OCTL11               _BIT(11,U)            /*!< pin 11 output bit */
#define GPIO_OCTL_OCTL12               _BIT(12,U)            /*!< pin 12 output bit */
#define GPIO_OCTL_OCTL13               _BIT(13,U)            /*!< pin 13 output bit */
#define GPIO_OCTL_OCTL14               _BIT(14,U)            /*!< pin 14 output bit */
#define GPIO_OCTL_OCTL15               _BIT(15,U)            /*!< pin 15 output bit */

/* GPIO_BOP */
#define GPIO_BOP_BOP0                  _BIT(0,U)             /*!< pin 0 set bit */
#define GPIO_BOP_BOP1                  _BIT(1,U)             /*!< pin 1 set bit */
#define GPIO_BOP_BOP2                  _BIT(2,U)             /*!< pin 2 set bit */
#define GPIO_BOP_BOP3                  _BIT(3,U)             /*!< pin 3 set bit */
#define GPIO_BOP_BOP4                  _BIT(4,U)             /*!< pin 4 set bit */
#define GPIO_BOP_BOP5                  _BIT(5,U)             /*!< pin 5 set bit */
#define GPIO_BOP_BOP6                  _BIT(6,U)             /*!< pin 6 set bit */
#define GPIO_BOP_BOP7                  _BIT(7,U)             /*!< pin 7 set bit */
#define GPIO_BOP_BOP8                  _BIT(8,U)             /*!< pin 8 set bit */
#define GPIO_BOP_BOP9                  _BIT(9,U)             /*!< pin 9 set bit */
#define GPIO_BOP_BOP10                 _BIT(10,U)            /*!< pin 10 set bit */
#define GPIO_BOP_BOP11                 _BIT(11,U)            /*!< pin 11 set bit */
#define GPIO_BOP_BOP12                 _BIT(12,U)            /*!< pin 12 set bit */
#define GPIO_BOP_BOP13                 _BIT(13,U)            /*!< pin 13 set bit */
#define GPIO_BOP_BOP14                 _BIT(14,U)            /*!< pin 14 set bit */
#define GPIO_BOP_BOP15                 _BIT(15,U)            /*!< pin 15 set bit */
#define GPIO_BOP_CR0                   _BIT(16,U)            /*!< pin 0 clear bit */
#define GPIO_BOP_CR1                   _BIT(17,U)            /*!< pin 1 clear bit */
#define GPIO_BOP_CR2                   _BIT(18,U)            /*!< pin 2 clear bit */
#define GPIO_BOP_CR3                   _BIT(19,U)            /*!< pin 3 clear bit */
#define GPIO_BOP_CR4                   _BIT(20,U)            /*!< pin 4 clear bit */
#define GPIO_BOP_CR5                   _BIT(21,U)            /*!< pin 5 clear bit */
#define GPIO_BOP_CR6                   _BIT(22,U)            /*!< pin 6 clear bit */
#define GPIO_BOP_CR7                   _BIT(23,U)            /*!< pin 7 clear bit */
#define GPIO_BOP_CR8                   _BIT(24,U)            /*!< pin 8 clear bit */
#define GPIO_BOP_CR9                   _BIT(25,U)            /*!< pin 9 clear bit */
#define GPIO_BOP_CR10                  _BIT(26,U)            /*!< pin 10 clear bit */
#define GPIO_BOP_CR11                  _BIT(27,U)            /*!< pin 11 clear bit */
#define GPIO_BOP_CR12                  _BIT(28,U)            /*!< pin 12 clear bit */
#define GPIO_BOP_CR13                  _BIT(29,U)            /*!< pin 13 clear bit */
#define GPIO_BOP_CR14                  _BIT(30,U)            /*!< pin 14 clear bit */
#define GPIO_BOP_CR15                  _BIT(31,U)            /*!< pin 15 clear bit */

/* GPIO_BC */
#define GPIO_BC_CR0                    _BIT(0,U)             /*!< pin 0 clear bit */
#define GPIO_BC_CR1                    _BIT(1,U)             /*!< pin 1 clear bit */
#define GPIO_BC_CR2                    _BIT(2,U)             /*!< pin 2 clear bit */
#define GPIO_BC_CR3                    _BIT(3,U)             /*!< pin 3 clear bit */
#define GPIO_BC_CR4                    _BIT(4,U)             /*!< pin 4 clear bit */
#define GPIO_BC_CR5                    _BIT(5,U)             /*!< pin 5 clear bit */
#define GPIO_BC_CR6                    _BIT(6,U)             /*!< pin 6 clear bit */
#define GPIO_BC_CR7                    _BIT(7,U)             /*!< pin 7 clear bit */
#define GPIO_BC_CR8                    _BIT(8,U)             /*!< pin 8 clear bit */
#define GPIO_BC_CR9                    _BIT(9,U)             /*!< pin 9 clear bit */
#define GPIO_BC_CR10                   _BIT(10,U)            /*!< pin 10 clear bit */
#define GPIO_BC_CR11                   _BIT(11,U)            /*!< pin 11 clear bit */
#define GPIO_BC_CR12                   _BIT(12,U)            /*!< pin 12 clear bit */
#define GPIO_BC_CR13                   _BIT(13,U)            /*!< pin 13 clear bit */
#define GPIO_BC_CR14                   _BIT(14,U)            /*!< pin 14 clear bit */
#define GPIO_BC_CR15                   _BIT(15,U)            /*!< pin 15 clear bit */

/* GPIO_LOCK */
#define GPIO_LOCK_LK0                  _BIT(0,U)             /*!< pin 0 lock bit */
#define GPIO_LOCK_LK1                  _BIT(1,U)             /*!< pin 1 lock bit */
#define GPIO_LOCK_LK2                  _BIT(2,U)             /*!< pin 2 lock bit */
#define GPIO_LOCK_LK3                  _BIT(3,U)             /*!< pin 3 lock bit */
#define GPIO_LOCK_LK4                  _BIT(4,U)             /*!< pin 4 lock bit */
#define GPIO_LOCK_LK5                  _BIT(5,U)             /*!< pin 5 lock bit */
#define GPIO_LOCK_LK6                  _BIT(6,U)             /*!< pin 6 lock bit */
#define GPIO_LOCK_LK7                  _BIT(7,U)             /*!< pin 7 lock bit */
#define GPIO_LOCK_LK8                  _BIT(8,U)             /*!< pin 8 lock bit */
#define GPIO_LOCK_LK9                  _BIT(9,U)             /*!< pin 9 lock bit */
#define GPIO_LOCK_LK10                 _BIT(10,U)            /*!< pin 10 lock bit */
#define GPIO_LOCK_LK11                 _BIT(11,U)            /*!< pin 11 lock bit */
#define GPIO_LOCK_LK12                 _BIT(12,U)            /*!< pin 12 lock bit */
#define GPIO_LOCK_LK13                 _BIT(13,U)            /*!< pin 13 lock bit */
#define GPIO_LOCK_LK14                 _BIT(14,U)            /*!< pin 14 lock bit */
#define GPIO_LOCK_LK15                 _BIT(15,U)            /*!< pin 15 lock bit */
#define GPIO_LOCK_LKK                  _BIT(16,U)            /*!< pin sequence lock key */

/* AFIO_EC */
#define AFIO_EC_EOE                    _BIT(7,U)             /*!< event output enable */
#define AFIO_EC_PORT_Pos               4
#define AFIO_EC_PORT_Msk               _AC(0x00000070,U)     /*!< event output port selection */
#define AFIO_EC_PORT(x)                ((x) << AFIO_EC_PORT_Pos)
#define AFIO_EC_PORT_A                 AFIO_EC_PORT(0)
#define AFIO_EC_PORT_B                 AFIO_EC_PORT(1)
#define AFIO_EC_PORT_C                 AFIO_EC_PORT(2)
#define AFIO_EC_PORT_D                 AFIO_EC_PORT(3)
#define AFIO_EC_PORT_E                 AFIO_EC_PORT(4)
#define AFIO_EC_PIN_Pos                0
#define AFIO_EC_PIN_Msk                _AC(0x0000000f,U)     /*!< event output pin selection */
#define AFIO_EC_PIN(x)                 ((x) << AFIO_EC_PIN_Pos)

/* AFIO_PCF0 */
#define AFIO_PCF0_TIMER1_ITI1_REMAP    _BIT(29,U)            /*!< TIMER1 internal trigger 1 remapping */
#define AFIO_PCF0_SPI2_REMAP           _BIT(28,U)            /*!< SPI2/I2S2 remapping */
#define AFIO_PCF0_SWJ_CFG_Pos          24
#define AFIO_PCF0_SWJ_CFG_Msk          _AC(0x07000000,U)     /*!< serial wire JTAG configuration */
#define AFIO_PCF0_SWJ_CFG(x)           ((x) << AFIO_PCF0_SWJ_CFG_Pos)
#define AFIO_PCF0_SWJ_CFG_RESET        AFIO_PCF0_SWJ_CFG(0)
#define AFIO_PCF0_SWJ_CFG_NORST        AFIO_PCF0_SWJ_CFG(1)
#define AFIO_PCF0_SWJ_CFG_DISABLED     AFIO_PCF0_SWJ_CFG(2)
#define AFIO_PCF0_CAN1_REMAP           _BIT(22,U)            /*!< CAN1 remapping */
#define AFIO_PCF0_TIMER4CH3_IREMAP     _BIT(16,U)            /*!< TIMER3 channel3 internal remapping */
#define AFIO_PCF0_PD01_REMAP           _BIT(15,U)            /*!< port D0/port D1 mapping on OSC_IN/OSC_OUT */
#define AFIO_PCF0_CAN0_REMAP_Pos       13
#define AFIO_PCF0_CAN0_REMAP_Msk       _AC(0x00006000,U)     /*!< CAN remapping */
#define AFIO_PCF0_CAN0_REMAP(x)        ((x) << AFIO_PCF0_CAN_REMAP_Pos)
#define AFIO_PCF0_CAN0_REMAP_NONE      AFIO_PCF0_CAN0_REMAP(0)
#define AFIO_PCF0_CAN0_REMAP_PARTIAL   AFIO_PCF0_CAN0_REMAP(2)
#define AFIO_PCF0_CAN0_REMAP_FULL      AFIO_PCF0_CAN0_REMAP(3)
#define AFIO_PCF0_TIMER3_REMAP         _BIT(12,U)            /*!< TIMER3 remapping */
#define AFIO_PCF0_TIMER2_REMAP_Pos     10
#define AFIO_PCF0_TIMER2_REMAP_Msk     _AC(0x00000c00,U)     /*!< TIMER2 remapping */
#define AFIO_PCF0_TIMER2_REMAP(x)      ((x) << AFIO_PCF0_TIMER2_REMAP_Pos)
#define AFIO_PCF0_TIMER2_REMAP_NONE    AFIO_PCF0_TIMER2_REMAP(0)
#define AFIO_PCF0_TIMER2_REMAP_PARTIAL AFIO_PCF0_TIMER2_REMAP(2)
#define AFIO_PCF0_TIMER2_REMAP_FULL    AFIO_PCF0_TIMER2_REMAP(3)
#define AFIO_PCF0_TIMER1_REMAP_Pos     8
#define AFIO_PCF0_TIMER1_REMAP_Msk     _AC(0x00000300,U)     /*!< TIMER1 remapping */
#define AFIO_PCF0_TIMER1_REMAP(x)      ((x) << AFIO_PCF0_TIMER2_REMAP_Pos)
#define AFIO_PCF0_TIMER1_REMAP_NONE    AFIO_PCF0_TIMER1_REMAP(0)
#define AFIO_PCF0_TIMER1_REMAP_PARTIAL0 AFIO_PCF0_TIMER1_REMAP(1)
#define AFIO_PCF0_TIMER1_REMAP_PARTIAL1 AFIO_PCF0_TIMER1_REMAP(2)
#define AFIO_PCF0_TIMER1_REMAP_FULL    AFIO_PCF0_TIMER1_REMAP(3)
#define AFIO_PCF0_TIMER0_REMAP_Pos     6
#define AFIO_PCF0_TIMER0_REMAP_Msk     _AC(0x000000c0,U)     /*!< TIMER0 remapping */
#define AFIO_PCF0_TIMER0_REMAP(x)      ((x) << AFIO_PCF0_TIMER0_REMAP_Pos)
#define AFIO_PCF0_TIMER0_REMAP_NONE    AFIO_PCF0_TIMER0_REMAP(0)
#define AFIO_PCF0_TIMER0_REMAP_PARTIAL AFIO_PCF0_TIMER0_REMAP(1)
#define AFIO_PCF0_TIMER0_REMAP_FULL    AFIO_PCF0_TIMER0_REMAP(3)
#define AFIO_PCF0_USART2_REMAP_Pos     4
#define AFIO_PCF0_USART2_REMAP_Msk     _AC(0x00000030,U)     /*!< USART2 remapping */
#define AFIO_PCF0_USART2_REMAP(x)      ((x) << AFIO_PCF0_USART2_REMAP_Pos)
#define AFIO_PCF0_USART2_REMAP_NONE    AFIO_PCF0_USART2_REMAP(0)
#define AFIO_PCF0_USART2_REMAP_PARTIAL AFIO_PCF0_USART2_REMAP(1)
#define AFIO_PCF0_USART2_REMAP_FULL    AFIO_PCF0_USART2_REMAP(3)
#define AFIO_PCF0_USART1_REMAP         _BIT(3,U)             /*!< USART1 remapping */
#define AFIO_PCF0_USART0_REMAP         _BIT(2,U)             /*!< USART0 remapping */
#define AFIO_PCF0_I2C0_REMAP           _BIT(1,U)             /*!< I2C0 remapping */
#define AFIO_PCF0_SPI0_REMAP           _BIT(0,U)             /*!< SPI0 remapping */

/* AFIO_EXTISS0 */
#define AFIO_EXTI_SS_Pos(x)            (4*((x) & 3))
#define AFIO_EXTI_SS_Msk(x)            (_AC(0xf,U) << GPIO_CTL0_MD_Pos(x))
#define AFIO_EXTI0_SS_Pos              AFIO_EXTI_SS_Pos(0)
#define AFIO_EXTI0_SS_Msk              AFIO_EXTI_SS_Msk(0)   /*!< EXTI 0 sources selection */
#define AFIO_EXTI1_SS_Pos              AFIO_EXTI_SS_Pos(1)
#define AFIO_EXTI1_SS_Msk              AFIO_EXTI_SS_Msk(1)   /*!< EXTI 1 sources selection */
#define AFIO_EXTI2_SS_Pos              AFIO_EXTI_SS_Pos(2)
#define AFIO_EXTI2_SS_Msk              AFIO_EXTI_SS_Msk(2)   /*!< EXTI 2 sources selection */
#define AFIO_EXTI3_SS_Pos              AFIO_EXTI_SS_Pos(3)
#define AFIO_EXTI3_SS_Msk              AFIO_EXTI_SS_Msk(3)   /*!< EXTI 3 sources selection */

/* AFIO_EXTISS1 */
#define AFIO_EXTI4_SS_Pos              AFIO_EXTI_SS_Pos(4)
#define AFIO_EXTI4_SS_Msk              AFIO_EXTI_SS_Msk(4)   /*!< EXTI 4 sources selection */
#define AFIO_EXTI5_SS_Pos              AFIO_EXTI_SS_Pos(5)
#define AFIO_EXTI5_SS_Msk              AFIO_EXTI_SS_Msk(5)   /*!< EXTI 5 sources selection */
#define AFIO_EXTI6_SS_Pos              AFIO_EXTI_SS_Pos(6)
#define AFIO_EXTI6_SS_Msk              AFIO_EXTI_SS_Msk(6)   /*!< EXTI 6 sources selection */
#define AFIO_EXTI7_SS_Pos              AFIO_EXTI_SS_Pos(7)
#define AFIO_EXTI7_SS_Msk              AFIO_EXTI_SS_Msk(7)   /*!< EXTI 7 sources selection */

/* AFIO_EXTISS2 */
#define AFIO_EXTI8_SS_Pos              AFIO_EXTI_SS_Pos(8)
#define AFIO_EXTI8_SS_Msk              AFIO_EXTI_SS_Msk(8)   /*!< EXTI 8 sources selection */
#define AFIO_EXTI9_SS_Pos              AFIO_EXTI_SS_Pos(9)
#define AFIO_EXTI9_SS_Msk              AFIO_EXTI_SS_Msk(9)   /*!< EXTI 9 sources selection */
#define AFIO_EXTI10_SS_Pos             AFIO_EXTI_SS_Pos(10)
#define AFIO_EXTI10_SS_Msk             AFIO_EXTI_SS_Msk(10)  /*!< EXTI 10 sources selection */
#define AFIO_EXTI11_SS_Pos             AFIO_EXTI_SS_Pos(11)
#define AFIO_EXTI11_SS_Msk             AFIO_EXTI_SS_Msk(11)  /*!< EXTI 11 sources selection */

/* AFIO_EXTISS3 */
#define AFIO_EXTI12_SS_Pos             AFIO_EXTI_SS_Pos(12)
#define AFIO_EXTI12_SS_Msk             AFIO_EXTI_SS_Msk(12)  /*!< EXTI 12 sources selection */
#define AFIO_EXTI13_SS_Pos             AFIO_EXTI_SS_Pos(13)
#define AFIO_EXTI13_SS_Msk             AFIO_EXTI_SS_Msk(13)  /*!< EXTI 13 sources selection */
#define AFIO_EXTI14_SS_Pos             AFIO_EXTI_SS_Pos(14)
#define AFIO_EXTI14_SS_Msk             AFIO_EXTI_SS_Msk(14)  /*!< EXTI 14 sources selection */
#define AFIO_EXTI15_SS_Pos             AFIO_EXTI_SS_Pos(15)
#define AFIO_EXTI15_SS_Msk             AFIO_EXTI_SS_Msk(15)  /*!< EXTI 15 sources selection */

/* AFIO_PCF1 */
#define AFIO_PCF1_EXMC_NADV            _BIT(10,U)            /*!< EXMC_NADV connect/disconnect */

/* --------------------- I2C -------------------------- */

#define I2C0_BASE                      _AC(0x40005400,UL)  /*!< I2C0 base address */
#if defined(GD32VF103C8T6) || defined(GD32VF103CBT6) || defined(GD32VF103R8T6) || \
    defined(GD32VF103RBT6) || defined(GD32VF103V8T6) || defined(GD32VF103VBT6)
    #define I2C1_BASE                  _AC(0x40005800,UL)  /*!< I2C1 base address */
#endif

/* register definitions */
#define I2C_CTL0                       _AC(0x00,UL)  /*!< I2C control register 0 */
#define I2C_CTL1                       _AC(0x04,UL)  /*!< I2C control register 1 */
#define I2C_SADDR0                     _AC(0x08,UL)  /*!< I2C slave address register 0*/
#define I2C_SADDR1                     _AC(0x0C,UL)  /*!< I2C slave address register */
#define I2C_DATA                       _AC(0x10,UL)  /*!< I2C transfer buffer register */
#define I2C_STAT0                      _AC(0x14,UL)  /*!< I2C transfer status register 0 */
#define I2C_STAT1                      _AC(0x18,UL)  /*!< I2C transfer status register */
#define I2C_CKCFG                      _AC(0x1C,UL)  /*!< I2C clock configure register */
#define I2C_RT                         _AC(0x20,UL)  /*!< I2C rise time register */

/* I2C_CTL0 */
#define I2C_CTL0_SRESET                _BIT(15,U)         /*!< software reset */
#define I2C_CTL0_SALT                  _BIT(13,U)         /*!< SMBus alert */
#define I2C_CTL0_PECTRANS              _BIT(12,U)         /*!< packet error checking */
#define I2C_CTL0_POAP                  _BIT(11,U)         /*!< acknowledge/PEC position (for data reception) */
#define I2C_CTL0_ACKEN                 _BIT(10,U)         /*!< acknowledge enable */
#define I2C_CTL0_STOP                  _BIT(9,U)          /*!< stop generation */
#define I2C_CTL0_START                 _BIT(8,U)          /*!< start generation */
#define I2C_CTL0_SS                    _BIT(7,U)          /*!< clock stretching disable (slave mode) */
#define I2C_CTL0_GCEN                  _BIT(6,U)          /*!< general call enable */
#define I2C_CTL0_PECEN                 _BIT(5,U)          /*!< PEC enable */
#define I2C_CTL0_ARPEN                 _BIT(4,U)          /*!< ARP enable */
#define I2C_CTL0_SMBSEL                _BIT(3,U)          /*!< SMBus type */
#define I2C_CTL0_SMBEN                 _BIT(1,U)          /*!< SMBus mode */
#define I2C_CTL0_I2CEN                 _BIT(0,U)          /*!< peripheral enable */

/* I2C_CTL1 */
#define I2C_CTL1_DMALST                _BIT(12,U)         /*!< DMA last transfer */
#define I2C_CTL1_DMAON                 _BIT(11,U)         /*!< DMA requests enable */
#define I2C_CTL1_BUFIE                 _BIT(10,U)         /*!< buffer interrupt enable */
#define I2C_CTL1_EVIE                  _BIT(9,U)          /*!< event interrupt enable */
#define I2C_CTL1_ERRIE                 _BIT(8,U)          /*!< error interrupt enable */
#define I2C_CTL1_I2CCLK_Pos            0
#define I2C_CTL1_I2CCLK_Msk            _AC(0x0000003f,U)  /*!< I2CCLK[5:0] bits (peripheral clock frequency) */
#define I2C_CTL1_I2CCLK(x)             ((x) << I2C_CTL1_I2CCLK_Pos)

/* I2C_SADDR0 */
#define I2C_SADDR0_ADDFORMAT           _BIT(15,U)         /*!< address mode for the I2C slave */
#define I2C_SADDR0_ADDRESS_10B_Pos     0
#define I2C_SADDR0_ADDRESS_10B_Msk     _AC(0x000003ff,U)  /*!< 10-bit address */
#define I2C_SADDR0_ADDRESS_10B(x)      ((x) << I2C_SADDR0_ADDRESS_Pos)
#define I2C_SADDR0_ADDRESS_Pos         1
#define I2C_SADDR0_ADDRESS_Msk         _AC(0x000000fe,U)  /*!< 7-bit address */
#define I2C_SADDR0_ADDRESS(x)          ((x) << I2C_SADDR0_ADDRESS_Pos)

/* I2C_SADDR1 */
#define I2C_SADDR1_ADDRESS2_Pos        1
#define I2C_SADDR1_ADDRESS2_Msk        _AC(0x000000fe,U)  /*!< second I2C address for the slave in dual-address mode */
#define I2C_SADDR1_ADDRESS2(x)         ((x) << I2C_SADDR1_ADDRESS2_Pos)
#define I2C_SADDR1_DUADEN              _BIT(0,U)          /*!< aual-address mode switch */

/* I2C_DATA */
#define I2C_DATA_TRB_Pos               0
#define I2C_DATA_TRB_Msk               _AC(0x000000ff,U)  /*!< 8-bit data register */
#define I2C_DATA_TRB(x)                ((x) << I2C_DATA_TRB_Pos)

/* I2C_STAT0 */
#define I2C_STAT0_SMBALT               _BIT(15,U)         /*!< SMBus alert status */
#define I2C_STAT0_SMBTO                _BIT(14,U)         /*!< timeout signal in SMBus mode */
#define I2C_STAT0_PECERR               _BIT(12,U)         /*!< PEC error in reception */
#define I2C_STAT0_OUERR                _BIT(11,U)         /*!< overrun/underrun */
#define I2C_STAT0_AERR                 _BIT(10,U)         /*!< acknowledge failure */
#define I2C_STAT0_LOSTARB              _BIT(9,U)          /*!< arbitration lost (master mode) */
#define I2C_STAT0_BERR                 _BIT(8,U)          /*!< bus error */
#define I2C_STAT0_TBE                  _BIT(7,U)          /*!< data register empty (transmitters) */
#define I2C_STAT0_RBNE                 _BIT(6,U)          /*!< data register not empty (receivers) */
#define I2C_STAT0_STPDET               _BIT(4,U)          /*!< stop detection (slave mode) */
#define I2C_STAT0_ADD10SEND            _BIT(3,U)          /*!< 10-bit header sent (master mode) */
#define I2C_STAT0_BTC                  _BIT(2,U)          /*!< byte transfer finished */
#define I2C_STAT0_ADDSEND              _BIT(1,U)          /*!< address sent (master mode)/matched (slave mode) */
#define I2C_STAT0_SBSEND               _BIT(0,U)          /*!< start bit (master mode) */

/* I2C_STAT1 */
#define I2C_STAT1_PECV_Pos             8
#define I2C_STAT1_PECV_Msk             _AC(0x0000ff00,U)  /*!< packet error checking value */
#define I2C_STAT1_PECV(x)              ((x) << I2C_STAT1_PECV_Pos)
#define I2C_STAT1_DUMODF               _BIT(7,U)          /*!< dual flag (slave mode) */
#define I2C_STAT1_HSTSMB               _BIT(6,U)          /*!< SMBus host header (slave mode) */
#define I2C_STAT1_DEFSMB               _BIT(5,U)          /*!< SMBus device default address (slave mode) */
#define I2C_STAT1_RXGC                 _BIT(4,U)          /*!< general call address (slave mode) */
#define I2C_STAT1_TR                   _BIT(2,U)          /*!< transmitter/receiver */
#define I2C_STAT1_I2CBSY               _BIT(1,U)          /*!< bus busy */
#define I2C_STAT1_MASTER               _BIT(0,U)          /*!< master/slave */

/* I2C_CKCFG */
#define I2C_CKCFG_FAST                 _BIT(15,U)         /*!< I2C speed selection in master mode */
#define I2C_CKCFG_DTCY                 _BIT(14,U)         /*!< fast mode duty cycle */
#define I2C_CKCFG_CLKC_Pos             0
#define I2C_CKCFG_CLKC_Msk             _AC(0x00000fff,U)  /*!< clock control register in fast/standard mode (master mode) */
#define I2C_CKCFG_CLKC(x)              ((x) << I2C_CKCFG_CLKC_Pos)

/* I2C_RT */
#define I2C_RT_RISETIME_Pos            0
#define I2C_RT_RISETIME_Msk            _AC(0x0000003f,U)  /*!< maximum rise time in fast/standard mode (Master mode) */
#define I2C_RT_RISETIME(x)             ((x) << I2C_RT_RISETIME_Pos)

/* --------------------- INFO -------------------------- */

#define INFO_BASE                      _AC(0x1FFFF7E0,UL)  /*!< flash size, sram size and id */

/* register definitions */
#define INFO_FLASH                     _AC(0x00,UL)  /*!< flash size in kilobytes */
#define INFO_SRAM                      _AC(0x02,UL)  /*!< sram size in kilobytes  */
#define INFO_ID0                       _AC(0x08,UL)  /*!< UNIQUE_ID bits 31:0     */
#define INFO_ID1                       _AC(0x0c,UL)  /*!< UNIQUE_ID bits 63:32    */
#define INFO_ID2                       _AC(0x10,UL)  /*!< UNIQUE_ID bits 95:64    */

/* --------------------- MTIMER -------------------------- */

/* in the gd32vf103 the mtime timer increments at coreclk/4 */
#ifdef CORECLOCK
    #define MTIMER_FREQ                (FOSC_KHZ_VALUE * 1000/4)
#endif

#define MTIMER_BASE                    _AC(0xD1000000,UL)  /*!< MTIMER base address */

/* register definitions */
#define MTIMER_MTIME                   _AC(0x000,UL)
#define MTIMER_MTIME_LO                _AC(0x000,UL)
#define MTIMER_MTIME_HI                _AC(0x004,UL)
#define MTIMER_MTIMECMP                _AC(0x008,UL)
#define MTIMER_MTIMECMP_LO             _AC(0x008,UL)
#define MTIMER_MTIMECMP_HO             _AC(0x00c,UL)
#define MTIMER_MSTOP                   _AC(0xff8,UL)
#define MTIMER_MSIP                    _AC(0xffc,UL)

/* mstop bits */
#define MTIMER_MSTOP_TIMESTOP          _BIT(0,U)

/* msip bits */
#define MTIMER_MSIP_MSIP               _BIT(0,U)

/* --------------------- PMU -------------------------- */

#define PMU_BASE                       _AC(0x40007000,UL)  /*!< PMU base address */

/* register definitions */
#define PMU_CTL                        _AC(0x00,UL)  /*!< PMU control register */
#define PMU_CS                         _AC(0x04,UL)  /*!< PMU control and status register */

/* PMU_CTL */
#define PMU_CTL_BKPWEN                 _BIT(8,U)          /*!< backup domain write enable */
#define PMU_CTL_LVDT_Pos               5
#define PMU_CTL_LVDT_Msk               _AC(0x000000e0,U)  /*!< low voltage detector threshold */
#define PMU_CTL_LVDT(x)                ((x) << PMU_CTL_LVDT_Pos)
#define PMU_CTL_LVDT_2_2V              PMU_CTL_LVDT(0)    /*!< voltage threshold is 2.2V */
#define PMU_CTL_LVDT_2_3V              PMU_CTL_LVDT(1)    /*!< voltage threshold is 2.3V */
#define PMU_CTL_LVDT_2_4V              PMU_CTL_LVDT(2)    /*!< voltage threshold is 2.4V */
#define PMU_CTL_LVDT_2_5V              PMU_CTL_LVDT(3)    /*!< voltage threshold is 2.5V */
#define PMU_CTL_LVDT_2_6V              PMU_CTL_LVDT(4)    /*!< voltage threshold is 2.6V */
#define PMU_CTL_LVDT_2_7V              PMU_CTL_LVDT(5)    /*!< voltage threshold is 2.7V */
#define PMU_CTL_LVDT_2_8V              PMU_CTL_LVDT(6)    /*!< voltage threshold is 2.8V */
#define PMU_CTL_LVDT_2_9V              PMU_CTL_LVDT(7)    /*!< voltage threshold is 2.9V */
#define PMU_CTL_LVDEN                  _BIT(4,U)          /*!< low voltage detector enable */
#define PMU_CTL_STBRST                 _BIT(3,U)          /*!< standby flag reset */
#define PMU_CTL_WURST                  _BIT(2,U)          /*!< wakeup flag reset */
#define PMU_CTL_STBMOD                 _BIT(1,U)          /*!< standby mode */
#define PMU_CTL_LDOLP                  _BIT(0,U)          /*!< LDO low power mode */

/* PMU_CS */
#define PMU_CS_WUPEN                   _BIT(8,U)          /*!< wakeup pin enable */
#define PMU_CS_LVDF                    _BIT(2,U)          /*!< low voltage detector status flag */
#define PMU_CS_STBF                    _BIT(1,U)          /*!< standby flag */
#define PMU_CS_WUF                     _BIT(0,U)          /*!< wakeup flag */

/* --------------------- RCU -------------------------- */

#define RCU_BASE                       _AC(0x40021000,UL)  /*!< RCU base address */

/* register definitions */
#define RCU_CTL                        _AC(0x00,UL) /*!< control register */
#define RCU_CFG0                       _AC(0x04,UL) /*!< clock configuration register 0 */
#define RCU_INT                        _AC(0x08,UL) /*!< clock interrupt register */
#define RCU_APB2RST                    _AC(0x0C,UL) /*!< APB2 reset register */
#define RCU_APB1RST                    _AC(0x10,UL) /*!< APB1 reset register */
#define RCU_AHBEN                      _AC(0x14,UL) /*!< AHB1 enable register */
#define RCU_APB2EN                     _AC(0x18,UL) /*!< APB2 enable register */
#define RCU_APB1EN                     _AC(0x1C,UL) /*!< APB1 enable register */
#define RCU_BDCTL                      _AC(0x20,UL) /*!< backup domain control register */
#define RCU_RSTSCK                     _AC(0x24,UL) /*!< reset source / clock register */
#define RCU_AHBRST                     _AC(0x28,UL) /*!< AHB reset register */
#define RCU_CFG1                       _AC(0x2C,UL) /*!< clock configuration register 1 */
#define RCU_DSV                        _AC(0x34,UL) /*!< deep-sleep mode voltage register */

/* RCU_CTL */
#define RCU_CTL_PLL2STB                _BIT(29,U)              /*!< PLL2 clock stabilization flag */
#define RCU_CTL_PLL2EN                 _BIT(28,U)              /*!< PLL2 enable */
#define RCU_CTL_PLL1STB                _BIT(27,U)              /*!< PLL1 clock stabilization flag */
#define RCU_CTL_PLL1EN                 _BIT(26,U)              /*!< PLL1 enable */
#define RCU_CTL_PLLSTB                 _BIT(25,U)              /*!< PLL clock stabilization flag */
#define RCU_CTL_PLLEN                  _BIT(24,U)              /*!< PLL enable */
#define RCU_CTL_CKMEN                  _BIT(19,U)              /*!< HXTAL clock monitor enable */
#define RCU_CTL_HXTALBPS               _BIT(18,U)              /*!< external crystal oscillator clock bypass mode enable */
#define RCU_CTL_HXTALSTB               _BIT(17,U)              /*!< external crystal oscillator clock stabilization flag */
#define RCU_CTL_HXTALEN                _BIT(16,U)              /*!< external high speed oscillator enable */
#define RCU_CTL_IRC8MCALIB_Pos         8
#define RCU_CTL_IRC8MCALIB_Msk         _AC(0x0000ff00,U)       /*!< high speed internal oscillator calibration value register */
#define RCU_CTL_IRC8MCALIB(x)          ((x) << RCU_CTL_IRC8MCALIB_Pos)
#define RCU_CTL_IRC8MADJ_Pos           3
#define RCU_CTL_IRC8MADJ_Msk           _AC(0x000000f80,U)      /*!< high speed internal oscillator clock trim adjust value */
#define RCU_CTL_IRC8MADJ(x)            ((x) << RCU_CTL_IRC8MADJ_Pos)
#define RCU_CTL_IRC8MSTB               _BIT(1,U)               /*!< IRC8M high speed internal oscillator stabilization flag */
#define RCU_CTL_IRC8MEN                _BIT(0,U)               /*!< internal high speed oscillator enable */

/* RCU_CFG0 */
#define RCU_CFG0_PLLMF_4_Pos           29
#define RCU_CFG0_PLLMF_4               _BIT(29,U)              /*!< bit 4 of PLLMF */
#define RCU_CFG0_ADCPSC_2_Pos          28
#define RCU_CFG0_ADCPSC_2              _BIT(28,U)              /*!< bit 2 of ADCPSC */
#define RCU_CFG0_CKOUT0SEL_Pos         24
#define RCU_CFG0_CKOUT0SEL_Msk         _AC(0x0f000000,U)       /*!< CKOUT0 clock source selection */
#define RCU_CFG0_CKOUT0SEL(x)          ((x) << RCU_CFG0_CKOUT0SEL_Pos)
#define RCU_CFG0_CKOUT0SEL_NONE        RCU_CFG0_CKOUT0SEL(0)   /*!< no clock selected */
#define RCU_CFG0_CKOUT0SEL_CKSYS       RCU_CFG0_CKOUT0SEL(4)   /*!< system clock selected */
#define RCU_CFG0_CKOUT0SEL_IRC8M       RCU_CFG0_CKOUT0SEL(5)   /*!< internal 8M RC oscillator clock selected */
#define RCU_CFG0_CKOUT0SEL_HXTAL       RCU_CFG0_CKOUT0SEL(6)   /*!< high speed crystal oscillator clock (HXTAL) selected */
#define RCU_CFG0_CKOUT0SEL_CKPLL_DIV2  RCU_CFG0_CKOUT0SEL(7)   /*!< CK_PLL/2 clock selected */
#define RCU_CFG0_CKOUT0SEL_CKPLL1      RCU_CFG0_CKOUT0SEL(8)   /*!< CK_PLL1 clock selected */
#define RCU_CFG0_CKOUT0SEL_CKPLL2_DIV2 RCU_CFG0_CKOUT0SEL(9)   /*!< CK_PLL2/2 clock selected */
#define RCU_CFG0_CKOUT0SEL_EXT1        RCU_CFG0_CKOUT0SEL(10)  /*!< EXT1 selected */
#define RCU_CFG0_CKOUT0SEL_CKPLL2      RCU_CFG0_CKOUT0SEL(11)  /*!< CK_PLL2 clock selected */
#define RCU_CFG0_USBFSPSC_Pos          22
#define RCU_CFG0_USBFSPSC_Msk          _AC(0x00c00000,U)       /*!< USBFS clock prescaler selection */
#define RCU_CFG0_USBFSPSC(x)           ((x) << RCU_CFG0_USBFSPSC_Pos)
#define RCU_CFG0_USBFSPSC_DIV1_5       RCU_CFG0_USBFSPSC(0)    /*!< USBFS prescaler select CK_PLL/1.5 */
#define RCU_CFG0_USBFSPSC_DIV1         RCU_CFG0_USBFSPSC(1)    /*!< USBFS prescaler select CK_PLL/1 */
#define RCU_CFG0_USBFSPSC_DIV2_5       RCU_CFG0_USBFSPSC(2)    /*!< USBFS prescaler select CK_PLL/2.5 */
#define RCU_CFG0_USBFSPSC_DIV2         RCU_CFG0_USBFSPSC(3)    /*!< USBFS prescaler select CK_PLL/2 */
#define RCU_CFG0_PLLMF_Pos             18
#define RCU_CFG0_PLLMF_Msk             _AC(0x203c0000,U)       /*!< PLL clock multiplication factor */
#define RCU_CFG0_PLLMF(x)              ((((x) & _AC(0xf,U)) << RCU_CFG0_PLLMF_Pos) | (((x) >> 4) << RCU_CFG0_PLLMF_4_Pos))
#define RCU_CFG0_PLLMF_MUL2            RCU_CFG0_PLLMF(0)       /*!< PLL source clock multiply by 2 */
#define RCU_CFG0_PLLMF_MUL3            RCU_CFG0_PLLMF(1)       /*!< PLL source clock multiply by 3 */
#define RCU_CFG0_PLLMF_MUL4            RCU_CFG0_PLLMF(2)       /*!< PLL source clock multiply by 4 */
#define RCU_CFG0_PLLMF_MUL5            RCU_CFG0_PLLMF(3)       /*!< PLL source clock multiply by 5 */
#define RCU_CFG0_PLLMF_MUL6            RCU_CFG0_PLLMF(4)       /*!< PLL source clock multiply by 6 */
#define RCU_CFG0_PLLMF_MUL7            RCU_CFG0_PLLMF(5)       /*!< PLL source clock multiply by 7 */
#define RCU_CFG0_PLLMF_MUL8            RCU_CFG0_PLLMF(6)       /*!< PLL source clock multiply by 8 */
#define RCU_CFG0_PLLMF_MUL9            RCU_CFG0_PLLMF(7)       /*!< PLL source clock multiply by 9 */
#define RCU_CFG0_PLLMF_MUL10           RCU_CFG0_PLLMF(8)       /*!< PLL source clock multiply by 10 */
#define RCU_CFG0_PLLMF_MUL11           RCU_CFG0_PLLMF(9)       /*!< PLL source clock multiply by 11 */
#define RCU_CFG0_PLLMF_MUL12           RCU_CFG0_PLLMF(10)      /*!< PLL source clock multiply by 12 */
#define RCU_CFG0_PLLMF_MUL13           RCU_CFG0_PLLMF(11)      /*!< PLL source clock multiply by 13 */
#define RCU_CFG0_PLLMF_MUL14           RCU_CFG0_PLLMF(12)      /*!< PLL source clock multiply by 14 */
#define RCU_CFG0_PLLMF_MUL6_5          RCU_CFG0_PLLMF(13)      /*!< PLL source clock multiply by 6.5 */
#define RCU_CFG0_PLLMF_MUL16           RCU_CFG0_PLLMF(14)      /*!< PLL source clock multiply by 16 */
#define RCU_CFG0_PLLMF_MUL17           RCU_CFG0_PLLMF(16)      /*!< PLL source clock multiply by 17 */
#define RCU_CFG0_PLLMF_MUL18           RCU_CFG0_PLLMF(17)      /*!< PLL source clock multiply by 18 */
#define RCU_CFG0_PLLMF_MUL19           RCU_CFG0_PLLMF(18)      /*!< PLL source clock multiply by 19 */
#define RCU_CFG0_PLLMF_MUL20           RCU_CFG0_PLLMF(19)      /*!< PLL source clock multiply by 20 */
#define RCU_CFG0_PLLMF_MUL21           RCU_CFG0_PLLMF(20)      /*!< PLL source clock multiply by 21 */
#define RCU_CFG0_PLLMF_MUL22           RCU_CFG0_PLLMF(21)      /*!< PLL source clock multiply by 22 */
#define RCU_CFG0_PLLMF_MUL23           RCU_CFG0_PLLMF(22)      /*!< PLL source clock multiply by 23 */
#define RCU_CFG0_PLLMF_MUL24           RCU_CFG0_PLLMF(23)      /*!< PLL source clock multiply by 24 */
#define RCU_CFG0_PLLMF_MUL25           RCU_CFG0_PLLMF(24)      /*!< PLL source clock multiply by 25 */
#define RCU_CFG0_PLLMF_MUL26           RCU_CFG0_PLLMF(25)      /*!< PLL source clock multiply by 26 */
#define RCU_CFG0_PLLMF_MUL27           RCU_CFG0_PLLMF(26)      /*!< PLL source clock multiply by 27 */
#define RCU_CFG0_PLLMF_MUL28           RCU_CFG0_PLLMF(27)      /*!< PLL source clock multiply by 28 */
#define RCU_CFG0_PLLMF_MUL29           RCU_CFG0_PLLMF(28)      /*!< PLL source clock multiply by 29 */
#define RCU_CFG0_PLLMF_MUL30           RCU_CFG0_PLLMF(29)      /*!< PLL source clock multiply by 30 */
#define RCU_CFG0_PLLMF_MUL31           RCU_CFG0_PLLMF(30)      /*!< PLL source clock multiply by 31 */
#define RCU_CFG0_PLLMF_MUL32           RCU_CFG0_PLLMF(31)      /*!< PLL source clock multiply by 32 */
#define RCU_CFG0_PREDV0_LSB            _BIT(17,U)              /*!< the LSB of PREDV0 division factor */
#define RCU_CFG0_PLLSEL                _BIT(16,U)              /*!< PLL clock source selection */
#define RCU_CFG0_ADCPSC_Pos            14
#define RCU_CFG0_ADCPSC_Msk            _AC(0x1000c000,U)       /*!< ADC prescaler selection */
#define RCU_CFG0_ADCPSC(x)             ((((x) & _AC(0x3,U)) << RCU_CFG0_ADCPSC_Pos) | (((x) >> 2) << RCU_CFG0_ADCPSC_2_Pos))
#define RCU_CFG0_ADCPSC_DIV2           RCU_CFG0_ADCPSC(0)      /*!< ADC prescaler select CK_APB2/2 */
#define RCU_CFG0_ADCPSC_DIV4           RCU_CFG0_ADCPSC(1)      /*!< ADC prescaler select CK_APB2/4 */
#define RCU_CFG0_ADCPSC_DIV6           RCU_CFG0_ADCPSC(2)      /*!< ADC prescaler select CK_APB2/6 */
#define RCU_CFG0_ADCPSC_DIV8           RCU_CFG0_ADCPSC(3)      /*!< ADC prescaler select CK_APB2/8 */
#define RCU_CFG0_ADCPSC_DIV12          RCU_CFG0_ADCPSC(5)      /*!< ADC prescaler select CK_APB2/12 */
#define RCU_CFG0_ADCPSC_DIV16          RCU_CFG0_ADCPSC(7)      /*!< ADC prescaler select CK_APB2/16 */
#define RCU_CFG0_APB2PSC_Pos           11
#define RCU_CFG0_APB2PSC_Msk           _AC(0x00003800,U)       /*!< APB2 prescaler selection */
#define RCU_CFG0_APB2PSC(x)            ((x) << RCU_CFG0_APB2PSC_Pos)
#define RCU_CFG0_APB2PSC_DIV1          RCU_CFG0_APB2PSC(0)     /*!< APB2 prescaler select CK_AHB */
#define RCU_CFG0_APB2PSC_DIV2          RCU_CFG0_APB2PSC(4)     /*!< APB2 prescaler select CK_AHB/2 */
#define RCU_CFG0_APB2PSC_DIV4          RCU_CFG0_APB2PSC(5)     /*!< APB2 prescaler select CK_AHB/4 */
#define RCU_CFG0_APB2PSC_DIV8          RCU_CFG0_APB2PSC(6)     /*!< APB2 prescaler select CK_AHB/8 */
#define RCU_CFG0_APB2PSC_DIV16         RCU_CFG0_APB2PSC(7)     /*!< APB2 prescaler select CK_AHB/16 */
#define RCU_CFG0_APB1PSC_Pos           8
#define RCU_CFG0_APB1PSC_Msk           _AC(0x00000700,U)       /*!< APB1 prescaler selection */
#define RCU_CFG0_APB1PSC(x)            ((x) << RCU_CFG0_APB1PSC_Pos)
#define RCU_CFG0_APB1PSC_DIV1          RCU_CFG0_APB1PSC(0)     /*!< APB1 prescaler select CK_AHB */
#define RCU_CFG0_APB1PSC_DIV2          RCU_CFG0_APB1PSC(4)     /*!< APB1 prescaler select CK_AHB/2 */
#define RCU_CFG0_APB1PSC_DIV4          RCU_CFG0_APB1PSC(5)     /*!< APB1 prescaler select CK_AHB/4 */
#define RCU_CFG0_APB1PSC_DIV8          RCU_CFG0_APB1PSC(6)     /*!< APB1 prescaler select CK_AHB/8 */
#define RCU_CFG0_APB1PSC_DIV16         RCU_CFG0_APB1PSC(7)     /*!< APB1 prescaler select CK_AHB/16 */
#define RCU_CFG0_AHBPSC_Pos            4
#define RCU_CFG0_AHBPSC_Msk            _AC(0x000000f0,U)       /*!< AHB prescaler selection */
#define RCU_CFG0_AHBPSC(x)             ((x) << RCU_CFG0_AHBPSC_Pos)
#define RCU_CFG0_AHBPSC_DIV1           RCU_CFG0_AHBPSC(0)      /*!< AHB prescaler select CK_SYS */
#define RCU_CFG0_AHBPSC_DIV2           RCU_CFG0_AHBPSC(8)      /*!< AHB prescaler select CK_SYS/2 */
#define RCU_CFG0_AHBPSC_DIV4           RCU_CFG0_AHBPSC(9)      /*!< AHB prescaler select CK_SYS/4 */
#define RCU_CFG0_AHBPSC_DIV8           RCU_CFG0_AHBPSC(10)     /*!< AHB prescaler select CK_SYS/8 */
#define RCU_CFG0_AHBPSC_DIV16          RCU_CFG0_AHBPSC(11)     /*!< AHB prescaler select CK_SYS/16 */
#define RCU_CFG0_AHBPSC_DIV64          RCU_CFG0_AHBPSC(12)     /*!< AHB prescaler select CK_SYS/64 */
#define RCU_CFG0_AHBPSC_DIV128         RCU_CFG0_AHBPSC(13)     /*!< AHB prescaler select CK_SYS/128 */
#define RCU_CFG0_AHBPSC_DIV256         RCU_CFG0_AHBPSC(14)     /*!< AHB prescaler select CK_SYS/256 */
#define RCU_CFG0_AHBPSC_DIV512         RCU_CFG0_AHBPSC(15)     /*!< AHB prescaler select CK_SYS/512 */
#define RCU_CFG0_SCSS_Pos              2
#define RCU_CFG0_SCSS_Msk              _AC(0x0000000c,U)       /*!< system clock switch status */
#define RCU_CFG0_SCSS(x)               ((x) << RCU_CFG0_SCSS_Pos)
#define RCU_CFG0_SCSS_IRC8M            RCU_CFG0_SCSS(0)        /*!< system clock source select IRC8M */
#define RCU_CFG0_SCSS_HXTAL            RCU_CFG0_SCSS(1)        /*!< system clock source select HXTAL */
#define RCU_CFG0_SCSS_PLL              RCU_CFG0_SCSS(2)        /*!< system clock source select PLLP */
#define RCU_CFG0_SCS_Pos               0
#define RCU_CFG0_SCS_Msk               _AC(0x00000003,U)       /*!< system clock switch */
#define RCU_CFG0_SCS(x)                ((x) << RCU_CFG0_SCS_Pos)
#define RCU_CFG0_SCS_IRC8M             RCU_CFG0_SCS(0)         /*!< system clock source select IRC8M */
#define RCU_CFG0_SCS_HXTAL             RCU_CFG0_SCS(1)         /*!< system clock source select HXTAL */
#define RCU_CFG0_SCS_PLL               RCU_CFG0_SCS(2)         /*!< system clock source select PLL */

/* RCU_INT */
#define RCU_INT_CKMIC                  _BIT(23,U)              /*!< HXTAL clock stuck interrupt clear */
#define RCU_INT_PLL2STBIC              _BIT(22,U)              /*!< PLL2 stabilization interrupt clear */
#define RCU_INT_PLL1STBIC              _BIT(21,U)              /*!< PLL1 stabilization interrupt clear */
#define RCU_INT_PLLSTBIC               _BIT(20,U)              /*!< PLL stabilization interrupt clear */
#define RCU_INT_HXTALSTBIC             _BIT(19,U)              /*!< HXTAL stabilization interrupt clear */
#define RCU_INT_IRC8MSTBIC             _BIT(18,U)              /*!< IRC8M stabilization interrupt clear */
#define RCU_INT_LXTALSTBIC             _BIT(17,U)              /*!< LXTAL stabilization interrupt clear */
#define RCU_INT_IRC40KSTBIC            _BIT(16,U)              /*!< IRC40K stabilization interrupt clear */
#define RCU_INT_PLL2STBIE              _BIT(14,U)              /*!< PLL2 stabilization interrupt enable */
#define RCU_INT_PLL1STBIE              _BIT(13,U)              /*!< PLL1 stabilization interrupt enable */
#define RCU_INT_PLLSTBIE               _BIT(12,U)              /*!< PLL stabilization interrupt enable */
#define RCU_INT_HXTALSTBIE             _BIT(11,U)              /*!< HXTAL stabilization interrupt enable */
#define RCU_INT_IRC8MSTBIE             _BIT(10,U)              /*!< IRC8M stabilization interrupt enable */
#define RCU_INT_LXTALSTBIE             _BIT(9,U)               /*!< LXTAL stabilization interrupt enable */
#define RCU_INT_IRC40KSTBIE            _BIT(8,U)               /*!< IRC40K stabilization interrupt enable */
#define RCU_INT_CKMIF                  _BIT(7,U)               /*!< HXTAL clock stuck interrupt flag */
#define RCU_INT_PLL2STBIF              _BIT(6,U)               /*!< PLL2 stabilization interrupt flag */
#define RCU_INT_PLL1STBIF              _BIT(5,U)               /*!< PLL1 stabilization interrupt flag */
#define RCU_INT_PLLSTBIF               _BIT(4,U)               /*!< PLL stabilization interrupt flag */
#define RCU_INT_HXTALSTBIF             _BIT(3,U)               /*!< HXTAL stabilization interrupt flag */
#define RCU_INT_IRC8MSTBIF             _BIT(2,U)               /*!< IRC8M stabilization interrupt flag */
#define RCU_INT_LXTALSTBIF             _BIT(1,U)               /*!< LXTAL stabilization interrupt flag */
#define RCU_INT_IRC40KSTBIF            _BIT(0,U)               /*!< IRC40K stabilization interrupt flag */

/* RCU_APB2RST */
#define RCU_APB2RST_USART0RST          _BIT(14,U)              /*!< USART0 reset */
#define RCU_APB2RST_SPI0RST            _BIT(12,U)              /*!< SPI0 reset */
#define RCU_APB2RST_TIMER0RST          _BIT(11,U)              /*!< TIMER0 reset */
#define RCU_APB2RST_ADC1RST            _BIT(10,U)              /*!< ADC1 reset */
#define RCU_APB2RST_ADC0RST            _BIT(9,U)               /*!< ADC0 reset */
#define RCU_APB2RST_PERST              _BIT(6,U)               /*!< GPIO port E reset */
#define RCU_APB2RST_PDRST              _BIT(5,U)               /*!< GPIO port D reset */
#define RCU_APB2RST_PCRST              _BIT(4,U)               /*!< GPIO port C reset */
#define RCU_APB2RST_PBRST              _BIT(3,U)               /*!< GPIO port B reset */
#define RCU_APB2RST_PARST              _BIT(2,U)               /*!< GPIO port A reset */
#define RCU_APB2RST_AFRST              _BIT(0,U)               /*!< alternate function I/O reset */

/* RCU_APB1RST */
#define RCU_APB1RST_DACRST             _BIT(29,U)              /*!< DAC reset */
#define RCU_APB1RST_PMURST             _BIT(28,U)              /*!< PMU reset */
#define RCU_APB1RST_BKPIRST            _BIT(27,U)              /*!< backup interface reset */
#define RCU_APB1RST_CAN1RST            _BIT(26,U)              /*!< CAN1 reset */
#define RCU_APB1RST_CAN0RST            _BIT(25,U)              /*!< CAN0 reset */
#define RCU_APB1RST_I2C1RST            _BIT(22,U)              /*!< I2C1 reset */
#define RCU_APB1RST_I2C0RST            _BIT(21,U)              /*!< I2C0 reset */
#define RCU_APB1RST_UART4RST           _BIT(20,U)              /*!< UART4 reset */
#define RCU_APB1RST_UART3RST           _BIT(19,U)              /*!< UART3 reset */
#define RCU_APB1RST_USART2RST          _BIT(18,U)              /*!< USART2 reset */
#define RCU_APB1RST_USART1RST          _BIT(17,U)              /*!< USART1 reset */
#define RCU_APB1RST_SPI2RST            _BIT(15,U)              /*!< SPI2 reset */
#define RCU_APB1RST_SPI1RST            _BIT(14,U)              /*!< SPI1 reset */
#define RCU_APB1RST_WWDGTRST           _BIT(11,U)              /*!< WWDGT reset */
#define RCU_APB1RST_TIMER6RST          _BIT(5,U)               /*!< TIMER6 reset */
#define RCU_APB1RST_TIMER5RST          _BIT(4,U)               /*!< TIMER5 reset */
#define RCU_APB1RST_TIMER4RST          _BIT(3,U)               /*!< TIMER4 reset */
#define RCU_APB1RST_TIMER3RST          _BIT(2,U)               /*!< TIMER3 reset */
#define RCU_APB1RST_TIMER2RST          _BIT(1,U)               /*!< TIMER2 reset */
#define RCU_APB1RST_TIMER1RST          _BIT(0,U)               /*!< TIMER1 reset */

/* RCU_AHBEN */
#define RCU_AHBEN_USBFSEN              _BIT(12,U)              /*!< USBFS clock enable */
#define RCU_AHBEN_EXMCEN               _BIT(8,U)               /*!< EXMC clock enable */
#define RCU_AHBEN_CRCEN                _BIT(6,U)               /*!< CRC clock enable */
#define RCU_AHBEN_FMCSPEN              _BIT(4,U)               /*!< FMC clock enable when sleep mode */
#define RCU_AHBEN_SRAMSPEN             _BIT(2,U)               /*!< SRAM clock enable when sleep mode */
#define RCU_AHBEN_DMA1EN               _BIT(1,U)               /*!< DMA1 clock enable */
#define RCU_AHBEN_DMA0EN               _BIT(0,U)               /*!< DMA0 clock enable */

/* RCU_APB2EN */
#define RCU_APB2EN_USART0EN            _BIT(14,U)              /*!< USART0 clock enable */
#define RCU_APB2EN_SPI0EN              _BIT(12,U)              /*!< SPI0 clock enable */
#define RCU_APB2EN_TIMER0EN            _BIT(11,U)              /*!< TIMER0 clock enable */
#define RCU_APB2EN_ADC1EN              _BIT(10,U)              /*!< ADC1 clock enable */
#define RCU_APB2EN_ADC0EN              _BIT(9,U)               /*!< ADC0 clock enable */
#define RCU_APB2EN_PEEN                _BIT(6,U)               /*!< GPIO port E clock enable */
#define RCU_APB2EN_PDEN                _BIT(5,U)               /*!< GPIO port D clock enable */
#define RCU_APB2EN_PCEN                _BIT(4,U)               /*!< GPIO port C clock enable */
#define RCU_APB2EN_PBEN                _BIT(3,U)               /*!< GPIO port B clock enable */
#define RCU_APB2EN_PAEN                _BIT(2,U)               /*!< GPIO port A clock enable */
#define RCU_APB2EN_AFEN                _BIT(0,U)               /*!< alternate function IO clock enable */

/* RCU_APB1EN */
#define RCU_APB1EN_DACEN               _BIT(29,U)              /*!< DAC clock enable */
#define RCU_APB1EN_PMUEN               _BIT(28,U)              /*!< PMU clock enable */
#define RCU_APB1EN_BKPIEN              _BIT(27,U)              /*!< backup interface clock enable */
#define RCU_APB1EN_CAN1EN              _BIT(26,U)              /*!< CAN1 clock enable */
#define RCU_APB1EN_CAN0EN              _BIT(25,U)              /*!< CAN0 clock enable */
#define RCU_APB1EN_I2C1EN              _BIT(22,U)              /*!< I2C1 clock enable */
#define RCU_APB1EN_I2C0EN              _BIT(21,U)              /*!< I2C0 clock enable */
#define RCU_APB1EN_UART4EN             _BIT(20,U)              /*!< UART4 clock enable */
#define RCU_APB1EN_UART3EN             _BIT(19,U)              /*!< UART3 clock enable */
#define RCU_APB1EN_USART2EN            _BIT(18,U)              /*!< USART2 clock enable */
#define RCU_APB1EN_USART1EN            _BIT(17,U)              /*!< USART1 clock enable */
#define RCU_APB1EN_SPI2EN              _BIT(15,U)              /*!< SPI2 clock enable */
#define RCU_APB1EN_SPI1EN              _BIT(14,U)              /*!< SPI1 clock enable */
#define RCU_APB1EN_WWDGTEN             _BIT(11,U)              /*!< WWDGT clock enable */
#define RCU_APB1EN_TIMER6EN            _BIT(5,U)               /*!< TIMER6 clock enable */
#define RCU_APB1EN_TIMER5EN            _BIT(4,U)               /*!< TIMER5 clock enable */
#define RCU_APB1EN_TIMER4EN            _BIT(3,U)               /*!< TIMER4 clock enable */
#define RCU_APB1EN_TIMER3EN            _BIT(2,U)               /*!< TIMER3 clock enable */
#define RCU_APB1EN_TIMER2EN            _BIT(1,U)               /*!< TIMER2 clock enable */
#define RCU_APB1EN_TIMER1EN            _BIT(0,U)               /*!< TIMER1 clock enable */

/* RCU_BDCTL */
#define RCU_BDCTL_BKPRST               _BIT(16,U)              /*!< backup domain reset */
#define RCU_BDCTL_RTCEN                _BIT(15,U)              /*!< RTC clock enable */
#define RCU_BDCTL_RTCSRC_Pos           8
#define RCU_BDCTL_RTCSRC_Msk           _AC(0x00000300,U)       /*!< RTC clock entry selection */
#define RCU_BDCTL_RTCSRC(x)            ((x) << RCU_BDCTL_RTCSRC_Pos)
#define RCU_BDCTL_RTCSRC_NONE          RCU_BDCTL_RTCSRC(0)     /*!< no clock selected */
#define RCU_BDCTL_RTCSRC_LXTAL         RCU_BDCTL_RTCSRC(1)     /*!< RTC source clock select LXTAL  */
#define RCU_BDCTL_RTCSRC_IRC40K        RCU_BDCTL_RTCSRC(2)     /*!< RTC source clock select IRC40K */
#define RCU_BDCTL_RTCSRC_HXTAL_DIV_128 RCU_BDCTL_RTCSRC(3)     /*!< RTC source clock select HXTAL/128 */
#define RCU_BDCTL_LXTALBPS             _BIT(2,U)               /*!< LXTAL bypass mode enable */
#define RCU_BDCTL_LXTALSTB             _BIT(1,U)               /*!< low speed crystal oscillator stabilization flag */
#define RCU_BDCTL_LXTALEN              _BIT(0,U)               /*!< LXTAL enable */

/* RCU_RSTSCK */
#define RCU_RSTSCK_LPRSTF              _BIT(31,U)              /*!< low-power reset flag */
#define RCU_RSTSCK_WWDGTRSTF           _BIT(30,U)              /*!< window watchdog timer reset flag */
#define RCU_RSTSCK_FWDGTRSTF           _BIT(29,U)              /*!< free watchdog timer reset flag */
#define RCU_RSTSCK_SWRSTF              _BIT(28,U)              /*!< software reset flag */
#define RCU_RSTSCK_PORRSTF             _BIT(27,U)              /*!< power reset flag */
#define RCU_RSTSCK_EPRSTF              _BIT(26,U)              /*!< external pin reset flag */
#define RCU_RSTSCK_RSTFC               _BIT(24,U)              /*!< reset flag clear */
#define RCU_RSTSCK_IRC40KSTB           _BIT(1,U)               /*!< IRC40K stabilization flag */
#define RCU_RSTSCK_IRC40KEN            _BIT(0,U)               /*!< IRC40K enable */

/* RCU_AHBRST */
#define RCU_AHBRST_USBFSRST            _BIT(12,U)              /*!< USBFS reset */

/* RCU_CFG1 */
#define RCU_CFG1_I2S2SEL               _BIT(18,U)              /*!< I2S2 clock source selection  */
#define RCU_CFG1_I2S1SEL               _BIT(17,U)              /*!< I2S1 clock source selection */
#define RCU_CFG1_PREDV0SEL             _BIT(16,U)              /*!< PREDV0 input clock source selection */
#define RCU_CFG1_PLL2MF_Pos            12
#define RCU_CFG1_PLL2MF_Msk            _AC(0x0000f000,U)       /*!< PLL2 clock multiplication factor */
#define RCU_CFG1_PLL2MF(x)             ((x) << RCU_CFG1_PLL2MF_Pos)
#define RCU_CFG1_PLL2MF_MUL8           RCU_CFG1_PLL2MF(6)      /*!< PLL2 source clock multiply by 8 */
#define RCU_CFG1_PLL2MF_MUL9           RCU_CFG1_PLL2MF(7)      /*!< PLL2 source clock multiply by 9 */
#define RCU_CFG1_PLL2MF_MUL10          RCU_CFG1_PLL2MF(8)      /*!< PLL2 source clock multiply by 10 */
#define RCU_CFG1_PLL2MF_MUL11          RCU_CFG1_PLL2MF(9)      /*!< PLL2 source clock multiply by 11 */
#define RCU_CFG1_PLL2MF_MUL12          RCU_CFG1_PLL2MF(10)     /*!< PLL2 source clock multiply by 12 */
#define RCU_CFG1_PLL2MF_MUL13          RCU_CFG1_PLL2MF(11)     /*!< PLL2 source clock multiply by 13 */
#define RCU_CFG1_PLL2MF_MUL14          RCU_CFG1_PLL2MF(12)     /*!< PLL2 source clock multiply by 14 */
#define RCU_CFG1_PLL2MF_MUL15          RCU_CFG1_PLL2MF(13)     /*!< PLL2 source clock multiply by 15 */
#define RCU_CFG1_PLL2MF_MUL16          RCU_CFG1_PLL2MF(14)     /*!< PLL2 source clock multiply by 16 */
#define RCU_CFG1_PLL2MF_MUL20          RCU_CFG1_PLL2MF(15)     /*!< PLL2 source clock multiply by 20 */
#define RCU_CFG1_PLL1MF_Pos            8
#define RCU_CFG1_PLL1MF_Msk            _AC(0x00000f00,U)       /*!< PLL1 clock multiplication factor */
#define RCU_CFG1_PLL1MF(x)             ((x) << RCU_CFG1_PLL1MF_Pos)
#define RCU_CFG1_PLL1MF_MUL8           RCU_CFG1_PLL1MF(6)      /*!< PLL1 source clock multiply by 8 */
#define RCU_CFG1_PLL1MF_MUL9           RCU_CFG1_PLL1MF(7)      /*!< PLL1 source clock multiply by 9 */
#define RCU_CFG1_PLL1MF_MUL10          RCU_CFG1_PLL1MF(8)      /*!< PLL1 source clock multiply by 10 */
#define RCU_CFG1_PLL1MF_MUL11          RCU_CFG1_PLL1MF(9)      /*!< PLL1 source clock multiply by 11 */
#define RCU_CFG1_PLL1MF_MUL12          RCU_CFG1_PLL1MF(10)     /*!< PLL1 source clock multiply by 12 */
#define RCU_CFG1_PLL1MF_MUL13          RCU_CFG1_PLL1MF(11)     /*!< PLL1 source clock multiply by 13 */
#define RCU_CFG1_PLL1MF_MUL14          RCU_CFG1_PLL1MF(12)     /*!< PLL1 source clock multiply by 14 */
#define RCU_CFG1_PLL1MF_MUL15          RCU_CFG1_PLL1MF(13)     /*!< PLL1 source clock multiply by 15 */
#define RCU_CFG1_PLL1MF_MUL16          RCU_CFG1_PLL1MF(14)     /*!< PLL1 source clock multiply by 16 */
#define RCU_CFG1_PLL1MF_MUL20          RCU_CFG1_PLL1MF(15)     /*!< PLL1 source clock multiply by 20 */
#define RCU_CFG1_PREDV1_Pos            4
#define RCU_CFG1_PREDV1_Msk            _AC(0x000000f0,U)       /*!< PREDV1 division factor */
#define RCU_CFG1_PREDV1(x)             ((x) << RCU_CFG1_PREDV1_Pos)
#define RCU_CFG1_PREDV1_DIV1           RCU_CFG1_PREDV1(0)      /*!< PREDV1 input source clock not divided */
#define RCU_CFG1_PREDV1_DIV2           RCU_CFG1_PREDV1(1)      /*!< PREDV1 input source clock divided by 2 */
#define RCU_CFG1_PREDV1_DIV3           RCU_CFG1_PREDV1(2)      /*!< PREDV1 input source clock divided by 3 */
#define RCU_CFG1_PREDV1_DIV4           RCU_CFG1_PREDV1(3)      /*!< PREDV1 input source clock divided by 4 */
#define RCU_CFG1_PREDV1_DIV5           RCU_CFG1_PREDV1(4)      /*!< PREDV1 input source clock divided by 5 */
#define RCU_CFG1_PREDV1_DIV6           RCU_CFG1_PREDV1(5)      /*!< PREDV1 input source clock divided by 6 */
#define RCU_CFG1_PREDV1_DIV7           RCU_CFG1_PREDV1(6)      /*!< PREDV1 input source clock divided by 7 */
#define RCU_CFG1_PREDV1_DIV8           RCU_CFG1_PREDV1(7)      /*!< PREDV1 input source clock divided by 8 */
#define RCU_CFG1_PREDV1_DIV9           RCU_CFG1_PREDV1(8)      /*!< PREDV1 input source clock divided by 9 */
#define RCU_CFG1_PREDV1_DIV10          RCU_CFG1_PREDV1(9)      /*!< PREDV1 input source clock divided by 10 */
#define RCU_CFG1_PREDV1_DIV11          RCU_CFG1_PREDV1(10)     /*!< PREDV1 input source clock divided by 11 */
#define RCU_CFG1_PREDV1_DIV12          RCU_CFG1_PREDV1(11)     /*!< PREDV1 input source clock divided by 12 */
#define RCU_CFG1_PREDV1_DIV13          RCU_CFG1_PREDV1(12)     /*!< PREDV1 input source clock divided by 13 */
#define RCU_CFG1_PREDV1_DIV14          RCU_CFG1_PREDV1(13)     /*!< PREDV1 input source clock divided by 14 */
#define RCU_CFG1_PREDV1_DIV15          RCU_CFG1_PREDV1(14)     /*!< PREDV1 input source clock divided by 15 */
#define RCU_CFG1_PREDV1_DIV16          RCU_CFG1_PREDV1(15)     /*!< PREDV1 input source clock divided by 16 */
#define RCU_CFG1_PREDV0_Pos            0
#define RCU_CFG1_PREDV0_Msk            _AC(0x0000000f,U)       /*!< PREDV0 division factor */
#define RCU_CFG1_PREDV0(x)             ((x) << RCU_CFG1_PREDV0_Pos)
#define RCU_CFG1_PREDV0_DIV1           RCU_CFG1_PREDV0(0)      /*!< PREDV0 input source clock not divided */
#define RCU_CFG1_PREDV0_DIV2           RCU_CFG1_PREDV0(1)      /*!< PREDV0 input source clock divided by 2 */
#define RCU_CFG1_PREDV0_DIV3           RCU_CFG1_PREDV0(2)      /*!< PREDV0 input source clock divided by 3 */
#define RCU_CFG1_PREDV0_DIV4           RCU_CFG1_PREDV0(3)      /*!< PREDV0 input source clock divided by 4 */
#define RCU_CFG1_PREDV0_DIV5           RCU_CFG1_PREDV0(4)      /*!< PREDV0 input source clock divided by 5 */
#define RCU_CFG1_PREDV0_DIV6           RCU_CFG1_PREDV0(5)      /*!< PREDV0 input source clock divided by 6 */
#define RCU_CFG1_PREDV0_DIV7           RCU_CFG1_PREDV0(6)      /*!< PREDV0 input source clock divided by 7 */
#define RCU_CFG1_PREDV0_DIV8           RCU_CFG1_PREDV0(7)      /*!< PREDV0 input source clock divided by 8 */
#define RCU_CFG1_PREDV0_DIV9           RCU_CFG1_PREDV0(8)      /*!< PREDV0 input source clock divided by 9 */
#define RCU_CFG1_PREDV0_DIV10          RCU_CFG1_PREDV0(9)      /*!< PREDV0 input source clock divided by 10 */
#define RCU_CFG1_PREDV0_DIV11          RCU_CFG1_PREDV0(10)     /*!< PREDV0 input source clock divided by 11 */
#define RCU_CFG1_PREDV0_DIV12          RCU_CFG1_PREDV0(11)     /*!< PREDV0 input source clock divided by 12 */
#define RCU_CFG1_PREDV0_DIV13          RCU_CFG1_PREDV0(12)     /*!< PREDV0 input source clock divided by 13 */
#define RCU_CFG1_PREDV0_DIV14          RCU_CFG1_PREDV0(13)     /*!< PREDV0 input source clock divided by 14 */
#define RCU_CFG1_PREDV0_DIV15          RCU_CFG1_PREDV0(14)     /*!< PREDV0 input source clock divided by 15 */
#define RCU_CFG1_PREDV0_DIV16          RCU_CFG1_PREDV0(15)     /*!< PREDV0 input source clock divided by 16 */

/* RCU_DSV */
#define RCU_DSV_DSLPVS_Pos             0
#define RCU_DSV_DSLPVS_Msk             _AC(0x00000003,U)       /*!< deep-sleep mode voltage select */
#define RCU_DSV_DSLPVS(x)              ((x) << RCU_DSV_DSLPVS_Pos)
#define RCU_DSV_DSLPVS_1_2             RCU_DSV_DSLPVS(0)       /*!< core voltage is 1.2V in deep-sleep mode */
#define RCU_DSV_DSLPVS_1_1             RCU_DSV_DSLPVS(1)       /*!< core voltage is 1.1V in deep-sleep mode */
#define RCU_DSV_DSLPVS_1_0             RCU_DSV_DSLPVS(2)       /*!< core voltage is 1.0V in deep-sleep mode */
#define RCU_DSV_DSLPVS_0_9             RCU_DSV_DSLPVS(3)       /*!< core voltage is 0.9V in deep-sleep mode */

/* --------------------- RTC -------------------------- */

#define RTC_BASE                       _AC(0x40002800,UL)  /*!< RTC base address */

/* register definitions */
#define RTC_INTEN                      _AC(0x00,UL)  /*!< interrupt enable register */
#define RTC_CTL                        _AC(0x04,UL)  /*!< control register */
#define RTC_PSCH                       _AC(0x08,UL)  /*!< prescaler high register */
#define RTC_PSCL                       _AC(0x0C,UL)  /*!< prescaler low register */
#define RTC_DIVH                       _AC(0x10,UL)  /*!< divider high register */
#define RTC_DIVL                       _AC(0x14,UL)  /*!< divider low register */
#define RTC_CNTH                       _AC(0x18,UL)  /*!< counter high register */
#define RTC_CNTL                       _AC(0x1C,UL)  /*!< counter low register */
#define RTC_ALRMH                      _AC(0x20,UL)  /*!< alarm high register */
#define RTC_ALRML                      _AC(0x24,UL)  /*!< alarm low register */

/* RTC_INTEN */
#define RTC_INTEN_OVIE                 _BIT(2,U)          /*!< overflow interrupt enable */
#define RTC_INTEN_ALRMIE               _BIT(1,U)          /*!< alarm interrupt enable */
#define RTC_INTEN_SCIE                 _BIT(0,U)          /*!< second interrupt enable */

/* RTC_CTL */
#define RTC_CTL_LWOFF                  _BIT(5,U)          /*!< last write operation finished flag */
#define RTC_CTL_CMF                    _BIT(4,U)          /*!< configuration mode flag */
#define RTC_CTL_RSYNF                  _BIT(3,U)          /*!< registers synchronized flag */
#define RTC_CTL_OVIF                   _BIT(2,U)          /*!< overflow interrupt flag */
#define RTC_CTL_ALRMIF                 _BIT(1,U)          /*!< alarm interrupt flag */
#define RTC_CTL_SCIF                   _BIT(0,U)          /*!< second interrupt flag */

/* RTC_PSCH */
#define RTC_PSCH_PSC_Pos               0
#define RTC_PSCH_PSC_Msk               _AC(0x0000000f,U)  /*!< prescaler high value */
#define RTC_PSCH_PSC(x)                ((x) << RTC_PSCH_PSC_Pos)

/* RTC_PSCL */
#define RTC_PSCL_PSC_Pos               0
#define RTC_PSCL_PSC_Msk               _AC(0x0000ffff,U)  /*!< prescaler low value */
#define RTC_PSCL_PSC(x)                ((x) << RTC_PSCL_PSC_Pos)

/* RTC_DIVH */
#define RTC_DIVH_DIV_Pos               0
#define RTC_DIVH_DIV_Msk               _AC(0x0000000f,U)  /*!< divider high value */

/* RTC_DIVL */
#define RTC_DIVL_DIV_Pos               0
#define RTC_DIVL_DIV_Msk               _AC(0x0000ffff,U)  /*!< divider low value */
#define RTC_DIVL_DIV(x)                ((x) << RTC_DIVL_DIV_Pos)

/* RTC_CNTH */
#define RTC_CNTH_CNT_Pos               0
#define RTC_CNTH_CNT_Msk               _AC(0x0000ffff,U)  /*!< counter high value */
#define RTC_CNTH_CNT(x)                ((x) << RTC_CNTH_CNT_Pos)

/* RTC_CNTL */
#define RTC_CNTL_CNT_Pos               0
#define RTC_CNTL_CNT_Msk               _AC(0x0000ffff,U)  /*!< counter low value */
#define RTC_CNTL_CNT(x)                ((x) << RTC_CNTL_CNT_Pos)

/* RTC_ALRMH */
#define RTC_ALRMH_ALRM_Pos             0
#define RTC_ALRMH_ALRM_Msk             _AC(0x0000ffff,U)  /*!< alarm high value */
#define RTC_ALRMH_ALRM(x)              ((x) << RTC_ALRMH_ALRM_Pos)

/* RTC_ALRML */
#define RTC_ALRML_ALRM_Pos             0
#define RTC_ALRML_ALRM_Msk             _AC(0x0000ffff,U)  /*!< alarm low value */
#define RTC_ALRML_ALRM(x)              ((x) << RTC_ALRML_ALRM_Pos)

/* --------------------- SPI -------------------------- */

#define SPI0_BASE                      _AC(0x40013000,UL)  /*!< SPI0 base address */
#if defined(GD32VF103C8T6) || defined(GD32VF103CBT6) || defined(GD32VF103R8T6) || \
    defined(GD32VF103RBT6) || defined(GD32VF103V8T6) || defined(GD32VF103VBT6)
    #define SPI1_BASE                  _AC(0x40003800,UL)  /*!< SPI1 base address */
    #define SPI2_BASE                  _AC(0x40003C00,UL)  /*!< SPI2 base address */
#endif

/* register definitions */
#define SPI_CTL0                       _AC(0x00,UL)  /*!< SPI control register 0 */
#define SPI_CTL1                       _AC(0x04,UL)  /*!< SPI control register 1*/
#define SPI_STAT                       _AC(0x08,UL)  /*!< SPI status register */
#define SPI_DATA                       _AC(0x0C,UL)  /*!< SPI data register */
#define SPI_CRCPOLY                    _AC(0x10,UL)  /*!< SPI CRC polynomial register */
#define SPI_RCRC                       _AC(0x14,UL)  /*!< SPI receive CRC register */
#define SPI_TCRC                       _AC(0x18,UL)  /*!< SPI transmit CRC register */
#define SPI_I2SCTL                     _AC(0x1C,UL)  /*!< SPI I2S control register */
#define SPI_I2SPSC                     _AC(0x20,UL)  /*!< SPI I2S clock prescaler register */

/* SPI_CTL0 */
#define SPI_CTL0_BDEN                  _BIT(15,U)              /*!< bidirectional enable */
#define SPI_CTL0_BDOEN                 _BIT(14,U)              /*!< bidirectional transmit output enable*/
#define SPI_CTL0_CRCEN                 _BIT(13,U)              /*!< CRC calculation enable */
#define SPI_CTL0_CRCNT                 _BIT(12,U)              /*!< CRC next transfer */
#define SPI_CTL0_FF16                  _BIT(11,U)              /*!< data frame size */
#define SPI_CTL0_RO                    _BIT(10,U)              /*!< receive only */
#define SPI_CTL0_SWNSSEN               _BIT(9,U)               /*!< NSS software mode selection */
#define SPI_CTL0_SWNSS                 _BIT(8,U)               /*!< NSS pin selection in NSS software mode */
#define SPI_CTL0_LF                    _BIT(7,U)               /*!< LSB first mode */
#define SPI_CTL0_SPIEN                 _BIT(6,U)               /*!< SPI enable*/
#define SPI_CTL0_PSC_Pos               3
#define SPI_CTL0_PSC_Msk               _AC(0x00000038,U)       /*!< master clock prescaler selection */
#define SPI_CTL0_PSC(x)                ((x) << SPI_CTL0_PSC_Pos)
#define SPI_CTL0_PSC_DIV2              SPI_CTL0_PSC(0)         /*!< SPI clock prescale factor is 2 */
#define SPI_CTL0_PSC_DIV4              SPI_CTL0_PSC(1)         /*!< SPI clock prescale factor is 4 */
#define SPI_CTL0_PSC_DIV8              SPI_CTL0_PSC(2)         /*!< SPI clock prescale factor is 8 */
#define SPI_CTL0_PSC_DIV16             SPI_CTL0_PSC(3)         /*!< SPI clock prescale factor is 16 */
#define SPI_CTL0_PSC_DIV32             SPI_CTL0_PSC(4)         /*!< SPI clock prescale factor is 32 */
#define SPI_CTL0_PSC_DIV64             SPI_CTL0_PSC(5)         /*!< SPI clock prescale factor is 64 */
#define SPI_CTL0_PSC_DIV128            SPI_CTL0_PSC(6)         /*!< SPI clock prescale factor is 128 */
#define SPI_CTL0_PSC_DIV256            SPI_CTL0_PSC(7)         /*!< SPI clock prescale factor is 256 */
#define SPI_CTL0_MSTMOD                _BIT(2,U)               /*!< master mode enable */
#define SPI_CTL0_CKPL                  _BIT(1,U)               /*!< clock polarity selection */
#define SPI_CTL0_CKPH                  _BIT(0,U)               /*!< clock phase selection*/

/* SPI_CTL1 */
#define SPI_CTL1_TBEIE                 _BIT(7,U)               /*!< transmit buffer empty interrupt enable */
#define SPI_CTL1_RBNEIE                _BIT(6,U)               /*!< receive buffer not empty interrupt enable */
#define SPI_CTL1_ERRIE                 _BIT(5,U)               /*!< errors interrupt enable */
#define SPI_CTL1_TMOD                  _BIT(4,U)               /*!< SPI TI mode enable */
#define SPI_CTL1_NSSP                  _BIT(3,U)               /*!< SPI NSS pulse mode enable */
#define SPI_CTL1_NSSDRV                _BIT(2,U)               /*!< drive NSS output */
#define SPI_CTL1_DMATEN                _BIT(1,U)               /*!< transmit buffer dma enable */
#define SPI_CTL1_DMAREN                _BIT(0,U)               /*!< receive buffer dma enable */

/* SPI_STAT */
#define SPI_STAT_FERR                  _BIT(8,U)               /*!< format error bit */
#define SPI_STAT_TRANS                 _BIT(7,U)               /*!< transmitting on-going bit */
#define SPI_STAT_RXORERR               _BIT(6,U)               /*!< SPI reception overrun error bit */
#define SPI_STAT_CONFERR               _BIT(5,U)               /*!< SPI configuration error bit */
#define SPI_STAT_CRCERR                _BIT(4,U)               /*!< SPI CRC error bit */
#define SPI_STAT_TXURERR               _BIT(3,U)               /*!< I2S transmission underrun error bit */
#define SPI_STAT_I2SCH                 _BIT(2,U)               /*!< I2S channel side */
#define SPI_STAT_TBE                   _BIT(1,U)               /*!< transmit buffer empty */
#define SPI_STAT_RBNE                  _BIT(0,U)               /*!< receive buffer not empty */

/* SPI_DATA */
#define SPI_DATA_DATA_Pos              0
#define SPI_DATA_DATA_Msk              _AC(0x0000ffff,U)       /*!< data transfer register */
#define SPI_DATA_DATA(x)               ((x) << SPI_DATA_DATA_Pos)

/* SPI_CRCPOLY */
#define SPI_CRCPOLY_CRCPOLY_Pos        0
#define SPI_CRCPOLY_CRCPOLY_Msk        _AC(0x0000ffff,U)       /*!< CRC polynomial value */
#define SPI_CRCPOLY_CRCPOLY(x)         ((x) << SPI_CRCPOLY_CRCPOLY_Pos)

/* SPI_RCRC */
#define SPI_RCRC_RCRC_Pos              0
#define SPI_RCRC_RCRC_Msk              _AC(0x0000ffff,U)       /*!< RX CRC value */
#define SPI_RCRC_RCRC(x)               ((x) << SPI_RCRC_RCRC_Pos)

/* SPI_TCRC */
#define SPI_TCRC_TCRC_Pos              0
#define SPI_TCRC_TCRC_Msk              _AC(0x0000ffff,U)       /*!< TX CRC value */
#define SPI_TCRC_TCRC(x)               ((x) << SPI_TCRC_TCRC_Pos)

/* SPI_I2SCTL */
#define SPI_I2SCTL_I2SSEL              _BIT(11,U)              /*!< I2S mode selection */
#define SPI_I2SCTL_I2SEN               _BIT(10,U)              /*!< I2S enable */
#define SPI_I2SCTL_I2SOPMOD_Pos        8
#define SPI_I2SCTL_I2SOPMOD_Msk        _AC(0x00000300,U)       /*!< I2S operation mode */
#define SPI_I2SCTL_I2SOPMOD(x)         ((x) << SPI_I2SCTL_I2SOPMOD_Pos)
#define SPI_I2SCTL_I2SOPMOD_SLAVETX    SPI_I2SCTL_I2SOPMOD(0)  /*!< I2S slave transmit mode */
#define SPI_I2SCTL_I2SOPMOD_SLAVERX    SPI_I2SCTL_I2SOPMOD(1)  /*!< I2S slave receive mode */
#define SPI_I2SCTL_I2SOPMOD_MASTERTX   SPI_I2SCTL_I2SOPMOD(2)  /*!< I2S master transmit mode */
#define SPI_I2SCTL_I2SOPMOD_MASTERRX   SPI_I2SCTL_I2SOPMOD(3)  /*!< I2S master receive mode */
#define SPI_I2SCTL_PCMSMOD             _BIT(7,U)               /*!< PCM frame synchronization mode */
#define SPI_I2SCTL_I2SSTD_Pos          4
#define SPI_I2SCTL_I2SSTD_Msk          _AC(0x00000030,U)       /*!< I2S standard selection */
#define SPI_I2SCTL_I2SSTD(x)           ((x) << SPI_I2SCTL_I2SSTD_Pos)
#define SPI_I2SCTL_I2SSTD_PHILLIPS     SPI_I2SCTL_I2SSTD(0)    /*!< I2S phillips standard */
#define SPI_I2SCTL_I2SSTD_MSB          SPI_I2SCTL_I2SSTD(1)    /*!< I2S MSB standard */
#define SPI_I2SCTL_I2SSTD_LSB          SPI_I2SCTL_I2SSTD(2)    /*!< I2S LSB standard */
#define SPI_I2SCTL_I2SSTD_PCM          SPI_I2SCTL_I2SSTD(3)    /*!< I2S PCM standard */
#define SPI_I2SCTL_CKPL                _BIT(3,U)               /*!< idle state clock polarity */
#define SPI_I2SCTL_DTLEN_Pos           1
#define SPI_I2SCTL_DTLEN_Msk           _AC(0x00000006,U)       /*!< data length */
#define SPI_I2SCTL_DTLEN(x)            ((x) << SPI_I2SCTL_DTLEN_Pos)
#define SPI_I2SCTL_DTLEN_16B           SPI_I2SCTL_DTLEN(0)     /*!< I2S data length is 16 bit */
#define SPI_I2SCTL_DTLEN_24B           SPI_I2SCTL_DTLEN(1)     /*!< I2S data length is 24 bit */
#define SPI_I2SCTL_DTLEN_32B           SPI_I2SCTL_DTLEN(2)     /*!< I2S data length is 32 bit */
#define SPI_I2SCTL_CHLEN               _BIT(0,U)               /*!< channel length */

/* SPI_I2SPSC */
#define SPI_I2SPSC_MCKOEN              _BIT(9,U)               /*!< I2S MCK output enable */
#define SPI_I2SPSC_OF                  _BIT(8,U)               /*!< odd factor for the prescaler */
#define SPI_I2SPSC_DIV_Pos             0
#define SPI_I2SPSC_DIV_Msk             _AC(0x0000000f,U)       /*!< dividing factor for the prescaler */
#define SPI_I2SPSC_DIV(x)              ((x) << SPI_I2SPSC_DIV_Pos)

/* --------------------- TIMER -------------------------- */

#define TIMER0_BASE                    _AC(0x40012C00,UL)  /*!< TIMER0 base address */
#define TIMER1_BASE                    _AC(0x40000000,UL)  /*!< TIMER1 base address */
#define TIMER2_BASE                    _AC(0x40000400,UL)  /*!< TIMER2 base address */
#if defined(GD32VF103C8T6) || defined(GD32VF103CBT6) || \
    defined(GD32VF103R8T6) || defined(GD32VF103RBT6) || \
    defined(GD32VF103T8U6) || defined(GD32VF103TBU6) || \
    defined(GD32VF103V8T6) || defined(GD32VF103VBT6)
    #define TIMER3_BASE                _AC(0x40000800,UL)  /*!< TIMER3 base address */
    #define TIMER4_BASE                _AC(0x40000C00,UL)  /*!< TIMER4 base address */
#endif

/* register definitions */
#define TIMER_CTL0                     _AC(0x00,UL)  /*!< TIMER control register 0 */
#define TIMER_CTL1                     _AC(0x04,UL)  /*!< TIMER control register 1 */
#define TIMER_SMCFG                    _AC(0x08,UL)  /*!< TIMER slave mode configuration register */
#define TIMER_DMAINTEN                 _AC(0x0C,UL)  /*!< TIMER DMA and interrupt enable register */
#define TIMER_INTF                     _AC(0x10,UL)  /*!< TIMER interrupt flag register */
#define TIMER_SWEVG                    _AC(0x14,UL)  /*!< TIMER software event generation register */
#define TIMER_CHCTL0                   _AC(0x18,UL)  /*!< TIMER channel control register 0 */
#define TIMER_CHCTL1                   _AC(0x1C,UL)  /*!< TIMER channel control register 1 */
#define TIMER_CHCTL2                   _AC(0x20,UL)  /*!< TIMER channel control register 2 */
#define TIMER_CNT                      _AC(0x24,UL)  /*!< TIMER counter register */
#define TIMER_PSC                      _AC(0x28,UL)  /*!< TIMER prescaler register */
#define TIMER_CAR                      _AC(0x2C,UL)  /*!< TIMER counter auto reload register */
#define TIMER_CREP                     _AC(0x30,UL)  /*!< TIMER counter repetition register */
#define TIMER_CH0CV                    _AC(0x34,UL)  /*!< TIMER channel 0 capture/compare value register */
#define TIMER_CH1CV                    _AC(0x38,UL)  /*!< TIMER channel 1 capture/compare value register */
#define TIMER_CH2CV                    _AC(0x3C,UL)  /*!< TIMER channel 2 capture/compare value register */
#define TIMER_CH3CV                    _AC(0x40,UL)  /*!< TIMER channel 3 capture/compare value register */
#define TIMER_CCHP                     _AC(0x44,UL)  /*!< TIMER channel complementary protection register */
#define TIMER_DMACFG                   _AC(0x48,UL)  /*!< TIMER DMA configuration register */
#define TIMER_DMATB                    _AC(0x4C,UL)  /*!< TIMER DMA transfer buffer register */

/* TIMER_CTL0 */
#define TIMER_CTL0_CKDIV_Pos           8
#define TIMER_CTL0_CKDIV_Msk           _AC(0x00000300,U)       /*!< clock division */
#define TIMER_CTL0_CKDIV(x)            ((x) << TIMER_CTL0_CKDIV_Pos)
#define TIMER_CTL0_CKDIV_DIV1          TIMER_CTL0_CKDIV(0)     /*!< clock division value is 1, fDTS=fTIMER_CK   */
#define TIMER_CTL0_CKDIV_DIV2          TIMER_CTL0_CKDIV(1)     /*!< clock division value is 2, fDTS=fTIMER_CK/2 */
#define TIMER_CTL0_CKDIV_DIV4          TIMER_CTL0_CKDIV(2)     /*!< clock division value is 4, fDTS=fTIMER_CK/4 */
#define TIMER_CTL0_ARSE                _BIT(7,U)               /*!< auto-reload shadow enable */
#define TIMER_CTL0_CAM_Pos             5
#define TIMER_CTL0_CAM_Msk             _AC(0x00000060,U)       /*!< center-aligned mode selection */
#define TIMER_CTL0_CAM(x)              ((x) << TIMER_CTL0_CAM_Pos)
#define TIMER_CTL0_CAM_EDGE            TIMER_CTL0_CAM(0)       /*!< edge-aligned mode */
#define TIMER_CTL0_CAM_CENTER_DOWN     TIMER_CTL0_CAM(1)       /*!< center-aligned and counting down assert mode */
#define TIMER_CTL0_CAM_CENTER_UP       TIMER_CTL0_CAM(2)       /*!< center-aligned and counting up assert mode */
#define TIMER_CTL0_CAM_CENTER_BOTH     TIMER_CTL0_CAM(3)       /*!< center-aligned and counting up/down assert mode */
#define TIMER_CTL0_DIR                 _BIT(4,U)               /*!< timer counter direction */
#define TIMER_CTL0_SPM                 _BIT(3,U)               /*!< single pulse mode */
#define TIMER_CTL0_UPS                 _BIT(2,U)               /*!< update source */
#define TIMER_CTL0_UPDIS               _BIT(1,U)               /*!< update disable */
#define TIMER_CTL0_CEN                 _BIT(0,U)               /*!< TIMER counter enable */

/* TIMER_CTL1 */
#define TIMER_CTL1_ISO3                _BIT(14,U)              /*!< idle state of channel 3 output */
#define TIMER_CTL1_ISO2N               _BIT(13,U)              /*!< idle state of channel 2 complementary output */
#define TIMER_CTL1_ISO2                _BIT(12,U)              /*!< idle state of channel 2 output */
#define TIMER_CTL1_ISO1N               _BIT(11,U)              /*!< idle state of channel 1 complementary output */
#define TIMER_CTL1_ISO1                _BIT(10,U)              /*!< idle state of channel 1 output */
#define TIMER_CTL1_ISO0N               _BIT(9,U)               /*!< idle state of channel 0 complementary output */
#define TIMER_CTL1_ISO0                _BIT(8,U)               /*!< idle state of channel 0 output */
#define TIMER_CTL1_TI0S                _BIT(7,U)               /*!< channel 0 trigger input selection(hall mode selection) */
#define TIMER_CTL1_MMC_Pos             4
#define TIMER_CTL1_MMC_Msk             _AC(0x00000070,U)       /*!< master mode control */
#define TIMER_CTL1_MMC(x)              ((x) << TIMER_CTL1_MMC_Pos)
#define TIMER_CTL1_MMC_RESET           TIMER_CTL1_MMC(0)       /*!< the UPG bit as trigger output */
#define TIMER_CTL1_MMC_ENABLE          TIMER_CTL1_MMC(1)       /*!< the counter enable signal TIMER_CTL0_CEN as trigger output */
#define TIMER_CTL1_MMC_UPDATE          TIMER_CTL1_MMC(2)       /*!< update event as trigger output */
#define TIMER_CTL1_MMC_CH0             TIMER_CTL1_MMC(3)       /*!< a capture or a compare match occurred in channel 0 as trigger output TRGO */
#define TIMER_CTL1_MMC_O0CPRE          TIMER_CTL1_MMC(4)       /*!< O0CPRE as trigger output */
#define TIMER_CTL1_MMC_O1CPRE          TIMER_CTL1_MMC(5)       /*!< O1CPRE as trigger output */
#define TIMER_CTL1_MMC_O2CPRE          TIMER_CTL1_MMC(6)       /*!< O2CPRE as trigger output */
#define TIMER_CTL1_MMC_O3CPRE          TIMER_CTL1_MMC(7)       /*!< O3CPRE as trigger output */
#define TIMER_CTL1_DMAS                _BIT(3,U)               /*!< DMA request source selection */
#define TIMER_CTL1_CCUC                _BIT(2,U)               /*!< commutation control shadow register update control */
#define TIMER_CTL1_CCSE                _BIT(0,U)               /*!< commutation control shadow enable */

/* TIMER_SMCFG */
#define TIMER_SMCFG_ETP                _BIT(15,U)              /*!< external trigger polarity */
#define TIMER_SMCFG_SMC1               _BIT(14,U)              /*!< part of SMC for enable external clock mode 1 */
#define TIMER_SMCFG_ETPSC_Pos          12
#define TIMER_SMCFG_ETPSC_Msk          _AC(0x00003000,U)       /*!< external trigger prescaler */
#define TIMER_SMCFG_ETPSC(x)           ((x) << TIMER_SMCFG_ETPSC_Pos)
#define TIMER_SMCFG_ETPSC_OFF          TIMER_SMCFG_ETPSC(0)    /*!< not divided */
#define TIMER_SMCFG_ETPSC_DIV2         TIMER_SMCFG_ETPSC(1)    /*!< divided by 2 */
#define TIMER_SMCFG_ETPSC_DIV4         TIMER_SMCFG_ETPSC(2)    /*!< divided by 4 */
#define TIMER_SMCFG_ETPSC_DIV8         TIMER_SMCFG_ETPSC(3)    /*!< divided by 8 */
#define TIMER_SMCFG_ETFC_Pos           8
#define TIMER_SMCFG_ETFC_Msk           _AC(0x00000f00,U)       /*!< external trigger filter control */
#define TIMER_SMCFG_ETFC(x)            ((x) << TIMER_SMCFG_ETFC_Pos)
#define TIMER_SMCFG_ETFC_OFF           TIMER_SMCFG_ETFC(0)
#define TIMER_SMCFG_ETFC_DIV1_N2       TIMER_SMCFG_ETFC(1)
#define TIMER_SMCFG_ETFC_DIV1_N4       TIMER_SMCFG_ETFC(2)
#define TIMER_SMCFG_ETFC_DIV1_N8       TIMER_SMCFG_ETFC(3)
#define TIMER_SMCFG_ETFC_DIV2_N6       TIMER_SMCFG_ETFC(4)
#define TIMER_SMCFG_ETFC_DIV2_N8       TIMER_SMCFG_ETFC(5)
#define TIMER_SMCFG_ETFC_DIV4_N6       TIMER_SMCFG_ETFC(6)
#define TIMER_SMCFG_ETFC_DIV4_N8       TIMER_SMCFG_ETFC(7)
#define TIMER_SMCFG_ETFC_DIV8_N6       TIMER_SMCFG_ETFC(8)
#define TIMER_SMCFG_ETFC_DIV8_N8       TIMER_SMCFG_ETFC(9)
#define TIMER_SMCFG_ETFC_DIV16_N5      TIMER_SMCFG_ETFC(10)
#define TIMER_SMCFG_ETFC_DIV16_N6      TIMER_SMCFG_ETFC(11)
#define TIMER_SMCFG_ETFC_DIV16_N8      TIMER_SMCFG_ETFC(12)
#define TIMER_SMCFG_ETFC_DIV32_N5      TIMER_SMCFG_ETFC(13)
#define TIMER_SMCFG_ETFC_DIV32_N6      TIMER_SMCFG_ETFC(14)
#define TIMER_SMCFG_ETFC_DIV32_N8      TIMER_SMCFG_ETFC(15)
#define TIMER_SMCFG_MSM                _BIT(7,U)               /*!< master-slave mode */
#define TIMER_SMCFG_TRGS_Pos           4
#define TIMER_SMCFG_TRGS_Msk           _AC(0x00000070,U)       /*!< trigger selection */
#define TIMER_SMCFG_TRGS(x)            ((x) << TIMER_SMCFG_TRGS_Pos)
#define TIMER_SMCFG_TRGS_ITI0          TIMER_SMCFG_TRGS(0)     /*!< internal trigger 0 */
#define TIMER_SMCFG_TRGS_ITI1          TIMER_SMCFG_TRGS(1)     /*!< internal trigger 1 */
#define TIMER_SMCFG_TRGS_ITI2          TIMER_SMCFG_TRGS(2)     /*!< internal trigger 2 */
#define TIMER_SMCFG_TRGS_ITI3          TIMER_SMCFG_TRGS(3)     /*!< internal trigger 3 */
#define TIMER_SMCFG_TRGS_CI0F_ED       TIMER_SMCFG_TRGS(4)     /*!< TI0 Edge Detector */
#define TIMER_SMCFG_TRGS_CI0FE0        TIMER_SMCFG_TRGS(5)     /*!< filtered TIMER input 0 */
#define TIMER_SMCFG_TRGS_CI1FE1        TIMER_SMCFG_TRGS(6)     /*!< filtered TIMER input 1 */
#define TIMER_SMCFG_TRGS_ETIFP         TIMER_SMCFG_TRGS(7)     /*!< filtered external trigger input */
#define TIMER_SMCFG_SMC_Pos            0
#define TIMER_SMCFG_SMC_Msk            _AC(0x00000007,U)       /*!< slave mode control */
#define TIMER_SMCFG_SMC(x)             ((x) << TIMER_SMCFG_SMC_Pos)
#define TIMER_SMCFG_SMC_DISABLE        TIMER_SMCFG_SMC(0)      /*!< slave mode disable */
#define TIMER_SMCFG_SMC_ENCODER0       TIMER_SMCFG_SMC(1)      /*!< encoder mode 0 */
#define TIMER_SMCFG_SMC_ENCODER1       TIMER_SMCFG_SMC(2)      /*!< encoder mode 1 */
#define TIMER_SMCFG_SMC_ENCODER2       TIMER_SMCFG_SMC(3)      /*!< encoder mode 2 */
#define TIMER_SMCFG_SMC_RESTART        TIMER_SMCFG_SMC(4)      /*!< restart mode */
#define TIMER_SMCFG_SMC_PAUSE          TIMER_SMCFG_SMC(5)      /*!< pause mode */
#define TIMER_SMCFG_SMC_EVENT          TIMER_SMCFG_SMC(6)      /*!< event mode */
#define TIMER_SMCFG_SMC_EXTERNAL0      TIMER_SMCFG_SMC(7)      /*!< external clock mode 0 */

/* TIMER_DMAINTEN */
#define TIMER_DMAINTEN_TRGDEN          _BIT(14,U)              /*!< trigger DMA request enable */
#define TIMER_DMAINTEN_CMTDEN          _BIT(13,U)              /*!< commutation DMA request enable */
#define TIMER_DMAINTEN_CH3DEN          _BIT(12,U)              /*!< channel 3 capture/compare DMA request enable */
#define TIMER_DMAINTEN_CH2DEN          _BIT(11,U)              /*!< channel 2 capture/compare DMA request enable */
#define TIMER_DMAINTEN_CH1DEN          _BIT(10,U)              /*!< channel 1 capture/compare DMA request enable */
#define TIMER_DMAINTEN_CH0DEN          _BIT(9,U)               /*!< channel 0 capture/compare DMA request enable */
#define TIMER_DMAINTEN_UPDEN           _BIT(8,U)               /*!< update DMA request enable */
#define TIMER_DMAINTEN_BRKIE           _BIT(7,U)               /*!< break interrupt enable */
#define TIMER_DMAINTEN_TRGIE           _BIT(6,U)               /*!< trigger interrupt enable */
#define TIMER_DMAINTEN_CMTIE           _BIT(5,U)               /*!< commutation interrupt request enable */
#define TIMER_DMAINTEN_CH3IE           _BIT(4,U)               /*!< channel 3 capture/compare interrupt enable */
#define TIMER_DMAINTEN_CH2IE           _BIT(3,U)               /*!< channel 2 capture/compare interrupt enable */
#define TIMER_DMAINTEN_CH1IE           _BIT(2,U)               /*!< channel 1 capture/compare interrupt enable */
#define TIMER_DMAINTEN_CH0IE           _BIT(1,U)               /*!< channel 0 capture/compare interrupt enable */
#define TIMER_DMAINTEN_UPIE            _BIT(0,U)               /*!< update interrupt enable */

/* TIMER_INTF */
#define TIMER_INTF_CH3OF               _BIT(12,U)              /*!< channel 3 over capture flag */
#define TIMER_INTF_CH2OF               _BIT(11,U)              /*!< channel 2 over capture flag */
#define TIMER_INTF_CH1OF               _BIT(10,U)              /*!< channel 1 over capture flag */
#define TIMER_INTF_CH0OF               _BIT(9,U)               /*!< channel 0 over capture flag */
#define TIMER_INTF_BRKIF               _BIT(7,U)               /*!< break interrupt flag */
#define TIMER_INTF_TRGIF               _BIT(6,U)               /*!< trigger interrupt flag */
#define TIMER_INTF_CMTIF               _BIT(5,U)               /*!< channel commutation interrupt flag */
#define TIMER_INTF_CH3IF               _BIT(4,U)               /*!< channel 3 capture/compare interrupt flag */
#define TIMER_INTF_CH2IF               _BIT(3,U)               /*!< channel 2 capture/compare interrupt flag */
#define TIMER_INTF_CH1IF               _BIT(2,U)               /*!< channel 1 capture/compare interrupt flag */
#define TIMER_INTF_CH0IF               _BIT(1,U)               /*!< channel 0 capture/compare interrupt flag */
#define TIMER_INTF_UPIF                _BIT(0,U)               /*!< update interrupt flag */

/* TIMER_SWEVG */
#define TIMER_SWEVG_BRKG               _BIT(7,U)               /*!< break event generation */
#define TIMER_SWEVG_TRGG               _BIT(6,U)               /*!< trigger event generation */
#define TIMER_SWEVG_CMTG               _BIT(5,U)               /*!< channel commutation event generation */
#define TIMER_SWEVG_CH3G               _BIT(4,U)               /*!< channel 3 capture or compare event generation */
#define TIMER_SWEVG_CH2G               _BIT(3,U)               /*!< channel 2 capture or compare event generation */
#define TIMER_SWEVG_CH1G               _BIT(2,U)               /*!< channel 1 capture or compare event generation */
#define TIMER_SWEVG_CH0G               _BIT(1,U)               /*!< channel 0 capture or compare event generation */
#define TIMER_SWEVG_UPG                _BIT(0,U)               /*!< update event generate */

/* TIMER_CHCTL0 */
/* output compare mode */
#define TIMER_CHCTL0_CH1COMCEN         _BIT(15,U)              /*!< channel 1 output compare clear enable */
#define TIMER_CHCTL0_CH1COMCTL_Pos     12
#define TIMER_CHCTL0_CH1COMCTL_Msk     _AC(0x00007000,U)       /*!< channel 1 output compare control  */
#define TIMER_CHCTL0_CH1COMCTL(x)      ((x) << TIMER_CHCTL0_CH1COMCTL_Pos)
#define TIMER_CHCTL0_CH1COMSEN         _BIT(11,U)              /*!< channel 1 output compare shadow enable */
#define TIMER_CHCTL0_CH1COMFEN         _BIT(10,U)              /*!< channel 1 output compare fast enable */
#define TIMER_CHCTL0_CH1MS_Pos         8
#define TIMER_CHCTL0_CH1MS_Msk         _AC(0x00000300,U)       /*!< channel 1 mode selection */
#define TIMER_CHCTL0_CH1MS(x)          ((x) << TIMER_CHCTL0_CH1MS_Pos)
#define TIMER_CHCTL0_CH0COMCEN         _BIT(7,U)               /*!< channel 0 output compare clear enable */
#define TIMER_CHCTL0_CH0COMCTL_Pos     4
#define TIMER_CHCTL0_CH0COMCTL_Msk     _AC(0x00000070,U)       /*!< channel 0 output compare control  */
#define TIMER_CHCTL0_CH0COMCTL(x)      ((x) << TIMER_CHCTL0_CH0COMCTL_Pos)
#define TIMER_CHCTL0_CH0COMSEN         _BIT(3,U)               /*!< channel 0 output compare shadow enable */
#define TIMER_CHCTL0_CH0COMFEN         _BIT(2,U)               /*!< channel 0 output compare fast enable */
#define TIMER_CHCTL0_CH0MS_Pos         0
#define TIMER_CHCTL0_CH0MS_Msk         _AC(0x00000003,U)       /*!< channel 0 mode selection */
#define TIMER_CHCTL0_CH0MS(x)          ((x) << TIMER_CHCTL0_CH0MS_Pos)
/* input capture mode */
#define TIMER_CHCTL0_CH1CAPFLT_Pos     12
#define TIMER_CHCTL0_CH1CAPFLT_Msk     _AC(0x0000f000,U)       /*!< channel 1 input capture filter control */
#define TIMER_CHCTL0_CH1CAPFLT(x)      ((x) << TIMER_CHCTL0_CH1CAPFLT_Pos)
#define TIMER_CHCTL0_CH1CAPPSC_Pos     10
#define TIMER_CHCTL0_CH1CAPPSC_Msk     _AC(0x00000c00,U)       /*!< channel 1 input capture prescaler */
#define TIMER_CHCTL0_CH1CAPPSC(x)      ((x) << TIMER_CHCTL0_CH1CAPPSC_Pos)
#define TIMER_CHCTL0_CH0CAPFLT_Pos     4
#define TIMER_CHCTL0_CH0CAPFLT_Msk     _AC(0x000000f0,U)       /*!< channel 0 input capture filter control */
#define TIMER_CHCTL0_CH0CAPFLT(x)      ((x) << TIMER_CHCTL0_CH0CAPFLT_Pos)
#define TIMER_CHCTL0_CH0CAPPSC_Pos     2
#define TIMER_CHCTL0_CH0CAPPSC_Msk     _AC(0x0000000c,U)       /*!< channel 0 input capture prescaler */
#define TIMER_CHCTL0_CH0CAPPSC(x)      ((x) << TIMER_CHCTL0_CH0CAPPSC_Pos)

/* TIMER_CHCTL1 */
/* output compare mode */
#define TIMER_CHCTL1_CH3COMCEN         _BIT(15,U)              /*!< channel 3 output compare clear enable */
#define TIMER_CHCTL1_CH3COMCTL_Pos     12
#define TIMER_CHCTL1_CH3COMCTL_Msk     _AC(0x00007000,U)       /*!< channel 3 output compare control */
#define TIMER_CHCTL1_CH3COMCTL(x)      ((x) << TIMER_CHCTL1_CH3COMCTL_Pos)
#define TIMER_CHCTL1_CH3COMSEN         _BIT(11,U)              /*!< channel 3 output compare shadow enable */
#define TIMER_CHCTL1_CH3COMFEN         _BIT(10,U)              /*!< channel 3 output compare fast enable */
#define TIMER_CHCTL1_CH3MS_Pos         8
#define TIMER_CHCTL1_CH3MS_Msk         _AC(0x00000300,U)       /*!< channel 3 mode selection */
#define TIMER_CHCTL1_CH3MS(x)          ((x) << TIMER_CHCTL1_CH3MS_Pos)
#define TIMER_CHCTL1_CH2COMCEN         _BIT(7,U)               /*!< channel 2 output compare clear enable */
#define TIMER_CHCTL1_CH2COMCTL_Pos     4
#define TIMER_CHCTL1_CH2COMCTL_Msk     _AC(0x00000070,U)       /*!< channel 2 output compare control */
#define TIMER_CHCTL1_CH2COMCTL(x)      ((x) << TIMER_CHCTL1_CH2COMCTL_Pos)
#define TIMER_CHCTL1_CH2COMSEN         _BIT(3,U)               /*!< channel 2 output compare shadow enable */
#define TIMER_CHCTL1_CH2COMFEN         _BIT(2,U)               /*!< channel 2 output compare fast enable */
#define TIMER_CHCTL1_CH2MS_Pos         0
#define TIMER_CHCTL1_CH2MS_Msk         _AC(0x00000003,U)       /*!< channel 2 mode selection */
#define TIMER_CHCTL1_CH2MS(x)          ((x) << TIMER_CHCTL1_CH2MS_Pos)
/* input capture mode */
#define TIMER_CHCTL1_CH3CAPFLT_Pos     12
#define TIMER_CHCTL1_CH3CAPFLT_Msk     _AC(0x0000f000,U)       /*!< channel 3 input capture filter control */
#define TIMER_CHCTL1_CH3CAPFLT(x)      ((x) << TIMER_CHCTL1_CH3CAPFLT_Pos)
#define TIMER_CHCTL1_CH3CAPPSC_Pos     10
#define TIMER_CHCTL1_CH3CAPPSC_Msk     _AC(0x00000c00,U)       /*!< channel 3 input capture prescaler */
#define TIMER_CHCTL1_CH3CAPPSC(x)      ((x) << TIMER_CHCTL1_CH3CAPPSC_Pos)
#define TIMER_CHCTL1_CH2CAPFLT_Pos     4
#define TIMER_CHCTL1_CH2CAPFLT_Msk     _AC(0x000000f0,U)       /*!< channel 2 input capture filter control */
#define TIMER_CHCTL1_CH2CAPFLT(x)      ((x) << TIMER_CHCTL1_CH2CAPFLT_Pos)
#define TIMER_CHCTL1_CH2CAPPSC_Pos     2
#define TIMER_CHCTL1_CH2CAPPSC_Msk     _AC(0x0000000c,U)       /*!< channel 2 input capture prescaler */
#define TIMER_CHCTL1_CH2CAPPSC(x)      ((x) << TIMER_CHCTL1_CH2CAPPSC_Pos)

/* TIMER_CHCTL2 */
#define TIMER_CHCTL2_CH3P              _BIT(13,U)              /*!< channel 3 capture/compare function polarity */
#define TIMER_CHCTL2_CH3EN             _BIT(12,U)              /*!< channel 3 capture/compare function enable  */
#define TIMER_CHCTL2_CH2NP             _BIT(11,U)              /*!< channel 2 complementary output polarity */
#define TIMER_CHCTL2_CH2NEN            _BIT(10,U)              /*!< channel 2 complementary output enable */
#define TIMER_CHCTL2_CH2P              _BIT(9,U)               /*!< channel 2 capture/compare function polarity */
#define TIMER_CHCTL2_CH2EN             _BIT(8,U)               /*!< channel 2 capture/compare function enable  */
#define TIMER_CHCTL2_CH1NP             _BIT(7,U)               /*!< channel 1 complementary output polarity */
#define TIMER_CHCTL2_CH1NEN            _BIT(6,U)               /*!< channel 1 complementary output enable */
#define TIMER_CHCTL2_CH1P              _BIT(5,U)               /*!< channel 1 capture/compare function polarity */
#define TIMER_CHCTL2_CH1EN             _BIT(4,U)               /*!< channel 1 capture/compare function enable  */
#define TIMER_CHCTL2_CH0NP             _BIT(3,U)               /*!< channel 0 complementary output polarity */
#define TIMER_CHCTL2_CH0NEN            _BIT(2,U)               /*!< channel 0 complementary output enable */
#define TIMER_CHCTL2_CH0P              _BIT(1,U)               /*!< channel 0 capture/compare function polarity */
#define TIMER_CHCTL2_CH0EN             _BIT(0,U)               /*!< channel 0 capture/compare function enable */

/* TIMER_CNT */
#define TIMER_CNT_CNT_Pos              0
#define TIMER_CNT_CNT_Msk              _AC(0x0000ffff,U)       /*!< 16 bit timer counter */
#define TIMER_CNT_CNT(x)               ((x) << TIMER_CNT_CNT_Pos)

/* TIMER_PSC */
#define TIMER_PSC_PSC_Pos              0
#define TIMER_PSC_PSC_Msk              _AC(0x0000ffff,U)       /*!< prescaler value of the counter clock */
#define TIMER_PSC_PSC(x)               ((x) << TIMER_PSC_PSC_Pos)

/* TIMER_CAR */
#define TIMER_CAR_CARL_Pos             0
#define TIMER_CAR_CARL_Msk             _AC(0x0000ffff,U)       /*!< 16 bit counter auto reload value */
#define TIMER_CAR_CARL(x)              ((x) << TIMER_CAR_CARL_Pos)

/* TIMER_CREP */
#define TIMER_CREP_CREP_Pos            0
#define TIMER_CREP_CREP_Msk            _AC(0x000000ff,U)       /*!< counter repetition value */
#define TIMER_CREP_CREP(x)             ((x) << TIMER_CREP_CREP_Pos)

/* TIMER_CH0CV */
#define TIMER_CH0CV_CH0VAL_Pos         0
#define TIMER_CH0CV_CH0VAL_Msk         _AC(0x0000ffff,U)       /*!< 16 bit capture/compare value of channel 0 */
#define TIMER_CH0CV_CH0VAL(x)          ((x) << TIMER_CH0CV_CH0VAL_Pos)

/* TIMER_CH1CV */
#define TIMER_CH1CV_CH1VAL_Pos         0
#define TIMER_CH1CV_CH1VAL_Msk         _AC(0x0000ffff,U)       /*!< 16 bit capture/compare value of channel 1 */
#define TIMER_CH1CV_CH1VAL(x)          ((x) << TIMER_CH1CV_CH1VAL_Pos)

/* TIMER_CH2CV */
#define TIMER_CH2CV_CH2VAL_Pos         0
#define TIMER_CH2CV_CH2VAL_Msk         _AC(0x0000ffff,U)       /*!< 16 bit capture/compare value of channel 2 */
#define TIMER_CH2CV_CH2VAL(x)          ((x) << TIMER_CH2CV_CH2VAL_Pos)

/* TIMER_CH3CV */
#define TIMER_CH3CV_CH3VAL_Pos         0
#define TIMER_CH3CV_CH3VAL_Msk         _AC(0x0000ffff,U)       /*!< 16 bit capture/compare value of channel 3 */
#define TIMER_CH3CV_CH3VAL(x)          ((x) << TIMER_CH3CV_CH3VAL_Pos)

/* TIMER_CCHP */
#define TIMER_CCHP_POEN                _BIT(15,U)              /*!< primary output enable */
#define TIMER_CCHP_OAEN                _BIT(14,U)              /*!< output automatic enable */
#define TIMER_CCHP_BRKP                _BIT(13,U)              /*!< break polarity */
#define TIMER_CCHP_BRKEN               _BIT(12,U)              /*!< break enable */
#define TIMER_CCHP_ROS                 _BIT(11,U)              /*!< run mode off-state configure */
#define TIMER_CCHP_IOS                 _BIT(10,U)              /*!< idle mode off-state configure */
#define TIMER_CCHP_PROT_Pos            8
#define TIMER_CCHP_PROT_Msk            _AC(0x00000300,U)       /*!< complementary register protect control */
#define TIMER_CCHP_PROT(x)             ((x) << TIMER_CCHP_PROT_Pos)
#define TIMER_CCHP_PROT_OFF            TIMER_CCHP_PROT(0)      /*!< protect disable */
#define TIMER_CCHP_PROT_0              TIMER_CCHP_PROT(1)      /*!< PROT mode 0 */
#define TIMER_CCHP_PROT_1              TIMER_CCHP_PROT(2)      /*!< PROT mode 1 */
#define TIMER_CCHP_PROT_2              TIMER_CCHP_PROT(3)      /*!< PROT mode 2 */
#define TIMER_CCHP_DTCFG_Pos           0
#define TIMER_CCHP_DTCFG_Msk           _AC(0x000000ff,U)       /*!< dead time configure */
#define TIMER_CCHP_DTCFG(x)            ((x) << TIMER_CCHP_DTCFG_Pos)

/* TIMER_DMACFG */
#define TIMER_DMACFG_DMATC_Pos         8
#define TIMER_DMACFG_DMATC_Msk         _AC(0x00000f00,U)       /*!< DMA transfer count */
#define TIMER_DMACFG_DMATC(x)          ((x) << TIMER_DMACFG_DMATC_Pos)
#define TIMER_DMACFG_DMATC_1TRANSFER   TIMER_DMACFG_DMATC(0)   /*!< DMA transfer 1 time */
#define TIMER_DMACFG_DMATC_2TRANSFER   TIMER_DMACFG_DMATC(1)   /*!< DMA transfer 2 times */
#define TIMER_DMACFG_DMATC_3TRANSFER   TIMER_DMACFG_DMATC(2)   /*!< DMA transfer 3 times */
#define TIMER_DMACFG_DMATC_4TRANSFER   TIMER_DMACFG_DMATC(3)   /*!< DMA transfer 4 times */
#define TIMER_DMACFG_DMATC_5TRANSFER   TIMER_DMACFG_DMATC(4)   /*!< DMA transfer 5 times */
#define TIMER_DMACFG_DMATC_6TRANSFER   TIMER_DMACFG_DMATC(5)   /*!< DMA transfer 6 times */
#define TIMER_DMACFG_DMATC_7TRANSFER   TIMER_DMACFG_DMATC(6)   /*!< DMA transfer 7 times */
#define TIMER_DMACFG_DMATC_8TRANSFER   TIMER_DMACFG_DMATC(7)   /*!< DMA transfer 8 times */
#define TIMER_DMACFG_DMATC_9TRANSFER   TIMER_DMACFG_DMATC(8)   /*!< DMA transfer 9 times */
#define TIMER_DMACFG_DMATC_10TRANSFER  TIMER_DMACFG_DMATC(9)   /*!< DMA transfer 10 times */
#define TIMER_DMACFG_DMATC_11TRANSFER  TIMER_DMACFG_DMATC(10)  /*!< DMA transfer 11 times */
#define TIMER_DMACFG_DMATC_12TRANSFER  TIMER_DMACFG_DMATC(11)  /*!< DMA transfer 12 times */
#define TIMER_DMACFG_DMATC_13TRANSFER  TIMER_DMACFG_DMATC(12)  /*!< DMA transfer 13 times */
#define TIMER_DMACFG_DMATC_14TRANSFER  TIMER_DMACFG_DMATC(13)  /*!< DMA transfer 14 times */
#define TIMER_DMACFG_DMATC_15TRANSFER  TIMER_DMACFG_DMATC(14)  /*!< DMA transfer 15 times */
#define TIMER_DMACFG_DMATC_16TRANSFER  TIMER_DMACFG_DMATC(15)  /*!< DMA transfer 16 times */
#define TIMER_DMACFG_DMATC_17TRANSFER  TIMER_DMACFG_DMATC(16)  /*!< DMA transfer 17 times */
#define TIMER_DMACFG_DMATC_18TRANSFER  TIMER_DMACFG_DMATC(17)  /*!< DMA transfer 18 times */
#define TIMER_DMACFG_DMATA_Pos         0
#define TIMER_DMACFG_DMATA_Msk         _AC(0x0000000f,U)       /*!< DMA transfer access start address */
#define TIMER_DMACFG_DMATA(x)          ((x) << TIMER_DMACFG_DMATA_Pos)
#define TIMER_DMACFG_DMATA_CTL0        TIMER_DMACFG_DMATA(0)   /*!< DMA transfer address is TIMER_CTL0 */
#define TIMER_DMACFG_DMATA_CTL1        TIMER_DMACFG_DMATA(1)   /*!< DMA transfer address is TIMER_CTL1 */
#define TIMER_DMACFG_DMATA_SMCFG       TIMER_DMACFG_DMATA(2)   /*!< DMA transfer address is TIMER_SMCFG */
#define TIMER_DMACFG_DMATA_DMAINTEN    TIMER_DMACFG_DMATA(3)   /*!< DMA transfer address is TIMER_DMAINTEN */
#define TIMER_DMACFG_DMATA_INTF        TIMER_DMACFG_DMATA(4)   /*!< DMA transfer address is TIMER_INTF */
#define TIMER_DMACFG_DMATA_SWEVG       TIMER_DMACFG_DMATA(5)   /*!< DMA transfer address is TIMER_SWEVG */
#define TIMER_DMACFG_DMATA_CHCTL0      TIMER_DMACFG_DMATA(6)   /*!< DMA transfer address is TIMER_CHCTL0 */
#define TIMER_DMACFG_DMATA_CHCTL1      TIMER_DMACFG_DMATA(7)   /*!< DMA transfer address is TIMER_CHCTL1 */
#define TIMER_DMACFG_DMATA_CHCTL2      TIMER_DMACFG_DMATA(8)   /*!< DMA transfer address is TIMER_CHCTL2 */
#define TIMER_DMACFG_DMATA_CNT         TIMER_DMACFG_DMATA(9)   /*!< DMA transfer address is TIMER_CNT */
#define TIMER_DMACFG_DMATA_PSC         TIMER_DMACFG_DMATA(10)  /*!< DMA transfer address is TIMER_PSC */
#define TIMER_DMACFG_DMATA_CAR         TIMER_DMACFG_DMATA(11)  /*!< DMA transfer address is TIMER_CAR */
#define TIMER_DMACFG_DMATA_CREP        TIMER_DMACFG_DMATA(12)  /*!< DMA transfer address is TIMER_CREP */
#define TIMER_DMACFG_DMATA_CH0CV       TIMER_DMACFG_DMATA(13)  /*!< DMA transfer address is TIMER_CH0CV */
#define TIMER_DMACFG_DMATA_CH1CV       TIMER_DMACFG_DMATA(14)  /*!< DMA transfer address is TIMER_CH1CV */
#define TIMER_DMACFG_DMATA_CH2CV       TIMER_DMACFG_DMATA(15)  /*!< DMA transfer address is TIMER_CH2CV */
#define TIMER_DMACFG_DMATA_CH3CV       TIMER_DMACFG_DMATA(16)  /*!< DMA transfer address is TIMER_CH3CV */
#define TIMER_DMACFG_DMATA_CCHP        TIMER_DMACFG_DMATA(17)  /*!< DMA transfer address is TIMER_CCHP */
#define TIMER_DMACFG_DMATA_DMACFG      TIMER_DMACFG_DMATA(18)  /*!< DMA transfer address is TIMER_DMACFG */

/* TIMER_DMATB */
#define TIMER_DMATB_DMATB_Pos          0
#define TIMER_DMATB_DMATB_Msk          _AC(0x0000ffff,U)       /*!< DMA transfer buffer address */
#define TIMER_DMATB_DMATB(x)           ((x) << TIMER_DMATB_DMATB_Pos)

/* --------------------- UART/USART -------------------------- */

#define USART0_BASE                    _AC(0x40013800,UL)  /*!< USART0 base address */
#define USART1_BASE                    _AC(0x40004400,UL)  /*!< USART1 base address */
#if defined(GD32VF103C8T6) || defined(GD32VF103CBT6) || defined(GD32VF103R8T6) || \
    defined(GD32VF103RBT6) || defined(GD32VF103V8T6) || defined(GD32VF103VBT6)
    #define USART2_BASE                _AC(0x40004800,UL)  /*!< USART2 base address */
#endif
#if defined(GD32VF103R8T6) || defined(GD32VF103RBT6) || \
    defined(GD32VF103V8T6) || defined(GD32VF103VBT6)
    #define UART3_BASE                 _AC(0x40004C00,UL)  /*!< UART3 base address  */
    #define UART4_BASE                 _AC(0x40005000,UL)  /*!< UART4 base address  */
#endif

/* register definitions */
#define USART_STAT                     _AC(0x00,UL)  /*!< USART status register */
#define USART_DATA                     _AC(0x04,UL)  /*!< USART data register */
#define USART_BAUD                     _AC(0x08,UL)  /*!< USART baud rate register */
#define USART_CTL0                     _AC(0x0C,UL)  /*!< USART control register 0 */
#define USART_CTL1                     _AC(0x10,UL)  /*!< USART control register 1 */
#define USART_CTL2                     _AC(0x14,UL)  /*!< USART control register 2 */
#define USART_GP                       _AC(0x18,UL)  /*!< USART guard time and prescaler register */

/* USARTx_STAT */
#define USART_STAT_CTSF                _BIT(9,U)          /*!< CTS change flag */
#define USART_STAT_LBDF                _BIT(8,U)          /*!< LIN break detected flag */
#define USART_STAT_TBE                 _BIT(7,U)          /*!< transmit data buffer empty */
#define USART_STAT_TC                  _BIT(6,U)          /*!< transmission complete */
#define USART_STAT_RBNE                _BIT(5,U)          /*!< read data buffer not empty */
#define USART_STAT_IDLEF               _BIT(4,U)          /*!< IDLE frame detected flag */
#define USART_STAT_ORERR               _BIT(3,U)          /*!< overrun error */
#define USART_STAT_NERR                _BIT(2,U)          /*!< noise error flag */
#define USART_STAT_FERR                _BIT(1,U)          /*!< frame error flag */
#define USART_STAT_PERR                _BIT(0,U)          /*!< parity error flag */

/* USARTx_DATA */
#define USART_DATA_DATA_Pos            0
#define USART_DATA_DATA_Msk            _AC(0x000000ff,U)  /*!< transmit or read data value */
#define USART_DATA_DATA(x)             ((x) << USART_DATA_DATA_Pos)

/* USARTx_BAUD */
#define USART_BAUD_INTDIV_Pos          4
#define USART_BAUD_INTDIV_Msk          _AC(0x0000fff0,U)  /*!< integer part of baud-rate divider */
#define USART_BAUD_INTDIV(x)           ((x) << USART_BAUD_INTDIV_Pos)
#define USART_BAUD_FRADIV_Pos          0
#define USART_BAUD_FRADIV_Msk          _AC(0x0000000f,U)  /*!< fraction part of baud-rate divider */
#define USART_BAUD_FRADIV(x)           ((x) << USART_BAUD_FRADIV_Pos)

/* USARTx_CTL0 */
#define USART_CTL0_UEN                 _BIT(13,U)         /*!< USART enable */
#define USART_CTL0_WL                  _BIT(12,U)         /*!< word length */
#define USART_CTL0_WM                  _BIT(11,U)         /*!< wakeup method in mute mode */
#define USART_CTL0_PCEN                _BIT(10,U)         /*!< parity check function enable */
#define USART_CTL0_PM                  _BIT(9,U)          /*!< parity mode */
#define USART_CTL0_PERRIE              _BIT(8,U)          /*!< parity error interrupt enable */
#define USART_CTL0_TBEIE               _BIT(7,U)          /*!< transmitter buffer empty interrupt enable */
#define USART_CTL0_TCIE                _BIT(6,U)          /*!< transmission complete interrupt enable */
#define USART_CTL0_RBNEIE              _BIT(5,U)          /*!< read data buffer not empty interrupt and overrun error interrupt enable */
#define USART_CTL0_IDLEIE              _BIT(4,U)          /*!< idle line detected interrupt enable */
#define USART_CTL0_TEN                 _BIT(3,U)          /*!< transmitter enable */
#define USART_CTL0_REN                 _BIT(2,U)          /*!< receiver enable */
#define USART_CTL0_RWU                 _BIT(1,U)          /*!< receiver wakeup from mute mode */
#define USART_CTL0_SBKCMD              _BIT(0,U)          /*!< send break command */

/* USARTx_CTL1 */
#define USART_CTL1_LMEN                _BIT(14,U)         /*!< LIN mode enable */
#define USART_CTL1_STB_Pos             12
#define USART_CTL1_STB_Msk             _AC(0x00000c00,U)  /*!< STOP bits length */
#define USART_CTL1_STB(x)              ((x) << USART_CTL1_STB_Pos)
#define USART_CTL1_STB_1               USART_CTL1_STB(0)  /*!< 1 bit */
#define USART_CTL1_STB_0_5             USART_CTL1_STB(1)  /*!< 0.5 bit */
#define USART_CTL1_STB_2               USART_CTL1_STB(2)  /*!< 2 bits */
#define USART_CTL1_STB_1_5             USART_CTL1_STB(3)  /*!< 1.5 bits */
#define USART_CTL1_CKEN                _BIT(11,U)         /*!< CK pin enable */
#define USART_CTL1_CPL                 _BIT(10,U)         /*!< CK polarity */
#define USART_CTL1_CPH                 _BIT(9,U)          /*!< CK phase */
#define USART_CTL1_CLEN                _BIT(8,U)          /*!< CK length */
#define USART_CTL1_LBDIE               _BIT(6,U)          /*!< LIN break detected interrupt eanble */
#define USART_CTL1_LBLEN               _BIT(5,U)          /*!< LIN break frame length */
#define USART_CTL1_ADDR_Pos            0
#define USART_CTL1_ADDR_Msk            _AC(0x0000000f,U)  /*!< address of USART */
#define USART_CTL1_ADDR(x)             ((x) << USART_CTL1_ADDR_Pos)

/* USARTx_CTL2 */
#define USART_CTL2_CTSIE               _BIT(10,U)         /*!< CTS interrupt enable */
#define USART_CTL2_CTSEN               _BIT(9,U)          /*!< CTS enable */
#define USART_CTL2_RTSEN               _BIT(8,U)          /*!< RTS enable */
#define USART_CTL2_DENT                _BIT(7,U)          /*!< DMA request enable for transmission */
#define USART_CTL2_DENR                _BIT(6,U)          /*!< DMA request enable for reception */
#define USART_CTL2_SCEN                _BIT(5,U)          /*!< smartcard mode enable */
#define USART_CTL2_NKEN                _BIT(4,U)          /*!< NACK enable in smartcard mode */
#define USART_CTL2_HDEN                _BIT(3,U)          /*!< half-duplex enable */
#define USART_CTL2_IRLP                _BIT(2,U)          /*!< IrDA low-power */
#define USART_CTL2_IREN                _BIT(1,U)          /*!< IrDA mode enable */
#define USART_CTL2_ERRIE               _BIT(0,U)          /*!< error interrupt enable */

/* USARTx_GP */
#define USART_GP_GUAT_Pos              8
#define USART_GP_GUAT_Msk              _AC(0x0000ff00,U)  /*!< guard time value in smartcard mode */
#define USART_GP_GUAT(x)               ((x) << USART_GP_GUAT_Pos)
#define USART_GP_PSC_Pos               0
#define USART_GP_PSC_Msk               _AC(0x000000ff,U)  /*!< prescaler value for dividing the system clock */
#define USART_GP_PSC(x)                ((x) << USART_GP_PSC_Pos)

/* --------------------- USBFS -------------------------- */

#define USBFS_BASE                     _AC(0x50000000,UL)  /*!< USBFS base address */

/* limits */
#define USBFS_MAX_TX_FIFOS             15          /*!< FIFO number */
#define USBFS_MAX_PACKET_SIZE          _AC(64,U)   /*!< USBFS max packet size */
#define USBFS_MAX_CHANNEL_COUNT        _AC(8,U)    /*!< USBFS host channel count */
#define USBFS_MAX_EP_COUNT             _AC(4,U)    /*!< USBFS device endpoint count */
#define USBFS_MAX_FIFO_WORDLEN         _AC(320,U)  /*!< USBFS max fifo size in words */

/* register definitions */
#define USBFS_GOTGCS                   _AC(0x000,UL)  /*!< USBFS global OTG control and status register */
#define USBFS_GOTGINTF                 _AC(0x004,UL)  /*!< USBFS global OTG interrupt flag register */
#define USBFS_GAHBCS                   _AC(0x008,UL)  /*!< USBFS global AHB control and status register */
#define USBFS_GUSBCS                   _AC(0x00C,UL)  /*!< USBFS global USB control and status register */
#define USBFS_GRSTCTL                  _AC(0x010,UL)  /*!< USBFS global reset control register */
#define USBFS_GINTF                    _AC(0x014,UL)  /*!< USBFS global interrupt flag register */
#define USBFS_GINTEN                   _AC(0x018,UL)  /*!< USBFS global interrupt enable register */
#define USBFS_GRSTATR                  _AC(0x01C,UL)  /*!< USBFS receive status debug read register */
#define USBFS_GRSTATP                  _AC(0x020,UL)  /*!< USBFS receive status and pop register */
#define USBFS_GRFLEN                   _AC(0x024,UL)  /*!< USBFS global receive FIFO length register */
#define USBFS_DIEP0TFLEN_HNPTFLEN      _AC(0x028,UL)  /*!< USBFS device IN endpoint 0/host non-periodic transmit FIFO length register */
#define USBFS_HNPTFLEN                 _AC(0x028,UL)
#define USBFS_DIEP0TFLEN               _AC(0x028,UL)
#define USBFS_HNPTFQSTAT               _AC(0x02C,UL)  /*!< USBFS host non-periodic FIFO/queue status register */
#define USBFS_GCCFG                    _AC(0x038,UL)  /*!< USBFS global core configuration register */
#define USBFS_CID                      _AC(0x03C,UL)  /*!< USBFS core ID register */
#define USBFS_HPTFLEN                  _AC(0x100,UL)  /*!< USBFS host periodic transmit FIFO length register */
#define USBFS_DIEP1TFLEN               _AC(0x104,UL)  /*!< USBFS device IN endpoint 1 transmit FIFO length register */
#define USBFS_DIEP2TFLEN               _AC(0x108,UL)  /*!< USBFS device IN endpoint 2 transmit FIFO length register */
#define USBFS_DIEP3TFLEN               _AC(0x10C,UL)  /*!< USBFS device IN endpoint 3 transmit FIFO length register */
#define USBFS_DIEPTFLEN(x)             (_AC(0x104,UL) + (4*((x) - 1)))  /*!< USBFS device IN endpoint transmit FIFO length register */

#define USBFS_HCTL                     _AC(0x400,UL)  /*!< USB host control register                             */
#define USBFS_HFT                      _AC(0x404,UL)  /*!< USB host frame interval register                      */
#define USBFS_HFINFR                   _AC(0x408,UL)  /*!< USB host frame information remaining register         */
#define USBFS_HPTFQSTAT                _AC(0x410,UL)  /*!< USB host periodic transmit FIFO/queue status register */
#define USBFS_HACHINT                  _AC(0x414,UL)  /*!< USB host all channels interrupt register              */
#define USBFS_HACHINTEN                _AC(0x418,UL)  /*!< USB host all channels interrupt enable register       */

#define USBFS_HPCS                     _AC(0x440,UL)  /*!< USB host port control and status register */

#define USBFS_HCHCTL(x)                (_AC(0x500,UL) + ((x) * _AC(20,UL)))  /*!< USB host channel control register          */
#define USBFS_HCHINTF(x)               (_AC(0x508,UL) + ((x) + _AC(20,UL)))  /*!< USB host channel interrupt flag register   */
#define USBFS_HCHINTEN(x)              (_AC(0x50C,UL) + ((x) + _AC(20,UL)))  /*!< USB host channel interrupt enable register */
#define USBFS_HCHLEN(x)                (_AC(0x510,UL) + ((x) + _AC(20,UL)))  /*!< USB host channel transfer length register  */

#define USBFS_DCFG                     _AC(0x800,UL)  /*!< USB device configuration register                           */
#define USBFS_DCTL                     _AC(0x804,UL)  /*!< USB device control register                                 */
#define USBFS_DSTAT                    _AC(0x808,UL)  /*!< USB device status register                                  */
#define USBFS_DIEPINTEN                _AC(0x810,UL)  /*!< USB device IN endpoint common interrupt enable register     */
#define USBFS_DOEPINTEN                _AC(0x814,UL)  /*!< USB device OUT endpoint common interrupt enable register    */
#define USBFS_DAEPINT                  _AC(0x818,UL)  /*!< USB device all endpoints interrupt register                 */
#define USBFS_DAEPINTEN                _AC(0x81C,UL)  /*!< USB device all endpoints interrupt enable register          */
#define USBFS_DVBUSDT                  _AC(0x828,UL)  /*!< USB device VBUS discharge time register                     */
#define USBFS_DVBUSPT                  _AC(0x82C,UL)  /*!< USB device VBUS pulsing time register                       */
#define USBFS_DIEPFEINTEN              _AC(0x834,UL)  /*!< USB device IN endpoint FIFO empty interrupt enable register */

#define USBFS_DIEPCTL(x)               (_AC(0x900,UL) + (_AC(20,UL) * (x)))  /*!< USB device IN endpoint control register              */
#define USBFS_DIEPINTF(x)              (_AC(0x908,UL) + (_AC(20,UL) * (x)))  /*!< USB device IN endpoint interrupt flag register       */
#define USBFS_DIEPLEN(x)               (_AC(0x910,UL) + (_AC(20,UL) * (x)))  /*!< USB device IN endpoint transfer length register      */
#define USBFS_DIEPTFSTAT(x)            (_AC(0x918,UL) + (_AC(20,UL) * (x)))  /*!< USB device IN endpoint transmit FIFO status register */
#define USBFS_DIEP0CTL                 _AC(0x900,UL)  /*!< USB device IN endpoint 0 control register              */
#define USBFS_DIEP0INTF                _AC(0x908,UL)  /*!< USB device IN endpoint 0 interrupt flag register       */
#define USBFS_DIEP0LEN                 _AC(0x910,UL)  /*!< USB device IN endpoint 0 transfer length register      */
#define USBFS_DIEP0TFSTAT              _AC(0x918,UL)  /*!< USB device IN endpoint 0 transmit FIFO status register */
#define USBFS_DIEP1CTL                 _AC(0x920,UL)  /*!< USB device IN endpoint 1 control register              */
#define USBFS_DIEP1INTF                _AC(0x928,UL)  /*!< USB device IN endpoint 1 interrupt flag register       */
#define USBFS_DIEP1LEN                 _AC(0x930,UL)  /*!< USB device IN endpoint 1 transfer length register      */
#define USBFS_DIEP1TFSTAT              _AC(0x938,UL)  /*!< USB device IN endpoint 1 transmit FIFO status register */
#define USBFS_DIEP2CTL                 _AC(0x940,UL)  /*!< USB device IN endpoint 2 control register              */
#define USBFS_DIEP2INTF                _AC(0x948,UL)  /*!< USB device IN endpoint 2 interrupt flag register       */
#define USBFS_DIEP2LEN                 _AC(0x950,UL)  /*!< USB device IN endpoint 2 transfer length register      */
#define USBFS_DIEP2TFSTAT              _AC(0x958,UL)  /*!< USB device IN endpoint 2 transmit FIFO status register */
#define USBFS_DIEP3CTL                 _AC(0x960,UL)  /*!< USB device IN endpoint 3 control register              */
#define USBFS_DIEP3INTF                _AC(0x968,UL)  /*!< USB device IN endpoint 3 interrupt flag register       */
#define USBFS_DIEP3LEN                 _AC(0x970,UL)  /*!< USB device IN endpoint 3 transfer length register      */
#define USBFS_DIEP3TFSTAT              _AC(0x978,UL)  /*!< USB device IN endpoint 3 transmit FIFO status register */

#define USBFS_DOEPCTL(x)               (_AC(0xB00,UL) + (_AC(20,UL) * (x)))  /*!< USB device IN endpoint control register         */
#define USBFS_DOEPINTF(x)              (_AC(0xB08,UL) + (_AC(20,UL) * (x)))  /*!< USB device IN endpoint interrupt flag register  */
#define USBFS_DOEPLEN(x)               (_AC(0xB10,UL) + (_AC(20,UL) * (x)))  /*!< USB device IN endpoint transfer length register */
#define USBFS_DOEP0CTL                 _AC(0xB00,UL)  /*!< USB device IN endpoint 0 control register         */
#define USBFS_DOEP0INTF                _AC(0xB08,UL)  /*!< USB device IN endpoint 0 interrupt flag register  */
#define USBFS_DOEP0LEN                 _AC(0xB10,UL)  /*!< USB device IN endpoint 0 transfer length register */
#define USBFS_DOEP1CTL                 _AC(0xB20,UL)  /*!< USB device IN endpoint 1 control register         */
#define USBFS_DOEP1INTF                _AC(0xB28,UL)  /*!< USB device IN endpoint 1 interrupt flag register  */
#define USBFS_DOEP1LEN                 _AC(0xB30,UL)  /*!< USB device IN endpoint 1 transfer length register */
#define USBFS_DOEP2CTL                 _AC(0xB40,UL)  /*!< USB device IN endpoint 2 control register         */
#define USBFS_DOEP2INTF                _AC(0xB48,UL)  /*!< USB device IN endpoint 2 interrupt flag register  */
#define USBFS_DOEP2LEN                 _AC(0xB50,UL)  /*!< USB device IN endpoint 2 transfer length register */
#define USBFS_DOEP3CTL                 _AC(0xB60,UL)  /*!< USB device IN endpoint 3 control register         */
#define USBFS_DOEP3INTF                _AC(0xB68,UL)  /*!< USB device IN endpoint 3 interrupt flag register  */
#define USBFS_DOEP3LEN                 _AC(0xB70,UL)  /*!< USB device IN endpoint 3 transfer length register */

#define USBFS_PWRCLKCTL                _AC(0xE00,UL)  /*!< USB power and clock control register */

#define USBFS_DATA_FIFO_OFFSET         _AC(0x1000,UL)  /*!< USB data fifo offset */
#define USBFS_DATA_FIFO_SIZE           _AC(0x1000,UL)  /*!< USB data fifo size */

/* USBFS_GOTGCS */
#define USBFS_GOTGCS_BSV               _BIT(19,U)           /*!< B-Session Valid */
#define USBFS_GOTGCS_ASV               _BIT(18,U)           /*!< A-session valid */
#define USBFS_GOTGCS_DI                _BIT(17,U)           /*!< debounce interval */
#define USBFS_GOTGCS_CIDPS             _BIT(16,U)           /*!< id pin status */
#define USBFS_GOTGCS_DHNPEN            _BIT(11,U)           /*!< device HNP enable */
#define USBFS_GOTGCS_HHNPEN            _BIT(10,U)           /*!< host HNP enable */
#define USBFS_GOTGCS_HNPREQ            _BIT(9,U)            /*!< HNP request */
#define USBFS_GOTGCS_HNPS              _BIT(8,U)            /*!< HNP successes */
#define USBFS_GOTGCS_SRPREQ            _BIT(1,U)            /*!< SRP request */
#define USBFS_GOTGCS_SRPS              _BIT(0,U)            /*!< SRP successes */

/* USBFS_GOTGINTF */
#define USBFS_GOTGINTF_DF              _BIT(19,U)           /*!< debounce finish */
#define USBFS_GOTGINTF_ADTO            _BIT(18,U)           /*!< A-device timeout */
#define USBFS_GOTGINTF_HNPDET          _BIT(17,U)           /*!< host negotiation request detected */
#define USBFS_GOTGINTF_HNPEND          _BIT(9,U)            /*!< HNP end */
#define USBFS_GOTGINTF_SRPEND          _BIT(8,U)            /*!< SRP end */
#define USBFS_GOTGINTF_SESEND          _BIT(2,U)            /*!< session end */

/* USBFS_GAHBCS */
#define USBFS_GAHBCS_PTXFTH            _BIT(8,U)            /*!< periodic Tx FIFO threshold */
#define USBFS_GAHBCS_TXFTH             _BIT(7,U)            /*!< tx FIFO threshold */
#define USBFS_GAHBCS_DMAEN             _BIT(5,U)            /*!< DMA function Enable */
#define USBFS_GAHBCS_BURST_Pos         1
#define USBFS_GAHBCS_BURST_Msk         _AC(0x0000001e,U)    /*!< the AHB burst type used by DMA */
#define USBFS_GAHBCS_BURST(x)          ((x) << USBFS_GAHBCS_BURST_Pos)
#define USBFS_GAHBCS_GINTEN            _BIT(0,U)            /*!< global interrupt enable */

/* USBFS_GUSBCS */
#define USBFS_GUSBCS_FDM               _BIT(30,U)           /*!< force device mode */
#define USBFS_GUSBCS_FHM               _BIT(29,U)           /*!< force host mode */
#define USBFS_GUSBCS_ULPIEOI           _BIT(21,U)           /*!< ULPI external over-current indicator */
#define USBFS_GUSBCS_ULPIEVD           _BIT(20,U)           /*!< ULPI external VBUS driver */
#define USBFS_GUSBCS_UTT_Pos           10
#define USBFS_GUSBCS_UTT_Msk           _AC(0x00003c00,U)    /*!< USB turnaround time */
#define USBFS_GUSBCS_UTT(x)            ((x) << USBFS_GUSBCS_UTT_Pos)
#define USBFS_GUSBCS_HNPCEN            _BIT(9,U)            /*!< HNP capability enable */
#define USBFS_GUSBCS_SRPCEN            _BIT(8,U)            /*!< SRP capability enable */
#define USBFS_GUSBCS_EMBPHY            _BIT(6,U)            /*!< embedded PHY selected */
#define USBFS_GUSBCS_TOC_Pos           0
#define USBFS_GUSBCS_TOC_Msk           _AC(0x00000007,U)    /*!< timeout calibration */
#define USBFS_GUSBCS_TOC(x)            ((x) << USBFS_GUSBCS_TOC_Pos)

/* USBFS_GRSTCTL */
#define USBFS_GRSTCTL_DMAIDL           _BIT(31,U)           /*!< DMA idle state */
#define USBFS_GRSTCTL_DMABSY           _BIT(30,U)           /*!< DMA busy */
#define USBFS_GRSTCTL_TXFNUM_Pos       6
#define USBFS_GRSTCTL_TXFNUM_Msk       _AC(0x000007c0,U)    /*!< tx FIFO number */
#define USBFS_GRSTCTL_TXFNUM(x)        ((x) << USBFS_GRSTCTL_TXFNUM_Pos)
#define USBFS_GRSTCTL_TXFF             _BIT(5,U)            /*!< tx FIFO flush */
#define USBFS_GRSTCTL_RXFF             _BIT(4,U)            /*!< rx FIFO flush */
#define USBFS_GRSTCTL_HFCRST           _BIT(2,U)            /*!< host frame counter reset */
#define USBFS_GRSTCTL_HCSRST           _BIT(1,U)            /*!< HCLK soft reset */
#define USBFS_GRSTCTL_CSRST            _BIT(0,U)            /*!< core soft reset */

/* USBFS_GINTF */
#define USBFS_GINTF_WKUPIF             _BIT(31,U)           /*!< wakeup interrupt flag */
#define USBFS_GINTF_SESIF              _BIT(30,U)           /*!< session interrupt flag */
#define USBFS_GINTF_DISCIF             _BIT(29,U)           /*!< disconnect interrupt flag */
#define USBFS_GINTF_IDPSC              _BIT(28,U)           /*!< id pin status change */
#define USBFS_GINTF_PTXFEIF            _BIT(26,U)           /*!< periodic tx FIFO empty interrupt flag */
#define USBFS_GINTF_HCIF               _BIT(25,U)           /*!< host channels interrupt flag */
#define USBFS_GINTF_HPIF               _BIT(24,U)           /*!< host port interrupt flag */
#define USBFS_GINTF_PXNCIF             _BIT(21,U)           /*!< periodic transfer not complete interrupt flag */
#define USBFS_GINTF_ISOONCIF           _BIT(21,U)           /*!< isochronous OUT transfer not complete interrupt flag */
#define USBFS_GINTF_ISOINCIF           _BIT(20,U)           /*!< isochronous IN transfer not complete interrupt flag */
#define USBFS_GINTF_OEPIF              _BIT(19,U)           /*!< OUT endpoint interrupt flag */
#define USBFS_GINTF_IEPIF              _BIT(18,U)           /*!< IN endpoint interrupt flag */
#define USBFS_GINTF_EOPFIF             _BIT(15,U)           /*!< end of periodic frame interrupt flag */
#define USBFS_GINTF_ISOOPDIF           _BIT(14,U)           /*!< isochronous OUT packet dropped interrupt flag */
#define USBFS_GINTF_ENUMF              _BIT(13,U)           /*!< enumeration finished */
#define USBFS_GINTF_RST                _BIT(12,U)           /*!< USB reset */
#define USBFS_GINTF_SP                 _BIT(11,U)           /*!< USB suspend */
#define USBFS_GINTF_ESP                _BIT(10,U)           /*!< early suspend */
#define USBFS_GINTF_GONAK              _BIT(7,U)            /*!< global OUT NAK effective */
#define USBFS_GINTF_GNPINAK            _BIT(6,U)            /*!< global IN non-periodic NAK effective */
#define USBFS_GINTF_NPTXFEIF           _BIT(5,U)            /*!< non-periodic tx FIFO empty interrupt flag */
#define USBFS_GINTF_RXFNEIF            _BIT(4,U)            /*!< rx FIFO non-empty interrupt flag */
#define USBFS_GINTF_SOF                _BIT(3,U)            /*!< start of frame */
#define USBFS_GINTF_OTGIF              _BIT(2,U)            /*!< OTG interrupt flag */
#define USBFS_GINTF_MFIF               _BIT(1,U)            /*!< mode fault interrupt flag */
#define USBFS_GINTF_COPM               _BIT(0,U)            /*!< current operation mode */

/* USBFS_GINTEN */
#define USBFS_GINTEN_WKUPIE            _BIT(31,U)           /*!< wakeup interrupt enable */
#define USBFS_GINTEN_SESIE             _BIT(30,U)           /*!< session interrupt enable */
#define USBFS_GINTEN_DISCIE            _BIT(29,U)           /*!< disconnect interrupt enable */
#define USBFS_GINTEN_IDPSCIE           _BIT(28,U)           /*!< id pin status change interrupt enable */
#define USBFS_GINTEN_PTXFEIE           _BIT(26,U)           /*!< periodic tx FIFO empty interrupt enable */
#define USBFS_GINTEN_HCIE              _BIT(25,U)           /*!< host channels interrupt enable */
#define USBFS_GINTEN_HPIE              _BIT(24,U)           /*!< host port interrupt enable */
#define USBFS_GINTEN_IPXIE             _BIT(21,U)           /*!< periodic transfer not complete interrupt enable */
#define USBFS_GINTEN_ISOONCIE          _BIT(21,U)           /*!< isochronous OUT transfer not complete interrupt enable */
#define USBFS_GINTEN_ISOINCIE          _BIT(20,U)           /*!< isochronous IN transfer not complete interrupt enable */
#define USBFS_GINTEN_OEPIE             _BIT(19,U)           /*!< OUT endpoints interrupt enable */
#define USBFS_GINTEN_IEPIE             _BIT(18,U)           /*!< IN endpoints interrupt enable */
#define USBFS_GINTEN_EOPFIE            _BIT(15,U)           /*!< end of periodic frame interrupt enable */
#define USBFS_GINTEN_ISOOPDIE          _BIT(14,U)           /*!< isochronous OUT packet dropped interrupt enable */
#define USBFS_GINTEN_ENUMFIE           _BIT(13,U)           /*!< enumeration finish enable */
#define USBFS_GINTEN_RSTIE             _BIT(12,U)           /*!< USB reset interrupt enable */
#define USBFS_GINTEN_SPIE              _BIT(11,U)           /*!< USB suspend interrupt enable */
#define USBFS_GINTEN_ESPIE             _BIT(10,U)           /*!< early suspend interrupt enable */
#define USBFS_GINTEN_GONAKIE           _BIT(7,U)            /*!< global OUT NAK effective interrupt enable */
#define USBFS_GINTEN_GNPINAKIE         _BIT(6,U)            /*!< global non-periodic IN NAK effective interrupt enable */
#define USBFS_GINTEN_NPTXFEIE          _BIT(5,U)            /*!< non-periodic Tx FIFO empty interrupt enable */
#define USBFS_GINTEN_RXFNEIE           _BIT(4,U)            /*!< receive FIFO non-empty interrupt enable */
#define USBFS_GINTEN_SOFIE             _BIT(3,U)            /*!< start of frame interrupt enable */
#define USBFS_GINTEN_OTGIE             _BIT(2,U)            /*!< OTG interrupt enable */
#define USBFS_GINTEN_MFIE              _BIT(1,U)            /*!< mode fault interrupt enable */

/* USBFS_GRSTATx, x=R,P */
#define USBFS_GRSTAT_RPCKST_Pos        17
#define USBFS_GRSTAT_RPCKST_Msk        _AC(0x001e0000,U)    /*!< received packet status */
#define USBFS_GRSTAT_RPCKST(x)         ((x) << USBFS_GRSTAT_RPCKST_Pos)
#define USBFS_GRSTAT_RPCKST_GONAK      USBFS_GRSTAT_RPCKST(1)
#define USBFS_GRSTAT_RPCKST_PKT        USBFS_GRSTAT_RPCKST(2)
#define USBFS_GRSTAT_RPCKST_TF         USBFS_GRSTAT_RPCKST(3)
#define USBFS_GRSTAT_RPCKST_STPF       USBFS_GRSTAT_RPCKST(4)
#define USBFS_GRSTAT_RPCKST_STP        USBFS_GRSTAT_RPCKST(6)
#define USBFS_GRSTAT_DPID_Pos          15
#define USBFS_GRSTAT_DPID_Msk          _AC(0x00018000,U)    /*!< data PID */
#define USBFS_GRSTAT_DPID(x)           ((x) << USBFS_GRSTAT_DPID_Pos)
#define USBFS_GRSTAT_BCOUNT_Pos        4
#define USBFS_GRSTAT_BCOUNT_Msk        _AC(0x00007ff0,U)    /*!< byte count */
#define USBFS_GRSTAT_BCOUNT(x)         ((x) << USBFS_GRSTAT_BCOUNT_Pos)
#define USBFS_GRSTAT_CNUM_Pos          0
#define USBFS_GRSTAT_CNUM_Msk          _AC(0x0000000f,U)    /*!< channel number */
#define USBFS_GRSTAT_CNUM(x)           ((x) << USBFS_GRSTAT_CNUM_Pos)
#define USBFS_GRSTAT_EPNUM_Pos         0
#define USBFS_GRSTAT_EPNUM_Msk         _AC(0x0000000f,U)    /*!< endpoint number */
#define USBFS_GRSTAT_EPNUM(x)          ((x) << USBFS_GRSTAT_EPNUM_Pos)

/* USBFS_GRFLEN */
#define USBFS_GRFLEN_RXFD_Pos          0
#define USBFS_GRFLEN_RXFD_Msk          _AC(0x0000ffff,U)    /*!< rx FIFO depth */
#define USBFS_GRFLEN_RXFD(x)           ((x) << USBFS_GRFLEN_RXFD_Pos)

/* USBFS_HNPTFLEN */
#define USBFS_HNPTFLEN_HNPTXFD_Pos     16
#define USBFS_HNPTFLEN_HNPTXFD_Msk     _AC(0xffff0000,U)    /*!< non-periodic Tx FIFO depth */
#define USBFS_HNPTFLEN_HNPTXFD(x)      ((x) << USBFS_HNPTFLEN_HNPTXFD_Pos)
#define USBFS_HNPTFLEN_HNPTXRSAR_Pos   0
#define USBFS_HNPTFLEN_HNPTXRSAR_Msk   _AC(0x0000ffff,U)    /*!< non-periodic Tx RAM start address */
#define USBFS_HNPTFLEN_HNPTXRSAR(x)    ((x) << USBFS_HNPTFLEN_HNPTXRSAR_Pos)

/* USBFS_DIEP0TFLEN */
#define USBFS_DIEP0TFLEN_IEP0TXFD_Pos  16
#define USBFS_DIEP0TFLEN_IEP0TXFD_Msk  _AC(0xffff0000,U)    /*!< IN Endpoint 0 Tx FIFO depth */
#define USBFS_DIEP0TFLEN_IEP0TXFD(x)   ((x) << USBFS_DIEP0TFLEN_IEP0TXFD_Pos)
#define USBFS_DIEP0TFLEN_IEP0TXRSAR_Pos 0
#define USBFS_DIEP0TFLEN_IEP0TXRSAR_Msk _AC(0x0000ffff,U)    /*!< IN Endpoint 0 TX RAM start address */
#define USBFS_DIEP0TFLEN_IEP0TXRSAR(x) ((x) << USBFS_DIEP0TFLEN_IEP0TXRSAR_Pos)

/* USBFS_HNPTFQSTAT */
#define USBFS_HNPTFQSTAT_NPTXRQTOP_Pos 24
#define USBFS_HNPTFQSTAT_NPTXRQTOP_Msk _AC(0x7f000000,U)    /*!< top entry of the non-periodic Tx request queue */
#define USBFS_HNPTFQSTAT_NPTXRQTOP(x)  ((x) << USBFS_HNPTFQSTAT_NPTXRQTOP_Pos)
#define USBFS_HNPTFQSTAT_NPTXRQS_Pos   16
#define USBFS_HNPTFQSTAT_NPTXRQS_Msk   _AC(0x00ff0000,U)    /*!< non-periodic Tx request queue space */
#define USBFS_HNPTFQSTAT_NPTXRQS(x)    ((x) << USBFS_HNPTFQSTAT_NPTXRQS_Pos)
#define USBFS_HNPTFQSTAT_NPTXFS_Pos    0
#define USBFS_HNPTFQSTAT_NPTXFS_Msk    _AC(0x0000ffff,U)    /*!< non-periodic Tx FIFO space */
#define USBFS_HNPTFQSTAT_NPTXFS(x)     ((x) << USBFS_HNPTFQSTAT_NPTXFS_Pos)
#define USBFS_HNPTFQSTAT_CNUM          BITS(27, 30)         /*!< channel number*/
#define USBFS_HNPTFQSTAT_EPNUM         BITS(27, 30)         /*!< endpoint number */
#define USBFS_HNPTFQSTAT_TYPE          BITS(25, 26)         /*!< token type */
#define USBFS_HNPTFQSTAT_TMF           _BIT(24,U)           /*!< terminate flag */

/* USBFS_GCCFG */
#define USBFS_GCCFG_VBUSIG             _BIT(21,U)           /*!< vbus ignored */
#define USBFS_GCCFG_SOFOEN             _BIT(20,U)           /*!< SOF output enable */
#define USBFS_GCCFG_VBUSBCEN           _BIT(19,U)           /*!< the VBUS B-device comparer enable */
#define USBFS_GCCFG_VBUSACEN           _BIT(18,U)           /*!< the VBUS A-device comparer enable */
#define USBFS_GCCFG_PWRON              _BIT(16,U)           /*!< power on */

/* USBFS_CID */
#define USBFS_CID_CID_Pos              0
#define USBFS_CID_CID_Msk              _AC(0xffffffff,U)    /*!< core ID */
#define USBFS_CID_CID(x)               ((x) << USBFS_CID_CID_Pos)

/* USBFS_HPTFLEN */
#define USBFS_HPTFLEN_HPTXFD_Pos       16
#define USBFS_HPTFLEN_HPTXFD_Msk       _AC(0xffff0000,U)    /*!< host periodic Tx FIFO depth */
#define USBFS_HPTFLEN_HPTXFD(x)        ((x) << USBFS_HPTFLEN_HPTXFD_Pos)
#define USBFS_HPTFLEN_HPTXFSAR_Pos     0
#define USBFS_HPTFLEN_HPTXFSAR_Msk     _AC(0x0000ffff,U)    /*!< host periodic Tx RAM start address */
#define USBFS_HPTFLEN_HPTXFSAR(x)      ((x) << USBFS_HPTFLEN_HPTXFSAR_Pos)

/* USBFS_DIEPxTFLEN, x = 1..3 */
#define USBFS_DIEPTFLEN_IEPTXFD_Pos    16
#define USBFS_DIEPTFLEN_IEPTXFD_Msk    _AC(0xffff0000,U)    /*!< IN endpoint Tx FIFO x depth */
#define USBFS_DIEPTFLEN_IEPTXFD(x)     ((x) << USBFS_DIEPTFLEN_IEP0TXFD_Pos)
#define USBFS_DIEPTFLEN_IEPTXRSAR_Pos  0
#define USBFS_DIEPTFLEN_IEPTXRSAR_Msk  _AC(0x0000ffff,U)    /*!< IN endpoint FIFOx Tx x RAM start address */
#define USBFS_DIEPTFLEN_IEPTXRSAR(x)   ((x) << USBFS_DIEPTFLEN_IEPTXRSAR_Pos)

/* USBFS_HCTL */
#define USBFS_HCTL_SPDFSLS             _BIT(2,U)            /*!< speed limited to FS and LS */
#define USBFS_HCTL_CLKSEL_Pos          0
#define USBFS_HCTL_CLKSEL_Msk          _AC(0x00000003,U)    /*!< clock select for USB clock */
#define USBFS_HCTL_CLKSEL(x)           ((x) << USBFS_HCTL_CLKSEL_Pos)
#define USBFS_HCTL_CLKSEL_48MHZ        USBFS_HCTL_CLKSEL(1)

/* USBFS_HFT */
#define USBFS_HFT_FRI_Pos              0
#define USBFS_HFT_FRI_Msk              _AC(0x0000ffff,U)    /*!< frame interval */

/* USBFS_HFINFR */
#define USBFS_HFINFR_FRT_Pos           16
#define USBFS_HFINFR_FRT_Msk           _AC(0xffff0000,U)    /*!< frame remaining time */
#define USBFS_HFINFR_FRT(x)            ((x) << USBFS_HFINFR_FRT_Pos)
#define USBFS_HFINFR_FRNUM_Pos         0
#define USBFS_HFINFR_FRNUM_Msk         _AC(0x0000ffff,U)    /*!< frame number */
#define USBFS_HFINFR_FRNUM(x)          ((x) << USBFS_HFINFR_FRNUM_Pos)

/* USBFS_HPTFQSTAT */
#define USBFS_HPTFQSTAT_PTXREQT_Pos    24
#define USBFS_HPTFQSTAT_PTXREQT_Msk    _AC(0xff000000,U)    /*!< top entry of the periodic Tx request queue */
#define USBFS_HPTFQSTAT_PTXREQT(x)     ((x) << USBFS_HPTFQSTAT_PTXREQT_Pos)
#define USBFS_HPTFQSTAT_PTXREQS_Pos    16
#define USBFS_HPTFQSTAT_PTXREQS_Msk    _AC(0x00ff0000,U)    /*!< periodic Tx request queue space */
#define USBFS_HPTFQSTAT_PTXREQS(x)     ((x) << USBFS_HPTFQSTAT_PTXREQS_Pos)
#define USBFS_HPTFQSTAT_PTXFS_Pos      0
#define USBFS_HPTFQSTAT_PTXFS_Msk      _AC(0x0000ffff,U)    /*!< periodic Tx FIFO space */
#define USBFS_HPTFQSTAT_PTXFS(x)       ((x) << USBFS_HPTFQSTAT_PTXFS_Pos)
#define USBFS_HPTFQSTAT_OEFRM          _BIT(31,U)           /*!< odd/eveb frame */
#define USBFS_HPTFQSTAT_CNUM           BITS(27, 30)         /*!< channel number */
#define USBFS_HPTFQSTAT_EPNUM          BITS(27, 30)         /*!< endpoint number */
#define USBFS_HPTFQSTAT_TYPE           BITS(25, 26)         /*!< token type */
#define USBFS_HPTFQSTAT_TMF            _BIT(24,U)           /*!< terminate flag */

/* USBFS_HACHINT */
#define USBFS_HACHINT_HACHINT_Pos      0
#define USBFS_HACHINT_HACHINT_Msk      _AC(0x000000ff,U)    /*!< host all channel interrupts */
#define USBFS_HACHINT_HACHINT(x)       ((x) << USBFS_HACHINT_HACHINT_Pos)

/* USBFS_HACHINTEN */
#define USBFS_HACHINTEN_CINTEN_Pos     0
#define USBFS_HACHINTEN_CINTEN_Msk     _AC(0x000000ff,U)    /*!< channel interrupt enable */
#define USBFS_HACHINTEN_CINTEN(x)      ((x) << USBFS_HACHINTEN_CINTEN_Pos)

/* USBFS_HPCS */
#define USBFS_HPCS_PS_Pos              17
#define USBFS_HPCS_PS_Msk              _AC(0x00060000,U)    /*!< port speed */
#define USBFS_HPCS_PS(x)               ((x) << USBFS_HPCS_PS_Pos)
#define USBFS_HPCS_PS_FULL             USBFS_HPCS_PS(1)     /*!< full speed */
#define USBFS_HPCS_PS_LOW              USBFS_HPCS_PS(2)     /*!< low speed */
#define USBFS_HPCS_PP                  _BIT(12,U)           /*!< port power */
#define USBFS_HPCS_PLST_Pos            10
#define USBFS_HPCS_PLST_Msk            _AC(0x00000c00,U)    /*!< port line status */
#define USBFS_HPCS_PLST(x)             ((x) << USBFS_HPCS_PLST_Pos)
#define USBFS_HPCS_PRST                _BIT(8,U)            /*!< port reset */
#define USBFS_HPCS_PSP                 _BIT(7,U)            /*!< port suspend */
#define USBFS_HPCS_PREM                _BIT(6,U)            /*!< port resume */
#define USBFS_HPCS_PEDC                _BIT(3,U)            /*!< port enable/disable change */
#define USBFS_HPCS_PE                  _BIT(2,U)            /*!< port enable */
#define USBFS_HPCS_PCD                 _BIT(1,U)            /*!< port connect detected */
#define USBFS_HPCS_PCST                _BIT(0,U)            /*!< port connect status */

/* USBFS_HCHCTL */
#define USBFS_HCHCTL_CEN               _BIT(31,U)           /*!< channel enable */
#define USBFS_HCHCTL_CDIS              _BIT(30,U)           /*!< channel disable */
#define USBFS_HCHCTL_ODDFRM            _BIT(29,U)           /*!< odd frame */
#define USBFS_HCHCTL_DAR_Pos           22
#define USBFS_HCHCTL_DAR_Msk           _AC(0x1fc00000,U)    /*!< device address */
#define USBFS_HCHCTL_DAR(x)            ((x) << USBFS_HCHCTL_DAR_Pos)
#define USBFS_HCHCTL_MPC_Pos           20
#define USBFS_HCHCTL_MPC_Msk           _AC(0x00300000,U)    /*!< multiple packet count */
#define USBFS_HCHCTL_MPC(x)            ((x) << USBFS_HCHCTL_MPC_Pos)
#define USBFS_HCHCTL_EPTYPE_Pos        18
#define USBFS_HCHCTL_EPTYPE_Msk        _AC(0x000c0000,U)    /*!< endpoint type */
#define USBFS_HCHCTL_EPTYPE(x)         ((x) << USBFS_HCHCTL_EPTYPE_Pos)
#define USBFS_HCHCTL_LSD               _BIT(17,U)           /*!< low-speed device */
#define USBFS_HCHCTL_EPDIR             _BIT(15,U)           /*!< endpoint direction */
#define USBFS_HCHCTL_EPNUM_Pos         11
#define USBFS_HCHCTL_EPNUM_Msk         _AC(0x00007800,U)    /*!< endpoint number */
#define USBFS_HCHCTL_EPNUM(x)          ((x) << USBFS_HCHCTL_EPNUM_Pos)
#define USBFS_HCHCTL_MPL_Pos           0
#define USBFS_HCHCTL_MPL_Msk           _AC(0x000007ff,U)    /*!< maximum packet length */
#define USBFS_HCHCTL_MPL(x)            ((x) << USBFS_HCHCTL_MPL_Pos)

/* USBFS_HCHSTCTL */
#define USBFS_HCHSTCTL_SPLEN           _BIT(31,U)           /*!< enable high-speed split transaction */
#define USBFS_HCHSTCTL_CSPLT           _BIT(16,U)           /*!< complete-split enable */
#define USBFS_HCHSTCTL_ISOPCE          BITS(14, 15)         /*!< isochronous OUT payload continuation encoding */
#define USBFS_HCHSTCTL_HADDR           BITS(7, 13)          /*!< HUB address */
#define USBFS_HCHSTCTL_PADDR           BITS(0, 6)           /*!< port address */

/* USBFS_HCHINTF */
#define USBFS_HCHINTF_DTER             _BIT(10,U)           /*!< data toggle error */
#define USBFS_HCHINTF_REQOVR           _BIT(9,U)            /*!< request queue overrun */
#define USBFS_HCHINTF_BBER             _BIT(8,U)            /*!< babble error */
#define USBFS_HCHINTF_USBER            _BIT(7,U)            /*!< USB bus Error */
#define USBFS_HCHINTF_NYET             _BIT(6,U)            /*!< NYET */
#define USBFS_HCHINTF_ACK              _BIT(5,U)            /*!< ACK */
#define USBFS_HCHINTF_NAK              _BIT(4,U)            /*!< NAK */
#define USBFS_HCHINTF_STALL            _BIT(3,U)            /*!< STALL */
#define USBFS_HCHINTF_DMAER            _BIT(2,U)            /*!< DMA error */
#define USBFS_HCHINTF_CH               _BIT(1,U)            /*!< channel halted */
#define USBFS_HCHINTF_TF               _BIT(0,U)            /*!< transfer finished */

/* USBFS_HCHINTEN */
#define USBFS_HCHINTEN_DTERIE          _BIT(10,U)           /*!< data toggle error interrupt enable */
#define USBFS_HCHINTEN_REQOVRIE        _BIT(9,U)            /*!< request queue overrun interrupt enable */
#define USBFS_HCHINTEN_BBERIE          _BIT(8,U)            /*!< babble error interrupt enable */
#define USBFS_HCHINTEN_USBERIE         _BIT(7,U)            /*!< USB bus error interrupt enable */
#define USBFS_HCHINTEN_NYETIE          _BIT(6,U)            /*!< NYET interrupt enable */
#define USBFS_HCHINTEN_ACKIE           _BIT(5,U)            /*!< ACK interrupt enable */
#define USBFS_HCHINTEN_NAKIE           _BIT(4,U)            /*!< NAK interrupt enable */
#define USBFS_HCHINTEN_STALLIE         _BIT(3,U)            /*!< STALL interrupt enable */
#define USBFS_HCHINTEN_DMAERIE         _BIT(2,U)            /*!< DMA error interrupt enable */
#define USBFS_HCHINTEN_CHIE            _BIT(1,U)            /*!< channel halted interrupt enable */
#define USBFS_HCHINTEN_TFIE            _BIT(0,U)            /*!< transfer finished interrupt enable */

/* USBFS_HCHLEN */
#define USBFS_HCHLEN_PING              _BIT(31,U)           /*!< PING token request */
#define USBFS_HCHLEN_DPID_Pos          29
#define USBFS_HCHLEN_DPID_Msk          _AC(0x60000000,U)    /*!< data PID */
#define USBFS_HCHLEN_DPID(x)           ((x) << USBFS_HCHLEN_DPID_Pos)
#define USBFS_HCHLEN_PCNT_Pos          19
#define USBFS_HCHLEN_PCNT_Msk          _AC(0x1ff80000,U)    /*!< packet count */
#define USBFS_HCHLEN_PCNT(x)           ((x) << USBFS_HCHLEN_PCNT_Pos)
#define USBFS_HCHLEN_TLEN_Pos          0
#define USBFS_HCHLEN_TLEN_Msk          _AC(0x0007ffff,U)    /*!< transfer length */
#define USBFS_HCHLEN_TLEN(x)           ((x) << USBFS_HCHLEN_TLEN_Pos)

/* USBFS_DCFG */
#define USBFS_DCFG_EOPFT_Pos           11
#define USBFS_DCFG_EOPFT_Msk           _AC(0x00001800,U)    /*!< end of periodic frame time */
#define USBFS_DCFG_EOPFT(x)            ((x) << USBFS_DCFG_EOPFT_Pos)
#define USBFS_DCFG_EOPFT_80PCT         USBFS_DCFG_EOPFT(0)  /*!< 80% of the frame time */
#define USBFS_DCFG_EOPFT_85PCT         USBFS_DCFG_EOPFT(1)  /*!< 85% of the frame time */
#define USBFS_DCFG_EOPFT_90PCT         USBFS_DCFG_EOPFT(2)  /*!< 90% of the frame time */
#define USBFS_DCFG_EOPFT_95PCT         USBFS_DCFG_EOPFT(3)  /*!< 95% of the frame time */
#define USBFS_DCFG_DAR_Pos             4
#define USBFS_DCFG_DAR_Msk             _AC(0x000007f0,U)    /*!< device address */
#define USBFS_DCFG_DAR(x)              ((x) << USBFS_DCFG_DAR_Pos)
#define USBFS_DCFG_NZLSOH              _BIT(2,U)            /*!< non-zero-length status OUT handshake */
#define USBFS_DCFG_DS_Pos              0
#define USBFS_DCFG_DS_Msk              _AC(0x00000003,U)    /*!< device speed */
#define USBFS_DCFG_DS(x)               ((x) << USBFS_DCFG_DS_Pos)
#define USBFS_DCFG_DS_FULL             USBFS_DCFG_DS(3)

/* USBFS_DCTL */
#define USBFS_DCTL_POIF                _BIT(11,U)           /*!< power-on initialization finished */
#define USBFS_DCTL_CGONAK              _BIT(10,U)           /*!< clear global OUT NAK */
#define USBFS_DCTL_SGONAK              _BIT(9,U)            /*!< set global OUT NAK */
#define USBFS_DCTL_CGINAK              _BIT(8,U)            /*!< clear global IN NAK */
#define USBFS_DCTL_SGINAK              _BIT(7,U)            /*!< set global IN NAK */
#define USBFS_DCTL_GONS                _BIT(3,U)            /*!< global OUT NAK status */
#define USBFS_DCTL_GINS                _BIT(2,U)            /*!< global IN NAK status */
#define USBFS_DCTL_SD                  _BIT(1,U)            /*!< soft disconnect */
#define USBFS_DCTL_RWKUP               _BIT(0,U)            /*!< remote wakeup */

/* USBFS_DSTAT */
#define USBFS_DSTAT_FNRSOF_Pos         8
#define USBFS_DSTAT_FNRSOF_Msk         _AC(0x003fff00,U)    /*!< the frame number of the received SOF. */
#define USBFS_DSTAT_FNRSOF(x)          ((x) << USBFS_DSTAT_FNRSOF_Pos)
#define USBFS_DSTAT_ES_Pos             1
#define USBFS_DSTAT_ES_Msk             _AC(0x00000006,U)    /*!< enumerated speed */
#define USBFS_DSTAT_ES(x)              ((x) << USBFS_DSTAT_ES_Pos)
#define USBFS_DSTAT_ES_FULL            USBFS_DSTAT_ES(3)
#define USBFS_DSTAT_SPST               _BIT(0,U)            /*!< suspend status */

/* USBFS_DIEPINTEN */
#define USBFS_DIEPINTEN_NAKEN          _BIT(13,U)           /*!< NAK handshake sent by USBHS interrupt enable bit */
#define USBFS_DIEPINTEN_TXFEEN         _BIT(7,U)            /*!< transmit FIFO empty interrupt enable bit */
#define USBFS_DIEPINTEN_IEPNEEN        _BIT(6,U)            /*!< IN endpoint NAK effective interrupt enable bit */
#define USBFS_DIEPINTEN_EPTXFUDEN      _BIT(4,U)            /*!< endpoint Tx FIFO underrun interrupt enable bit */
#define USBFS_DIEPINTEN_CITOEN         _BIT(3,U)            /*!< control In Timeout interrupt enable bit */
#define USBFS_DIEPINTEN_EPDISEN        _BIT(1,U)            /*!< endpoint disabled interrupt enable bit */
#define USBFS_DIEPINTEN_TFEN           _BIT(0,U)            /*!< transfer finished interrupt enable bit */

/* USBFS_DOEPINTEN */
#define USBFS_DOEPINTEN_NYETEN         _BIT(14,U)           /*!< NYET handshake is sent interrupt enable bit */
#define USBFS_DOEPINTEN_BTBSTPEN       _BIT(6,U)            /*!< back-to-back SETUP packets interrupt enable bit */
#define USBFS_DOEPINTEN_EPRXFOVREN     _BIT(4,U)            /*!< endpoint Rx FIFO overrun interrupt enable bit */
#define USBFS_DOEPINTEN_STPFEN         _BIT(3,U)            /*!< SETUP phase finished interrupt enable bit */
#define USBFS_DOEPINTEN_EPDISEN        _BIT(1,U)            /*!< endpoint disabled interrupt enable bit */
#define USBFS_DOEPINTEN_TFEN           _BIT(0,U)            /*!< transfer finished interrupt enable bit */

/* USBFS_DAEPINT */
#define USBFS_DAEPINT_OEPITB_Pos       16
#define USBFS_DAEPINT_OEPITB_Msk       _AC(0x000f0000,U)    /*!< device all OUT endpoint interrupt bits */
#define USBFS_DAEPINT_OEPITB(x)        ((x) << USBFS_DAEPINT_OEPITB_Pos)
#define USBFS_DAEPINT_IEPITB_Pos       0
#define USBFS_DAEPINT_IEPITB_Msk       _AC(0x0000000f,U)    /*!< device all IN endpoint interrupt bits */
#define USBFS_DAEPINT_IEPITB(x)        ((x) << USBFS_DAEPINT_IEPITB_Pos)

/* USBFS_DAEPINTEN */
#define USBFS_DAEPINTEN_OEPIE_Pos      16
#define USBFS_DAEPINTEN_OEPIE_Msk      _AC(0x000f0000,U)    /*!< OUT endpoint interrupt enable */
#define USBFS_DAEPINTEN_OEPIE(x)       ((x) << USBFS_DAEPINTEN_OEPIE_Pos)
#define USBFS_DAEPINTEN_IEPIE_Pos      0
#define USBFS_DAEPINTEN_IEPIE_Msk      _AC(0x0000000f,U)    /*!< IN endpoint interrupt enable */
#define USBFS_DAEPINTEN_IEPIE(x)       ((x) << USBFS_DAEPINTEN_IEPIE_Pos)

/* USBFS_DVBUSDT */
#define USBFS_DVBUSDT_DVBUSDT_Pos      0
#define USBFS_DVBUSDT_DVBUSDT_Msk      _AC(0x0000ffff,U)    /*!< device VBUS discharge time */
#define USBFS_DVBUSDT_DVBUSDT(x)       ((x) << USBFS_DVBUSDT_DVBUSDT_Pos)

/* USBFS_DVBUSPT */
#define USBFS_DVBUSPT_DVBUSPT_Pos      0
#define USBFS_DVBUSPT_DVBUSPT_Msk      _AC(0x00000fff,U)    /*!< device VBUS pulsing time */
#define USBFS_DVBUSPT_DVBUSPT(x)       ((x) << USBFS_DVBUSDT_DVBUSDT_Pos)

/* USBFS_DIEPFEINTEN */
#define USBFS_DIEPFEINTEN_IEPTXFEIE_Pos 0
#define USBFS_DIEPFEINTEN_IEPTXFEIE_Msk _AC(0x0000000f,U)    /*!< IN endpoint Tx FIFO empty interrupt enable bits */
#define USBFS_DIEPFEINTEN_IEPTXFEIE(x) ((x) << USBFS_DIEPFEINTEN_IEPTXFEIE_Pos)

/* USBFS_DIEPxCTL, x = 0..3 */
#define USBFS_DIEPCTL_EPEN             _BIT(31,U)           /*!< IN endpoint enable */
#define USBFS_DIEPCTL_EPD              _BIT(30,U)           /*!< IN endpoint disable */
#define USBFS_DIEPCTL_SODDFRM          _BIT(29,U)           /*!< IN endpoint set odd frame */
#define USBFS_DIEPCTL_SD1PID           _BIT(29,U)           /*!< IN endpoint set DATA1 PID */
#define USBFS_DIEPCTL_SEVENFRM         _BIT(28,U)           /*!< IN endpoint set even frame */
#define USBFS_DIEPCTL_SD0PID           _BIT(28,U)           /*!< IN endpoint set DATA0 PID */
#define USBFS_DIEPCTL_SNAK             _BIT(27,U)           /*!< IN endpoint set NAK */
#define USBFS_DIEPCTL_CNAK             _BIT(26,U)           /*!< IN endpoint clear NAK */
#define USBFS_DIEPCTL_TXFNUM_Pos       22
#define USBFS_DIEPCTL_TXFNUM_Msk       _AC(0x03c00000,U)    /*!< IN tx FIFO number */
#define USBFS_DIEPCTL_TXFNUM(x)        ((x) << USBFS_DIEPCTL_TXFNUM_Pos)
#define USBFS_DIEPCTL_STALL            _BIT(21,U)           /*!< IN STALL handshake */
#define USBFS_DIEPCTL_EPTYPE_Pos       18
#define USBFS_DIEPCTL_EPTYPE_Msk       _AC(0x000c0000,U)    /*!< IN endpoint type */
#define USBFS_DIEPCTL_EPTYPE(x)        ((x) << USBFS_DIEPCTL_EPTYPE_Pos)
#define USBFS_DIEPCTL_EPTYPE_CONTROL   USBFS_DIEPCTL_EPTYPE(0)
#define USBFS_DIEPCTL_EPTYPE_ISO       USBFS_DIEPCTL_EPTYPE(1)
#define USBFS_DIEPCTL_EPTYPE_BULK      USBFS_DIEPCTL_EPTYPE(2)
#define USBFS_DIEPCTL_EPTYPE_INTERRUPT USBFS_DIEPCTL_EPTYPE(3)
#define USBFS_DIEPCTL_NAKS             _BIT(17,U)           /*!< IN NAK status */
#define USBFS_DIEPCTL_EOFRM            _BIT(16,U)           /*!< IN even/odd frame */
#define USBFS_DIEPCTL_DPID             _BIT(16,U)           /*!< IN endpoint data PID */
#define USBFS_DIEPCTL_EPACT            _BIT(15,U)           /*!< IN endpoint active */
#define USBFS_DIEPCTL_MPL_Pos          0
#define USBFS_DIEPCTL_MPL_Msk          _AC(0x000007ff,U)    /*!< IN maximum packet length */
#define USBFS_DIEPCTL_MPL(x)           ((x) << USBFS_DIEPCTL_MPL_Pos)
/* specific to endpoint 0 */
#define USBFS_DIEP0CTL_MPL_Pos         0
#define USBFS_DIEP0CTL_MPL_Msk         _AC(0x00000003,U)    /*!< IN endpoint 0 maximum packet length */
#define USBFS_DIEP0CTL_MPL(x)          ((x) << USBFS_DIEP0CTL_MPL_Pos)
#define USBFS_DIEP0CTL_MPL_64B         USBFS_DIEP0CTL_MPL(0)
#define USBFS_DIEP0CTL_MPL_32B         USBFS_DIEP0CTL_MPL(1)
#define USBFS_DIEP0CTL_MPL_16B         USBFS_DIEP0CTL_MPL(2)
#define USBFS_DIEP0CTL_MPL_8B          USBFS_DIEP0CTL_MPL(3)

/* USBFS_DOEPxCTL, x = 0..3 */
#define USBFS_DOEPCTL_EPEN             _BIT(31,U)           /*!< OUT endpoint enable */
#define USBFS_DOEPCTL_EPD              _BIT(30,U)           /*!< OUT endpoint disable */
#define USBFS_DOEPCTL_SODDFRM          _BIT(29,U)           /*!< OUT endpoint set odd frame */
#define USBFS_DOEPCTL_SD1PID           _BIT(29,U)           /*!< OUT endpoint set DATA1 PID */
#define USBFS_DOEPCTL_SEVENFRM         _BIT(28,U)           /*!< OUT endpoint set even frame */
#define USBFS_DOEPCTL_SD0PID           _BIT(28,U)           /*!< OUT endpoint set DATA0 PID */
#define USBFS_DOEPCTL_SNAK             _BIT(27,U)           /*!< OUT set NAK */
#define USBFS_DOEPCTL_CNAK             _BIT(26,U)           /*!< OUT clear NAK */
#define USBFS_DOEPCTL_STALL            _BIT(21,U)           /*!< OUT STALL handshake */
#define USBFS_DOEPCTL_SNOOP            _BIT(20,U)           /*!< OUT snoop mode */
#define USBFS_DOEPCTL_EPTYPE_Pos       18
#define USBFS_DOEPCTL_EPTYPE_Msk       _AC(0x000c0000,U)    /*!< OUT endpoint type */
#define USBFS_DOEPCTL_EPTYPE(x)        ((x) << USBFS_DOEPCTL_EPTYPE_Pos)
#define USBFS_DOEPCTL_EPTYPE_CONTROL   USBFS_DOEPCTL_EPTYPE(0)
#define USBFS_DOEPCTL_EPTYPE_ISO       USBFS_DOEPCTL_EPTYPE(1)
#define USBFS_DOEPCTL_EPTYPE_BULK      USBFS_DOEPCTL_EPTYPE(2)
#define USBFS_DOEPCTL_EPTYPE_INTERRUPT USBFS_DOEPCTL_EPTYPE(3)
#define USBFS_DOEPCTL_NAKS             _BIT(17,U)           /*!< OUT NAK status */
#define USBFS_DOEPCTL_EOFRM            _BIT(16,U)           /*!< OUT even/odd frame */
#define USBFS_DOEPCTL_DPID             _BIT(16,U)           /*!< OUT endpoint data PID */
#define USBFS_DOEPCTL_EPACT            _BIT(15,U)           /*!< OUT endpoint active */
#define USBFS_DOEPCTL_MPL_Pos          0
#define USBFS_DOEPCTL_MPL_Msk          _AC(0x000007ff,U)    /*!< OUT maximum packet length */
#define USBFS_DOEPCTL_MPL(x)           ((x) << USBFS_DOEPCTL_MPL_Pos)
/* specific to endpoint 0 */
#define USBFS_DOEP0CTL_MPL_Pos         0
#define USBFS_DOEP0CTL_MPL_Msk         _AC(0x00000003,U)    /*!< OUT endpoint 0 maximum packet length */
#define USBFS_DOEP0CTL_MPL(x)          ((x) << USBFS_DOEP0CTL_MPL_Pos)
#define USBFS_DOEP0CTL_MPL_64B         USBFS_DOEP0CTL_MPL(0)
#define USBFS_DOEP0CTL_MPL_32B         USBFS_DOEP0CTL_MPL(1)
#define USBFS_DOEP0CTL_MPL_16B         USBFS_DOEP0CTL_MPL(2)
#define USBFS_DOEP0CTL_MPL_8B          USBFS_DOEP0CTL_MPL(3)

/* USBFS_DIEPxINTF, x = 0..3 */
#define USBFS_DIEPINTF_NAK             _BIT(13,U)           /*!< NAK handshake sent by USBHS */
#define USBFS_DIEPINTF_TXFE            _BIT(7,U)            /*!< transmit FIFO empty */
#define USBFS_DIEPINTF_IEPNE           _BIT(6,U)            /*!< IN endpoint NAK effective */
#define USBFS_DIEPINTF_EPTXFUD         _BIT(4,U)            /*!< endpoint Tx FIFO underrun */
#define USBFS_DIEPINTF_CITO            _BIT(3,U)            /*!< control In Timeout interrupt */
#define USBFS_DIEPINTF_EPDIS           _BIT(1,U)            /*!< endpoint disabled */
#define USBFS_DIEPINTF_TF              _BIT(0,U)            /*!< transfer finished */

/* USBFS_DOEPxINTF, x = 0..3 */
#define USBFS_DOEPINTF_NYET            _BIT(14,U)           /*!< NYET handshake is sent */
#define USBFS_DOEPINTF_BTBSTP          _BIT(6,U)            /*!< back-to-back SETUP packets */
#define USBFS_DOEPINTF_EPRXFOVR        _BIT(4,U)            /*!< endpoint Rx FIFO overrun */
#define USBFS_DOEPINTF_STPF            _BIT(3,U)            /*!< SETUP phase finished */
#define USBFS_DOEPINTF_EPDIS           _BIT(1,U)            /*!< endpoint disabled */
#define USBFS_DOEPINTF_TF              _BIT(0,U)            /*!< transfer finished */

/* USBFS_DIEP0LEN */
#define USBFS_DIEP0LEN_PCNT_Pos        19
#define USBFS_DIEP0LEN_PCNT_Msk        _AC(0x00180000,U)    /*!< packet count */
#define USBFS_DIEP0LEN_PCNT(x)         ((x) << USBFS_DIEP0LEN_PCNT_Pos)
#define USBFS_DIEP0LEN_TLEN_Pos        0
#define USBFS_DIEP0LEN_TLEN_Msk        _AC(0x0000007f,U)    /*!< transfer length */
#define USBFS_DIEP0LEN_TLEN(x)         ((x) << USBFS_DIEP0LEN_TLEN_Pos)

/* USBFS_DOEP0LEN */
#define USBFS_DOEP0LEN_STPCNT_Pos      29
#define USBFS_DOEP0LEN_STPCNT_Msk      _AC(0x60000000,U)    /*!< SETUP packet count */
#define USBFS_DOEP0LEN_STPCNT(x)       ((x) << USBFS_DOEP0LEN_STPCNT_Pos)
#define USBFS_DOEP0LEN_PCNT            _BIT(19,U)           /*!< packet count */
#define USBFS_DOEP0LEN_TLEN_Pos        0
#define USBFS_DOEP0LEN_TLEN_Msk        _AC(0x0000007f,U)    /*!< transfer length */
#define USBFS_DOEP0LEN_TLEN(x)         ((x) << USBFS_DOEP0LEN_TLEN_Pos)

/* USBFS_DIEPxLEN, x = 1..3 */
#define USBFS_DIEPLEN_MCPF_Pos         29
#define USBFS_DIEPLEN_MCPF_Msk         _AC(0x60000000,U)    /*!< multi packet count per frame */
#define USBFS_DIEPLEN_MCPF(x)          ((x) << USBFS_DIEPLEN_MCPF_Pos)
#define USBFS_DIEPLEN_PCNT_Pos         19
#define USBFS_DIEPLEN_PCNT_Msk         _AC(0x1ff80000,U)    /*!< packet count */
#define USBFS_DIEPLEN_PCNT(x)          ((x) << USBFS_DIEPLEN_PCNT_Pos)
#define USBFS_DIEPLEN_TLEN_Pos         0
#define USBFS_DIEPLEN_TLEN_Msk         _AC(0x0007ffff,U)    /*!< transfer length */
#define USBFS_DIEPLEN_TLEN(x)          ((x) << USBFS_DIEPLEN_TLEN_Pos)

/* USBFS_DOEPxLEN, x = 1..3 */
#define USBFS_DOEPLEN_RXDPID_Pos       29
#define USBFS_DOEPLEN_RXDPID_Msk       _AC(0x60000000,U)    /*!< received data PID */
#define USBFS_DOEPLEN_RXDPID(x)        ((x) << USBFS_DOEPLEN_RXDPID_Pos)
#define USBFS_DOEPLEN_RXDPID_DATA0     USBFS_DOEPLEN_RXDPID(0)
#define USBFS_DOEPLEN_RXDPID_DATA1     USBFS_DOEPLEN_RXDPID(2)
#define USBFS_DOEPLEN_STPCNT_Pos       29
#define USBFS_DOEPLEN_STPCNT_Msk       _AC(0x60000000,U)    /*!< SETUP packet count */
#define USBFS_DOEPLEN_STPCNT(x)        ((x) << USBFS_DOEPLEN_STPCNT_Pos)
#define USBFS_DOEPLEN_PCNT_Pos         19
#define USBFS_DOEPLEN_PCNT_Msk         _AC(0x1ff80000,U)    /*!< packet count */
#define USBFS_DOEPLEN_PCNT(x)          ((x) << USBFS_DOEPLEN_PCNT_Pos)
#define USBFS_DOEPLEN_TLEN_Pos         0
#define USBFS_DOEPLEN_TLEN_Msk         _AC(0x0007ffff,U)    /*!< transfer length */
#define USBFS_DOEPLEN_TLEN(x)          ((x) << USBFS_DOEPLEN_TLEN_Pos)

/* USBFS_DIEPxTFSTAT, x = 0..3 */
#define USBFS_DIEPTFSTAT_IEPTFS_Pos    0
#define USBFS_DIEPTFSTAT_IEPTFS_Msk    _AC(0x0000ffff,U)    /*!< IN endpoint Tx FIFO space remaining */
#define USBFS_DIEPTFSTAT_IEPTFS(x)     ((x) << USBFS_DIEPTFSTAT_IEPTFS_Pos)

/* USBFS_PWRCLKCTL */
#define USBFS_PWRCLKCTL_SHCLK          _BIT(1,U)            /*!< stop HCLK */
#define USBFS_PWRCLKCTL_SUCLK          _BIT(0,U)            /*!< stop the USB clock */

/* --------------------- WWDGT -------------------------- */

#define WWDGT_BASE                     _AC(0x40002C00,UL)  /*!< WWDGT base address */

/* register definitions */
#define WWDGT_CTL                      _AC(0x00,UL)  /*!< WWDGT control register */
#define WWDGT_CFG                      _AC(0x04,UL)  /*!< WWDGT configuration register */
#define WWDGT_STAT                     _AC(0x08,UL)  /*!< WWDGT status register */

/* WWDGT_CTL */
#define WWDGT_CTL_WDGTEN               _BIT(7,U)          /*!< WWDGT counter enable */
#define WWDGT_CTL_CNT_Pos              0
#define WWDGT_CTL_CNT_Msk              _AC(0x0000007f,U)  /*!< WWDGT counter value */
#define WWDGT_CTL_CNT(x)               ((x) << WWDGT_CTL_CNT_Pos)

/* WWDGT_CFG */
#define WWDGT_CFG_EWIE                 _BIT(9,U)          /*!< early wakeup interrupt enable */
#define WWDGT_CFG_PSC_Pos              7
#define WWDGT_CFG_PSC_Msk              _AC(0x00000180,U)  /*!< WWDGT prescaler divider value */
#define WWDGT_CFG_PSC(x)               ((x) << WWDGT_CFG_PSC_Pos)
#define WWDGT_CFG_PSC_DIV1             WWDGT_CFG_PSC(0)   /*!< the time base of WWDGT = (PCLK1/4096)/1 */
#define WWDGT_CFG_PSC_DIV2             WWDGT_CFG_PSC(1)   /*!< the time base of WWDGT = (PCLK1/4096)/2 */
#define WWDGT_CFG_PSC_DIV4             WWDGT_CFG_PSC(2)   /*!< the time base of WWDGT = (PCLK1/4096)/4 */
#define WWDGT_CFG_PSC_DIV8             WWDGT_CFG_PSC(3)   /*!< the time base of WWDGT = (PCLK1/4096)/8 */
#define WWDGT_CFG_WIN_Pos              0
#define WWDGT_CFG_WIN_Msk              _AC(0x0000007f,U)  /*!< WWDGT counter window value */
#define WWDGT_CFG_WIN(x)               ((x) << WWDGT_CFG_WIN_Pos)

/* WWDGT_STAT */
#define WWDGT_STAT_EWIF                _BIT(0,U)          /*!< early wakeup interrupt flag */

#ifndef __ASSEMBLER__
#include <stdint.h>

typedef struct gd32vf103_adc {
    volatile uint32_t STAT;
    volatile uint32_t CTL0;
    volatile uint32_t CTL1;
    volatile uint32_t SAMPT0;
    volatile uint32_t SAMPT1;
    union {
        volatile uint32_t IOFF[4];
        struct {
            volatile uint32_t IOFF0;
            volatile uint32_t IOFF1;
            volatile uint32_t IOFF2;
            volatile uint32_t IOFF3;
        };
    };
    volatile uint32_t WDHT;
    volatile uint32_t WDLT;
    volatile uint32_t RSQ0;
    volatile uint32_t RSQ1;
    volatile uint32_t RSQ2;
    volatile uint32_t ISQ;
    union {
        volatile uint32_t IDATA[4];
        struct {
            volatile uint32_t IDATA0;
            volatile uint32_t IDATA1;
            volatile uint32_t IDATA2;
            volatile uint32_t IDATA3;
        };
    };
    volatile uint32_t RDATA;
    uint32_t reserved1[12];
    volatile uint32_t OVSAMPCTL;
} gd32vf103_adc_t;

typedef struct gd32vf103_bkp_data {
    uint16_t reserved;
    volatile uint16_t DATA;
} gd32vf103_bkp_data_t;

typedef struct gd32vf103_bkp {
    uint32_t reserved1;
    struct gd32vf103_bkp_data DATA0_9[10];
    volatile uint32_t OCTL;
    volatile uint32_t TPCTL;
    volatile uint32_t TPCS;
    uint32_t reserved2;
    uint32_t reserved3;
    struct gd32vf103_bkp_data DATA10_41[32];
} gd32vf103_bkp_t;

typedef struct gd32vf103_can_mailbox {
    volatile uint32_t I;
    volatile uint32_t P;
    volatile uint32_t DATA0;
    volatile uint32_t DATA1;
} gd32vf103_can_mailbox_t;

typedef struct gd32vf103_can_filter {
    volatile uint32_t DATA0;
    volatile uint32_t DATA1;
} gd32vf103_can_filter_t;

typedef struct gd32vf103_can {
    volatile uint32_t CTL;
    volatile uint32_t STAT;
    volatile uint32_t TSTAT;
    volatile uint32_t RFIFO0;
    volatile uint32_t RFIFO1;
    volatile uint32_t INTEN;
    volatile uint32_t ERR;
    volatile uint32_t BT;
    uint32_t reserved1[88];
    union {
        struct gd32vf103_can_mailbox TM[3];
        struct {
            volatile uint32_t TMI0;
            volatile uint32_t TMP0;
            volatile uint32_t TMDATA00;
            volatile uint32_t TMDATA10;
            volatile uint32_t TMI1;
            volatile uint32_t TMP1;
            volatile uint32_t TMDATA01;
            volatile uint32_t TMDATA11;
            volatile uint32_t TMI2;
            volatile uint32_t TMP2;
            volatile uint32_t TMDATA02;
            volatile uint32_t TMDATA12;
        };
    };
    union {
        struct gd32vf103_can_mailbox RFIFOM[2];
        struct {
            volatile uint32_t RFIFOMI0;
            volatile uint32_t RFIFOMP0;
            volatile uint32_t RFIFOMDATA00;
            volatile uint32_t RFIFOMDATA10;
            volatile uint32_t RFIFOMI1;
            volatile uint32_t RFIFOMP1;
            volatile uint32_t RFIFOMDATA01;
            volatile uint32_t RFIFOMDATA11;
        };
    };
    uint32_t reserved2[12];
    volatile uint32_t FCTL;
    volatile uint32_t FMCFG;
    uint32_t reserved3;
    volatile uint32_t FSCFG;
    uint32_t reserved4;
    volatile uint32_t FAFIFO;
    uint32_t reserved5;
    volatile uint32_t FW;
    uint32_t reserved6[8];
    struct gd32vf103_can_filter F[28];
} gd32vf103_can_t;

typedef struct gd32vf103_crc {
    volatile uint32_t DATA;
    volatile uint32_t FDATA;
    volatile uint32_t CTL;
} gd32vf103_crc_t;

typedef struct gd32vf103_dac {
    volatile uint32_t CTL;
    volatile uint32_t SWT;
    volatile uint32_t R12DH0;
    volatile uint32_t L12DH0;
    volatile uint32_t R8DH0;
    volatile uint32_t R12DH1;
    volatile uint32_t L12DH1;
    volatile uint32_t R8DH1;
    volatile uint32_t R12DHC;
    volatile uint32_t L12DHC;
    volatile uint32_t R8DHC;
    volatile uint32_t DO0;
    volatile uint32_t DO1;
} gd32vf103_dac_t;

typedef struct gd32vf103_dbg {
    const uint32_t ID;
    volatile uint32_t CTL;
    volatile uint32_t CMD;
    volatile uint32_t KEY;
} gd32vf103_dbg_t;

typedef struct gd32vf103_dma_channel {
    volatile uint32_t CTL;
    volatile uint32_t CNT;
    volatile uint32_t PADDR;
    volatile uint32_t MADDR;
    uint32_t reserved;
} gd32vf103_dma_channel_t;

typedef struct gd32vf103_dma {
    volatile uint32_t INTF;
    volatile uint32_t INTC;
    union {
        struct gd32vf103_dma_channel CH[7];
        struct {
            volatile uint32_t CH0CTL;
            volatile uint32_t CH0CNT;
            volatile uint32_t CH0PADDR;
            volatile uint32_t CH0MADDR;
            uint32_t reserved0;
            volatile uint32_t CH1CTL;
            volatile uint32_t CH1CNT;
            volatile uint32_t CH1PADDR;
            volatile uint32_t CH1MADDR;
            uint32_t reserved1;
            volatile uint32_t CH2CTL;
            volatile uint32_t CH2CNT;
            volatile uint32_t CH2PADDR;
            volatile uint32_t CH2MADDR;
            uint32_t reserved2;
            volatile uint32_t CH3CTL;
            volatile uint32_t CH3CNT;
            volatile uint32_t CH3PADDR;
            volatile uint32_t CH3MADDR;
            uint32_t reserved3;
            volatile uint32_t CH4CTL;
            volatile uint32_t CH4CNT;
            volatile uint32_t CH4PADDR;
            volatile uint32_t CH4MADDR;
            uint32_t reserved4;
            volatile uint32_t CH5CTL;
            volatile uint32_t CH5CNT;
            volatile uint32_t CH5PADDR;
            volatile uint32_t CH5MADDR;
            uint32_t reserved5;
            volatile uint32_t CH6CTL;
            volatile uint32_t CH6CNT;
            volatile uint32_t CH6PADDR;
            volatile uint32_t CH6MADDR;
            uint32_t reserved6;
        };
    };
} gd32vf103_dma_t;

typedef struct gd32vf103_eclic {
    volatile uint8_t cfg;
    uint8_t reserved1[3];
    const uint32_t info;
    uint8_t reserved2[3];
    volatile uint8_t mth;
    uint32_t reserved3[1021];
    struct {
        volatile uint8_t ip;
        volatile uint8_t ie;
        volatile uint8_t attr;
        volatile uint8_t ctl;
    } clicint[];
} gd32vf103_eclic_t;

typedef struct gd32vf103_exmc {
    volatile uint32_t SNCTL0;
    volatile uint32_t SNTCFG0;
    uint32_t reserved1[63];
    volatile uint32_t SNWTCFG0;
} gd32vf103_exmc_t;

typedef struct gd32vf103_exti {
    volatile uint32_t INTEN;
    volatile uint32_t EVEN;
    volatile uint32_t RTEN;
    volatile uint32_t FTEN;
    volatile uint32_t SWIEV;
    volatile uint32_t PD;
} gd32vf103_exti_t;

typedef struct gd32vf103_fmc {
    volatile uint32_t WS;
    volatile uint32_t KEY;
    volatile uint32_t OBKEY;
    volatile uint32_t STAT;
    volatile uint32_t CTL;
    volatile uint32_t ADDR;
    const uint32_t OBSTAT;
    const uint32_t WP;
    uint32_t reserved[56];
    const uint32_t PID;
} gd32vf103_fmc_t;

typedef struct gd32vf103_ob {
    volatile uint16_t SPC;
    volatile uint16_t USER;
    union {
        volatile uint32_t DATA;
        struct {
            volatile uint16_t DATA_LO;
            volatile uint16_t DATA_HI;
        };
    };
    volatile uint16_t WP0;
    volatile uint16_t WP1;
    volatile uint16_t WP2;
    volatile uint16_t WP3;
} gd32vf103_ob_t;

typedef struct gd32vf103_fwdgt {
    volatile uint32_t CTL;
    volatile uint32_t PSC;
    volatile uint32_t RLD;
    volatile uint32_t STAT;
} gd32vf103_fwdgt_t;

typedef struct gd32vf103_afio {
    volatile uint32_t EC;
    volatile uint32_t PCF0;
    union {
        volatile uint32_t EXTISS[4];
        struct {
            volatile uint32_t EXTISS0;
            volatile uint32_t EXTISS1;
            volatile uint32_t EXTISS2;
            volatile uint32_t EXTISS3;
        };
    };
    uint32_t reserved1;
    volatile uint32_t PCF1;
} gd32vf103_afio_t;

typedef struct gd32vf103_gpio {
    volatile uint32_t CTL0;
    volatile uint32_t CTL1;
    volatile uint32_t ISTAT;
    volatile uint32_t OCTL;
    volatile uint32_t BOP;
    volatile uint32_t BC;
    volatile uint32_t LOCK;
} gd32vf103_gpio_t;

typedef struct gd32vf103_i2c {
    volatile uint32_t CTL0;
    volatile uint32_t CTL1;
    volatile uint32_t SADDR0;
    volatile uint32_t SADDR1;
    volatile uint32_t DATA;
    volatile uint32_t STAT0;
    volatile uint32_t STAT1;
    volatile uint32_t CKCFG;
    volatile uint32_t RT;
} gd32vf103_i2c_t;

typedef struct gd32vf103_info {
    const uint16_t FLASH;
    const uint16_t SRAM;
    uint32_t reserved1;
    const uint32_t ID[3];
} gd32vf103_info_t;


typedef struct gd32vf103_mtimer {
    volatile uint32_t mtime_lo;
    volatile uint32_t mtime_hi;
    volatile uint32_t mtimecmp_lo;
    volatile uint32_t mtimecmp_hi;
    uint32_t reserved1[1018];
    volatile uint32_t mstop;
    volatile uint32_t msip;
} gd32vf103_mtimer_t;

typedef struct gd32vf103_pmu {
    volatile uint32_t CTL;
    volatile uint32_t CS;
} gd32vf103_pmu_t;

typedef struct gd32vf103_rcu {
    volatile uint32_t CTL;
    volatile uint32_t CFG0;
    volatile uint32_t INT;
    volatile uint32_t APB2RST;
    volatile uint32_t APB1RST;
    volatile uint32_t AHBEN;
    volatile uint32_t APB2EN;
    volatile uint32_t APB1EN;
    volatile uint32_t BDCTL;
    volatile uint32_t RSTSCK;
    volatile uint32_t AHBRST;
    volatile uint32_t CFG1;
    uint32_t reserved1;
    volatile uint32_t DSV;
} gd32vf103_rcu_t;

typedef struct gd32vf103_rtc {
    volatile uint32_t INTEN;
    volatile uint32_t RTL;
    volatile uint32_t PSCH;
    volatile uint32_t PSCL;
    volatile uint32_t DIVH;
    volatile uint32_t DIVL;
    volatile uint32_t CNTH;
    volatile uint32_t CNTL;
    volatile uint32_t ALRMH;
    volatile uint32_t ALRML;
} gd32vf103_rtc_t;

typedef struct gd32vf103_spi {
    volatile uint32_t CTL0;
    volatile uint32_t CTL1;
    volatile uint32_t STAT;
    volatile uint32_t DATA;
    volatile uint32_t CRCPOLY;
    volatile uint32_t RCRC;
    volatile uint32_t TCRC;
    volatile uint32_t I2SCTL;
    volatile uint32_t I2SPSC;
} gd32vf103_spi_t;

typedef struct gd32vf103_timer {
    volatile uint32_t CTL0;
    volatile uint32_t CTL1;
    volatile uint32_t SMCFG;
    volatile uint32_t DMAINTEN;
    volatile uint32_t INTF;
    volatile uint32_t SWEVG;
    volatile uint32_t CHCTL0;
    volatile uint32_t CHCTL1;
    volatile uint32_t CHCTL2;
    volatile uint32_t CNT;
    volatile uint32_t PSC;
    volatile uint32_t CAR;
    volatile uint32_t CREP;
    volatile uint32_t CH0CV;
    volatile uint32_t CH1CV;
    volatile uint32_t CH2CV;
    volatile uint32_t CH3CV;
    volatile uint32_t CCHP;
    volatile uint32_t DMACFG;
    volatile uint32_t DMATB;
} gd32vf103_timer_t;

typedef struct gd32vf103_usart {
    volatile uint32_t STAT;
    volatile uint32_t DATA;
    volatile uint32_t BAUD;
    volatile uint32_t CTL0;
    volatile uint32_t CTL1;
    volatile uint32_t CTL2;
    volatile uint32_t GP;
} gd32vf103_usart_t;

typedef struct gd32vf103_usbfs_hch {
    volatile uint32_t CTL;                          /*!< USB host channel control register          */
    uint32_t reserved1;                             /*!< reserved (STCTL)                           */
    volatile uint32_t INTF;                         /*!< USB host channel interrupt flag register   */
    volatile uint32_t INTEN;                        /*!< USB host channel interrupt enable register */
    volatile uint32_t LEN;                          /*!< USB host channel transfer length register  */
    uint32_t reserved2[3];                          /*!< reserved (DMAADDR)                         */
} gd32vf103_usbfs_hch_t;

typedef struct gd32vf103_usbfs_diep {
    volatile uint32_t CTL;                          /*!< USB device IN endpoint control register              */
    uint32_t reserved1;                             /*!< reserved                                             */
    volatile uint32_t INTF;                         /*!< USB device IN endpoint interrupt flag register       */
    uint32_t reserved2;                             /*!< reserved                                             */
    volatile uint32_t LEN;                          /*!< USB device IN endpoint transfer length register      */
    uint32_t reserved3;                             /*!< reserved (DMAADDR)                                   */
    volatile uint32_t TFSTAT;                       /*!< USB device IN endpoint transmit FIFO status register */
    uint32_t reserved4;                             /*!< reserved                                             */
} gd32vf103_usbfs_diep_t;

typedef struct gd32vf103_usbfs_doep {
    volatile uint32_t CTL;                          /*!< USB device IN endpoint control register         */
    uint32_t reserved1;                             /*!< reserved                                        */
    volatile uint32_t INTF;                         /*!< USB device IN endpoint interrupt flag register  */
    uint32_t reserved2;                             /*!< reserved                                        */
    volatile uint32_t LEN;                          /*!< USB device IN endpoint transfer length register */
    uint32_t reserved3[3];                          /*!< reserved (DMAADDR)                              */
} gd32vf103_usbfs_doep_t;

typedef struct gd32vf103_usbfs {
    volatile uint32_t GOTGCS;                       /*!< USB global OTG control and status register                  000h */
    volatile uint32_t GOTGINTF;                     /*!< USB global OTG interrupt flag register                      004h */
    volatile uint32_t GAHBCS;                       /*!< USB global AHB control and status register                  008h */
    volatile uint32_t GUSBCS;                       /*!< USB global USB control and status register                  00Ch */
    volatile uint32_t GRSTCTL;                      /*!< USB global reset control register                           010h */
    volatile uint32_t GINTF;                        /*!< USB global interrupt flag register                          014h */
    volatile uint32_t GINTEN;                       /*!< USB global interrupt enable register                        018h */
    volatile uint32_t GRSTATR;                      /*!< USB receive status debug read register                      01Ch */
    volatile uint32_t GRSTATP;                      /*!< USB receive status and pop register                         020h */
    volatile uint32_t GRFLEN;                       /*!< USB global receive FIFO length register                     024h */
    union {
        volatile uint32_t DIEP0TFLEN_HNPTFLEN;  /*!< USB device IN endpoint 0/host non-periodic transmit FIFO length 028h */
        volatile uint32_t HNPTFLEN;             /*!< USB host non-periodic transmit FIFO length                  028h */
        volatile uint32_t DIEP0TFLEN;           /*!< USB device IN endpoint 0 transmit FIFO length               028h */
    };
    volatile uint32_t HNPTFQSTAT;                   /*!< USB host non-periodic FIFO/queue status register            02Ch */
    uint32_t reserved1[2];                          /*!< reserved                                               030h-037h */
    volatile uint32_t GCCFG;                        /*!< USB global core configuration register                      038h */
    volatile uint32_t CID;                          /*!< USB core ID register                                        03Ch */
    uint32_t reserved2[48];                         /*!< reserved                                               040h-0FFh */
    volatile uint32_t HPTFLEN;                      /*!< USB host periodic transmit FIFO length register             100h */
    volatile uint32_t DIEP1TFLEN;                   /*!< USB device IN endpoint 1 transmit FIFO length               104h */
    volatile uint32_t DIEP2TFLEN;                   /*!< USB device IN endpoint 2 transmit FIFO length               108h */
    volatile uint32_t DIEP3TFLEN;                   /*!< USB device IN endpoint 3 transmit FIFO length               10Ch */
    uint32_t reserved3[188];                        /*!< reserved                                               110h-3FFh */
    volatile uint32_t HCTL;                         /*!< USB host control register                                   400h */
    volatile uint32_t HFT;                          /*!< USB host frame interval register                            404h */
    volatile uint32_t HFINFR;                       /*!< USB host frame information remaining register               408h */
    uint32_t reserved4;                             /*!< reserved                                                    40Ch */
    volatile uint32_t HPTFQSTAT;                    /*!< USB host periodic transmit FIFO/queue status register       410h */
    volatile uint32_t HACHINT;                      /*!< USB host all channels interrupt register                    414h */
    volatile uint32_t HACHINTEN;                    /*!< USB host all channels interrupt enable register             418h */
    uint32_t reserved5[9];                          /*!< reserved                                               41Ch-43Fh */
    volatile uint32_t HPCS;                         /*!< USB host port control and status register                   440h */
    uint32_t reserved6[47];                         /*!< reserved                                               444h-4FFh */
    struct gd32vf103_usbfs_hch HCH[8];              /*                                                          500h-5FFh */
    uint32_t reserved7[128];                        /*!< reserved                                               600h-7FFh */
    volatile uint32_t DCFG;                         /*!< USB device configuration register                           800h */
    volatile uint32_t DCTL;                         /*!< USB device control register                                 804h */
    volatile uint32_t DSTAT;                        /*!< USB device status register                                  808h */
    uint32_t reserved8;                             /*!< reserved                                                    80Ch */
    volatile uint32_t DIEPINTEN;                    /*!< USB device IN endpoint common interrupt enable register     810h */
    volatile uint32_t DOEPINTEN;                    /*!< USB device OUT endpoint common interrupt enable register    814h */
    volatile uint32_t DAEPINT;                      /*!< USB device all endpoints interrupt register                 818h */
    volatile uint32_t DAEPINTEN;                    /*!< USB device all endpoints interrupt enable register          81Ch */
    uint32_t reserved9[2];                          /*!< reserved                                               820h-827h */
    volatile uint32_t DVBUSDT;                      /*!< USB device VBUS discharge time register                     828h */
    volatile uint32_t DVBUSPT;                      /*!< USB device VBUS pulsing time register                       82Ch */
    uint32_t reserved10;                            /*!< reserved                                                    830h */
    volatile uint32_t DIEPFEINTEN;                  /*!< USB Device IN endpoint FIFO empty interrupt enable register 834h */
    uint32_t reserved11[50];                        /*!< reserved                                               838h-8FFh */
    struct gd32vf103_usbfs_diep DIEP[4];            /*                                                          900h-97Fh */
    uint32_t reserved12[96];                        /*!< reserved                                               980h-B00h */
    struct gd32vf103_usbfs_doep DOEP[4];            /*                                                          B00h-B7Fh */
    uint32_t reserved13[160];                       /*!< reserved                                               B80h-DFFh */
    volatile uint32_t PWRCLKCTL;                    /*!< USB power and clock control register                        E00h */
    uint32_t reserved14[127];                       /*!< reserved                                               E04h-FFFh */
    volatile uint32_t DFIFO[4][1024];
} gd32vf103_usbfs_t;

typedef struct gd32vf103_wwdgt {
    volatile uint32_t CTL;
    volatile uint32_t CFG;
    volatile uint32_t STAT;
} gd32vf103_wwdgt_t;

static struct gd32vf103_adc *const ADC0 = (struct gd32vf103_adc *)ADC0_BASE;
static struct gd32vf103_adc *const ADC1 = (struct gd32vf103_adc *)ADC1_BASE;
static struct gd32vf103_bkp *const BKP = (struct gd32vf103_bkp *)BKP_BASE;
static struct gd32vf103_can *const CAN0 = (struct gd32vf103_can *)CAN0_BASE;
static struct gd32vf103_can *const CAN1 = (struct gd32vf103_can *)CAN1_BASE;
static struct gd32vf103_crc *const CRC = (struct gd32vf103_crc *)CRC_BASE;
static struct gd32vf103_dac *const DAC = (struct gd32vf103_dac *)DAC_BASE;
static struct gd32vf103_dbg *const DBG = (struct gd32vf103_dbg *)DBG_BASE;
static struct gd32vf103_dma *const DMA0 = (struct gd32vf103_dma *)DMA0_BASE;
static struct gd32vf103_dma *const DMA1 = (struct gd32vf103_dma *)DMA1_BASE;
static struct gd32vf103_eclic *const ECLIC = (struct gd32vf103_eclic *)ECLIC_BASE;
static struct gd32vf103_exmc *const EXMC = (struct gd32vf103_exmc *)EXMC_BASE;
static struct gd32vf103_exti *const EXTI = (struct gd32vf103_exti *)EXTI_BASE;
static struct gd32vf103_fmc *const FMC = (struct gd32vf103_fmc *)FMC_BASE;
static struct gd32vf103_ob *const OB = (struct gd32vf103_ob *)OB_BASE;
static struct gd32vf103_fwdgt *const FWDGT = (struct gd32vf103_fwdgt *)FWDGT_BASE;
static struct gd32vf103_afio *const AFIO  = (struct gd32vf103_afio *)AFIO_BASE;
static struct gd32vf103_gpio *const GPIOA = (struct gd32vf103_gpio *)GPIOA_BASE;
static struct gd32vf103_gpio *const GPIOB = (struct gd32vf103_gpio *)GPIOB_BASE;
static struct gd32vf103_gpio *const GPIOC = (struct gd32vf103_gpio *)GPIOC_BASE;
#if defined(GD32VF103R4T6) || defined(GD32VF103R6T6) || defined(GD32VF103R8T6) || \
    defined(GD32VF103RBT6) || defined(GD32VF103V8T6) || defined(GD32VF103VBT6)
    static struct gd32vf103_gpio *const GPIOD = (struct gd32vf103_gpio *)GPIOD_BASE;
#endif
#if defined(GD32VF103V8T6) || defined(GD32VF103VBT6)
    static struct gd32vf103_gpio *const GPIOE = (struct gd32vf103_gpio *)GPIOE_BASE;
#endif
static struct gd32vf103_i2c *const I2C0 = (struct gd32vf103_i2c *)I2C0_BASE;
#if defined(GD32VF103C8T6) || defined(GD32VF103CBT6) || defined(GD32VF103R8T6) || \
    defined(GD32VF103RBT6) || defined(GD32VF103V8T6) || defined(GD32VF103VBT6)
    static struct gd32vf103_i2c *const I2C1 = (struct gd32vf103_i2c *)I2C1_BASE;
#endif
static struct gd32vf103_info *const INFO = (struct gd32vf103_info *)INFO_BASE;
static struct gd32vf103_mtimer *const MTIMER = (struct gd32vf103_mtimer *)MTIMER_BASE;
static struct gd32vf103_pmu *const PMU = (struct gd32vf103_pmu *)PMU_BASE;
static struct gd32vf103_rcu *const RCU = (struct gd32vf103_rcu *)RCU_BASE;
static struct gd32vf103_rtc *const RTC = (struct gd32vf103_rtc *)RTC_BASE;
static struct gd32vf103_spi *const SPI0 = (struct gd32vf103_spi *)SPI0_BASE;
#if defined(GD32VF103C8T6) || defined(GD32VF103CBT6) || defined(GD32VF103R8T6) || \
    defined(GD32VF103RBT6) || defined(GD32VF103V8T6) || defined(GD32VF103VBT6)
    static struct gd32vf103_spi *const SPI1 = (struct gd32vf103_spi *)SPI1_BASE;
    static struct gd32vf103_spi *const SPI2 = (struct gd32vf103_spi *)SPI2_BASE;
#endif
static struct gd32vf103_timer *const TIMER0 = (struct gd32vf103_timer *)TIMER0_BASE;
static struct gd32vf103_timer *const TIMER1 = (struct gd32vf103_timer *)TIMER1_BASE;
static struct gd32vf103_timer *const TIMER2 = (struct gd32vf103_timer *)TIMER2_BASE;
#if defined(GD32VF103C8T6) || defined(GD32VF103CBT6) || \
    defined(GD32VF103R8T6) || defined(GD32VF103RBT6) || \
    defined(GD32VF103T8U6) || defined(GD32VF103TBU6) || \
    defined(GD32VF103V8T6) || defined(GD32VF103VBT6)
    static struct gd32vf103_timer *const TIMER3 = (struct gd32vf103_timer *)TIMER3_BASE;
    static struct gd32vf103_timer *const TIMER4 = (struct gd32vf103_timer *)TIMER4_BASE;
#endif
static struct gd32vf103_usart *const USART0 = (struct gd32vf103_usart *)USART0_BASE;
static struct gd32vf103_usart *const USART1 = (struct gd32vf103_usart *)USART1_BASE;
#if defined(GD32VF103C8T6) || defined(GD32VF103CBT6) || defined(GD32VF103R8T6) || \
    defined(GD32VF103RBT6) || defined(GD32VF103V8T6) || defined(GD32VF103VBT6)
    static struct gd32vf103_usart *const USART2 = (struct gd32vf103_usart *)USART2_BASE;
#endif
#if defined(GD32VF103R8T6) || defined(GD32VF103RBT6) || \
    defined(GD32VF103V8T6) || defined(GD32VF103VBT6)
    static struct gd32vf103_usart *const UART3  = (struct gd32vf103_usart *)UART3_BASE;
    static struct gd32vf103_usart *const UART4  = (struct gd32vf103_usart *)UART4_BASE;
#endif
static struct gd32vf103_usbfs *const USBFS = (struct gd32vf103_usbfs *)USBFS_BASE;
static struct gd32vf103_wwdgt *const WWDGT = (struct gd32vf103_wwdgt *)WWDGT_BASE;

#endif
#endif
