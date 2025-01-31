# include "MethodState.hpp"

MethodState::MethodState() {}

MethodState::~MethodState() {}

MethodState::MethodState(const MethodState& tmp) { *this = tmp; }

MethodState& MethodState::operator=(const MethodState& tmp)
{
    if (this != &tmp)
        *this = tmp;
    return *this;
}

void MethodState::handle(HTTPRequest& httpRequest, char c)
{
    if (isspace(c))
        httpRequest.TransitionTo(new UriState());
    else {
        httpRequest.appendToMethod(c);
    }
    httpRequest.feedFromFd(httpRequest.getFd());
}
