#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LENGTH 16384
#define STRIP_LENGTH 30000

int main(int argc, char* argv[])
{
  FILE* file = NULL;
  if (argc > 1) {
    file = fopen(argv[1], "r");
    if (!file) {
      printf("Error opening file %s. Ensure the file exists and is readable.\n", argv[1]);
      return -1;
    }
  } else {
    file = stdin;
  }

  // Remove comments to process just the raw commands
  const char brain_chars[] = "<>+-.,[]";
  char filtered[BUFFER_LENGTH];
  size_t length = 0;
  
  int ch;
  while ((ch = fgetc(file)) != EOF && length < BUFFER_LENGTH - 1) {
    if (strchr(brain_chars, ch)) filtered[length++] = (char)ch;
  }
  if (file != stdin) fclose(file);
  filtered[length] = '\0';

  printf("%s\n", filtered);

  return 0;
}
