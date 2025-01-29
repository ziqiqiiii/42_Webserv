#pragma once

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <iostream>
# include <unistd.h>
# include <csignal>
# include <map>

# include "HTTPRequest.hpp"
# include "IState.hpp"

class HTTPRequest;

class HttpVersionState: public IState
{
    public:
        HttpVersionState();
        ~HttpVersionState();
        HttpVersionState(const HttpVersionState& tmp);
        HttpVersionState& operator=(const HttpVersionState& tmp);

        void handle(HTTPRequest& httpReques, char c);
};
