#include "ft_ls.h"

bool is_directory(struct stat *st) {
  return (st->st_mode & S_IFMT) == S_IFDIR;
}

void  print_files(File *f) {
  File *current = f->next;
  while (current) {
    char *is_dir = is_directory(current->stat) ? "d " : "- ";
    ft_putstr_fd(is_dir, 1);
    ft_putendl_fd(current->path_name, 1);
    // printf("デバイスID : %d\n",current->stat->st_dev);
    // printf("inode番号 : %llu\n",current->stat->st_ino);
    // printf("アクセス保護 : %o\n",current->stat->st_mode);
    // printf("ハードリンクの数 : %d\n",current->stat->st_nlink);
    // printf("所有者のユーザID : %d\n",current->stat->st_uid);
    // printf("所有者のグループID : %d\n",current->stat->st_gid);
    // printf("デバイスID(特殊ファイルの場合) : %d\n",current->stat->st_rdev);
    // printf("容量(バイト単位) : %lld\n",current->stat->st_size);
    // printf("ファイルシステムのブロックサイズ : %d\n",current->stat->st_blksize);
    // printf("割り当てられたブロック数 : %lld\n",current->stat->st_blocks);
    // printf("最終アクセス時刻 : %s",ctime(&current->stat->st_atime));
    // printf("最終修正時刻 : %s",ctime(&current->stat->st_mtime));
    // printf("最終状態変更時刻 : %s",ctime(&current->stat->st_ctime));
    current = current->next;
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
  printf("len: %d\n", len);

  FileInfo **infos = (FileInfo **)malloc((sizeof(FileInfo) * len) + 1);
  infos[len] = NULL;

  File *c = head->next;
  for (int i = 0; infos[i]; i++) {
    FileInfo *info = (FileInfo *)malloc(sizeof(FileInfo));

    info->path_name = ft_strdup(c->path_name);
    info->stat_path = ft_strdup(c->stat_path);
    info->file_mode = c->stat->st_mode & S_IFMT;
    info->owner_permission = (c->stat->st_mode / 100) % 10;
    info->others_permission = (c->stat->st_mode / 10) % 10;
    info->others_permission = c->stat->st_mode % 10;
    info->bytes = c->stat->st_size;
    info->num_of_block = c->stat->st_blocks;
    info->num_of_hard_link = c->stat->st_nlink;
    info->modified_date = ft_strdup(ctime(&c->stat->st_mtime));
    info->group_name = ft_strdup(getgrgid(c->stat->st_gid)->gr_name);
    info->owner_name = ft_strdup(getpwuid(c->stat->st_uid)->pw_name);

    infos[i] = info;
    c = c->next;
  }

  // sort infos
  if (args->order_by_modified_time) {
    ft_putendl_fd("変更時刻順に並び替える", 1);
  }
  else { // ordered by ascii
    ft_putendl_fd("ASCII順に並び替える", 1);
    // for (int i = 0; i < len - 1; i++) {
    //   for (int j = len - 1; j > i; j--) {

    //   }
    // }
  }

  if (args->reverse) {
    ft_putendl_fd("逆順に並び替える", 1);
  }

  // 出力する
  print_files(head);

  // 再帰的に実行
  if (args->recursive) {
    // loop head
    //   exec_ls(stat_path, args);
    return;
  }

  // free

}
