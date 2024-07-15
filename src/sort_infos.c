#include "ft_ls.h"

int mtime_cmp(FileInfo *info1, FileInfo *info2) {
  int diff_tv_sec = info1->modified_date - info2->modified_date;
  if (diff_tv_sec == 0) {
    return ft_strcmp(info2->path_name, info1->path_name);
  }
  return diff_tv_sec;
}

FileInfo **sort_infos(FileInfo **infos, int len, bool t, bool r) {
  for (int i = 0; i < len - 1; i++) {
    for (int j = i + 1; j < len; j++) {
      if (ft_strcmp(infos[i]->path_name, infos[j]->path_name) > 0) {
        FileInfo *tmp = infos[j];
        infos[j] = infos[i];
        infos[i] = tmp;
      }
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
