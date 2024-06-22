#include "ft_ls.h"

int main(int argc, char** argv) {
  // parse args
  Args* args = parse_args(argc, argv);
  if(!args->paths) {
    return 1;
  }

  char **sorted_paths = sort_paths(
    args->paths,
    args->order_by_modified_time,
    args->reverse
  );

  for (int i = 0; sorted_paths[i]; i++) {
    exec_ls(sorted_paths[i], args);
  }

  // free
  for (int i = 0; sorted_paths[i]; i++) {
    free(sorted_paths[i]);
  }
  free(sorted_paths);
  free(args);
}
