//FIXME: include de file
#include "file.c"
#include "http.c"
#define BUFFER_SIZE 200

StringList parse;

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
    
    parse = string_list_init();
	add_line_to_list(&parse,buffer);
	print_list_for_shell(&parse);
	printf("\n");
	
	URI uri = Uri_init(buffer);
	print_uri(&uri);
	http(parse);
	int a = 0;
    //TODO:imprimir peticiones de navegadores
   
return 1;
}

