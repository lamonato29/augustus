#ifndef GRAPHICS_LANG_TEXT_H
#define GRAPHICS_LANG_TEXT_H

#include "graphics/font.h"
#include "graphics/color.h"
#include "translation/translation.h"

/**
 * @file lang_text.h
 * @brief Defines functions for drawing language-specific text.
 */

/**
 * @brief An enumeration of different types of language fragments.
 */
typedef enum {
    LANG_FRAG_LABEL,    /**< A language string. */
    LANG_FRAG_AMOUNT,   /**< A number with an associated language string. */
    LANG_FRAG_NUMBER,   // raw number
    LANG_FRAG_TEXT,     // raw utf-8 string
    LANG_FRAG_SPACE,    /**< A space of a given width. */
} lang_fragment_type;

/**
 * @brief Represents a fragment of text, which can be a string, number, or space.
 */
typedef struct {
    lang_fragment_type type; /**< The type of the fragment. */
    int text_group; /**< The text group for a label or amount. */
    int text_id; /**< The text ID for a label or amount. */
    int number; /**< The number for an amount or raw number. */
    int space_width; /**< The width of a space. */
    const uint8_t *text; /**< A pointer to a raw text string. */
} lang_fragment;

/**
 * @brief Gets the width of a language-specific text string.
 * @param group The text group.
 * @param number The text ID.
 * @param font The font to use.
 * @return The width of the text string.
 */
int lang_text_get_width(int group, int number, font_t font);

/**
 * @brief Draws a language-specific text string.
 * @param group The text group.
 * @param number The text ID.
 * @param x_offset The x-coordinate to draw the text at.
 * @param y_offset The y-coordinate to draw the text at.
 * @param font The font to use.
 * @return The width of the drawn text.
 */
int lang_text_draw(int group, int number, int x_offset, int y_offset, font_t font);

/**
 * @brief Draws a colored language-specific text string.
 * @param group The text group.
 * @param number The text ID.
 * @param x_offset The x-coordinate to draw the text at.
 * @param y_offset The y-coordinate to draw the text at.
 * @param font The font to use.
 * @param color The color of the text.
 * @return The width of the drawn text.
 */
int lang_text_draw_colored(int group, int number, int x_offset, int y_offset, font_t font, color_t color);

/**
 * @brief Draws a centered language-specific text string.
 * @param group The text group.
 * @param number The text ID.
 * @param x_offset The x-coordinate of the bounding box.
 * @param y_offset The y-coordinate of the bounding box.
 * @param box_width The width of the bounding box.
 * @param font The font to use.
 */
void lang_text_draw_centered(int group, int number, int x_offset, int y_offset, int box_width, font_t font);
/**
 * @brief Draws a right-aligned language-specific text string.
 * @param group The text group.
 * @param number The text ID.
 * @param x_offset The x-coordinate of the bounding box.
 * @param y_offset The y-coordinate of the bounding box.
 * @param box_width The width of the bounding box.
 * @param font The font to use.
 */
void lang_text_draw_right_aligned(int group, int number, int x_offset, int y_offset, int box_width, font_t font);

/**
 * @brief Draws a centered and colored language-specific text string.
 * @param group The text group.
 * @param number The text ID.
 * @param x_offset The x-coordinate of the bounding box.
 * @param y_offset The y-coordinate of the bounding box.
 * @param box_width The width of the bounding box.
 * @param font The font to use.
 * @param color The color of the text.
 */
void lang_text_draw_centered_colored(
    int group, int number, int x_offset, int y_offset, int box_width, font_t font, color_t color);

/**
 * @brief Draws an ellipsized language-specific text string.
 * @param group The text group.
 * @param number The text ID.
 * @param x_offset The x-coordinate of the bounding box.
 * @param y_offset The y-coordinate of the bounding box.
 * @param box_width The width of the bounding box.
 * @param font The font to use.
 */
void lang_text_draw_ellipsized(int group, int number, int x_offset, int y_offset, int box_width, font_t font);

/**
 * @brief Gets the width of a language-specific text string with an amount.
 * @param group The text group.
 * @param number The text ID.
 * @param amount The amount to display.
 * @param font The font to use.
 * @return The width of the text string.
 */
