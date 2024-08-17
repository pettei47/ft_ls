#include "ft_ls.h"

char *get_stat_path(char *path, char *name) {
  char *dir_path = ft_strjoin(path, "/");
  if (!dir_path) {
    return NULL;
  }
  char *stat_path = ft_strjoin(dir_path, name);
  if (!stat_path) {
    free(dir_path);
    return NULL;
  }
  free(dir_path);
  return stat_path;
}

int exec_ls(char *path, Args *args, bool print_path, bool endline) {
  int exit_code = 0;
  errno = 0;
  DIR *dp = opendir(path);
  if (errno != 0) {
    exit_code = 1;
  }

  File *head = (File *)malloc(sizeof(File));
  if (!head) {
    perror("malloc failed");
    return 42;
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
      perror("malloc failed");
      return 42;
    }
    current->next = f;
    current = f;
  }

  if (dp != NULL) closedir(dp);
  if (errno != 0) {
    exit_code = 1;
  }

  // stats to file info
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

  // sort infos
  FileInfo **sorted_infos = sort_infos(infos, files_len, args->order_by_modified_time, args->reverse);
  if (!sorted_infos) {
    free_file_infos(infos);
    perror("malloc failed");
    return 42;
  }

  // 出力する
  if (!exit_code && print_path) {
    if (endline) {
      ft_putendl_fd("", 1);
    }
    ft_putstr_fd(path, 1);
    ft_putendl_fd(":", 1);
  }
  if (exit_code) {
    ft_putstr_fd("ls: cannot open directory '", 2);
    ft_putstr_fd(path, 2);
    ft_putstr_fd("': ", 2);
    ft_putendl_fd(strerror(errno), 2);
  }
  print_file_info(sorted_infos, args, true);

  // 再帰的に実行
  if (args->recursive) {
    for (int i = 0; sorted_infos[i]; i++) {
      // directoryかどうかを判定
      if (sorted_infos[i]->file_mode != S_IFDIR) {
        continue;
      }
      if (ft_strcmp(sorted_infos[i]->path_name, ".") == 0 ||
          ft_strcmp(sorted_infos[i]->path_name, "..") == 0 ) {
        continue;
      }
      if (!args->show_hidden && sorted_infos[i]->path_name[0] == '.') {
        continue;
      }
      if (exec_ls(sorted_infos[i]->stat_path, args, true, true)) {
        exit_code = 1;
      }
    }
  }

  // free
  free_file_infos(sorted_infos);

  return exit_code;
}
