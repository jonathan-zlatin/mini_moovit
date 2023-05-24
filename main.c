#include "sort_bus_lines.h"
#include "test_bus_lines.h"
#include "stdio.h"
#include "stdlib.h"

#define DIGITS_DOWN_LIMIT 48
#define DIGITS_UP_LIMIT 57
#define AMOUNT_OF_SENTENCES 8
#define MAX_IN_SENTENCE 1000
#define ARGS_AMOUNT 2
#define DISTANCE_UP 1000
#define BASE 10
#define DURATION_DOWN 10
#define DURATION_UP 100
#define MAX_LINE_INPUT 60
#define MAX_TAB_INPUT 20
#define MIN_LINES 1
#define MAX_LINES 1000
#define TEST1 1
#define TEST2 2
#define TEST3 3
#define TEST4 4
#define TEST5 5
#define TEST6 6

/**
 * A program that sorts bus lines.
 */

char error_list[AMOUNT_OF_SENTENCES][MAX_IN_SENTENCE] = {
    "ERROR: lines number should be an integer only\n",
    "ERROR: line name should include only small english letters or digits\n",
    "ERROR: distance should be integer in [0-1000] range\n",
    "ERROR: duration should be integer in [10-100] range\n",
    "USAGE: The args amount should be 1\n",
    "USAGE: The args must be one of the 4 options\n",
    "ERROR: Sscanf failed, the args weren't correct\n",
    "ERROR: The input is to long\n"
};

enum Messages
{
    INVALID_LINES_NUMBER,
    INVALID_LINE_NAME,
    INVALID_DISTANCE,
    INVALID_DURATION,
    INVALID_ARGS_AMOUNT,
    INVALID_ARGS,
    INVALID_SSCANF,
    BUFFER_OVERFLOW
};

int is_dig(const char dig[])
{
    int i = 0;
    if (dig[0] == '\0') // check if empty
    {
        return 1;
    }
    while (dig[i] != '\0')
    {
        if (dig[i] < DIGITS_DOWN_LIMIT || dig[i] > DIGITS_UP_LIMIT)
        {
            return 1;
        }
        i++;
    }
    return 0;
}


int check_numbers_of_lines_validity (const char number[])
{
  if (is_dig (number))
  {
    printf ("%s", error_list[INVALID_LINES_NUMBER]);
    return 1;
  }
  return 0;
}

int check_line_name_validity (const char line_name[])
{
  int i = 0;
  while (line_name[i] != '\0') // check positive
  {
    if (!(
        (line_name[i] >= DIGITS_DOWN_LIMIT && line_name[i] <= DIGITS_UP_LIMIT)
        || (line_name[i] >= 'a' && line_name[i] <= 'z'))
        || strlen(line_name)==0)
    { //check the number validity (also checks if the number isn't integer)
      printf ("%s", error_list[INVALID_LINE_NAME]);
      return 1;
    }
    i++;
  }
  return 0;
}

int check_duration_validity (const char duration[])
{
  if (is_dig (duration))
  {
    printf ("%s", error_list[INVALID_DURATION]);
    return 1;
  }
  int temp_dur = (int) strtol (duration, NULL, BASE);
  if (temp_dur > DURATION_UP || temp_dur < DURATION_DOWN)
  {
    printf ("%s", error_list[INVALID_DURATION]);
    return 1;
  }
  return 0;
}
int check_distance_validity (const char distance[])
{
  if (is_dig (distance))
  {
    printf ("%s", error_list[INVALID_DISTANCE]);
    return 1;
  }
  int temp_dis = (int) strtol (distance, NULL, BASE);
  if (temp_dis > DISTANCE_UP || temp_dis < 0)
  {
    printf ("%s", error_list[INVALID_DISTANCE]);
    return 1;
  }
  return 0;
}

