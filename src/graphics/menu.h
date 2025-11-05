#ifndef GRAPHICS_MENU_H
#define GRAPHICS_MENU_H

#include "input/mouse.h"

/**
 * @file menu.h
 * @brief Defines menu and menu bar UI elements.
 */

#define TOP_MENU_HEIGHT 24

/**
 * @brief Represents an item in a menu.
 */
typedef struct {
    short text_group; /**< The text group for the item's label. */
    short text_number; /**< The text ID for the item's label. */
    void (*left_click_handler)(int param); /**< The handler for left-click events. */
    int parameter; /**< A parameter for the click handler. */
} menu_item;

/**
 * @brief Represents an item in a menu bar.
 */
typedef struct {
    short text_group; /**< The text group for the item's label. */
    menu_item *items; /**< A pointer to the array of menu items in the dropdown. */
    int num_items; /**< The number of items in the dropdown. */
    short x_start; /**< The starting x-coordinate of the item. */
    short x_end; /**< The ending x-coordinate of the item. */
    int calculated_width_blocks; /**< The calculated width of the item in blocks. */
    int calculated_height_blocks; /**< The calculated height of the item in blocks. */
} menu_bar_item;

/**
 * @brief Draws a menu bar.
 * @param items A pointer to the array of menu bar items.
 * @param num_items The number of items in the menu bar.
 * @param max_width The maximum width of the menu bar.
 * @return The width of the drawn menu bar.
 */
int menu_bar_draw(menu_bar_item *items, int num_items, int max_width);

/**
 * @brief Handles mouse events for a menu bar.
 * @param m A pointer to the mouse state.
 * @param items A pointer to the array of menu bar items.
 * @param num_items The number of items in the menu bar.
 * @param focus_menu_id A pointer to the ID of the menu that has focus.
 * @return The ID of the clicked menu, or 0 if no menu was clicked.
 */
int menu_bar_handle_mouse(const mouse *m, menu_bar_item *items, int num_items, int *focus_menu_id);

/**
 * @brief Draws a menu.
 * @param menu A pointer to the menu to draw.
 * @param focus_item_id The ID of the item that has focus.
 */
void menu_draw(menu_bar_item *menu, int focus_item_id);

/**
 * @brief Handles mouse events for a menu.
 * @param m A pointer to the mouse state.
 * @param menu A pointer to the menu.
 * @param focus_item_id A pointer to the ID of the item that has focus.
 * @return The ID of the clicked item, or 0 if no item was clicked.
 */
int menu_handle_mouse(const mouse *m, menu_bar_item *menu, int *focus_item_id);

/**
 * @brief Updates the text of a menu item.
 * @param menu A pointer to the menu.
 * @param index The index of the item to update.
 * @param text_number The new text ID for the item.
 */
void menu_update_text(menu_bar_item *menu, int index, int text_number);

#endif // GRAPHICS_MENU_H
