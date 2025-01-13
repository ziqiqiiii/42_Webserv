# include "../../includes/HTTPMessage/HTTPMessage.hpp"

HTTPMessage::HTTPMessage() {}

HTTPMessage::~HTTPMessage() {}

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
	this->_parseMessage(message);
}


void HTTPMessage::setHeader(const string& name, const string& value)
{
	this->_headers.push_back(KeyValue(name, value));
}

void HTTPMessage::setBody(string body)
{
	this->_body = body;
}

string HTTPMessage::getFieldName(const string& name) const
{
	for (size_t i = 0; i < this->_headers.size(); i++) {
		if (this->_headers[i].key == name)
			return this->_headers[i].value;
	}
	return NULL;
}

const std::vector<KeyValue> HTTPMessage::getHeaders() const
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
	size_t size = this->_headers.size();

	for (size_t i = 0; i < size; i++) {
		message += this->_headers[i].key + ": " + this->_headers[i].value + CRLF;
	}
	message += CRLF + this->_body;
	return message;
}

string HTTPMessage::getStarline() const { return this->_start_line; }

void HTTPMessage::_parseMessage(const string& message)
{
    size_t pos;

    pos = message.find(CRLF);
	if (pos == string::npos)
		throw HTTPMessage::HeadersDoNotExist();
	this->_parseStartline(message.substr(0, pos));
	this->_parseHeaders(message.substr(pos+2, message.find(FIELD_LINE_SEPARATOR, pos)));
	this->_parseBody(message.substr(pos + 2));
}

void HTTPMessage::_parseStartline(const string& start_line)
{
	this->_start_line = start_line;
}

void HTTPMessage::_parseHeaders(const string& headers)
{
	size_t pos1, pos2;
	string line, name, value;

	pos1 = 0;
	pos2 = headers.find(CRLF);
	while (pos2 != string::npos) {
		line = headers.substr(pos1, pos2 - pos1);
		pos1 = pos2 + 2;
		pos2 = headers.find(CRLF, pos1);
		pos2 = pos2 == string::npos ? headers.length() : pos2;
		name = line.substr(0, line.find(": "));
		value = line.substr(line.find(": ") + 2);
		this->_headers.push_back(KeyValue(name, value));
	}
}

void HTTPMessage::_parseBody(const string& body)
{
	this->_body = body;
}

std::ostream& operator<<(std::ostream& os, const std::vector<KeyValue>& headers)
{
	for (size_t i = 0; i < headers.size(); i++)
		os << headers[i].key << ": " << headers[i].value << "\n";
	return os;
}