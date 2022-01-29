//FIXME: include de file
#include "file.c"

#define BUFFER_SIZE 200
void handle_http(int socket)
{
    if (recv_request(socket) < 0)
	{
		perror("Receive");
		exit(-1);
	}
}

int  recv_request(int socket)
{
	char buffer[BUFFER_SIZE];
	memset(buffer,'\0', BUFFER_SIZE);

	if (recv(socket, buffer, BUFFER_SIZE, 0) == -1)
	{
		perror("Request");
		return -1;
	}
    
    printf("\n%s",buffer);
    //TODO:imprimir peticiones de navegadores
   
return 1;
}

