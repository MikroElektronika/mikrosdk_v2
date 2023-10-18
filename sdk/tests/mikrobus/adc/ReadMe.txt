This example is meant for testing all AN mikroBUS
pins on mikroBUS sockets.

The example initializes each pin separately on all mikroBUS
socket, reads raw analog input value and logs the data
via defined UART pins.

Take into consideration that a single pin can also be
tested.

NOTE1: If `board.h` has defined USB UART pins, UART log will
be mapped to them by default. Else, user is expected to define
them.

NOTE2: USB UART click might be required for a successful test.

LINK: https://www.mikroe.com/usb-uart-click
LINK: https://www.mikroe.com/usb-uart-2-click
LINK: https://www.mikroe.com/usb-uart-3-click
LINK: https://www.mikroe.com/usb-uart-4-click
