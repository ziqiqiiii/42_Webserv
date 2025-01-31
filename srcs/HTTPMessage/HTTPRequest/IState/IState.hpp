#pragma once

namespace State
{
    enum State
    {
        Idle, 
        Method,
        Uri,
        HttpVersion,
        Header,
        Body,
        Done, 
        Error,
    };
}

class HTTPRequest;

class IState
{
	private:
		HTTPRequest* _request;

    public:
        virtual ~IState();
        virtual void handle(HTTPRequest& httpReques, char c) = 0;
		void	setRequestContext(HTTPRequest *request);
};
