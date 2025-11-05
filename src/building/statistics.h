#ifndef BUILDING_STATISTICS_H
#define BUILDING_STATISTICS_H

#include "building.h"

void building_init_statistics(building *b);
void building_update_statistics(building *b, int resource, int amount, int is_adding);

#endif // BUILDING_STATISTICS_H
