#include "ft_ls.h"

char *ft_strlower(char *str) {
  char *lower = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
  if (!lower) {
    return NULL;
  }
  for (int i = 0; str[i]; i++) {
    lower[i] = ft_tolower(str[i]);
  }
  lower[ft_strlen(str)] = '\0';
  return lower;
}

int mtime_cmp(FileInfo *info1, char *path_name1, FileInfo *info2, char *path_name2) {
  long long diff_tv_sec = (long long)info1->modified_date_sec - (long long)info2->modified_date_sec;
  long long diff_tv_nsec = (long long)info1->modified_date_nsec - (long long)info2->modified_date_nsec;
  if (diff_tv_sec == 0 && diff_tv_nsec == 0) {
    int cmp = ft_strcmp(path_name2, path_name1);
    return cmp;
  }
  if (diff_tv_sec == 0) {
    return diff_tv_nsec;
  }
  return diff_tv_sec;
}

FileInfo **sort_infos(FileInfo **infos, int len, bool t, bool r) {
  for (int i = 0; i < len - 1; i++) {
    for (int j = i + 1; j < len; j++) {
      char *path_name1 = infos[i]->path_name[0] == '.' ? ft_strlower(infos[i]->path_name + 1) : ft_strlower(infos[i]->path_name);
      char *path_name2 = infos[j]->path_name[0] == '.' ? ft_strlower(infos[j]->path_name + 1) : ft_strlower(infos[j]->path_name);
      if (!path_name1 || !path_name2) {
        free(path_name1);
        free(path_name2);
        return NULL;
      }

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
        char *path_name1 = infos[i]->path_name[0] == '.' ? ft_strlower(infos[i]->path_name + 1) : ft_strlower(infos[i]->path_name);
        char *path_name2 = infos[j]->path_name[0] == '.' ? ft_strlower(infos[j]->path_name + 1) : ft_strlower(infos[j]->path_name);
        if (!path_name1 || !path_name2) {
          free(path_name1);
          free(path_name2);
          return NULL;
        }
        if (mtime_cmp(infos[i], path_name1, infos[j], path_name2) < 0) {
          FileInfo *tmp = infos[j];
          infos[j] = infos[i];
          infos[i] = tmp;
        }
        free(path_name1);
        free(path_name2);
      }
    }
  }

  if (r) {
    FileInfo **reversed_infos = (FileInfo **)malloc(sizeof(FileInfo) * (len + 1));
    if (!reversed_infos) {
      return NULL;
    }
    reversed_infos[len] = NULL;

    for (int i = 0; i < len; i++) {
      reversed_infos[i] = (FileInfo *)malloc(sizeof(FileInfo));
      if (!reversed_infos[i]) {
        free_file_infos(reversed_infos);
        return NULL;
      }

      int j = len - i - 1;
      reversed_infos[i]->bytes = infos[j]->bytes;
      reversed_infos[i]->file_mode = infos[j]->file_mode;
      reversed_infos[i]->path_name = ft_strdup(infos[j]->path_name);
      reversed_infos[i]->stat_path = ft_strdup(infos[j]->stat_path);
      reversed_infos[i]->permission = ft_strdup(infos[j]->permission);
      reversed_infos[i]->owner_name = ft_strdup(infos[j]->owner_name);
      reversed_infos[i]->group_name = ft_strdup(infos[j]->group_name);
      reversed_infos[i]->modified_date_sec = infos[j]->modified_date_sec;
      reversed_infos[i]->modified_date_nsec = infos[j]->modified_date_nsec;
      reversed_infos[i]->num_of_block = infos[j]->num_of_block;
      reversed_infos[i]->num_of_hard_link = infos[j]->num_of_hard_link;
      if (!reversed_infos[i]->path_name || !reversed_infos[i]->stat_path || !reversed_infos[i]->permission || !reversed_infos[i]->owner_name || !reversed_infos[i]->group_name) {
        free_file_infos(reversed_infos);
        return NULL;
      }
    }
    free_file_infos(infos);
    return reversed_infos;
  }
  return infos;
}
