#ifndef GRAPHICS_CLOUDS_H
#define GRAPHICS_CLOUDS_H

/**
 * @file clouds.h
 * @brief Functions for drawing clouds.
 */

/**
 * @brief Pauses the cloud animation.
 */
void clouds_pause(void);

/**
 * @brief Draws the clouds.
 * @param x_offset The x-offset of the clouds.
 * @param y_offset The y-offset of the clouds.
 * @param x_limit The x-limit of the screen.
 * @param y_limit The y-limit of the screen.
 * @param base_scale The base scale of the clouds.
 */
void clouds_draw(int x_offset, int y_offset, int x_limit, int y_limit, float base_scale);

#endif // GRAPHICS_CLOUDS_H
