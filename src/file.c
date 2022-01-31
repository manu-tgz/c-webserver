#include <dirent.h>
//Método para abrir archivos, descargar ....etc

//TODO: Abrir archivos
void open(char *address)
{
    DIR *dp;
    struct dirent *dirp;
    dp = opendir(address);

    while ((dirp = readdir(dp)) != NULL)
        printf("%s\n", dirp->d_name);
}

//TODO: Descargar archivos