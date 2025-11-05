#include "trade_summary.h"
#include <string.h>

static trade_summary summary;

void trade_summary_init(void)
{
    memset(&summary, 0, sizeof(trade_summary));
}

void trade_summary_process_import(resource_type resource, int quantity, int price)
{
    summary.items[resource].units_imported += quantity;
    summary.items[resource].denarii_imported += price;
}

void trade_summary_process_export(resource_type resource, int quantity, int price)
{
    summary.items[resource].units_exported += quantity;
    summary.items[resource].denarii_exported += price;
}

const trade_summary *trade_summary_get(void)
{
    return &summary;
}

void trade_summary_handle_year_change(void)
{
    trade_summary_init();
}
