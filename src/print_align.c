#include "ft_ls.h"

void print_align_right(char *str, int width) {
  int len = ft_strlen(str);
  for (int i = 0; i < width - len; i++) {
    ft_putchar_fd(' ', 1);
  }
  ft_putstr_fd(str, 1);
}

void print_align_left(char *str, int width) {
  int len = ft_strlen(str);
  ft_putstr_fd(str, 1);
  for (int i = 0; i < width - len; i++) {
    ft_putchar_fd(' ', 1);
  }
}

void print_align_right_number(int num, int width) {
  char *str = ft_itoa(num);
  print_align_right(str, width);
  free(str);
}
