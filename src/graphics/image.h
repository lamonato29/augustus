#ifndef GRAPHICS_IMAGE_H
#define GRAPHICS_IMAGE_H

#include "core/image.h"
#include "graphics/color.h"
#include "graphics/font.h"

/**
 * @file image.h
 * @brief Defines functions for drawing images.
 */

#define SCALE_NONE 1.0f

/**
 * @brief Draws an image.
 * @param image_id The ID of the image to draw.
 * @param x The x-coordinate to draw the image at.
 * @param y The y-coordinate to draw the image at.
 * @param color The color to tint the image with.
 * @param scale The scale to draw the image at.
 */
void image_draw(int image_id, int x, int y, color_t color, float scale);

/**
 * @brief Draws a silhouette of an image.
 * @param image_id The ID of the image to draw.
 * @param x The x-coordinate to draw the silhouette at.
 * @param y The y-coordinate to draw the silhouette at.
 * @param color The color of the silhouette.
 * @param scale The scale to draw the silhouette at.
 */
void image_draw_silhouette(int image_id, int x, int y, color_t color, float scale);

/**
 * @brief Draws an enemy image.
 * @param image_id The ID of the image to draw.
 * @param x The x-coordinate to draw the image at.
 * @param y The y-coordinate to draw the image at.
 * @param scale The scale to draw the image at.
 */
void image_draw_enemy(int image_id, int x, int y, float scale);

/**
 * @brief Draws an image scaled and centered at a given position.
 * @param image_id The ID of the image to draw.
 * @param x The x-coordinate to center the image at.
 * @param y The y-coordinate to center the image at.
 * @param color The color to tint the image with.
 * @param draw_scale_percent The percentage to scale the image by.
 */
void image_draw_scaled_centered(int image_id, int x, int y, color_t color, int draw_scale_percent);

/**
 * @brief Draws a letter.
 * @param font The font to use.
 * @param letter_id The ID of the letter to draw.
 * @param x The x-coordinate to draw the letter at.
 * @param y The y-coordinate to draw the letter at.
 * @param color The color of the letter.
 * @param scale The scale to draw the letter at.
 */
void image_draw_letter(font_t font, int letter_id, int x, int y, color_t color, float scale);

/**
 * @brief Draws a fullscreen background image.
 * @param image_id The ID of the image to draw.
 */
void image_draw_fullscreen_background(int image_id);

/**
 * @brief Draws a blurred fullscreen image.
 * @param image_id The ID of the image to draw.
 * @param intensity The intensity of the blur.
 */
void image_draw_blurred_fullscreen(int image_id, int intensity);

/**
 * @brief Draws a border using a base image.
 * @param base_image_id The ID of the base image to use for the border.
 * @param x The x-coordinate of the border.
 * @param y The y-coordinate of the border.
 * @param color The color of the border.
 */
void image_draw_border(int base_image_id, int x, int y, color_t color);

/**
 * @brief Draws an isometric footprint.
 * @param image_id The ID of the image to draw.
 * @param x The x-coordinate to draw the footprint at.
 * @param y The y-coordinate to draw the footprint at.
 * @param color_mask The color to mask the footprint with.
 * @param scale The scale to draw the footprint at.
 */
void image_draw_isometric_footprint(int image_id, int x, int y, color_t color_mask, float scale);

/**
 * @brief Draws an isometric footprint from a draw tile.
 * @param image_id The ID of the image to draw.
 * @param x The x-coordinate to draw the footprint at.
 * @param y The y-coordinate to draw the footprint at.
 * @param color_mask The color to mask the footprint with.
 * @param scale The scale to draw the footprint at.
 */
void image_draw_isometric_footprint_from_draw_tile(int image_id, int x, int y, color_t color_mask, float scale);

/**
 * @brief Blends a color with a footprint.
 * @param x The x-coordinate of the footprint.
 * @param y The y-coordinate of the footprint.
 * @param color The color to blend.
 * @param scale The scale of the footprint.
 */
void image_blend_footprint_color(int x, int y, color_t color, float scale);

/**
 * @brief Draws the top of an isometric image.
 * @param image_id The ID of the image to draw.
 * @param x The x-coordinate to draw the image at.
 * @param y The y-coordinate to draw the image at.
 * @param color_mask The color to mask the image with.
 * @param scale The scale to draw the image at.
 */
void image_draw_isometric_top(int image_id, int x, int y, color_t color_mask, float scale);

/**
 * @brief Draws the top of an isometric image from a draw tile.
 * @param image_id The ID of the image to draw.
 * @param x The x-coordinate to draw the image at.
 * @param y The y-coordinate to draw the image at.
 * @param color_mask The color to mask the image with.
 * @param scale The scale to draw the image at.
 */
void image_draw_isometric_top_from_draw_tile(int image_id, int x, int y, color_t color_mask, float scale);

/**
 * @brief Sets and draws the top of an isometric image from a draw tile.
 * @param image_id The ID of the image to draw.
 * @param x The x-coordinate to draw the image at.
 * @param y The y-coordinate to draw the image at.
 * @param color_mask The color to mask the image with.
 * @param scale The scale to draw the image at.
 */
void image_draw_set_isometric_top_from_draw_tile(int image_id, int x, int y, color_t color_mask, float scale);

#endif // GRAPHICS_IMAGE_H
