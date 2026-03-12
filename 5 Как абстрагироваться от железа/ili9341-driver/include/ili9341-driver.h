#pragma once

#include "ili9341-driver.h"

/* ── Register definitions (ILI9341 datasheet) ───────────────────────── */
#define ILI9341_CMD_SWRESET 0x01u   /* Software Reset                  */
#define ILI9341_CMD_SLEEP_OUT 0x11u /* Sleep Mode OFF                  */
#define ILI9341_CMD_INVOFF 0x20u    /* Display Inversion OFF           */
#define ILI9341_CMD_INVON 0x21u     /* Display Inversion ON            */
#define ILI9341_CMD_GAMMA 0x26u     /* Gamma Curve Selection           */
#define ILI9341_CMD_DISPOFF 0x28u   /* Display OFF                     */
#define ILI9341_CMD_DISPON 0x29u    /* Display ON                      */
#define ILI9341_CMD_CASET 0x2Au     /* Column Address Set              */
#define ILI9341_CMD_PASET 0x2Bu     /* Page Address Set                */
#define ILI9341_CMD_MEMWRITE 0x2Cu  /* Memory Write                    */
#define ILI9341_CMD_MEMREAD 0x2Eu   /* Memory Read                     */
#define ILI9341_CMD_MADCTL 0x36u    /* Memory Access Control (rotation)*/
#define ILI9341_CMD_COLMOD 0x3Au    /* Interface Pixel Format          */

/* Pixel format: 16-bit RGB565 */
#define ILI9341_COLMOD_16BIT 0x55u

/* MADCTL bit flags */
#define ILI9341_MADCTL_MY 0x80u  /* Row address order               */
#define ILI9341_MADCTL_MX 0x40u  /* Column address order            */
#define ILI9341_MADCTL_MV 0x20u  /* Row/Column exchange             */
#define ILI9341_MADCTL_ML 0x10u  /* Vertical refresh order          */
#define ILI9341_MADCTL_BGR 0x08u /* BGR colour order (most modules) */
#define ILI9341_MADCTL_MH 0x04u  /* Horizontal refresh order        */

#define ILI9341_NATIVE_WIDTH 240u
#define ILI9341_NATIVE_HEIGHT 320u

#include <stdint.h>
#include <stdbool.h>

typedef void (*ili9341_spi_write)(const uint8_t* data, uint32_t size);
typedef void (*ili9341_spi_read)(uint8_t* buffer, uint32_t length);
typedef void (*ili9341_gpio_cs_write)(bool level);      /* Chip Select  — active LOW  */
typedef void (*ili9341_gpio_dc_write)(bool level);      /* Data/Command — 0=CMD 1=DATA */
typedef void (*ili9341_gpio_reset_write)(bool level);   /* Reset        — active LOW  */
typedef void (*ili9341_delay_ms)(uint32_t ms);

typedef struct
{
    ili9341_spi_write spi_write;
    ili9341_spi_read spi_read;
    ili9341_gpio_cs_write gpio_cs_write;
    ili9341_gpio_dc_write gpio_dc_write;
    ili9341_gpio_reset_write gpio_reset_write;
    ili9341_delay_ms delay_ms;
} ili9341_hal_t;

typedef enum
{
    ILI9341_ROTATION_0 = 0,   /* Portrait  240×320 */
    ILI9341_ROTATION_90 = 1,  /* Landscape 320×240 */
    ILI9341_ROTATION_180 = 2, /* Portrait  240×320 inverted */
    ILI9341_ROTATION_270 = 3  /* Landscape 320×240 inverted */
} ili9341_rotation_t;

typedef struct
{
    ili9341_hal_t hal;
    uint16_t width;
    uint16_t height;
    ili9341_rotation_t rotation;
} ili9341_display_t;

bool ili9341_init(ili9341_display_t *dev, const ili9341_hal_t *hal);

void ili9341_write_cmd(const ili9341_display_t *dev, uint8_t cmd);
void ili9341_write_data(const ili9341_display_t *dev, const uint8_t *data, uint32_t len);
void ili9341_write_data_byte(const ili9341_display_t *dev, uint8_t byte);
void ili9341_set_address_window(const ili9341_display_t *dev, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
