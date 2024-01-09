#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *fileName = "in.txt";


const int red = 12, green = 13, blue = 14;

int main() {
  FILE *file;
  char line[1024];

  // Open the file in read mode
  file = fopen(fileName, "r");

  // Check if file opened succesffully

  if (file == NULL) {
    perror("Error opening file");
    return 1; // Exit with error code
  }


  int sum = 0;
  while (fgets(line, sizeof(line), file) != NULL) {
    const char *ptr = line;
    const char *substring = "Game";

    char *result = strstr(ptr, substring);

    printf("%ld", result - ptr);

      
      

  }

  // close the file
  fclose(file);

  return 0;
}
