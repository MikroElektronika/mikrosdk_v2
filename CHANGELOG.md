# CHANGELOG

*All notable changes to this project shall be documented in this file.*

**VERSIONS:**

+ **[v2.1.0](#v210)**
+ **[v2.0.3](#v203)**
+ **[v2.0.2](#v202)**
+ **[v2.0.1](#v201)**
+ **[v2.0.0](#v200)**

---
---
---

## `v2.1.0`

- released: 2021-04-29

### `2.1.0` Changes

1. **[PIC32 low level hal support](#pic32-sdk)**
2. **[NEW HARDWARE](#new-hardware)**
3. Updated relevant **manifest files**
4. Updated relevant **[development kit package](#development-kit-package)**
5. **[Fixes](#210-fixes)**
6. **[Improvements](#210-improvements)**
5. **[GIT relevant updates](#git-relevant-updates)**
6. **[Collaborators](#collaborators)**

#### <font color=red>PIC32 SDK</font>

- **Support added for 163 PIC32 MCU's**

**MX CHIPS:**

| CHIP NAME       | CHIP NAME        | CHIP NAME       | CHIP NAME        | CHIP NAME       |
|-----------------|------------------|-----------------|------------------|-----------------|
| PIC32MX110F016B | PIC32MX210F016B  | PIC32MX320F032H | PIC32MX440F256H  | PIC32MX570F512L |
| PIC32MX110F016C | PIC32MX210F016C  | PIC32MX320F064H | PIC32MX440F512H  | PIC32MX575F256H |
| PIC32MX110F016D | PIC32MX210F016D  | PIC32MX320F128H | PIC32MX450F128H  | PIC32MX575F256L |
| PIC32MX120F032B | PIC32MX220F032B  | PIC32MX320F128L | PIC32MX450F128L  | PIC32MX575F512H |
| PIC32MX120F032C | PIC32MX220F032C  | PIC32MX330F064H | PIC32MX450F256H  | PIC32MX575F512L |
| PIC32MX120F032D | PIC32MX220F032D  | PIC32MX330F064L | PIC32MX450F256HB | PIC32MX664F064H |
| PIC32MX120F064H | PIC32MX230F064B  | PIC32MX340F128H | PIC32MX450F256L  | PIC32MX664F064L |
| PIC32MX130F064B | PIC32MX230F064C  | PIC32MX340F128L | PIC32MX460F256L  | PIC32MX664F128H |
| PIC32MX130F064C | PIC32MX230F064D  | PIC32MX340F256H | PIC32MX460F512L  | PIC32MX664F128L |
| PIC32MX130F064D | PIC32MX230F128H  | PIC32MX340F512H | PIC32MX470F512H  | PIC32MX675F256H |
| PIC32MX130F128H | PIC32MX230F128L  | PIC32MX350F128H | PIC32MX470F512L  | PIC32MX675F256L |
| PIC32MX130F128L | PIC32MX230F256B  | PIC32MX350F128L | PIC32MX470F512LB | PIC32MX675F512H |
| PIC32MX130F256B | PIC32MX230F256D  | PIC32MX350F256H | PIC32MX530F128H  | PIC32MX675F512L |
| PIC32MX130F256D | PIC32MX250F128B  | PIC32MX350F256L | PIC32MX530F128L  | PIC32MX695F512H |
| PIC32MX150F128B | PIC32MX250F128C  | PIC32MX360F256L | PIC32MX534F064H  | PIC32MX695F512L |
| PIC32MX150F128C | PIC32MX250F128D  | PIC32MX360F512L | PIC32MX534F064L  | PIC32MX764F128H |
| PIC32MX150F128D | PIC32MX250F256H  | PIC32MX370F512H | PIC32MX550F256H  | PIC32MX764F128L |
| PIC32MX150F256H | PIC32MX250F256L  | PIC32MX370F512L | PIC32MX550F256L  | PIC32MX775F256H |
| PIC32MX150F256L | PIC32MX270F256B  | PIC32MX420F032H | PIC32MX564F064H  | PIC32MX775F256L |
| PIC32MX170F256B | PIC32MX270F256D  | PIC32MX430F064H | PIC32MX564F064L  | PIC32MX775F512H |
| PIC32MX170F256D | PIC32MX270F256DB | PIC32MX430F064L | PIC32MX564F128H  | PIC32MX775F512L |
| PIC32MX170F512H | PIC32MX270F512H  | PIC32MX440F128H | PIC32MX564F128L  | PIC32MX795F512H |
| PIC32MX170F512L | PIC32MX270F512L  | PIC32MX440F128L | PIC32MX570F512H  | PIC32MX795F512L |

**MZ CHIPS:**

| CHIP NAME         | CHIP NAME         | CHIP NAME         | CHIP NAME         |
|-------------------|-------------------|-------------------|-------------------|
| PIC32MZ0512EFE064 | PIC32MZ1024EFE064 | PIC32MZ1024EFH064 | PIC32MZ2048EFG064 |
| PIC32MZ0512EFE100 | PIC32MZ1024EFE100 | PIC32MZ1024EFH100 | PIC32MZ2048EFG100 |
| PIC32MZ0512EFE124 | PIC32MZ1024EFE124 | PIC32MZ1024EFH124 | PIC32MZ2048EFG124 |
| PIC32MZ0512EFE144 | PIC32MZ1024EFE144 | PIC32MZ1024EFH144 | PIC32MZ2048EFG144 |
| PIC32MZ0512EFF064 | PIC32MZ1024EFF064 | PIC32MZ1024EFK064 | PIC32MZ2048EFH064 |
| PIC32MZ0512EFF100 | PIC32MZ1024EFF100 | PIC32MZ1024EFK100 | PIC32MZ2048EFH100 |
| PIC32MZ0512EFF124 | PIC32MZ1024EFF124 | PIC32MZ1024EFK124 | PIC32MZ2048EFH124 |
| PIC32MZ0512EFF144 | PIC32MZ1024EFF144 | PIC32MZ1024EFK144 | PIC32MZ2048EFH144 |
| PIC32MZ0512EFK064 | PIC32MZ1024EFG064 | PIC32MZ1024EFM064 | PIC32MZ2048EFM064 |
| PIC32MZ0512EFK100 | PIC32MZ1024EFG100 | PIC32MZ1024EFM100 | PIC32MZ2048EFM100 |
| PIC32MZ0512EFK124 | PIC32MZ1024EFG124 | PIC32MZ1024EFM124 | PIC32MZ2048EFM124 |
| PIC32MZ0512EFK144 | PIC32MZ1024EFG144 | PIC32MZ1024EFM144 | PIC32MZ2048EFM144 |

**Supported modules:**

1. **ADC**
   - Full module support
   - Note --> PIC32 MX chips have a fixed resolution of 10-bit (hw specific)
2. **SPI**
   - Full module support
3. **UART**
   - Full module support
   - Implemented using interrupts
4. **I2C**
   - Full module support
5. **PWM**
   - Full module support
6. **GPIO**
   - Full module support

#### NEW HARDWARE

1. **[Fusion for PIC32 v8](https://www.mikroe.com/fusion-for-pic32)**
   - Added adequate board definition files
   - Updated adequate manifest files
   - Configuration files updated
2. **[EasyPIC Fusion v7](https://www.mikroe.com/easypic-fusion)**
   - Added adequate board definition files
   - Updated adequate manifest files
   - Configuration files updated
3. **[PIC32MX Clicker](https://www.mikroe.com/clicker-pic32mx)**
   - Added adequate board definition files
   - Updated adequate manifest files
   - Configuration files updated
4. **[PIC32MZ Clicker](https://www.mikroe.com/pic32mz-clicker)**
   - Added adequate board definition files
   - Updated adequate manifest files
   - Configuration files updated
5. **[Clicker 2 for PIC32MX](https://www.mikroe.com/clicker-2-pic32mx)**
   - Added adequate board definition files
   - Updated adequate manifest files
   - Configuration files updated
6. **[Clicker 2 for PIC32MZ](https://www.mikroe.com/clicker-2-for-pic32mz)**
   - Added adequate board definition files
   - Updated adequate manifest files
   - Configuration files updated
7. **[Flip&Click PIC32MZ](https://www.mikroe.com/flipclick-pic32mz)**
   - Added adequate board definition files
   - Updated adequate manifest files
   - Configuration files updated

**Config files added for adequate `NEW` boards.**

#### DEVELOPMENT KIT PACKAGE

Updated **[mikroSDK development kit](./development/readme.md)** to follow added hardware.

### `2.1.0` Fixes

1. **`hal_ll_bit_control.h`**
   - Implemented guard for unintentional bit manipulation using expressions
   - Changed files:
      -  **[PIC file](./targets/pic_8bit/mikroe/common/include/hal_ll_bit_control.h)**
      -  **[PIC32 file](./targets/pic_32bit/mikroe/common/include/hal_ll_bit_control.h)**
      -  **[STM32 file](./targets/arm/mikroe/common/include/hal_ll_bit_control.h)**

### `2.1.0` Improvements

1. Updated all ADC memake files
   - Default resolution is now dependent on adequate python regex
2. Clicker 2 for PIC18FK
   - Default UART board pins changed to USB connector
   - Pins are now `RC0` and `RC1`
3. All ADC module resolutions are now set to hardware specific values
   - For example, `PIC32MX` chips have a default value of `10bit`, `STM32` have a default value of `12bit` etc.
   - Relevant files:
      -  Driver layer:
         -  **[memake.txt](./drv/lib/memake.txt)**
         -  **[drv_analog_in.h](./drv/lib/include/drv_analog_in.h)**
      -  HAL layer:
         -  **[memake.txt](./hal/lib/memake.txt)**
         -  **[hal_adc.h](./hal/lib/include/hal_adc.h)**
      -  Targets layer:
         -  **[PIC memake.txt](./targets/pic_8bit/mikroe/pic18/memake.txt)**
         -  **[PIC hal_ll_adc.h](./targets/pic_8bit/mikroe/pic18/include/adc/hal_ll_adc.h)**
         -  **[PIC32 memake.txt](./targets/pic_32bit/mikroe/pic32/memake.txt)**
         -  **[PIC32 hal_ll_adc.h](./targets/pic_32bit/mikroe/pic32/include/adc/hal_ll_adc.h)**
         -  **[STM32 memake.txt](./targets/arm/mikroe/stm32/memake.txt)**
         -  **[STM32 hal_ll_adc.h](./targets/arm/mikroe/stm32/include/adc/hal_ll_adc.h)**

#### Git relevant updates

1. **[CODE_OF_CONDUCT.md](./CODE_OF_CONDUCT.md)** added
2. **[CONTRIBUTING.md](./CONTRIBUTING.md)** added
3. **[AUTHORS.md](./AUTHORS.md)** updated( added contributors )
4. **Templates** added
   - **[Pull request](./.github/pull_request_template.md)**
   - **[Bug report](./.github/ISSUE_TEMPLATE/bug_report.md)**
   - **[Feature request](./.github/ISSUE_TEMPLATE/feature_request.md)**

#### Collaborators

**We would like to thank the following people for contributing:**

+ **[@sofijaf](https://github.com/sofijaf)**
   - **[CORE library](./targets/pic_32bit/mikroe/core/src/hal_ll_core.c)** for PIC32 chips
   - **[UART library](./targets/pic_32bit/mikroe/pic32/src/uart/implementation_1/hal_ll_uart.c)** for PIC32MX and PIC32MZ chips
      - Implemented using interrupts
+ **[@sanjamandic](https://github.com/sanjamandic)**
   - **GPIO library** initial version for PIC32 chips
      - **[implementation](./targets/pic_32bit/mikroe/pic32/src/gpio/implementation_1/hal_ll_gpio.c)**
      - **[subimplementation](./targets/pic_32bit/mikroe/pic32/src/gpio/implementation_1/subimplementation_1/hal_ll_gpio_port.c)**
   - **ADC library** initial version for PIC32MX chips
      - **[implemetation_1](./targets/pic_32bit/mikroe/pic32/src/adc/implementation_1/hal_ll_adc.c)**
+ **[@mkovacevic95](https://github.com/mkovacevic95)**
   - Board def for **[EasyPIC Fusion v7](./bsp/board/include/boards/easypic_fusion_v7/board.h)**
   - MCU Card defs:
      - **[EasyPIC Fusion v7 ETH MCU Card with PIC32MX460F512L](./bsp/board/include/mcu_cards/easypic_fusion_v7_mcucard_with_pic32mx460f512l/mcu_card.h)**
      - **[EasyPIC Fusion v7 ETH MCU Card with PIC32MX795F512L](./bsp/board/include/mcu_cards/easypic_fusion_v7_eth_mcucard_with_pic32mx795f512l/mcu_card.h)**
      - **[EasyPIC Fusion v7 ETH MCU Card with PIC32MMZ2048EFH144](./bsp/board/include/mcu_cards/easypic_fusion_v7_eth_mcucard_with_pic32mz2048efh144/mcu_card.h)**
   - **[I2C library](./targets/pic_32bit/mikroe/pic32/src/i2c/implementation_1/hal_ll_i2c_master.c)** for PIC32MX and PIC32MZ chips
+ **[@NikolaDucak](https://github.com/NikolaDucak)**
   - **GPIO library** improvements for PIC32 chips
      - **[implementation](./targets/pic_32bit/mikroe/pic32/src/gpio/implementation_1/hal_ll_gpio.c)**
      - **[subimplementation](./targets/pic_32bit/mikroe/pic32/src/gpio/implementation_1/subimplementation_1/hal_ll_gpio_port.c)**
   - **ADC library** for PIC32MX and PIC32MZ chips
      - **[implemetation_1](./targets/pic_32bit/mikroe/pic32/src/adc/implementation_1/hal_ll_adc.c)** -- PIC32MX
      - **[implemetation_2](./targets/pic_32bit/mikroe/pic32/src/adc/implementation_2/hal_ll_adc.c)** -- PIC32MZ

**[BACK TO TOP OF 2.1.0](#v210)**

---
**[BACK TO TOP](#changelog)**

---

## `v2.0.3`

- released: 2021-01-28

### `2.0.3` Changes

- Added support for **new hardware**
- Updated relevant **manifest files**
- Updated relevant **development kit package**
- Updated **SPI**, **I2C** and **PPS** libraries

**Curiosity HPC** is now supported in mikroSDK 2.0.
**Clicker 2 for STM32/PIC18FJ/PIC18FK** is now supported in mikroSDK 2.0.

Added support for **PIC18F47Q10** chip.

**Added** adequate board definition files for **Curiosity HPC board**.
**Added** adequate board definition files for **Clicker 2 for STM32**.
**Added** adequate board definition files for **Clicker 2 for PIC18FJ**.
**Added** adequate board definition files for **Clicker 2 for PIC18FK**.

**Config files added for adequate `NEW` boards.**

Updated **mikroSDK development kit** to follow added hardware.

- **Curiosity HPC** - [official page](https://www.microchip.com/Developmenttools/ProductDetails/DM164136)
- **Clicker 2 for STM32** - [official page](https://www.mikroe.com/clicker-2-stm32f4)
- **Clicker 2 for PIC18FJ** - [official page](https://www.mikroe.com/clicker-2-pic18fj)
- **Clicker 2 for PIC18FK** - [official page](https://www.mikroe.com/clicker-2-pic18fk)

### `2.0.3` Fixes

- `UNI Clicker` renamed to follow naming convention
- `low level PPS implementation` ( PIC chips )
  - Applies to all PIC chips
  - Updated map sizes to 2 bytes
  - Some chips have more than 255 PPS pin functionalities, hence the map needs to be bigger

**NOTE**: PPS wasn't being set correctly for PIC18xxxK40 chips. Applied PPS fix covers this issue.

### `2.0.3` Improvements

- `low level SPI implementation` ( PIC chips )
  - **Setting SCK pin as both digital input/output is required**
  - [Documentation](https://ww1.microchip.com/downloads/en/DeviceDoc/PIC18F27-47Q10-Data-Sheet-40002043E.pdf) page 444 for more information
  - In Master mode the clock signal output to the SCK pin is also the clock signal input to the
  peripheral. The pin selected for output with the RxyPPS register must also be selected as the peripheral input with the SSPxCLKPPS register. The pin that is selected using the SSPxCLKPPS register should also be made a digital I/O. This is done by clearing the corresponding ANSEL bit.

- `low level I2C implementation` ( PIC chips )
  - **Bidirectional pins**
  - [Documentation](https://ww1.microchip.com/downloads/en/DeviceDoc/PIC18F27-47Q10-Data-Sheet-40002043E.pdf) page 289 for more information
    - PPS selections for peripherals with bidirectional signals on a single pin must be made so that the PPS input and PPS output select the same pin

**[BACK TO TOP OF 2.0.3](#v203)**

---
**[BACK TO TOP](#changelog)**

---

## `v2.0.2` 

- released: 2020-12-30

### `2.0.2` Changes

- Added support for **new hardware**
- Updated relevant **manifest files**
- Updated relevant **development kit package**

**Clicker 4 for STM32** is now supported in mikroSDK 2.0.

**Added** adequate board definition files for **Clicker 4 for STM32**.

Updated **mikroSDK development kit** to follow added hardware.

- **Clicker 4 for STM32** - [official page](https://www.mikroe.com/clicker-4-for-stm32)

### `2.0.2` Fixes

- `mcu_definitions` ( PIC chips )
  - **Setting pins as digital/analog**
  - [Documentation](https://ww1.microchip.com/downloads/en/DeviceDoc/30000575C.pdf) page 431 is at fault
  - Changed setting ANCONx register bits appropriately
    - RA4 pin ( ANCON1 bit 4, not ANCON1 bit 6 )
    - RA5 pin ( ANCON1 bit 5, not ANCON1 bit 4 )
    - RF2 pin ( ANCON1 bit 6, not ANCON1 bit 7 )
    - RF5 pin ( ANCON2 bit 1, not ANCON2 bit 2 )
    - RF6 pin ( ANCON2 bit 2, not ANCON2 bit 3 )
    - RG4 pin ( ANCON2 bit 7, not ANCON3 bit 0 )

Fix applied to following chips:

- PIC18F97J94
- PIC18F87J94
- PIC18F67J94
- PIC18F96J94
- PIC18F86J94
- PIC18F66J94
- PIC18F95J94
- PIC18F85J94
- PIC18F65J94

**[BACK TO TOP OF 2.0.2](#v202)**

---
**[BACK TO TOP](#changelog)**

---

## `v2.0.1` 

- released: 2020-12-11

### `2.0.1` Changes

- Added support for **new hardware**
- Updated relevant **manifest files**
- Updated relevant **development kit package**

**MCU CARD 11 FOR PIC** is now supported in **mikroSDK 2.0**.

**Added** following **PIC chips**:

- `PIC18F57K42` - [official page](https://www.mikroe.com/mcu-card-11-for-pic-pic18f57k42)
- `PIC18F57Q43` - [official page](https://www.mikroe.com/mcu-card-11-for-pic-pic18f57q43)

**Added** adequate board definition files for **MCU CARD 11 FOR PIC**.

Updated **mikroSDK development kit** to follow added hardware.

- `PIC18F57K42` - [official page](https://www.mikroe.com/mcu-card-11-for-pic-pic18f57k42)
- `PIC18F57Q43` - [official page](https://www.mikroe.com/mcu-card-11-for-pic-pic18f57q43)

### `2.0.1` Fixes

- HAL GPIO low level ( PIC chips )
  - **HAL GPIO low level PIC** implementation now doesn't change previous state of **LATCH** registers.

**[BACK TO TOP OF 2.0.1](#v201)**

---
**[BACK TO TOP](#changelog)**

---

## `v2.0.0` 

- released: 2020-10-02

**`INITIAL RELEASE.`**

---

**[BACK TO TOP](#changelog)**

---
