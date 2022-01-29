#include "socket.c"

int main(int argc, char **argv)
{
    close(8080);
    init_socket(8080, "/home/emmanuel/Almacenamiento/Test/");

    return 0;
}
