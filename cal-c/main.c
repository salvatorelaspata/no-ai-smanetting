#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
  ARG_OK = 0,
  ARG_ERR_EMPTY,
  ARG_ERR_EXTRA_CHARS,
  ARG_ERR_OVERFLOW,
  ARG_ERR_RANGE
} ArgStatus;

ArgStatus parse_int_arg(const char* s, int min_val, int max_val, int* out) {
  if (s == NULL || *s == '\0') return ARG_ERR_EMPTY;

  errno = 0;            // error imported from errno.h
  char* endptr = NULL;  // empty value
  long val = strtol(s, &endptr, 10);

  if (errno == ERANGE) return ARG_ERR_OVERFLOW;

  if (endptr == s) return ARG_ERR_EMPTY;

  if (*endptr != '\0') return ARG_ERR_EXTRA_CHARS;

  if (val < INT_MIN || val > INT_MAX) return ARG_ERR_OVERFLOW;

  if (val < min_val || val > max_val) return ARG_ERR_RANGE;

  *out = (int)val;
  return ARG_OK;
}

void print_arg_error(const char* name, ArgStatus status, const char* raw) {
  switch (status) {
    case ARG_ERR_EMPTY:
      printf("[error] %s is empty\n", name);
      break;
    case ARG_ERR_EXTRA_CHARS:
      printf("[error] %s only numeric characters allowed (near '%s')\n", name,
             raw);
      break;
    case ARG_ERR_OVERFLOW:
      printf("[error] %s out of range (overflow)\n", name);
      break;
    case ARG_ERR_RANGE:
      printf("[error] %s out of valid bounds\n", name);
      break;
    default:
      printf("[error] invalid %s\n", name);
      break;
  }
}

int main(int argc, char* argv[]) {
  int month = 11;
  int year = 2026;
  ArgStatus st;

  switch (argc) {
    case 1:  // cal --> print: month current; year current;
      printf("print calendar month=%d year=%d\n", month, year);
      break;
    case 2:  // cal YYYY --> print: calendar YYYY
      st = parse_int_arg(argv[1], 0, 9999, &year);
      if (st != ARG_OK) {
        print_arg_error("year", st, argv[1]);
        return 1;
      }

      printf("print calendar year=%d\n", year);
      break;
    case 3:  // cal MM YYYY --> print: month MM; year YYYY;
      st = parse_int_arg(argv[1], 0, 12, &month);
      if (st != ARG_OK) {
        print_arg_error("month", st, argv[1]);
        return 1;
      }
      st = parse_int_arg(argv[2], 1, 9999, &year);
      if (st != ARG_OK) {
        print_arg_error("year", st, argv[2]);
        return 1;
      }
      printf("print calendar month=%d year=%d\n", month, year);
      break;
    default:
      printf("[error] too many arguments\n");
      return 1;
  }
  return 0;
}