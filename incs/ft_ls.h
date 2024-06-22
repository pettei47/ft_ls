#ifndef FT_LS_H
# define FT_LS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_args
{
  char **paths;
  bool long_style;
  bool order_by_modified_time;
  bool reverse;
  bool recursive;
  bool show_hidden;
} Args;

typedef struct s_file {
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

#endif
