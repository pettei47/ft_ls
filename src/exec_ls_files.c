#include "ft_ls.h"

static File  *get_files_head(char **files, Args *args) {
  File *head = (File *)malloc(sizeof(File));
  if (!head) {
    return NULL;
  }
  head->path_name = NULL;
  head->stat = NULL;
  head->next = NULL;

  File *current = head;
  for (int i = 0; files[i]; i++) {
    File *f = get_file_stat(args, files[i], NULL, NULL);
    if (!f) {
      free_files(head);
      return NULL;
    }
    current->next = f;
    current = f;
  }
  return head;
}

int exec_ls_files(char **files, Args *args) {
  File *head = get_files_head(files, args);
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
  FileInfo **sorted_infos = sort_infos(
    infos, files_len, args->order_by_modified_time, args->reverse
  );
  if (!sorted_infos) {
    free_file_infos(infos);
    perror("malloc failed");
    return 42;
  }
  print_file_info(sorted_infos, args, false);
  free_file_infos(sorted_infos);
  return 0;
}
