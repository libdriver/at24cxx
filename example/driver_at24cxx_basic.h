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
 * @file      driver_at24cxx_basic.h
 * @brief     driver at24cxx basic header file
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

#ifndef DRIVER_AT24CXX_BASIC_H
#define DRIVER_AT24CXX_BASIC_H

#include "driver_at24cxx_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup at24cxx_example_driver at24cxx example driver function
 * @brief    at24cxx example driver modules
 * @ingroup  at24cxx_driver
 * @{
 */

/**
 * @brief     basic example init
 * @param[in] type is the chip type
 * @param[in] address is the chip address pin
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t at24cxx_basic_init(at24cxx_t type, at24cxx_address_t address);

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t at24cxx_basic_deinit(void);

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
uint8_t at24cxx_basic_read(uint32_t address, uint8_t *buf, uint16_t len);

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
uint8_t at24cxx_basic_write(uint32_t address, uint8_t *buf, uint16_t len);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
