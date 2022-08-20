#pragma once

// ls.h
 // ls command-like
// chang log
// 2022-06-01 K.OHWADA
// slightly modified so that can run on Mac

// original : https://github.com/ohmae/ls

/**
 * @file ls14.c
 *
 * Copyright (c) 2015 大前良介 (OHMAE Ryosuke)
 *
 * This software is released under the MIT License.
 * http://opensource.org/licenses/MIT
 *
 * @brief lsコマンド風のプログラムを作るNo.14
 * 複数のパス指定に対応
 *
 * @author <a href="mailto:ryo@mm2d.net">大前良介 (OHMAE Ryosuke)</a>
 * @date 2015/11/30
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <getopt.h>
#include <sys/stat.h>
//#include <sys/sysmacros.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>


#define major(dev) ((int)(((unsigned int) (dev) >> 8) & 0xff))
#define minor(dev) ((int)((dev) & 0xff))
#define NAME_MAX 255


#define PATH_MAX 4096
#define HALF_YEAR_SECOND (365 * 24 * 60 * 60 / 2)


#ifndef S_IXUGO
#define S_IXUGO (S_IXUSR | S_IXGRP | S_IXOTH)
#endif


/**
 * Policy for displaying hidden files
 */
enum {
  FILTER_DEFAULT, /** display anything other than those starting with '.' */
  FILTER_ALMOST,  /** display '.' and other than '..' */
  FILTER_ALL,     /** show all */
};

/**
 * linked list holding directory names for recursive calls
 */
struct dir_path {
  char path[PATH_MAX + 1];
  int depth;
  struct dir_path *next;
};

/**
 * store file information
 */
struct info {
  char name[NAME_MAX + 1];
  char link[PATH_MAX + 1];
  struct stat stat;
  mode_t link_mode;
  bool link_ok;
};

/**
 * variable-length list containing file information
 */
struct info_list {
  struct info **array;
  int size;
  int used;
};

static void *xmalloc(size_t n);
static void *xrealloc(void *ptr, size_t size);
static struct dir_path *parse_cmd_args(int argc, char**argv);
static void get_mode_string(mode_t mode, char *str);
static void print_type_indicator(mode_t mode);
static void print_user(uid_t uid);
static void print_group(gid_t gid);
static void get_time_string(char *str, time_t time);
static void print_name_with_color(const char *name, mode_t mode, bool link_ok);
static struct dir_path *new_dir_path(const char *path, int depth, struct dir_path *next);
static void init_info_list(struct info_list *list, int size);
static void free_info_list(struct info_list *list);
static void add_info(struct info_list *list, struct info *info);
static struct info *new_info(const char *path, const char *name);
static int compare_name(const void *a, const void *b);
static void sort_list(struct info_list *list);
static void print_info(struct info *info);
static const char *find_filename(const char *path);
static void list_dir(struct dir_path *base);

/**
 * Policy for displaying hidden files
 */
static int filter = FILTER_DEFAULT;

/**
 * display in color
 */
static bool color = false;

/**
 * display characters that indicate attributes
 */
static bool classify = false;

/**
 * display in long format
 */
static bool long_format = false;

/**
 * UNIX time half a year ago
 */
static time_t half_year_ago;

/**
 * recursive display
 */
static bool recursive = false;


/**
 * @brief Exit if malloc result is NULL.
 * @param[IN] size reserve size
 * @retrun pointer to allocated space
 */
static void *xmalloc(size_t n) {
  void *p = malloc(n);
  if (p == NULL) {
    perror("");
    exit(EXIT_FAILURE);
  }
  return p;
}


/**
 * @brief  Exit if realloc result is NULL.
 * @param[IN] ptr region pointer to extend
 * @param[IN] size reserve size
 * @retrun pointer to allocated space
 */
static void *xrealloc(void *ptr, size_t size) {
  void *p = realloc(ptr, size);
  if (p == NULL) {
    perror("");
    exit(EXIT_FAILURE);
  }
  return p;
}


/**
 * @brief parse command line arguments
 * @param[IN] argc number of arguments
 * @param[IN/OUT] argv argument array
 * @return path
 */
