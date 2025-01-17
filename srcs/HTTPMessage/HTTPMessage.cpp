# include "../../includes/HTTPMessage/HTTPMessage.hpp"

HTTPMessage::HTTPMessage() {}

HTTPMessage::~HTTPMessage()
{
	this->_headers.clear();
}

HTTPMessage::HTTPMessage(const HTTPMessage& src) { *this = src; }

HTTPMessage& HTTPMessage::operator=(const HTTPMessage& src)
{
	if (this != &src) {
		this->_headers = src._headers;
		this->_body = src._body;
	}
	return *this;
}

HTTPMessage::HTTPMessage(const string& message)
{
	this->parseMessage(message);
}


void HTTPMessage::setHeader(const string& name, const string& value)
{
	this->_headers[name] = value;
}

void HTTPMessage::setBody(string body)
{
	this->_body = body;
}

string HTTPMessage::getFieldName(const string& name) const
{
	try
	{
		return this->_headers.at(name);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return NULL;
}

const std::map<string, string> HTTPMessage::getHeaders() const
{
	return this->_headers;
}

string HTTPMessage::getBody() const
{
	return this->_body;
}

string HTTPMessage::getMessage() const
{
	string message;

	for (std::map<string, string>::const_iterator it = this->_headers.begin(); it != this->_headers.end(); it++) {
		message += it->first + ": " + it->second + CRLF;
	}
	message += CRLF + this->_body;
	return message;
}

string HTTPMessage::getStarline() const { return this->_start_line; }

void HTTPMessage::parseMessage(const std::string& message) {
    // Check if the message contains a CRLF to separate the start line from headers
    size_t startLineEnd = message.find(CRLF);
    if (startLineEnd == std::string::npos) {
        throw HTTPMessage::HeadersDoNotExist();
    }

    // Parse the start line (e.g., request/response line)
    this->_parseStartline(message.substr(0, startLineEnd));

    // Find the position of the field line separator (empty line between headers and body)
    size_t fieldLinePos = message.find(FIELD_LINE_SEPARATOR, startLineEnd + string(CRLF).size());
    if (fieldLinePos == std::string::npos) {
        throw std::runtime_error("FIELD_LINE_SEPARATOR not found after headers");
    }

    // Calculate the length of the headers section
    size_t headersStart = startLineEnd + string(CRLF).size();
    size_t headerLength = fieldLinePos - headersStart;

    // Ensure header length is within bounds
    if (headersStart + headerLength > message.size()) {
        throw std::out_of_range("Header length exceeds message size");
    }

    // Parse headers
    this->_parseHeaders(message.substr(headersStart, headerLength));

    // Calculate the position where the body starts
    size_t bodyStart = fieldLinePos + string(FIELD_LINE_SEPARATOR).size();

    // Parse the body if it exists
    if (bodyStart < message.size()) {
        this->_parseBody(message.substr(bodyStart));
    }
}

void HTTPMessage::_parseStartline(const string& start_line)
{
	this->_start_line = start_line;
}

void HTTPMessage::_parseHeaders(const string& headers)
{
	std::vector<string> key_value;
	std::vector<string> tmp = Utils::splitString(headers, CRLF);
	for (size_t i = 0; i < tmp.size(); i++)
	{
		key_value = Utils::splitString(tmp[i], ": ");
		this->_headers[key_value[0]] = key_value [1];
	}
}

void HTTPMessage::_parseBody(const string& body)
{
	this->_body = body;
}

std::ostream& operator<<(std::ostream& os, const std::map<std::string, std::string>& headers)
{
    for (std::map<std::string, std::string>::const_iterator it = headers.begin(); it != headers.end(); ++it)
    {
        os << it->first << ": " << it->second << "\n";
    }
    return os;
}
