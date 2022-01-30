#include <sys/socket.h>
#define SEEK_END 2	/* Seek from end of file.  */

int sendBinary(int *byte, int length)
{
	int bytes_sent;
	bytes_sent = send(new_socket, byte, length, 0);

	return bytes_sent;


	return 0;
}

//Encviar archivo por binarios
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
        printf("Unable to open file");
        //sendString("404 Not Found\n", new_socket);
        return;
    }
    int contentLength = Content_Lenght(fp);
    sendFile(fp, contentLength);
    fclose (fp);

    // char* ext = get_ext(url);

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
void Head(StringList list)
{
    print_list(&list);
    printf("Llego al HEAD /n");
}
void Options(StringList list)
{
    printf("Llego al OPTIONS /n");
}
void Trace(StringList list)
{
    printf("Llego al TRACE /n");
}