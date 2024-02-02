#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

char *replace_string_dynamic(const char *source_string, const char *sequence_to_replace, const char *replacement)
{
  const uint64_t REPLACEMENT_STRING_LENGTH = strlen(replacement);
  const uint64_t SEQUENCE_TO_REPLACE_LENGTH = strlen(sequence_to_replace);

  char *result_string = NULL;
  char *replace_at = NULL;

  uint64_t result_string_size = 0;
  uint64_t previous_string_size = 0;

  while ((replace_at = strstr(source_string, sequence_to_replace)) != NULL)
  {
    uint64_t diff = replace_at - source_string;

    previous_string_size = result_string_size;
    result_string_size += diff + REPLACEMENT_STRING_LENGTH + 1;

    result_string = realloc(result_string, sizeof(char) * result_string_size);
    // realloc gives non-empty memory blocks, but "strcat" starts appending at the last '\0'
    result_string[previous_string_size] = '\0';

    result_string = strncat(result_string, source_string, diff);
    result_string = strcat(result_string, replacement);

    source_string += diff + SEQUENCE_TO_REPLACE_LENGTH;
  }

  previous_string_size = result_string_size;
  result_string_size += strlen(source_string) + 1;
  result_string = realloc(result_string, sizeof(char) * result_string_size);
  result_string[previous_string_size] = '\0';

  result_string = strcat(result_string, source_string);

  return result_string;
}

int main(void)
{
  char *result = replace_string_dynamic("Iubita mea este cea mai frumoasa!", "Iubita", "Nadira");
  printf(result);

  free(result);
  return 0;
}