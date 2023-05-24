#ifndef EX2_REPO_SORTBUSLINES_H
#define EX2_REPO_SORTBUSLINES_H
// write only between #define EX2_REPO_SORTBUSLINES_H
// and #endif //EX2_REPO_SORTBUSLINES_H

#include <string.h>
#define NAME_LEN 21
/**
 * A structure of a bus with info about it name, distance, and duration
 */
typedef struct BusLine
{
    char name[NAME_LEN];
    int distance, duration;
} BusLine;
typedef enum SortType
{
    DISTANCE,  //0
    DURATION   //1
} SortType;

/**
 * O(n^2) complexity of bubble sort to sort the line by the given parameter
 */
void bubble_sort (BusLine *start, BusLine *end);

/**
 * O(nlog(n) complexity of quicksort to sort the line by the given parameter
 */
void quick_sort (BusLine *start, BusLine *end, SortType sort_type);

/**
 * finding a partition for the recursive quick sort
 */
BusLine *partition (BusLine *start, BusLine *end, SortType sort_type);
// write only between #define EX2_REPO_SORTBUSLINES_H
// and #endif //EX2_REPO_SORTBUSLINES_H
#endif //EX2_REPO_SORTBUSLINES_H
