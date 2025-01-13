#pragma once

# include <stdio.h>
# include <stdlib.h>
# include <sys/socket.h> // for functions like socket, bind, listen, accept and others
# include <netinet/in.h> // some macros for socket
# include <netdb.h> // getaddrinfo
# include <string.h> // strerror
# include <fcntl.h>
# include <iostream>
# include <unistd.h>
# include <csignal>
# include <vector>

# include "../HTTPMessage.hpp"

using std::cout;
using std::endl;
using std::string;

//MACROS 
# define SP " "

class HTTPRequest: public HTTPMessage
{
    private:
        string	_method;
		string	_request_target;
		string	_http_version;

        //Private Setters 
        void _setMethod(const string& method);
        void _setRequestTarget(const string& request_target);
        void _setHttpVersion(const string& http_version);
    public:
        HTTPRequest();
        ~HTTPRequest();
        HTTPRequest(const HTTPRequest& src);
        HTTPRequest& operator=(const HTTPRequest& src);
        HTTPRequest(const string& message);

        //Getters
		string	getRequestMethod()	const;
		string	getRequestTarget()	const;
		string	getHttpVersion()	const;

		void checker();
};
