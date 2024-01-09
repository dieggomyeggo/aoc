#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *fileName = "day2.txt";

const char *colors[] = {"red", "green", "blue"};

const int RED_MAX = 12, GREEN_MAX = 13, BLUE_MAX = 14;

struct ColorMax {
  int red;
  int green;
  int blue;
};

struct ColorMax findMinimums(char *inputString) {
  struct ColorMax min;
  min.red = INT_MIN;
  min.green = INT_MIN;
  min.blue = INT_MIN;
  char *currentPos = inputString;

  for (int i = 0; i < 3; i++) {
    currentPos = inputString;
    while ((currentPos = strstr(currentPos, colors[i])) != NULL) {
      // Check if the substring starts with a number
      if (currentPos != inputString && isdigit(*(currentPos - 2))) {
        // Extract the number
        char *endptr;
        long number = strtol(currentPos - 3, &endptr, 10);
          // Successfully extracted a number
          if (i == 0) {
            min.red = min.red < number ? number : min.red;
          } else if (i == 1) {
            min.green = min.green < number ? number : min.green;
          } else if (i == 2) {
            min.blue = min.blue < number ? number : min.blue;
          }
      }
      // Move to the next position to avoid an infinite loop
      currentPos++;
    }
  }
  return min;
}

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

    // long red = findColor(ptr, "red", RED_MAX);
    // long green = findColor(ptr, "green", GREEN_MAX);
    // long blue = findColor(ptr, "blue", BLUE_MAX);

    const int gameid = findId(ptr);

    struct ColorMax min = findMinimums(ptr);

    printf("%s\n", ptr);
    printf("RED: %d, GREEN:  %d, BLUE: %d\n", min.red, min.green, min.blue);

    long power = min.red * min.green * min.blue;
    sum += power;

    // if (red == -1 || green == -1 || blue == -1) {
    //   continue;
    // } else {
    //   sum += gameid;
    // }

    // printf("%d\n", gameid);
    // printf("%ld", result - ptr);
  }

  printf("Sum: %d\n", sum);

  // close the file
  fclose(file);

  return 0;
}
