# include "../../includes/HTTPMessage/HTTPMessage.hpp"

std::vector<string> splitString(const string& s, const string& del = " ")
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
	// cout << "index of pos2: " << pos2 << endl;
	// while (pos2 != string::npos) {
	// 	line = headers.substr(pos1, pos2 - pos1);
	// 	cout << "line: " << line << endl;
	// 	cout << "[inside] index of pos2: " << pos2 << endl;
	// 	pos2 = pos2 == string::npos ? headers.length() : pos2;
	// 	name = line.substr(pos1, line.find(": "));
	// 	value = line.substr(line.find(": ") + 2);
	// 	cout << name << value << endl;
	// 	this->_headers.push_back(KeyValue(name, value));
	// 	cout << this->_headers[i].key << ":" << endl;
	// 	pos1 = pos2 + 2;
	// 	pos2 = headers.find(CRLF, pos1);
	// }

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
	this->parseMessage(message);
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
	std::vector<string> tmp = splitString(headers, CRLF);
	for (size_t i = 0; i < tmp.size(); i++)
	{
		key_value = splitString(tmp[i], ": ");
		this->_headers.push_back(KeyValue(key_value[0], key_value[1]));
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
