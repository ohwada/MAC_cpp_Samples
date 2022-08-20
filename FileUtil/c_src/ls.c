/**
 *  ls.c
 * ls command-like
 * 2022-06-01 K.OHWADA
 */

//  gcc ls.c -Wall -o ls

// original : https://github.com/ohmae/ls

#include "ls.h"


/**
 *  main
 */
int main(int argc, char**argv) 
{
  struct dir_path *head = parse_cmd_args(argc, argv);
  if (head == NULL) {
    return EXIT_FAILURE;
  }

  while(head != NULL) 
{
    if (head->depth != 0) {
      printf("\n%s:\n", head->path);
    }
    list_dir(head);
    struct dir_path *tmp = head;
    head = head->next;
    free(tmp);
} // while

  return EXIT_SUCCESS;
}