int check_for_invalid_bus_info (const char name[],
                            const char distance[], const char duration[])
{
  if (check_line_name_validity (name) || check_distance_validity (distance)
      || check_duration_validity (duration))
  {
    return 1;
  }
  return 0;
}
int check_args_valid (int argc, char *argv[])
{
  if (argc != ARGS_AMOUNT)
  {
    printf ("%s", error_list[INVALID_ARGS_AMOUNT]);
  }
  if (strcmp (argv[1], "test") == 0
      || strcmp (argv[1], "by_name") == 0
      || strcmp (argv[1], "by_duration") == 0
      || strcmp (argv[1], "by_distance") == 0)
  {
    return 0; // the argument is one of the above
  }

  printf ("%s", error_list[INVALID_ARGS]);
  return 1;
}
int get_number_of_lines ()
{
  char input[MAX_LINE_INPUT];
  char number_of_lines_st[MAX_TAB_INPUT];
  int sscanf_fail = 0;
  long int number_of_lines = 0;

  printf ("Enter number of lines. Then enter\n");
  fgets (input, sizeof (input), stdin);

  // Check for input buffer overflow
  if (input[strlen (input) - 1] != '\n')
  {
    printf ("%s", error_list[BUFFER_OVERFLOW]);
    sscanf_fail = 1;
  }

  if (sscanf (input, "%s", number_of_lines_st) != 1)
  {
    printf ("%s", error_list[INVALID_SSCANF]);
    sscanf_fail = 1;
  }

  while (check_numbers_of_lines_validity (number_of_lines_st) || sscanf_fail)
  {
    sscanf_fail = 0;
    printf ("Enter number of lines. Then enter\n");
    fgets (input, sizeof (input), stdin);

    if (input[strlen (input) - 1] != '\n')
    {
      printf ("%s", error_list[BUFFER_OVERFLOW]);
      sscanf_fail = 1;
    }

    if (sscanf (input, "%s", number_of_lines_st) != 1)
    {
      printf ("%s", error_list[INVALID_SSCANF]);
      sscanf_fail = 1;
    }
    number_of_lines = (int) strtol
        (number_of_lines_st, NULL, BASE);
    if (number_of_lines < MIN_LINES || number_of_lines > MAX_LINES)
    {
      printf ("Error: number of lines must be between %d and %d\n",
              MIN_LINES, MAX_LINES);
      sscanf_fail = 1;
    }
  }
  return (int) strtol (number_of_lines_st, NULL, BASE);
}

BusLine *build_bus_list (int number_of_lines_in)
{
  BusLine *bus_list = calloc (number_of_lines_in,sizeof (BusLine));
    if (bus_list == NULL)
    {
        printf ("ERROR: couldn't allocate space for the bus list");
        return NULL;
    }
  char input[MAX_LINE_INPUT];
  char line_name[MAX_TAB_INPUT];
  char distance_st[MAX_TAB_INPUT];
  char duration_st[MAX_TAB_INPUT];

  for (int i = 0; i < number_of_lines_in; i++)
  {
    int sscanf_fail = 0;
    printf ("Enter line info. Then enter\n");
    fgets (input, sizeof (input), stdin);
    if (sscanf (input, "%[^,],%[^,],%s", line_name,
                distance_st, duration_st)!= 3)
    {
      sscanf_fail = 1;
    }
    while (check_for_invalid_bus_info
    (line_name,distance_st,duration_st) || sscanf_fail)
    {
      sscanf_fail = 0;
      printf ("Enter line info. Then enter\n");
      fgets (input, sizeof (input), stdin);
      if (sscanf (input, "%[^,],%[^,],%s",
                  line_name, distance_st, duration_st)!= 3)
      {
        sscanf_fail = 1;
      }
    }
    int distance_in = (int) strtol (distance_st, NULL, BASE);
    int duration_in = (int) strtol (duration_st, NULL, BASE);
    strcpy(bus_list[i].name, line_name);
    bus_list[i].distance = distance_in;
    bus_list[i].duration = duration_in;
  }
  return bus_list;
}

void bubble_sort_helper (BusLine *start, BusLine *end)
{
  bubble_sort (start, end);
  BusLine *temp = start;
  while (temp!=end)
  {
    printf ("%s,", temp->name);
    printf ("%d,", temp->distance);
    printf ("%d\n", temp->duration);
    temp++;
  }
}

SortType find_type (char *sort_type)
{
  if (strcmp (sort_type, "by_distance") == 0)
  {
    return DISTANCE;
  }
  return DURATION;
}

void quick_sort_helper (BusLine *start, BusLine *end, SortType sort_type)
{
  quick_sort (start, end, sort_type);
  BusLine *temp = start;
  while (temp!=end) // verify
  {
    printf ("%s,", temp->name);
    printf ("%d,", temp->distance);
    printf ("%d\n", temp->duration);
    temp++;
  }
}
int test_distance (BusLine *start, BusLine *end)
{
// make a copy
  const int list_len = (int) (end - start);
  BusLine *sort_start = malloc (sizeof (BusLine) * list_len);
  if (sort_start == NULL)
  {
    printf ("ERROR: couldn't allocate enough space for a copy busline");
    return 1;
  }
  BusLine *sort_temp = sort_start;
  BusLine *temp = start;
  while (temp != end)
  {
    sort_temp->distance = temp->distance;
    sort_temp->duration = temp->duration;
    memcpy(sort_temp, temp->name, strlen (temp->name) + 1);
    temp++;
    sort_temp++;
  }
  BusLine *sort_end = sort_temp;
  quick_sort (sort_start, sort_end, DISTANCE);
  int a = is_sorted_by_distance (sort_start, sort_end);
  int b = is_equal (sort_start, sort_end, start, end);
  if (a)
  {
    printf ("%s %d %s", "TEST", TEST1, "PASSED: Sorted by distance\n");
  }
  else
  {
    printf ("%s %d %s", "TEST", TEST1, "FAILED: Not sorted by distance\n");
  }
  if (b)
  {
    printf ("%s %d %s", "TEST", TEST2, "PASSED: Lists are equal\n");
  }
  else
  {
    printf ("%s %d %s", "TEST", TEST2, "FAILED: Lists aren't equal\n");
  }
  free (sort_start);
    return 0;
}

