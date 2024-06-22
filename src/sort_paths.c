#include "ft_ls.h"

char **reverse_paths(char **paths, int len) {
  char **reversed_paths = (char **)malloc((sizeof(char *) * len) + 1);
  reversed_paths[len] = NULL;

  for (int i = 0; i < len; i++) {
    reversed_paths[i] = ft_strdup(paths[len - i - 1]);
    free(paths[len - i - 1]);
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
  char **sorted_paths = (char **)malloc((sizeof(char *) * len) + 1);
  sorted_paths[len] = NULL;

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
  // pathsの存在チェック
  if (t) {
    // tがあれば更新時間順
    for (int i = 0; i < len - 1; i++) {
      for (int j = i + 1; j < len; j++) {
        if (mt_cmp(paths[i], paths[j]) < 0) {
          char *tmp = paths[j];
          paths[j] = paths[i];
          paths[i] = tmp;
        }
      }
    }
  }

  for (int i = 0; paths[i]; i++) {
    sorted_paths[i] = ft_strdup(paths[i]);
    free(paths[i]);
  }
  free(paths);

  if (r) {
    return reverse_paths(sorted_paths, len);
  }
  return sorted_paths;
}
