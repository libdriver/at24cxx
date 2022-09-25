### 1. Chip

#### 1.1 Chip Info

chip name : Raspberry Pi 4B.

iic pin: SCL/SDA GPIO3/GPIO2.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(at24cxx REQUIRED)
```

### 3. AT24CXX

#### 3.1 Command Instruction

​          at24cxx is a basic command which can test all at24cxx driver function:

​           -i          show at24cxx chip and driver information.

​           -h         show at24cxx help.

​           -p         show at24cxx pin connections of the current board.

​           -t  read -type (1 | 2 | 4 | 8 | 16 | 32 | 64 | 128 | 256) -a (0 | 1| 2 | 3 | 4 | 5 | 6 | 7)         run at24cxx read test.

​           -c (read -type (1 | 2 | 4 | 8 | 16 | 32 | 64 | 128 | 256) -a (0 | 1| 2 | 3 | 4 | 5 | 6 | 7)  <registeraddr>| write  -type (1 | 2 | 4 | 8 | 16 | 32 | 64 | 128 | 256) -a (0 | 1| 2 | 3 | 4 | 5 | 6 | 7)  <registeraddr> <data>)

​           -c read -type (1 | 2 | 4 | 8 | 16 | 32 | 64 | 128 | 256) -a (0 | 1| 2 | 3 | 4 | 5 | 6 | 7)  <registeraddr>        run at24cxx read function.

​           -c write -type (1 | 2 | 4 | 8 | 16 | 32 | 64 | 128 | 256) -a (0 | 1| 2 | 3 | 4 | 5 | 6 | 7)  <registeraddr> <data>        run at24cxx write function.data is hexadecimal.

#### 3.2 Command Example

```shell
./at24cxx -i

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
./at24cxx -p

at24cxx: SCL connected to GPIO3(BCM).
at24cxx: SDA connected to GPIO2(BCM).
```

```shell
./at24cxx -t read -type 1 -a 0

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
./at24cxx -c read -type 1 -a 0 0001

at24cxx: read 0x0001 is 0xB0.
```

```shell
./at24cxx -c write -type 1 -a 0 0001 11 

at24cxx: write 0x0001 is 0x11.
```

```shell
./at24cxx -h

at24cxx -i
	show at24cxx chip and driver information.
at24cxx -h
	show at24cxx help.
at24cxx -p
	show at24cxx pin connections of the current board.
at24cxx -t read -type (1 | 2 | 4 | 8 | 16 | 32 | 64 | 128 | 256) -a (0 | 1| 2 | 3 | 4 | 5 | 6 | 7)
	run at24cxx read test.
at24cxx -c read -type (1 | 2 | 4 | 8 | 16 | 32 | 64 | 128 | 256) -a (0 | 1| 2 | 3 | 4 | 5 | 6 | 7) <registeraddr>
	run at24cxx read function.
at24cxx -c write -type (1 | 2 | 4 | 8 | 16 | 32 | 64 | 128 | 256) -a (0 | 1| 2 | 3 | 4 | 5 | 6 | 7) <registeraddr> <data>
	run at24cxx write function.data is hexadecimal.
```

