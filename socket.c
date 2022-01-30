char *address;
#include "handle_http.c"

#define BACKLOG 10



int current_socket;
int port, True;
struct sockaddr_in server_addr;
struct sockaddr_storage client_address;
socklen_t addr_size;

void assign_port_address(int Port, char *Address)
{
    //TODO: Parche de rango de puerto.
    port = Port;
    printf("Listening in port: %d \n", port);

    if (chdir(Address) == -1)
        perror("Error:");
    else
    {
        address = Address;
        printf("Serving Directory: %s \n", address);
    }
}

void createsocket()
{
    current_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (current_socket == -1) // Crea la conexión y devuelve fd
        perror("Server: Crear socket - ");

    /* @SO_REUSEADDR si es true la dirección puede estar utilizada por otro socket o 
    está en TIME_WAIT
    Entonces con esto nos permite usar esa dirección */
    if ((setsockopt(current_socket, SOL_SOCKET, SO_REUSEADDR, &True,
                    sizeof(int))) < 0)
    {
        close(current_socket);
        perror("setsockopt");
    }
}

void bind_listen_socket()
{
    bzero(&server_addr, sizeof(server_addr));        // Inicializa la estructura
    server_addr.sin_family = AF_INET;                // Establecer familia de direcciones
    server_addr.sin_port = htons(port);              // Establecer el puerto
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // Establecer dirección

    /*Asocia el socket a la dirección server_addr*/
    if (bind(current_socket, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) < 0)
    {
        close(current_socket);
        perror("Server bind:");
    }

    //Inicial el listen
    //especifica que el socket desea recibir conexiones
    if (listen(current_socket, BACKLOG) < 0)
    {
        close(current_socket);
        perror("Server listen:");
    }
}

/*
Aceptar peticiones en el puerto
*/
void accept_connection_and_response()
{
    while (True)
    {
        int pid;
        addr_size = sizeof(client_address);
        //Acepta peticiones del navegador u otro cliente.
        new_socket = accept(current_socket, (struct sockaddr *)&client_address, &addr_size);

        // if ((pid = fork()) == -1)
        // {
        //     close(new_socket);
        // }
        // else if (pid == 0)
        // {
            if (new_socket < 0)
            {
                perror("Accepting sockets");
                exit(-1);
            }
            //Trabaja con la petición
            handle_http(new_socket);
            close(new_socket);
            exit(0);
        // }
    }
}

void init_socket(int Port, char *Address)
{
    assign_port_address(Port, Address);
    True = 1;
    createsocket();
    bind_listen_socket();
    accept_connection_and_response();
}
