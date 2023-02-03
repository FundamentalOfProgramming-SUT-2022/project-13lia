#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#include "tls.h"
#include "plotter.h"

const int PADDING = 2;

int main(int argc, char *argv[])
{
    Options options;
    options.recursionDepth = 0;
    options.all = false;

    if (parseOptions(argc, argv, &options) != 0)
        return -1;

    printf("%s\n", options.path);

    run(options.path, 0, &options);

    return 0;
}

int parseOptions(int argc, char *argv[], Options *options)
{

    options->recursionDepth = 0;
    options->all = true;
    strcpy(options->path, argv[argc-1]);

    return 0;
}

void run(char *path, int depth, Options *options)
{
    DIR *dir;
    struct dirent *dentry;
    struct stat fileStat;

    if ((dir = opendir(path)) == NULL)
        return;

    while (1)
    {
        dentry = readdir(dir);
        if (dentry == NULL)
            break;

        if (dentry->d_name[0] == '.')
        {
            if (options->all == true)
                printLine(dentry->d_name, depth, 1);

            continue;
        }

        char currentFilePath[strlen(path) + strlen(dentry->d_name + 2)];
        strcpy(currentFilePath, path);
        strcat(currentFilePath, "/");
        strcat(currentFilePath, dentry->d_name);

        stat(currentFilePath, &fileStat);

        if (S_ISDIR(fileStat.st_mode))
        {
            printLine(dentry->d_name, depth, 1);

            if (depth <= options->recursionDepth || options->recursionDepth == 0)
                run(currentFilePath, depth + PADDING, options);
        }
        else
        {
            printLine(dentry->d_name, depth, 0);
        }
    }
    closedir(dir);
}