#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

const char *fileName = "day1.txt";

struct Result {
  int firstDigit;
  int lastDigit;
};

struct Result searchDigit(const char *str) {
  const char *start = str;
  const char *end = str;

  // Check if end is at the end of the line
  while (*end != '\0') {
    end++;
  }
  end--;

  while (start <= end) {
    if (!isdigit(*start)) {
      start++;
    }
    if (!isdigit(*end)) {
      end--;
    }

    if (isdigit(*start) && isdigit(*end)) {
      break;
    }
  }

  int startDigit = *start - '0';
  int endDigit = *end - '0';

  struct Result result = {startDigit, endDigit};
  return result;
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

    struct Result result = searchDigit(line);

    printf("%s", line);
    printf("first digit: %d, last digit: %d\n", result.firstDigit,
           result.lastDigit);
    int number = result.firstDigit * 10 + result.lastDigit;
    printf("Number: %d\n", number);

    sum += number;
    printf("Sum: %d\n", sum);
  }

  printf("Sum: %d\n", sum);

  // close the file
  fclose(file);

  // printf("Hello, world!\n");
  return 0;
}
