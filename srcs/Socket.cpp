#include "../includes/Socket.hpp"

// Default Constructor
WebServer::Socket::Socket(int domain, int service,  int protocol, int port, unsigned long interface)
{
    // Define address struct
    Socket::_address.sin_family = domain;
    Socket::_address.sin_port = htons(port);
    Socket::_address.sin_addr.s_addr = htons(interface);
    // Establish Socket
    Socket::_sock = socket(domain, service, protocol);
    Socket::test_connection(Socket::_sock);
    // Establish Network Connection
    Socket::_connection = connect_to_network(Socket::_sock, Socket::_address);
    Socket::test_connection(Socket::_connection);
}

// Default Destructor
WebServer::Socket::~Socket() {}

// Test connection of virtual function
void WebServer::Socket::test_connection(int test_variable)
{
    if (test_variable < 0) {
        perror("Failed to connect ...");
        exit(EXIT_FAILURE);
    }
}

// Getters
struct sockaddr_in WebServer::Socket::get_address()
{
    return Socket::_address;
}

int WebServer::Socket::get_sock()
{
    return Socket::_sock;
}

int WebServer::Socket::get_connection()
{
    return Socket::_connection;
}
