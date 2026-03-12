#include "ili9341-display.h"

/* ── Internal helpers ────────────────────────────────────────────────── */

/**
 * Write a contiguous block of identically-coloured pixels.
 * CS and DC are managed here; caller must have already issued
 * ili9341_set_address_window().
 */
static void write_pixels(const ili9341_display_t *dev,
                         uint16_t color, uint32_t count)
{
    uint8_t pixel[2] = { (uint8_t)(color >> 8), (uint8_t)(color & 0xFFu) };
    const ili9341_hal_t *hal = &dev->hal;

    hal->gpio_cs_write(false);
    hal->gpio_dc_write(true);   /* data mode */
    while (count--) {
        hal->spi_write(pixel, 2);
    }
    hal->gpio_cs_write(true);
}

/* ── Public API ──────────────────────────────────────────────────────── */

void ili9341_fill_screen(const ili9341_display_t *dev, uint16_t color)
{
    ili9341_draw_filled_rect(dev, 0, 0, dev->width, dev->height, color);
}

void ili9341_draw_pixel(const ili9341_display_t *dev,
                        uint16_t x, uint16_t y, uint16_t color)
{
    if (x >= dev->width || y >= dev->height) return;
    ili9341_set_address_window(dev, x, y, x, y);
    write_pixels(dev, color, 1);
}

void ili9341_draw_filled_rect(const ili9341_display_t *dev,
                               uint16_t x, uint16_t y,
                               uint16_t width, uint16_t height,
                               uint16_t color)
{
    if (x >= dev->width || y >= dev->height) return;

    /* Clip to display bounds */
    if (x + width  > dev->width)  width  = dev->width  - x;
    if (y + height > dev->height) height = dev->height - y;

    ili9341_set_address_window(dev,
                               x, y,
                               x + width  - 1u,
                               y + height - 1u);
    write_pixels(dev, color, (uint32_t)width * height);
}

void ili9341_draw_rect(const ili9341_display_t *dev,
                       uint16_t x, uint16_t y,
                       uint16_t width, uint16_t height,
                       uint16_t color)
{
    if (width == 0 || height == 0) return;

    /* Top / bottom horizontal edges */
    ili9341_draw_filled_rect(dev, x, y,             width, 1, color);
    ili9341_draw_filled_rect(dev, x, y + height - 1u, width, 1, color);

    /* Left / right vertical edges (avoid overdrawing corners) */
    if (height > 2u) {
        ili9341_draw_filled_rect(dev, x,             y + 1u, 1, height - 2u, color);
        ili9341_draw_filled_rect(dev, x + width - 1u, y + 1u, 1, height - 2u, color);
    }
}

void ili9341_draw_line(const ili9341_display_t *dev,
                       uint16_t x0, uint16_t y0,
                       uint16_t x1, uint16_t y1,
                       uint16_t color)
{
    /* Bresenham's line algorithm */
    int16_t dx  =  (int16_t)x1 - (int16_t)x0;
    int16_t dy  =  (int16_t)y1 - (int16_t)y0;
    int16_t sx  = (dx > 0) ? 1 : -1;
    int16_t sy  = (dy > 0) ? 1 : -1;
    if (dx < 0) dx = -dx;
    if (dy < 0) dy = -dy;
    int16_t err = dx - dy;

    int16_t x = (int16_t)x0;
    int16_t y = (int16_t)y0;

    for (;;) {
        if (x >= 0 && y >= 0) {
            ili9341_draw_pixel(dev, (uint16_t)x, (uint16_t)y, color);
        }
        if (x == (int16_t)x1 && y == (int16_t)y1) break;
        int16_t e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x += sx; }
        if (e2 <  dx) { err += dx; y += sy; }
    }
}

/* ── Rotation ────────────────────────────────────────────────────────── */

static uint8_t madctl_for_rotation(ili9341_rotation_t rotation,
                                   uint16_t *out_width,
                                   uint16_t *out_height)
{
    switch (rotation) {
        case ILI9341_ROTATION_0:
            *out_width  = ILI9341_NATIVE_WIDTH;
            *out_height = ILI9341_NATIVE_HEIGHT;
            return ILI9341_MADCTL_MX | ILI9341_MADCTL_BGR;

        case ILI9341_ROTATION_90:
            *out_width  = ILI9341_NATIVE_HEIGHT;
            *out_height = ILI9341_NATIVE_WIDTH;
            return ILI9341_MADCTL_MV | ILI9341_MADCTL_BGR;

        case ILI9341_ROTATION_180:
            *out_width  = ILI9341_NATIVE_WIDTH;
            *out_height = ILI9341_NATIVE_HEIGHT;
            return ILI9341_MADCTL_MY | ILI9341_MADCTL_BGR;

        case ILI9341_ROTATION_270:
            *out_width  = ILI9341_NATIVE_HEIGHT;
            *out_height = ILI9341_NATIVE_WIDTH;
            return ILI9341_MADCTL_MX | ILI9341_MADCTL_MY |
                   ILI9341_MADCTL_MV | ILI9341_MADCTL_BGR;

        default:
            *out_width  = ILI9341_NATIVE_WIDTH;
            *out_height = ILI9341_NATIVE_HEIGHT;
            return ILI9341_MADCTL_MX | ILI9341_MADCTL_BGR;
    }
}

void ili9341_set_rotation(ili9341_display_t *dev,
                          ili9341_rotation_t rotation)
{
    uint16_t w, h;
    uint8_t  madctl = madctl_for_rotation(rotation, &w, &h);

    dev->rotation = rotation;
    dev->width    = w;
    dev->height   = h;

    ili9341_write_cmd(dev, ILI9341_CMD_MADCTL);
    ili9341_write_data_byte(dev, madctl);
}
