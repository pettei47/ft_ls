#include "ft_ls.h"

char **reverse_paths(char **paths, int path_len, char **files, int file_len) {
  char **reversed_paths = (char **)malloc(sizeof(char *) * (path_len + file_len + 1));
  reversed_paths[path_len] = NULL;

  for (int i = 0; i < file_len; i++) {
    reversed_paths[i] = ft_strdup(files[file_len - i - 1]);
    free(files[file_len - i - 1]);
  }
  free(files);
  for (int i = 0; i < path_len; i++) {
    reversed_paths[file_len + i] = ft_strdup(paths[path_len - i - 1]);
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
  int diff_tv_sec = &st1.st_mtimespec.tv_sec - &st2.st_mtimespec.tv_sec;
  int diff_tv_nsec = &st1.st_mtimespec.tv_nsec - &st2.st_mtimespec.tv_nsec;

  if (diff_tv_sec != 0) {
    return diff_tv_sec;
  }
  return diff_tv_nsec;
}

char **sort_paths(char **paths, bool t, bool r) {
  int len = 0;
  for (int i = 0; paths[i]; i++) {
    ++len;
  }
  // 基本はascii順
  for (int i = 0; i < len - 1; i++) {
    for (int j = i + 1; j < len; j++) {
      if (ft_strcmp(paths[i], paths[j]) > 0) {
        char *tmp = paths[j];
        paths[j] = paths[i];
        paths[i] = tmp;
      }
    }
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
        ft_putstr_fd("ft_ls: ", 2);
        ft_putstr_fd(paths[i], 2);
        ft_putstr_fd(": ", 2);
        ft_putendl_fd(strerror(errno), 2);
      }
    } else if (stat_success == 0) {
      checked_files[checked_file_len++] = ft_strdup(paths[i]);
    } else {
      ft_putstr_fd("ft_ls: ", 2);
      ft_putstr_fd(paths[i], 2);
      ft_putstr_fd(": ", 2);
      ft_putendl_fd(strerror(errno), 2);
    }
    free(st);
  }
  for (int i = checked_path_len; i < len; i++) {
    checked_paths[i] = NULL;
  }
  for (int i = checked_file_len; i < len; i++) {
    checked_files[i] = NULL;
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
    for (int i = 0; i < checked_file_len - 1; i++) {
      for (int j = i + 1; j < checked_file_len; j++) {
        if (mt_cmp(checked_files[i], checked_files[j]) < 0) {
          char *tmp = checked_files[j];
          checked_files[j] = checked_files[i];
          checked_files[i] = tmp;
        }
      }
    }
  }

  if (r) {
    return reverse_paths(checked_paths, checked_path_len, checked_files, checked_file_len);
  }

  int total_checked_len = checked_path_len + checked_file_len;
  char **sorted_paths = (char **)malloc(sizeof(char *) * (total_checked_len + 1));
  sorted_paths[total_checked_len] = NULL;

  // ファイルが先になるように
  for (int i = 0; checked_files[i]; i++) {
    sorted_paths[i] = ft_strdup(checked_files[i]);
    free(checked_files[i]);
  }
  free(checked_files);
  for (int i = 0; checked_paths[i]; i++) {
    sorted_paths[checked_file_len + i] = ft_strdup(checked_paths[i]);
    free(checked_paths[i]);
  }
  free(checked_paths);

  return sorted_paths;
}
