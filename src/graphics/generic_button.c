#include "generic_button.h"

/**
 * @file generic_button.c
 * @brief Implementation of the generic_button functions.
 */

/**
 * @brief Gets the ID of the button at a given position.
 * @param m A pointer to the mouse state.
 * @param x The x-coordinate of the buttons.
 * @param y The y-coordinate of the buttons.
 * @param buttons A pointer to the array of buttons.
 * @param num_buttons The number of buttons.
 * @return The ID of the button at the given position, or 0 if no button is at the position.
 */
static unsigned int get_button(const mouse *m, int x, int y, generic_button *buttons, unsigned int num_buttons)
{
    for (unsigned int i = 0; i < num_buttons; i++) {
        if (x + buttons[i].x <= m->x &&
            x + buttons[i].x + buttons[i].width > m->x &&
            y + buttons[i].y <= m->y &&
            y + buttons[i].y + buttons[i].height > m->y) {
            return i + 1;
        }
    }
    return 0;
}

int generic_buttons_handle_mouse(const mouse *m, int x, int y, generic_button *buttons, unsigned int num_buttons,
    unsigned int *focus_button_id)
{
    unsigned int button_id = get_button(m, x, y, buttons, num_buttons);
    if (focus_button_id) {
        *focus_button_id = button_id;
    }
    if (!button_id) {
        return 0;
    }
    generic_button *button = &buttons[button_id - 1];
    if (m->left.went_up) {
        if (button->left_click_handler) {
            button->left_click_handler(button);
            return 1;
        } else {
            return 0;
        }
    } else if (m->right.went_up) {
        if (button->right_click_handler) {
            button->right_click_handler(button);
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}
