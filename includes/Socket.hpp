#pragma once

# include <sys/socket.h> // for functions like socket, bind, listen, accept and others
# include <netinet/in.h> // some macros for socket
# include <netdb.h> // getaddrinfo
# include <string.h> // strerror
# include <vector>
# include <fcntl.h>
# include <iostream>
# include <unistd.h>

namespace WebServer
{
    class Socket
    {
        private:
            int _sock;
            int _connection;
            struct sockaddr_in _address;
        public:
            Socket(int domain, int service,  int protocol, int port, unsigned long interface);
            ~Socket();
            virtual int connect_to_network(int sock, struct sockaddr_in address) = 0;
            void test_connection(int test_variable);

            //Getters
            struct sockaddr_in get_address();
            int get_sock();
            int get_connection();
    };
}
