#ifndef GRAPHICS_PANEL_H
#define GRAPHICS_PANEL_H

/**
 * @file panel.h
 * @brief Defines functions for drawing UI panels and labels.
 */

#define BLOCK_SIZE 16
#define LABEL_TYPE_HOVER 2
#define LABEL_TYPE_NORMAL 1

/**
 * @brief Draws an outer panel.
 * @param x The x-coordinate of the panel.
 * @param y The y-coordinate of the panel.
 * @param width_blocks The width of the panel in blocks.
 * @param height_blocks The height of the panel in blocks.
 */
void outer_panel_draw(int x, int y, int width_blocks, int height_blocks);

/**
 * @brief Draws an inner panel.
 * @param x The x-coordinate of the panel.
 * @param y The y-coordinate of the panel.
 * @param width_blocks The width of the panel in blocks.
 * @param height_blocks The height of the panel in blocks.
 */
void inner_panel_draw(int x, int y, int width_blocks, int height_blocks);

/**
 * @brief Draws an unbordered panel.
 * @param x The x-coordinate of the panel.
 * @param y The y-coordinate of the panel.
 * @param width_blocks The width of the panel in blocks.
 * @param height_blocks The height of the panel in blocks.
 */
void unbordered_panel_draw(int x, int y, int width_blocks, int height_blocks);

/**
 * @brief Draws a label.
 * @param x The x-coordinate of the label.
 * @param y The y-coordinate of the label.
 * @param width_blocks The width of the label in blocks.
 * @param type The type of the label.
 */
void label_draw(int x, int y, int width_blocks, int type);

/**
 * @brief Draws a large label.
 * @param x The x-coordinate of the label.
 * @param y The y-coordinate of the label.
 * @param width_blocks The width of the label in blocks.
 * @param type The type of the label.
 */
void large_label_draw(int x, int y, int width_blocks, int type);

#endif // GRAPHICS_PANEL_H
