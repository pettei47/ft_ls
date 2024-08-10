#include "ft_ls.h"

char *get_stat_path(char *path, char *name) {
  char *dir_path = ft_strjoin(path, "/");
  char *stat_path = ft_strjoin(dir_path, name);
  free(dir_path);
  return stat_path;
}


int exec_ls(char *path, Args *args, bool print_path, bool endline) {
  int exit_code = 0;
  errno = 0;
  DIR *dp = opendir(path);
  if (errno != 0) {
    exit_code = 1;
  }

  File *head = (File *)malloc(sizeof(File));
  head->path_name = NULL;
  head->stat = NULL;
  head->next = NULL;

  File *current = head;
  struct dirent *ent;
  while (exit_code == 0 && (ent = readdir(dp))) {
    char *name = dp == NULL ? path : ent->d_name;
    struct stat *st = (struct stat *)malloc(sizeof(struct stat));
    File *f = (File *)malloc(sizeof(File));
    f->next = NULL;
    f->stat_path = dp == NULL ? ft_strdup(path) : get_stat_path(path, ent->d_name);
    lstat(f->stat_path, st);
    f->stat = st;
    if (args->long_style && (st->st_mode & S_IFMT) == S_IFLNK) {
      char *link_buf = (char *)malloc(PATH_MAX);
      ssize_t len = readlink(f->stat_path, link_buf, PATH_MAX);
      link_buf[len] = '\0';
      char *link_from = ft_strjoin(name, " -> ");
      f->path_name = ft_strjoin(link_from, link_buf);
      free(link_buf);
      free(link_from);
    } else {
      f->path_name = ft_strdup(name);
    }
    current->next = f;
    current = f;
  }

  if (dp != NULL) closedir(dp);
  if (errno != 0) {
    exit_code = 1;
  }

  // stats to file info
  int files_len = 0;
  File *f = head->next;
  while (f) {
    ++files_len;
    f = f->next;
  }

  FileInfo **infos = (FileInfo **)malloc(sizeof(FileInfo) * (files_len + 1));
  infos[files_len] = NULL;

  File *c = head->next;
  for (int i = 0; i < files_len; i++) {
    infos[i] = (FileInfo *)malloc(sizeof(FileInfo));
    infos[i]->path_name = ft_strdup(c->path_name);
    free(c->path_name);
    infos[i]->stat_path = ft_strdup(c->stat_path);
    free(c->stat_path);
    infos[i]->file_mode = c->stat->st_mode & S_IFMT;
    infos[i]->permission = convert_permission(c->stat->st_mode);
    infos[i]->bytes = c->stat->st_size;
    infos[i]->num_of_block = c->stat->st_blocks / 2;
    infos[i]->num_of_hard_link = c->stat->st_nlink;
    infos[i]->modified_date = c->stat->st_mtime;
    infos[i]->group_name = ft_strdup(getgrgid(c->stat->st_gid)->gr_name);
    infos[i]->owner_name = ft_strdup(getpwuid(c->stat->st_uid)->pw_name);
    free(c->stat);
    File *tmp = c;
    c = c->next;
    free(tmp);
  }
  free(head);

  // sort infos
  FileInfo **sorted_infos = sort_infos(infos, files_len, args->order_by_modified_time, args->reverse);

  // 出力する
  if (!exit_code && print_path) {
    if (endline) {
      ft_putendl_fd("", 1);
    }
    ft_putstr_fd(path, 1);
    ft_putendl_fd(":", 1);
  }
  if (exit_code) {
    ft_putstr_fd("ls: cannot open directory '", 2);
    ft_putstr_fd(path, 2);
    ft_putstr_fd("': ", 2);
    ft_putendl_fd(strerror(errno), 2);
  }
  print_file_info(sorted_infos, args, true);

  // 再帰的に実行
  if (args->recursive) {
    for (int i = 0; sorted_infos[i]; i++) {
      // directoryかどうかを判定
      if (sorted_infos[i]->file_mode != S_IFDIR) {
        continue;
      }
      if (ft_strcmp(sorted_infos[i]->path_name, ".") == 0 ||
          ft_strcmp(sorted_infos[i]->path_name, "..") == 0 ) {
        continue;
      }
      if (!args->show_hidden && sorted_infos[i]->path_name[0] == '.') {
        continue;
      }
      if (exec_ls(sorted_infos[i]->stat_path, args, true, true)) {
        exit_code = 1;
      }
    }
  }

  // free
  for (int i = 0; sorted_infos[i]; i++) {
    free(sorted_infos[i]->group_name);
    free(sorted_infos[i]->owner_name);
    free(sorted_infos[i]->path_name);
    free(sorted_infos[i]->stat_path);
    free(sorted_infos[i]->permission);
    free(sorted_infos[i]);
  }
  free(sorted_infos[files_len]);
  free(sorted_infos);

  return exit_code;
}
