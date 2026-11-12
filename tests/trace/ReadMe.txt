Example is meant for testing the firmware trace library (MikroSDK.Trace) using mikroSDK 2.0

The test writes a GPIO pin and named values, and checks the records the trace keeps in its
RAM buffer: their order, the flush, the restart after a loss, the bursts of fast writes, and
a fault holding an input pin.

Define the pins in main.c before building:

* #define TEST_PIN_TRACE   - any free pin, its writes are the traced events
* #define TEST_PIN_INPUT   - another free pin, read as an input
* #define TEST_PIN_1 .. 7  - error pins, the pin of the first failed check goes high
* #define TEST_PIN_SUCCESS - goes high when all checks pass

Error pins:

* TEST_PIN_1 - pin init failed, or the trace recorded something before the first event
* TEST_PIN_2 - first event: META, lane definition and level record expected
* TEST_PIN_3 - named value: lane definition and value record expected
* TEST_PIN_4 - trace_flush() did not empty the buffer
* TEST_PIN_5 - first event after the flush: META and DROPPED (or only the event) expected
* TEST_PIN_6 - fast writes filled the buffer, or no BURST record after them
* TEST_PIN_7 - an input held by a fault did not read its level, or its record was not marked
               injected

Run the test without stopping between the checks: a debugger that reads the trace empties
the buffer whenever the program stops. Breakpoints on the error lines are fine.

The burst check (TEST_PIN_6) runs only with a time base: Cortex-M3 and newer, RISC-V and PIC32.
