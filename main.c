#include "server.h"
#include "socket.c"

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        init_socket(8080, "/home/emmanuel/Almacenamiento/Test");
    }
    else if (argc == 3)
        init_socket(argv[1], argv[2]);
    else
        printf("Entra valores válidos, puerto y directorio");

    return 0;
}
