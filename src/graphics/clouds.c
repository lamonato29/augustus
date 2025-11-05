#include "clouds.h"

/**
 * @file clouds.c
 * @brief Implementation of the cloud drawing functions.
 */

#include "core/config.h"
#include "core/image.h"
#include "core/random.h"
#include "core/speed.h"
#include "game/settings.h"
#include "graphics/renderer.h"

#include <math.h>
#include <string.h>

#define NUM_CLOUD_ELLIPSES 180
#define CLOUD_ALPHA_INCREASE 16

#define CLOUD_WIDTH 64
#define CLOUD_HEIGHT 64
#define CLOUD_SIZE_RATIO 0.05

#define CLOUD_SCALE 12

#define CLOUD_MIN_CREATION_TIMEOUT 200
#define CLOUD_MAX_CREATION_TIMEOUT 2400

#define CLOUD_ROWS 4
#define CLOUD_COLUMNS 4
#define NUM_CLOUDS (CLOUD_ROWS * CLOUD_COLUMNS)

#define CLOUD_TEXTURE_WIDTH (CLOUD_WIDTH * CLOUD_COLUMNS)
#define CLOUD_TEXTURE_HEIGHT (CLOUD_HEIGHT * CLOUD_ROWS)

#define CLOUD_SPEED 0.3

#define PAUSE_MIN_FRAMES 2

#define PI 3.14159265358979323846

/**
 * @brief An enumeration of cloud statuses.
 */
typedef enum {
    STATUS_INACTIVE, /**< The cloud is inactive and not visible. */
    STATUS_CREATED, /**< The cloud has been created but is not yet moving. */
    STATUS_MOVING /**< The cloud is moving across the screen. */
} cloud_status;

/**
 * @brief Represents an ellipse used to draw a cloud.
 */
typedef struct {
    int x; /**< The x-coordinate of the center of the ellipse. */
    int y; /**< The y-coordinate of the center of the ellipse. */
    int width; /**< The width of the ellipse. */
    int height; /**< The height of the ellipse. */
    int half_width; /**< Half the width of the ellipse. */
    int half_height; /**< Half the height of the ellipse. */
    int radius; /**< The radius of the ellipse. */
    int squared_width; /**< The squared width of the ellipse. */
    int squared_height; /**< The squared height of the ellipse. */
    int width_times_height; /**< The width of the ellipse multiplied by the height. */
} ellipse;

/**
 * @brief Represents a single cloud.
 */
typedef struct {
    image img; /**< The image of the cloud. */
    int x; /**< The x-coordinate of the cloud. */
    int y; /**< The y-coordinate of the cloud. */
    cloud_status status; /**< The status of the cloud. */
    struct {
        speed_type x; /**< The x-speed of the cloud. */
        speed_type y; /**< The y-speed of the cloud. */
    } speed; /**< The speed of the cloud. */
    float scale_x; /**< The x-scale of the cloud. */
    float scale_y; /**< The y-scale of the cloud. */
    int side; /**< The side of the cloud. */
    int angle; /**< The angle of the cloud. */
} cloud_type;

static struct {
    cloud_type clouds[NUM_CLOUDS];
    int movement_timeout;
    int pause_frames;
} data;

/**
 * @brief Generates a random number in a given range.
 * @param min The minimum value.
 * @param range The range.
 * @return A random number in the given range.
 */
static int random_from_min_to_range(int min, int range)
{
    return min + random_between_from_stdlib(0, range);
}

/**
 * @brief Positions an ellipse within a cloud.
 * @param e A pointer to the ellipse to position.
 * @param cloud_width The width of the cloud.
 * @param cloud_height The height of the cloud.
 */
static void position_ellipse(ellipse *e, int cloud_width, int cloud_height)
{
    double angle = random_fractional_from_stdlib() * PI * 2;

    e->x = (int) (CLOUD_WIDTH / 2 + random_fractional_from_stdlib() * cloud_width * cos(angle));
    e->y = (int) (CLOUD_HEIGHT / 2 + random_fractional_from_stdlib() * cloud_height * sin(angle));

    e->width = random_from_min_to_range((int) (CLOUD_WIDTH * CLOUD_SIZE_RATIO), (int) (CLOUD_WIDTH * CLOUD_SIZE_RATIO));
    e->height = random_from_min_to_range((int) (CLOUD_HEIGHT * CLOUD_SIZE_RATIO), (int) (CLOUD_HEIGHT * CLOUD_SIZE_RATIO));

    e->half_width = e->width / 2;
    e->half_height = e->height / 2;
    e->squared_width = e->width * e->width;
    e->squared_height = e->height * e->height;

    e->width_times_height = e->squared_width * e->squared_height;
    e->radius = e->half_width > e->half_height ? e->half_width : e->half_height;
}

