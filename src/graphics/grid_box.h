#ifndef GRID_BOX_H
#define GRID_BOX_H

#include "graphics/scrollbar.h"
#include "graphics/tooltip.h"
#include "input/mouse.h"

/**
 * @file grid_box.h
 * @brief Defines a grid box UI element for displaying items in a grid.
 */

/**
 * @brief Represents an item within a grid box.
 */
typedef struct {
    int x; /**< The x-coordinate of the item. */
    int y; /**< The y-coordinate of the item. */
    int width; /**< The width of the item. */
    int height; /**< The height of the item. */
    unsigned int index; /**< The index of the item. */
    unsigned int position; /**< The position of the item in the grid. */
    int is_focused; /**< A flag indicating if the item is focused. */
    struct {
        unsigned int x; /**< The x-coordinate of the mouse relative to the item. */
        unsigned int y; /**< The y-coordinate of the mouse relative to the item. */
    } mouse; /**< The mouse coordinates relative to the item. */
} grid_box_item;

/**
 * @brief Represents a grid box UI element.
 */
typedef struct {
    int x; /**< The x-coordinate of the grid box. */
    int y; /**< The y-coordinate of the grid box. */
    unsigned int width; /**< The width of the grid box. */
    unsigned int height; /**< The height of the grid box. */
    unsigned int item_height; /**< The height of each item in the grid. */
    unsigned int num_columns; /**< The number of columns in the grid. */
    struct {
        int horizontal; /**< The horizontal margin between items. */
        int vertical; /**< The vertical margin between items. */
    } item_margin; /**< The margins between items. */
    int draw_inner_panel; /**< A flag indicating if an inner panel should be drawn. */
    int extend_to_hidden_scrollbar; /**< A flag indicating if the grid should extend to a hidden scrollbar. */
    int decorate_scrollbar; /**< A flag indicating if the scrollbar should be decorated. */
    void (*draw_item)(const grid_box_item *item); /**< A function to draw an item. */
    void (*on_click)(const grid_box_item *item); /**< A function to handle item clicks. */
    void (*handle_tooltip)(const grid_box_item *item, tooltip_context *c); /**< A function to handle tooltips for an item. */
    unsigned int total_items; /**< The total number of items in the grid. */
    grid_box_item focused_item; /**< The currently focused item. */
    scrollbar_type scrollbar; /**< The scrollbar for the grid. */
    int offset_scrollbar_x; /**< The x-offset of the scrollbar. */
    int offset_scrollbar_y; /**< The y-offset of the scrollbar. */
    int refresh_requested; /**< A flag indicating if a refresh is requested. */
} grid_box_type;

/**
 * @brief Initializes a grid box.
 * @param grid_box A pointer to the grid box to initialize.
 * @param total_items The total number of items in the grid.
 */
void grid_box_init(grid_box_type *grid_box, unsigned int total_items);

/**
 * @brief Updates the total number of items in a grid box.
 * @param grid_box A pointer to the grid box to update.
 * @param total_items The new total number of items.
 */
void grid_box_update_total_items(grid_box_type *grid_box, unsigned int total_items);

/**
 * @brief Gets the total number of items in a grid box.
 * @param grid_box A pointer to the grid box.
 * @return The total number of items.
 */
unsigned int grid_box_get_total_items(const grid_box_type *grid_box);

/**
 * @brief Draws a grid box.
 * @param grid_box A pointer to the grid box to draw.
 */
void grid_box_draw(grid_box_type *grid_box);

/**
 * @brief Gets the usable width of a grid box.
 * @param grid_box A pointer to the grid box.
 * @return The usable width of the grid box.
 */
unsigned int get_usable_width(const grid_box_type *grid_box);

/**
 * @brief Sets the bounds of a grid box.
 * @param grid_box A pointer to the grid box.
 * @param new_x The new x-coordinate.
 * @param new_y The new y-coordinate.
 * @param new_width The new width.
 * @param new_height The new height.
 */
void grid_box_set_bounds(grid_box_type *grid_box,
                         int new_x, int new_y,
                         int new_width, int new_height);

/**
 * @brief Sets the offset of the scrollbar in a grid box.
 * @param grid_box A pointer to the grid box.
 * @param offset_scrollbar_x The new x-offset of the scrollbar.
 * @param offset_scrollbar_y The new y-offset of the scrollbar.
 */
void grid_box_set_offset_scrollbar(grid_box_type *grid_box, int offset_scrollbar_x, int offset_scrollbar_y);

/**
 * @brief Handles input for a grid box.
 * @param grid_box A pointer to the grid box.
 * @param m A pointer to the mouse state.
 * @param in_dialog A flag indicating if the grid box is in a dialog.
 * @return 1 if the input was handled, 0 otherwise.
 */
int grid_box_handle_input(grid_box_type *grid_box, const mouse *m, int in_dialog);

/**
 * @brief Handles tooltips for a grid box.
 * @param grid_box A pointer to the grid box.
 * @param c A pointer to the tooltip context.
 */
void grid_box_handle_tooltip(const grid_box_type *grid_box, tooltip_context *c);

/**
 * @brief Shows a specific item in a grid box.
 * @param grid_box A pointer to the grid box.
 * @param index The index of the item to show.
 */
void grid_box_show_index(grid_box_type *grid_box, unsigned int index);

/**
 * @brief Requests a refresh of a grid box.
 * @param grid_box A pointer to the grid box.
 */
void grid_box_request_refresh(grid_box_type *grid_box);

/**
 * @brief Checks if a grid box has a scrollbar.
 * @param grid_box A pointer to the grid box.
 * @return 1 if the grid box has a scrollbar, 0 otherwise.
 */
int grid_box_has_scrollbar(const grid_box_type *grid_box);

/**
 * @brief Gets the scroll position of a grid box.
 * @param grid_box A pointer to the grid box.
 * @return The scroll position of the grid box.
 */
unsigned int grid_box_get_scroll_position(const grid_box_type *grid_box);

#endif // GRID_BOX_H
