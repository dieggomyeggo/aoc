#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *fileName = "day2.txt";

const int RED_MAX = 12, GREEN_MAX = 13, BLUE_MAX = 14;

int findId(char *str) {
  char *ptr = str;
  while (*ptr) {
    if (isdigit(*ptr)) {
      return strtol(ptr, &ptr, 10);
    } else {
      ptr++;
    }

    if (*ptr == '\0') {
      break;
    }
  }
  return -1;
}

long findColor(char *inputString, char *color, int maxColor) {
  char *currentPos = inputString;
  long number = -1;

  while ((currentPos = strstr(currentPos, color)) != NULL) {
    // Check if the substring starts with a number
    if (currentPos != inputString && isdigit(*(currentPos - 2))) {
      // Extract the number
      char *endptr;
      number = strtol(currentPos - 3, &endptr, 10);

      if (number > maxColor) {
        return -1;
      }

      if (endptr != currentPos - 1) {
        // Successfully extracted a number
      }
    }

    // Move to the next position to avoid an infinite loop
    currentPos++;
  }

  return number;
}

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
    char *ptr = line;

    long red = findColor(ptr, "red", RED_MAX);
    long green = findColor(ptr, "green", GREEN_MAX);
    long blue = findColor(ptr, "blue", BLUE_MAX);

    const int gameid = findId(ptr);

    if (red == -1 || green == -1 || blue == -1) {
      continue;
    } else {
      sum += gameid;
    }

    // printf("%d\n", gameid);
    // printf("%ld", result - ptr);
  }

  printf("Sum: %d\n", sum);

  // close the file
  fclose(file);

  return 0;
}