static struct dir_path *parse_cmd_args(int argc, char**argv) {
  int opt;
  const struct option longopts[] = {
      { "all", no_argument, NULL, 'a' },
      { "almost-all", no_argument, NULL, 'A' },
      { "color", no_argument, NULL, 'C' },
      { "classify", no_argument, NULL, 'F' },
      { "long-format", no_argument, NULL, 'l' },
      { "recursive", no_argument, NULL, 'R' },
  };
  while ((opt = getopt_long(argc, argv, "aACFlR", longopts, NULL)) != -1) {
    switch (opt) {
      case 'a':
        filter = FILTER_ALL;
        break;
      case 'A':
        filter = FILTER_ALMOST;
        break;
      case 'C':
        if (isatty(STDOUT_FILENO)) {
          color = true;
        }
        break;
      case 'F':
        classify = true;
        break;
      case 'l':
        long_format = true;
        half_year_ago = time(NULL) - HALF_YEAR_SECOND;
        break;
      case 'R':
        recursive = true;
        break;
      default:
        return NULL;
    }
  }
  if (argc <= optind) {
    return new_dir_path("./", 0, NULL);
  } else {
    struct dir_path *head;
    struct dir_path **work = &head;
    int i;
    for (i = optind; i < argc; i++) {
      *work = new_dir_path(argv[i], 0, NULL);
      work = &(*work)->next;
    }
    return head;
  }
}


/**
 * @brief create mode string
 * @param[IN]  mode parameter
 * @param[OUT] str  string destination, specify a buffer of 11 bytes or more
 */
static void get_mode_string(mode_t mode, char *str) {
  str[0] = (S_ISBLK(mode))  ? 'b' :
           (S_ISCHR(mode))  ? 'c' :
           (S_ISDIR(mode))  ? 'd' :
           (S_ISREG(mode))  ? '-' :
           (S_ISFIFO(mode)) ? 'p' :
           (S_ISLNK(mode))  ? 'l' :
           (S_ISSOCK(mode)) ? 's' : '?';
  str[1] = mode & S_IRUSR ? 'r' : '-';
  str[2] = mode & S_IWUSR ? 'w' : '-';
  str[3] = mode & S_ISUID ? (mode & S_IXUSR ? 's' : 'S') : (mode & S_IXUSR ? 'x' : '-');
  str[4] = mode & S_IRGRP ? 'r' : '-';
  str[5] = mode & S_IWGRP ? 'w' : '-';
  str[6] = mode & S_ISGID ? (mode & S_IXGRP ? 's' : 'S') : (mode & S_IXGRP ? 'x' : '-');
  str[7] = mode & S_IROTH ? 'r' : '-';
  str[8] = mode & S_IWOTH ? 'w' : '-';
  str[9] = mode & S_ISVTX ? (mode & S_IXOTH ? 't' : 'T') : (mode & S_IXOTH ? 'x' : '-');
  str[10] = '\0';
}


/**
 * @brief output indicators by file type
 * @param[IN] mode mode parameter
 */
static void print_type_indicator(mode_t mode) {
  if (S_ISREG(mode)) {
    if (mode & S_IXUGO) {
      putchar('*');
    }
  } else {
    if (S_ISDIR(mode)) {
      putchar('/');
    } else if (S_ISLNK(mode)) {
      putchar('@');
    } else if (S_ISFIFO(mode)) {
      putchar('|');
    } else if (S_ISSOCK(mode)) {
      putchar('=');
    }
  }
}


/**
 * @brief Show user name
 * @param[IN] uid User ID
 */
static void print_user(uid_t uid) {
  struct passwd *passwd = getpwuid(uid);
  if (passwd != NULL) {
    printf("%8s ", passwd->pw_name);
  } else {
    printf("%8d ", uid);
  }
}


/**
 * @brief show group name
 * @param[IN] gid Group ID
 */
static void print_group(gid_t gid) {
  struct group *group = getgrgid(gid);
  if (group != NULL) {
    printf("%8s ", group->gr_name);
  } else {
    printf("%8d ", gid);
  }
}


/**
 * @brief create a time display string
* Month-Day Year if more than half a year ago
 * Month-Day Hour:Minute if within six months
 *
 * @param[OUT] str  storage location, specify a buffer of 12 bytes or more
 * @param[IN]  time Unix time to create a string
 */
static void get_time_string(char *str, time_t time) {
  if (time - half_year_ago > 0) {
    strftime(str, 12, "%m/%d %H:%M", localtime(&time));
  } else {
    strftime(str, 12, "%m/%d  %Y", localtime(&time));
  }
}


