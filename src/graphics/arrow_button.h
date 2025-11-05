#ifndef GRAPHICS_ARROW_BUTTON_H
#define GRAPHICS_ARROW_BUTTON_H

#include "core/time.h"
#include "input/mouse.h"

/**
 * @file arrow_button.h
 * @brief Defines the arrow_button struct and related functions.
 */

/**
 * @brief Represents an arrow button in the UI.
 */
typedef struct {
    short x_offset; /**< The x-offset of the button. */
    short y_offset; /**< The y-offset of the button. */
    short image_id; /**< The ID of the button's image. */
    short size; /**< The size of the button. */
    void (*left_click_handler)(int param1, int param2); /**< The handler for left-click events. */
    int parameter1; /**< The first parameter for the click handler. */
    int parameter2; /**< The second parameter for the click handler. */
    int pressed; /**< A flag indicating if the button is pressed. */
    int repeats; /**< The number of times the click event has been repeated. */
    time_millis last_time; /**< The time of the last click event. */
} arrow_button;

/**
 * @brief Draws a set of arrow buttons.
 * @param x The x-coordinate to draw the buttons at.
 * @param y The y-coordinate to draw the buttons at.
 * @param buttons A pointer to the array of buttons to draw.
 * @param num_buttons The number of buttons to draw.
 */
void arrow_buttons_draw(int x, int y, arrow_button *buttons, unsigned int num_buttons);

/**
 * @brief Handles mouse events for a set of arrow buttons.
 * @param m A pointer to the mouse state.
 * @param x The x-coordinate of the buttons.
 * @param y The y-coordinate of the buttons.
 * @param buttons A pointer to the array of buttons.
 * @param num_buttons The number of buttons.
 * @param focus_button_id A pointer to the ID of the button that has focus.
 * @return 1 if a button was clicked, 0 otherwise.
 */
int arrow_buttons_handle_mouse(
    const mouse *m, int x, int y, arrow_button *buttons, unsigned int num_buttons, unsigned int *focus_button_id);

#endif // GRAPHICS_ARROW_BUTTON_H
