#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include "server.h"
#include "useful.c"

void main()
{
   char* d= "text1";
    char *s = (char *)malloc((6) * sizeof(char));
    strncpy(s,d,2);
    printf("%s",s);
}