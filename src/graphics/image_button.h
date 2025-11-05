#ifndef GRAPHICS_IMAGE_BUTTON_H
#define GRAPHICS_IMAGE_BUTTON_H

#include "graphics/button.h"
#include "input/mouse.h"

#include "core/time.h"

/**
 * @file image_button.h
 * @brief Defines the image_button struct and related functions for creating buttons with images.
 */

/**
 * @brief An enumeration of image button types.
 */
enum {
    IB_NORMAL = 4, /**< A normal button. */
    IB_SCROLL = 6, /**< A scroll button. */
    IB_BUILD = 2 /**< A build button. */
};

/**
 * @brief Represents a button with an image.
 */
typedef struct {
    short x_offset; /**< The x-offset of the button. */
    short y_offset; /**< The y-offset of the button. */
    short width; /**< The width of the button. */
    short height; /**< The height of the button. */
    short button_type; /**< The type of the button. */
    short image_collection; /**< The image collection for the button. */
    short image_offset; /**< The image offset within the collection. */
    void (*left_click_handler)(int param1, int param2); /**< The handler for left-click events. */
    void (*right_click_handler)(int param1, int param2); /**< The handler for right-click events. */
    int parameter1; /**< The first parameter for the click handlers. */
    int parameter2; /**< The second parameter for the click handlers. */
    char enabled; /**< A flag indicating if the button is enabled. */
    const char *assetlist_name; /**< The name of the asset list for Augustus assets. */
    const char *image_name; /**< The name of the image for Augustus assets. */
    char pressed; /**< A flag indicating if the button is pressed. */
    char focused; /**< A flag indicating if the button is focused. */
    time_millis pressed_since; /**< The time since the button was pressed. */
    char dont_draw; /**< A flag indicating if the button should not be drawn. */
    char static_image; /**< A flag indicating if the button has a static image. */
} image_button;

/**
 * @brief Draws an array of image buttons.
 * @param x The x-coordinate to draw the buttons at.
 * @param y The y-coordinate to draw the buttons at.
 * @param buttons A pointer to the array of buttons to draw.
 * @param num_buttons The number of buttons to draw.
 */
void image_buttons_draw(int x, int y, image_button *buttons, unsigned int num_buttons);

/**
 * @brief Handles mouse events for an array of image buttons.
 * @param m A pointer to the mouse state.
 * @param x The x-coordinate of the buttons.
 * @param y The y-coordinate of the buttons.
 * @param buttons A pointer to the array of buttons.
 * @param num_buttons The number of buttons.
 * @param focus_button_id A pointer to the ID of the button that has focus.
 * @return The ID of the clicked button, or 0 if no button was clicked.
 */
int image_buttons_handle_mouse(
    const mouse *m, int x, int y, image_button *buttons, unsigned int num_buttons, unsigned int *focus_button_id);

#endif // GRAPHICS_IMAGE_BUTTON_H
