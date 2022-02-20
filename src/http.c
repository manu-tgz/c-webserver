/*
Contiene todos los metodos del protocolo http implementados
*/
#include "uri.c"
#include "http_response.c"
#include "update_html.c"

char *html_answer(char *address1, int mode, char *field, char *order);

void Get(URI uri);

char *commands[] = {
	"GET",
};

void (*Function[])(URI args) = {
	Get,
	0};

// Selecciona el controlador
void http(StringList list)
{
	URI uri = Uri_init(list);
	print_uri(&uri);
	char *command = get_and_delete_from_list(&list, 0);
	int a = 0;
	for (int i = 0; i < 5; i++)
		if (strcmp(command, commands[i]) == 0)
		{
			Function[i](uri);
			return;
		}
	// TODO: Enviar al cliente
	printf("501 Not Implemented\n");
}
void Get(URI uri)
{
	char *ext = get_ext((char *)uri.path);
	if (check_mime(ext) != -1) // Si tiene extension descargalo.
	{
		drowload_file(uri);
	}
	else // Sino tiene muestra las carpetas/archivos del directorio
	{
		get_html(uri);
	}
}

void drowload_file(URI uri)
{
	// Concat address y uri
	char *url = strcpy_init(strlen(uri.path) + strlen(address), address, uri.path);
	// Entra al archivo
	Msg("Abriendo archivo ", url,"");
	FILE *fp = fopen(url, "rb+");
	if (fp == NULL)
	{
		printf("%s", url);
		sendString("400 Bad Request\n", client_socket);
		printf("No se puede abrir el archivo\n");
		return;
	}
	int contentLength = Content_Lenght(fp);
	sendHeader("200 OK", mime, contentLength, client_socket, "attachment", rindex(url, '/') + 1);
	sendFile(fp, contentLength);
	fclose(fp);
}

void get_html(URI uri)
{
	char *s; // Todo el nuevo html

	char *order, *field;
	int mode = 0;
	if (uri.query != NULL)
	{
		char *ptr = strdup(uri.query);
		if (strstr(ptr, "sort") != 0 && strstr(ptr, "order") != 0)
		{
			field = calloc(4 * sizeof(char), sizeof(char));
			order = calloc(3 * sizeof(char), sizeof(char));
			sscanf(ptr, "sort=%4s&order=%3s", field, order);
		}
		mode = 1;
	}

	if (strcmp(uri.path, "/") == 0)
		s = html_answer("", mode, field, order);
	else
		s = html_answer(uri.path, mode, field, order);

    if(strlen(s)!=0)
	{
    // HTML Resultante
	char *html = (char *)malloc((strlen(buffer) + strlen(s)) *
								sizeof(char));
	Create_HTML(html, s);
	int contentLength = strlen(html);

	sendHeader("200 OK", "text/html; charset: UTF-8", contentLength, client_socket, "", "");
	sendhtml(client_socket, html, contentLength);
	free(s);
	free(html);
	}
	else
	{
		char *a = "ERROR No se pudo abrir. Verifique que no tenga espacios:(";
		sendHeader("500", "", strlen(a), client_socket, "", "");
		sendhtml(client_socket, a, strlen(a));
	}
}