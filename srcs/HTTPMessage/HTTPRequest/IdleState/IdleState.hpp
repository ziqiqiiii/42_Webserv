#pragma once

# include "IState.hpp"
# include "HTTPRequest.hpp"

class HTTPRequest;

class IdleState : public IState
{
    public:
        IdleState();
        ~IdleState();
        IdleState(const IdleState& tmp);
        IdleState& operator=(const IdleState& tmp);

        void handle(HTTPRequest& httpRequest, char c);
};
