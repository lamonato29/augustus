#ifndef GRAPHICS_COMPLEX_BUTTON_H
#define GRAPHICS_COMPLEX_BUTTON_H

#include "graphics/tooltip.h"
#include "graphics/image.h"
#include "graphics/lang_text.h"
#include "input/mouse.h"

/**
 * @file complex_button.h
 * @brief Defines the complex_button struct and related functions for creating advanced UI buttons.
 */

#define MAX_COMPLEX_BUTTON_PARAMETERS 10 // arbitrary

/**
 * @brief An enumeration of different visual styles for a complex button.
 */
typedef enum {
    COMPLEX_BUTTON_STYLE_DEFAULT,  /**< Basic style: single rectangle with red border and texture fill. */
    COMPLEX_BUTTON_STYLE_GRAY,     /**< Main-menu-like style. */
} complex_button_style;

/**
 * @brief An enumeration for positioning a sequence of text or images on a button.
 */
typedef enum {
    SEQUENCE_POSITION_TOP_LEFT = 1,      /*         ┌───┬───┬───┐         */
    SEQUENCE_POSITION_TOP_CENTER = 2,    /*         │ 1 │ 2 │ 3 │         */
    SEQUENCE_POSITION_TOP_RIGHT = 3,     /*         ├───┼───┼───┤         */
    SEQUENCE_POSITION_CENTER_LEFT = 4,   /*         │ 4 │ 5 │ 6 │         */
    SEQUENCE_POSITION_CENTER = 5,        /*         ├───┼───┼───┤         */
    SEQUENCE_POSITION_CENTER_RIGHT = 6,  /*         │ 7 │ 8 │ 9 │         */
    SEQUENCE_POSITION_BOTTOM_LEFT = 7,   /*         └───┴───┴───┘         */
    SEQUENCE_POSITION_BOTTOM_CENTER = 8, /*    mirroring phone keypad     */
    SEQUENCE_POSITION_BOTTOM_RIGHT = 9,  /*  OOB values will be centered  */
} sequence_positioning;

/**
 * @brief Represents a complex button with various states and handlers.
 */
typedef struct complex_button {
    short x; /**< The x-coordinate of the button. */
    short y; /**< The y-coordinate of the button. */
    short width; /**< The width of the button. */
    short height; /**< The height of the button. */
    short is_focused; /**< A flag indicating if the button is focused. */
    short is_clicked; /**< A flag indicating if the button is clicked. */
    short is_active;              /**< A flag indicating if the button is active (e.g., toggled, selected). */
    short is_hidden;              /**< A flag indicating if the button is hidden. */
    short is_disabled;            /**< A flag indicating if the button is disabled. */
    short state;                  /**< A special parameter for custom behaviors. */
    void (*left_click_handler)(const struct complex_button *button); /**< The handler for left-click events. */
    void (*right_click_handler)(const struct complex_button *button); /**< The handler for right-click events. */
    void (*hover_handler)(const struct complex_button *button); /**< The handler for hover events. */
    tooltip_context tooltip_c; /**< The tooltip context for the button. */
    const lang_fragment *sequence;     /**< A sequence of text or images to draw on the button. */
    sequence_positioning sequence_position; /**< The position of the sequence on the button. */
    int sequence_size; /**< The size of the sequence. */
    int parameters[MAX_COMPLEX_BUTTON_PARAMETERS]; /**< An array of parameters for the button. */
    int image_before; /**< The ID of an image to draw before the button's text or sequence. */
    int image_after; /**< The ID of an image to draw after the button's text or sequence. */
    complex_button_style style; /**< The visual style of the button. */
    short expanded_hitbox_radius; /**< The radius of an expanded hitbox for the button. */
    void *user_data; /**< A pointer to custom user data. */
} complex_button;

/**
 * @brief Draws a single complex button.
 * @param button A pointer to the button to draw.
 */
void complex_button_draw(const complex_button *button);

/**
 * @brief Draws an array of complex buttons.
 * @param buttons A pointer to the array of buttons to draw.
 * @param num_buttons The number of buttons to draw.
 */
void complex_button_array_draw(const complex_button *buttons, unsigned int num_buttons);

/**
 * @brief Handles mouse events for a single complex button.
 * @param m A pointer to the mouse state.
 * @param btn A pointer to the button.
 * @return 1 if the button was clicked, 0 otherwise.
 */
int complex_button_handle_mouse(const mouse *m, complex_button *btn);

/**
 * @brief Handles mouse events for an array of complex buttons.
 * @param m A pointer to the mouse state.
 * @param buttons A pointer to the array of buttons.
 * @param num_buttons The number of buttons.
 * @return The ID of the clicked button, or 0 if no button was clicked.
 */
int complex_button_array_handle_mouse(const mouse *m, complex_button *buttons, unsigned int num_buttons);

#endif // GRAPHICS_COMPLEX_BUTTON_H
