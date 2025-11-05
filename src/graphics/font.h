#ifndef GRAPHICS_FONT_H
#define GRAPHICS_FONT_H

#include "core/encoding.h"

#include <stdint.h>

/**
 * @file font.h
 * @brief Defines font types and functions for text rendering.
 */

/**
 * @brief An enumeration of all available font types.
 */
typedef enum {
    FONT_NORMAL_PLAIN, /**< A plain normal-sized font. */
    FONT_NORMAL_BLACK, /**< A black normal-sized font. */
    FONT_NORMAL_WHITE,
    FONT_NORMAL_RED,
    FONT_LARGE_PLAIN,
    FONT_LARGE_BLACK,
    FONT_LARGE_BROWN,
    FONT_SMALL_PLAIN,
    FONT_NORMAL_GREEN,
    FONT_NORMAL_BROWN,
    FONT_TYPES_MAX
} font_t;

/**
 * @brief Represents the definition of a font, including its properties and callbacks.
 */
typedef struct {
    font_t font; /**< The font type. */
    int image_offset; /**< The offset of the font's image in the image atlas. */
    int multibyte_image_offset; /**< The offset of the font's multibyte image in the image atlas. */
    int space_width; /**< The width of a space character. */
    int letter_spacing; /**< The spacing between letters. */
    int line_height; /**< The height of a line of text. */
    int (*image_y_offset)(uint8_t c, int image_height, int line_height); /**< A function to calculate the y-offset of a character. */
} font_definition;

/**
 * @brief Sets the encoding for font drawing functions.
 * @param encoding The encoding to use.
 */
void font_set_encoding(encoding_type encoding);

/**
 * @brief Gets the font definition for a given font type.
 * @param font The font type.
 * @return A pointer to the font definition.
 */
const font_definition *font_definition_for(font_t font);

/**
 * @brief Checks if a character can be displayed with the current font.
 * @param character A pointer to the character to check.
 * @return 1 if the character can be displayed, 0 otherwise.
 */
int font_can_display(const uint8_t *character);

/**
 * @brief Gets the letter ID for a character in a given font.
 * @param def A pointer to the font definition.
 * @param str A pointer to the character string.
 * @param num_bytes A pointer to an integer to store the number of bytes consumed by the letter.
 * @return The letter ID, or -1 if the character is not a letter.
 */
int font_letter_id(const font_definition *def, const uint8_t *str, int *num_bytes);

#endif // GRAPHICS_FONT_H
