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
# include "Logger.hpp"

using std::cout;
using std::endl;
using std::string;

#define CONNECTION_TIMEOUT 60 // Time in seconds for a client to disconnect due to inactivity
#define MESSAGE_BUFFER 40000 //Size of the buffer for reading messages

#define MAX_CONTENT_LENGTH 30000000 //Maximum size of HTTP request content

enum PathType
{
	IS_FILE = 1,
	IS_DIRECTORY = 2,
	IS_OTHER = 3,
	STATFAIL = -1
};

namespace HttpStatusCode {
    enum HttpStatusCode {
        Continue = 100,
        SwitchingProtocol = 101,
        Processing = 102,
        OK = 200,
        Created = 201,
        Accepted = 202,
        NonAuthoritativeInformation = 203,
        NoContent = 204,
        ResetContent = 205,
        PartialContent = 206,
        MultiStatus = 207,
        AlreadyReported = 208,
        MultipleChoice = 300,
        MovedPermanently = 301,
        MovedTemporarily = 302,
        SeeOther = 303,
        NotModified = 304,
        UseProxy = 305,
        SwitchProxy = 306,
        TemporaryRedirect = 307,
        PermanentRedirect = 308,
        BadRequest = 400,
        Unauthorized = 401,
        PaymentRequired = 402,
        Forbidden = 403,
        NotFound = 404,
        MethodNotAllowed = 405,
        NotAcceptable = 406,
        ProxyAuthenticationRequired = 407,
        RequestTimeout = 408,
        Conflict = 409,
        Gone = 410,
        LengthRequired = 411,
        PreconditionFailed = 412,
        PayloadTooLarge = 413,
        URITooLong = 414,
        UnsupportedMediaType = 415,
        RequestedRangeNotSatisfiable = 416,
        ExpectationFailed = 417,
        ImATeapot = 418,
        MisdirectedRequest = 421,
        TooEarly = 425,
        UpgradeRequired = 426,
        PreconditionRequired = 428,
        TooManyRequests = 429,
        RequestHeaderFieldsTooLarge = 431,
        NoResponse = 444,
        UnavailableForLegalReasons = 451,
        InternalServerError = 500,
        NotImplemented = 501,
        BadGateway = 502,
        ServiceUnavailable = 503,
        GatewayTimeout = 504,
        HTTPVersionNotSupported = 505,
        VariantAlsoNegotiates = 506,
        InsufficientStorage = 507,
        NotExtended = 510,
        NetworkAuthenticationRequired = 511,
        UnknownError = 520,
        WebServerIsDown = 521,
        OriginIsUnreachable = 523,
        TimeoutOccurred = 524,
        NetworkReadTimeoutError = 598,
        NetworkConnectTimeoutError = 599,
        Undefined = 0 // Default for unknown codes
    };
}

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
