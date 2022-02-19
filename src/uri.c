// #include <stdio.h>
// #include <stdlib.h>
// #include <strings.h>
// #include "List.c"

typedef struct {
	char* sheme;
	char* autority;
	char* path;
	char* query;
	char* fragment;
} URI;

StringList Parser_path (char* path);

URI Uri_init(StringList list){
    
	URI uri;
	uri.sheme = NULL;
	uri.autority = NULL;
	uri.path = NULL;
	uri.query = NULL;
	uri.fragment = NULL;

	uri.sheme = "http"; 
	uri.autority = "hostpot"; 
	char* path = get_from_list(&list,1);
	StringList parser_path = Parser_path(path);
    
	uri.path = parser_path.items[0];
	if(parser_path.count >1)
	{
		if(strcmp(parser_path.items[1],"?" )==0)
			uri.query = parser_path.items[2];
		if(strcmp(parser_path.items[1],"#" )==0)
			uri.fragment = parser_path.items[2];
	}
	if(parser_path.count >3)
		uri.fragment = parser_path.items[4];
	// if(strcmp( uri.path, "/")==0)
	// 	uri.path = "/index.html";
	return uri;
}

StringList Parser_path (char* path)
{
	StringList result = string_list_init();
	int temp = 0;
	for (size_t i=0; i<strlen(path); i++)
	{
		if(path[i] != '?' && path[i] != '#' && path[i] != '\0')
            temp +=1;
        else 
        {
            char* tempChar = (char*)malloc(temp*sizeof(char));
            for (size_t j = 0; j < temp; j++)
                tempChar[j] = path[j+i - temp];
            tempChar[temp] = '\0';
            add_to_list(&result,tempChar);                
            temp=0;

			if(path[i] == '?') 
            	add_to_list(&result,"?");
			if(path[i] == '#') 
            	add_to_list(&result,"#");
        }
	}
    char* tempChar = (char*)malloc(temp*sizeof(char));
    for (size_t j = 0; j < temp; j++)
   	    tempChar[j] = path[j+strlen(path) - temp];
   	tempChar[temp] = '\0';

   	add_to_list(&result,tempChar); 
	return result;
}
void print_uri(URI* uri)
{
	printf("sheme: %s \n",uri->sheme);
	printf("autority: %s \n",uri->autority);
	printf("path: %s \n",uri->path);
	printf("query: %s \n",uri->query);
	printf("fragment: %s \n",uri->fragment);
}

// int main ()
// {
// 	char* test = "GET test/test1?search=test-question#part2";
// 	URI uri = Uri_init(test);
// 	print_uri(&uri);
// }