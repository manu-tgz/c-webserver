#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <strings.h>
#include <errno.h>
#include "List.c"
#include "uri.c"
#include <time.h>

#define Index "/web"

int new_socket;
char *index_address;

