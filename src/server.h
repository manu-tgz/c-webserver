#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <poll.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <sys/select.h>
#include <signal.h>
#include <dirent.h>
#include <time.h>
#include "List.c"
#include "useful.c"
#include "html.c"


#define html_table "<tr><td><a href=%s>%s</a></td><td>%s</td><td>%s</td></tr><use xlink:href=\"%s\"></use>%c"
#define init_html "<!DOCTYPE html><html><head></head><body><main><div class=\"listing\"><table aria-describedby=\"summary\"><thead><tr><th><a href=\"?sort=name&order=asc\" class=\"icon\"><svgwidth=\"1em\" height=\".5em\" version=\"1.1\" viewBox=\"0 012.922194 6.0358899\"><use xlink:href=\"#up-arrow\"></use><svg></a><a href=\"?sort=name&order=dsc\" class=\"icon\"><svgwidth=\"1em\" height=\".5em\" version=\"1.1\" viewBox=\"0 012.922194 6.0358899\"><use xlink:href=\"#down-arrow\"><use></svg></a><a href=\"?sort=name&order=asc\">Name</a></th><th><a href=\"?sort=size&order=asc\" class=\"icon\"><svgwidth=\"1em\" height=\".5em\" version=\"1.1\" viewBox=\"0 012.922194 6.0358899\"><use xlink:href=\"#up-arrow\"></use><svg></a><a href=\"?sort=size&order=dsc\" class=\"icon\"><svgwidth=\"1em\" height=\".5em\" version=\"1.1\" viewBox=\"0 012.922194 6.0358899\"><use xlink:href=\"#down-arrow\"><use></svg></a><a href=\"?sort=size&order=asc\">Size</a></th><th class=\"hideable\"><a href=\"?sort=time&order=asc\" class=\"icon\"><svgwidth=\"1em\" height=\".5em\" version=\"1.1\" viewBox=\"0 012.922194 6.0358899\"><use xlink:href=\"#up-arrow\"></use><svg></a><a href=\"?sort=time&order=dsc\" class=\"icon\"><svgwidth=\"1em\" height=\".5em\" version=\"1.1\" viewBox=\"0 012.922194 6.0358899\"><use xlink:href=\"#down-arrow\"><use></svg></a><a href=\"?sort=time&order=asc\">Modified</a></tr></thead><tbody>"
#define end_html "</tbody> </table></div></main> <footer>   Victor --- Raul ----- Emmanuel  WebServer   </footer></body></html> "
#define FOLDER_CONT 5000
int True = 1;
