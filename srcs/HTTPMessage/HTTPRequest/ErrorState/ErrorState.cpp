# include "ErrorState.hpp"

ErrorState::ErrorState() {}

ErrorState::~ErrorState() {}

ErrorState::ErrorState(const ErrorState& tmp) { *this = tmp; }

ErrorState& ErrorState::operator=(const ErrorState& tmp)
{
    if (this != &tmp)
        *this = tmp;
    return *this;
}

void ErrorState::handle(HTTPRequest& httpRequest, char c)
{
    httpRequest.setStateEnum(State::Error);
    httpRequest.setErrorCode(static_cast<int>(c));
}