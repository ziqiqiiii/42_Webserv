# include "../../includes/HTTPMessage/HTTPMessage.hpp"

/**
 * Default constructor for the HTTPMessage class.
 * Initializes an empty HTTPMessage object.
 */
HTTPMessage::HTTPMessage() {}

/**
 * Destructor for the HTTPMessage class.
 * Clears all headers and releases resources.
 */
HTTPMessage::~HTTPMessage()
{
	this->_headers.clear();
}

/**
 * Copy constructor for the HTTPMessage class.
 *
 * @param src The HTTPMessage object to copy from.
 */
HTTPMessage::HTTPMessage(const HTTPMessage& src) { *this = src; }

/**
 * Assignment operator for the HTTPMessage class.
 *
 * @param src The HTTPMessage object to assign from.
 * @returns A reference to the updated HTTPMessage object.
 */
HTTPMessage& HTTPMessage::operator=(const HTTPMessage& src)
{
	if (this != &src) {
		this->_headers = src._headers;
		this->_body = src._body;
	}
	return *this;
}

/**
 * Constructs an HTTPMessage object from a raw message string.
 *
 * @param message The raw HTTP message string to parse.
 */
HTTPMessage::HTTPMessage(const string& message)
{
	this->parseMessage(message);
}

/**
 * Sets a header field in the HTTP message.
 *
 * @param name The name of the header field.
 * @param value The value of the header field.
 */
void HTTPMessage::setHeader(const string& name, const string& value)
{
	this->_headers.push_back(KeyValue(name, value));
}

/**
 * Sets the body of the HTTP message.
 *
 * @param body The body content as a string.
 */
void HTTPMessage::setBody(string body)
{
	this->_body = body;
}

/**
 * Retrieves the value of a header field by name.
 *
 * @param name The name of the header field to retrieve.
 * @returns The value of the header field, or NULL if not found.
 */
string HTTPMessage::getFieldName(const string& name) const
{
	for (size_t i = 0; i < this->_headers.size(); i++) {
		if (this->_headers[i].key == name)
			return this->_headers[i].value;
	}
	return NULL;
}

/**
 * Retrieves all header fields in the HTTP message.
 *
 * @returns A vector of KeyValue objects representing the headers.
 */
const std::vector<KeyValue> HTTPMessage::getHeaders() const
{
	return this->_headers;
}

/**
 * Retrieves the body of the HTTP message.
 *
 * @returns The body content as a string.
 */
string HTTPMessage::getBody() const
{
	return this->_body;
}

/**
 * Constructs the full HTTP message as a string, including headers and body.
 *
 * @returns The HTTP message as a string.
 */
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

/**
 * Retrieves the start line of the HTTP message.
 *
 * @returns The start line as a string.
 */
string HTTPMessage::getStarline() const { return this->_start_line; }

/**
 * Parses a raw HTTP message into its components: start line, headers, and body.
 *
 * @param message The raw HTTP message string to parse.
 * @throws HTTPMessage::HeadersDoNotExist if no headers exist in the message.
 * @throws std::runtime_error if FIELD_LINE_SEPARATOR is not found after headers.
 * @throws std::out_of_range if header length exceeds message size.
 */
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

/**
 * Parses the start line of the HTTP message.
 *
 * @param start_line The start line as a string.
 */
void HTTPMessage::_parseStartline(const string& start_line)
{
	this->_start_line = start_line;
}

/**
 * Parses the headers of the HTTP message.
 *
 * @param headers The headers as a single string.
 */
void HTTPMessage::_parseHeaders(const string& headers)
{
	std::vector<string> key_value;
	std::vector<string> tmp = WebServer::Utils::splitString(headers, CRLF);
	for (size_t i = 0; i < tmp.size(); i++)
	{
		key_value = WebServer::Utils::splitString(tmp[i], ": ");
		this->_headers.push_back(KeyValue(key_value[0], key_value[1]));
	}
}

/**
 * Parses the body of the HTTP message.
 *
 * @param body The body as a string.
 */
void HTTPMessage::_parseBody(const string& body)
{
	this->_body = body;
}

/**
 * Overloaded stream operator to output a vector of KeyValue objects (headers).
 *
 * @param os The output stream to write to.
 * @param headers The vector of KeyValue objects to output.
 * @returns A reference to the output stream.
 */
std::ostream& operator<<(std::ostream& os, const std::vector<KeyValue>& headers)
{
	for (size_t i = 0; i < headers.size(); i++)
		os << headers[i].key << ": " << headers[i].value << "\n";
	return os;
}
