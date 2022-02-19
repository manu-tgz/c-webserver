#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <poll.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <signal.h>
#include <dirent.h>
#include <time.h>
#include "index1.c"
#include "List.c"

void main()
{
    StringList dirName = string_list_init();
    add_to_list(&dirName, "/home/emmanuel/Almacenamiento/Test/Bloque 3.2 Juegos Simples en C - Snake (copia).mkv");
    add_to_list(&dirName, "/home/emmanuel/Almacenamiento/Test/index.html");
    add_to_list(&dirName, "/home/emmanuel/Almacenamiento/Test/10");
    add_to_list(&dirName, "/home/emmanuel/Almacenamiento/Test/image.png");
    

    struct stat dir[4];
    struct stat temp;
    for (size_t i = 0; i < 4; i++)
    {
        stat(dirName.items[i], &temp);
        dir[i] = temp;
    }

    char *field = "size", *name;
    char *order = "dsc";
    int sortData = 1;
 
    int val, index;
    for (int i = 0; i < dirName.count; ++i)
    {
        index = i;
        for (int j = i + 1; j < dirName.count; ++j)
        {
            if (sortData == 0 || strcmp(field, "name") == 0)
                val = strcasecmp(dirName.items[index], dirName.items[j]);
            else if (strcmp(field, "size") == 0)
                val = (dir[index].st_size > dir[j].st_size) - (dir[index].st_size < dir[j].st_size);
            else
                val = (dir[index].st_ctime > dir[j].st_ctime) - (dir[index].st_ctime < dir[j].st_ctime);
            if (sortData == 0 || strcmp(order, "dsc") == 0)
                index = (val <= 0 ? index : j);
            else
                index = (val >= 0 ? index : j);
        }
        temp = dir[index];
        name = dirName.items[index];
        dir[index] = dir[i];
        dirName.items[index] = dirName.items[i];
        dir[i] = temp;
        dirName.items[i] = name;
    }

    print_list_for_shell(&dirName);
}