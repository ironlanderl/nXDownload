#include "socket.h"
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>

#ifndef SO_REUSEPORT
#define SO_REUSEPORT 15
#endif

int start_socket_server(int port)
{
    int server_fd;
    struct sockaddr_in address;
    int opt = 1;

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        return -1;
    }

    // Forcefully attaching socket to the port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        close(server_fd);
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Binding the socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        close(server_fd);
        return -1;
    }

    // Start listening for incoming connections
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        close(server_fd);
        return -1;
    }

    return server_fd;
}

int accept_connection(int server_fd)
{
    int addrlen = sizeof(struct sockaddr_in);
    struct sockaddr_in address;
    int conn_fd;

    if ((conn_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
    {
        perror("accept");
        return -1;
    }

    return conn_fd;
}

int read_from_connection(int conn_fd, char *buffer, int buffer_size)
{
    int bytes_read = recv(conn_fd, buffer, buffer_size, 0);
    if (bytes_read < 0)
    {
        perror("read");
    }
    return bytes_read;
}

int write_to_connection(int conn_fd, char *buffer, int buffer_size)
{
    int bytes_written = write(conn_fd, buffer, buffer_size);
    if (bytes_written < 0)
    {
        perror("write");
    }
    return bytes_written;
}

int close_connection(int conn_fd)
{
    if (close(conn_fd) < 0)
    {
        perror("close");
        return -1;
    }
    return 0;
}

int get_ip_address(char *ip_address, int ip_address_size)
{
    struct in_addr addr;
    if (gethostid() == -1)
    {
        perror("gethostid");
        return -1;
    }
    addr.s_addr = gethostid();
    strncpy(ip_address, inet_ntoa(addr), ip_address_size);
    return 0;
}

bool get_string_from_remote(char *url)
{
    // start socket
    int server_fd = start_socket_server(8180);
    printf("server_fd: %d\n", server_fd);
    consoleUpdate(NULL);
    if (server_fd < 0)
    {
        printf("Failed to start socket server\n");
        consoleUpdate(NULL);
        return false;
    }
    printf("Socket server started\n");
    consoleUpdate(NULL);

    // accept connection
    int conn_fd = accept_connection(server_fd);
    if (conn_fd < 0)
    {
        printf("Failed to accept connection\n");
        consoleUpdate(NULL);
        close(server_fd);
        return false;
    }
    printf("Connection accepted\n");
    consoleUpdate(NULL);

    // read from connection
    char buffer[1024];
    int bytes_read = read_from_connection(conn_fd, buffer, sizeof(buffer));
    if (bytes_read < 0)
    {
        printf("Failed to read from connection\n");
        consoleUpdate(NULL);
        close(server_fd);
        close(conn_fd);
        return false;
    }

    printf("Bytes read: %d\n", bytes_read);
    printf("Received data: %s\n", buffer);

    strcpy(url, buffer);

    consoleUpdate(NULL);

    // write to connection
    char response[] = "OK";
    int bytes_written = write_to_connection(conn_fd, response, sizeof(response));
    if (bytes_written < 0)
    {
        printf("Failed to write to connection\n");
        consoleUpdate(NULL);
        close(server_fd);
        close(conn_fd);
        return false;
    }

    // close connection
    if (close_connection(conn_fd) < 0)
    {
        printf("Failed to close connection\n");
        consoleUpdate(NULL);
        close(server_fd);
        close(conn_fd);
        return false;
    }
    printf("Connection closed\n");
    consoleUpdate(NULL);

    return true;
}