char *address;

// #include "http.c"
#define BUFFER_SIZE 200
#define BACKLOG 10

int listen_socket, client_socket;  //Socket escuchar y para el cliente
int port;

struct sockaddr_in server_addr;
struct sockaddr_storage client_address;

socklen_t addr_size;

//Clientes 
int count, max;
fd_set fd_read;
int client_sockets[20];

//Asignar puerto y dirección donde se va ejecutar el servidor
void assign_port_address(int Port, char *Address)
{
    //TODO: Parche de rango de puerto.
    port = Port;
    printf("REV-Server: Listening in port: %d \n", port);

    if (chdir(Address) == -1)
        perror("REV-Server: Error:");
    else
    {
        address = Address;
        printf("REV-Server: Serving Directory: %s \n", address);
    }
}

//Crear el sockect
void createsocket()
{
    listen_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_socket == -1) // Crea la conexión y devuelve fd
        perror("REV-Server: Crear socket - ");

    /*SO_REUSEADDR si es true la dirección puede estar utilizada por otro socket o 
    está en TIME_WAIT
    Entonces con esto nos permite usar esa dirección */
    if ((setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR, &True,
                    sizeof(int))) < 0)
    {
        close(listen_socket);
        perror("REV-Server: setsockopt - ");
    }
}

void bind_listen_socket()
{
    bzero(&server_addr, sizeof(server_addr));        // Inicializa la estructura
    server_addr.sin_family = AF_INET;                // Establecer familia de direcciones
    server_addr.sin_port = htons(port);              // Establecer el puerto
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // Establecer dirección

    /*Asocia el socket a la dirección server_addr*/
    if (bind(listen_socket, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) < 0)
    {
        close(listen_socket);
        perror("REV-Server: bind:");
    }

    //Inicial el listen
    //especifica que el socket desea recibir conexiones
    if (listen(listen_socket, BACKLOG) < 0)
    {
        close(listen_socket);
        perror("REV-Server: listen:");
    }
}

/*
Aceptar peticiones en el puerto
*/
void accept_connection()
{
    addr_size = sizeof(client_address);
    // Acepta peticiones del navegador u otro cliente.
    client_socket = accept(listen_socket, (struct sockaddr *)&client_address, &addr_size);
    
    addClient( client_socket);
    
}
void addClient(int connctfd)
{
    client_sockets[count] = connctfd;
    count++;
}
void DeleteClient(int client)
{
    close(client_sockets[client]);
    client_sockets[client] = -1;
}

StringList parse;

void handle_http(int socket)
{
    if (recv_request(socket) < 0)
	{
		perror("REV-Server: Receive");
		exit(-1);
	}

}

int  recv_request(int socket)
{
	char buffer[BUFFER_SIZE];
	memset(buffer,'\0', BUFFER_SIZE);

	if (recv(socket, buffer, BUFFER_SIZE, 0) == -1)
	{
		perror("REV-Server: Request");
		return -1;
	}
    //Agregar mensaje a la lista
    printf("%s", buffer);
    parse = string_list_init();
	add_line_to_list(&parse,buffer);

	printf("\n\n");
 
return 1;
}
/*
 * Función que devuelve el valor máximo en el array.
 * Supone que los valores válidos de el array son positivos y mayores que 0.
 * Devuelve 0 si n es 0 o el array es NULL */
int Max (int *array, int n)
{
	int i;
	int max;

	if ((array == NULL) || (n<1))
		return 0;
		
	max = array[0];
	for (i=0; i<n; i++)
		if (array[i] > max)
			max = array[i];

	return max;
}
void initialize()
{   
    count=0;
    /* Se inicializa descriptoresLectura */
    FD_ZERO(&fd_read);
}

void init_socket(int Port, char *Address)
{
    assign_port_address(Port, Address);
    createsocket();
    bind_listen_socket();
    initialize();
}
