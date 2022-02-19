// #include <stdlib.h>
// #include <stdio.h>

typedef struct {
	char ** items;
	int count;
	int _size;
	int char_count;
} StringList;

//inicializador de la lista de strings
StringList string_list_init(){

	StringList list;
	list._size = 2;
	list.count = 0;	
	list.char_count = 0;
	list.items = (char**) calloc(sizeof(char*), list._size);

	return list;
};

//agrega al final de la lista
void add_to_list(StringList* list,char* s){
	if(list->count == list->_size){
		//alargar la lista
		char** items = (char**) calloc(sizeof(char*), list->_size*2);
		for(int i=0; i<list->_size;i++)
			items[i] = list->items[i];

		free(list->items);

		list->_size *= 2;
		list->items = items;
	}
    list->char_count = list->char_count + strlen(s);
	list->items[list->count++] = s;
}

//Elimina de la lista la cadena en la posición n
void remove_from_list_for_position (StringList* list,int n)
{
	int count = 0;

	if((list->count-1)*2 <= list->_size){
		char** items = (char**) calloc(sizeof(char*), list->_size);
		for(int i=0; i<list->_size;i++)
		{
			if(i != n)
				items[i-count] = list->items[i];
			else{
				list->count -= 1;
				count++;
			}
		}
		free(list->items);

		list->_size /= 2;
		list->items = items;
	}
	else
	{
		char** items = (char**) calloc(sizeof(char*), list->_size);
		for(int i=0; i<list->_size;i++)
		{
			if(i != n)
				items[i-count] = list->items[i];
			else{
				list->count -= 1;
				count++;
			}
		}
		free(list->items);

		list->items = items;
	}
}

void clear_list(StringList* list)
{	
	free(list->items);
	list->_size = 2;
	list->count = 0;	
	list->char_count = 0;
	list->items = (char**) calloc(sizeof(char*), list->_size);
} 

//Elimina de la lista la cadena s
void remove_from_list(StringList* list,char* s)
{
	int count = 0;
	int temp = 0;

	for(int i=0; i<list->_size;i++)
		if(list->items[i] == s)
			temp ++;

	if((list->count-temp)*2 <= list->_size){
		char** items = (char**) calloc(sizeof(char*), list->_size);
		for(int i=0; i<list->_size;i++)
		{
			if(list->items[i] != s)
				items[i-count] = list->items[i];
			else{
				list->count -= 1;
				count++;
			}
		}
		free(list->items);

		list->_size /= 2;
		list->items = items;
	}
	else
	{
		char** items = (char**) calloc(sizeof(char*), list->_size);
		for(int i=0; i<list->_size;i++)
		{
			if(list->items[i] != s)
				items[i-count] = list->items[i];
			else{
				list->count -= 1;
				count++;
			}
		}
		free(list->items);

		list->items = items;
	}
}

//obtiene el elemento en la posicion index de la lista
char* get_from_list(StringList* list, int index){
	return list->items[index];
}
char* get_and_delete_from_list(StringList* list, int index){
	char* s = list->items[index];
	remove_from_list_for_position(list,index);
	return s;
}
//asigna en la posicion index de la lista
void set_in_list(StringList* list, int index, char* value){
	list->items[index] = value;
}

//extrae el ultimo elemento de la lista (como una pila)
char* pop_from_list(StringList* list){
	char* s = list->items[list->count-1];
	list->items[list->count--]=NULL;
	return s;
}

//extrae el primer elemento de la lista 
char* shift_from_list(StringList* list){
	char* s = list->items[0];
	list->items++;
	list->count--;
	return s;
}

void add_line_to_list(StringList* list, char*line)
{
	int temp = 0;
	for (size_t i=0; i<strlen(line); i++)
	{
		if(line[i] != ' ' && line[i] != '\0')
            temp +=1;
        else 
        {
            char* tempChar = (char*) calloc(sizeof(char), temp+1);
            for (size_t j = 0; j < temp; j++)
                tempChar[j] = line[j+i - temp];
            tempChar[temp] = '\0';
            
            add_to_list(list,tempChar);                
            temp=0;
        }
	}
    
	char* tempChar = (char*) calloc(sizeof(char), temp+1);
    for (size_t j = 0; j < temp; j++)
   	    tempChar[j] = line[j+strlen(line) - temp];
   	tempChar[temp] = '\0';

   	add_to_list(list,tempChar);                
}

//imprime la lista con la cantidad de elementos
void print_list(StringList* list){
	printf(" [ ");

	for(int i=0;i<list->count; i++){
		printf("%s ", list->items[i]);
	}

	printf(" ]\n (count: %d, size: %d)\n ",list->count,list->_size);
}

void print_list_for_shell (StringList* list)
{
	for(int i=0;i<list->count; i++){
		printf("%s \n", list->items[i]);
	}
}
//Devuelve la posición donde se encuentra line
int Indexof(StringList* list, char* line)
{
  	for (int i = 0; i < list->count; i++)
	  	if(strcmp(list->items[i],line)==0)
	  		return i;
	return -1;
}
int index_of_char_in_list(StringList* list, char* c)
{
	for (size_t i = 0; i < list->count; i++)
		for (size_t j = 0; j < strlen(list->items[i]); j++)
			if(list->items[i][j] == c)
				return i;
	return -1;
}


char* Concat(StringList* list, int init, int large)
{
  char* tempChar = (char*)malloc(list->char_count*sizeof(char)+ list->count-1);
    int a = 0;

      for (int i = init; i < large; i++)
      {
           for (int j = 0; j < strlen(list->items[i]); j++)
           {
               tempChar[a++]= list->items[i][j];
           } 
          if(i!= (list->count-1))
              tempChar[a++]= ' ';
      }
  return tempChar;
}