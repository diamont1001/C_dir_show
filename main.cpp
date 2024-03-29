#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

void printdir(char *dir, int depth)
{
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;

    if((dp = opendir(dir)) == NULL) {
        fprintf(stderr, "connot open directory: %s\n",dir);
        return ;
    }
    chdir(dir); //the same as comand"cd"
    while((entry = readdir(dp)) != NULL) {
        stat(entry->d_name, &statbuf);  //lstat(entry->d_name, &statbuf);
        if(S_ISDIR(statbuf.st_mode)) {
            //Found a directory, but ignore. and ..
            if(strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
                continue;
            printf("%*s%s/\n", depth, "", entry->d_name);
            //Recurse at a new indent level
            printdir(entry->d_name, depth + 4);
        }
        //else printf("%*s%s\n", depth, "", entry->d_name);
    }
    chdir("..");
    closedir(dp);
}

int main(int argc, char *argv[])
{
    char *topdir, pwd[] = "..";
    if(argc != 2)
        topdir = pwd;
    else
        topdir = argv[1];

    printf("Directory scan of %s\n", topdir);
    printdir(topdir, 0);
    printf("done.\n");

    return 0;
}
