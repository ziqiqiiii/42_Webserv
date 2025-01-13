#include "../includes/Socket.hpp"

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
            std::cout << "+++++++ Connection Accepted ++++++++" << std::endl;
            cout << "new socket fd: " << new_socket << endl;

            std::cout << "+++++++ Sending Message ++++++++" << std::endl;
            char buffer[30000] = {0};
            int valread = read(new_socket, buffer, 30000);
            std::string hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nnihao world!";

            std::cout << "+++++++ Header ++++++++" << std::endl;
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