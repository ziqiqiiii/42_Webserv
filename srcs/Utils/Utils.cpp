# include "../includes/Utils/Utils.hpp"
# include <sys/stat.h>

/**
 * @brief Default constructor for Utils.
 * Private to prevent instantiation.
 */
WebServer::Utils::Utils() {}

/**
 * @brief Destructor for Utils.
 * Private to prevent deletion of instances.
 */
WebServer::Utils::~Utils() {}

/**
 * @brief Copy constructor for Utils.
 * Private to prevent copying of the Utils class.
 *
 * @param other The Utils object to copy from.
 */
WebServer::Utils::Utils(const Utils& other) { *this = other; }

/**
 * @brief Assignment operator for Utils.
 * Private to prevent assignment of the Utils class.
 *
 * @param other The Utils object to assign from.
 * @return Utils& A reference to the updated Utils object.
 */
WebServer::Utils& WebServer::Utils::operator=(const Utils& other)
{
    if (this != &other)
        *this = other;
    return *this; 
}

/**
 * @brief Handles signals received by the server.
 *
 * Logs the received signal and exits the application.
 *
 * @param signum The signal number to handle (e.g., SIGINT, SIGTERM).
 */
void WebServer::Utils::signalHandler(int signum)
{
    WebServer::Logger *logManager = WebServer::Logger::getInstance();

    logManager->logMsg(RED, "Interrup signal (%d) received.\n", signum);
    exit(signum);
}

/**
 * @brief Splits a string into a vector of substrings based on a specified delimiter.
 *
 * This method takes an input string and a delimiter, then splits the string into
 * substrings wherever the delimiter occurs. The substrings are returned as a vector.
 *
 * @param s The input string to split.
 * @param del The delimiter used to split the string. Defaults to a single space (" ").
 * @return std::vector<string> A vector containing the split substrings.
 */
std::vector<string> WebServer::Utils::splitString(const string& s, const string& del)
{
    std::vector<string> tokens;
    size_t start = 0;
    size_t end = s.find(del);

    while (end != string::npos) {
        tokens.push_back(s.substr(start, end - start));
        start = end + del.size();
        end = s.find(del, start);
    }
    tokens.push_back(s.substr(start, end - start)); // Add the last token

    return tokens;
}

// Check path is file, directory or other
PathType WebServer::Utils::getPathType(const std::string &path)
{
	struct stat	file_stat;

	if (stat(path.c_str(), &file_stat) == 0)
	{
		if (file_stat.st_mode & S_IFREG) // File
			return (IS_FILE);
		else if (file_stat.st_mode & S_IFDIR) // Directory
			return (IS_DIRECTORY);
		else // Other types (symlink, socket, etc.)
			return (IS_OTHER);
	}
	return (STATFAIL); // stat failed
}

int WebServer::Utils::ft_stoi(std::string str)
{
	std::stringstream ss(str);
	if (str.length() > 10)
		throw std::exception();
	for (size_t i = 0; i < str.length(); ++i)
	{
		if(!isdigit(str[i]))
			throw std::exception();
	}
	int res;
	ss >> res;
	return (res);
}

int	WebServer::Utils::checkFile(const std::string &path, int mode)
{
	return (access(path.c_str(), mode));
}

std::string WebServer::Utils::readFile(const std::string &path)
{
	if (path.empty())
		return (NULL);
	// Open the file in read mode
	std::ifstream config_file(path.c_str());
	if (!config_file) 
		return (NULL);
	// Read the file into a string
	std::stringstream ss;
	ss << config_file.rdbuf();
	return (ss.str());
}

//Check file exists and is readable for two locations(index or path+index)
int WebServer::Utils::fileExistReadable(const std::string &path, const std::string &index)
{
	std::string fullPath1 = index;
	std::string fullPath2 = path + index;
	if ((Utils::getPathType(fullPath1) == IS_FILE && Utils::checkFile(fullPath1, R_OK) == 0) ||
		(Utils::getPathType(fullPath2) == IS_FILE && Utils::checkFile(fullPath2, R_OK) == 0))
		return (0);
	return (-1);
}

