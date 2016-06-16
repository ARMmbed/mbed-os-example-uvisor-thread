# Threaded Blinky with uVisor Example

This is a simple example to show how to write a uVisor-secured threaded
application. Three LEDs will blink from three separate secure processes. Each
process also updates some memory private to that process. The memory allocator
is also used in this example.

## Building
The example currently only works on K64F with the GCC_ARM tool chain.
### Release
For normal compilation, please enter:
```bash
mbed compile -m K64F_SECURE -t GCC_ARM -c
```
### Debug
When connecting a debugger, output can be seen on the debug console:
```bash
mbed compile -m K64F_SECURE -t GCC_ARM -c -o debug-info
```
