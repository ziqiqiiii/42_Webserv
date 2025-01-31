# include "DoneState.hpp"

DoneState::DoneState() {}

DoneState::~DoneState() {}

DoneState::DoneState(const DoneState& tmp) { *this = tmp; }

DoneState& DoneState::operator=(const DoneState& tmp)
{
    if (this != &tmp)
        *this = tmp;
    return *this;
}

void DoneState::handle(HTTPRequest& httpRequest, char c)
{
    httpRequest.setStateEnum(State::Done);
    (void) httpRequest;
    (void) c;
}