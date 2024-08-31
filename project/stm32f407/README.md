### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

IIC Pin: SCL/SDA PB8/PB9.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. AT24CXX

#### 3.1 Command Instruction

1. Show at24cxx chip and driver information.

   ```shell
   at24cxx (-i | --information)
   ```

2. Show at24cxx help.

   ```shell
   at24cxx (-h | --help)
   ```

3. Show at24cxx pin connections of the current board.

   ```shell
   at24cxx (-p | --port)
   ```

4. Run at24cxx read test.

   ```shell
   at24cxx (-t read | --test=read) [--type=<AT24C01 | AT24C02 | AT24C04 | AT24C08 | AT24C16 | AT24C32 | AT24C64 | AT24C128 | AT24C256 | AT24C512 | AT24CM01 | AT24CM02>] [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]
   ```

5. Run at24cxx read function, reg is the register address and it is hexadecimal.

   ```shell
   at24cxx (-e read | --example=read) [--type=<AT24C01 | AT24C02 | AT24C04 | AT24C08 | AT24C16 | AT24C32 | AT24C64 | AT24C128 | AT24C256 | AT24C512 | AT24CM01 | AT24CM02>] [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--reg=<address>]
   ```

6. Run at24cxx write function, reg is the register address and data is the set value, both are hexadecimal.

   ```shell
   at24cxx (-e write | --example=write) [--type=<AT24C01 | AT24C02 | AT24C04 | AT24C08 | AT24C16 | AT24C32 | AT24C64 | AT24C128 | AT24C256 | AT24C512 | AT24CM01 | AT24CM02>] [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--reg=<address>] [--data=<value>]
   ```

#### 3.2 Command Example

```shell
at24cxx -i

at24cxx: chip is Microchip AT24CXX.
at24cxx: manufacturer is Microchip.
at24cxx: interface is IIC.
at24cxx: driver version is 2.0.
at24cxx: min supply voltage is 1.7V.
at24cxx: max supply voltage is 5.5V.
at24cxx: max current is 5.00mA.
at24cxx: max temperature is 85.0C.
at24cxx: min temperature is -40.0C.
```

```shell
at24cxx -p

at24cxx: SCL connected to GPIOB PIN8.
at24cxx: SDA connected to GPIOB PIN9.
```

```shell
at24cxx -t read --type=AT24C01 --addr=0

at24cxx: chip is Microchip AT24CXX.
at24cxx: manufacturer is Microchip.
at24cxx: interface is IIC.
at24cxx: driver version is 2.0.
at24cxx: min supply voltage is 1.7V.
at24cxx: max supply voltage is 5.5V.
at24cxx: max current is 5.00mA.
at24cxx: max temperature is 85.0C.
at24cxx: min temperature is -40.0C.
at24cxx: start read test.
at24cxx: 0x0000 read write test passed.
at24cxx: 0x0010 read write test passed.
at24cxx: 0x0020 read write test passed.
at24cxx: 0x0030 read write test passed.
at24cxx: 0x0040 read write test passed.
at24cxx: 0x0050 read write test passed.
at24cxx: 0x0060 read write test passed.
at24cxx: 0x0070 read write test passed.
at24cxx: finish read test.
```

```shell
at24cxx -e read --type=AT24C01 --addr=0 --reg=0001

at24cxx: read 0x0001 is 0x53.
```

```shell
at24cxx -e write --type=AT24C01 --addr=0 --reg=0001 --data=15

at24cxx: write 0x0001 is 0x15.
```

```shell
at24cxx -h

Usage:
  at24cxx (-i | --information)
  at24cxx (-h | --help)
  at24cxx (-p | --port)
  at24cxx (-t read | --test=read) [--type=<AT24C01 | AT24C02 | AT24C04 | AT24C08 | AT24C16 | AT24C32 | AT24C64 | AT24C128 | AT24C256 |
                                           AT24C512 | AT24CM01 | AT24CM02>]
          [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]
  at24cxx (-e read | --example=read) [--type=<AT24C01 | AT24C02 | AT24C04 | AT24C08 | AT24C16 | AT24C32 | AT24C64 | AT24C128 | AT24C256 |
                                              AT24C512 | AT24CM01 | AT24CM02>]
          [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--reg=<address>]
  at24cxx (-e write | --example=write) [--type=<AT24C01 | AT24C02 | AT24C04 | AT24C08 | AT24C16 | AT24C32 | AT24C64 | AT24C128 | AT24C256 |
                                                AT24C512 | AT24CM01 | AT24CM02>]
          [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--reg=<address>] [--data=<value>]

Options:
      --addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>    Set the connection of the addr pin and the addr number is A2A1A0.([default: 0])
      --data=<value>                            Set the sent data and it is hexadecimal.([default: random])
  -e <read>, --example=<read>                   Run the driver example.
  -h, --help                                    Show the help.
  -i, --information                             Show the chip information.
  -p, --port                                    Display the pin connections of the current board.
      --reg=<address>                           Set the register address and it is hexadecimal.([default: 0x0000])
  -t <read | write>, --test=<read | write>      Run the driver test.
      --type=<AT24C01 | AT24C02 | AT24C04 | AT24C08 | AT24C16 | AT24C32 | AT24C64 | AT24C128 | AT24C256 |
              AT24C512 | AT24CM01 | AT24CM02>
                                                Set the chip type.([default: AT24C01])
```

