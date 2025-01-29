# include "HTTPRequest.hpp"

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
string	HTTPRequest::getHttpVersion() const { return this->_http_version; }

size_t	HTTPRequest::getFd() const { return this->_fd; }

string	HTTPRequest::getBody() const { return string(this->_body, this->_bodyIdx); }

std::map<string, string>	HTTPRequest::getHeaders() const { return this->_headers; }
