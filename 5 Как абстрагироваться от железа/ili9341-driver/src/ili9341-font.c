#include "ili9341-font.h"
#include "font-jetbrains.h"

const ili9341_font_t jetbrains_font = {
    .data       = (const unsigned char*)font_jetbrains_mono_8,
    .width      = FONT_JETBRAINS_MONO_8_CHAR_WIDTH,
    .height     = FONT_JETBRAINS_MONO_8_CHAR_HEIGHT,
    .first_char = FONT_JETBRAINS_MONO_8_START_CHAR,
    .char_count = FONT_JETBRAINS_MONO_8_LENGTH
};

/* ── Character renderer ──────────────────────────────────────────────── */

void ili9341_draw_char(const ili9341_display_t *dev,
                       uint16_t x, uint16_t y, char c,
                       const ili9341_font_t *font,
                       uint16_t color, uint16_t bg_color)
{
    if (x + font->width  > dev->width)  return;
    if (y + font->height > dev->height) return;

    /* Map out-of-range characters to space */
    uint8_t uc = (uint8_t)c;
    if (uc < font->first_char || uc >= font->first_char + font->char_count) {
        uc = font->first_char;  /* space */
    }

    const unsigned char *glyph = font->data +
                           (uint32_t)(uc - font->first_char) * font->height;

    uint8_t fg_hi = (uint8_t)(color    >> 8);
    uint8_t fg_lo = (uint8_t)(color    & 0xFFu);
    uint8_t bg_hi = (uint8_t)(bg_color >> 8);
    uint8_t bg_lo = (uint8_t)(bg_color & 0xFFu);

    /* Set address window once, then stream all pixels */
    ili9341_set_address_window(dev,
                               x, y,
                               x + font->width  - 1u,
                               y + font->height - 1u);

    const ili9341_hal_t *hal = &dev->hal;
    hal->gpio_cs_write(false);
    hal->gpio_dc_write(true);   /* data mode */

    for (uint8_t row = 0; row < font->height; row++) {
        unsigned char bits = glyph[row];
        for (uint8_t col = font->width; col > 0; col--) {
            uint8_t pixel[2];
            if (bits & (0x80u >> col)) {
                pixel[0] = fg_hi; pixel[1] = fg_lo;
            } else {
                pixel[0] = bg_hi; pixel[1] = bg_lo;
            }
            hal->spi_write(pixel, 2);
        }
    }

    hal->gpio_cs_write(true);
}

void ili9341_draw_text(const ili9341_display_t *dev,
                       uint16_t x, uint16_t y,
                       const char *text,
                       const ili9341_font_t *font,
                       uint16_t color, uint16_t bg_color)
{
    if (!text || !font) return;

    uint16_t cursor_x = x;
    while (*text) {
        if (cursor_x + font->width > dev->width) break;
        ili9341_draw_char(dev, cursor_x, y, *text, font, color, bg_color);
        cursor_x = (uint16_t)(cursor_x + font->width);
        text++;
    }
}
