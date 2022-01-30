#include "server.h"
#include "useful.c"
#include "socket.c"


int main(int argc, char **argv)
{
    thisdirectory();
    if (argc == 1)
    {
        init_socket(8080, index_address);
    }
    else if (argc == 3)
        init_socket(argv[1], argv[2]);
    else
        printf("Entra valores válidos, puerto y directorio");

    return 0;
}
