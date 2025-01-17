# include "../includes/Client/Socket.hpp"
# include "../includes/HTTPMessage/HTTPRequest/HTTPRequest.hpp"
# include "../includes/Logger/Logger.hpp"
# include "../includes/ConfigParser/ConfigParser.hpp"
# include "../includes/ServerManager/ServerManager.hpp"

void handleSigpipe(int sig)
{ 
	if(sig){}
}

int main(int argc, char **argv)
{
	try 
	{
        signal(SIGINT, WebServer::Utils::signalHandler);
		signal(SIGPIPE, handleSigpipe);
        HTTPRequest request;
		std::string configFilePath = WebServer::Utils::getConfigFilePath(argc, argv);
		ConfigParser	configParser;
		configParser.createCluster(configFilePath);
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
