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

class DoneState: public IState
{
    public:
        DoneState();
        ~DoneState();
        DoneState(const DoneState& tmp);
        DoneState& operator=(const DoneState& tmp);

        void handle(HTTPRequest& httpReques, char c);
};
