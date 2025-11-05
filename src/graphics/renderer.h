#ifndef GRAPHICS_RENDERER_H
#define GRAPHICS_RENDERER_H

#include "core/image.h"

/**
 * @file renderer.h
 * @brief Defines the interface for the graphics renderer.
 */

/**
 * @brief An enumeration of image atlas types.
 */
typedef enum {
    ATLAS_FIRST, /**< The first atlas type. */
    ATLAS_MAIN = ATLAS_FIRST, /**< The main atlas. */
    ATLAS_ENEMY,
    ATLAS_FONT,
    ATLAS_EXTRA_ASSET,
    ATLAS_UNPACKED_EXTRA_ASSET,
    ATLAS_CUSTOM,
    ATLAS_EXTERNAL, /**< An external atlas. */
    ATLAS_MAX /**< The maximum number of atlas types. */
} atlas_type;

/**
 * @brief An enumeration of custom image types.
 */
typedef enum {
    CUSTOM_IMAGE_NONE, /**< No custom image. */
    CUSTOM_IMAGE_EXTERNAL, /**< An external image. */
    CUSTOM_IMAGE_MINIMAP,
    CUSTOM_IMAGE_VIDEO,
    CUSTOM_IMAGE_EMPIRE_MAP,
    CUSTOM_IMAGE_RED_FOOTPRINT,
    CUSTOM_IMAGE_GREEN_FOOTPRINT,
    CUSTOM_IMAGE_CLOUDS,
    CUSTOM_IMAGE_MAX /**< The maximum number of custom image types. */
} custom_image_type;

/**
 * @brief An enumeration of image filtering modes.
 */
typedef enum {
    IMAGE_FILTER_NEAREST = 0, /**< Nearest-neighbor filtering. */
    IMAGE_FILTER_LINEAR = 1 /**< Linear filtering. */
} image_filter;

/**
 * @brief Represents the data for an image atlas.
 */
typedef struct {
    atlas_type type; /**< The type of the atlas. */
    int num_images; /**< The number of images in the atlas. */
    color_t **buffers; /**< A pointer to the array of image buffers. */
    int *image_widths; /**< A pointer to the array of image widths. */
    int *image_heights; /**< A pointer to the array of image heights. */
} image_atlas_data;

/**
 * @brief Defines the interface for the graphics renderer.
 */
typedef struct {
    /** @brief Clears the screen. */
    void (*clear_screen)(void);

    /** @brief Sets the viewport for rendering. */
    void (*set_viewport)(int x, int y, int width, int height);
    /** @brief Resets the viewport to the full screen. */
    void (*reset_viewport)(void);

    /** @brief Sets the clipping rectangle for rendering. */
    void (*set_clip_rectangle)(int x, int y, int width, int height);
    /** @brief Resets the clipping rectangle. */
    void (*reset_clip_rectangle)(void);

    /** @brief Draws a line. */
    void (*draw_line)(int x_start, int x_end, int y_start, int y_end, color_t color);
    /** @brief Draws a rectangle. */
    void (*draw_rect)(int x_start, int x_end, int y_start, int y_end, color_t color);
    /** @brief Fills a rectangle. */
    void (*fill_rect)(int x_start, int x_end, int y_start, int y_end, color_t color);

    /** @brief Draws an image. */
    void (*draw_image)(const image *img, int x, int y, color_t color, float scale);
    /** @brief Draws an image with advanced options. */
    void (*draw_image_advanced)(const image *img, float x, float y, color_t color,
        float scale_x, float scale_y, double angle, int disable_coord_scaling);
    /** @brief Draws a silhouette of an image. */
    void (*draw_silhouette)(const image *img, int x, int y, color_t color, float scale);

    /** @brief Creates a custom image. */
    void (*create_custom_image)(custom_image_type type, int width, int height, int is_yuv);
    /** @brief Checks if a custom image exists. */
    int (*has_custom_image)(custom_image_type type);
    /** @brief Gets the buffer for a custom image. */
    color_t *(*get_custom_image_buffer)(custom_image_type type, int *actual_texture_width);
    /** @brief Releases the buffer for a custom image. */
    void (*release_custom_image_buffer)(custom_image_type type);
    /** @brief Updates a custom image. */
    void (*update_custom_image)(custom_image_type type);
    /** @brief Updates a custom image from a buffer. */
    void (*update_custom_image_from)(custom_image_type type, const color_t *buffer,
        int x_offset, int y_offset, int width, int height);
    /** @brief Updates a custom YUV image. */
    void (*update_custom_image_yuv)(custom_image_type type, const uint8_t *y_data, int y_width,
        const uint8_t *cb_data, int cb_width, const uint8_t *cr_data, int cr_width);
    /** @brief Draws a custom image. */
    void (*draw_custom_image)(custom_image_type type, int x, int y, float scale, int disable_filtering);
    /** @brief Checks if the renderer supports the YUV image format. */
    int (*supports_yuv_image_format)(void);

    /** @brief Starts the creation of a tooltip. */
    int (*start_tooltip_creation)(int width, int height);
    /** @brief Finishes the creation of a tooltip. */
    void (*finish_tooltip_creation)(void);
    /** @brief Checks if a tooltip exists. */
    int (*has_tooltip)(void);
    /** @brief Sets the position of the tooltip. */
    void (*set_tooltip_position)(int x, int y);
    /** @brief Sets the opacity of the tooltip. */
    void (*set_tooltip_opacity)(int opacity);

    /** @brief Saves a portion of the screen to an image. */
    int (*save_image_from_screen)(int image_id, int x, int y, int width, int height);
    /** @brief Draws an image to the screen. */
    void (*draw_image_to_screen)(int image_id, int x, int y);
    /** @brief Saves a portion of the screen to a buffer. */
    int (*save_screen_buffer)(color_t *pixels, int x, int y, int width, int height, int row_width);

    /** @brief Gets the maximum image size supported by the renderer. */
    void (*get_max_image_size)(int *width, int *height);

    /** @brief Prepares an image atlas. */
    const image_atlas_data *(*prepare_image_atlas)(atlas_type type, int num_images, int last_width, int last_height);
    /** @brief Creates an image atlas. */
    int (*create_image_atlas)(const image_atlas_data *data, int delete_buffers);
    /** @brief Gets an image atlas. */
    const image_atlas_data *(*get_image_atlas)(atlas_type type);
    /** @brief Checks if an image atlas exists. */
    int (*has_image_atlas)(atlas_type type);
    /** @brief Frees an image atlas. */
    void (*free_image_atlas)(atlas_type type);

    /** @brief Loads an unpacked image. */
    void (*load_unpacked_image)(const image *img, const color_t *pixels);
    /** @brief Frees an unpacked image. */
    void (*free_unpacked_image)(const image *img);

    /** @brief Checks if an image should be packed. */
    int (*should_pack_image)(int width, int height);

    /** @brief Updates the scale of the city. */
    void (*update_scale)(int city_scale);
} graphics_renderer_interface;

/**
 * @brief Gets the current graphics renderer interface.
 * @return A pointer to the current graphics renderer interface.
 */
const graphics_renderer_interface *graphics_renderer(void);

/**
 * @brief Sets the graphics renderer interface.
 * @param new_renderer A pointer to the new graphics renderer interface.
 */
void graphics_renderer_set_interface(const graphics_renderer_interface *new_renderer);

#endif // GRAPHICS_RENDERER_H
