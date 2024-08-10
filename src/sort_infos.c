#include "ft_ls.h"

char *ft_strlower(char *str) {
  char *lower = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
  for (int i = 0; str[i]; i++) {
    lower[i] = ft_tolower(str[i]);
  }
  lower[ft_strlen(str)] = '\0';
  return lower;
}

int mtime_cmp(FileInfo *info1, FileInfo *info2) {
  int diff_tv_sec = info1->modified_date - info2->modified_date;
  if (diff_tv_sec == 0) {
    char *path_name1 = info1->path_name[0] == '.' ? ft_strlower(info1->path_name + 1) : ft_strlower(info1->path_name);
    char *path_name2 = info2->path_name[0] == '.' ? ft_strlower(info2->path_name + 1) : ft_strlower(info2->path_name);
    int cmp = ft_strcmp(path_name2, path_name1);
    free(path_name1);
    free(path_name2);
    return cmp;
  }
  return diff_tv_sec;
}

FileInfo **sort_infos(FileInfo **infos, int len, bool t, bool r) {
  for (int i = 0; i < len - 1; i++) {
    for (int j = i + 1; j < len; j++) {
      char *path_name1 = infos[i]->path_name[0] == '.' ? ft_strlower(infos[i]->path_name + 1) : ft_strlower(infos[i]->path_name);
      char *path_name2 = infos[j]->path_name[0] == '.' ? ft_strlower(infos[j]->path_name + 1) : ft_strlower(infos[j]->path_name);
      if (ft_strcmp(path_name1, path_name2) > 0) {
        FileInfo *tmp = infos[j];
        infos[j] = infos[i];
        infos[i] = tmp;
      }
      free(path_name1);
      free(path_name2);
    }
  }
  if (t) {
    for (int i = 0; i < len - 1; i++) {
      for (int j = i + 1; j < len; j++) {
        if (mtime_cmp(infos[i], infos[j]) < 0) {
          FileInfo *tmp = infos[j];
          infos[j] = infos[i];
          infos[i] = tmp;
        }
      }
    }
  }

  if (r) {
    FileInfo **reversed_infos = (FileInfo **)malloc(sizeof(FileInfo) * (len + 1));
    reversed_infos[len] = NULL;

    for (int i = 0; i < len; i++) {
      reversed_infos[i] = (FileInfo *)malloc(sizeof(FileInfo));

      int j = len - i - 1;
      reversed_infos[i]->bytes = infos[j]->bytes;
      reversed_infos[i]->file_mode = infos[j]->file_mode;
      reversed_infos[i]->path_name = ft_strdup(infos[j]->path_name);
      free(infos[j]->path_name);
      reversed_infos[i]->stat_path = ft_strdup(infos[j]->stat_path);
      free(infos[j]->stat_path);
      reversed_infos[i]->permission = ft_strdup(infos[j]->permission);
      free(infos[j]->permission);
      reversed_infos[i]->owner_name = ft_strdup(infos[j]->owner_name);
      free(infos[j]->owner_name);
      reversed_infos[i]->group_name = ft_strdup(infos[j]->group_name);
      free(infos[j]->group_name);
      reversed_infos[i]->modified_date = infos[j]->modified_date;
      reversed_infos[i]->num_of_block = infos[j]->num_of_block;
      reversed_infos[i]->num_of_hard_link = infos[j]->num_of_hard_link;

      free(infos[j]);
    }
    free(infos[len]);
    free(infos);
    return reversed_infos;
  }
  return infos;
}
