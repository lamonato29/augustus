#ifndef CORE_DIRECTION_H
#define CORE_DIRECTION_H

/**
 * @file direction.h
 * @brief Defines the direction types used in the game.
 */

/**
 * @brief An enumeration of all possible directions.
 */
typedef enum {
    DIR_0_TOP = 0, /**< Top direction. */
    DIR_1_TOP_RIGHT = 1, /**< Top-right direction. */
    DIR_2_RIGHT = 2, /**< Right direction. */
    DIR_3_BOTTOM_RIGHT = 3, /**< Bottom-right direction. */
    DIR_4_BOTTOM = 4, /**< Bottom direction. */
    DIR_5_BOTTOM_LEFT = 5, /**< Bottom-left direction. */
    DIR_6_LEFT = 6, /**< Left direction. */
    DIR_7_TOP_LEFT = 7, /**< Top-left direction. */
    DIR_8_NONE = 8, /**< No direction. */
    DIR_FIGURE_AT_DESTINATION = 8, /**< Figure is at its destination. */
    DIR_FIGURE_REROUTE = 9, /**< Figure needs to be rerouted. */
    DIR_FIGURE_LOST = 10, /**< Figure is lost. */
    DIR_FIGURE_ATTACK = 11, /**< Figure is attacking. */
} direction_type;

#endif // CORE_DIRECTION_H
