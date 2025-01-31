# include "HttpVersionState.hpp"

HttpVersionState::HttpVersionState() {}

HttpVersionState::~HttpVersionState() {}

HttpVersionState::HttpVersionState(const HttpVersionState& tmp) { *this = tmp; }

HttpVersionState& HttpVersionState::operator=(const HttpVersionState& tmp)
{
    if (this != &tmp)
        *this = tmp;
    return *this;
}

void HttpVersionState::handle(HTTPRequest& httpRequest, char c)
{
    if (c == '\n')
        httpRequest.TransitionTo(new HeaderState());
    else if (c != '\r') 
        httpRequest.appendToVersion(c);
    httpRequest.feedFromFd(httpRequest.getFd());
}