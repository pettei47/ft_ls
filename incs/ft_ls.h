#ifndef FT_LS_H
# define FT_LS_H

# include <time.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/param.h>
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
  bool show_blocks;
} Args;

typedef struct s_paths
{
  char **files;
  char **paths;
  int total_paths_len;
} Paths;

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
  time_t modified_date;
  char *owner_name;
  char *group_name;
} FileInfo;

Args      *parse_args(int argc, char **argv);
Paths     *sort_paths(char **paths, bool t, bool r);
File      *get_file_stat(Args *args, char *path, DIR *dp, struct dirent *ent);
FileInfo  **get_file_infos(File *head, int files_len);
int       exec_ls(char *path, Args *args, bool print_path, bool endline);
int       exec_ls_files(char **files, Args *args);
char      *convert_permission(int mode);
FileInfo  **sort_infos(FileInfo **infos, int len, bool t, bool r);
int       print_file_info(FileInfo **infos, Args *args, bool is_dir);
void      print_align_left(char *str, int width);
void      print_align_right(char *str, int width);
void      free_files(File *head);
void      free_file_infos(FileInfo **infos);

// debugger
void      print_args(Args *args);

#endif
