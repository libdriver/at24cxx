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
 * @file      driver_at24cxx_read_test.c
 * @brief     driver at24cxx read test source file
 * @version   2.0.0
 * @author    Shifeng Li
 * @date      2021-02-17
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/02/17  <td>2.0      <td>Shifeng Li  <td>format the code
 * <tr><td>2020/10/15  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */
 
#include "driver_at24cxx_read_test.h"
#include <stdlib.h>

static at24cxx_handle_t gs_handle;        /**< at24cxx handle */

/**
 * @brief     read test
 * @param[in] type is the chip type
 * @param[in] address is the chip address pin
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t at24cxx_read_test(at24cxx_t type, at24cxx_address_t address)
{
    uint8_t res, i, j;
    uint8_t buf[12];
    uint8_t buf_check[12];
    uint32_t inc;
    at24cxx_info_t info;
    
    /* link interface function */
    DRIVER_AT24CXX_LINK_INIT(&gs_handle, at24cxx_handle_t);
    DRIVER_AT24CXX_LINK_IIC_INIT(&gs_handle, at24cxx_interface_iic_init);
    DRIVER_AT24CXX_LINK_IIC_DEINIT(&gs_handle, at24cxx_interface_iic_deinit);
    DRIVER_AT24CXX_LINK_IIC_READ(&gs_handle, at24cxx_interface_iic_read);
    DRIVER_AT24CXX_LINK_IIC_WRITE(&gs_handle, at24cxx_interface_iic_write);
    DRIVER_AT24CXX_LINK_IIC_READ_ADDRESS16(&gs_handle, at24cxx_interface_iic_read_address16);
    DRIVER_AT24CXX_LINK_IIC_WRITE_ADDRESS16(&gs_handle, at24cxx_interface_iic_write_address16);
    DRIVER_AT24CXX_LINK_DELAY_MS(&gs_handle, at24cxx_interface_delay_ms);
    DRIVER_AT24CXX_LINK_DEBUG_PRINT(&gs_handle, at24cxx_interface_debug_print);
    
    /* get information */
    res = at24cxx_info(&info);
    if (res != 0)
    {
        at24cxx_interface_debug_print("at24cxx: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print chip information */
        at24cxx_interface_debug_print("at24cxx: chip is %s.\n", info.chip_name);
        at24cxx_interface_debug_print("at24cxx: manufacturer is %s.\n", info.manufacturer_name);
        at24cxx_interface_debug_print("at24cxx: interface is %s.\n", info.interface);
        at24cxx_interface_debug_print("at24cxx: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        at24cxx_interface_debug_print("at24cxx: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        at24cxx_interface_debug_print("at24cxx: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        at24cxx_interface_debug_print("at24cxx: max current is %0.2fmA.\n", info.max_current_ma);
        at24cxx_interface_debug_print("at24cxx: max temperature is %0.1fC.\n", info.temperature_max);
        at24cxx_interface_debug_print("at24cxx: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* set chip type */
    res = at24cxx_set_type(&gs_handle, type);
    if (res != 0)
    {
        at24cxx_interface_debug_print("at24cxx: set type failed.\n");
       
        return 1;
    }
    
    /* set iic addr pin */
    res = at24cxx_set_addr_pin(&gs_handle, address);
    if (res != 0)
    {
        at24cxx_interface_debug_print("at24cxx: set address pin failed.\n");
       
        return 1;
    }
    
    /* at24cxx init */
    res = at24cxx_init(&gs_handle);
    if (res != 0)
    {
        at24cxx_interface_debug_print("at24cxx: init failed.\n");
       
        return 1;
    }
    
    /* start read test */
    at24cxx_interface_debug_print("at24cxx: start read test.\n");
    inc = ((uint32_t)type + 1) / 8;
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 12; j++)
        {
            buf[j] = (uint8_t)(rand() % 256);
        }
    
        /* write data */
        res = at24cxx_write(&gs_handle, i*inc, (uint8_t *)buf, 12);
        if (res != 0)
        {
            at24cxx_interface_debug_print("at24cxx: write failed.\n");
            (void)at24cxx_deinit(&gs_handle);
            
            return 1;
        }

        /* read data */
        res = at24cxx_read(&gs_handle, i*inc, (uint8_t *)buf_check, 12);
        if (res != 0)
        {
            at24cxx_interface_debug_print("at24cxx: read failed.\n");
            (void)at24cxx_deinit(&gs_handle);
            
            return 1;
        }
        for (j = 0; j < 12; j++)
        {
            /* check data */
            if (buf[j] != buf_check[j])
            {
                at24cxx_interface_debug_print("at24cxx: check error.\n");
                (void)at24cxx_deinit(&gs_handle);
                
                return 1;
            }
        }
        at24cxx_interface_debug_print("at24cxx: 0x%04X read write test passed.\n", i*inc);
    }

    /* finish read test */
    at24cxx_interface_debug_print("at24cxx: finish read test.\n");
    (void)at24cxx_deinit(&gs_handle);
    
    return 0;
}
