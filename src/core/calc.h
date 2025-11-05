#ifndef CORE_CALC_H
#define CORE_CALC_H

#include "core/direction.h"

#include <stdint.h>

/**
 * @file calc.h
 * @brief A collection of mathematical utility functions.
 */

/**
 * @brief Calculates the number of digits in an integer.
 * @param value The integer to inspect.
 * @return The number of digits, including the minus sign if negative.
 */
int calc_digits_in_number(int value);

/**
 * @brief Adjusts a value by a given percentage.
 * @param value The value to adjust.
 * @param percentage The percentage to apply.
 * @return The adjusted value.
 */
int calc_adjust_with_percentage(int value, int percentage);

/**
 * @brief Calculates the percentage of a value in relation to a total.
 * @param value The value.
 * @param total The total amount.
 * @return The calculated percentage.
 */
int calc_percentage(int value, int total);

/**
 * @brief Calculates the nearest multiple of a step that is greater than or equal to a value.
 * @param value The value.
 * @param step The step.
 * @return The nearest multiple of the step.
 */
int calc_value_in_step(int value, int step);

/**
 * @brief Calculates the maximum distance between two points.
 * @param x1 The x-coordinate of the first point.
 * @param y1 The y-coordinate of the first point.
 * @param x2 The x-coordinate of the second point.
 * @param y2 The y-coordinate of the second point.
 * @return The maximum distance.
 */
int calc_maximum_distance(int x1, int y1, int x2, int y2);

/**
 * @brief Calculates the distance between two bounding boxes.
 * @param ax The x-coordinate of the first box.
 * @param ay The y-coordinate of the first box.
 * @param aw The width of the first box.
 * @param ah The height of the first box.
 * @param bx The x-coordinate of the second box.
 * @param by The y-coordinate of the second box.
 * @param bw The width of the second box.
 * @param bh The height of the second box.
 * @return The distance between the two boxes.
 */
int calc_box_distance(int ax, int ay, int aw, int ah, int bx, int by, int bw, int bh);

/**
 * @brief Calculates the general direction from a source to a destination.
 * @param x_from The x-coordinate of the source.
 * @param y_from The y-coordinate of the source.
 * @param x_to The x-coordinate of the destination.
 * @param y_to The y-coordinate of the destination.
 * @return The general direction.
 */
direction_type calc_general_direction(int x_from, int y_from, int x_to, int y_to);

/**
 * @brief Calculates the direction for a missile shooter.
 * @param x_from The x-coordinate of the source.
 * @param y_from The y-coordinate of the source.
 * @param x_to The x-coordinate of the destination.
 * @param y_to The y-coordinate of the destination.
 * @return The direction for the missile shooter.
 */
direction_type calc_missile_shooter_direction(int x_from, int y_from, int x_to, int y_to);

/**
 * @brief Calculates the direction for a missile.
 * @param x_from The x-coordinate of the source.
 * @param y_from The y-coordinate of the source.
 * @param x_to The x-coordinate of the destination.
 * @param y_to The y-coordinate of the destination.
 * @return The direction for the missile.
 */
int calc_missile_direction(int x_from, int y_from, int x_to, int y_to);

/**
 * @brief Clamps a 32-bit integer value between a minimum and maximum.
 * @param value The value to clamp.
 * @param min The minimum value.
 * @param max The maximum value.
 * @return The clamped value.
 */
int32_t calc_bound(int32_t value, int32_t min, int32_t max);

/**
 * @brief Clamps a double-precision floating-point value between a minimum and maximum.
 * @param value The value to clamp.
 * @param min The minimum value.
 * @param max The maximum value.
 * @return The clamped value.
 */
double calc_bound_double(double value, double min, double max);

/**
 * @brief Decrements a value towards zero by a given step.
 * @param value The value to decrement.
 * @param step A pointer to the step value.
 * @return The decremented value.
 */
int calc_absolute_decrement(int value, int *step);


#endif // CORE_CALC_H
