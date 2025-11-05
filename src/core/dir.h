#ifndef CORE_DIR_H
#define CORE_DIR_H

#define ASSETS_DIR_NAME "assets"
#define ASSETS_DIRECTORY "***" ASSETS_DIR_NAME "***"
#define CAMPAIGNS_DIR_NAME "campaigns"
#define CAMPAIGNS_DIRECTORY "***" CAMPAIGNS_DIR_NAME "***"

/**
 * @file dir.h
 * @brief Provides functions for interacting with the file system.
 */

/**
 * @brief An enumeration of localization options.
 */
enum {
    NOT_LOCALIZED = 0, /**< The file is not localized. */
    MAY_BE_LOCALIZED = 1, /**< The file may be localized. */
    MUST_BE_LOCALIZED = 2 /**< The file must be localized. */
};

/**
 * @brief An enumeration of path locations.
 */
enum {
    PATH_LOCATION_ROOT = 0, /**< The root directory of the game. */
    PATH_LOCATION_CONFIG = 1, /**< The configuration directory. */
    PATH_LOCATION_ASSET = 2,
    PATH_LOCATION_SAVEGAME = 3,
    PATH_LOCATION_SCENARIO = 4,
    PATH_LOCATION_CAMPAIGN = 5,
    PATH_LOCATION_SCREENSHOT = 6,
    PATH_LOCATION_COMMUNITY = 7,
    PATH_LOCATION_EDITOR_CUSTOM_EMPIRES = 8,
    PATH_LOCATION_EDITOR_CUSTOM_MESSAGES = 9,
    PATH_LOCATION_EDITOR_CUSTOM_EVENTS = 10,
    PATH_LOCATION_MAX = 11
};

/**
 * @brief Represents a single entry in a directory listing.
 */
typedef struct {
    char *name; /**< The name of the file, encoded in UTF-8. */
    unsigned int modified_time; /**< The last modification time of the file. */
} dir_entry;

/**
 * @brief Represents a listing of files in a directory.
 */
typedef struct {
    dir_entry *files; /**< An array of directory entries. */
    int num_files; /**< The number of files in the listing. */
} dir_listing;

/**
 * @brief Finds all files with a given extension in a directory.
 * @param dir The directory to search in.
 * @param extension The file extension to search for.
 * @return A directory listing of the found files.
 */
const dir_listing *dir_find_files_with_extension(const char *dir, const char *extension);

/**
 * @brief Finds all files with a given extension in a specific location.
 * @param location The location to search in.
 * @param extension The file extension to search for.
 * @return A directory listing of the found files.
 */
const dir_listing *dir_find_files_with_extension_at_location(int location, const char *extension);

/**
 * @brief Appends all files with a given extension to the current directory listing.
 * @param extension The file extension to search for.
 * @return The updated directory listing.
 */
const dir_listing *dir_append_files_with_extension(const char *extension);

/**
 * @brief Finds all subdirectories in a directory.
 * @param dir The directory to search in.
 * @return A directory listing of the found subdirectories.
 */
const dir_listing *dir_find_all_subdirectories(const char *dir);

/**
 * @brief Finds all subdirectories in a specific location.
 * @param location The location to search in.
 * @return A directory listing of the found subdirectories.
 */
const dir_listing *dir_find_all_subdirectories_at_location(int location);

/**
 * @brief Gets the case-sensitive and localized filename of a file.
 * @param filepath The file path to match.
 * @param localizable Whether the file is localizable.
 * @return The corrected file path, or NULL if the file was not found.
 */
const char *dir_get_file(const char *filepath, int localizable);

/**
 * @brief Gets the case-sensitive filename of a file in a specific location.
 * @param filepath The file path to match.
 * @param location The location to search in.
 * @return The corrected file path, or NULL if the file was not found.
 */
const char *dir_get_file_at_location(const char *filepath, int location);

/**
 * @brief Appends a location to a filename.
 * @param filename The filename.
 * @param location The location to append.
 * @return The filename with the location appended.
 */
const char *dir_append_location(const char *filename, int location);

#endif // CORE_DIR_H
