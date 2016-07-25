# Threaded Blinky with uVisor Example

This is a simple example to show how to write a uVisor-secured threaded
application. Three LEDs will blink from three separate secure processes. Each
process also updates some memory private to that process. The memory allocator
is also used in this example.

## Building

The example currently only works on K64F with the GCC_ARM toolchain.

### Release

For a release build, please enter:

```bash
$ mbed compile -m K64F -t GCC_ARM
```

You will find the resulting binary in `.build/K64F/GCC_ARM/mbed-os-example-uvisor.bin`. You can drag and drop it onto your board USB drive.

### Debug

When a debugger is connected, you can observe debug output from uVisor. Please note that these messages are sent through semihosting, which halts the program execution if a debugger is not connected. For more information please read the [Debugging uVisor on mbed OS](https://github.com/ARMmbed/uvisor/blob/master/docs/api/DEBUGGING.md) guide. To build a debug version of the program:

```bash
$ mbed compile -m K64F -t GCC_ARM -o "debug-info"
```
