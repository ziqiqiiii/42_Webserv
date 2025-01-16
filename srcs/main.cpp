# include "../includes/Client/Socket.hpp"
# include "../includes/HTTPMessage/HTTPRequest/HTTPRequest.hpp"

int main()
{
    signal(SIGINT, WebServer::Utils::signalHandler);
    int new_socket = -1;
    WebServer::Socket test = WebServer::Socket(AF_INET, SOCK_STREAM, 0, 8080, INADDR_ANY);
    test.bindConnection();
    test.listenConnection();
    HTTPRequest request;

    std::cout << "+++++++ Waiting for new connection ++++++++" << std::endl;
    try {
        while (true) {
            new_socket = test.acceptConnection();
            std::cout << "+++++++ Connection Accepted ++++++++" << std::endl;

            char buffer[30000] = {0};
            int valread = read(new_socket, buffer, 30000);
            std::string hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nnihao world!";

            std::cout << "------- Header -------" << std::endl;
            std::cout << buffer << std::endl;
            request.parseMessage(buffer);
            std::cout << "------- Getters -------" << std::endl;
            std::cout << "Start line: " << request.getStarline() << std::endl;
            std::cout << "Field line: " << request.getHeaders() << std::endl;
            std::cout << "Message Body: " << request.getBody() << std::endl;

            std::cout << "+++++++ Sending Message ++++++++" << std::endl;
            send(new_socket, hello.c_str(), hello.size(), 0);
            std::cout << "------------------Hello message sent-------------------" << valread << std::endl;
            close(new_socket);
            // Reset the socket descriptor
            new_socket = -1;
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        if (new_socket != -1) {
            close(new_socket);
        }
        return 1;
    }
    close(test.getServerFd());
    return 0;
}