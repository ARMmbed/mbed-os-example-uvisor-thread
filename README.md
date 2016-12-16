# Threaded blinky with uVisor example

This is a simple example to show how to write a uVisor-secured threaded application. Three LEDs will blink from three separate secure processes. Each process also updates some memory private to that process. The memory allocator is also used in this example.

Supported devices:

| Target              | Toolchain | Baud rate    |
|---------------------|-----------|--------------|
| `ARM_MPS2_ARMv8MML` | `GCC_ARM` | See `stdout` |

Latest release: [uvisor-v8m-epr](https://github.com/ARMmbed/mbed-os-example-uvisor-thread/releases/tag/uvisor-v8m-epr). Tested with [mbed-cli v1.0.0](https://github.com/ARMmbed/mbed-cli/releases/tag/1.0.0).

## Caveats

* This is a ARMv8-M specific example, and only works on an ARMv8-M FastModel. For the officially supported example, please use the [master branch](https://github.com/ARMmbed/mbed-os-example-uvisor-thread).
* The ARMv8-M target requires GCC 5.4.1 20160919 or higher.
* The ARMv8-M target used via our FastModel binary cannot show LED output. Refer to `stdout` instead.

For a complete list of ARMv8-M-specific known issue, check out the [uvisor-tests-v8m README](https://github.com/ARMmbed/uvisor-tests-v8m/tree/dev/v8m#caveats).

## Quickstart

First, in order to use the ARMv8-M target you need to setup our Docker'ized FastModel. This allows you to use the FastModel as a self-contained binary on both Linux and macOS. First, clone the FastModel repository:

```bash
$ mkdir -p ~/code
$ cd ~/code
$ git clone git@github.com:ARMmbed/uvisor-fastmodel-testing
$ cd uvisor-fastmodel-testing
```

If you have git-lfs installed, the clone operation will have fetched the Docker image, otherwise you need to visit [this link](https://github.com/ARMmbed/uvisor-fastmodel-testing/blob/master/mbed-v8m.tar.xz) and download it manually:

[https://github.com/ARMmbed/uvisor-fastmodel-testing/blob/master/mbed-v8m.tar.xz](https://github.com/ARMmbed/uvisor-fastmodel-testing/blob/master/mbed-v8m.tar.xz)

Once the Docker image has been downloaded, load it via Docker:

```bash
$ docker load -i mbed-v8m.tar.xz
```

You can verify that it has been loaded correctly by running `docker images`:

```bash
REPOSITORY   TAG      IMAGE ID       CREATED      SIZE
mbed-v8m     latest   402206ca9a0b   2 days ago   108.7 MB
```

Run our provided script to create links to the Docker'ized fastmodel binaries and then add them to your path:

```bash
$ docker/tools/link_binaries.sh
$ export PATH=$PATH:$HOME/code/uvisor-fastmodel-testing/docker/bin
```

You can verify that the path is set correctly by running:

```bash
$ which simulate
~/uvisor-fastmodel-testing/docker/bin/simulate
```

Finally, you can clone this repository, select the `dev/v8m` branch, and build the example app:

```bash
$ cd ~/code
$ git clone git@github.com:ARMmbed/mbed-os-example-uvisor-thread
$ cd mbed-os-example-uvisor-thread
$ git checkout dev/v8m
$ mbed deploy

# For a release build:
$ mbed compile -m ARM_MPS2_ARMv8MML -t GCC_ARM -c

# For a debug build:
$ mbed compile -m ARM_MPS2_ARMv8MML -t GCC_ARM -c --profile mbed-os/tools/profiles/debug.json
```

You will find the resulting ELF file in `BUILD/ARM_MPS2_ARMv8MML/GCC_ARM/mbed-os-example-uvisor-thread.elf`.

To execute the example, simply run:

```bash
$ simulate FVP_MPS2_Cortex-M33 BUILD/ARM_MPS2_ARMv8MML/GCC_ARM/mbed-os-example-uvisor-thread.elf
```

You can observe the serial output in `stdout` from the `simulate` command. You will see an output similar to the following one:

```
***** threaded blinky uvisor-rtos example *****
Main loop count: 0
Main loop count: 1
Main loop count: 2
Main loop count: 3
Main loop count: 4
Main loop count: 5
Main loop count: 6
...
```