int lang_text_get_amount_width(int group, int number, int amount, font_t font);

/**
 * @brief Draws a language-specific text string with an amount.
 * @param group The text group.
 * @param number The text ID.
 * @param amount The amount to display.
 * @param x_offset The x-coordinate to draw the text at.
 * @param y_offset The y-coordinate to draw the text at.
 * @param font The font to use.
 * @return The width of the drawn text.
 */
int lang_text_draw_amount(int group, int number, int amount, int x_offset, int y_offset, font_t font);

/**
 * @brief Draws a centered language-specific text string with an amount.
 * @param group The text group.
 * @param number The text ID.
 * @param amount The amount to display.
 * @param x_offset The x-coordinate of the bounding box.
 * @param y_offset The y-coordinate of the bounding box.
 * @param box_width The width of the bounding box.
 * @param font The font to use.
 * @return The width of the drawn text.
 */
int lang_text_draw_amount_centered(int group, int number, int amount, int x_offset, int y_offset, int box_width,
    font_t font);

/**
 * @brief Draws a colored language-specific text string with an amount.
 * @param group The text group.
 * @param number The text ID.
 * @param amount The amount to display.
 * @param x_offset The x-coordinate to draw the text at.
 * @param y_offset The y-coordinate to draw the text at.
 * @param font The font to use.
 * @param color The color of the text.
 * @return The width of the drawn text.
 */
int lang_text_draw_amount_colored(int group, int number, int amount, int x_offset, int y_offset,
    font_t font, color_t color);

/**
 * @brief Draws a year string.
 * @param year The year to draw.
 * @param x_offset The x-coordinate to draw the text at.
 * @param y_offset The y-coordinate to draw the text at.
 * @param font The font to use.
 * @return The width of the drawn text.
 */
int lang_text_draw_year(int year, int x_offset, int y_offset, font_t font);

/**
 * @brief Draws a month and year string with a maximum width.
 * @param month The month to draw.
 * @param year The year to draw.
 * @param x_offset The x-coordinate of the bounding box.
 * @param y_offset The y-coordinate of the bounding box.
 * @param box_width The maximum width of the text.
 * @param font The font to use.
 * @param color The color of the text.
 */
void lang_text_draw_month_year_max_width(
    int month, int year, int x_offset, int y_offset, int box_width, font_t font, color_t color);

/**
 * @brief Draws a multiline language-specific text string.
 * @param group The text group.
 * @param number The text ID.
 * @param x_offset The x-coordinate of the bounding box.
 * @param y_offset The y-coordinate of the bounding box.
 * @param box_width The width of the bounding box.
 * @param font The font to use.
 * @return The height of the drawn text.
 */
int lang_text_draw_multiline(int group, int number, int x_offset, int y_offset, int box_width, font_t font);

/**
 * @brief Gets the width of a sequence of language fragments.
 * @param seq A pointer to the array of language fragments.
 * @param count The number of fragments in the sequence.
 * @param font The font to use.
 * @return The width of the sequence.
 */
int lang_text_get_sequence_width(const lang_fragment *seq, int count, font_t font);

/**
 * @brief Draws a sequence of language fragments.
 * @param seq A pointer to the array of language fragments.
 * @param count The number of fragments in the sequence.
 * @param x The x-coordinate to draw the sequence at.
 * @param y The y-coordinate to draw the sequence at.
 * @param font The font to use.
 * @param color The color of the text.
 * @return The width of the drawn sequence.
 */
int lang_text_draw_sequence(const lang_fragment *seq, int count, int x, int y, font_t font, color_t color);

/**
 * @brief Draws a centered sequence of language fragments.
 * @param seq A pointer to the array of language fragments.
 * @param count The number of fragments in the sequence.
 * @param x The x-coordinate of the bounding box.
 * @param y The y-coordinate of the bounding box.
 * @param box_width The width of the bounding box.
 * @param font The font to use.
 * @param color The color of the text.
 * @return The width of the drawn sequence.
 */
int lang_text_draw_sequence_centered(const lang_fragment *seq, int count, int x, int y, int box_width, font_t font, color_t color);

#endif // GRAPHICS_LANG_TEXT_H