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

  time_t six_months = ((365 / 2) * 86400);
  time_t now = time(NULL);
  if (ftime < now && now < ftime + six_months)
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
