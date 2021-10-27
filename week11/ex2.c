#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(void) {
  DIR *dir;
  struct dirent *ent;
  if ((dir = opendir ("/")) != NULL) {
    while ((ent = readdir (dir)) != NULL) {
      printf ("%s\n", ent->d_name);
    }
    closedir (dir);
    return EXIT_SUCCESS;
  } else {
    perror ("");
    return EXIT_FAILURE;
  }
}
