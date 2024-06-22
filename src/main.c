#include "ft_ls.h"

int main(int argc, char** argv) {
  // parse args
  (void)argc;
  (void)argv;
  // get file blob
  Args* args = parse_args(argc, argv);
  if(!args->paths) {
    return 1;
  }

  print_args(args);

  // set file info to struct

  // print
  // write(1, "hello world\n", 12);

  // free
  free(args->paths);
  free(args);
}
