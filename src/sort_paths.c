#include "ft_ls.h"

char **reverse_paths(char **paths, int path_len) {
  char **reversed_paths = (char **)malloc(sizeof(char *) * (path_len + 1));
  reversed_paths[path_len] = NULL;

  for (int i = 0; i < path_len; i++) {
    reversed_paths[i] = ft_strdup(paths[path_len - i - 1]);
    free(paths[path_len - i - 1]);
  }
  free(paths);
  return reversed_paths;
}

int mt_cmp(char *s1, char *s2) {
  struct stat st1;
  struct stat st2;

  stat(s1, &st1);
  stat(s2, &st2);
  time_t diff_tv_sec = st1.st_mtime - st2.st_mtime;

  return diff_tv_sec;
}

Paths *sort_paths(char **paths, bool t, bool r) {
  int len = 0;
  for (int i = 0; paths[i]; i++) {
    ++len;
  }
  char **checked_paths = (char **)malloc(sizeof(char *) * (len + 1));
  checked_paths[len] = NULL;

  char **checked_files = (char **)malloc(sizeof(char *) * (len + 1));
  checked_files[len] = NULL;

  // pathsの存在チェック & グルーピング
  int checked_path_len = 0;
  int checked_file_len = 0;
  for (int i = 0; i < len; i++) {
    struct stat *st = (struct stat *)malloc(sizeof(struct stat));
    int stat_success = stat(paths[i], st) != 0;
    if (stat_success == 0 && S_ISDIR(st->st_mode)) {
      DIR *dir = opendir(paths[i]);
      if (dir != NULL) {
        closedir(dir);
        checked_paths[checked_path_len++] = ft_strdup(paths[i]);
      } else {
        ft_putstr_fd("ls: cannot access '", 2);
        ft_putstr_fd(paths[i], 2);
        ft_putstr_fd("': ", 2);
        ft_putendl_fd(strerror(errno), 2);
      }
    } else if (stat_success == 0) {
      checked_files[checked_file_len++] = ft_strdup(paths[i]);
    } else {
      ft_putstr_fd("ls: cannot access '", 2);
      ft_putstr_fd(paths[i], 2);
      ft_putstr_fd("': ", 2);
      ft_putendl_fd(strerror(errno), 2);
    }
    free(st);
  }
  for (int i = checked_file_len; i < len; i++) {
    checked_files[i] = NULL;
  }
  for (int i = checked_path_len; i < len; i++) {
    checked_paths[i] = NULL;
  }

  // 基本はascii順
  for (int i = 0; i < checked_path_len - 1; i++) {
    for (int j = i + 1; j < checked_path_len; j++) {
      if (ft_strcmp(checked_paths[i], checked_paths[j]) > 0) {
        char *tmp = checked_paths[j];
        checked_paths[j] = checked_paths[i];
        checked_paths[i] = tmp;
      }
    }
  }

  // tがあれば更新時間順
  if (t) {
    for (int i = 0; i < checked_path_len - 1; i++) {
      for (int j = i + 1; j < checked_path_len; j++) {
        if (mt_cmp(checked_paths[i], checked_paths[j]) < 0) {
          char *tmp = checked_paths[j];
          checked_paths[j] = checked_paths[i];
          checked_paths[i] = tmp;
        }
      }
    }
  }

  Paths *grouped_paths = (Paths *)malloc(sizeof(Paths));
  grouped_paths->files = checked_files;
  grouped_paths->total_paths_len = checked_file_len + checked_path_len;
  if (r) {
    grouped_paths->paths = reverse_paths(checked_paths, checked_path_len);
    return grouped_paths;
  }
  grouped_paths->paths = checked_paths;
  return grouped_paths;
}
