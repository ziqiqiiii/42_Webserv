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
# include <map>
# include "../Utils/Utils.hpp"

using std::cout;
using std::endl;
using std::string;

//MACROS 
# define CRLF "\r\n"
# define FIELD_LINE_SEPARATOR "\r\n\r\n"

class HTTPMessage
{
    protected:
        string							_start_line;
        std::map<string, string>		_headers;
        string							_body;

	private:
        void    						_parseStartline(const string& start_line);
        void    						_parseHeaders(const string& headers);
        void    						_parseBody(const string& body);
		
    public:
        HTTPMessage();
        ~HTTPMessage();
        HTTPMessage(const HTTPMessage& src);
        HTTPMessage& operator=(const HTTPMessage& src);
        HTTPMessage(const string& message);

        //Setters
        void							setHeader(const string& name, const string& value);
        void							setBody(string body);

        //Getters
        string							getFieldName(const string& name) const;
        const std::map<string, string>	getHeaders() const;
        string							getBody() const;
        string							getMessage() const;
		string							getStarline() const;

		void    						parseMessage(const string& message);

        //Exceptions 
        class HeadersDoNotExist: public std::exception
        {
            public:
                virtual const char* what() const throw()
                {
                    return "Headers don't exist in HTTP message";
                }
        };

        virtual void checker() = 0;
};

std::ostream&	operator<<(std::ostream& os, const std::map<string, string>& headers);
