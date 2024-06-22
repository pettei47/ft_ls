#ifndef FT_LS_H
# define FT_LS_H

# include <time.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <errno.h>
# include <err.h>
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
  char *path_name;
  char *stat_path;
  struct stat *stat;
  struct s_file *next;
} File;

typedef struct s_file_info
{
  char *path_name;
  char *stat_path;
  int file_mode;
  char *permission;
  int bytes;
  int num_of_block;
  int num_of_hard_link;
  struct timespec modified_date;
  char *owner_name;
  char *group_name;
} FileInfo;

Args *parse_args(int argc, char **argv);
char **sort_paths(char **paths, bool t, bool r);
void exec_ls(char *path, Args *args, bool print_path, bool endline);
FileInfo **sort_infos(FileInfo **infos, int len, bool t, bool r);

// debugger
void print_args(Args *args);

#endif
