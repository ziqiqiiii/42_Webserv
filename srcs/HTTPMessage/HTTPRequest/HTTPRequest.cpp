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

void HTTPRequest::checker() {}

void    HTTPRequest::appendToBuffer(char* buffer, size_t& index, size_t maxLen, char c)
{
    if (index < maxLen - 1) {
        buffer[index++] = c;
    }
}

void    HTTPRequest::feedFromFd(int fd) {
    this->_fd = fd;
    char buffer[BUFFER_SIZE];
    int bytesRead = 0;

    if (fd < 0) {
        perror("Invalid file descriptor");
        this->TransitionTo(new ErrorState());
        return;
    }

    // cout << "dassdad" << endl;
    fcntl(fd, F_SETFL, O_NONBLOCK);
    if ((bytesRead = read(fd, buffer, BUFFER_SIZE)) > 0) {
            this->_current_state->handle(*this, buffer[0]);
    } 
    if (bytesRead == 0) {
        cout << "End Reading" << endl;  
        close(fd);
        memset(buffer, 0, sizeof(buffer));
        this->TransitionTo(new DoneState());
    }
    else if (bytesRead < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            std::cerr << "No data available yet. Try again later." << std::endl;
            return;
        }
        perror("Error");
        this->TransitionTo(new ErrorState());
        this->_current_state->handle(*this, static_cast<char>(HttpStatusCode::InternalServerError));
    }
}

void	HTTPRequest::TransitionTo(IState* state)
{
    cout << "Context: Transition to " << typeid(*state).name() << endl;
    if (this->_current_state != NULL)
        delete this->_current_state;
    this->_current_state = state;
    this->_current_state->setRequestContext(this);
}
