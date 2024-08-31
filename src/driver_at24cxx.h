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
 * @file      driver_at24cxx.h
 * @brief     driver at24cxx header file
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

#ifndef DRIVER_AT24CXX_H
#define DRIVER_AT24CXX_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup at24cxx_driver at24cxx driver function
 * @brief    at24cxx driver modules
 * @{
 */

/**
 * @addtogroup at24cxx_base_driver
 * @{
 */

/**
 * @brief at24cxx type enumeration definition
 */
typedef enum
{
    AT24C01  = 128,          /**< AT24C01 type */
    AT24C02  = 256,          /**< AT24C02 type */
    AT24C04  = 512,          /**< AT24C04 type */
    AT24C08  = 1024,         /**< AT24C08 type */
    AT24C16  = 2048,         /**< AT24C16 type */
    AT24C32  = 4096,         /**< AT24C32 type */
    AT24C64  = 8192,         /**< AT24C64 type */
    AT24C128 = 16384,        /**< AT24C128 type */
    AT24C256 = 32768,        /**< AT24C256 type */
    AT24C512 = 65536,        /**< AT24C512 type */
    AT24CM01 = 131072,       /**< AT24CM01 type */
    AT24CM02 = 262144,       /**< AT24CM02 type */
} at24cxx_t;

/**
 * @brief at24cxx address enumeration definition
 */
typedef enum
{
    AT24CXX_ADDRESS_A000 = 0,        /**< A2A1A0 000 */
    AT24CXX_ADDRESS_A001 = 1,        /**< A2A1A0 001 */
    AT24CXX_ADDRESS_A010 = 2,        /**< A2A1A0 010 */
    AT24CXX_ADDRESS_A011 = 3,        /**< A2A1A0 011 */
    AT24CXX_ADDRESS_A100 = 4,        /**< A2A1A0 100 */
    AT24CXX_ADDRESS_A101 = 5,        /**< A2A1A0 101 */
    AT24CXX_ADDRESS_A110 = 6,        /**< A2A1A0 110 */
    AT24CXX_ADDRESS_A111 = 7,        /**< A2A1A0 111 */
} at24cxx_address_t;

/**
 * @brief at24cxx handle structure definition
 */
typedef struct at24cxx_handle_s
{
    uint8_t iic_addr;                                                                              /**< iic device address */
    uint8_t (*iic_init)(void);                                                                     /**< point to an iic_init function address */
    uint8_t (*iic_deinit)(void);                                                                   /**< point to an iic_deinit function address */
    uint8_t (*iic_read)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);                    /**< point to an iic_read function address */
    uint8_t (*iic_write)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);                   /**< point to an iic_write function address */
    uint8_t (*iic_read_address16)(uint8_t addr, uint16_t reg, uint8_t *buf, uint16_t len);         /**< point to an iic_read_address16 function address */
    uint8_t (*iic_write_address16)(uint8_t addr, uint16_t reg, uint8_t *buf, uint16_t len);        /**< point to an iic_write_address16 function address */
    void (*delay_ms)(uint32_t ms);                                                                 /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                                               /**< point to a debug_print function address */
    uint32_t id;                                                                                   /**< chip id */
    uint8_t inited;                                                                                /**< inited flag */
} at24cxx_handle_t;

/**
 * @brief at24cxx information structure definition
 */
typedef struct at24cxx_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} at24cxx_info_t;

/**
 * @}
 */

/**
 * @defgroup at24cxx_link_driver at24cxx link driver function
 * @brief    at24cxx link driver modules
 * @ingroup  at24cxx_driver
 * @{
 */

/**
 * @brief     initialize at24cxx_handle_t structure
 * @param[in] HANDLE points to an at24cxx handle structure
 * @param[in] STRUCTURE is at24cxx_handle_t
 * @note      none
 */
#define DRIVER_AT24CXX_LINK_INIT(HANDLE, STRUCTURE)           memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link iic_init function
 * @param[in] HANDLE points to an at24cxx handle structure
 * @param[in] FUC points to an iic_init function address
 * @note      none
 */
#define DRIVER_AT24CXX_LINK_IIC_INIT(HANDLE, FUC)             (HANDLE)->iic_init = FUC

