#include "ft_ls.h"

void free_files(File *head) {
  if (!head) {
    return;
  }
  File *c = head->next;
  while (c) {
    File *tmp = c;
    c = c->next;
    free(tmp->path_name);
    free(tmp->stat_path);
    free(tmp->stat);
    free(tmp);
  }
  free(head);
}

void free_file_infos(FileInfo **infos) {
  if (!infos) {
    return;
  }
  if (!infos[0]) {
    free(infos);
    return;
  }
  for (int i = 0; infos[i]; i++) {
    free(infos[i]->group_name);
    free(infos[i]->owner_name);
    free(infos[i]->path_name);
    free(infos[i]->stat_path);
    free(infos[i]->permission);
    free(infos[i]);
  }
  free(infos);
}
