
//Método para abrir archivos, descargar ....etc

//TODO: Abrir archivos

void get_directory(/*char *address ,*/FILE *fp)
{
    char* shtml;

    DIR *dp;
    struct dirent *dirp;
    dp = opendir(address);


    while ((dirp = readdir(dp)) != NULL)
    {
        char* temp = (char*)malloc((strlen(dirp->d_name)+1)*sizeof(char));
        strcpy(temp,"/");
        strcat(temp,dirp->d_name);
        // add_to_list(&folders,temp);
        shtml = (char*)malloc((2*strlen(temp)+ strlen(html))*sizeof(char));
        AddToHTML(temp,shtml );
        fputs(shtml,fp);
    } 
   
}

//TODO: Descargar archivos