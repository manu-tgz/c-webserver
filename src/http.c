#include "http_functions.c"

char* commands[] = {
    "GET",
    "POST",
};

void (*Function[])(URI args) = {
    Get,
    Post,
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

