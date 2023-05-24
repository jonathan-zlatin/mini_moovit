#include "test_bus_lines.h"

int is_sorted_by_distance (BusLine *start, BusLine *end)
{
  BusLine *current = start;
  BusLine *next = start;
  next++;
  while (next != end)
  {
    if ((next)->distance < current->distance)
    {
      return 0;
    }
    current++;
    next++;
  }
  return 1;
}

int is_sorted_by_duration (BusLine *start, BusLine *end)
{
  BusLine *current = start;
  BusLine *next = start;
  next++;
  while (next != end)
  {
    if ((next)->duration < current->duration)
    {
      return 0;
    }
    current++;
    next++;
  }
  return 1;
}

int is_sorted_by_name (BusLine *start, BusLine *end)
{
  BusLine *current = start;
  BusLine *next = start;
  next++;
  while (next != end)
  {
    if (strcmp (next->name, current->name) < 0)
    {
      return 0;
    }
    current++;
    next++;
  }
  return 1;
}

int is_equal (BusLine *start_sorted,
              BusLine *end_sorted, BusLine *start_original,
              BusLine *end_original)
{
  const int sorted_len = (int) (end_sorted - start_sorted);
  const int original_len = (int) (end_original - start_original);
  if (original_len != sorted_len)
  {
    return 0;
  }
  int found_pair_flag = 0;
  for (int i = 0; i < original_len; i++)
  {
    for (int j = 0; j < sorted_len; j++)
    {
      if (strcmp (start_original[i].name, start_sorted[j].name) == 0)
      {
        found_pair_flag = 1;
      }
    }
    if (!found_pair_flag)
    {
      return 0;
    }
    found_pair_flag = 0;
  }
  return 1;
}
