#pragma once

# include "IState.hpp"
# include "HTTPRequest.hpp"
# include "HTTPMessage.hpp"

class HTTPRequest;

class BodyState: public IState {
     public:
        BodyState();
        ~BodyState();
        BodyState(const BodyState& tmp);
        BodyState& operator=(const BodyState& tmp);

        void handle(HTTPRequest& httpReques, char c);
};
