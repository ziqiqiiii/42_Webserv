# include "BodyState.hpp"

BodyState::BodyState() {}

BodyState::~BodyState() {}

BodyState::BodyState(const BodyState& tmp) { *this = tmp; }

BodyState& BodyState::operator=(const BodyState& tmp)
{
    if (this != &tmp)
        *this = tmp;
    return *this;
}

void BodyState::handle(HTTPRequest& httpRequest, char c)
{
    if (httpRequest.getBody()[MAX_BODY_LEN - 2] != '\0') { // Check for body completion
        httpRequest.appendToBody(c);
    } else {
        httpRequest.TransitionTo(new DoneState()); // Transition to DoneState when body is complete
    }
}
