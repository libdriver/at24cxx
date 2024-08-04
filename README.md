[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver AT24CXX

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/at24cxx/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

AT24CXX is the EEPROM of IIC bus launched by Microchip. It supports 1.7v-5.5v power supply range, IIC standard mode (100kHz), fast mode (400kHz) and high speed mode (1MHz).

LibDriver AT24CXX is the full function driver of AT24CXX launched by LibDriver. AT24CXX provides EEPROM write and read functions. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver AT24CXX source files.

/interface includes LibDriver AT24CXX IIC platform independent template.

/test includes LibDriver AT24CXX driver test code and this code can test the chip necessary function simply.

/example includes LibDriver AT24CXX sample code.

/doc includes LibDriver AT24CXX offline document.

/datasheet includes AT24CXX datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface IIC platform independent template and finish your platform IIC driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

#### example basic

```C
#include "driver_at24cxx_basic.h"

uint8_t res;
uint8_t data;

res = at24cxx_basic_init(AT24C01, AT24CXX_ADDRESS_A000);
if (res != 0)
{
    return 1;
}

...

res = at24cxx_basic_read(0x00, (uint8_t *)&data, 1);
if (res != 0)
{
    (void)at24cxx_basic_deinit();

    return 1;
}
else
{
    at24cxx_interface_debug_print("at24cxx: 0x%02X.\n", data);
}

...

res = at24cxx_basic_write(0x00, (uint8_t *)&data, 1);
if (res != 0)
{
    (void)at24cxx_basic_deinit();

    return 1;
}
else
{
    at24cxx_interface_debug_print("at24cxx: 0x%02X.\n", data);
}

...

(void)at24cxx_basic_deinit();

return 0;
```

### Document

Online documents: [https://www.libdriver.com/docs/at24cxx/index.html](https://www.libdriver.com/docs/at24cxx/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



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

Please send an e-mail to lishifenging@outlook.com.