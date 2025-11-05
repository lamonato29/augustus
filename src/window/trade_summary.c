#include "window/trade_summary.h"

#include <stdio.h>
#include <stddef.h>
#include "city/finance.h"
#include "game/game.h"
#include "game/resource.h"
#include "city/trade_summary.h"
#include "graphics/button.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/lang_text.h"
#include "graphics/panel.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "input/input.h"
#include "window/advisors.h"

static void draw_foreground(void)
{
    graphics_in_dialog();
    outer_panel_draw(128, 32, 24, 25);
    lang_text_draw_centered(54, 1, 128, 48, 384, FONT_LARGE_BLACK);

    inner_panel_draw(144, 80, 22, 18);

    // Draw header
    lang_text_draw(54, 2, 250, 85, FONT_NORMAL_BLACK); // Imports
    lang_text_draw(54, 3, 350, 85, FONT_NORMAL_BLACK); // Exports
    lang_text_draw(54, 4, 250, 95, FONT_NORMAL_BLACK); // Units
    lang_text_draw(54, 5, 300, 95, FONT_NORMAL_BLACK); // Denarii
    lang_text_draw(54, 4, 350, 95, FONT_NORMAL_BLACK); // Units
    lang_text_draw(54, 5, 400, 95, FONT_NORMAL_BLACK); // Denarii


    int y = 110;
    const trade_summary* summary = trade_summary_get();
    for (int i = 0; i < RESOURCE_MAX; ++i) {
        const trade_summary_item* entry = &summary->items[i];
        if (entry->units_imported > 0 || entry->units_exported > 0) {
            const resource_data* res = resource_get_data(i);
            if (res) {
              image_draw(res->image.icon, 150, y - 5, COLOR_MASK_NONE, SCALE_NONE);
              text_draw(res->text, 170, y, FONT_NORMAL_BLACK, 0);

              char buffer[64];
              snprintf(buffer, sizeof(buffer), "%d", entry->units_imported);
              text_draw((const uint8_t*)buffer, 250, y, FONT_NORMAL_BLACK, 0);
              text_draw_money(entry->denarii_imported, 300, y, FONT_NORMAL_BLACK);

              snprintf(buffer, sizeof(buffer), "%d", entry->units_exported);
              text_draw((const uint8_t*)buffer, 350, y, FONT_NORMAL_BLACK, 0);
              text_draw_money(entry->denarii_exported, 400, y, FONT_NORMAL_BLACK);

              y += 15;
            }
        }
    }
    graphics_reset_dialog();
}

static void handle_input(const mouse *m, const hotkeys *h)
{
    if (input_go_back_requested(m, h)) {
        window_advisors_show();
    }
}

void window_trade_summary_show(void)
{
    window_type window = {
        WINDOW_TRADE_SUMMARY,
        window_advisors_draw_dialog_background,
        draw_foreground,
        handle_input,
    };
    window_show(&window);
}
