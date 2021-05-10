<div align=center>
<img src="/doc/image/logo.png"/>
</div>

## LibDriver ADS1115

[English](/README.md) | [ 简体中文](/README_CN.md)

### Table of Contents

  - [Description](#Description)
  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)


### Description

AT24CXX is the EEPROM of IIC bus launched by Microchip. It supports 1.7v-5.5v power supply range, IIC standard mode (100kHz), fast mode (400kHz) and high speed mode (1MHz).

LibDriver AT24CXX is the full function driver of AT24CXX launched by LibDriver. AT24CXX provides EEPROM write and read functions.

### Instruction

/src includes LibDriver AT24CXX source files.

/interface includes LibDriver AT24CXX IIC platform independent template。

/test includes LibDriver AT24CXX driver test code and this code can test the chip necessary function simply。

/example includes LibDriver AT24CXX sample code.

/doc includes LibDriver AT24CXX offline document.

/datasheet includes AT24CXX datasheet。

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

### Install

Reference /interface IIC platform independent template and finish your platform IIC driver.

Add /src, /interface and /example to your project.

### Usage

#### example basic

```C
uint8_t res;
uint8_t data;

res = at24cxx_basic_init(AT24C01, AT24CXX_ADDRESS_A000);
if (res)
{
    return 1;
}

...

res = at24cxx_basic_read(0x00, (uint8_t *)&data, 1);
if (res)
{
    at24cxx_basic_deinit();

    return 1;
}
else
{
    at24cxx_interface_debug_print("at24cxx: 0x%02X.\n", data);
}

...

res = at24cxx_basic_write(0x00, (uint8_t *)&data, 1);
if (res)
{
    at24cxx_basic_deinit();

    return 1;
}
else
{
    at24cxx_interface_debug_print("at24cxx: 0x%02X.\n", data);
}

...

at24cxx_basic_deinit();

return 0;
```

### Document

Online documents: https://www.libdriver.com/docs/at24cxx/index.html

Offline documents: /doc/html/index.html

### Contributing

Please sent an e-mail to lishifenging@outlook.com

### License

Copyright (C) LibDriver 2015-2021 All rights reserved 



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please sent an e-mail to lishifenging@outlook.com