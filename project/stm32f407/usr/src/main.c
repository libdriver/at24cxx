/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      main.c
 * @brief     main source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2021-02-17
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/02/17  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_at24cxx_read_test.h"
#include "driver_at24cxx_basic.h"
#include "shell.h"
#include "clock.h"
#include "delay.h"
#include "uart.h"
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];        /**< uart buffer */
uint16_t g_len;            /**< uart buffer length */

/**
 * @brief     at24cxx full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 *             - 1 run failed
 *             - 5 param is invalid
 * @note      none
 */
uint8_t at24cxx(uint8_t argc, char **argv)
{
    if (argc == 1)
    {
        goto help;
    }
    if (argc == 2)
    {
        if (strcmp("-i", argv[1]) == 0)
        {
            at24cxx_info_t info;
            
            /* print at24cxx info */
            at24cxx_info(&info);
            at24cxx_interface_debug_print("at24cxx: chip is %s.\n", info.chip_name);
            at24cxx_interface_debug_print("at24cxx: manufacturer is %s.\n", info.manufacturer_name);
            at24cxx_interface_debug_print("at24cxx: interface is %s.\n", info.interface);
            at24cxx_interface_debug_print("at24cxx: driver version is %d.%d.\n", info.driver_version/1000, (info.driver_version%1000)/100);
            at24cxx_interface_debug_print("at24cxx: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
            at24cxx_interface_debug_print("at24cxx: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
            at24cxx_interface_debug_print("at24cxx: max current is %0.2fmA.\n", info.max_current_ma);
            at24cxx_interface_debug_print("at24cxx: max temperature is %0.1fC.\n", info.temperature_max);
            at24cxx_interface_debug_print("at24cxx: min temperature is %0.1fC.\n", info.temperature_min);
            
            return 0;
        }
        else if (strcmp("-p", argv[1]) == 0)
        {
            /* print pin connection */
            at24cxx_interface_debug_print("at24cxx: SCL connected to GPIOB PIN8.\n");
            at24cxx_interface_debug_print("at24cxx: SDA connected to GPIOB PIN9.\n");
            
            return 0;
        }
        else if (strcmp("-h", argv[1]) == 0)
        {
            /* show at24cxx help */
            
            help:
            
            at24cxx_interface_debug_print("at24cxx -i\n\tshow at24cxx chip and driver information.\n");
            at24cxx_interface_debug_print("at24cxx -h\n\tshow at24cxx help.\n");
            at24cxx_interface_debug_print("at24cxx -p\n\tshow at24cxx pin connections of the current board.\n");
            at24cxx_interface_debug_print("at24cxx -t read -type (1 | 2 | 4 | 8 | 16 | 32 | 64 | 128 | 256) -a (0 | 1| 2 | 3 | 4 | 5 | 6 | 7)\n\t"
                                          "run at24cxx read test.\n");
            at24cxx_interface_debug_print("at24cxx -c read -type (1 | 2 | 4 | 8 | 16 | 32 | 64 | 128 | 256) -a (0 | 1| 2 | 3 | 4 | 5 | 6 | 7) <registeraddr>\n\t"
                                          "run at24cxx read function.\n");
            at24cxx_interface_debug_print("at24cxx -c write -type (1 | 2 | 4 | 8 | 16 | 32 | 64 | 128 | 256) -a (0 | 1| 2 | 3 | 4 | 5 | 6 | 7) <registeraddr> <data>\n\t"
                                          "run at24cxx write function.data is hexadecimal.\n");
            
            return 0;
        }
        else
        {
            return 5;
        }
    }
    else if (argc == 7)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
             /* read test */
            if (strcmp("read", argv[2]) == 0)
            {
                at24cxx_t type;
                at24cxx_address_t address;
                
                if (strcmp("type", argv[3]) == 0)
                {
                    return 5;
                }
                if (strcmp("1", argv[4]) == 0)
                {
                    type = AT24C01;
                }
                else if (strcmp("2", argv[4]) == 0)
                {
                    type = AT24C02;
                }
                else if (strcmp("4", argv[4]) == 0)
                {
                    type = AT24C04;
                }
                else if (strcmp("8", argv[4]) == 0)
                {
                    type = AT24C08;
                }
                else if (strcmp("16", argv[4]) == 0)
                {
                    type = AT24C16;
                }
                else if (strcmp("32", argv[4]) == 0)
                {
                    type = AT24C32;
                }
                else if (strcmp("64", argv[4]) == 0)
                {
                    type = AT24C64;
                }
                else if (strcmp("128", argv[4]) == 0)
                {
                    type = AT24C128;
                }
                else if (strcmp("256", argv[4]) == 0)
                {
                    type = AT24C256;
                }
                else
                {
                    at24cxx_interface_debug_print("at24cxx: type is invalid.\n");
                    
                    return 5;
                }
                if (strcmp("a", argv[5]) == 0)
                {
                    return 5;
                }
                if ((argv[6][0]<'0') || argv[6][0]>'7')
                {
                    at24cxx_interface_debug_print("at24cxx: iic address is invalid.\n");
                    
                    return 5;
                }
                address = (at24cxx_address_t)atoi(argv[6]);
                
                /* run read test */
                if (at24cxx_read_test(type, address) != 0)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 8)
    {
        /* run function */
        if (strcmp("-c", argv[1]) == 0)
        {
            /* read function */
            if (strcmp("read", argv[2]) == 0)
            {
                uint8_t res;
                uint8_t data;
                uint16_t reg_address;
                at24cxx_t type;
                at24cxx_address_t address;
                
                if (strcmp("type", argv[3]) == 0)
                {
                    return 5;
                }
                if (strcmp("1", argv[4]) == 0)
                {
                    type = AT24C01;
                }
                else if (strcmp("2", argv[4]) == 0)
                {
                    type = AT24C02;
                }
                else if (strcmp("4", argv[4]) == 0)
                {
                    type = AT24C04;
                }
                else if (strcmp("8", argv[4]) == 0)
                {
                    type = AT24C08;
                }
                else if (strcmp("16", argv[4]) == 0)
                {
                    type = AT24C16;
                }
                else if (strcmp("32", argv[4]) == 0)
                {
                    type = AT24C32;
                }
                else if (strcmp("64", argv[4]) == 0)
                {
                    type = AT24C64;
                }
                else if (strcmp("128", argv[4]) == 0)
                {
                    type = AT24C128;
                }
                else if (strcmp("256", argv[4]) == 0)
                {
                    type = AT24C256;
                }
                else
                {
                    at24cxx_interface_debug_print("at24cxx: type is invalid.\n");
                    
                    return 5;
                }
                if (strcmp("a", argv[5]) == 0)
                {
                    return 5;
                }
                if ((argv[6][0]<'0') || argv[6][0]>'7')
                {
                    at24cxx_interface_debug_print("at24cxx: iic address is invalid.\n");
                    
                    return 5;
                }
                address = (at24cxx_address_t)atoi(argv[6]);
                if (strlen(argv[7]) < 4)
                {
                    at24cxx_interface_debug_print("at24cxx: read address length must be 4.\n");
                    
                    return 5;
                }
                reg_address = 0;
                if ((argv[7][0] <= '9') && (argv[7][0] >= '0'))
                {
                    reg_address = (argv[7][0] - '0') * 16 * 16 *16;
                }
                else
                {
                    reg_address = (argv[7][0] - 'A' + 10) * 16 * 16 *16;
                }
                if ((argv[7][1] <= '9') && (argv[7][1] >= '0'))
                {
                    reg_address += (argv[7][1] - '0') * 16 *16;
                }
                else
                {
                    reg_address += (argv[7][1] - 'A' + 10) * 16 * 16;
                }
                if ((argv[7][2] <= '9') && (argv[7][2] >= '0'))
                {
                    reg_address += (argv[7][2] - '0') * 16;
                }
                else
                {
                    reg_address += (argv[7][2] - 'A' + 10) * 16;
                }
                if ((argv[7][3] <= '9') && (argv[7][3] >= '0'))
                {
                    reg_address += (argv[7][3] - '0');
                }
                else
                {
                    reg_address += (argv[7][3] - 'A' + 10);
                }
                res = at24cxx_basic_init(type, address);
                if (res != 0)
                {
                    return 1;
                }
                res = at24cxx_basic_read(reg_address, (uint8_t *)&data, 1);
                if (res != 0)
                {
                    (void)at24cxx_basic_deinit();
                    
                    return 1;
                }
                else
                {
                    at24cxx_interface_debug_print("at24cxx: read 0x%04x is 0x%02X.\n", reg_address, data);
                }
                (void)at24cxx_basic_deinit();
                
                return 0;
            }
            
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 9)
    {
        /* run function */
        if (strcmp("-c", argv[1]) == 0)
        {
            /* write function */
            if (strcmp("write", argv[2]) == 0)
            {
                uint8_t res;
                uint8_t data;
                uint16_t reg_address;
                at24cxx_t type;
                at24cxx_address_t address;
                
                if (strcmp("type", argv[3]) == 0)
                {
                    return 5;
                }
                if (strcmp("1", argv[4]) == 0)
                {
                    type = AT24C01;
                }
                else if (strcmp("2", argv[4]) == 0)
                {
                    type = AT24C02;
                }
                else if (strcmp("4", argv[4]) == 0)
                {
                    type = AT24C04;
                }
                else if (strcmp("8", argv[4]) == 0)
                {
                    type = AT24C08;
                }
                else if (strcmp("16", argv[4]) == 0)
                {
                    type = AT24C16;
                }
                else if (strcmp("32", argv[4]) == 0)
                {
                    type = AT24C32;
                }
                else if (strcmp("64", argv[4]) == 0)
                {
                    type = AT24C64;
                }
                else if (strcmp("128", argv[4]) == 0)
                {
                    type = AT24C128;
                }
                else if (strcmp("256", argv[4]) == 0)
                {
                    type = AT24C256;
                }
                else
                {
                    at24cxx_interface_debug_print("at24cxx: type is invalid.\n");
                    
                    return 5;
                }
                if (strcmp("a", argv[5]) == 0)
                {
                    return 5;
                }
                if ((argv[6][0]<'0') || argv[6][0]>'7')
                {
                    at24cxx_interface_debug_print("at24cxx: iic address is invalid.\n");
                    
                    return 5;
                }
                address = (at24cxx_address_t)atoi(argv[6]);
                if (strlen(argv[7]) < 4)
                {
                    at24cxx_interface_debug_print("at24cxx: write address length must be 4.\n");
                    
                    return 5;
                }
                reg_address = 0;
                if ((argv[7][0] <= '9') && (argv[7][0] >= '0'))
                {
                    reg_address = (argv[7][0] - '0') * 16 * 16 *16;
                }
                else
                {
                    reg_address = (argv[7][0] - 'A' + 10) * 16 * 16 *16;
                }
                if ((argv[7][1] <= '9') && (argv[7][1] >= '0'))
                {
                    reg_address += (argv[7][1] - '0') * 16 *16;
                }
                else
                {
                    reg_address += (argv[7][1] - 'A' + 10) * 16 * 16;
                }
                if ((argv[7][2] <= '9') && (argv[7][2] >= '0'))
                {
                    reg_address += (argv[7][2] - '0') * 16;
                }
                else
                {
                    reg_address += (argv[7][2] - 'A' + 10) * 16;
                }
                if ((argv[7][3] <= '9') && (argv[7][3] >= '0'))
                {
                    reg_address += (argv[7][3] - '0');
                }
                else
                {
                    reg_address += (argv[7][3] - 'A' + 10);
                }
                data = 0;
                if ((argv[8][0] <= '9') && (argv[8][0] >= '0'))
                {
                    data += (argv[8][0] - '0') * 16;
                }
                else
                {
                    data += (argv[8][0] - 'A' + 10) * 16;
                }
                if ((argv[8][1] <= '9') && (argv[8][1] >= '0'))
                {
                    data += (argv[8][1] - '0');
                }
                else
                {
                    data += (argv[8][1] - 'A' + 10);
                }
                res = at24cxx_basic_init(type, address);
                if (res != 0)
                {
                    return 1;
                }
                res = at24cxx_basic_write(reg_address, (uint8_t *)&data, 1);
                if (res != 0)
                {
                    (void)at24cxx_basic_deinit();
                    
                    return 1;
                }
                else
                {
                    at24cxx_interface_debug_print("at24cxx: write 0x%04x is 0x%02X.\n", reg_address, data);
                }
                (void)at24cxx_basic_deinit();
                
                return 0;
            }
            
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    
    /* param is invalid */
    else
    {
        return 5;
    }
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    uint8_t res;
    
    /* stm32f407 clock init and hal init */
    clock_init();
    
    /* delay init */
    delay_init();
    
    /* uart1 init */
    uart1_init(115200);
    
    /* shell init && register at24cxx fuction */
    shell_init();
    shell_register("at24cxx", at24cxx);
    uart1_print("at24cxx: welcome to libdriver at24cxx.\n");
    
    while (1)
    {
        /* read uart */
        g_len = uart1_read(g_buf, 256);
        if (g_len)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart1_print("at24cxx: run failed.\n");
            }
            else if (res == 2)
            {
                uart1_print("at24cxx: unknow command.\n");
            }
            else if (res == 3)
            {
                uart1_print("at24cxx: length is too long.\n");
            }
            else if (res == 4)
            {
                uart1_print("at24cxx: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart1_print("at24cxx: param is invalid.\n");
            }
            else
            {
                uart1_print("at24cxx: unknow status code.\n");
            }
            uart1_flush();
        }
        delay_ms(100);
    }
}
