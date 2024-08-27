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
 * @file      driver_at24cxx_basic.c
 * @brief     driver at24cxx basic source file
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

#include "driver_at24cxx_basic.h"

static at24cxx_handle_t gs_handle;        /**< at24cxx handle */

/**
 * @brief     basic example init
 * @param[in] type is the chip type
 * @param[in] address is the chip address pin
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t at24cxx_basic_init(at24cxx_t type, at24cxx_address_t address)
{
    uint8_t res;
    
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
    
    /* set chip type */
    res = at24cxx_set_type(&gs_handle, type);
    if (res != 0)
    {
        at24cxx_interface_debug_print("at24cxx: set type failed.\n");
       
        return 1;
    }
    
    /* set addr pin */
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

    return 0;
}

/**
 * @brief      basic example read
 * @param[in]  address is the register address
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the buffer length
 * @return     status code
 *             - 0 success
 *             - 1 read data failed
 * @note       none
 */
uint8_t at24cxx_basic_read(uint32_t address, uint8_t *buf, uint16_t len)
{
    /* read data */
    if (at24cxx_read(&gs_handle, address, buf, len) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief     basic example write
 * @param[in] address is the register address
 * @param[in] *buf points to a data buffer
 * @param[in] len is the buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write data failed
 * @note      none
 */
uint8_t at24cxx_basic_write(uint32_t address, uint8_t *buf, uint16_t len)
{
    /* read data */
    if (at24cxx_write(&gs_handle, address, buf, len) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t at24cxx_basic_deinit(void)
{
    /* at24cxx deinit */
    if (at24cxx_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
