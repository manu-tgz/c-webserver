#include "server.h"
#include "socket.c"
#include "http.c"

int main(int argc, char **argv)
{
    signal(SIGPIPE, SIG_IGN);

    // if (argc != 2)
    // {
    //     init_socket((int)strtol(argv[1], NULL, 10), argv[2]);
    // }
    
    init_socket(8000, "/home/emmanuel/Almacenamiento");
    while (True)
    {
        int pid;
        //TODO: Terminar el select()

        /* Se añade para select() el socket servidor */
        // FD_SET(listen_socket, &fd_read);

        // max = Max(client_sockets, count);

        // if (max < listen_socket)
        //     max = listen_socket;

        // select (max + 1, &fd_read, NULL, NULL, NULL);
        accept_connection();

        if ((pid = fork()) == -1)
        {
            close(client_socket);
        }
        else if (pid == 0)
        {
            if (client_socket < 0)
            {
                perror("REV-Server: Accepting sockets");
                exit(-1);
            }
            // Trabaja con la petición
            handle_http(client_socket);
            http(parse);
            close(client_socket);
            exit(0);
        }
    }
}
