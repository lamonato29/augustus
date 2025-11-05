#ifndef CORE_ARRAY_H
#define CORE_ARRAY_H

#include <stdlib.h>
#include <string.h>

/**
 * @file array.h
 * @brief A dynamic array implementation using macros.
 */

/**
 * @brief Creates a new array type.
 * @param T The type of the elements to be stored in the array.
 */
#define array(T) \
struct { \
    T **items; /**< A pointer to the array's data. */ \
    unsigned int size; /**< The number of items in the array. */ \
    unsigned int blocks; /**< The number of allocated blocks. */ \
    unsigned int block_offset; /**< The offset to the current block. */ \
    unsigned int bit_offset; /**< The bit offset for block calculation. */ \
    void (*constructor)(T *, unsigned int); /**< A constructor function for new items. */ \
    int (*in_use)(const T *); /**< A function to check if an item is in use. */ \
}

/**
 * @brief Clears the array and frees its memory.
 * @param a The array to clear.
 */
#define array_clear(a) \
( \
    array_free((void **)(a).items, (a).blocks), \
    memset(&(a), 0, sizeof(a)) \
)

/**
 * @brief Initializes a new array.
 * @param a The array to initialize.
 * @param size The number of items to allocate per block.
 * @param new_item_callback A constructor function to be called for each new item.
 * @param in_use_callback A function to check if an item is in use.
 * @return 1 on success, 0 on failure.
 */
#define array_init(a, size, new_item_callback, in_use_callback) \
( \
    array_clear(a), \
    (a).constructor = new_item_callback, \
    (a).in_use = in_use_callback, \
    (a).block_offset = array_next_power_of_two(size) - 1, \
    (a).bit_offset = array_active_bit(array_next_power_of_two(size)), \
    array_create_blocks(a, 1) \
)

/**
 * @brief Creates a new item in the array.
 * @param a The array.
 * @param ptr A pointer to the new item.
 */
#define array_new_item(a, ptr) \
{ \
    ptr = 0; \
    int error = 0; \
    if ((a).in_use) { \
        for (unsigned int array_index = 0; array_index < (a).size; array_index++) { \
            if (!(a).in_use(array_item(a, array_index))) { \
                ptr = array_item(a, array_index); \
                memset(ptr, 0, sizeof(**(a).items)); \
                if ((a).constructor) { \
                    (a).constructor(ptr, array_index); \
                } \
                break; \
            } \
        } \
    } \
    if (!error && !ptr) { \
        ptr = array_advance(a); \
    } \
}

/**
 * @brief Creates a new item in the array after a given index.
 * @param a The array.
 * @param index The index after which to create the new item.
 * @param ptr A pointer to the new item.
 */
#define array_new_item_after_index(a, index, ptr) \
{ \
    ptr = 0; \
    int error = 0; \
    while (index > (a).size) { \
        if (!array_advance(a)) { \
            error = 1; \
            break; \
        } \
    } \
    if (!error && (a).in_use) { \
        for (unsigned int array_index = index; array_index < (a).size; array_index++) { \
            if (!(a).in_use(array_item(a, array_index))) { \
                ptr = array_item(a, array_index); \
                memset(ptr, 0, sizeof(**(a).items)); \
                if ((a).constructor) { \
                    (a).constructor(ptr, array_index); \
                } \
                break; \
            } \
        } \
    } \
    if (!error && !ptr) { \
        ptr = array_advance(a); \
    } \
}

/**
 * @brief Removes an item from the array at a given index.
 * @param a The array.
 * @param index The index of the item to remove.
 */
#define array_remove_item(a, index) \
{ \
    for (unsigned int array_index = index; array_index + 1 < (a).size; array_index++) { \
        memcpy(array_item(a, array_index), array_item(a, array_index + 1), sizeof(**(a).items)); \
        if ((a).constructor && (!(a).in_use || (a).in_use(array_item(a, array_index)))) { \
            (a).constructor(array_item(a, array_index), array_index); \
        } \
    } \
    if (index < (a).size) { \
        memset(array_item(a, (a).size - 1), 0, sizeof(**(a).items)); \
        (a).size--; \
    } \
}

/**
 * @brief Advances the array, creating a new item at the end.
 * @param a The array.
 * @return A pointer to the new item, or 0 on failure.
 */
#define array_advance(a) \
( \
    (a).size >> (a).bit_offset < (a).blocks || \
    array_create_blocks(a, 1) ? \
    array_next(a) : 0 \
)

/**
 * @brief Gets a pointer to the item at the specified position in the array.
 * @param a The array.
 * @param position The index of the item to retrieve.
 * @return A pointer to the item.
 */
#define array_item(a, position) \
( \
    &(a).items[(position) >> (a).bit_offset][(position) & (a).block_offset] \
)

/**
 * @brief Gets a pointer to the first item in the array.
 * @param a The array.
 * @return A pointer to the first item, or NULL if the array is empty.
 */
#define array_first(a) \
    ( (a).size > 0 ? (a).items[0] : 0 )

/**
 * @brief Gets a pointer to the last item in the array.
 * @param a The array.
 * @return A pointer to the last item, or NULL if the array is empty.
 */
