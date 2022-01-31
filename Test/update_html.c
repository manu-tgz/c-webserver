//TODO: Agregar la parte de mostrar el repositorio en html

#define SEEK_END 2 /* Seek from end of file.  */
#define html "<tr><td><a href=%s>%s</a></td><td>%s</td><td>%s</td></tr>%c"

int Content_Lenght(FILE *fp)
{
	int filesize = 0;

	fseek(fp, 0, SEEK_END);
	filesize = ftell(fp);
	rewind(fp);

	return filesize;
}


void  update_html(char* url)
{
    FILE *fp = fopen(url, "rb+");
	if (fp == NULL)
	{
		printf("%s", url);
		printf("No se puede abrir el archivo\n");
		return;
	}
	sendFile(fp);

}


void sendFile(FILE *fp)
{
    char *s = (char *)malloc((Content_Lenght(fp)-10193+100) * sizeof(char));
	fseek(fp,10195,SEEK_SET); //Empieza a partir de esa posición
	int current_char = 0;
	int count = 0;
	do
	{
		current_char = fgetc(fp); //bytes
		s[count]=(char)current_char;
		count ++;

	} while (current_char != EOF);
	printf("%s",s);
	fseek(fp,10195,SEEK_SET);
	get_directory(fp);
	fputs(s,fp);
	
}


//Add files to the folder list
void AddToHTML( char*  dirName, char *shtml)
{
	char *s = strcpy_init(strlen(address) + strlen(dirName), address);
	strcat(s, dirName);
	sprintf(shtml, html, s, dirName, "Falta", "Falta", '\0');
}