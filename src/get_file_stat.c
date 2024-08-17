#include "ft_ls.h"

File  *get_file_stat(Args *args, char *path, DIR *dp, struct dirent *ent) {
  char *name = dp == NULL ? path : ent->d_name;
  File *f = (File *)malloc(sizeof(File));
  if (!f) {
    return NULL;
  }
  f->stat = (struct stat *)malloc(sizeof(struct stat));
  if (!f->stat) {
    free(f);
    return NULL;
  }
  f->next = NULL;
  f->stat_path = dp == NULL ? ft_strdup(path) : get_stat_path(path, ent->d_name);
  if (!f->stat_path) {
    free(f->stat);
    free(f);
    return NULL;
  }
  lstat(f->stat_path, f->stat);
  if (args->long_style && (f->stat->st_mode & S_IFMT) == S_IFLNK) {
    char *link_buf = (char *)malloc(PATH_MAX);
    if (!link_buf) {
      free(f->stat_path);
      free(f->stat);
      free(f);
      return NULL;
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
      return NULL;
    }
    free(link_from);
  } else {
    f->path_name = ft_strdup(name);
    if (!f->path_name) {
      free(f->stat_path);
      free(f->stat);
      free(f);
      return NULL;
    }
  }
  return f;
}
