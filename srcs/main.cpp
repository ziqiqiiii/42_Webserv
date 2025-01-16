# include "../includes/Client/Socket.hpp"
# include "../includes/HTTPMessage/HTTPRequest/HTTPRequest.hpp"
# include "../includes/Logger/Logger.hpp"
# include "../includes/ConfigParser/ConfigParser.hpp"
# include "../includes/ServerManager/ServerManager.hpp"

/*
int main()
{
    signal(SIGINT, Utils::signalHandler);
    int new_socket = -1;
    WebServer::Socket test = WebServer::Socket(AF_INET, SOCK_STREAM, 0, 8080, INADDR_ANY);
    test.bindConnection();
    test.listenConnection();
    HTTPRequest request;

    Logger::logMsg(LIGHTMAGENTA, "+++++++ Waiting for new connection ++++++++\n");
    try {
        while (true) {
            new_socket = test.acceptConnection();
            Logger::logMsg(LIGHTMAGENTA, "+++++++ Connection Accepted ++++++++\n");

            char buffer[30000] = {0};
            int valread = read(new_socket, buffer, 30000);
            string hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nnihao world!";

            Logger::logMsg(YELLOW, "------- Header -------\n");
            Logger::logMsg(YELLOW, "%s\n", buffer);
            request.parseMessage(buffer);
            Logger::logMsg(LIGHT_BLUE, "------- Getters -------\n");
            Logger::logMsg(LIGHT_BLUE, "Start line: %s\n", request.getStarline().c_str());
            cout << LIGHT_BLUE << "Field line:\n" << request.getHeaders() << endl;
            Logger::logMsg(LIGHT_BLUE, "Message Body: %s\n", request.getBody().c_str());
            Logger::logMsg(LIGHT_BLUE, "+++++++ Sending Message ++++++++\n");
            send(new_socket, hello.c_str(), hello.size(), 0);
            Logger::logMsg(LIGHT_BLUE, "------------------Hello message sent-------------------%d\n", valread);
            close(new_socket);
            // Reset the socket descriptor
            new_socket = -1;
        }
    } catch (std::exception &e) {
        cerr << e.what() << endl;
        if (new_socket != -1) {
            close(new_socket);
        }
        return 1;
    }
    close(test.getServerFd());
    return 0;
}
*/

// ========================TEST FOR PARSER================================//
// Handles SIGPIPE signals to prevent program termination.
// If a client disconnects while the server is writing data, SIGPIPE would
// terminate the server unexpectedly, leading to downtime.
void handleSigpipe(int sig)
{ 
	if(sig){}
}

int main(int argc, char **argv)
{
	try 
	{
        signal(SIGINT, Utils::signalHandler);
		signal(SIGPIPE, handleSigpipe);
        HTTPRequest request;
		//Get config file path
		std::string configFilePath = Utils::getConfigFilePath(argc, argv);
		//Parse config file for servers
		ConfigParser	configParser;
		configParser.createCluster(configFilePath);
        //configParser.print();
        //exit(1);
		ServerManager 	serverManager;
		serverManager.setupServers(configParser.getServers());
		serverManager.runServers();
	}
	catch (std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return (1);
	}
	return (0);
}
