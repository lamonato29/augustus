#ifndef CITY_TRADE_SUMMARY_H
#define CITY_TRADE_SUMMARY_H

#include "game/resource.h"

typedef struct {
    unsigned int units_imported;
    unsigned int units_exported;
    unsigned int denarii_imported;
    unsigned int denarii_exported;
} trade_summary_item;

typedef struct {
    trade_summary_item items[RESOURCE_MAX];
} trade_summary;

void trade_summary_init(void);
void trade_summary_process_import(resource_type resource, int quantity, int price);
void trade_summary_process_export(resource_type resource, int quantity, int price);
const trade_summary *trade_summary_get(void);

#endif // CITY_TRADE_SUMMARY_H
