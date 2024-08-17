#include "ft_ls.h"

static File  *get_files_head(Args *args, char *path, DIR *dp, int exit_code) {
  File *head = (File *)malloc(sizeof(File));
  if (!head) {
    return NULL;
  }
  head->path_name = NULL;
  head->stat = NULL;
  head->next = NULL;

  File *current = head;
  struct dirent *ent;
  while (exit_code == 0 && (ent = readdir(dp))) {
    File  *f = get_file_stat(args, path, dp, ent);
    if (!f) {
      free_files(head);
      return NULL;
    }
    current->next = f;
    current = f;
  }
  return head;
}

static void  print_dir_name(char *path, bool print_path, bool endline, int exit_code) {
  if (!exit_code && print_path) {
    if (endline) {
      ft_putendl_fd("", 1);
    }
    ft_putstr_fd(path, 1);
    ft_putendl_fd(":", 1);
  }
}

static void  print_error_message(char *path, int exit_code) {
  if (exit_code) {
    ft_putstr_fd("ls: cannot open directory '", 2);
    ft_putstr_fd(path, 2);
    ft_putstr_fd("': ", 2);
    ft_putendl_fd(strerror(errno), 2);
  }
}

static bool  is_skip_recursive(FileInfo *info, Args *args) {
  bool is_dir = info->file_mode == S_IFDIR;
  bool is_current = ft_strcmp(info->path_name, ".") == 0;
  bool is_parent = ft_strcmp(info->path_name, "..") == 0;
  bool is_hidden = !args->show_hidden && info->path_name[0] == '.';
  return !is_dir || is_current || is_parent || is_hidden;
}

int exec_ls(char *path, Args *args, bool print_path, bool endline) {
  int exit_code = 0;
  errno = 0;
  DIR *dp = opendir(path);
  if (errno != 0) exit_code = 1;
  File *head = get_files_head(args, path, dp, exit_code);
  if (dp != NULL) closedir(dp);
  if (!head) {
    perror("malloc failed");
    return 42;
  }
  if (errno != 0) exit_code = 1;
  int files_len = 0;
  File *f = head->next;
  while (f) {
    ++files_len;
    f = f->next;
  }
  FileInfo **infos = get_file_infos(head, files_len);
  free_files(head);
  if (!infos) {
    perror("malloc failed");
    return 42;
  }
  FileInfo **sorted_infos = sort_infos(
    infos, files_len, args->order_by_modified_time, args->reverse
  );
  if (!sorted_infos) {
    free_file_infos(infos);
    perror("malloc failed");
    return 42;
  }
  print_dir_name(path, print_path, endline, exit_code);
  print_error_message(path, exit_code);
  print_file_info(sorted_infos, args, true);
  if (args->recursive) {
    for (int i = 0; sorted_infos[i]; i++) {
      if (is_skip_recursive(sorted_infos[i], args)) continue;
      exit_code |= exec_ls(sorted_infos[i]->stat_path, args, true, true);
    }
  }
  free_file_infos(sorted_infos);
  return exit_code;
}
