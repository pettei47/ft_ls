#include "ft_ls.h"

void  free_args(Args *args) {
  if (!args) {
    return;
  }
  if (args->paths) {
    for (int i = 0; args->paths[i]; i++) {
      free(args->paths[i]);
    }
    free(args->paths);
  }
  free(args);
}

void  free_paths(Paths *paths) {
  if (!paths) {
    return;
  }
  if (paths->paths) {
    for (int i = 0; paths->paths[i]; i++) {
      free(paths->paths[i]);
    }
    free(paths->paths);
  }
  if (paths->files) {
    for (int i = 0; paths->files[i]; i++) {
      free(paths->files[i]);
    }
    free(paths->files);
  }
  free(paths);
}

int main(int argc, char** argv) {
  // parse args
  Args *args = parse_args(argc, argv);
  if(!args || !args->paths) {
    free_args(args);
    exit(1);
  }

  int arg_paths_count = 0;
  for (int i = 0; args->paths[i]; i++) {
    ++arg_paths_count;
  }

  Paths *sorted_paths = sort_paths(
    args->paths,
    args->order_by_modified_time,
    args->reverse
  );
  if (!sorted_paths || !sorted_paths->paths || !sorted_paths->files) {
    free_paths(sorted_paths);
    free_args(args);
    exit(1);
  }

  int sorted_paths_count = sorted_paths->total_paths_len;
  int exit_code = arg_paths_count == sorted_paths_count ? 0 : 1;

  int exec_file_exit_code = exec_ls_files(sorted_paths->files, args);
  if (exec_file_exit_code == 42) {
    free_paths(sorted_paths);
    free_args(args);
    exit(1);
  }
  exit_code |= exec_file_exit_code;

  for (int i = 0; sorted_paths->paths[i]; i++) {
    int exec_exit_code = exec_ls(
      sorted_paths->paths[i],
      args, arg_paths_count > 1 || args->recursive,
      sorted_paths->files[0] || i > 0
    );
    if (exec_exit_code == 42) {
      free_paths(sorted_paths);
      free_args(args);
      exit(1);
    }
    exit_code |= exec_exit_code;
  }

  // free
  free_paths(sorted_paths);
  free_args(args);
  return exit_code;
}
