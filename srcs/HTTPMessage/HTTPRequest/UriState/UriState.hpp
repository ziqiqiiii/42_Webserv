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

class UriState: public IState
{
    public:
        UriState();
        ~UriState();
        UriState(const UriState& tmp);
        UriState& operator=(const UriState& tmp);

        void handle(HTTPRequest& httpReques, char c);
};
