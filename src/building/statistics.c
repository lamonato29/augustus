#include "building.h"
#include "core/time.h"
#include "game/time.h"
#include <stdlib.h>
#include <string.h>

void building_init_statistics(building *b) {
    if (b->stats == NULL) {
        b->stats = calloc(1, sizeof(building_statistics));
    }
    b->stats->last_minute_update = time_get_millis();
    b->stats->year_of_stats = game_time_year();
    memset(b->stats->resource_stats, 0, sizeof(b->stats->resource_stats));
}

void building_update_statistics(building *b, int resource, int amount, int is_adding) {
    if (b->stats == NULL) {
        building_init_statistics(b);
    }

    // Update yearly stats
    if (game_time_year() != b->stats->year_of_stats) {
        b->stats->year_of_stats = game_time_year();
        for (int i = 0; i < RESOURCE_MAX; i++) {
            b->stats->resource_stats[i].in_per_year = 0;
            b->stats->resource_stats[i].out_per_year = 0;
        }
    }

    if (is_adding) {
        b->stats->resource_stats[resource].in_per_year += amount;
        b->stats->resource_stats[resource].in_this_minute += amount;
    } else {
        b->stats->resource_stats[resource].out_per_year += amount;
        b->stats->resource_stats[resource].out_this_minute += amount;
    }

    // Update per-minute stats
    time_millis now = time_get_millis();
    if (now - b->stats->last_minute_update >= 60000) { // 60 seconds
        for (int i = 0; i < RESOURCE_MAX; i++) {
            b->stats->resource_stats[i].in_last_minute = b->stats->resource_stats[i].in_this_minute;
            b->stats->resource_stats[i].out_last_minute = b->stats->resource_stats[i].out_this_minute;
            b->stats->resource_stats[i].in_this_minute = 0;
            b->stats->resource_stats[i].out_this_minute = 0;
        }
        b->stats->last_minute_update = now;
    }
}
