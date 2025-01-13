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

using std::cout;
using std::endl;
using std::string;

//MACROS 
# define CRLF "\r\n"
# define FIELD_LINE_SEPARATOR "\r\n\r\n"

//Struct for Key-Value pair
struct KeyValue {
    string key;
    string value;

    //Struct Constructor 
    KeyValue(string key, string value): key(key), value(value) {}
};

class HTTPMessage
{
    private:
        string  _start_line;
        std::vector<KeyValue>   _headers;
        string  _body;

        void    _parseMessage(const string& message);
        void    _parseStartline(const string& start_line);
        void    _parseHeaders(const string& headers);
        void    _parseBody(const string& body);
    public:
        HTTPMessage();
        ~HTTPMessage();
        HTTPMessage(const HTTPMessage& src);
        HTTPMessage& operator=(const HTTPMessage& src);
        HTTPMessage(const string& message);

        //Setters
        void setHeader(const string& name, const string& value);
        void setBody(string body);

        //Getters
        string getFieldName(const string& name) const;
        const std::vector<KeyValue> getHeaders() const;
        string getBody() const;
        string getMessage() const;

        //Exceptions 
        class HeadersDoNotExist: public std::exception
        {
            public:
                virtual const char* what() const throw()
                {
                    return "Headers doesn't exits in HTTP message";
                }
        };


        virtual void checker() = 0;
};
