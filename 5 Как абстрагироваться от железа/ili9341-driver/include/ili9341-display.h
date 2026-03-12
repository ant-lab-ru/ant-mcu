#pragma once

#include "ili9341-driver.h"
#include "ili9341-font.h"

/* ── Colour helpers ──────────────────────────────────────────────────── */
#define COLOR_BLACK      ((uint16_t)0x0000)
#define COLOR_WHITE      ((uint16_t)0xFFFF)
#define COLOR_RED        ((uint16_t)0xF800)
#define COLOR_GREEN      ((uint16_t)0x07E0)
#define COLOR_BLUE       ((uint16_t)0x001F)
#define COLOR_CYAN       ((uint16_t)0x07FF)
#define COLOR_MAGENTA    ((uint16_t)0xF81F)
#define COLOR_YELLOW     ((uint16_t)0xFFE0)
#define COLOR_ORANGE     ((uint16_t)0xFC00)

/** Convert 8-bit R, G, B components to 16-bit RGB565. */
#define RGB565(r, g, b) \
    ((uint16_t)( (((uint16_t)(r) & 0xF8u) << 8) | \
                 (((uint16_t)(g) & 0xFCu) << 3) | \
                 (((uint16_t)(b) & 0xF8u) >> 3) ))

#define RGB888_2_RGB565(c) RGB565((c & 0x00FF0000) >> 16, (c & 0x0000FF00) >> 8, (c & 0x000000FF))

/* ── Drawing API ─────────────────────────────────────────────────────── */

/** Fill the entire display with one colour. */
void ili9341_fill_screen(const ili9341_display_t *dev, uint16_t color);

/** Draw a single pixel. Out-of-bounds calls are silently ignored. */
void ili9341_draw_pixel(const ili9341_display_t *dev,
                        uint16_t x, uint16_t y, uint16_t color);

/** Draw a filled rectangle. Clips to display bounds automatically. */
void ili9341_draw_filled_rect(const ili9341_display_t *dev,
                               uint16_t x, uint16_t y,
                               uint16_t width, uint16_t height,
                               uint16_t color);

/** Draw a hollow rectangle (outline only). */
void ili9341_draw_rect(const ili9341_display_t *dev,
                       uint16_t x, uint16_t y,
                       uint16_t width, uint16_t height,
                       uint16_t color);

/** Draw a line using Bresenham's algorithm. */
void ili9341_draw_line(const ili9341_display_t *dev,
                       uint16_t x0, uint16_t y0,
                       uint16_t x1, uint16_t y1,
                       uint16_t color);

/**
 * Set display rotation and update dev->width / dev->height accordingly.
 * Writes the MADCTL register (0x36) as per the spec.
 */
void ili9341_set_rotation(ili9341_display_t *dev,
                          ili9341_rotation_t rotation);
