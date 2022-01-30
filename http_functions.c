#include <sys/socket.h>
#define SEEK_END 2	/* Seek from end of file.  */
#include "mimes.c"

sendString(char *message, int socket)
{
	int length, bytes_sent;
	length = strlen(message);

	bytes_sent = send(socket, message, length, 0);

	return bytes_sent;
}


void sendHeader(char *Status_code, char *Content_Type, int TotalSize, int socket)
{
	char *head = "\r\nHTTP/1.1 ";
	char *content_head = "\r\nContent-Type: ";
	char *server_head = "\r\nServer: PT06";
	char *length_head = "\r\nContent-Length: ";
	char *date_head = "\r\nDate: ";
	char *newline = "\r\n";
	char contentLength[100];

	time_t rawtime;
	time(&rawtime);

	sprintf(contentLength, "%i", TotalSize);

	char *message = malloc((
							   strlen(head) +
							   strlen(content_head) +
							   strlen(server_head) +
							   strlen(length_head) +
							   strlen(date_head) +
							   strlen(newline) +
							   strlen(Status_code) +
							   strlen(Content_Type) +
							   strlen(contentLength) +
							   28 +
							   sizeof(char)) *
						   2);

	if (message != NULL)
	{
		strcpy(message, head);
		strcat(message, Status_code);
		strcat(message, content_head);
		strcat(message, Content_Type);
		strcat(message, server_head);
		strcat(message, length_head);
		strcat(message, contentLength);
		strcat(message, date_head);
		strcat(message, (char *)ctime(&rawtime));
		strcat(message, newline);

		sendString(message, socket);

		free(message);
	}
}

int sendBinary(int *byte, int length)
{
	int bytes_sent;
	bytes_sent = send(new_socket, byte, length, 0);

	return bytes_sent;


	return 0;
}

<<<<<<< HEAD
//Encviar archivo por binarios
=======
>>>>>>> aad40a529fcbc6e7fb003af5625d4ee700c67ad1
void sendFile(FILE *fp, int file_size)
{
	int current_char = 0;

	do{
		current_char = fgetc(fp);
		sendBinary(&current_char, sizeof(char));
	}
	while(current_char != EOF);
}
//Devuelve el largo del archivo
int Content_Lenght(FILE *fp)
{
	int filesize = 0;

	fseek(fp, 0, SEEK_END);
	filesize = ftell(fp);
	rewind(fp);

	return filesize;
}

char* get_ext(char item []);

void Get(StringList list)
{
    //Concat address y archivo
    int temp =strlen(list.items[0])+ strlen(address);
    char* url = (char*)malloc(temp*sizeof(char));
    strcpy(url, address);
    strcat(url, list.items[0]);

    //TODO: Cambiar a funciones del proyecto
    FILE *fp = fopen(url, "rb");

    if (fp == NULL)
    {
        sendString("400 Bad Request\n", new_socket);
        printf("No se puede abrir el archivo\n");
        return;
    }
    int contentLength = Content_Lenght(fp);
<<<<<<< HEAD
    sendFile(fp, contentLength);
    fclose (fp);

    // char* ext = get_ext(url);

=======
    
    char* ext = get_ext(url);
    
    if(check_mime(ext)!= -1){
        sendHeader("200 OK", mime, contentLength, new_socket);
        sendFile(fp, contentLength);
    }
    else{
        sendString("400 Bad Request\n", new_socket);
    }
    fclose (fp);
>>>>>>> aad40a529fcbc6e7fb003af5625d4ee700c67ad1
}

char* get_ext(char item [])
{
    int index = 0;
    int ini = strlen(item)-1;
    for ( int i = ini; i >= 0; i--)
    {
        if(item[i] == '.')
        {
            index = i;
            break;
        }
        if(item[i] == '/')
        break;
    }
    if(index == 0) return '/0';

    int count = strlen(item)- index;
    char* result =  (char*)malloc(count*sizeof(char)); 
    
    for (int i = index; i < strlen(item); i++)
        result[i-index] = item[i];
    
    return result;    
}









void Post(StringList list)
{
    printf("Llego al POST /n");
}