bool WebServer::Utils::isValidLocationPath(const std::string &path)
{
	// Define invalid characters
	static const std::string invalid_chars = "*?<>|\"\\\0";
	static const std::string whitespace = " \t\n\r";

	// Path must not be empty and start with /
	if (path.empty() || path[0] != '/')
		return (false);

	// Check for invalid characters
	if (path.find_first_of(invalid_chars) != std::string::npos)
		return (false);

	// No whitespaces
	if (path.find_first_of(whitespace) != std::string::npos)
		return (false);
		
	// Normalize and validate double slashes (e.g., "//")
	if (path.find("//") != std::string::npos)
		return (false);

	// If all checks pass, path is valid
	return (true);
}

std::string WebServer::Utils::getConfigFilePath(int argc, char** argv)
{
	if (argc > 2)
	{
		WebServer::Logger *logManager = WebServer::Logger::getInstance();
		logManager->logMsg(RED, "Error: Wrong number of arguments.");
		logManager->logMsg(RED, "Usage: ./webserv or ./webserv [config file path]");
		throw std::invalid_argument("Invalid arguments.");
	}
	return ((argc == 1) ? "configs/default.conf" : argv[1]);
}

std::string WebServer::Utils::statusCodeString(short statusCode)
{
	switch (statusCode)
	{
		case 100:
			return "Continue";
		case 101:
			return "Switching Protocol";
		case 102:
			return "Processing";
		case 200:
			return "OK";
		case 201:
			return "Created";
		case 202:
			return "Accepted";
		case 203:
			return "Non-Authoritative Information";
		case 204:
			return "No Content";
		case 205:
			return "Reset Content";
		case 206:
			return "Partial Content";
		case 207:
			return "Multi_status";
		case 208:
			return "Already Reported";
		case 300:
			return "Multiple Choice";
		case 301:
			return "Moved Permanently";
		case 302:
			return "Moved Temporarily";
		case 303:
			return "See Other";
		case 304:
			return "Not Modified";
		case 305:
			return "Use Proxy";
		case 306:
			return "Switch Proxy";
		case 307:
			return "Temporary Redirect";
		case 308:
			return "Permanent Redirect";
		case 400:
			return "Bad Request";
		case 401:
			return "Unauthorized";
		case 402:
			return "Payment Required";
		case 403:
			return "Forbidden";
		case 404:
			return "Not Found";
		case 405:
			return "Method Not Allowed";
		case 406:
			return "Not Acceptable";
		case 407:
			return "Proxy Authentication Required";
		case 408:
			return "Request Timeout";
		case 409:
			return "Conflict";
		case 410:
			return "Gone";
		case 411:
			return "Length Required";
		case 412:
			return "Precondition Failed";
		case 413:
			return "Payload Too Large";
		case 414:
			return "URI Too Long";
		case 415:
			return "Unsupported Media Type";
		case 416:
			return "Requested Range Not Satisfiable";
		case 417:
			return "Expectation Failed";
		case 418:
			return "I'm a teapot";
		case 421:
			return "Misdirected Request";
		case 425:
			return "Too Early";
		case 426:
			return "Upgrade Required";
		case 428:
			return "Precondition Required";
		case 429:
			return "Too Many Requests";
		case 431:
			return "Request Header Fields Too Large";
		case 444:
			return "No Response";
		case 451:
			return "Unavailable for Legal Reasons";
		case 500:
			return "Internal Server Error";
		case 501:
			return "Not Implemented";
		case 502:
			return "Bad Gateway";
		case 503:
			return "Service Unavailable";
		case 504:
			return "Gateway Timeout";
		case 505:
			return "HTTP Version Not Supported";
		case 506:
			return "Variant Also Negotiates";
		case 507:
			return "Insufficient Storage";
		case 510:
			return "Not Extended";
		case 511:
			return "Network Authentication Required";
		case 520:
			return "Unknown Error";
		case 521:
			return "Web Server is Down";
		case 523:
			return "Origin is Unreachable";
		case 524:
			return "A Timeout Occured";
		case 598:
			return "Network Read Timeout Error";
		case 599:
			return "Network Connect Timeout Error";
		default:
			return "Undefined";
		}
}
