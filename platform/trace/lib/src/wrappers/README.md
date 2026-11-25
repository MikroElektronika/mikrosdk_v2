# Firmware trace wrappers

The drivers know nothing of the firmware trace. When an application links `MikroSDK.Trace`, the
linker option `--wrap=<function>` sends every call of `<function>` to `__wrap_<function>`, which
lives in this folder. The original driver function stays reachable as `__real_<function>`.

Each wrapper records the call through the hooks in `../trace_hooks.h` (implemented in
`../trace.c`), applies fault injection where it makes sense, and calls the real function.

Projects without `MikroSDK.Trace` (and every build outside NECTO Studio) never see these files.

## Adding a wrapper

The example wraps a hypothetical `pwm_set_duty()` from `MikroSDK.Driver.PWM`.

### 1. Create `trace_<driver>.c`

Copy the license header from another wrapper, then:

```c
/*!
 * @file  trace_pwm.c
 * @brief Firmware trace wrappers of the PWM driver.
 *
 * @details See trace_i2c.c.
 */

#include "drv_pwm.h"
#include "../trace_hooks.h"

err_t __real_pwm_set_duty( pwm_t *obj, float duty_ratio );

err_t __wrap_pwm_set_duty( pwm_t *obj, float duty_ratio )
{
    uint32_t start = trace_hook_now();
    err_t result = __real_pwm_set_duty( obj, duty_ratio );
    trace_hook_pwm( obj, duty_ratio, result, start );
    return result;
}
```

`trace_hook_pwm()` does not exist yet: a driver the trace does not record so far needs a new hook
(step 2).

Rules:

- **Same signature.** `__real_` and `__wrap_` must match the driver function exactly, including
  qualifiers such as `__generic_ptr`.
- **Always call `__real_`.** Calling `pwm_set_duty()` from a wrapper goes back to the wrapper
  and recurses forever.
- **Take the start time first.** Call `trace_hook_now()` before the real call, so that the record
  carries the start of the transfer.
- **Keep wrappers thin.** Recording, lanes and the buffer belong in `../trace.c`. A wrapper only
  gathers the arguments and the result.
- **Fault injection** follows the existing pattern: ask a `trace_hook_fault_*()` hook before the
  call (and skip the real call, as `trace_i2c.c` does) or after it (and change the data read, as
  `trace_spi.c` does).
- **Flattened functions.** A function that becomes a macro under `FLATTEN_ME_LEVEL_HIGH` does not
  exist in the driver library. Guard its wrapper with
  `#if (FLATTEN_ME_LEVEL < FLATTEN_ME_LEVEL_HIGH)` (see `trace_gpio_out.c`), and give the macro in
  the driver header a `MIKROSDK_TRACE` branch that calls the hook.

### 2. Add a hook, if no existing one fits

1. Declare it in `../trace_hooks.h` as `trace_hook_<name>()`.
2. Implement it in `../trace.c` under `HOOK DEFINITIONS`.

A new record or lane type changes the format the debugger reads. Add it to the record and lane
enums in `trace.c`, raise `TRACE_FORMAT_VERSION`, and update the trace decoder in NECTO Studio
(see the file comment of `trace.c` for the format document).

### 3. Register it in `platform/trace/lib/CMakeLists.txt`

Add a block next to the others, guarded by the driver's module name:

```cmake
if (msdk_pwm IN_LIST module_list_supported)
    list(APPEND trace_wrappers trace_pwm.c)
    list(APPEND trace_drivers MikroSDK.Driver.PWM)
    list(APPEND trace_wrapped pwm_set_duty)
endif()
```

- `trace_wrappers`: the file in this folder. It is compiled into the application and installed
  to `src/platform/trace/wrappers/`.
- `trace_drivers`: the driver library that `MikroSDK.Trace` links.
- `trace_wrapped`: every function the file wraps. Each gets a `--wrap` linker option; a function
  missing from this list is not traced, even if its wrapper exists.

### 4. Check it

- Only calls from other files are wrapped. A driver calling its own function inside the same `.c`
  file bypasses the wrapper.
- Build a NECTO Studio setup with `MikroSDK.Trace` and call the function from the application. The
  map file should list `__wrap_pwm_set_duty`, and the call should show on the trace timeline.
- Build the same application without `MikroSDK.Trace`: nothing from this folder may be linked.

The trace needs a linker with `--wrap`: GCC, Clang and XC32. mikroC is not supported.
