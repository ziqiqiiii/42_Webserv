#pragma once

# include "HTTPMessage.hpp"
# include "HTTPRequest.hpp"
# include "IState.hpp"

class HTTPRequest;

class HeaderState: public IState
{
    public:
        HeaderState();
        ~HeaderState();
        HeaderState(const HeaderState& tmp);
        HeaderState& operator=(const HeaderState& tmp);

        void handle(HTTPRequest& httpReques, char c);
};
