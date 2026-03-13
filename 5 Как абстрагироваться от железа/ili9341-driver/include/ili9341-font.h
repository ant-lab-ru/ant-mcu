#pragma once

#include <stdint.h>
#include "ili9341-driver.h"

/**
 * Bitmap font descriptor.
 *
 * Font data layout: one byte per row, `height` rows per glyph.
 * Bit 7 of each byte is the leftmost pixel; bit 0 is the rightmost.
 * Glyphs are stored contiguously starting at `first_char`.
 */
typedef struct ili9341_font_t {
    const unsigned char* data; /* Pointer to raw glyph bitmap data      */
    uint8_t        width;      /* Glyph width  in pixels (≤8)           */
    uint8_t        height;     /* Glyph height in pixels                */
    uint8_t        first_char; /* First ASCII codepoint in the table    */
    uint8_t        char_count; /* Number of glyphs in the table         */
} ili9341_font_t;

/* Built-in 8×8 monospaced font covering ASCII 0x20–0x7E. */
extern const ili9341_font_t jetbrains_font;

/**
 * Render a single character at (x, y).
 * Characters outside the glyph table are replaced with a space.
 */
void ili9341_draw_char(const ili9341_display_t *dev,
                       uint16_t x, uint16_t y, char c,
                       const ili9341_font_t *font,
                       uint16_t color, uint16_t bg_color);


/** Render a null-terminated string. Stops at display edge. */
void ili9341_draw_text(const ili9341_display_t *dev,
                       uint16_t x, uint16_t y,
                       const char *text,
                       const ili9341_font_t *font,
                       uint16_t color, uint16_t bg_color);