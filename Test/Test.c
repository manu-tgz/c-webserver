// #include <stdlib.h>
// #include <stdio.h>
// #include <string.h>
// #include <sys/socket.h>
// // #include <netinet/in.h>
// // #include <arpa/inet.h>
// // #include <sys/types.h>
// #include <unistd.h>
// // #include <poll.h>
// // #include <sys/stat.h>
// // #include <fcntl.h>
// // #include <sys/sendfile.h>
// // #include <signal.h>
//
// #include <time.h>
#include "server.h"
 #include <dirent.h>
#include "useful.c"
#define address "/home/emmanuel/Almacenamiento/Test"
#include "update_html.c"
#include "file.c"


// #include "update_new.c"


void main()
{
    // update_html("/home/emmanuel/Almacenamiento/Repo/P_C/Webserver/c-webserver/web/index.html");

    char* s1 = (char *)malloc((150) * sizeof(char));
    sprintf(s1, "%s%s", "looo", "aaa");
    printf("%s",s1);
    
}

///"home/emmanuel/Almacenamiento/Repo/P_C/Webserver/c-webserver/web/index.html"