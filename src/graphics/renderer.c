#include "renderer.h"

/**
 * @file renderer.c
 * @brief Implementation of the graphics renderer interface.
 */

static const graphics_renderer_interface *renderer;

const graphics_renderer_interface *graphics_renderer(void)
{
    return renderer;
}

void graphics_renderer_set_interface(const graphics_renderer_interface *new_renderer)
{
    renderer = new_renderer;
}
