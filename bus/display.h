#include "esphome/components/display/rect.h"

Rect get_box(Display &it, int pos);

void draw_bar(Display &it, int pos, const char *name, float value, BaseFont *icon_font, BaseFont *text_font);