#include "ft_ls.h"

int main(int argc, char** argv) {
  // parse args
  Args* args = parse_args(argc, argv);
  if(!args->paths) {
    return 1;
  }

  print_args(args);

  // get file blob


  // set file info to struct


  // print

  // free
  free(args->paths);
  free(args);
}
