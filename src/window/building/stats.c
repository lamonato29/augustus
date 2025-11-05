#include "stats.h"
#include "building/building.h"
#include "game/resource.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "graphics/panel.h"
#include "graphics/button.h"
#include "graphics/generic_button.h"
#include "input/input.h"
#include "translation/translation.h"
#include <stdio.h>
#include <string.h>

static int building_id;
static window_type stats_window;

static void draw_background(void)
{
    button_border_draw(200, 100, 400, 300, 0);
    text_draw_centered(translation_for(TR_STATISTICS), 200, 110, 400, FONT_NORMAL_BLACK, 0);
}

static void draw_foreground(void)
{
    building *b = building_get(building_id);
    if (!b || !b->stats) {
        return;
    }

    int y = 140;
    for (int i = 0; i < RESOURCE_MAX; i++) {
        if (b->stats->resource_stats[i].in_per_year > 0 || b->stats->resource_stats[i].out_per_year > 0) {
            char buffer[256];
            snprintf(buffer, sizeof(buffer), "%s:", resource_get_data(i)->text);
            text_draw((const uint8_t*)buffer, 210, y, FONT_NORMAL_BLACK, 0);

            snprintf(buffer, sizeof(buffer), "In (year): %d", b->stats->resource_stats[i].in_per_year);
            text_draw((const uint8_t*)buffer, 350, y, FONT_NORMAL_BLACK, 0);

            snprintf(buffer, sizeof(buffer), "Out (year): %d", b->stats->resource_stats[i].out_per_year);
            text_draw((const uint8_t*)buffer, 450, y, FONT_NORMAL_BLACK, 0);

            snprintf(buffer, sizeof(buffer), "In (min): %d", b->stats->resource_stats[i].in_last_minute);
            text_draw((const uint8_t*)buffer, 350, y + 15, FONT_NORMAL_BLACK, 0);

            snprintf(buffer, sizeof(buffer), "Out (min): %d", b->stats->resource_stats[i].out_last_minute);
            text_draw((const uint8_t*)buffer, 450, y + 15, FONT_NORMAL_BLACK, 0);
            y += 35;
        }
    }
}

static void handle_input(const mouse *m, const hotkeys *h)
{
    if (input_go_back_requested(m, h)) {
        window_go_back();
    }
}

void window_building_stats_show(int b_id) {
    building_id = b_id;
    stats_window.draw_background = draw_background;
    stats_window.draw_foreground = draw_foreground;
    stats_window.handle_input = handle_input;
    stats_window.get_tooltip = NULL;
    stats_window.id = WINDOW_BUILDING_STATS;
    window_show(&stats_window);
}