int test_duration (BusLine *start, BusLine *end)
{
// make a copy
  const int list_len = (int) (end - start);
  BusLine *sort_start = malloc (sizeof (BusLine) * list_len);
  if (sort_start == NULL)
  {
    printf ("ERROR: couldn't allocate enough space for a copy busline");
    return 1;
  }
  BusLine *sort_temp = sort_start;
  BusLine *temp = start;
  while (temp != end)
  {
    sort_temp->distance = temp->distance;
    sort_temp->duration = temp->duration;
    memcpy(sort_temp, temp->name, strlen (temp->name) + 1);
    temp++;
    sort_temp++;
  }
  BusLine *sort_end = sort_temp;
  quick_sort (sort_start, sort_end, DURATION);
  int c = is_sorted_by_duration (sort_start, sort_end);
  int d = is_equal (sort_start, sort_end, start, end);
  if (c)
  {
    printf ("%s %d %s", "TEST", TEST3, "PASSED: Sort by duration\n");
  }
  else
  {
    printf ("%s %d %s", "TEST", TEST3, "FAILED: Not sorted by duration\n");
  }
  if (d)
  {
    printf ("%s %d %s", "TEST", TEST4, "PASSED: Lists are equal\n");
  }
  else
  {
    printf ("%s %d %s", "TEST", TEST4, "FAILED: Lists aren't equal\n");
  }
  free (sort_start);
  return 0;
}

int test_name (BusLine *start, BusLine *end)
{
// make a copy
  const int list_len = (int) (end - start);
  BusLine *sort_start = malloc (sizeof (BusLine) * list_len);
  if (sort_start == NULL)
  {
    printf ("ERROR: couldn't allocate enough space for a copy busline");
    return 1;
  }
  BusLine *sort_temp = sort_start;
  BusLine *temp = start;
  while (temp != end)
  {
    sort_temp->distance = temp->distance;
    sort_temp->duration = temp->duration;
    memcpy(sort_temp, temp->name, strlen (temp->name) + 1);
    temp++;
    sort_temp++;
  }
  BusLine *sort_end = sort_temp;
  bubble_sort (sort_start, sort_end);
  int e = is_sorted_by_name (sort_start, sort_end);
  int f = is_equal (sort_start, sort_end, start, end);
  if (e)
  {
    printf ("%s %d %s", "TEST", TEST5, "PASSED: Sorted by name\n");
  }
  else
  {
    printf ("%s %d %s", "TEST", TEST5, "FAILED: Not sorted by name\n");
  }
  if (f)
  {
    printf ("%s %d %s", "TEST", TEST6, "PASSED: Lists are equal\n");
  }
  else
  {
    printf ("%s %d %s", "TEST ", TEST6, "FAILED: Lists aren't equal\n");
  }
  free (sort_start);
  return 0;
}

int test (BusLine *start, BusLine *end)
{
  int a = test_distance (start, end);
  int b = test_duration (start, end);
  int c = test_name (start, end);
  if(a+b+c)
  {
      return 1;
  }
    return 0;
}

int main (int argc, char *argv[])
{
  if (check_args_valid (argc, argv)) // if 1 -> the inputs are invalids
  {
    return EXIT_FAILURE;
  }
  int number_of_lines = get_number_of_lines ();
  BusLine *start = build_bus_list (number_of_lines);
  if (start == NULL)
  {
    return EXIT_FAILURE;
  }
  BusLine *end = start;
  int i =0;
  while (i<number_of_lines)
  {
    end++;
    i++;
  }
  SortType sort_type = find_type (argv[1]);
  if (strcmp (argv[1], "by_name") == 0)
  {
    bubble_sort_helper (start, end);
  }
  else if (strcmp (argv[1], "test") == 0)
  {
    if(test (start, end))
    {
        free(start);
        return EXIT_FAILURE;
    }
  }
  else
  {
    quick_sort_helper (start, end, sort_type);
  }
  free (start);
  return 0;
}

