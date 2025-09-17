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
  int length = 0;
  
  int ch;
  while ((ch = fgetc(file)) != EOF && length < BUFFER_LENGTH - 1) {
    if (strchr(brain_chars, ch)) filtered[length++] = (char)ch;
  }
  if (file != stdin) fclose(file);
  filtered[length] = '\0';

  printf("%s\n", filtered);

  int memory[STRIP_LENGTH] = {0};
  int pointer = STRIP_LENGTH / 2;
  long pc = 0;

  while (pc != length) {
    /* printf("%d %c\n", pc, filtered[pc]); */
    /* printf("%ld %d", pc, memory[pointer]); */
    switch(filtered[pc]) {
    case '<':
      pointer--;
      break;
    case '>':
      pointer++;
      break;
    case '+':
      memory[pointer]++;
      break;
    case '-':
      memory[pointer]--;
      break;
    case '.':
      printf("%c", (char)memory[pointer]);
      break;
    case ',':
      int ch = getchar();
      memory[pointer] = ch;
      break;
    case '[':
      if (memory[pointer] == 0) { // skip the loop
        int loop_counter = 1;
        while (loop_counter != 0) {
          pc++;
          if (filtered[pc] == '[') loop_counter++;
          if (filtered[pc] == ']') loop_counter--;
        }
      }
      break;
    case ']':
      if (memory[pointer] != 0) { // jump to start of the loop
        int loop_counter = 1;
        while (loop_counter != 0) {
          pc--;
          if (filtered[pc] == ']') loop_counter++;
          if (filtered[pc] == '[') loop_counter--;
        }
      }
      break;
    default:
      break;
    }
    /* printf("pc: %ld, memory[pointer]: %d\n", pc, memory[pointer]); */
    pc++;
  }

  printf("\n");
  return 0;
}
