#include "sort_bus_lines.h"

void swap (BusLine *uno, BusLine *dos)
{
  char temp;
  char *p1 = uno->name;
  char *p2 = dos->name;

  // swapping the names of uno and dos
  while (*p1 != '\0' || *p2 != '\0')
  {
    temp = *p1;
    *p1++ = *p2;
    *p2++ = temp;
  }

  //swap the distance and duration fields
  int temp_distance = dos->distance;
  dos->distance = uno->distance;
  uno->distance = temp_distance;

  int temp_duration = dos->duration;
  dos->duration = uno->duration;
  uno->duration = temp_duration;
}

void bubble_sort (BusLine *start, BusLine *end)
{
  int list_len = (int) (end - start);
  for (int i = 0; i < list_len - 1; i++)
  {
    for (BusLine *j = start; j < end - i - 1; j++)
    {
      BusLine *next = j + 1;
      if (strcmp (j->name, next->name) > 0)
      {
        swap (j, next);
      }
    }
  }
}

BusLine *partition (BusLine *start, BusLine *end, SortType sort_type)
{
  int pivot = 0; //verify
  BusLine *high = end;
  high--;
  BusLine *low = start;
  if (!sort_type)
  {
    pivot = (high)->distance;
  }
  else
  {
    pivot = (high)->duration;
  }
  BusLine *i_smaller_c = low;
  i_smaller_c--;
  BusLine *high_minus_one = high;
  high_minus_one--;
  for (BusLine *j = low; j <= high_minus_one; j++)
  {
    if (sort_type == DISTANCE) //distance
    {
      if (j->distance < pivot)
      {
        i_smaller_c++;
        swap (i_smaller_c, j);
      }
    }
    else   //duration
    {
      if (j->duration < pivot)
      {
        i_smaller_c++;
        swap (i_smaller_c, j);
      }
    }
  }
  BusLine *i_temp = i_smaller_c;
  i_temp++;
  swap ((i_temp), high);
  return i_temp;
}

void quick_sort (BusLine *start, BusLine *end, SortType sort_type)
{
  BusLine *high = end;
  high--;
  if (start < high)
  {
    BusLine *pi = partition (start, end, sort_type);

    BusLine *pi_plus_one = pi;
    pi_plus_one++;
    quick_sort (start, pi, sort_type);
    quick_sort (pi_plus_one, end, sort_type);
  }
}
