# include "../../../includes/HTTPMessage/HTTPRequest/HTTPRequest.hpp"

/**
 * @brief Default constructor for HTTPRequest.
 * Initializes an empty HTTPRequest object.
 */
HTTPRequest::HTTPRequest() {}

/**
 * @brief Destructor for HTTPRequest.
 * Cleans up resources used by the HTTPRequest object.
 */
HTTPRequest::~HTTPRequest() {}

/**
 * @brief Copy constructor for HTTPRequest.
 *
 * @param src The HTTPRequest object to copy from.
 */
HTTPRequest::HTTPRequest(const HTTPRequest& src): HTTPMessage() { *this = src; }

/**
 * @brief Assignment operator for HTTPRequest.
 *
 * Copies the contents of one HTTPRequest object to another.
 *
 * @param src The HTTPRequest object to assign from.
 * @return HTTPRequest& A reference to the updated HTTPRequest object.
 */
HTTPRequest& HTTPRequest::operator=(const HTTPRequest& src)
{
	if (this != &src) {
		this->_method = src._method;
        this->_request_target = src._request_target;
        this->_http_version = src._http_version;
	}
	return *this;
}

/**
 * @brief Constructs an HTTPRequest object from a raw HTTP message string.
 *
 * Parses the start line of the message to extract the HTTP method, request target,
 * and HTTP version.
 *
 * @param message The raw HTTP request message.
 */
HTTPRequest::HTTPRequest(const string& message): HTTPMessage(message)
{
	std::vector<string> split_string = WebServer::Utils::splitString(this->_start_line);
	for (size_t i = 0; i < split_string.size(); i++)
	{
		switch (i)
		{
			case 0:
				this->_setMethod(split_string[i]);
				break;
			case 1:
				this->_setRequestTarget(split_string[i]);
				break;
			case 2:
				this->_setHttpVersion(split_string[i]);
				break;
			default:
				throw RequestLineError();
				break;
		}
	}
	this->checker();
}

// Private Setters

/**
 * @brief Sets the HTTP method of the request.
 *
 * @param method The HTTP method (e.g., GET, POST).
 */
void HTTPRequest::_setMethod(const string& method) { this->_method = method; }

/**
 * @brief Sets the request target of the HTTP request.
 *
 * @param request_target The target resource of the HTTP request (e.g., "/index.html").
 */
void HTTPRequest::_setRequestTarget(const string& request_target) { this->_request_target = request_target; }

/**
 * @brief Sets the HTTP version of the request.
 *
 * @param http_version The HTTP version (e.g., "HTTP/1.1").
 */
void HTTPRequest::_setHttpVersion(const string& http_version) { this->_http_version = http_version; }

// Getters

/**
 * @brief Retrieves the HTTP method of the request.
 *
 * @return string The HTTP method (e.g., GET, POST).
 */
string HTTPRequest::getRequestMethod() const { return this->_method; }

/**
 * @brief Retrieves the request target of the HTTP request.
 *
 * @return string The target resource (e.g., "/index.html").
 */
string HTTPRequest::getRequestTarget() const { return this->_request_target; }


/**
 * @brief Retrieves the HTTP version of the request.
 *
 * @return string The HTTP version (e.g., "HTTP/1.1").
 */
string HTTPRequest::getHttpVersion() const { return this->_http_version; }

/**
 * @brief Abstract method for additional validation or checks.
 *
 * This method is a placeholder to be implemented in derived classes.
 */
void HTTPRequest::checker() {}
