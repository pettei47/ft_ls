#include "ft_ls.h"

FileInfo  **get_file_infos(File *head, int files_len) {
  FileInfo **infos = (FileInfo **)malloc(sizeof(FileInfo) * (files_len + 1));
  if (!infos) {
    free_files(head);
    perror("malloc failed");
    return NULL;
  }
  infos[files_len] = NULL;

  File *c = head->next;
  for (int i = 0; i < files_len; i++) {
    infos[i] = (FileInfo *)malloc(sizeof(FileInfo));
    if (!infos[i]) {
      free_file_infos(infos);
      return NULL;
    }
    infos[i]->path_name = ft_strdup(c->path_name);
    infos[i]->stat_path = ft_strdup(c->stat_path);
    infos[i]->file_mode = c->stat->st_mode & S_IFMT;
    infos[i]->permission = convert_permission(c->stat->st_mode);
    infos[i]->bytes = c->stat->st_size;
    infos[i]->num_of_block = c->stat->st_blocks / 2;
    infos[i]->num_of_hard_link = c->stat->st_nlink;
    infos[i]->modified_date_sec = c->stat->st_mtim.tv_sec;
    infos[i]->modified_date_nsec = c->stat->st_mtim.tv_nsec;
    infos[i]->group_name = ft_strdup(getgrgid(c->stat->st_gid)->gr_name);
    infos[i]->owner_name = ft_strdup(getpwuid(c->stat->st_uid)->pw_name);
    if (!infos[i]->path_name || !infos[i]->stat_path || !infos[i]->group_name || !infos[i]->owner_name) {
      free_file_infos(infos);
      return NULL;
    }
    c = c->next;
  }
  return infos;
}
