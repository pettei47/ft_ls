#include "ft_ls.h"

int exec_ls_files(char **files, Args *args) {
  File *head = (File *)malloc(sizeof(File));
  if (!head) {
    perror("malloc failed");
    return 42;
  }
  head->path_name = NULL;
  head->stat = NULL;
  head->next = NULL;

  File *current = head;
  for (int i = 0; files[i]; i++) {
    char *name = files[i];
    File *f = (File *)malloc(sizeof(File));
    if (!f) {
      free(f);
      free_files(head);
      perror("malloc failed");
      return 42;
    }
    f->next = NULL;
    f->stat = (struct stat *)malloc(sizeof(struct stat));
    if (!f->stat) {
      free(f);
      free_files(head);
      perror("malloc failed");
      return 42;
    }
    f->stat_path = ft_strdup(name);
    if (!f->stat_path) {
      free(f->stat);
      free(f);
      free_files(head);
      perror("malloc failed");
      return 42;
    }
    lstat(f->stat_path, f->stat);
    if (args->long_style && (f->stat->st_mode & S_IFMT) == S_IFLNK) {
      char *link_buf = (char *)malloc(PATH_MAX);
      if (!link_buf) {
        free(f->stat);
        free(f->stat_path);
        free(f);
        free_files(head);
        perror("malloc failed");
        return 42;
      }
      ssize_t len = readlink(f->stat_path, link_buf, PATH_MAX);
      link_buf[len] = '\0';
      char *link_from = ft_strjoin(name, " -> ");
      f->path_name = ft_strjoin(link_from, link_buf);
      free(link_buf);
      if (!link_from || !f->path_name) {
        free(link_from);
        free(f->stat_path);
        free(f->stat);
        free_files(head);
        perror("malloc failed");
        return 42;
      }
      free(link_from);
    } else {
      f->path_name = ft_strdup(name);
      if (!f->path_name) {
        free(f->stat_path);
        free(f->stat);
        free(f);
        free_files(head);
        perror("malloc failed");
        return 42;
      }
    }
    current->next = f;
    current = f;
  }

  // stats to file info
  int files_len = 0;
  File *f = head->next;
  while (f) {
    ++files_len;
    f = f->next;
  }

  FileInfo **infos = (FileInfo **)malloc(sizeof(FileInfo) * (files_len + 1));
  if (!infos) {
    free_files(head);
    perror("malloc failed");
    return 42;
  }
  infos[files_len] = NULL;

  File *c = head->next;
  for (int i = 0; i < files_len; i++) {
    infos[i] = (FileInfo *)malloc(sizeof(FileInfo));
    if (!infos[i]) {
      free_files(head);
      free_file_infos(infos);
      perror("malloc failed");
      return 42;
    }
    infos[i]->path_name = ft_strdup(c->path_name);
    infos[i]->stat_path = ft_strdup(c->stat_path);
    infos[i]->file_mode = c->stat->st_mode & S_IFMT;
    infos[i]->permission = convert_permission(c->stat->st_mode);
    infos[i]->bytes = c->stat->st_size;
    infos[i]->num_of_block = c->stat->st_blocks / 2;
    infos[i]->num_of_hard_link = c->stat->st_nlink;
    infos[i]->modified_date = c->stat->st_mtime;
    infos[i]->group_name = ft_strdup(getgrgid(c->stat->st_gid)->gr_name);
    infos[i]->owner_name = ft_strdup(getpwuid(c->stat->st_uid)->pw_name);
    if (!infos[i]->path_name || !infos[i]->stat_path || !infos[i]->group_name || !infos[i]->owner_name) {
      free_files(head);
      free_file_infos(infos);
      perror("malloc failed");
      return 42;
    }
    c = c->next;
  }
  free_files(head);

  // sort infos
  FileInfo **sorted_infos = sort_infos(infos, files_len, args->order_by_modified_time, args->reverse);
  if (!sorted_infos) {
    free_file_infos(infos);
    perror("malloc failed");
    return 42;
  }

  // 出力する
  print_file_info(sorted_infos, args, false);

  // free
  free_file_infos(sorted_infos);

  return 0;
}
