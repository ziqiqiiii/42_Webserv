# include "HTTPRequest.hpp"

/**
 * @brief Default constructor for HTTPRequest.
 * Initializes an empty HTTPRequest object.
 */
HTTPRequest::HTTPRequest(): _current_state(new IdleState()) {}

/**
 * @brief Destructor for HTTPRequest.
 * Cleans up resources used by the HTTPRequest object.
 */
HTTPRequest::~HTTPRequest() { delete this->_current_state; }

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
        // Copying state
        if (this->_current_state != NULL)
            delete this->_current_state;
        this->_current_state = new IdleState();

        // Copying members
        std::memcpy(this->_method, src._method, MAX_METHOD_LEN);
        std::memcpy(this->_request_target, src._request_target, MAX_URI_LEN);
        std::memcpy(this->_http_version, src._http_version, MAX_VERSION_LEN);
        std::memcpy(this->_body, src._body, MAX_BODY_LEN);

        this->_methodIdx = src._methodIdx;
        this->_uriIdx = src._uriIdx;
        this->_versionIdx = src._versionIdx;
        this->_headerIdx = src._headerIdx;
        this->_bodyIdx = src._bodyIdx;

        this->_headers = src._headers; // std::map has a copy assignment operator
    }
    return *this;
}

void HTTPRequest::checker()
{
	std::map<string, string> headers = this->getHeaders();
}

void    HTTPRequest::appendToBuffer(char* buffer, size_t& index, size_t maxLen, char c)
{
    if (index < maxLen - 1) {
        buffer[index++] = c;
    }
}

void    HTTPRequest::feedFromFd(int fd) {
    char buffer[BUFFER_SIZE];
    int bytesRead;

    while ((bytesRead = read(fd, buffer, BUFFER_SIZE)) > 0) {
        for (int i = 0; i < bytesRead; ++i) {
            this->_current_state->handle(*this, buffer[i]);
        }
    }

    if (bytesRead < 0) {
        this->TransitionTo(new ErrorState());
        this->_current_state->handle(*this, static_cast<char>(InternalServerError));
    }
}

void	HTTPRequest::TransitionTo(IState* state)
{
    if (this->_current_state != NULL)
        delete this->_current_state;
    this->_current_state = state;
}
