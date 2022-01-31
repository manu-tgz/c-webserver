#define html "<tr><td><a href=%s>%s</a></td><td>%s</td><td>%s</td></tr>%c"

update_html(char* url)
{
    FILE *fp = fopen(url, "rb");
	if (fp == NULL)
	{
		printf("%s", url);
		printf("No se puede abrir el archivo\n");
		return;
	}
    fseek(fp,10193,SEEK_SET); 
    fputs("Loca",fp);
}


//Add files to the folder list
void AddToHTML( StringList  dirName, char *shtml)
{
    for (int i = 0; i < dirName.count; ++i)
    {
        char*s = strcpy_init(strlen(address)+ strlen(dirName.items[i]),address);
        strcat(s,dirName.items[i]);
        sprintf(shtml , html,s,dirName.items[i],"Falta","Falta", EOF);
       
    }
}
