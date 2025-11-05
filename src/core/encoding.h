#ifndef CORE_ENCODING_H
#define CORE_ENCODING_H

#include "core/locale.h"

#include <stdint.h>

/**
 * @file encoding.h
 * @brief Handles text encoding and conversion.
 */

/**
 * @brief An enumeration of all supported text encodings.
 */
typedef enum {
    ENCODING_WESTERN_EUROPE = 1252, /**< Windows-1252, Western European */
    ENCODING_EASTERN_EUROPE = 1250, /**< Windows-1250, Central and Eastern European */
    ENCODING_CZECH = 12502,
    ENCODING_CYRILLIC = 1251,
    ENCODING_GREEK = 1253,
    ENCODING_TRADITIONAL_CHINESE = 950,
    ENCODING_SIMPLIFIED_CHINESE = 936,
    ENCODING_JAPANESE = 932,
    ENCODING_KOREAN = 949
} encoding_type;

/**
 * @brief Determines the encoding to use based on the game language.
 * @param language The game language.
 * @return The determined encoding.
 */
encoding_type encoding_determine(language_type language);

/**
 * @brief Gets the currently used encoding.
 * @return The current encoding.
 */
encoding_type encoding_get(void);

/**
 * @brief Checks if the current encoding is multi-byte.
 * @return 1 if the encoding is multi-byte, 0 otherwise.
 */
int encoding_is_multibyte(void);

/**
 * @brief Checks if the operating system uses decomposed UTF-8.
 * @return 1 if the system uses decomposed UTF-8, 0 otherwise.
 */
int encoding_system_uses_decomposed(void);

/**
 * @brief Checks if a UTF-8 character can be displayed in the current encoding.
 * @param utf8_char The UTF-8 character to check.
 * @return 1 if the character can be displayed, 0 otherwise.
 */
int encoding_can_display(const char *utf8_char);

/**
 * @brief Converts a string from the current encoding to UTF-8.
 * @param input The input string to convert.
 * @param output The output buffer to store the UTF-8 string.
 * @param output_length The length of the output buffer.
 * @param decompose Whether to decompose Unicode characters.
 */
void encoding_to_utf8(const uint8_t *input, char *output, int output_length, int decompose);

/**
 * @brief Converts a string from UTF-8 to the current encoding.
 * @param input The input UTF-8 string to convert.
 * @param output The output buffer to store the converted string.
 * @param output_length The length of the output buffer.
 */
void encoding_from_utf8(const char *input, uint8_t *output, int output_length);

/**
 * @brief Gets the number of bytes in a UTF-8 character.
 * @param input The first byte of the UTF-8 character.
 * @return The number of bytes in the character.
 */
int encoding_get_utf8_character_bytes(const char input);

/**
 * @brief Converts a string from UTF-16 to UTF-8.
 * @param input The input UTF-16 string to convert.
 * @param output The output buffer to store the UTF-8 string.
 */
void encoding_utf16_to_utf8(const uint16_t *input, char *output);

/**
 * @brief Converts a string from UTF-8 to UTF-16.
 * @param input The input UTF-8 string to convert.
 * @param output The output buffer to store the UTF-16 string.
 */
void encoding_utf8_to_utf16(const char *input, uint16_t *output);

#endif // CORE_ENCODING_H
