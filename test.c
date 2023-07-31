#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

#define PATH_MAX 100

void listFilesAndDirectories(const char *path) {
    struct dirent *entry;
    struct stat fileStat;
    DIR *dir = opendir(path);

    if (dir == NULL) {
        perror("Unable to open directory");
        return;
    }
    printf("%d\n", dir->__dd_len);
    while ((entry = readdir(dir)) != NULL) {
        char fullpath[PATH_MAX];
        snprintf(fullpath, PATH_MAX, "%s/%s", path, entry->d_name);
        printf("%s\n", fullpath);
        if (lstat(fullpath, &fileStat) == -1) {
            perror("lstat");
            continue;
        }

        if (S_ISDIR(fileStat.st_mode)) {
            // It's a directory
            printf("[Directory] %s\n", entry->d_name);
        } else if (S_ISREG(fileStat.st_mode)) {
            // It's a regular file
            printf("[File] %s\n", entry->d_name);
        }
        // You can also check for other file types using S_ISLNK, S_ISCHR, S_ISBLK, S_ISFIFO, S_ISSOCK macros if needed.
    }

    closedir(dir);
}

int isMatch(char *pattern, char *text) {
    if (*pattern == '\0' && *text == '\0')
        return 1;
    if (*pattern == '\0')
        return 0;
    if (*pattern == '*') {
        while (*(pattern + 1) == '*')
            pattern++;
        return isMatch(pattern + 1, text) || (*text != '\0' && isMatch(pattern, text + 1));
    } else if (*pattern == *text)
        return isMatch(pattern + 1, text + 1);
    return 0;
}

                // "baaabab"

                // "*****ba*****ab"
                // "ba*****ab"
                // "ba*ab"
                // "a*ab"
                // "a*****ab"
                // "*a*****ab"
                // "ba*ab****"
                // "****"
                // "*"
                // "aa?ab"
                // "b*b"
                // "a*a"
                // "baaabab"
                // "?baaabab"
                // "*baaaba*"

// int pattern_match(char *text, char *pattern)
// {
//     return 0;
// }

int main(int argc, char **argv) {
    const char *currentDir = "."; // You can replace this with any desired directory path.

    printf("Files and Directories in %s:\n", currentDir);
    listFilesAndDirectories(currentDir);

    //printf("%d\n", isMatch(argv[1], argv[2]));
    return 0;
}