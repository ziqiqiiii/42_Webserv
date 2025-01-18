#pragma once

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <iostream>
# include <unistd.h>
# include <csignal>
# include <vector>
# include <stdlib.h>
# include <limits.h>
# include <sstream>
# include <iterator>
# include <fstream>
# include "../../includes/Logger/Logger.hpp"

using std::cout;
using std::endl;
using std::string;

#define CONNECTION_TIMEOUT 60 // Time in seconds for a client to disconnect due to inactivity
#define MESSAGE_BUFFER 40000 //Size of the buffer for reading messages

#define MAX_URI_LENGTH 4096
#define MAX_CONTENT_LENGTH 30000000 //Maximum size of HTTP request content

enum PathType
{
	IS_FILE = 1,
	IS_DIRECTORY = 2,
	IS_OTHER = 3,
	STATFAIL = -1
};

/**
 * @namespace WebServer
 * @brief Contains all components related to the web server.
 */
namespace WebServer
{
       /**
     * @class Utils
     * @brief A utility class providing static helper functions for common tasks.
     *
     * The Utils class offers utility functions for tasks such as handling signals and
     * splitting strings. All methods are static, and the class cannot be instantiated.
     *
     * Key features include:
     * - Signal handling for the server.
     * - String manipulation utilities.
     */
	class Utils
    {
        private:
            Utils();
            ~Utils();
            Utils(const Utils& other);
            Utils& operator=(const Utils& other);
        public:
            static  void signalHandler(int signum);
            static  std::vector<string> splitString(const string& s, const string& del = " ");
			static PathType getPathType(const std::string &path);
        	static int ft_stoi(std::string str);
        	static std::string statusCodeString(short statusCode);
        	static int	checkFile(const std::string &path, int mode);
        	static std::string readFile(const std::string &path);
        	static int fileExistReadable(const std::string &path, const std::string &index);
        	static bool isValidLocationPath(const std::string &path);
        	static std::string getConfigFilePath(int argc, char** argv);
    };
} // namespace WebServer
