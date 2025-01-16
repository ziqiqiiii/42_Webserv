# include "../../includes/Logger/Logger.hpp"

void	Logger::logMsg(const char *color, const char* msg, ...)
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

string Logger::getCurrTime()
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
