/*
Contien todos los metodos del protocolo http implementados
*/

#include "http_response.c"

char* commands[] = {
    "GET",
};

void (*Function[])(URI args) = {
    Get,
    0
};

//Selecciona el controlador
void http (StringList list,URI uri)
{
    char* command = get_and_delete_from_list(&list,0);
    int a = 0;   
    for (int i = 0; i < 5; i++)
        if(strcmp(command,commands[i])== 0)
        {
            Function[i](uri);
            return;
        }

    //TODO: Enviar al cliente
    printf ("501 Not Implemented\n");
}

//Comando Get
void Get(URI uri)
{
	//Concat address y archivo
	char *url = strcpy_init(strlen(uri.path) + strlen(address), address,uri.path);
    
	FILE *fp = open_file(url, "rb");

	int contentLength = Content_Lenght(fp);

	char *ext = get_ext(url);

	if (check_mime(ext) != -1)
	{
		sendHeader("200 OK", mime, contentLength, new_socket);
		sendFile(fp, contentLength);
	}
	else
	{
		sendString("400 Bad Request\n", new_socket);
	}
	fclose(fp);
}