#ifndef TESTBUSLINES_H
#define TESTBUSLINES_H

// and #endif //EX2_REPO_TESTBUSLINES_H
#include "sort_bus_lines.h"

/**
 * checks if all the busses are sorted by distance
 */
int is_sorted_by_distance (BusLine *start, BusLine *end);

/**
 * checks if all the busses are sorted by duration
 */
int is_sorted_by_duration (BusLine *start, BusLine *end);

/**
 * checks if all the busses are sorted by name
 */
int is_sorted_by_name (BusLine *start, BusLine *end);

/**
 * checks if two lists have identical arguments
 */
int is_equal (BusLine *start_sorted,
              BusLine *end_sorted, BusLine *start_original,
              BusLine *end_original);
// and #endif //TESTBUSLINES_H
#endif //TESTBUSLINES_H
