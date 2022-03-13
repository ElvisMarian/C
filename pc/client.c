#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"
#include "parson.h"

#define SIZE 4096

int main(int argc, char *argv[])
{
    int sockfd, number;
    char *message, *response, *string;
    char books[] = "/api/v1/tema/library/books/";
    char *host = "34.118.48.238";
    char *typepayload = "application/json";

    char command[50];
    char text[100];
    // pentru a demonstra ca sunt autentificat si ca am acces in biblioteca
    char *login_acces = calloc(SIZE, sizeof(char));
    char *library_acces = calloc(SIZE, sizeof(char));
    char **cookies = malloc(sizeof(char));

   	cookies[0] = malloc(SIZE * sizeof(char));
    while (1) {
    	// asteapta comanda
	    scanf("%s", command);
	    // deschid conexiunea si initializez json-urile
	    sockfd = open_connection("34.118.48.238", 8080, AF_INET, SOCK_STREAM, 0);  
	    JSON_Value *root_value = json_value_init_object();
	    JSON_Object *root_object = json_value_get_object(root_value);
	    char *serialized_string = NULL;
	    // pentru comanda register sau login
	    if (strcmp(command, "register") == 0 || strcmp(command, "login") == 0) {
	    	// citesc numele si parola, instantiez obiectele json
	    	printf("username=");
	    	scanf("%s", text);
	    	json_object_set_string(root_object, "username", text);
	    	printf("password=");
	    	scanf("%s", text);
	    	json_object_set_string(root_object, "password", text);
	   		serialized_string = json_serialize_to_string_pretty(root_value);
	   		// trimite cererea si primeste raspunsul
	   		if (strcmp(command, "register") == 0) {
	    		message = compute_post_request(host, "/api/v1/tema/auth/register" , typepayload, &serialized_string , 1, NULL, 0, NULL, 0);
	   		} else {
	    		message = compute_post_request(host, "/api/v1/tema/auth/login" , typepayload, &serialized_string , 1, NULL, 0, NULL, 0);
	   		}
			printf("%s\n", message);
			send_to_server(sockfd, message);
			response = receive_from_server(sockfd);
			printf("%s\n", response);
			// actualizez variabila pentru logare
			if (strcmp(command, "login") == 0) {
				memset(login_acces, 0, SIZE);
				strcpy(login_acces, strtok(strstr(response, "connect.sid=s"), ";"));
			}

		} else if (strcmp(command, "enter_library") == 0) {
			// veridic daca s-a logat mai intai
    		strcpy(cookies[0], login_acces);
    		message = compute_get_request(host, "/api/v1/tema/library/access", NULL, cookies, 1, NULL, 0);
    		printf("%s\n",message);
    		send_to_server(sockfd, message);
    		response = receive_from_server(sockfd);
    		printf("%s\n",response);
    		// acum salvez token-ul care imi da accesul in biblioteca
    		memset(library_acces, 0, SIZE);
    		library_acces = strtok(response, "\"");
    		for(int i = 0 ; i < 5; i++)
    			library_acces = strtok(NULL, "\"");

		} else if (strcmp(command, "get_books") == 0) {
			//verific accesul la biblioteca
    		strcpy(cookies[0], library_acces);
    		message = compute_get_request(host, "/api/v1/tema/library/books", NULL, NULL, 0, cookies, 1);
    		printf("%s\n",message);
    		send_to_server(sockfd, message);
    		response = receive_from_server(sockfd);
    		printf("%s\n",response);
    	
		} else if(strcmp(command, "add_book") == 0) {
			// verific accesul la biblioteca
    		strcpy(cookies[0], library_acces);
    		//creez obiectele json
    		printf("title=");
	    	scanf("%s", text);
	    	json_object_set_string(root_object, "title", text);
	    	printf("author=");
	    	scanf("%s", text);
	    	json_object_set_string(root_object, "author", text);
	    	printf("genre=");
	    	scanf("%s", text);
	    	json_object_set_string(root_object, "genre", text);
	    	printf("page_count=");
	    	scanf("%d", &number);
	    	json_object_set_number(root_object, "page_count", number);
	    	printf("publisher=");
	    	scanf("%s", text);
	    	json_object_set_string(root_object, "publisher", text);
	   		serialized_string = json_serialize_to_string_pretty(root_value);
	    	message = compute_post_request(host, "/api/v1/tema/library/books", typepayload, &serialized_string, 1, NULL, 0, cookies, 1);
			printf("%s\n", message);
			send_to_server(sockfd, message);
			response = receive_from_server(sockfd);
			printf("%s\n", response);

		} else if (strcmp(command, "get_book") == 0) {
			// verific accesul in biblioteca
    		strcpy(cookies[0], library_acces);
    		//solicit id
    		printf("id=");
    		scanf("%s", text);
    		//aici imi resetez ruta de acces
    		strcpy(books, "/api/v1/tema/library/books/");
    		string = NULL;
    		// creez parametrul pentru cerere
    		string = strcat(books, text);
    		//trimit cererea si primesc raspunsul
    		message = compute_get_request(host, string, NULL, NULL, 0, cookies, 1);
    		printf("%s\n",message);
    		send_to_server(sockfd, message);
    		response = receive_from_server(sockfd);
    		printf("%s\n",response);

		} else if (strcmp(command, "delete_book") == 0) { //repara-l;
			string = NULL;
			//citesc id-ul
    		strcpy(cookies[0], library_acces);
    		printf("id=");
    		scanf("%s", text);
    		// resetez ruta
    		strcpy(books, "/api/v1/tema/library/books/");
    		string = strcat(books, text);
    		message = compute_delete_request(host, string, NULL, NULL, 0, cookies, 1);
    		printf("%s\n",message);
    		send_to_server(sockfd, message);
    		response = receive_from_server(sockfd);
    		printf("%s\n",response);

		} else if (strcmp(command, "logout") == 0) {
			//verific daca sunt logat
    		strcpy(cookies[0], login_acces);
    		//sterg continutul acceselor intrucat ma deloghez
    		memset(login_acces, 0, SIZE);
    		memset(library_acces, 0, SIZE);
    		//trimit cererea si primesc raspuns
    		message = compute_get_request(host, "/api/v1/tema/auth/logout", NULL, cookies, 1, NULL, 0);
    		printf("%s\n",message);
    		send_to_server(sockfd, message);
    		response = receive_from_server(sockfd);
    		printf("%s\n",response);

		} else if (strcmp(command, "exit") == 0) {
			//daca primesc exit opresc conexiunea si ies din bucla
			close_connection(sockfd);
			break;

		} else {
			//pentru cazul in care nu este recunoscuta comanda
			printf("Unknown command! Try again or type exit!\n");
		}
		// resetez vectorul de securitate
    	memset(cookies[0], 0, SIZE);
		close_connection(sockfd);
	}
    return 0;
}
