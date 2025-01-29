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

class ErrorState: public IState
{
    public:
        ErrorState();
        ~ErrorState();
        ErrorState(const ErrorState& tmp);
        ErrorState& operator=(const ErrorState& tmp);

        void handle(HTTPRequest& httpReques, char c);
};