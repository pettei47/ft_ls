#include "ft_ls.h"

int main(int argc, char** argv) {
  // parse args
  Args* args = parse_args(argc, argv);
  if(!args->paths) {
    return 1;
  }

  print_args(args);

  char **sorted_paths = sort_paths(
    args->paths,
    args->order_by_modified_time,
    args->reverse
  );

  ft_putstrs_fd(sorted_paths, "\n", 1);
  ft_putendl_fd("", 1);

  // free
  for (int i = 0; sorted_paths[i]; i++) {
    free(sorted_paths[i]);
  }
  free(sorted_paths);
  free(args);
}
