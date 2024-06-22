#ifndef FT_LS_H
# define FT_LS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <errno.h>
# include "../libft/libft.h"

typedef struct s_args
{
  char **paths;
  bool long_style;
  bool order_by_modified_time;
  bool reverse;
  bool recursive;
  bool show_hidden;
} Args;

typedef struct s_file
{
  char *name;
  char *path_name;
  struct stat* stat;
} File;

typedef struct s_file_info
{
  char *path_name;
  char *name;
  int read_permission;
  int write_permission;
  int exec_permission;
  int size;
  int num_of_block;
  int modified_date;
  int created_date;
  int num_of_hard_link;
  char *owner_name;
  char *group_name;
} FileInfo;

Args *parse_args(int argc, char **argv);
char **sort_paths(char **paths, bool t, bool r);

// debugger
void print_args(Args *args);

#endif
