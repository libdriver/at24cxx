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
#include "getopt.h"
#include <math.h>
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];        /**< uart buffer */
volatile uint16_t g_len;   /**< uart buffer length */

/**
 * @brief     at24cxx full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t at24cxx(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"addr", required_argument, NULL, 1},
        {"data", required_argument, NULL, 2},
        {"reg", required_argument, NULL, 3},
        {"type", required_argument, NULL, 4},
        {NULL, 0, NULL, 0},
    };
    char type[32] = "unknown";
    uint8_t data = rand() % 0xFF;
    uint32_t reg = 0x0000;
    at24cxx_t chip_type = AT24C01;
    at24cxx_address_t addr = AT24CXX_ADDRESS_A000;

    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }

    /* init 0 */
    optind = 0;

    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);

        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 32);
                snprintf(type, 32, "h");

                break;
            }

            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 32);
                snprintf(type, 32, "i");

                break;
            }

            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 32);
                snprintf(type, 32, "p");

                break;
            }

            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 32);
                snprintf(type, 32, "e_%s", optarg);

                break;
            }

            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 32);
                snprintf(type, 32, "t_%s", optarg);

                break;
            }

            /* addr */
            case 1 :
            {
                /* set the addr pin */
                if (strcmp("0", optarg) == 0)
                {
                    addr = AT24CXX_ADDRESS_A000;
                }
                else if (strcmp("1", optarg) == 0)
                {
                    addr = AT24CXX_ADDRESS_A001;
                }
                else if (strcmp("2", optarg) == 0)
                {
                    addr = AT24CXX_ADDRESS_A010;
                }
                else if (strcmp("3", optarg) == 0)
                {
                    addr = AT24CXX_ADDRESS_A011;
                }
                else if (strcmp("4", optarg) == 0)
                {
                    addr = AT24CXX_ADDRESS_A100;
                }
                else if (strcmp("5", optarg) == 0)
                {
                    addr = AT24CXX_ADDRESS_A101;
                }
                else if (strcmp("6", optarg) == 0)
                {
                    addr = AT24CXX_ADDRESS_A110;
                }
                else if (strcmp("7", optarg) == 0)
                {
                    addr = AT24CXX_ADDRESS_A111;
                }
                else
                {
                    return 5;
                }

                break;
            }

            /* data */
            case 2 :
            {
                char *p;
                uint16_t l;
                uint16_t i;
                uint64_t hex_data;

                /* set the data */
                l = strlen(optarg);

                /* check the header */
                if (l >= 2)
                {
                    if (strncmp(optarg, "0x", 2) == 0)
                    {
                        p = optarg + 2;
                        l -= 2;
                    }
                    else if (strncmp(optarg, "0X", 2) == 0)
                    {
                        p = optarg + 2;
                        l -= 2;
                    }
                    else
                    {
                        p = optarg;
                    }
                }
                else
                {
                    p = optarg;
                }
                
                /* init 0 */
                hex_data = 0;

                /* loop */
                for (i = 0; i < l; i++)
                {
                    if ((p[i] <= '9') && (p[i] >= '0'))
                    {
                        hex_data += (p[i] - '0') * (uint32_t)pow(16, l - i - 1);
                    }
                    else if ((p[i] <= 'F') && (p[i] >= 'A'))
                    {
                        hex_data += ((p[i] - 'A') + 10) * (uint32_t)pow(16, l - i - 1);
                    }
                    else if ((p[i] <= 'f') && (p[i] >= 'a'))
                    {
                        hex_data += ((p[i] - 'a') + 10) * (uint32_t)pow(16, l - i - 1);
                    }
                    else
                    {
                        return 5;
                    }
                }
                
                /* set the data */
                data = hex_data & 0xFF;
                
                break;
            }

            /* register */
            case 3 :
            {
                char *p;
                uint16_t l;
                uint16_t i;
                uint64_t hex_data;

                /* set the data */
                l = strlen(optarg);

                /* check the header */
                if (l >= 2)
                {
                    if (strncmp(optarg, "0x", 2) == 0)
                    {
                        p = optarg + 2;
                        l -= 2;
                    }
                    else if (strncmp(optarg, "0X", 2) == 0)
                    {
                        p = optarg + 2;
                        l -= 2;
                    }
                    else
                    {
                        p = optarg;
                    }
                }
                else
                {
                    p = optarg;
                }
                
                /* init 0 */
                hex_data = 0;

                /* loop */
                for (i = 0; i < l; i++)
                {
                    if ((p[i] <= '9') && (p[i] >= '0'))
                    {
                        hex_data += (p[i] - '0') * (uint32_t)pow(16, l - i - 1);
                    }
                    else if ((p[i] <= 'F') && (p[i] >= 'A'))
                    {
                        hex_data += ((p[i] - 'A') + 10) * (uint32_t)pow(16, l - i - 1);
                    }
                    else if ((p[i] <= 'f') && (p[i] >= 'a'))
                    {
                        hex_data += ((p[i] - 'a') + 10) * (uint32_t)pow(16, l - i - 1);
                    }
                    else
                    {
                        return 5;
                    }
                }
                
                /* set the data */
                reg = hex_data & 0xFFFF;

                break;
            }

            /* type */
            case 4 :
            {
                if (strcmp("AT24C01", optarg) == 0)
                {
                    chip_type = AT24C01;
                }
                else if (strcmp("AT24C02", optarg) == 0)
                {
                    chip_type = AT24C02;
                }
                else if (strcmp("AT24C04", optarg) == 0)
                {
                    chip_type = AT24C04;
                }
                else if (strcmp("AT24C08", optarg) == 0)
                {
                    chip_type = AT24C08;
                }
                else if (strcmp("AT24C16", optarg) == 0)
                {
                    chip_type = AT24C16;
                }
                else if (strcmp("AT24C32", optarg) == 0)
                {
                    chip_type = AT24C32;
                }
                else if (strcmp("AT24C64", optarg) == 0)
                {
                    chip_type = AT24C64;
                }
                else if (strcmp("AT24C128", optarg) == 0)
                {
                    chip_type = AT24C128;
                }
                else if (strcmp("AT24C256", optarg) == 0)
                {
                    chip_type = AT24C256;
                }
                else if (strcmp("AT24C512", optarg) == 0)
                {
                    chip_type = AT24C512;
                }
                else if (strcmp("AT24CM01", optarg) == 0)
                {
                    chip_type = AT24CM01;
                }
                else if (strcmp("AT24CM02", optarg) == 0)
                {
                    chip_type = AT24CM02;
                }
                else
                {
                    return 5;
                }

                break;
            }

            /* the end */
            case -1 :
            {
                break;
            }

            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_read", type) == 0)
    {
        /* run the read test */
        if (at24cxx_read_test(chip_type, addr) != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (strcmp("e_read", type) == 0)
    {
        uint8_t res;

        /* basic init */
        res = at24cxx_basic_init(chip_type, addr);
        if (res != 0)
        {
            return 1;
        }

        /* read data */
        res = at24cxx_basic_read(reg, (uint8_t *)&data, 1);
        if (res != 0)
        {
            (void)at24cxx_basic_deinit();

            return 1;
        }
        else
        {
            at24cxx_interface_debug_print("at24cxx: read 0x%04x is 0x%02X.\n", reg, data);
        }

        /* deinit */
        (void)at24cxx_basic_deinit();

        return 0;
    }
    else if (strcmp("e_write", type) == 0)
    {
        uint8_t res;

        /* basic init */
        res = at24cxx_basic_init(chip_type, addr);
        if (res != 0)
        {
            return 1;
        }

        /* write data */
        res = at24cxx_basic_write(reg, (uint8_t *)&data, 1);
        if (res != 0)
        {
            (void)at24cxx_basic_deinit();

            return 1;
        }
        else
        {
            at24cxx_interface_debug_print("at24cxx: write 0x%04x is 0x%02X.\n", reg, data);
        }

        /* deinit */
        (void)at24cxx_basic_deinit();

        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        at24cxx_interface_debug_print("Usage:\n");
        at24cxx_interface_debug_print("  at24cxx (-i | --information)\n");
        at24cxx_interface_debug_print("  at24cxx (-h | --help)\n");
        at24cxx_interface_debug_print("  at24cxx (-p | --port)\n");
        at24cxx_interface_debug_print("  at24cxx (-t read | --test=read) [--type=<AT24C01 | AT24C02 | AT24C04 | AT24C08 | AT24C16 | AT24C32 | AT24C64 | AT24C128 | AT24C256 |\n");
        at24cxx_interface_debug_print("                                           AT24C512 | AT24CM01 | AT24CM02>]\n");
        at24cxx_interface_debug_print("          [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]\n");
        at24cxx_interface_debug_print("  at24cxx (-e read | --example=read) [--type=<AT24C01 | AT24C02 | AT24C04 | AT24C08 | AT24C16 | AT24C32 | AT24C64 | AT24C128 | AT24C256 |\n");
        at24cxx_interface_debug_print("                                              AT24C512 | AT24CM01 | AT24CM02>]\n");
        at24cxx_interface_debug_print("          [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--reg=<address>]\n");
        at24cxx_interface_debug_print("  at24cxx (-e write | --example=write) [--type=<AT24C01 | AT24C02 | AT24C04 | AT24C08 | AT24C16 | AT24C32 | AT24C64 | AT24C128 | AT24C256 |\n");
        at24cxx_interface_debug_print("                                                AT24C512 | AT24CM01 | AT24CM02>]\n");
        at24cxx_interface_debug_print("          [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--reg=<address>] [--data=<value>]\n");
        at24cxx_interface_debug_print("\n");
        at24cxx_interface_debug_print("Options:\n");
        at24cxx_interface_debug_print("      --addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>    Set the connection of the addr pin and the addr number is A2A1A0.([default: 0])\n");
        at24cxx_interface_debug_print("      --data=<value>                            Set the sent data and it is hexadecimal.([default: random])\n");
        at24cxx_interface_debug_print("  -e <read>, --example=<read>                   Run the driver example.\n");
        at24cxx_interface_debug_print("  -h, --help                                    Show the help.\n");
        at24cxx_interface_debug_print("  -i, --information                             Show the chip information.\n");
        at24cxx_interface_debug_print("  -p, --port                                    Display the pin connections of the current board.\n");
        at24cxx_interface_debug_print("      --reg=<address>                           Set the register address and it is hexadecimal.([default: 0x0000])\n");
        at24cxx_interface_debug_print("  -t <read | write>, --test=<read | write>      Run the driver test.\n");
        at24cxx_interface_debug_print("      --type=<AT24C01 | AT24C02 | AT24C04 | AT24C08 | AT24C16 | AT24C32 | AT24C64 | AT24C128 | AT24C256 |\n");
        at24cxx_interface_debug_print("              AT24C512 | AT24CM01 | AT24CM02>\n");
        at24cxx_interface_debug_print("                                                Set the chip type.([default: AT24C01])\n");

        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        at24cxx_info_t info;

        /* print at24cxx info */
        at24cxx_info(&info);
        at24cxx_interface_debug_print("at24cxx: chip is %s.\n", info.chip_name);
        at24cxx_interface_debug_print("at24cxx: manufacturer is %s.\n", info.manufacturer_name);
        at24cxx_interface_debug_print("at24cxx: interface is %s.\n", info.interface);
        at24cxx_interface_debug_print("at24cxx: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        at24cxx_interface_debug_print("at24cxx: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        at24cxx_interface_debug_print("at24cxx: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        at24cxx_interface_debug_print("at24cxx: max current is %0.2fmA.\n", info.max_current_ma);
        at24cxx_interface_debug_print("at24cxx: max temperature is %0.1fC.\n", info.temperature_max);
        at24cxx_interface_debug_print("at24cxx: min temperature is %0.1fC.\n", info.temperature_min);

        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        at24cxx_interface_debug_print("at24cxx: SCL connected to GPIOB PIN8.\n");
        at24cxx_interface_debug_print("at24cxx: SDA connected to GPIOB PIN9.\n");

        return 0;
    }
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

    /* uart init */
    uart_init(115200);

    /* shell init && register at24cxx function */
    shell_init();
    shell_register("at24cxx", at24cxx);
    uart_print("at24cxx: welcome to libdriver at24cxx.\n");

    while (1)
    {
        /* read uart */
        g_len = uart_read(g_buf, 256);
        if (g_len != 0)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart_print("at24cxx: run failed.\n");
            }
            else if (res == 2)
            {
                uart_print("at24cxx: unknown command.\n");
            }
            else if (res == 3)
            {
                uart_print("at24cxx: length is too long.\n");
            }
            else if (res == 4)
            {
                uart_print("at24cxx: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart_print("at24cxx: param is invalid.\n");
            }
            else
            {
                uart_print("at24cxx: unknown status code.\n");
            }
            uart_flush();
        }
        delay_ms(100);
    }
}
