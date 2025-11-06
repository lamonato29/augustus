
#include "manage_depots.h"

#include "building/building.h"
#include "building/storage.h"
#include "core/array.h"
#include "graphics/color.h"
#include "graphics/generic_button.h"
#include "graphics/panel.h"
#include "graphics/scrollbar.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "widget/dropdown_button.h"
#include "input/input.h"
#include "translation/translation.h"
#include "window/building_info.h"

#define MAX_VISIBLE_DEPOTS 15
#define ROW_HEIGHT 22

typedef struct {
    int building_id;
    resource_type product_id;
    int source_id;
    int destination_id;
} depot_info;

static array(depot_info) depot_list;
static array(depot_info) filtered_depot_list;

static dropdown_button product_filter_dropdown;
static dropdown_button origin_filter_dropdown;
static dropdown_button destination_filter_dropdown;

static int selected_product = 0;
static int selected_origin = 0;
static int selected_destination = 0;

static void on_scroll(void)
{
    window_request_refresh();
}

static scrollbar_type scrollbar = { 580, 50, ROW_HEIGHT * MAX_VISIBLE_DEPOTS, 0, MAX_VISIBLE_DEPOTS, on_scroll, 0, 4 };

static void depot_button_click(const generic_button *button)
{
    window_building_info_show(button->parameter1);
}

static generic_button depot_buttons[MAX_VISIBLE_DEPOTS];

static void init_filters(void);

static void draw_background(void)
{
    outer_panel_draw(0, 0, 40, 30);
    text_draw_centered(translation_for(TR_MANAGE_DEPOTS), 16, 16, 608, FONT_LARGE_BLACK, 0);
    inner_panel_draw(16, 42, 38, 21);
}

static void draw_foreground(void)
{
    scrollbar_draw(&scrollbar);
    dropdown_button_draw(&product_filter_dropdown);
    dropdown_button_draw(&origin_filter_dropdown);
    dropdown_button_draw(&destination_filter_dropdown);

    for (unsigned int i = 0; i < MAX_VISIBLE_DEPOTS && i + scrollbar.scroll_position < filtered_depot_list.size; i++) {
        depot_info *info = array_item(filtered_depot_list, i + scrollbar.scroll_position);
        building *b = building_get(info->building_id);
        building *src = building_get(info->source_id);
        building *dst = building_get(info->destination_id);

        depot_buttons[i].x = 20;
        depot_buttons[i].y = 50 + i * ROW_HEIGHT;
        depot_buttons[i].width = 550;
        depot_buttons[i].height = ROW_HEIGHT;
        depot_buttons[i].left_click_handler = depot_button_click;
        depot_buttons[i].parameter1 = info->building_id;

        button_border_draw(depot_buttons[i].x, depot_buttons[i].y, depot_buttons[i].width, depot_buttons[i].height, 0);

        text_draw((const uint8_t*)building_get_display_name(b), 24, 56 + i * ROW_HEIGHT, FONT_NORMAL_WHITE, 0);
        text_draw(resource_get_data(info->product_id)->text, 200, 56 + i * ROW_HEIGHT, FONT_NORMAL_WHITE, 0);
        text_draw((const uint8_t*)building_get_display_name(src), 300, 56 + i * ROW_HEIGHT, FONT_NORMAL_WHITE, 0);
        text_draw((const uint8_t*)building_get_display_name(dst), 450, 56 + i * ROW_HEIGHT, FONT_NORMAL_WHITE, 0);
    }
}

static void handle_input(const mouse *m, const hotkeys *h)
{
    if (input_go_back_requested(m, h)) {
        window_go_back();
    }

    if (scrollbar_handle_mouse(&scrollbar, m, 1)) {
        return;
    }

    if (dropdown_button_handle_mouse(m, &product_filter_dropdown)) {
        return;
    }
    if (dropdown_button_handle_mouse(m, &origin_filter_dropdown)) {
        return;
    }
    if (dropdown_button_handle_mouse(m, &destination_filter_dropdown)) {
        return;
    }

    generic_buttons_handle_mouse(m, 0, 0, depot_buttons, MAX_VISIBLE_DEPOTS, 0);
}

static void apply_filters(void)
{
    array_clear(filtered_depot_list);
    for (int i = 0; i < depot_list.size; i++) {
        depot_info *info = array_item(depot_list, i);
        if ((selected_product == 0 || info->product_id == selected_product) &&
            (selected_origin == 0 || info->source_id == selected_origin) &&
            (selected_destination == 0 || info->destination_id == selected_destination)) {
            array_add(filtered_depot_list, *info);
        }
    }
    scrollbar_init(&scrollbar, 0, filtered_depot_list.size);
}

