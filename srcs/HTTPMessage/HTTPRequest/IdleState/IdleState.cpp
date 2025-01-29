# include "IdleState.hpp"

IdleState::IdleState() {}

IdleState::~IdleState() {}

IdleState::IdleState(const IdleState& tmp) { *this = tmp; }

IdleState& IdleState::operator=(const IdleState& tmp)
{
    if (this != &tmp)
        *this = tmp;
    return *this;
}

void IdleState::handle(HTTPRequest& httpRequest, char c)
{
    if (!isspace(c)) {
        httpRequest.TransitionTo((IState *)(new MethodState()));
        httpRequest.feedFromFd(httpRequest.getFd());
    }
}
