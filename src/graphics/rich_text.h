#ifndef GRAPHICS_RICH_TEXT_H
#define GRAPHICS_RICH_TEXT_H

#include "graphics/color.h"
#include "graphics/font.h"
#include "input/mouse.h"

/**
 * @file rich_text.h
 * @brief Defines functions for rendering rich text.
 */

/**
 * @brief Initializes the rich text renderer.
 * @param text The text to show.
 * @param x_text X offset for the text
 * @param y_text Y offset for the text
 * @param width_blocks Width of the text in blocks of 16px
 * @param height_blocks Height of the text in blocks of 16px
 * @param adjust_width_on_no_scroll Whether to expand the text area into the scrollbar area
 * @return Width of the text in blocks
 */
int rich_text_init(
    const uint8_t *text, int x_text, int y_text, int width_blocks, int height_blocks, int adjust_width_on_no_scroll);

/**
 * @brief Sets the fonts to use for rendering rich text.
 * @param normal_font The font for normal text.
 * @param heading_font The font for headings.
 * @param link_font The font for links.
 * @param line_spacing The spacing between lines.
 */
void rich_text_set_fonts(font_t normal_font, font_t heading_font, font_t link_font, int line_spacing);

/**
 * @brief Resets the rich text to a specific scroll position.
 * @param scroll_position The scroll position to reset to.
 */
void rich_text_reset(int scroll_position);

/**
 * @brief Updates the rich text.
 */
void rich_text_update(void);

/**
 * @brief Clears the internal links table.
 */
void rich_text_clear_links(void);

/**
 * @brief Gets the ID of a clicked link.
 * @param m A pointer to the mouse state.
 * @return The ID of the clicked link, or -1 if no link was clicked.
 */
int rich_text_get_clicked_link(const mouse *m);

/**
 * @brief Draws rich text.
 * @param text The text to draw.
 * @param x_offset The x-coordinate to draw the text at.
 * @param y_offset The y-coordinate to draw the text at.
 * @param box_width The width of the bounding box.
 * @param height_lines The number of available lines.
 * @param measure_only A flag indicating if the text should only be measured and not drawn.
 * @return The total number of lines required for the text.
 */
int rich_text_draw(const uint8_t *text, int x_offset, int y_offset,
                   int box_width, int height_lines, int measure_only);

/**
 * @brief Parses rich text to obtain an image ID.
 * @param position A pointer to the current position in the text.
 * @param default_image_group The default image group to use if none is specified.
 * @param can_be_filepath A flag indicating if the string can be a filepath.
 * @return The image ID, or 0 if no image was found or if there was an error.
 */
int rich_text_parse_image_id(const uint8_t **position, int default_image_group, int can_be_filepath);

/**
 * @brief Draws colored rich text.
 * @param text The text to draw.
 * @param x_offset The x-coordinate to draw the text at.
 * @param y_offset The y-coordinate to draw the text at.
 * @param box_width The width of the bounding box.
 * @param height_lines The number of available lines.
 * @param color The color of the text.
 * @return The total number of lines required for the text.
 */
int rich_text_draw_colored(const uint8_t *text, int x_offset, int y_offset,
                           int box_width, int height_lines, color_t color);

/**
 * @brief Draws the scrollbar for the rich text.
 */
void rich_text_draw_scrollbar(void);

/**
 * @brief Handles mouse input for the rich text, including the scrollbar and scroll wheel.
 * @param m A pointer to the mouse state.
 * @return 1 if the input was handled, 0 otherwise.
 */
int rich_text_handle_mouse(const mouse *m);

/**
 * @brief Gets the current scroll position in lines.
 * @return The current scroll position.
 */
int rich_text_scroll_position(void);

/**
 * @brief Gets the line height of the rich text.
 * @return The line height.
 */
int rich_text_get_line_height(void);

#endif // GRAPHICS_RICH_TEXT_H
