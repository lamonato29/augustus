#ifndef GRAPHICS_GENERIC_BUTTON_H
#define GRAPHICS_GENERIC_BUTTON_H

#include "input/mouse.h"

/**
 * @file generic_button.h
 * @brief Defines the generic_button struct and related functions.
 */

/**
 * @brief Represents a generic button with basic properties and click handlers.
 */
typedef struct generic_button {
    short x; /**< The x-coordinate of the button. */
    short y; /**< The y-coordinate of the button. */
    short width; /**< The width of the button. */
    short height; /**< The height of the button. */
    void (*left_click_handler)(const struct generic_button *button); /**< The handler for left-click events. */
    void (*right_click_handler)(const struct generic_button *button); /**< The handler for right-click events. */
    int parameter1; /**< The first parameter for the click handlers. */
    int parameter2; /**< The second parameter for the click handlers. */
} generic_button;

/**
 * @brief Handles mouse events for an array of generic buttons.
 * @param m A pointer to the mouse state.
 * @param x The x-coordinate of the buttons.
 * @param y The y-coordinate of the buttons.
 * @param buttons A pointer to the array of buttons.
 * @param num_buttons The number of buttons.
 * @param focus_button_id A pointer to the ID of the button that has focus.
 * @return The ID of the clicked button, or 0 if no button was clicked.
 */
int generic_buttons_handle_mouse(const mouse *m, int x, int y, generic_button *buttons, unsigned int num_buttons,
    unsigned int *focus_button_id);

#endif // GRAPHICS_GENERIC_BUTTON_H
