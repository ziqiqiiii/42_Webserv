# include "../../../includes/HTTPMessage/HTTPRequest/HTTPRequest.hpp"

HTTPRequest::HTTPRequest() {}

HTTPRequest::~HTTPRequest() {}

HTTPRequest::HTTPRequest(const HTTPRequest& src): HTTPMessage() { *this = src; }

HTTPRequest& HTTPRequest::operator=(const HTTPRequest& src)
{
	if (this != &src) {
		this->_method = src._method;
        this->_request_target = src._request_target;
        this->_http_version = src._http_version;
	}
	return *this;
}

HTTPRequest::HTTPRequest(const string& message): HTTPMessage(message)
{
	size_t pos, pos1;
	pos = this->_start_line.find(SP);
	this->_setMethod(this->_start_line.substr(0, pos));
	pos1 = this->_start_line.find(SP, pos);
	this->_setRequestTarget(this->_start_line.substr(pos+2, pos1));
	pos = pos1;
	pos1 = this->_start_line.find(SP, pos);
	this->_setHttpVersion(this->_start_line.substr(pos+2, pos1));
}

//Private Setters
void HTTPRequest::_setMethod(const string& method) { this->_method = method; }

void HTTPRequest::_setRequestTarget(const string& request_target) { this->_request_target = request_target; }

void HTTPRequest::_setHttpVersion(const string& http_version) { this->_http_version = http_version; }

//Getters
string HTTPRequest::getRequestMethod() const { return this->_method; }

string HTTPRequest::getRequestTarget() const { return this->_request_target; }

string HTTPRequest::getHttpVersion() const { return this->_http_version; }

void HTTPRequest::checker() {}

