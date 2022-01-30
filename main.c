#include "server.h"
#include "socket.c"



int main(int argc, char **argv)
{
    //TODO: Descomentar la línea siguiente y borrar la otra
    //init_socket(argv[1],argv[2]);
    init_socket(8080, "/home/kuhaku/Desktop/Server");
    return 0;
}