/**
 * @brief display file names in color
 *
 * @param[IN] name file name
 * @param[IN] mode mode value
 * @param[IN] link_ok false if the destination does not exist
 */
static void print_name_with_color(const char *name, mode_t mode, bool link_ok) {
  if (!link_ok) {
    printf("\033[31m");
  } else if (S_ISREG(mode)) {
    if (mode & S_ISUID) {
      printf("\033[37;41m");
    } else if (mode & S_ISGID) {
      printf("\033[30;43m");
    } else if (mode & S_IXUGO) {
      printf("\033[01;32m");
    } else {
      printf("\033[0m");
    }
  } else if (S_ISDIR(mode)) {
    if ((mode & S_ISVTX) && (mode & S_IWOTH)) {
      printf("\033[30;42m");
    } else if (mode & S_IWOTH) {
      printf("\033[34;42m");
    } else if (mode & S_ISVTX) {
      printf("\033[37;44m");
    } else {
      printf("\033[01;34m");
    }
  } else if (S_ISLNK(mode)) {
    printf("\033[01;36m");
  } else if (S_ISFIFO(mode)) {
    printf("\033[33m");
  } else if (S_ISSOCK(mode)) {
    printf("\033[01;35m");
  } else if (S_ISBLK(mode)) {
    printf("\033[01;33m");
  } else if (S_ISCHR(mode)) {
    printf("\033[01;33m");
  }
  printf("%s", name);
  printf("\033[0m");
}


/**
 * @brief struct subdir no fakutorīmesoddo
Factory method for struct subdir
 * @param[IN] path 
 * @param[IN] depth 
 * @param[IN] next pointer to the next element
 * @return struct pointer to subdir
 */
static struct dir_path *new_dir_path(const char *path, int depth, struct dir_path *next) {
  struct dir_path *s = xmalloc(sizeof(struct dir_path));
  if (path != NULL) {
    strncpy(s->path, path, sizeof(s->path));
  }
  s->depth = depth;
  s->next = next;
  return s;
}


/**
 * @brief initialize a variable length list
 * @param[OUT] list structure to initialize
 * @param[IN] size initial size
 */
static void init_info_list(struct info_list *list, int size) {
  list->array = xmalloc(sizeof(struct info*) * size);
  list->size = size;
  list->used = 0;
}


/**
 * @brief free memory in variable length list
 * release information registered in the list as well.
 *
 * @param[IN] list structure to release
 */
static void free_info_list(struct info_list *list) {
  int i;
  for (i = 0; i < list->used; i++) {
    free(list->array[i]);
  }
  free(list->array);
}


/**
 * @brief store information in a variable length list
 * expand if there is no storage location
 *
 * @param[IN/OUT] list destination structure
 * @param[IN] info data to store
 */
static void add_info(struct info_list *list, struct info *info) {
  if (list->size == list->used) {
    list->size = list->size * 2;
    list->array = xrealloc(list->array, sizeof(struct info*) * list->size);
  }
  list->array[list->used] = info;
  list->used++;
}


/**
 * @brief factory method for entry information structure
 * executes from allocating memory to storing each information of the specified path
 *
 * @param[IN] path entry path
 * @param[IN] name entry name
 * @return entry information structure
 */
static struct info *new_info(const char *path, const char *name) {
  struct info *info = xmalloc(sizeof(struct info));
  strncpy(info->name, name, NAME_MAX + 1);
  if (lstat(path, &info->stat) != 0) {
    perror(path);
    free(info);
    return NULL;
  }
  info->link_ok = false;
  info->link[0] = 0;
  info->link_mode = 0;
  if (S_ISLNK(info->stat.st_mode)) {
    struct stat link_stat;
    int link_len = readlink(path, info->link, PATH_MAX);
    if (link_len > 0) {
      info->link[link_len] = 0;
    }
    if (stat(path, &link_stat) == 0) {
      info->link_ok = true;
      info->link_mode = link_stat.st_mode;
    }
  } else {
    info->link_ok = true;
  }
  return info;
}


/**
 * @brief file name comparison for sorting
 * @param[IN] a
 * @param[IN] b
 * @return positive if a>b, 0 if a==b, negative if a<b
 */
