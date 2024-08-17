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
    File *f = get_file_stat(args, files[i], NULL, NULL);
    if (!f) {
      free_files(head);
      perror("malloc failed");
      return 42;
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

  FileInfo **infos = get_file_infos(head, files_len);
  free_files(head);
  if (!infos) {
    perror("malloc failed");
    return 42;
  }

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
