
char *strcpy_init(int lengh, char *s1 , char* s2);

//Concatena dos string y los guarda en un string del tamaño especificado
char *strcpy_init(int lengh, char *s1 , char* s2)
{
    char *result = (char *)malloc((lengh) * sizeof(char));
    strcpy(result,s1);
    strcat(result,s2);
    // sprintf(result, "%s%s", s1, s2);
    return result;
}

void Msg(char *msg, char *text, char *end)
{
    printf("[REV-Server]: %s%s%s", msg, text, end);
}
