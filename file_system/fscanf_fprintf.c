#include <stdio.h>

int main(int argc, char const *argv[]) {
  FILE *file = fopen("D:\\hello_world.txt", "w+");
  fprintf(file, "%s", "hello world\n");
  // fflush(file);
  fclose(file);

  file = fopen("D:\\hello_world.txt", "r");
  char c;
  while (1) {
    if (feof(file))
      break;
    c = fgetc(file);
    printf("%c", c);
  }
  fclose(file);
  return 0;
}