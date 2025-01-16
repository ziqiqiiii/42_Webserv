# include "../../includes/Logger/Logger.hpp"

/**
 * @brief Default constructor for Logger.
 * Initializes a Logger object. Private to enforce Singleton design.
 */
WebServer::Logger::Logger() {}

/**
 * @brief Destructor for Logger.
 * Cleans up resources used by the Logger object. Private to enforce Singleton design.
 */
WebServer::Logger::~Logger() {}

/**
 * @brief Copy constructor for Logger.
 *
 * Copies the instance pointer from another Logger object.
 * 
 * @param other The Logger object to copy from.
 */
WebServer::Logger::Logger(const Logger &other) { instancePtr = other.instancePtr; }

/**
 * @brief Assignment operator for Logger.
 *
 * Assigns the instance pointer from another Logger object.
 * 
 * @param other The Logger object to assign from.
 * @return Logger& A reference to the updated Logger object.
 */
WebServer::Logger& WebServer::Logger::operator=(const Logger &other)
{
	if (this != &other)
        instancePtr = other.instancePtr;
    return *this;
}

WebServer::Logger* WebServer::Logger::instancePtr = nullptr; /**< Static pointer to the Singleton instance of Logger. */
std::mutex WebServer::Logger::mtx; /**< Mutex to ensure thread safety during Singleton instance creation. */

/**
 * @brief Retrieves the Singleton instance of the Logger class.
 *
 * Ensures that only one instance of the Logger class exists. If the instance
 * does not already exist, it creates one in a thread-safe manner.
 *
 * @return Logger* Pointer to the Singleton instance of the Logger class.
 */
WebServer::Logger* WebServer::Logger::getInstance() {
	if (instancePtr == nullptr) {
		std::lock_guard<std::mutex> lock(mtx);
		if (instancePtr == nullptr) {
			instancePtr = new WebServer::Logger();
		}
	}
	return instancePtr;
}

/**
 * @brief Logs a formatted message to the console with the specified color.
 *
 * This method uses ANSI escape codes to print the message in the given color.
 * It supports printf-style formatting for the message. Timestamps are automatically
 * appended to each log entry.
 *
 * @param color The color code for the message (e.g., `RED`, `CYAN`).
 * @param msg The format string for the message.
 * @param ... The arguments for the format string.
 */
void	WebServer::Logger::logMsg(const char *color, const char* msg, ...)
{
	char		output[8192];
	va_list		args;
	
	va_start(args, msg); 
	//vsnprintf(buffer, sizeof(buffer), msg, va_list)
	// returns the number of characters written if there were no size elimit
	int n = vsnprintf(output, sizeof(output), msg, args);
	va_end(args);
	// Check for buffer overflow
	if (n < 0)
	{
		cerr << "Error: Failed to format log message." << endl;
		return;
	}
	if (static_cast<size_t>(n) >= sizeof(output))
	{
		cerr << "Warning: Log message truncated due to buffer size." << endl;
	}
	string date = getCurrTime();
	cout << color << date << output << RESET << endl;
}

/**
 * @brief Retrieves the current time as a formatted string.
 *
 * The timestamp includes the current date and time in GST (GMT+8). If the hour exceeds 24,
 * the date is adjusted accordingly.
 *
 * @return string The current timestamp in a formatted string.
 */
string WebServer::Logger::getCurrTime()
{
	char date[50];
	time_t now = time(0);
	// gmtime converts time_t value into a tm struct, and
	// returns a pointer to this tm struct
	// tm struct fields: tm_year, tm_month, tm_hour, etc...
	struct tm tm = *gmtime(&now);
	// Add global time shift(GST) and adjust date 
	tm.tm_hour += GST;
	if (tm.tm_hour >= 24)
	{
		tm.tm_hour -= 24;
		tm.tm_mday += 1;
	}
	// Formats the time stored in tm struct into string
	strftime(date, sizeof(date), "[%Y-%m-%d  %H:%M:%S]   ", &tm);
	return (string(date));
}