/**
 * @brief     link iic_deinit function
 * @param[in] HANDLE points to an at24cxx handle structure
 * @param[in] FUC points to an iic_deinit function address
 * @note      none
 */
#define DRIVER_AT24CXX_LINK_IIC_DEINIT(HANDLE, FUC)           (HANDLE)->iic_deinit = FUC

/**
 * @brief     link iic_read function
 * @param[in] HANDLE points to an at24cxx handle structure
 * @param[in] FUC points to an iic_read function address
 * @note      none
 */
#define DRIVER_AT24CXX_LINK_IIC_READ(HANDLE, FUC)             (HANDLE)->iic_read = FUC

/**
 * @brief     link iic_write function
 * @param[in] HANDLE points to an at24cxx handle structure
 * @param[in] FUC points to an iic_write function address
 * @note      none
 */
#define DRIVER_AT24CXX_LINK_IIC_WRITE(HANDLE, FUC)            (HANDLE)->iic_write = FUC

/**
 * @brief     link iic_read_address16 function
 * @param[in] HANDLE points to an at24cxx handle structure
 * @param[in] FUC points to an iic_read_address16 function address
 * @note      none
 */
#define DRIVER_AT24CXX_LINK_IIC_READ_ADDRESS16(HANDLE, FUC)   (HANDLE)->iic_read_address16 = FUC

/**
 * @brief     link iic_write_address16 function
 * @param[in] HANDLE points to an at24cxx handle structure
 * @param[in] FUC points to an iic_write_address16 function address
 * @note      none
 */
#define DRIVER_AT24CXX_LINK_IIC_WRITE_ADDRESS16(HANDLE, FUC)  (HANDLE)->iic_write_address16 = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to an at24cxx handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_AT24CXX_LINK_DELAY_MS(HANDLE, FUC)             (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to an at24cxx handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_AT24CXX_LINK_DEBUG_PRINT(HANDLE, FUC)          (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup at24cxx_base_driver at24cxx base driver function
 * @brief    at24cxx base driver modules
 * @ingroup  at24cxx_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info points to an at24cxx info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t at24cxx_info(at24cxx_info_t *info);

/**
 * @brief     initialize the chip
 * @param[in] *handle points to an at24cxx handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t at24cxx_init(at24cxx_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle points to an at24cxx handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t at24cxx_deinit(at24cxx_handle_t *handle);

/**
 * @brief     set the chip type
 * @param[in] *handle points to an at24cxx handle structure
 * @param[in] type is the chip type
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t at24cxx_set_type(at24cxx_handle_t *handle, at24cxx_t type);

/**
 * @brief      get the chip type
 * @param[in]  *handle points to an at24cxx handle structure
 * @param[out] *type points to a chip type buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t at24cxx_get_type(at24cxx_handle_t *handle, at24cxx_t *type);

/**
 * @brief     set the chip address pin
 * @param[in] *handle points to an at24cxx handle structure
 * @param[in] addr_pin is the chip address pin
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t at24cxx_set_addr_pin(at24cxx_handle_t *handle, at24cxx_address_t addr_pin);

/**
 * @brief      get the chip address pin
 * @param[in]  *handle points to an at24cxx handle structure
 * @param[out] *addr_pin points to a chip address pin
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t at24cxx_get_addr_pin(at24cxx_handle_t *handle, at24cxx_address_t *addr_pin);

/**
 * @brief      read bytes from the chip
 * @param[in]  *handle points to an at24cxx handle structure
 * @param[in]  address is the register address
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the buffer length
 * @return     status code
 *             - 0 success
 *             - 1 read data failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 end address is over the max address
 * @note       none
 */
uint8_t at24cxx_read(at24cxx_handle_t *handle, uint32_t address, uint8_t *buf, uint16_t len);

/**
 * @brief     write bytes to the chip
 * @param[in] *handle points to an at24cxx handle structure
 * @param[in] address is the register address
 * @param[in] *buf points to a data buffer
 * @param[in] len is the buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write data failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 end address is over the max address
 * @note      none
 */
uint8_t at24cxx_write(at24cxx_handle_t *handle, uint32_t address, uint8_t *buf, uint16_t len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
