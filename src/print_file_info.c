#include "ft_ls.h"

static void print_time(time_t ftime)
{
	int i;
	char *long_string;

	long_string = ctime(&ftime);
	for (i = 4; i < 11; ++i)
		ft_putchar_fd(long_string[i], 1);

  time_t revolution_period = (365 * 86400) + (5 * 3600) + (48 * 60) + 46;
  time_t half_year = revolution_period / 2;
  time_t now = time(NULL);
  if (ftime < now && now < ftime + half_year)
    for (i = 11; i < 16; ++i)
			ft_putchar_fd(long_string[i], 1);
	else {
		ft_putchar_fd(' ', 1);
		for (i = 20; i < 24; ++i)
			ft_putchar_fd(long_string[i], 1);
	}
}

static int max(int a, int b) {
  return a > b ? a : b;
}

static int *calc_max_digits(FileInfo **infos, bool show_hidden) {
  int max_digit_of_blocks = 0;
  int max_digit_of_hard_links = 0;
  int max_user_name_len = 0;
  int max_group_name_len = 0;
  int max_bytes_len = 0;
  for (int i = 0; infos[i]; i++) {
    if (infos[i]->path_name[0] == '.' && !show_hidden) continue;
    char *num_of_block_str = ft_itoa(infos[i]->num_of_block);
    char *num_of_hardlink_str = ft_itoa(infos[i]->num_of_hard_link);
    char *bytes_str = ft_itoa(infos[i]->bytes);
    if (!num_of_block_str || !num_of_hardlink_str || !bytes_str) {
      free(num_of_block_str);
      free(num_of_hardlink_str);
      free(bytes_str);
      return NULL;
    }
    max_digit_of_blocks = max(max_digit_of_blocks, ft_strlen(num_of_block_str));
    max_digit_of_hard_links = max(max_digit_of_hard_links, ft_strlen(num_of_hardlink_str));
    max_user_name_len = max(max_user_name_len, ft_strlen(infos[i]->owner_name));
    max_group_name_len = max(max_group_name_len, ft_strlen(infos[i]->group_name));
    max_bytes_len = max(max_bytes_len, ft_strlen(bytes_str));
    free(num_of_block_str);
    free(num_of_hardlink_str);
    free(bytes_str);
  }
  int *max_digits = malloc(sizeof(int) * 5);
  if (!max_digits) return NULL;
  max_digits[0] = max_digit_of_blocks;
  max_digits[1] = max_digit_of_hard_links;
  max_digits[2] = max_user_name_len;
  max_digits[3] = max_group_name_len;
  max_digits[4] = max_bytes_len;
  return max_digits;
}

static void print_total_block_size(FileInfo **infos, Args *args, bool is_dir) {
  if (is_dir && (args->show_blocks || args->long_style)) {
    int total_block = 0;
    for (int i = 0; infos[i]; i++) {
      if (infos[i]->path_name[0] == '.' && !args->show_hidden) {
        continue;
      }
      total_block += infos[i]->num_of_block;
    }
    ft_putstr_fd("total ", 1);
    ft_putnbr_fd(total_block, 1);
    ft_putendl_fd("", 1);
  }
}

static int print_block_size(FileInfo **infos, Args *args, int i, int max_digit_of_blocks) {
  if (args->show_blocks) {
    char *num_of_block_str = ft_itoa(infos[i]->num_of_block);
    if (!num_of_block_str) {
      return 42;
    }
    print_align_right(num_of_block_str, max_digit_of_blocks);
    free(num_of_block_str);
    ft_putstr_fd(" ", 1);
  }
  return 0;
}

static int print_long_style(FileInfo **infos, Args *args, int i, int *max_digits) {
  int max_digit_of_hard_links = max_digits[1];
  int max_user_name_len = max_digits[2];
  int max_group_name_len = max_digits[3];
  int max_bytes_len = max_digits[4];
  if (args->long_style) {
    char *num_of_hard_link_str = ft_itoa(infos[i]->num_of_hard_link);
    char *bytes_str = ft_itoa(infos[i]->bytes);
    if (!num_of_hard_link_str || !bytes_str) {
      free(num_of_hard_link_str);
      free(bytes_str);
      return 42;
    }
    ft_putstr_fd(infos[i]->file_mode == S_IFDIR ? "d"
                : infos[i]->file_mode == S_IFLNK ? "l" : "-", 1);
    ft_putstr_fd(infos[i]->permission, 1);
    ft_putstr_fd(" ", 1);
    print_align_right(num_of_hard_link_str, max_digit_of_hard_links);
    ft_putstr_fd(" ", 1);
    print_align_left(infos[i]->owner_name, max_user_name_len);
    ft_putstr_fd(" ", 1);
    print_align_left(infos[i]->group_name, max_group_name_len);
    ft_putstr_fd(" ", 1);
    print_align_right(bytes_str, max_bytes_len);
    ft_putstr_fd(" ", 1);
    print_time(infos[i]->modified_date_sec);
    ft_putstr_fd(" ", 1);
    free(num_of_hard_link_str);
    free(bytes_str);
  }
  return 0;
}

int print_file_info(FileInfo **infos, Args *args, bool is_dir) {
  print_total_block_size(infos, args, is_dir);
  int *max_digits = calc_max_digits(infos, args->show_hidden);
  if (!max_digits) {
    perror("malloc failed");
    return 42;
  }
  for (int i = 0; infos[i]; i++) {
    if (infos[i]->path_name[0] == '.' && !args->show_hidden) continue;
    int print_block_size_result = print_block_size(infos, args, i, max_digits[0]);
    if (print_block_size_result == 42) {
      free(max_digits);
      perror("malloc failed");
      return 42;
    }
    int print_long_style_result = print_long_style(infos, args, i, max_digits);
    if (print_long_style_result == 42) {
      free(max_digits);
      perror("malloc failed");
      return 42;
    }
    ft_putendl_fd(infos[i]->path_name, 1);
  }
  free(max_digits);
  return 0;
}