static int compare_name(const void *a, const void *b) {
  struct info *ai = *(struct info**)a;
  struct info *bi = *(struct info**)b;
  if (S_ISDIR(ai->stat.st_mode) && !S_ISDIR(bi->stat.st_mode)) {
    return -1;
  }
  if (!S_ISDIR(ai->stat.st_mode) && S_ISDIR(bi->stat.st_mode)) {
    return 1;
  }
  return strcmp(ai->name, bi->name);
}


/**
 * @brief sort in list
 * @param[IN/OUT] the list to be sorted
 */
static void sort_list(struct info_list *list) {
  qsort(list->array, list->used, sizeof(struct info*), compare_name);
}


/**
 * @brief display information based on entry information
 * @param[IN] Information to display
 */
static void print_info(struct info *info) {
  if (long_format) {
    char buf[12];
    get_mode_string(info->stat.st_mode, buf);
    printf("%s ", buf);
    printf("%3d ", (int)info->stat.st_nlink);
    print_user(info->stat.st_uid);
    print_group(info->stat.st_gid);
    if (S_ISCHR(info->stat.st_mode) || S_ISBLK(info->stat.st_mode)) {
      printf("%4d,%4d ", major(info->stat.st_rdev),
             minor(info->stat.st_rdev));
    } else {
      printf("%9lld ", info->stat.st_size);
    }

    // get_time_string(buf, info->stat.st_mtim.tv_sec);
    get_time_string(buf, info->stat.st_mtime);

    printf("%s ", buf);
  }
  if (color) {
    print_name_with_color(info->name, info->stat.st_mode, info->link_ok);
  } else {
    printf("%s", info->name);
  }
  if (classify) {
    print_type_indicator(info->stat.st_mode);
  }
  if (long_format) {
    if (info->link[0] != 0) {
      printf(" -> ");
      if (color) {
        print_name_with_color(info->link, info->link_mode, info->link_ok);
      } else {
        printf("%s", info->link);
      }
    }
  }
  putchar('\n');
}


/**
 * @brief 
extract filename from pathname
 * @param[IN] path pathname
 * @return 
pointer to file name in path name
 */
static const char *find_filename(const char *path) {
  int i;
  size_t path_len = strlen(path);
  for (i = path_len;i >= 0; i--) {
    if (path[i] == '/') {
      return &path[i+1];
    }
  }
  return path;
}


/**
 * @brief ist directory entries for the given path
 * @param[IN] base path
 */
static void list_dir(struct dir_path *base) {
  const char *base_path = base->path;
  int i;
  DIR *dir;
  struct dirent *dent;
  char path[PATH_MAX + 1];
  size_t path_len;
  struct info_list list;
  struct dir_path *subque = base;
  dir = opendir(base_path);
  if (dir == NULL) {
    if (errno == ENOTDIR) {
      const char *name = find_filename(base_path);
      struct info *info = new_info(base_path, name);
      if (info != NULL) {
        print_info(info);
        free(info);
      }
    } else {
      perror(base_path);
    }
    return;
  }
  path_len = strlen(base_path);
  if (path_len >= PATH_MAX - 1) {
    fprintf(stderr, "too long path\n");
    return;
  }
  strncpy(path, base_path, PATH_MAX);
  if (path[path_len - 1] != '/') {
    path[path_len] = '/';
    path_len++;
    path[path_len] = '\0';
  }
  init_info_list(&list, 100);
  while ((dent = readdir(dir)) != NULL) {
    struct info *info;
    const char *name = dent->d_name;
    if (filter != FILTER_ALL
        && name[0] == '.'
        && (filter == FILTER_DEFAULT
            || name[1 + (name[1] == '.')] == '\0')) {
      continue;
    }
    strncpy(&path[path_len], dent->d_name, PATH_MAX - path_len);
    info = new_info(path, name);
    if (info == NULL) {
      continue;
    }
    add_info(&list, info);
  }
  closedir(dir);
  sort_list(&list);
  for (i = 0; i < list.used; i++) {
    struct info *info = list.array[i];
    if (recursive && S_ISDIR(info->stat.st_mode)) {
      const char *name = info->name;
      if (!(name[0] == '.'
          && name[1 + (name[1] == '.')] == '\0')) {
        strncpy(&path[path_len], name, PATH_MAX - path_len);
        subque->next = new_dir_path(path, base->depth + 1, subque->next);
        subque = subque->next;
      }
    }
    print_info(info);
  }
  free_info_list(&list);
}

