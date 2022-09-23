# Baremetal webserver on NUCLEO-F746ZG

This firmware uses experimental TCP/IP stack of the Mongoose Network Library,
which implements the following:

- A complete [HTTP device dashboard](../../device-dashboard) with:
  - User authentication
  - Real-time device data graph
  - Coninfiguration display and update
  - MQTT communication with a remote MQTT server
- Implements SNTP time synchronisation
- No dependencies: no HAL, no CMSIS, no RTOS
- Hand-written [mcu.h](mcu.h) header based on a [datasheet](https://www.st.com/resource/en/reference_manual/rm0385-stm32f75xxx-and-stm32f74xxx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)
- Interrupt-driven [Ethernet driver](../../../mip/driver_stm32.c)
- Blue LED blinky, based on SysTick interrupt
- User button handler, turns off/on green LED, based on EXTI, interrupt-driven 
- HardFault handler that blinks red LED
- Debug log on UART3 (st-link)

## Requirements

- GNU make
- [ARM GCC](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm) toolchain for build
- [st-link](https://github.com/stlink-org/stlink) for flashing

## Usage

Plugin your Nucleo board into USB, and attach an Ethernet cable.
To build and flash:

```sh
$ make clean flash
```

To see debug log, use any serial monitor program like `picocom` at 115200 bps and configure it to insert carriage returns after line feeds:

```sh
$ picocom /dev/ttyACM0 -i -b 115200 --imap=lfcrlf
```

## Benchmark

A quick comparison is made with several other implementations.
Note: `IP` in the table below is the IP address printed on the console after
boot. The benchmark command is the same: `siege -c 5 -t 5s http://IP`

|                     | Zephyr   | LWIP sockets | LWIP raw | MIP  |
| ------------------- | -------- | ------------ | -------- | ---- |
| Requests per second | 3        | 16           | 286      | 1080 |
| Firmware size       | 117k (*) | 160k         | 114k     | 28k  |

- Zephyr: uses Zehypr's RTOS and TCP stack, with Mongoose library on top,
  [source code](https://github.com/cesanta/mongoose/tree/master/examples/zephyr/http-server).
  (*) By default, Zephyr example is TLS-enabled. To compare sizes, a TLS-disabled
  build was done by disabling TLS in `prj.conf` and `CMakeLists.txt`
- LWIP sockets: uses FreeRTOS and LWIP with sockets support, with Mongoose
  library on top, [source code](https://github.com/mongoose-examples/stm32-nucleo-f746z).
  built with `#define MG` in `Core/main.c`
- LWIP raw: uses FreeRTOS and LWIP without sockets, LWIP's httpd server,
  [source code](https://github.com/mongoose-examples/stm32-nucleo-f746z).
  built with `#define MG` line commented out in `Core/main.c`
- MIP: this repository

