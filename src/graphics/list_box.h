#ifndef LIST_BOX_H
#define LIST_BOX_H

#include "graphics/scrollbar.h"
#include "graphics/tooltip.h"
#include "input/mouse.h"

/**
 * @file list_box.h
 * @brief Defines a list box UI element for displaying a scrollable list of items.
 */

#define LIST_BOX_NO_SELECTION ((unsigned int) -1)

/**
 * @brief Represents an item within a list box.
 */
typedef struct {
    int x; /**< The x-coordinate of the item. */
    int y; /**< The y-coordinate of the item. */
    int width; /**< The width of the item. */
    int height; /**< The height of the item. */
    unsigned int index; /**< The index of the item. */
    unsigned int position; /**< The position of the item in the list. */
    int is_selected; /**< A flag indicating if the item is selected. */
    int is_focused; /**< A flag indicating if the item is focused. */
} list_box_item;

/**
 * @brief Represents a list box UI element.
 */
typedef struct {
    int x; /**< The x-coordinate of the list box. */
    int y; /**< The y-coordinate of the list box. */
    unsigned int width_blocks; /**< The width of the list box in blocks. */
    unsigned int height_blocks; /**< The height of the list box in blocks. */
    unsigned int item_height; /**< The height of each item in the list. */
    int draw_inner_panel; /**< A flag indicating if an inner panel should be drawn. */
    int extend_to_hidden_scrollbar; /**< A flag indicating if the list should extend to a hidden scrollbar. */
    int decorate_scrollbar; /**< A flag indicating if the scrollbar should be decorated. */
    void (*draw_item)(const list_box_item *item); /**< A function to draw an item. */
    void (*on_select)(unsigned int index, int is_double_click); /**< A function to handle item selection. */
    void (*handle_tooltip)(const list_box_item *item, tooltip_context *c); /**< A function to handle tooltips for an item. */
    unsigned int total_items; /**< The total number of items in the list. */
    unsigned int selected_index; /**< The index of the currently selected item. */
    unsigned int focus_button_id; /**< The ID of the button that has focus. */
    scrollbar_type scrollbar; /**< The scrollbar for the list. */
    int refresh_requested; /**< A flag indicating if a refresh is requested. */
} list_box_type;

/**
 * @brief Initializes a list box.
 * @param list_box A pointer to the list box to initialize.
 * @param total_items The total number of items in the list.
 */
void list_box_init(list_box_type *list_box, unsigned int total_items);

/**
 * @brief Updates the total number of items in a list box.
 * @param list_box A pointer to the list box to update.
 * @param total_items The new total number of items.
 */
void list_box_update_total_items(list_box_type *list_box, unsigned int total_items);

/**
 * @brief Gets the total number of items in a list box.
 * @param list_box A pointer to the list box.
 * @return The total number of items.
 */
unsigned int list_box_get_total_items(const list_box_type *list_box);

/**
 * @brief Draws a list box.
 * @param list_box A pointer to the list box to draw.
 */
void list_box_draw(list_box_type *list_box);

/**
 * @brief Handles input for a list box.
 * @param list_box A pointer to the list box.
 * @param m A pointer to the mouse state.
 * @param in_dialog A flag indicating if the list box is in a dialog.
 * @return 1 if the input was handled, 0 otherwise.
 */
int list_box_handle_input(list_box_type *list_box, const mouse *m, int in_dialog);

/**
 * @brief Handles tooltips for a list box.
 * @param list_box A pointer to the list box.
 * @param c A pointer to the tooltip context.
 */
void list_box_handle_tooltip(const list_box_type *list_box, tooltip_context *c);

/**
 * @brief Shows a specific item in a list box.
 * @param list_box A pointer to the list box.
 * @param index The index of the item to show.
 */
void list_box_show_index(list_box_type *list_box, unsigned int index);

/**
 * @brief Shows the selected item in a list box.
 * @param list_box A pointer to the list box.
 */
void list_box_show_selected_index(list_box_type *list_box);

/**
 * @brief Selects an item in a list box.
 * @param list_box A pointer to the list box.
 * @param index The index of the item to select.
 */
void list_box_select_index(list_box_type *list_box, unsigned int index);

/**
 * @brief Gets the index of the selected item in a list box.
 * @param list_box A pointer to the list box.
 * @return The index of the selected item.
 */
unsigned int list_box_get_selected_index(const list_box_type *list_box);

/**
 * @brief Requests a refresh of a list box.
 * @param list_box A pointer to the list box.
 */
void list_box_request_refresh(list_box_type *list_box);

/**
 * @brief Gets the scroll position of a list box.
 * @param list_box A pointer to the list box.
 * @return The scroll position of the list box.
 */
int list_box_get_scroll_position(const list_box_type *list_box);

#endif // LIST_BOX_H
