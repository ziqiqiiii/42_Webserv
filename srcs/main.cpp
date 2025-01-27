# include "Socket.hpp"
# include "HTTPRequest.hpp"
# include "Logger.hpp"
# include "ConfigParser.hpp"
# include "ServerManager.hpp"

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
