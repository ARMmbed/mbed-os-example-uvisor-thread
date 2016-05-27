# Threaded Blinky with uVisor Example

This is a simple example to show how to write a uVisor-secured threaded
application. Three LEDs will blink from three separate secure processes. Each
process also updates some memory private to that process. The memory allocator
is also used in this example.

The example currently only works on K64F.
