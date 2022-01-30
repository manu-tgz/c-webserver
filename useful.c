#include <assert.h>
char *pwd();
char *strcpy_init(int lengh, char *address);

char *pwd()
{
    long n;
    char *buf;

    n = pathconf(".", _PC_PATH_MAX);
    assert(n != -1);
    buf = malloc(n * sizeof(*buf));
    assert(buf);
    if (getcwd(buf, n) == NULL)
    {
        perror("getcwd");
        exit(EXIT_FAILURE);
    }
    return buf;
}
//Obtener la direccion del index.html
void thisdirectory()
{
    char *buf = pwd();
    index_address = strcpy_init(strlen(buf) + strlen(Index), buf);
    strcat(index_address, Index);
    free(buf);
}
//Se diferencia con strcpy este crea el string inicial
char *strcpy_init(int lengh, char *address)
{
    char *s = (char *)malloc((lengh) * sizeof(char));
    strcpy(s, address);
    return s;
}