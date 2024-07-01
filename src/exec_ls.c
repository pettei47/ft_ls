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

void print_time(time_t ftime)
{
	int i;
	char *long_string;

	long_string = ctime(&ftime);
	for (i = 4; i < 11; ++i)
		ft_putchar_fd(long_string[i], 1);

  int six_months = ((365 / 2) * 86400);
  if (ftime + six_months > time(NULL))
    for (i = 11; i < 16; ++i)
			ft_putchar_fd(long_string[i], 1);
	else {
		ft_putchar_fd(' ', 1);
		for (i = 20; i < 24; ++i)
			ft_putchar_fd(long_string[i], 1);
	}
}

int max(int a, int b) {
  return a > b ? a : b;
}

bool is_dir(char *path) {
  struct stat *st = (struct stat *)malloc(sizeof(struct stat));
  lstat(path, st);
  bool is_dir = (st->st_mode & S_IFMT) == S_IFDIR;
  free(st);
  return is_dir;
}

void print_file_info(FileInfo **infos, Args *args, bool is_dir) {
  bool long_style = args->long_style;
  bool show_hidden = args->show_hidden;
  bool show_blocks = args->show_blocks;

  if (is_dir && (show_blocks || long_style)) {
    int total_block = 0;
    for (int i = 0; infos[i]; i++) {
      if (infos[i]->path_name[0] == '.' && !show_hidden) {
        continue;
      }
      total_block += infos[i]->num_of_block;
    }
    ft_putstr_fd("total ", 1);
    ft_putnbr_fd(total_block, 1);
    ft_putendl_fd("", 1);
  }

  int max_digit_of_blocks = 0;
  int max_digit_of_hard_links = 0;
  int max_user_name_len = 0;
  int max_group_name_len = 0;
  int max_bytes_len = 0;
  for (int i = 0; infos[i]; i++) {
    if (infos[i]->path_name[0] == '.' && !show_hidden) {
      continue;
    }
    char *num_of_block_str = ft_itoa(infos[i]->num_of_block);
    max_digit_of_blocks = max(max_digit_of_blocks, ft_strlen(num_of_block_str));
    free(num_of_block_str);
    char *num_of_hardlink_str = ft_itoa(infos[i]->num_of_hard_link);
    max_digit_of_hard_links = max(max_digit_of_hard_links, ft_strlen(num_of_hardlink_str));
    free(num_of_hardlink_str);
    max_user_name_len = max(max_user_name_len, ft_strlen(infos[i]->owner_name));
    max_group_name_len = max(max_group_name_len, ft_strlen(infos[i]->group_name));
    char *bytes_str = ft_itoa(infos[i]->bytes);
    max_bytes_len = max(max_bytes_len, ft_strlen(bytes_str));
    free(bytes_str);
  }

  for (int i = 0; infos[i]; i++) {
    if (infos[i]->path_name[0] == '.' && !show_hidden) {
      continue;
    }
    if (show_blocks) {
      print_align_right_number(infos[i]->num_of_block, max_digit_of_blocks);
      ft_putstr_fd(" ", 1);
    }
    if (long_style) {
      ft_putstr_fd(infos[i]->file_mode == S_IFDIR ? "d"
                  : infos[i]->file_mode == S_IFLNK ? "l" : "-", 1);
      ft_putstr_fd(infos[i]->permission, 1);
      ft_putstr_fd(" ", 1);
      print_align_right_number(infos[i]->num_of_hard_link, max_digit_of_hard_links + 1);
      ft_putstr_fd(" ", 1);
      print_align_left(infos[i]->owner_name, max_user_name_len + 1);
      ft_putstr_fd(" ", 1);
      print_align_left(infos[i]->group_name, max_group_name_len + 1);
      ft_putstr_fd(" ", 1);
      print_align_right_number(infos[i]->bytes, max_bytes_len);
      ft_putstr_fd(" ", 1);
      print_time(infos[i]->modified_date);
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


void  exec_ls(char *path, Args *args, bool print_path, bool endline) {
  DIR *dp = opendir(path);

  File *head = (File *)malloc(sizeof(File));
  head->path_name = NULL;
  head->stat = NULL;
  head->next = NULL;

  File *current = head;
  struct dirent *ent;
  while (dp == NULL || (ent = readdir(dp))) {
    char *name = dp == NULL ? path : ent->d_name;
    struct stat *st = (struct stat *)malloc(sizeof(struct stat));
    File *f = (File *)malloc(sizeof(File));

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
    if (dp == NULL) {
      break;
    }
  }

  if (dp != NULL) closedir(dp);

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
    infos[i]->num_of_block = c->stat->st_blocks;
    infos[i]->num_of_hard_link = c->stat->st_nlink;
    infos[i]->modified_mtimespec = c->stat->st_mtimespec;
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
  if (print_path && is_dir(path)) {
    if (endline) {
      ft_putendl_fd("", 1);
    }
    ft_putstr_fd(path, 1);
    ft_putendl_fd(":", 1);
  }
  print_file_info(sorted_infos, args, is_dir(path));

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
      exec_ls(sorted_infos[i]->stat_path, args, true, true);
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
}
