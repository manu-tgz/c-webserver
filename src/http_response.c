#include "mimes.c"

char *get_ext(char item[]);

int sendString(char *message, int socket)
{
	int length, bytes_sent;

	length = strlen(message);
	bytes_sent = send(socket, message, length, 0);

	return bytes_sent;
}

void sendHeader(char *Status_code, char *Content_Type, int TotalSize, int socket,char* Disposition, char* content_n)
{
	char *head = "\r\nHTTP/1.1 ";
	char *content = "\r\nContent: ";
	char *content_head = "\r\nContent-Type: ";
	char *disposition = "\r\nContent-Disposition:";
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
							   strlen(disposition) +
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

        if(strcmp(content_n,"")==1)
		{
			strcat(message, content);
			strcat(message, content_n);
		}
		else
		{
			strcat(message, content_head);
			strcat(message, Content_Type);
		}
		strcat(message, disposition);
		strcat(message, Disposition);
		strcat(message, server_head);
		strcat(message, length_head);
		strcat(message, contentLength);
		strcat(message, date_head);
		strcat(message, (char *)ctime(&rawtime));
		strcat(message, newline);
		sendString(message, socket);
		
		printf("%s",message);
		free(message);
	}
}

void sendFile(FILE *fp, int file_size)
{
	int current_char = 0;
	do
	{
		current_char = fgetc(fp); //bytes
		send(client_socket, &current_char, sizeof(char), 0);

	} while (current_char != EOF);
}

void sendhtml(int fd, char* buf, int length)
{
    int r = length;
    while (1)
    {
        int n = write(fd, buf, r);
        r -= n;
        if (n <= 0 || r <= 0)
            break;
    }
}

//Devuelve el largo del archivo
int Content_Lenght(FILE *fp)
{
	int filesize = 0;
	fseek(fp, 0, SEEK_END); //Va al final del archivo
	filesize = ftell(fp);  //obtiene el valor puntero que está al final
	rewind(fp);  //coloca el puntero al inicio del archivo

	return filesize;
}

//Obtener extensión
char *get_ext(char item[])
{
	int index = 0;
	int ini = strlen(item) - 1;
	for (int i = ini; i >= 0; i--)
	{
		printf("%c",item[i]);
		if (item[i] == '.')
		{
			index = i;
			break;
		}
		if (item[i] == '/')
			break;
	}
	if (index == 0)
		return '\0';

	int count = strlen(item) - index +1;
	char *result = (char *)malloc(count * sizeof(char));
	
	for (int i= index; i < strlen(item); i++)
		result[i - index] = item[i];
	result[strlen(item) - index] = '\0';	

	return result;
}

//Buscar el mime
int check_mime(char* ext)
{
	if(ext == NULL)
	return -1;
    for (int i = 0; i < ext_len; i++)
        if(strcmp(ext,exts[i])==0)
        {
            mime = mimes[i];
            return 1;
        }
    return -1;    
}
