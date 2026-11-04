GC9107 GL test

Tests the GC9107 display middleware through the mikroSDK GL driver.
The test fills the screen with red, green, blue, white and black,
draws a square near each corner, rotates through all four orientations,
and finally turns the display power off and on.

Settings are for the IPS Display 3 Click (128x115 round display) in
mikroBUS 1. To use another mikroBUS slot, change MIKROBUS_1 in main.c.
The backlight (BCK) of this click is on the PWM pin of the mikroBUS socket.

The glass is round, so the squares are drawn away from the corners,
otherwise they would be cut off by the edge of the glass.
