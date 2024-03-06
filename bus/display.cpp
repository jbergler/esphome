#include "esphome/components/display/display.h"
#include "esphome/components/display/rect.h"

using esphome::Color;
using esphome::display::Display;
using esphome::display::BaseFont;
using esphome::display::Rect;
using esphome::display::TextAlign;

#define SLOTS 8
#define PADDING 2

Rect get_box(Display &it, int pos) {
    const int width = it.get_width() / SLOTS;
    const int height = it.get_height();
    it.start_clipping(
        width * pos, // left
        0, // top
        (width * (pos + 1)) - 1, // right
        height // bottom
    );
    return it.get_clipping();
};

void draw_bar(Display &it, int pos, const char *name, float value, BaseFont *icon_font, BaseFont *text_font) {
    Rect box = get_box(it, pos);
    int top = box.y + PADDING;
    const int mid = box.x + (box.w / 2);
    it.print(
        mid,
        top,
        icon_font,
        TextAlign::CENTER_HORIZONTAL,
        name
    );
    top += 36;

    it.printf(
        mid,
        top,
        text_font,
        TextAlign::CENTER_HORIZONTAL,
        "%.0f %%",
        value * 100
    );
    top += 12 + (2 * PADDING);

    Color color = (value <= 0.4) ? Color(0xff, 0x00, 0x00) : esphome::display::COLOR_ON;

    const int bar_left = box.x + PADDING;
    const int bar_top = top;
    const int bar_width = box.w - PADDING * 2;
    const int bar_height = box.h - bar_top - PADDING;
    const int fill_height = bar_height * value;
    
    it.filled_rectangle(bar_left, bar_top + bar_height - fill_height, bar_width, fill_height, color);
    it.rectangle(bar_left, bar_top, bar_width, bar_height);
    
    it.end_clipping();
};