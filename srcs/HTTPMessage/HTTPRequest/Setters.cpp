# include "HTTPRequest.hpp"

void HTTPRequest::appendToMethod(char c)
{ 
    appendToBuffer(_method, _methodIdx, MAX_METHOD_LEN, c); 
}

void HTTPRequest::appendToUri(char c)
{
    appendToBuffer(_request_target, _uriIdx, MAX_URI_LEN, c);
}

void HTTPRequest::appendToVersion(char c)
{
    appendToBuffer(_http_version, _versionIdx, MAX_VERSION_LEN, c);
}

void HTTPRequest::appendToCurrentHeader(char c)
{
    appendToBuffer(_currentHeader, _headerIdx, MAX_HEADER_LEN, c);
}

void HTTPRequest::appendToBody(char c)
{
    appendToBuffer(_body, _bodyIdx, MAX_BODY_LEN, c);
}

void HTTPRequest::storeHeader()
{
    try {
        string header(this->_currentHeader, this->_headerIdx);
        std::vector<string> split_string = WebServer::Utils::splitString(header, ": ");
        cout << split_string[0] << " " << split_string[1] << endl;
        this->_headers[split_string[0]] = split_string[1];
		memset(this->_currentHeader, 0, this->_headerIdx);
    	this->_headerIdx = 0;
    } catch (std::exception &e) {
        this->TransitionTo(new ErrorState());
        this->_current_state->handle(*this, static_cast<char>(HttpStatusCode::InternalServerError));
    }

}

void    HTTPRequest::setErrorCode(int error_code)
{
    this->_error_code = error_code;
}

void    HTTPRequest::setStateEnum(int state) { this->_state_enum = state; }
