#include "ft_ls.h"

char **reverse_paths(char **paths, int len) {
  char **reversed_paths = (char **)malloc(sizeof(char *) * (len + 1));
  reversed_paths[len] = NULL;

  for (int i = 0; i < len; i++) {
    reversed_paths[i] = ft_strdup(paths[len - i - 1]);
    free(paths[len - i - 1]);
  }
  free(paths[len]);
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

  // pathsの存在チェック
  int checked_len = 0;
  for (int i = 0; i < len; i++) {
    DIR *dir = opendir(paths[i]);
    if (dir == NULL) {
      ft_putstr_fd("ft_ls: ", 2);
      ft_putstr_fd(paths[i], 2);
      ft_putstr_fd(": ", 2);
      ft_putendl_fd(strerror(errno), 2);
    } else {
      closedir(dir);
      checked_paths[checked_len++] = ft_strdup(paths[i]);
    }
  }
  for (int i = checked_len; i < len; i++) {
    checked_paths[i] = NULL;
  }

  // tがあれば更新時間順
  if (t) {
    for (int i = 0; i < checked_len - 1; i++) {
      for (int j = i + 1; j < checked_len; j++) {
        if (mt_cmp(checked_paths[i], checked_paths[j]) < 0) {
          char *tmp = checked_paths[j];
          checked_paths[j] = checked_paths[i];
          checked_paths[i] = tmp;
        }
      }
    }
  }

  char **sorted_paths = (char **)malloc(sizeof(char *) * (checked_len + 1));
  sorted_paths[checked_len] = NULL;

  for (int i = 0; checked_paths[i]; i++) {
    sorted_paths[i] = ft_strdup(checked_paths[i]);
    free(checked_paths[i]);
  }
  free(checked_paths);

  if (r) {
    return reverse_paths(sorted_paths, checked_len);
  }
  return sorted_paths;
}
