#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    struct stat fileStat;

    if(argc != 2) {
        printf("Usage: %s <pathname>\n", argv[0]);
        return 1;
    }

    if(stat(argv[1],&fileStat) < 0) {
        perror("stat");
        return 1;
    }

    printf("Information for %s\n",argv[1]);
    printf("---------------------------\n");
    printf("File Inode: \t\t%ld\n",fileStat.st_ino);

    printf("File Type: \t\t");
    if(S_ISREG(fileStat.st_mode)) printf("Regular File\n");
    else if(S_ISDIR(fileStat.st_mode)) printf("Directory\n");
    else printf("Other\n");

    return 0;
