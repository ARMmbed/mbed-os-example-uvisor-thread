# Threaded blinky with uVisor example

This is a simple example to show how to write a uVisor-secured threaded application. Three LEDs will blink from three separate secure processes. Each process also updates some memory private to that process. The memory allocator is also used in this example.

Supported devices:

| Target | Toolchain | Baud rate |
|--------|-----------|-----------|
| `K64F` | `GCC_ARM` | 9600      |

Latest release: [mbed-os-5.3.x](https://github.com/ARMmbed/mbed-os-example-uvisor/releases/latest). Tested with [mbed-cli v1.0.0](https://github.com/ARMmbed/mbed-cli/releases/tag/1.0.0).

## Quickstart

For a release build, please enter:

```bash
$ mbed compile -m K64F -t GCC_ARM -c
```

You will find the resulting binary in `BUILD/${TARGET}/${TOOLCHAIN}/mbed-os-example-uvisor-thread.bin`. You can drag and drop it onto your board USB drive.

Press the reset button. You will see 3 LEDs on your target blink one after the other as the 3 respective secure boxes are switched in and out.

If you want, you can also observe the serial port output:

```bash
$ screen /dev/tty.usbmodem1422 9600
```

You will see an output similar to the following one:

```
***** Threaded blinky uVisor example *****
Main loop count: 0
Main loop count: 1
Main loop count: 2
Main loop count: 3
Main loop count: 4
Main loop count: 5
Main loop count: 6
...
```

> **Note**: If your target does not have 3 different LEDs or LED colours, you will see the same LED blink multiple times. The example use the general mbed OS naming structure `LED1`, `LED2`, `LED3`.

### Debug

When a debugger is connected, you can observe debug output from uVisor. Please note that these messages are sent through semihosting, which halts the program execution if a debugger is not connected. For more information please read the [Debugging uVisor on mbed OS](https://github.com/ARMmbed/uvisor/blob/master/docs/api/DEBUGGING.md) guide. To build a debug version of this example, please enter:

```bash
$ mbed compile -m K64F -t GCC_ARM --profile mbed-os/tools/profiles/debug.json -c
```

## Known issues

- Use of exporters for multiple IDEs is not supported at the moment.

