# include "../includes/Utils/Utils.hpp"

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
