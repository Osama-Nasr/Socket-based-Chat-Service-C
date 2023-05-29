#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <pthread.h>

#define PORT 8080
#define MAX_CLIENTS 2
#define BUFFER_SIZE 1024

typedef struct {
    int sock;
    struct sockaddr_in addr;
} client_t;

client_t clients[MAX_CLIENTS];
int client_count = 0;

void *handle_client(void *arg) {
    client_t *client = (client_t *)arg;
    int bytes_received;
    char buffer[BUFFER_SIZE];
    
    while ((bytes_received = read(client->sock, buffer, BUFFER_SIZE - 1)) > 0) {
        buffer[bytes_received] = '\0';
        for (int i = 0; i < client_count; i++) {
            if (clients[i].sock != client->sock) {
                write(clients[i].sock, buffer, strlen(buffer));
            }
        }
    }

    close(client->sock);
    return NULL;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in server_addr, client_addr;
    int addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 2) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (client_count < MAX_CLIENTS) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t *)&addr_len)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        clients[client_count].sock = new_socket;
        clients[client_count].addr = client_addr;

        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, handle_client, &clients[client_count]) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }

        client_count++;
    }

    close(server_fd);
    return 0;
}
