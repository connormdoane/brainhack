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
  int* loop_points[100] = {0};
  int loop_point = 0;
  int pc = 0;

  while (pc != length) {
    /* printf("%d %c\n", pc, filtered[pc]); */
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
      int val = pc;
      loop_points[loop_point++] = &val;
      break;
    case ']':
      if (memory[pointer] != 0) {
        pc = *loop_points[--loop_point]-1;
      } else {
        loop_point--;
      }
      
      break;
    default:
      break;
    }
    pc++;
  }

  printf("\n");
  return 0;
}