/**
 * @brief Checks if an ellipse is inside the bounds of a cloud.
 * @param e A pointer to the ellipse to check.
 * @return 1 if the ellipse is inside the bounds, 0 otherwise.
 */
static int ellipse_is_inside_bounds(const ellipse *e)
{
    int x = e->x;
    int y = e->y;
    return x - e->width >= 0 && x + e->width < CLOUD_WIDTH &&
        y - e->height >= 0 && y + e->height < CLOUD_HEIGHT;
}

/**
 * @brief Darkens a pixel in a cloud.
 * @param cloud A pointer to the cloud's pixel data.
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 */
static void darken_pixel(color_t *cloud, int x, int y)
{
    int pixel = y * CLOUD_WIDTH + x;

    color_t alpha = cloud[pixel] >> COLOR_BITSHIFT_ALPHA;
    int darken = CLOUD_ALPHA_INCREASE >> (alpha >> 4);
    alpha = (alpha + ((darken * (255 - alpha)) >> 8));

    // Clamp
    if (alpha > 255) {
        alpha = 255;
    }

    cloud[pixel] = ALPHA_TRANSPARENT | (alpha << COLOR_BITSHIFT_ALPHA);
}

/**
 * @brief Generates a cloud ellipse.
 * @param cloud A pointer to the cloud's pixel data.
 * @param width The width of the cloud.
 * @param height The height of the cloud.
 */
static void generate_cloud_ellipse(color_t *cloud, int width, int height)
{
    ellipse e;
    do {
        position_ellipse(&e, width, height);
    } while (!ellipse_is_inside_bounds(&e));

    // Do the entire diameter
    for (int x = -e.width; x <= e.width; x++) {
        darken_pixel(cloud, e.x + x, e.y);
    }

    int line_width = e.width;
    int line_delta = 0;

    // Now do all four quarters at the same time, away from the diameter
    for (int y = 1; y <= e.height; y++) {
        int line_limit = line_width - (line_delta - 1);
        int squared_y = y * y;
        while (line_limit) {
            if (line_limit * line_limit * e.squared_height + squared_y * e.squared_width <= e.width_times_height) {
                break;
            }
            line_limit--;
        }
        line_delta = line_width - line_limit;
        line_width = line_limit;

        darken_pixel(cloud, e.x, e.y - y);
        darken_pixel(cloud, e.x, e.y + y);

        for (int x = 1; x <= line_width; x++) {
            darken_pixel(cloud, e.x + x, e.y - y);
            darken_pixel(cloud, e.x + x, e.y + y);
            darken_pixel(cloud, e.x - x, e.y - y);
            darken_pixel(cloud, e.x - x, e.y + y);
        }
    }
}

/**
 * @brief Initializes the cloud images.
 */
static void init_cloud_images(void)
{
    graphics_renderer()->create_custom_image(CUSTOM_IMAGE_CLOUDS, CLOUD_TEXTURE_WIDTH, CLOUD_TEXTURE_HEIGHT, 0);
    for (int i = 0; i < NUM_CLOUDS; i++) {
        cloud_type *cloud = &data.clouds[i];
        image *img = &cloud->img;
        img->width = img->original.width = CLOUD_WIDTH;
        img->height = img->original.height = CLOUD_HEIGHT;
        img->atlas.id = (ATLAS_CUSTOM << IMAGE_ATLAS_BIT_OFFSET) | CUSTOM_IMAGE_CLOUDS;
        img->atlas.x_offset = (i % CLOUD_COLUMNS) * CLOUD_WIDTH;
        img->atlas.y_offset = (i / CLOUD_COLUMNS) * CLOUD_HEIGHT;
        cloud->x = 0;
        cloud->y = 0;
        cloud->side = 0;
        cloud->angle = 0;
        cloud->status = STATUS_INACTIVE;
        speed_clear(&cloud->speed.x);
        speed_clear(&cloud->speed.y);
    }
}

/**
 * @brief Generates a new cloud.
 * @param cloud A pointer to the cloud to generate.
 */
