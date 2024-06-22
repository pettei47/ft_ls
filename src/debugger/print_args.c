#include "ft_ls.h"

void  print_args(Args* args) {
  char *l = args->long_style ? "true" : "false";
  char *t = args->order_by_modified_time ? "true" : "false";
  char *r = args->reverse ? "true" : "false";
  char *a = args->show_hidden ? "true" : "false";
  char *R = args->recursive ? "true" : "false";

  ft_putendl_fd("# options:", 1);
  ft_putstr_fd("  - l:", 1);
  ft_putendl_fd(l, 1);
  ft_putstr_fd("  - t:", 1);
  ft_putendl_fd(t, 1);
  ft_putstr_fd("  - r:", 1);
  ft_putendl_fd(r, 1);
  ft_putstr_fd("  - a:", 1);
  ft_putendl_fd(a, 1);
  ft_putstr_fd("  - R:", 1);
  ft_putendl_fd(R, 1);

  ft_putendl_fd("# paths:", 1);
  for (int i = 0; args->paths[i]; i++)
  {
    ft_putstr_fd("  - ", 1);
    ft_putendl_fd(args->paths[i], 1);
  }
}
