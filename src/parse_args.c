#include "ft_ls.h"

Args* parse_args(int argc, char** argv) {
  Args *parsed_args = (Args*)malloc(sizeof(Args));

  parsed_args->long_style = false;
  parsed_args->order_by_modified_time = false;
  parsed_args->recursive = false;
  parsed_args->reverse = false;
  parsed_args->show_hidden = false;
  parsed_args->show_blocks = false;

  bool acceptable_options = true;
  int count_paths = 0;
  int start_path_number = 0;
  for (int i = 1; argv[i]; i++)
  {
    char *arg = argv[i];
    if(ft_strlen(arg) == 0) {
      parsed_args->paths = NULL;
      ft_putendl_fd("ls: : No such file or directory", 2);
      return parsed_args;
    }

    if(acceptable_options && arg[0] == '-') {
      parsed_args->recursive = ft_strchr(arg, 'R') != 0;
      parsed_args->show_hidden = ft_strchr(arg, 'a') != 0;
      parsed_args->long_style = ft_strchr(arg, 'l') != 0;
      parsed_args->reverse = ft_strchr(arg, 'r') != 0;
      parsed_args->show_blocks = ft_strchr(arg, 's') != 0;
      parsed_args->order_by_modified_time = ft_strchr(arg, 't') != 0;
      for (int i = 1; arg[i]; i++) {
        if(!ft_strchr("Ralrst", arg[i])) {
          parsed_args->paths = NULL;
          ft_perror("ls: invalid option -- ", &arg[i]);
          ft_putendl_fd("usage: ft_ls [-Ralrst] [file ...]", 2);
          return parsed_args;
        }
      }
    } else {
      acceptable_options = false;
      if (start_path_number == 0) {
        start_path_number = i;
      }
      ++count_paths;
    }
  }

  if (count_paths == 0) {
    parsed_args->paths = (char **)malloc(sizeof(char *) * 2);
    parsed_args->paths[0] = ft_strdup(".");
    parsed_args->paths[1] = NULL;
    return parsed_args;
  }

  parsed_args->paths = (char **)malloc(sizeof(char *) * (count_paths + 1));
  for (int i = start_path_number; i < argc; i++) {
    parsed_args->paths[i - start_path_number] = ft_strdup(argv[i]);
  }
  parsed_args->paths[count_paths] = NULL;

  return parsed_args;
}
