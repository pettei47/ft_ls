#include "ft_ls.h"

int main(int argc, char** argv) {
  // parse args
  Args *args = parse_args(argc, argv);
  if(!args->paths) {
    return 1;
  }

  char **sorted_paths = sort_paths(
      args->paths,
      args->order_by_modified_time,
      args->reverse);

  int paths_count = 0;
  for (int i = 0; sorted_paths[i]; i++) {
    ++paths_count;
  }

  for (int i = 0; sorted_paths[i]; i++) {
    exec_ls(sorted_paths[i], args, paths_count > 1, i > 0);
  }

  // free
  for (int i = 0; sorted_paths[i]; i++) {
    free(sorted_paths[i]);
  }
  free(sorted_paths[paths_count]);
  free(sorted_paths);
  for (int i = 0; args->paths[i]; i++) {
    free(args->paths[i]);
  }
  free(args->paths[paths_count]);
  free(args->paths);
  free(args);
  return 0;
}