static void product_filter_changed(dropdown_button *button)
{
    selected_product = button->buttons[button->selected_index].parameter1;
    apply_filters();
    window_request_refresh();
}

static void origin_filter_changed(dropdown_button *button)
{
    selected_origin = button->buttons[button->selected_index].parameter1;
    apply_filters();
    window_request_refresh();
}

static void destination_filter_changed(dropdown_button *button)
{
    selected_destination = button->buttons[button->selected_index].parameter1;
    apply_filters();
    window_request_refresh();
}

static void init_filters(void)
{
    static lang_fragment product_frags[RESOURCE_MAX];
    static lang_fragment origin_frags[BUILDING_TYPE_MAX * 2];
    static lang_fragment destination_frags[BUILDING_TYPE_MAX * 2];

    product_frags[0].text_id = TR_ALL;
    product_frags[0].parameter1 = 0;
    origin_frags[0].text_id = TR_ALL;
    origin_frags[0].parameter1 = 0;
    destination_frags[0].text_id = TR_ALL;
    destination_frags[0].parameter1 = 0;

    int product_count = 1;
    for (int i = RESOURCE_MIN; i < RESOURCE_MAX; i++) {
        product_frags[product_count].text = resource_get_data(i)->text;
        product_frags[product_count].parameter1 = i;
        product_count++;
    }

    int origin_count = 1;
    for (building *b = building_first_of_type(BUILDING_WAREHOUSE); b; b = b->next_of_type) {
        if (origin_count >= BUILDING_TYPE_MAX * 2) break;
        origin_frags[origin_count].text = (const uint8_t*)building_get_display_name(b);
        origin_frags[origin_count].parameter1 = b->id;
        origin_count++;
    }
    for (building *b = building_first_of_type(BUILDING_GRANARY); b; b = b->next_of_type) {
        if (origin_count >= BUILDING_TYPE_MAX * 2) break;
        origin_frags[origin_count].text = (const uint8_t*)building_get_display_name(b);
        origin_frags[origin_count].parameter1 = b->id;
        origin_count++;
    }

    int destination_count = 1;
    for (building *b = building_first_of_type(BUILDING_WAREHOUSE); b; b = b->next_of_type) {
        if (destination_count >= BUILDING_TYPE_MAX * 2) break;
        destination_frags[destination_count].text = (const uint8_t*)building_get_display_name(b);
        destination_frags[destination_count].parameter1 = b->id;
        destination_count++;
    }
    for (building *b = building_first_of_type(BUILDING_GRANARY); b; b = b->next_of_type) {
        if (destination_count >= BUILDING_TYPE_MAX * 2) break;
        destination_frags[destination_count].text = (const uint8_t*)building_get_display_name(b);
        destination_frags[destination_count].parameter1 = b->id;
        destination_count++;
    }

    dropdown_button_init_simple(20, 20, product_frags, product_count, &product_filter_dropdown);
    product_filter_dropdown.selected_callback = product_filter_changed;
    dropdown_button_init_simple(200, 20, origin_frags, origin_count, &origin_filter_dropdown);
    origin_filter_dropdown.selected_callback = origin_filter_changed;
    dropdown_button_init_simple(400, 20, destination_frags, destination_count, &destination_filter_dropdown);
    destination_filter_dropdown.selected_callback = destination_filter_changed;
}


static void populate_depot_list(void)
{
    array_clear(depot_list);
    for (building *b = building_first_of_type(BUILDING_DEPOT); b; b = b->next_of_type) {
        if (b->state == BUILDING_STATE_IN_USE) {
            depot_info info;
            info.building_id = b->id;
            info.product_id = b->data.depot.current_order.resource_type;
            info.source_id = b->data.depot.current_order.src_storage_id;
            info.destination_id = b->data.depot.current_order.dst_storage_id;
            array_add(depot_list, info);
        }
    }
}

void window_manage_depots_show(void)
{
    static bool filters_initialized = false;
    if (!filters_initialized) {
        init_filters();
        filters_initialized = true;
    }

    populate_depot_list();
    apply_filters();

    window_type window = {
        .draw_background = draw_background,
        .draw_foreground = draw_foreground,
        .handle_input = handle_input,
    };
    window_show(&window);
}
