#include "../includes/Socket.hpp"

// int main(int argc, char const **argv) 
// {
//     (void)argc;
//     (void)argv;

//     const WebServer::Socket *test = new WebServer::(AF_INET, SOCK_STREAM, 0, 8080, INADDR_ANY);
//     int socket_fd = test.get_sock();
//     struct sockaddr_in temp_address = test.get_address();
//     struct sockaddr_in *address = &temp_address;
//     int addrlen = sizeof(address);
//     int new_socket;

//     if (listen(socket_fd, 10) < 0) 
//     {
//         perror("In listen");
//         exit(EXIT_FAILURE);
//     }
//      std::cout << "+++++++ Waiting for new connection ++++++++" << std::endl;

//     while (true) {
//         if ((new_socket = accept(socket_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen )) < 0) {
//             cout << socket_fd << " "  << address << endl;
//             perror("Accept failed");
//             exit(EXIT_FAILURE);
//         }

//         char buffer[30000] = {0};
//         int valread = read(new_socket, buffer, 30000);
//         std::string hello = "Hello from server";

//         std::cout << buffer << std::endl;
//         send(new_socket, hello.c_str(), hello.size(), 0);
//         std::cout << "------------------Hello message sent-------------------" << valread << std::endl;

//         close(new_socket);
//     }

//     return 0;
// }

void signalHandler(int signum) { exit(signum); }

int main()
{
    try{
        signal(SIGINT, signalHandler);
        int new_socket;
        WebServer::Socket test = WebServer::Socket(AF_INET, SOCK_STREAM, 0, 8080, INADDR_ANY);
        test.bindConnection();
        test.listenConnection();
        
        std::cout << "+++++++ Waiting for new connection ++++++++" << std::endl;
        while (true) {
            new_socket = test.acceptConnection();
            cout << "new socket fd: " << new_socket << endl;

            char buffer[30000] = {0};
            int valread = read(new_socket, buffer, 30000);
            std::string hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nnihao world!";

            std::cout << buffer << std::endl;
            send(new_socket, hello.c_str(), hello.size(), 0);
            std::cout << "------------------Hello message sent-------------------" << valread << std::endl;
            close(new_socket);
        }
    }catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return (1);
    }

    return 0;
}