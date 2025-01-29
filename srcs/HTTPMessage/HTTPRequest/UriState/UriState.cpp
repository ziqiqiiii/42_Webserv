# include "UriState.hpp"

UriState::UriState() {}

UriState::~UriState() {}

UriState::UriState(const UriState& tmp) { *this = tmp; }

UriState& UriState::operator=(const UriState& tmp)
{
    if (this != &tmp)
        *this = tmp;
    return *this;
}

void UriState::handle(HTTPRequest& httpRequest, char c)
{
    if (isspace(c))
        httpRequest.TransitionTo(new HttpVersionState());
    else
        httpRequest.appendToMethod(c);
}
