#define html_edit 1602
char *ObtainPermissions(mode_t st_mode);
char *ObtainSize(off_t st_size, mode_t st_mode);

char* html_answer(char *address1, int mode, char *field, char *order)
{
    char *url = strcpy_init(strlen(address1) + strlen(address), address, address1);

    //Parte del directorio
    //TODO: Agregar regresar atrás al html
    struct stat folders[FOLDER_CONT], files[FOLDER_CONT];
    StringList folderName = string_list_init();
    StringList filesName = string_list_init();
    int f_count = 0, filesCount = 0;
    
    //FIXME: La lista vuelve vacia. No imprime lista. Verificar q directory funciona.
    directory(url,folders,files,&folderName,&filesName,f_count,filesCount);
 
    Sort(folders, &folderName, mode, field, order);
    Sort(files, &filesName, mode, field, order);

    //Crear el html resultante  //TODO: Arreglar tama;o de result.
    int len = Len(folderName,filesName,strlen(html_table),strlen(address1));
    char *shtml = (char *)malloc(len*sizeof(char));
    sprintf(shtml + strlen(shtml), html_table, "/", "/", "", "", "",'\0');
    Add_HTML(folders, &folderName, shtml, address1, "#folder");
    Add_HTML(files, &filesName, shtml, address1, "#file");
    
    free(folderName.items);
    free(filesName.items);
    return shtml ;
}

int Len(StringList a, StringList b, int c, int d)
{
    int len = ((a.count + b.count + 1) * (c + d + 35) + (a.char_count + b._size) * 2);
    len += 2;
    return len;
}
//Guarda en las listas y stat las carpetas y archivos.
void directory(char* url, struct stat *folders, struct stat *files, StringList *folderName, StringList *filesName, int f_count, int files_count)
{
    Msg("\n\n Opening directory: ", url, "...\n");
    DIR *dp;
    struct dirent *dirp;
    dp = opendir(url);
    if (dp != NULL)
    {
        int a = 0;

        while ((dirp = readdir(dp)) != NULL)
        {
            if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
                continue;

            struct stat sb;

            char *temp1 = (char *)malloc((strlen(dirp->d_name) + 1 + strlen(url)) * sizeof(char));
            sprintf(temp1, "%s/%s", url, dirp->d_name);
            stat(temp1, &sb);

            if (ObtainPermissions(sb.st_mode)[0] == 'd')
            {
                folders[folderName->count] = sb;
                add_to_list(folderName, strdup(rindex(temp1, '/')));
            }
            else
            {
                files[filesName->count] = sb;
                add_to_list(filesName, strdup(rindex(temp1, '/')));
            }
        }
    }
    else
    {
        Msg("No se puede abrir", url, "");
    }

        // closedir(dp);
//FIXME: IMprime ambas listas para verificar q se guardaron los nombres
}

void Add_HTML(struct stat *dir, StringList *dirName, char *shtml, char* address1, char* k)
{
    char *size,  eof = '\0';
    char *dat = (char*)malloc(27*sizeof(char*));
    for (int i = 0; i < dirName->count; ++i)
    {   
        size = ObtainSize(dir[i].st_size, dir[i].st_mode);
        strcpy(dat,(char*)ctime(&dir[i].st_mtime));
        // dat = ctime(&dir[i].st_mtime);
        
        char *s = strcpy_init(strlen(address1) + strlen(dirName->items[i]), address1,dirName->items[i]);
        
        sprintf(shtml + strlen(shtml), html_table, s, dirName->items[i], size, dat, k,'\0');
    }
}

void Create_HTML(char* html, char* newhtml)
{
    // sprintf(html, "%s%s%s",init_html, newhtml,end_html);
   strncpy(html,buffer,13998);
   strcat(html, newhtml);
   strcat(html,buffer+13999);
}

void Sort(struct stat *dir, StringList *dirName, int sortData, char *field, char *order)
{
    struct stat temp;
    char *name;
    int index, val;
    for (int i = 0; i < dirName->count; ++i)
    {
        index = i;
        for (int j = i + 1; j < dirName->count; ++j)
        {
            if (sortData == 0 || strcmp(field, "name") == 0)
                val = strcasecmp(dirName->items[index], dirName->items[j]);
            else if (strcmp(field, "size") == 0)
                val = (dir[index].st_size > dir[j].st_size) - (dir[index].st_size < dir[j].st_size);
            else
                val = (dir[index].st_ctime > dir[j].st_ctime) - (dir[index].st_ctime < dir[j].st_ctime);
            if (sortData == 0 || strcmp(order, "dsc") == 0)
                index = (val <= 0 ? index : j);
            else
                index = (val >= 0 ? index : j);
        }
        temp = dir[index];
        name = dirName->items[index];
        dir[index] = dir[i];
        dirName->items[index] = dirName->items[i];
        dir[i] = temp;
        dirName->items[i] = name;
    }
}

int pmasks[10] = {S_IFMT, S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH};

char *ObtainPermissions(mode_t st_mode)
{
    char *per = calloc(11 * sizeof(char), sizeof(char));
    sprintf(per, "mrwxrwxrwx");

    switch (st_mode & pmasks[0])
    {
    case S_IFBLK:
        per[0] = 'b';
        break;
    case S_IFCHR:
        per[0] = 'c';
        break;
    case S_IFDIR:
        per[0] = 'd';
        break;
    case S_IFIFO:
        per[0] = 'p';
        break;
    case S_IFLNK:
        per[0] = 'l';
        break;
    case S_IFREG:
        per[0] = '-';
        break;
    case S_IFSOCK:
        per[0] = 's';
        break;
    default:
        per[0] = 'u';
        break;
    }

    int i;
    for (i = 1; i < 10; ++i)
        if (!(st_mode & pmasks[i]))
            per[i] = '-';

    return per;
}

char *ObtainSize(off_t st_size, mode_t st_mode)
{
    if (st_mode & S_IFDIR)
    {
        return "---\0";
    }
    char *size = calloc(64 * sizeof(char), sizeof(char));

    double val;
    int i;
    val = (double)st_size;
    char *tbyte[4] = {"B", "KB", "MB", "GB"};
    for (i = 0; val >= 1024 && i < 4; ++i)
        val /= 1024;
    sprintf(size, "%.2f%s", val, strdup(tbyte[i]));

    return size;
}