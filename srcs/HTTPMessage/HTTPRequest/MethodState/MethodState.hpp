#pragma once

# include "IState.hpp"
# include "HTTPRequest.hpp"

class HTTPRequest;

class MethodState: public IState
{
    public:
        MethodState();
        ~MethodState();
        MethodState(const MethodState& tmp);
        MethodState& operator=(const MethodState& tmp);

        void handle(HTTPRequest& httpReques, char c);
};
