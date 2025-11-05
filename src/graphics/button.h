#ifndef GRAPHICS_BUTTON_H
#define GRAPHICS_BUTTON_H

/**
 * @file button.h
 * @brief Defines common button-related functions.
 */

/**
 * @brief A no-operation function for buttons that have no action.
 * @param param1 An unused parameter.
 * @param param2 An unused parameter.
 */
void button_none(int param1, int param2);

/**
 * @brief Draws a border around a button.
 * @param x The x-coordinate of the button.
 * @param y The y-coordinate of the button.
 * @param width_pixels The width of the button in pixels.
 * @param height_pixels The height of the button in pixels.
 * @param has_focus A flag indicating if the button has focus.
 */
void button_border_draw(int x, int y, int width_pixels, int height_pixels, int has_focus);

#endif // GRAPHICS_BUTTON_H