static void generate_cloud(cloud_type *cloud)
{
    if (!graphics_renderer()->has_custom_image(CUSTOM_IMAGE_CLOUDS)) {
        init_cloud_images();
    }

    color_t pixels[CLOUD_WIDTH * CLOUD_HEIGHT];
    memset(pixels, 0, sizeof(color_t) * CLOUD_WIDTH * CLOUD_HEIGHT);

    int width = random_from_min_to_range((int) (CLOUD_WIDTH * 0.15f), (int) (CLOUD_WIDTH * 0.2f));
    int height = random_from_min_to_range((int) (CLOUD_HEIGHT * 0.15f), (int) (CLOUD_HEIGHT * 0.2f));

    for (int i = 0; i < NUM_CLOUD_ELLIPSES; i++) {
        generate_cloud_ellipse(pixels, width, height);
    }

    const image *img = &cloud->img;

    graphics_renderer()->update_custom_image_from(CUSTOM_IMAGE_CLOUDS, pixels,
        img->atlas.x_offset, img->atlas.y_offset, img->width, img->height);

    cloud->x = 0;
    cloud->y = 0;
    cloud->scale_x = (float) ((1.5 - random_fractional_from_stdlib()) / CLOUD_SCALE);
    cloud->scale_y = (float) ((1.5 - random_fractional_from_stdlib()) / CLOUD_SCALE);
    int scaled_width = (int) (CLOUD_WIDTH / cloud->scale_x);
    int scaled_height = (int) (CLOUD_HEIGHT / cloud->scale_y);
    cloud->side = (int) sqrt(scaled_width * scaled_width + scaled_height * scaled_height);
    cloud->angle = random_between_from_stdlib(0, 360);
    cloud->status = STATUS_CREATED;
}

/**
 * @brief Checks if a cloud intersects with any other moving clouds.
 * @param cloud A pointer to the cloud to check.
 * @return 1 if the cloud intersects with another cloud, 0 otherwise.
 */
static int cloud_intersects(const cloud_type *cloud)
{
    for (int i = 0; i < NUM_CLOUDS; i++) {
        const cloud_type *other = &data.clouds[i];
        if (other->status != STATUS_MOVING) {
            continue;
        }
        if (other->x < cloud->x + cloud->side && other->x + other->side > cloud->x &&
            other->y < cloud->y + cloud->side && other->y + other->side > cloud->y) {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Positions a cloud on the screen.
 * @param cloud A pointer to the cloud to position.
 * @param x_limit The x-limit of the screen.
 * @param y_limit The y-limit of the screen.
 */
static void position_cloud(cloud_type *cloud, int x_limit, int y_limit)
{
    int offset_x = random_between_from_stdlib(0, x_limit / 2);

    cloud->x = x_limit - offset_x + cloud->side;
    cloud->y = (y_limit - offset_x) / 2 - cloud->side;

    if (!cloud_intersects(cloud)) {
        cloud->status = STATUS_MOVING;
        speed_clear(&cloud->speed.x);
        speed_clear(&cloud->speed.y);
        data.movement_timeout = random_between_from_stdlib(CLOUD_MIN_CREATION_TIMEOUT, CLOUD_MAX_CREATION_TIMEOUT);
    }
}

void clouds_pause(void)
{
    data.pause_frames = PAUSE_MIN_FRAMES;
}

void clouds_draw(int x_offset, int y_offset, int x_limit, int y_limit, float base_scale)
{
    if (!config_get(CONFIG_UI_DRAW_CLOUD_SHADOWS)) {
        return;
    }

    double cloud_speed = 0;

    if (data.pause_frames) {
        data.pause_frames--;
    } else {
        cloud_speed = CLOUD_SPEED * setting_game_speed() / 100;
    }

    for (int i = 0; i < NUM_CLOUDS; i++) {
        cloud_type *cloud = &data.clouds[i];
        if (cloud->status == STATUS_INACTIVE) {
            generate_cloud(cloud);
            continue;
        } else if (cloud->status == STATUS_CREATED) {
            if (data.movement_timeout > 0) {
                data.movement_timeout--;
            } else {
                position_cloud(cloud, x_limit, y_limit);
            }
            continue;
        } else if (cloud->x < -cloud->side || cloud->y >= y_limit) {
            cloud->status = STATUS_INACTIVE;
            continue;
        }

        speed_set_target(&cloud->speed.x, -cloud_speed, SPEED_CHANGE_IMMEDIATE, 1);
        speed_set_target(&cloud->speed.y, cloud_speed / 2, SPEED_CHANGE_IMMEDIATE, 1);

        graphics_renderer()->draw_image_advanced(&cloud->img,
            (cloud->x - x_offset) / base_scale,
            (cloud->y - y_offset) / base_scale,
            COLOR_MASK_NONE,
            cloud->scale_x * base_scale, cloud->scale_y * base_scale, cloud->angle, 1);

        cloud->x += speed_get_delta(&cloud->speed.x);
        cloud->y += speed_get_delta(&cloud->speed.y);
    }
}
