/**
 * @file socket.h
 * @brief Header file for socket server functions.
 *
 * This file contains the declaration of functions used to start a socket server.
 */

#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <switch.h>

/**
 * @brief Starts a socket server.
 *
 * This function initializes and starts a socket server that listens on the specified port.
 * It creates a socket, sets socket options, binds the socket to the port, and listens for incoming connections.
 *
 * @param port The port number on which the server will listen.
 * @return int Returns 0 on success, -1 on failure.
 */
int start_socket_server(int port);

/**
 * @brief Accepts a connection from a client.
 *
 * This function accepts a connection from a client and returns the file descriptor of the connection.
 *
 * @param server_fd The file descriptor of the server socket.
 * @return int Returns the file descriptor of the connection on success, -1 on failure.
 */
int accept_connection(int server_fd);

/**
 * @brief Reads data from a connection.
 *
 * This function reads data from a connection and stores it in the specified buffer.
 *
 * @param conn_fd The file descriptor of the connection.
 * @param buffer The buffer in which to store the data.
 * @param buffer_size The size of the buffer.
 * @return int Returns the number of bytes read on success, -1 on failure.
 */

int read_from_connection(int conn_fd, char *buffer, int buffer_size);

/**
 * @brief Writes data to a connection.
 *
 * This function writes data to a connection from the specified buffer.
 *
 * @param conn_fd The file descriptor of the connection.
 * @param buffer The buffer containing the data to write.
 * @param buffer_size The size of the buffer.
 * @return int Returns the number of bytes written on success, -1 on failure.
 */
int write_to_connection(int conn_fd, char *buffer, int buffer_size);

/**
 * @brief Closes a connection.
 *
 * This function closes a connection.
 *
 * @param conn_fd The file descriptor of the connection.
 * @return int Returns 0 on success, -1 on failure.
 */
int close_connection(int conn_fd);

int get_ip_address(char *ip_address, int ip_address_size);

bool get_string_from_remote(char *url);