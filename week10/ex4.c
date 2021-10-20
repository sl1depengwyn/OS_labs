#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/dir.h>

int filter(const struct dirent* entry) {
    struct stat dir_entry_stat;
    stat(entry->d_name, &dir_entry_stat);
    if (dir_entry_stat.st_nlink > 1) {
        return 1;
    }
    return 0;
}

int main() {

    struct dirent **dir_entries;

    int n = scandir(".", &dir_entries, filter, NULL);

    if (n == -1) {
        return EXIT_FAILURE;
    }

    DIR *directory = opendir(".");
    if (directory == NULL) {
        return EXIT_FAILURE;
    }

    struct dirent* dir_entry;

    long already_printed[n];

    for (int i = 0; i < n; ++i) {
        already_printed[i] = 0;
    }

    for (int i = 0; i < n; ++i) {
	int is_printed = 0;
	for (int j = 0; j < i; ++j) {
	    if (dir_entries[i]->d_ino == already_printed[j]) {
		is_printed = 1;
		break;
	    }
	}
	if (is_printed == 1) {
	    continue;
	}
	already_printed[i] = dir_entries[i]->d_ino;
        while ((dir_entry = readdir(directory)) != NULL) {
            if (dir_entries[i]->d_ino == dir_entry->d_ino) {
                printf("%s ", dir_entry->d_name);
            }
        }
        printf("\n");
	rewinddir(directory);
    }

    return EXIT_SUCCESS;
}

