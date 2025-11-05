#ifndef GRAPHICS_GRAPHICS_H
#define GRAPHICS_GRAPHICS_H

#include "graphics/color.h"

/**
 * @file graphics.h
 * @brief Defines basic graphics rendering functions.
 */

/**
 * @brief Sets the graphics context to a dialog.
 */
void graphics_in_dialog(void);

/**
 * @brief Sets the graphics context to a dialog with a specific size.
 * @param width The width of the dialog.
 * @param height The height of the dialog.
 */
void graphics_in_dialog_with_size(int width, int height);

/**
 * @brief Resets the graphics context from a dialog.
 */
void graphics_reset_dialog(void);

/**
 * @brief Sets the clipping rectangle for rendering.
 * @param x The x-coordinate of the clipping rectangle.
 * @param y The y-coordinate of the clipping rectangle.
 * @param width The width of the clipping rectangle.
 * @param height The height of the clipping rectangle.
 */
void graphics_set_clip_rectangle(int x, int y, int width, int height);

/**
 * @brief Resets the clipping rectangle to the full screen.
 */
void graphics_reset_clip_rectangle(void);

/**
 * @brief Clears the entire screen.
 */
void graphics_clear_screen(void);

/**
 * @brief Draws a line.
 * @param x_start The starting x-coordinate of the line.
 * @param x_end The ending x-coordinate of the line.
 * @param y_start The starting y-coordinate of the line.
 * @param y_end The ending y-coordinate of the line.
 * @param color The color of the line.
 */
void graphics_draw_line(int x_start, int x_end, int y_start, int y_end, color_t color);

/**
 * @brief Draws a rectangle.
 * @param x The x-coordinate of the rectangle.
 * @param y The y-coordinate of the rectangle.
 * @param width The width of the rectangle.
 * @param height The height of the rectangle.
 * @param color The color of the rectangle.
 */
void graphics_draw_rect(int x, int y, int width, int height, color_t color);

/**
 * @brief Draws an inset rectangle.
 * @param x The x-coordinate of the rectangle.
 * @param y The y-coordinate of the rectangle.
 * @param width The width of the rectangle.
 * @param height The height of the rectangle.
 * @param color_dark The dark color of the inset.
 * @param color_light The light color of the inset.
 */
void graphics_draw_inset_rect(int x, int y, int width, int height, color_t color_dark, color_t color_light);

/**
 * @brief Fills a rectangle with a solid color.
 * @param x The x-coordinate of the rectangle.
 * @param y The y-coordinate of the rectangle.
 * @param width The width of the rectangle.
 * @param height The height of the rectangle.
 * @param color The color to fill the rectangle with.
 */
void graphics_fill_rect(int x, int y, int width, int height, color_t color);

/**
 * @brief Shades a rectangle with a given darkness.
 * @param x The x-coordinate of the rectangle.
 * @param y The y-coordinate of the rectangle.
 * @param width The width of the rectangle.
 * @param height The height of the rectangle.
 * @param darkness The darkness to apply to the rectangle.
 */
void graphics_shade_rect(int x, int y, int width, int height, int darkness);

/**
 * @brief Tints a rectangle with a given color and alpha level.
 * @param x The x-coordinate of the rectangle.
 * @param y The y-coordinate of the rectangle.
 * @param width The width of the rectangle.
 * @param height The height of the rectangle.
 * @param rgb The color to tint the rectangle with.
 * @param alpha_level The alpha level to apply to the tint.
 */
void graphics_tint_rect(int x, int y, int width, int height, color_t rgb, int alpha_level);

/**
 * @brief Saves a portion of the screen to an image.
 * @param image_id The ID of the image to save to.
 * @param x The x-coordinate of the portion of the screen to save.
 * @param y The y-coordinate of the portion of the screen to save.
 * @param width The width of the portion of the screen to save.
 * @param height The height of the portion of the screen to save.
 * @return 0 on success, -1 on failure.
 */
int graphics_save_to_image(int image_id, int x, int y, int width, int height);

/**
 * @brief Draws an image to the screen.
 * @param image_id The ID of the image to draw.
 * @param x The x-coordinate to draw the image at.
 * @param y The y-coordinate to draw the image at.
 */
void graphics_draw_from_image(int image_id, int x, int y);

#endif // GRAPHICS_GRAPHICS_H
