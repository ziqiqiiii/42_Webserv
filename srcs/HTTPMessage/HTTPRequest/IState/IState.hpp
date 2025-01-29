#pragma once

class HTTPRequest;

class IState
{   
    public:
        virtual ~IState() {};
        virtual void handle(HTTPRequest& httpReques, char c) = 0;
};
