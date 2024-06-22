#include "ft_ls.h"

char *convert_permission(int mode) {
  char *permission = ft_strdup("---------");
  if (mode & S_IRUSR) permission[0] = 'r';
  if (mode & S_IWUSR) permission[1] = 'w';
  if (mode & S_IXUSR) permission[2] = 'x';
  if (mode & S_IRGRP) permission[3] = 'r';
  if (mode & S_IWGRP) permission[4] = 'w';
  if (mode & S_IXGRP) permission[5] = 'x';
  if (mode & S_IROTH) permission[6] = 'r';
  if (mode & S_IWOTH) permission[7] = 'w';
  if (mode & S_IXOTH) permission[8] = 'x';
  return permission;
}

void  print_file_info(FileInfo **infos, bool long_style) {
  if (long_style) {
    int total_block = 0;
    for (int i = 0; infos[i]; i++) {
      total_block += infos[i]->num_of_block;
    }
    ft_putstr_fd("total ", 1);
    ft_putnbr_fd(total_block, 1);
    ft_putendl_fd("", 1);
  }

  for (int i = 0; infos[i]; i++) {
    if (long_style) {
      ft_putstr_fd(infos[i]->file_mode == S_IFDIR ? "d"
                  : infos[i]->file_mode == S_IFLNK ? "l" : "-", 1);
      ft_putstr_fd(infos[i]->permission, 1);
      ft_putstr_fd(" ", 1);
      ft_putnbr_fd(infos[i]->num_of_hard_link, 1);
      ft_putstr_fd(" ", 1);
      ft_putstr_fd(infos[i]->owner_name, 1);
      ft_putstr_fd(" ", 1);
      ft_putstr_fd(infos[i]->group_name, 1);
      ft_putstr_fd(" ", 1);
      ft_putnbr_fd(infos[i]->bytes, 1);
      ft_putstr_fd(" ", 1);
      ft_putstr_fd(infos[i]->modified_date, 1);
      ft_putstr_fd(" ", 1);
    }
    ft_putendl_fd(infos[i]->path_name, 1);
  }
}

char *get_stat_path(char *path, char *name) {
  char *dir_path = ft_strjoin(path, "/");
  char *stat_path = ft_strjoin(dir_path, name);
  free(dir_path);
  return stat_path;
}

void  exec_ls(char *path, Args *args) {
  DIR *dp = opendir(path);

  File *head = (File *)malloc(sizeof(File));
  head->path_name = NULL;
  head->stat = NULL;
  head->next = NULL;

  struct dirent *ent;
  File *current = head;
  while ((ent = readdir(dp))) {
    struct stat *st = (struct stat *)malloc(sizeof(struct stat));
    File *f = (File *)malloc(sizeof(File));

    f->path_name = ent->d_name;

    f->stat_path = get_stat_path(path, ent->d_name);
    lstat(f->stat_path, st);
    f->stat = st;

    current->next = f;
    current = f;
  }

  closedir(dp);

  // stats to file info
  int len = 0;
  File *f = head->next;
  while (f) {
    ++len;
    f = f->next;
  }

  FileInfo **infos = (FileInfo **)malloc((sizeof(FileInfo) * len) + 1);
  infos[len] = NULL;

  File *c = head->next;
  for (int i = 0; i < len; i++) {
    infos[i] = (FileInfo *)malloc(sizeof(FileInfo));
    infos[i]->path_name = ft_strdup(c->path_name);
    infos[i]->stat_path = ft_strdup(c->stat_path);
    infos[i]->file_mode = c->stat->st_mode & S_IFMT;
    infos[i]->permission = convert_permission(c->stat->st_mode);
    infos[i]->bytes = c->stat->st_size;
    infos[i]->num_of_block = c->stat->st_blocks;
    infos[i]->num_of_hard_link = c->stat->st_nlink;
    infos[i]->modified_date = ft_strdup(ctime(&c->stat->st_mtime));
    infos[i]->group_name = ft_strdup(getgrgid(c->stat->st_gid)->gr_name);
    infos[i]->owner_name = ft_strdup(getpwuid(c->stat->st_uid)->pw_name);
    c = c->next;
  }

  // sort infos
  if (args->order_by_modified_time) {
    ft_putendl_fd("変更時刻順に並び替える", 1);
  }
  else { // ordered by ascii
    ft_putendl_fd("ASCII順に並び替える", 1);
    for (int i = 0; i < len - 1; i++) {
      for (int j = i + 1; j < len; j++) {
        if (ft_strcmp(infos[i]->path_name, infos[j]->path_name) > 0) {
          FileInfo *tmp = infos[j];
          infos[j] = infos[i];
          infos[i] = tmp;
        }
      }
    }
  }

  if (args->reverse) {
    ft_putendl_fd("逆順に並び替える", 1);
  }

  // 出力する
  print_file_info(infos, args->long_style);

  // 再帰的に実行
  if (args->recursive) {
    // loop head
    //   exec_ls(stat_path, args);
    return;
  }

  // free

}
