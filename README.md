# mikroSDK 2.0

[![SDK Version](https://img.shields.io/badge/mikroSDK%20version-${MIKROSDK_CURRENT_VERSION}-gold)](https://github.com/MikroElektronika/mikrosdk_v2/tree/mikroSDK-${MIKROSDK_CURRENT_VERSION})

---
## About

**mikroSDK 2.0** is an embedded software development framework designed to simplify</br>
and accelerate application development on **Mikroe** hardware platform,</br>
specifically for [**Click Boards&trade;**](https://github.com/MikroElektronika/mikrosdk_click_v2) and other extension board drivers, on a wide range</br>
of microcontroller vendors and architectures. It includes peripheral libraries</br>
and drivers, middleware, board support, and application layer libraries like</br>
Graphic Library, Visual TFT, Logger, Console and many more to come (eg. HID, FAT32 etc.).</br>
It also comes with examples and user documentation. **mikroSDK 2.0** applications can</br>
be reused on any **mikroSDK 2.0** compatible platform.

**mikroSDK 2.0** platform can be extended by Components which are [**Click Boards&trade;**](https://github.com/MikroElektronika/mikrosdk_click_v2) and</br>
other extension board drivers.

Board support comes with definitions for pin connections between microcontroller,</br>
MCU card and board sockets (eg. [**mikroBUS&trade;**](https://www.mikroe.com/mikrobus)) and special function pinouts,</br>
so you can easily map your driver or application to the board.

The peripheral driver library simplifies and unifies usage of microcontrollers,</br>
so reading a microcontroller's user manual, in most cases, is not necessary.</br>
It also allows writing portable and re-usable applications.

## Design Goals

- Standard C.
  - Large code base can be easely reused with other platforms (Linux, Arduino).
- Fast development.
  - Simplify developing applications with portability, fast prototyping in mind,</br>
    minimal impact on performance.
- Ease of use.
  - Simplifies the usage of microcontrollers, providing an abstraction to the</br>
    hardware and high-value middleware.
- Layered and modular software architecture.

## Architecture diagram

*This is the basic architecture diagram.*

<p align="left">
  <img src=https://help.mikroe.com/sdk_overview.png height=500px alt="mikroSDK 2.0 diagram">
</p>

## Peripheral Libraries (HAL)

Provides common peripheral functionality, abstracting the hardware peripheral</br>
register access. The interface hides the register access details and various</br>
MCU peripheral instantiation differences so that the application can be</br>
abstracted from the low-level hardware details.

## Peripheral Drivers (DRV)

The Driver specification is a software API which describes peripheral driver</br>
interfaces for middle-ware stacks and user applications. It adds higher level</br>
functionality, implementing common protocols, handling multiple clients for</br>
peripheries and their re-initialization.

## Components

Wide range of reusable driver libraries for [**Click Boards&trade;**](https://github.com/MikroElektronika/mikrosdk_click_v2) and</br>
extension boards. The component should use peripheral drivers (DRV) to</br>
communicate with MCU peripherals and board support to port driver to/br>
specific pin mappings.

## Board support

Board support consists of pin mappings for sockets and other special function</br>
pins. It maps specific board pins to MCU target pins. It can also contain other</br>
useful information necessary for drivers to work properly on the board.

## API

High level libraries for commonly used services, so developers do not need to</br>
reinvent the wheel, shortening development cycles. It comes with new improved</br>
Graphic library, Visual TFT library for GUI applications, Logger,</br>
Console framework, Input library, and many more to come.

## Key Features

* Application framework for abstraction and code re-usability.
* Layered architecture.
* Simplified microcontroller common usage.
* Easy development of Click drivers.

## Release notes ( roadmap )

The [release notes](https://docs.mikroe.com/mikrosdk/user-manual/general/roadmap) detail the current release.</br>
You can also find information about previous versions.
Just follow the link provided.

## User manual

mikroSDK 2.0 user manual can be found [HERE](https://docs.mikroe.com/mikrosdk/user-manual/).

## Whitepaper

mikroSDK 2.0 whitepaper documentation can be found [HERE](https://download.mikroe.com/documents/mikrosdk/mikrosdk-v2.0-white-paper-avg-2020.pdf).

## Reference manual

mikroSDK 2.0 reference manual can be found [HERE](https://docs.mikroe.com/mikrosdk/ref-manual/index.html).

## License

The software is provided under [Mikroe Software License Agreement](https://www.mikroe.com/legal/software-license-agreement).</br>
Contributions to this project are accepted under the same license.</br>

Alternatively, this file may be used for</br>
non-commercial projects under the terms of the GNU Lesser</br>
General Public License version 3 as published by the Free Software</br>
Foundation. Click [HERE](https://www.gnu.org/licenses/lgpl-3.0.html) to see the license.

---

[![Bugs](https://img.shields.io/badge/Issues--bugs-0%20open-green)](https://github.com/MikroElektronika/mikrosdk_v2/issues?q=is%3Aissue+is%3Aopen+label%3Abug) [![Requests](https://img.shields.io/badge/Issues--requests-0%20open-green)](https://github.com/MikroElektronika/mikrosdk_v2/issues?q=is%3Aissue+is%3Aopen+label%3Auser-request)

---