#define array_last(a) \
    ( (a).size > 0 ? array_item(a, (a).size - 1) : 0 )

/**
 * @brief Iterates over each item in the array.
 * @param a The array to iterate over.
 * @param item A pointer to the current item in the iteration.
 */
#define array_foreach(a, item) \
    for(unsigned int array_index = 0; array_index < (a).size && ((item) = array_item(a, array_index)) != 0; array_index++)

/**
 * @brief Iterates over each item in the array and calls a callback function.
 * @param a The array to iterate over.
 * @param callback The callback function to call for each item.
 */
#define array_foreach_callback(a, callback) \
    for(unsigned int array_index = 0; array_index < (a).size && array_item(a, array_index) != 0; array_index++) { \
        callback(array_item(a, array_index)); \
    }

/**
 * @brief Trims the array by removing unused items from the end.
 * @param a The array to trim.
 */
#define array_trim(a) \
{ \
    if ((a).size > 1 && (a).in_use) { \
        while ((a).size - 1 && !(a).in_use(array_item(a, (a).size - 1))) { \
            (a).size--; \
        } \
    } \
}

/**
 * @brief Packs the array by removing unused items and making the used items contiguous.
 * @param a The array to pack.
 */
#define array_pack(a) \
{ \
    if ((a).in_use) { \
        unsigned int items_to_move = 0; \
        for (unsigned int array_index = 0; array_index < (a).size; array_index++) { \
            if (!(a).in_use(array_item(a, array_index))) { \
                items_to_move++; \
                continue; \
            } \
            if (!items_to_move) { \
                continue; \
            } \
            unsigned int new_index = array_index - items_to_move; \
            memcpy(array_item(a, new_index), array_item(a, array_index), sizeof(**(a).items)); \
            if ((a).constructor) { \
                (a).constructor(array_item(a, new_index), new_index); \
            } \
        } \
        if (items_to_move) { \
            for (unsigned int array_index = (a).size - items_to_move; array_index < (a).size; array_index++) { \
                memset(array_item(a, array_index), 0, sizeof(**(a).items)); \
            } \
            (a).size -= items_to_move; \
        } \
    } \
}

/**
 * @brief Expands the array to a new size.
 * @param a The array to expand.
 * @param size The new size of the array.
 * @return 1 on success, 0 on failure.
 */
#define array_expand(a, size) \
( \
    array_create_blocks(a, (size) > 0 ? (((size) - 1) >> (a).bit_offset) + 1 - (a).blocks : 0) \
)

/**
 * @brief Gets the next item in the array without checking bounds.
 * @param a The array.
 * @return A pointer to the next item.
 */
#define array_next(a) \
( \
    memset(array_item(a, (a).size), 0, sizeof(**(a).items)), \
    (a).constructor ? (a).constructor(array_item(a, (a).size), (a).size) : (void) 0, \
    (a).size++, \
    array_item(a, (a).size - 1) \
)

/** @private */
#define array_create_blocks(a, num_blocks) \
( \
    array_add_blocks((void ***)&(a).items, &(a).blocks, (a).block_offset + 1, sizeof(**(a).items), num_blocks) \
)

/** @private */
int array_add_blocks(void ***data, unsigned int *blocks, unsigned int items_per_block, unsigned int item_size, unsigned int num_blocks);

/** @private */
void array_free(void **data, unsigned int blocks);

/** @private */
#define array_next_power_of_two_0(v) ((v) - 1)
/** @private */
#define array_next_power_of_two_1(v) (array_next_power_of_two_0(v) | array_next_power_of_two_0(v) >> 1)
/** @private */
#define array_next_power_of_two_2(v) (array_next_power_of_two_1(v) | array_next_power_of_two_1(v) >> 2)
/** @private */
#define array_next_power_of_two_3(v) (array_next_power_of_two_2(v) | array_next_power_of_two_2(v) >> 4)
/** @private */
#define array_next_power_of_two_4(v) (array_next_power_of_two_3(v) | array_next_power_of_two_3(v) >> 8)
/** @private */
#define array_next_power_of_two_5(v) (array_next_power_of_two_4(v) | array_next_power_of_two_4(v) >> 16)
/** @private */
#define array_next_power_of_two(v) (((v) < 1) ? 1 : array_next_power_of_two_5(v) + 1)

/** @private */
#define array_active_bit_1(n) (((n) >= 2) ? 1 : 0)
/** @private */
#define array_active_bit_2(n) (((n) >= 1 << 2) ? (2 + array_active_bit_1((n) >> 2)) : array_active_bit_1(n))
/** @private */
#define array_active_bit_3(n) (((n) >= 1 << 4) ? (4 + array_active_bit_2((n) >> 4)) : array_active_bit_2(n))
/** @private */
#define array_active_bit_4(n) (((n) >= 1 << 8) ? (8 + array_active_bit_3((n) >> 8)) : array_active_bit_3(n))
/** @private */
#define array_active_bit(n)   (((n) >= 1 << 16) ? (16 + array_active_bit_4((n) >> 16)) : array_active_bit_4(n))

#endif // CORE_ARRAY_H
