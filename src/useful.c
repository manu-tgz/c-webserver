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
    index_address= (char *)malloc((strlen(buf) + strlen(Index)-4) * sizeof(char));
    strncpy(index_address, buf,strlen(buf)-4);
    strcat(index_address, Index);
    free(buf);

    printf("%s",index_address);
}

//Concatena dos string y los guarda en un string del tamaño especificado
char *strcpy_init(int lengh, char *s1 , char* s2)
{
    char *result = (char *)malloc((lengh) * sizeof(char));
    sprintf(result, "%s%s", s1, s2);
    return result;
}
