#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *fileName = "day1.txt";

const char *digitNames[9] = {"one", "two",   "three", "four", "five",
                             "six", "seven", "eight", "nine"};

struct Result {
  int firstDigit;
  int lastDigit;
};

int mapNameToDigit(const char *name) {
  for (int i = 0; i < 9; i++) {
    size_t len = strlen(digitNames[i]);
    printf("len: %ld, name: %s\n", len, name);
    if (strncmp(name, digitNames[i], len) == 0) {
      return i + 1;
    }
  }
  return -1;
}

struct Result searchDigit(const char *str) {
  const char *start = str;
  const char *end = str;

  const char *firstNamedDigit = NULL;
  const char *lastNamedDigit = NULL;

  for (int i = 0; i < 9; i++) {

    const char *found = strstr(str, digitNames[i]);

    if (found != NULL) {
      printf("Start Found %s\n", digitNames[i]);
      firstNamedDigit = (firstNamedDigit == NULL || found < firstNamedDigit)
                            ? found
                            : firstNamedDigit;
    }
  }

  for (int i = 0; i < 9; i++) {
    const char *found = strstr(str, digitNames[i]);
    const char *lastOccurence = found;

    if (found != NULL) {
      printf("End Found %s\n", digitNames[i]);
      lastNamedDigit = (lastNamedDigit == NULL || found > lastNamedDigit)
                           ? found
                           : lastNamedDigit;
    }

    while (found != NULL) {
      lastOccurence = found;
      found = strstr(found + 1, digitNames[i]);
    }

    if (lastOccurence != NULL) {
      printf("End Found %s\n", digitNames[i]);
      lastNamedDigit = (lastNamedDigit == NULL || lastOccurence > lastNamedDigit)
                         ? lastOccurence
                         : lastNamedDigit;
    }
      
  }

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

  start = (firstNamedDigit != NULL && firstNamedDigit < start) ? firstNamedDigit
                                                               : start;
  end = (lastNamedDigit != NULL && lastNamedDigit > end) ? lastNamedDigit : end;

  int startDigit =
      (*start >= '0' && *start <= '9') ? *start - '0' : mapNameToDigit(start);
  int endDigit =
      (*end >= '0' && *end <= '9') ? *end - '0' : mapNameToDigit(end);

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
    printf("Line: %s", line);
    struct Result result = searchDigit(line);
    printf("first digit: %d, last digit: %d\n", result.firstDigit,
           result.lastDigit);
    int number = result.firstDigit * 10 + result.lastDigit;
    printf("Number: %d\n", number);

    sum += number;
  }

  // close the file
  fclose(file);
  printf("Sum: %d\n", sum);

  return 0;
}
